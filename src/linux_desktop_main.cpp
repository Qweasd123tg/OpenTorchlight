#include "torchlight/actor_motion.hpp"
#include "torchlight/adm_document.hpp"
#include "torchlight/collision_scene.hpp"
#include "torchlight/combat.hpp"
#include "torchlight/entity_world.hpp"
#include "torchlight/enemy_ai.hpp"
#include "torchlight/gles_scene_renderer.hpp"
#include "torchlight/level_scene.hpp"
#include "torchlight/level_transition.hpp"
#include "torchlight/logic_runtime.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/navigation_grid.hpp"
#include "torchlight/ogre_material.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/player.hpp"
#include "torchlight/random_level.hpp"
#include "torchlight/scene_geometry.hpp"
#include "torchlight/spawn_class.hpp"
#include "torchlight/unit_definition.hpp"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <linux/input-event-codes.h>
#include <poll.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <xdg-shell-client-protocol.h>

#include <algorithm>
#include <array>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_map>
#include <utility>
#include <unistd.h>
#include <vector>

namespace {

constexpr float kCameraVerticalSpan = 22.0F;

class DesktopError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct Options {
    std::filesystem::path game_directory;
    std::uint64_t frame_limit = 0;
    std::optional<std::size_t> main_stratum;
    std::uint32_t seed = 42;
};

Options parse_options(int argc, char** argv) {
    if (argc < 2) {
        throw DesktopError(
            "usage: torchlight_desktop /path/to/Torchlight/game "
            "[--frames N] [--main-stratum N --seed N]");
    }
    Options options;
    options.game_directory = argv[1];
    for (int argument = 2; argument < argc; argument += 2) {
        if (argument + 1 >= argc) {
            throw DesktopError("desktop option has no value");
        }
        const std::string name = argv[argument];
        const std::string value = argv[argument + 1];
        if (name == "--frames") {
            const auto parsed = std::from_chars(value.data(), value.data() + value.size(),
                                                options.frame_limit);
            if (value.empty() || parsed.ec != std::errc{} ||
                parsed.ptr != value.data() + value.size() || options.frame_limit == 0) {
                throw DesktopError("frame limit must be a positive integer");
            }
        } else if (name == "--main-stratum") {
            std::size_t stratum = 0;
            const auto parsed =
                std::from_chars(value.data(), value.data() + value.size(), stratum);
            if (value.empty() || parsed.ec != std::errc{} ||
                parsed.ptr != value.data() + value.size()) {
                throw DesktopError("main stratum must be a non-negative integer");
            }
            options.main_stratum = stratum;
        } else if (name == "--seed") {
            const auto parsed =
                std::from_chars(value.data(), value.data() + value.size(), options.seed);
            if (value.empty() || parsed.ec != std::errc{} ||
                parsed.ptr != value.data() + value.size() || options.seed == 0) {
                throw DesktopError("seed must be a positive 32-bit integer");
            }
        } else {
            throw DesktopError("unknown desktop option: " + name);
        }
    }
    if (!options.main_stratum && options.seed != 42) {
        throw DesktopError("--seed requires --main-stratum");
    }
    return options;
}

void require_egl(bool condition, const char* operation) {
    if (!condition) {
        throw DesktopError(std::string(operation) + " failed with EGL error " +
                           std::to_string(eglGetError()));
    }
}

class DesktopWindow {
public:
    DesktopWindow(int width, int height) : width_(width), height_(height) {
        registry_listener_.global = registry_global;
        registry_listener_.global_remove = registry_global_remove;
        wm_base_listener_.ping = wm_base_ping;
        xdg_surface_listener_.configure = surface_configure;
        toplevel_listener_.configure = toplevel_configure;
        toplevel_listener_.close = toplevel_close;
        seat_listener_.capabilities = seat_capabilities;
        seat_listener_.name = seat_name;
        pointer_listener_.enter = pointer_enter;
        pointer_listener_.leave = pointer_leave;
        pointer_listener_.motion = pointer_motion;
        pointer_listener_.button = pointer_button;
        pointer_listener_.axis = pointer_axis;
        pointer_listener_.frame = pointer_frame;
        pointer_listener_.axis_source = pointer_axis_source;
        pointer_listener_.axis_stop = pointer_axis_stop;
        pointer_listener_.axis_discrete = pointer_axis_discrete;
        keyboard_listener_.keymap = keyboard_keymap;
        keyboard_listener_.enter = keyboard_enter;
        keyboard_listener_.leave = keyboard_leave;
        keyboard_listener_.key = keyboard_key;
        keyboard_listener_.modifiers = keyboard_modifiers;
        keyboard_listener_.repeat_info = keyboard_repeat_info;

        display_ = wl_display_connect(nullptr);
        if (display_ == nullptr) {
            throw DesktopError("could not connect to the Wayland display");
        }
        registry_ = wl_display_get_registry(display_);
        wl_registry_add_listener(registry_, &registry_listener_, this);
        if (wl_display_roundtrip(display_) < 0 || compositor_ == nullptr || wm_base_ == nullptr) {
            throw DesktopError("Wayland compositor does not expose xdg-shell");
        }
        surface_ = wl_compositor_create_surface(compositor_);
        xdg_surface_ = xdg_wm_base_get_xdg_surface(wm_base_, surface_);
        xdg_surface_add_listener(xdg_surface_, &xdg_surface_listener_, this);
        toplevel_ = xdg_surface_get_toplevel(xdg_surface_);
        xdg_toplevel_add_listener(toplevel_, &toplevel_listener_, this);
        xdg_toplevel_set_title(toplevel_, "Torchlight Recovery");
        xdg_toplevel_set_app_id(toplevel_, "torchlight-recovery");
        wl_surface_commit(surface_);
        while (!configured_ && wl_display_dispatch(display_) >= 0) {
        }
        if (!configured_) {
            throw DesktopError("Wayland did not configure the game window");
        }
        native_window_ = wl_egl_window_create(surface_, width_, height_);
        if (native_window_ == nullptr) {
            throw DesktopError("could not create the Wayland EGL window");
        }

        egl_display_ = eglGetDisplay(static_cast<EGLNativeDisplayType>(display_));
        require_egl(egl_display_ != EGL_NO_DISPLAY, "eglGetDisplay");
        EGLint major = 0;
        EGLint minor = 0;
        require_egl(eglInitialize(egl_display_, &major, &minor) == EGL_TRUE, "eglInitialize");
        require_egl(eglBindAPI(EGL_OPENGL_ES_API) == EGL_TRUE, "eglBindAPI");

        const EGLint attributes[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_NONE,
        };
        EGLint configuration_count = 0;
        require_egl(eglChooseConfig(egl_display_, attributes, &configuration_, 1,
                                    &configuration_count) == EGL_TRUE &&
                        configuration_count == 1,
                    "eglChooseConfig");

        egl_surface_ = eglCreateWindowSurface(egl_display_, configuration_,
                                              reinterpret_cast<EGLNativeWindowType>(native_window_),
                                              nullptr);
        require_egl(egl_surface_ != EGL_NO_SURFACE, "eglCreateWindowSurface");
        const EGLint context_attributes[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        egl_context_ = eglCreateContext(egl_display_, configuration_, EGL_NO_CONTEXT,
                                        context_attributes);
        require_egl(egl_context_ != EGL_NO_CONTEXT, "eglCreateContext");
        require_egl(eglMakeCurrent(egl_display_, egl_surface_, egl_surface_, egl_context_) == EGL_TRUE,
                    "eglMakeCurrent");
        eglSwapInterval(egl_display_, 1);
    }

    DesktopWindow(const DesktopWindow&) = delete;
    DesktopWindow& operator=(const DesktopWindow&) = delete;

    ~DesktopWindow() {
        if (egl_display_ != EGL_NO_DISPLAY) {
            eglMakeCurrent(egl_display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (egl_context_ != EGL_NO_CONTEXT) {
                eglDestroyContext(egl_display_, egl_context_);
            }
            if (egl_surface_ != EGL_NO_SURFACE) {
                eglDestroySurface(egl_display_, egl_surface_);
            }
            eglTerminate(egl_display_);
        }
        if (native_window_ != nullptr) {
            wl_egl_window_destroy(native_window_);
        }
        if (pointer_ != nullptr) {
            wl_pointer_destroy(pointer_);
        }
        if (keyboard_ != nullptr) {
            wl_keyboard_destroy(keyboard_);
        }
        if (seat_ != nullptr) {
            wl_seat_destroy(seat_);
        }
        if (toplevel_ != nullptr) {
            xdg_toplevel_destroy(toplevel_);
        }
        if (xdg_surface_ != nullptr) {
            xdg_surface_destroy(xdg_surface_);
        }
        if (surface_ != nullptr) {
            wl_surface_destroy(surface_);
        }
        if (wm_base_ != nullptr) {
            xdg_wm_base_destroy(wm_base_);
        }
        if (compositor_ != nullptr) {
            wl_compositor_destroy(compositor_);
        }
        if (registry_ != nullptr) {
            wl_registry_destroy(registry_);
        }
        if (display_ != nullptr) {
            wl_display_disconnect(display_);
        }
    }

    bool process_events() {
        if (wl_display_dispatch_pending(display_) < 0) {
            return false;
        }
        pollfd descriptor{wl_display_get_fd(display_), POLLIN, 0};
        const int ready = poll(&descriptor, 1, 0);
        if (ready > 0 && (descriptor.revents & POLLIN) != 0) {
            if (wl_display_dispatch(display_) < 0) {
                return false;
            }
        } else {
            wl_display_flush(display_);
        }
        return running_;
    }

    [[nodiscard]] std::optional<std::array<int, 2>> take_left_click() noexcept {
        auto result = left_click_;
        left_click_.reset();
        return result;
    }

    [[nodiscard]] int width() const noexcept { return width_; }
    [[nodiscard]] int height() const noexcept { return height_; }

    void draw_scene_frame(torchlight::GlesSceneRenderer& renderer) {
        renderer.draw(width_, height_);
        glEnable(GL_SCISSOR_TEST);
        const int top_height = std::max(54, height_ / 12);
        fill_rectangle(0, height_ - top_height, width_, top_height, 0.18F, 0.105F, 0.035F);
        const int status_size = std::max(12, std::min(width_, height_) / 45);
        fill_rectangle(status_size, height_ - top_height / 2 - status_size / 2, status_size,
                       status_size, 0.72F, 0.43F, 0.10F);
        glDisable(GL_SCISSOR_TEST);
        if (glGetError() != GL_NO_ERROR) {
            throw DesktopError("OpenGL ES failed while drawing the scene preview");
        }
        require_egl(eglSwapBuffers(egl_display_, egl_surface_) == EGL_TRUE, "eglSwapBuffers");
    }

private:
    static void registry_global(void* data, wl_registry* registry, std::uint32_t name,
                                const char* interface, std::uint32_t version) {
        auto& self = *static_cast<DesktopWindow*>(data);
        const std::string_view interface_name(interface);
        if (interface_name == wl_compositor_interface.name) {
            self.compositor_ = static_cast<wl_compositor*>(wl_registry_bind(
                registry, name, &wl_compositor_interface, std::min(version, 4U)));
        } else if (interface_name == xdg_wm_base_interface.name) {
            self.wm_base_ = static_cast<xdg_wm_base*>(
                wl_registry_bind(registry, name, &xdg_wm_base_interface, 1));
            xdg_wm_base_add_listener(self.wm_base_, &self.wm_base_listener_, &self);
        } else if (interface_name == wl_seat_interface.name) {
            self.seat_ = static_cast<wl_seat*>(
                wl_registry_bind(registry, name, &wl_seat_interface, std::min(version, 5U)));
            wl_seat_add_listener(self.seat_, &self.seat_listener_, &self);
        }
    }

    static void registry_global_remove(void*, wl_registry*, std::uint32_t) {}
    static void wm_base_ping(void*, xdg_wm_base* wm_base, std::uint32_t serial) {
        xdg_wm_base_pong(wm_base, serial);
    }
    static void surface_configure(void* data, xdg_surface* surface, std::uint32_t serial) {
        auto& self = *static_cast<DesktopWindow*>(data);
        xdg_surface_ack_configure(surface, serial);
        self.configured_ = true;
    }
    static void toplevel_configure(void* data, xdg_toplevel*, std::int32_t width,
                                   std::int32_t height, wl_array*) {
        auto& self = *static_cast<DesktopWindow*>(data);
        if (width <= 0 || height <= 0) {
            return;
        }
        self.width_ = width;
        self.height_ = height;
        if (self.native_window_ != nullptr) {
            wl_egl_window_resize(self.native_window_, width, height, 0, 0);
        }
    }
    static void toplevel_close(void* data, xdg_toplevel*) {
        static_cast<DesktopWindow*>(data)->running_ = false;
    }
    static void seat_capabilities(void* data, wl_seat* seat, std::uint32_t capabilities) {
        auto& self = *static_cast<DesktopWindow*>(data);
        if ((capabilities & WL_SEAT_CAPABILITY_POINTER) != 0 && self.pointer_ == nullptr) {
            self.pointer_ = wl_seat_get_pointer(seat);
            wl_pointer_add_listener(self.pointer_, &self.pointer_listener_, &self);
        }
        if ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) != 0 && self.keyboard_ == nullptr) {
            self.keyboard_ = wl_seat_get_keyboard(seat);
            wl_keyboard_add_listener(self.keyboard_, &self.keyboard_listener_, &self);
        }
    }
    static void seat_name(void*, wl_seat*, const char*) {}
    static void pointer_enter(void* data, wl_pointer*, std::uint32_t, wl_surface*, wl_fixed_t x,
                              wl_fixed_t y) {
        pointer_motion(data, nullptr, 0, x, y);
    }
    static void pointer_leave(void*, wl_pointer*, std::uint32_t, wl_surface*) {}
    static void pointer_motion(void* data, wl_pointer*, std::uint32_t, wl_fixed_t x,
                               wl_fixed_t y) {
        auto& self = *static_cast<DesktopWindow*>(data);
        self.pointer_x_ = wl_fixed_to_int(x);
        self.pointer_y_ = wl_fixed_to_int(y);
    }
    static void pointer_button(void* data, wl_pointer*, std::uint32_t, std::uint32_t,
                               std::uint32_t button, std::uint32_t state) {
        auto& self = *static_cast<DesktopWindow*>(data);
        if (button == BTN_LEFT && state == WL_POINTER_BUTTON_STATE_PRESSED) {
            self.left_click_ = {self.pointer_x_, self.pointer_y_};
        }
    }
    static void pointer_axis(void*, wl_pointer*, std::uint32_t, std::uint32_t, wl_fixed_t) {}
    static void pointer_frame(void*, wl_pointer*) {}
    static void pointer_axis_source(void*, wl_pointer*, std::uint32_t) {}
    static void pointer_axis_stop(void*, wl_pointer*, std::uint32_t, std::uint32_t) {}
    static void pointer_axis_discrete(void*, wl_pointer*, std::uint32_t, std::int32_t) {}
    static void keyboard_keymap(void*, wl_keyboard*, std::uint32_t, std::int32_t fd,
                                std::uint32_t) {
        if (fd >= 0) {
            close(fd);
        }
    }
    static void keyboard_enter(void*, wl_keyboard*, std::uint32_t, wl_surface*, wl_array*) {}
    static void keyboard_leave(void*, wl_keyboard*, std::uint32_t, wl_surface*) {}
    static void keyboard_key(void* data, wl_keyboard*, std::uint32_t, std::uint32_t,
                             std::uint32_t key, std::uint32_t state) {
        if (key == KEY_ESC && state == WL_KEYBOARD_KEY_STATE_PRESSED) {
            static_cast<DesktopWindow*>(data)->running_ = false;
        }
    }
    static void keyboard_modifiers(void*, wl_keyboard*, std::uint32_t, std::uint32_t,
                                   std::uint32_t, std::uint32_t, std::uint32_t) {}
    static void keyboard_repeat_info(void*, wl_keyboard*, std::int32_t, std::int32_t) {}

    void fill_rectangle(int x, int y, int width, int height, float red, float green, float blue) {
        glScissor(x, y, width, height);
        glClearColor(red, green, blue, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    wl_display* display_ = nullptr;
    wl_registry* registry_ = nullptr;
    wl_compositor* compositor_ = nullptr;
    xdg_wm_base* wm_base_ = nullptr;
    wl_surface* surface_ = nullptr;
    xdg_surface* xdg_surface_ = nullptr;
    xdg_toplevel* toplevel_ = nullptr;
    wl_seat* seat_ = nullptr;
    wl_pointer* pointer_ = nullptr;
    wl_keyboard* keyboard_ = nullptr;
    wl_egl_window* native_window_ = nullptr;
    wl_registry_listener registry_listener_{};
    xdg_wm_base_listener wm_base_listener_{};
    xdg_surface_listener xdg_surface_listener_{};
    xdg_toplevel_listener toplevel_listener_{};
    wl_seat_listener seat_listener_{};
    wl_pointer_listener pointer_listener_{};
    wl_keyboard_listener keyboard_listener_{};
    EGLDisplay egl_display_ = EGL_NO_DISPLAY;
    EGLConfig configuration_ = nullptr;
    EGLSurface egl_surface_ = EGL_NO_SURFACE;
    EGLContext egl_context_ = EGL_NO_CONTEXT;
    int width_ = 1280;
    int height_ = 720;
    int pointer_x_ = 0;
    int pointer_y_ = 0;
    bool configured_ = false;
    bool running_ = true;
    std::optional<std::array<int, 2>> left_click_;
};

struct LoadedDesktopLevel {
    torchlight::DungeonAddress address;
    torchlight::DungeonManifest dungeon;
    torchlight::LevelRules rules;
    torchlight::LayoutManifest layout;
    torchlight::FixedSceneGeometry geometry;
    torchlight::NavigationGrid navigation;
    std::array<float, 3> player_start{};
    std::string scene_state;
    std::size_t chunk_count = 1;
    std::size_t expanded_layout_link_count = 0;
    std::size_t placed_monster_count = 0;
    float player_floor_offset = 0.0F;
};

std::u16string dungeon_data_file(std::u16string_view dungeon_name) {
    std::u16string result = u"media/dungeons/";
    result.append(dungeon_name);
    result.append(u".DAT");
    return result;
}

std::uint32_t level_seed(std::uint32_t base_seed, std::int32_t depth) noexcept {
    const auto offset = depth > 0 ? static_cast<std::uint32_t>(depth - 1) : 0U;
    auto value = base_seed ^ (offset * 0x9e3779b9U);
    return value == 0 ? 1U : value;
}

std::string narrow_ascii(std::u16string_view value) {
    std::string result;
    result.reserve(value.size());
    for (const auto character : value) {
        if (character > 0x7fU) {
            throw DesktopError("dungeon name contains a non-ASCII character");
        }
        result.push_back(static_cast<char>(character));
    }
    return result;
}

torchlight::LayoutManifest load_static_layout(
    const torchlight::LevelSceneLoader& loader,
    const torchlight::LevelRules& rules) {
    std::vector<std::string> candidates;
    if (rules.chunks.size() == 1U) {
        candidates = loader.layout_candidates(rules, rules.chunks.front().type);
    } else if (rules.chunk_types.size() == 1U) {
        candidates = loader.layout_candidates(rules, rules.chunk_types.front().name);
    }
    if (candidates.size() != 1U) {
        throw DesktopError("static level does not resolve to exactly one layout");
    }
    return loader.load_layout(candidates.front());
}

LoadedDesktopLevel load_desktop_level(
    const torchlight::PakArchive& archive,
    const torchlight::LevelsetCatalog& levelsets,
    const torchlight::LevelSceneLoader& loader,
    torchlight::DungeonAddress requested_address,
    std::uint32_t base_seed) {
    LoadedDesktopLevel result;
    result.dungeon = loader.load_dungeon(
        dungeon_data_file(requested_address.dungeon_name));
    const auto floor = torchlight::select_dungeon_floor(
        result.dungeon, requested_address.depth);
    result.address = {result.dungeon.name, floor.depth};
    result.rules = loader.load_rules(result.dungeon.strata[floor.stratum_index].ruleset);
    const auto seed = level_seed(base_seed, floor.depth);

    torchlight::CollisionScene collision;
    if (result.rules.randomized) {
        const torchlight::RandomLevelGenerator generator(loader);
        const auto generated = generator.generate(result.rules, seed);
        result.chunk_count = generated.chunks.size();
        auto composed = torchlight::compose_generated_level_layout(loader, generated);
        result.layout = std::move(composed.layout);
        const auto expansion = torchlight::expand_layout_links(loader, result.layout);
        result.expanded_layout_link_count = expansion.links_expanded;
        const torchlight::FixedLevelScene scene{
            result.dungeon, result.rules, result.layout};
        result.geometry = torchlight::build_room_piece_geometry(
            archive, levelsets, scene);
        result.player_start = torchlight::generated_player_start(loader, generated);
        collision = torchlight::build_generated_level_collision(
            archive, levelsets, loader, generated);
        result.scene_state = "generated-dungeon";
    } else {
        result.layout = load_static_layout(loader, result.rules);
        const auto expansion = torchlight::expand_layout_links(loader, result.layout);
        result.expanded_layout_link_count = expansion.links_expanded;
        const torchlight::FixedLevelScene scene{
            result.dungeon, result.rules, result.layout};
        result.geometry = torchlight::build_room_piece_geometry(
            archive, levelsets, scene);
        result.player_start = torchlight::layout_player_start(result.layout);
        collision = torchlight::build_fixed_level_collision(archive, levelsets, scene);
        result.scene_state = result.dungeon.strata[floor.stratum_index].is_town
                                 ? "town-playable"
                                 : "fixed-dungeon";
    }

    result.navigation = torchlight::NavigationGrid::build(collision);
    if (const auto start_cell = result.navigation.nearest_walkable(result.player_start)) {
        result.player_floor_offset =
            result.player_start[1] -
            result.navigation.cell((*start_cell)[0], (*start_cell)[1]).height;
    }
    return result;
}

struct LevelInteraction {
    std::int64_t object_id = 0;
    std::array<float, 3> position{};
};

std::vector<LevelInteraction> collect_unit_triggers(
    const torchlight::LayoutManifest& layout) {
    const auto transforms = torchlight::resolve_layout_world_transforms(layout);
    std::vector<LevelInteraction> result;
    for (std::size_t index = 0; index < layout.objects.size(); ++index) {
        if (layout.objects[index].descriptor == u"Unit Trigger") {
            result.push_back({layout.objects[index].id, transforms[index].position});
        }
    }
    return result;
}

const LevelInteraction* nearest_interaction(
    const std::vector<LevelInteraction>& interactions,
    const std::array<float, 3>& position, float maximum_distance) noexcept {
    const LevelInteraction* result = nullptr;
    auto nearest_squared = maximum_distance * maximum_distance;
    for (const auto& interaction : interactions) {
        const auto dx = interaction.position[0] - position[0];
        const auto dz = interaction.position[2] - position[2];
        const auto distance_squared = dx * dx + dz * dz;
        if (distance_squared <= nearest_squared) {
            result = &interaction;
            nearest_squared = distance_squared;
        }
    }
    return result;
}

} // namespace

int main(int argc, char** argv) {
    try {
        const auto options = parse_options(argc, argv);
        const torchlight::PakArchive archive(options.game_directory / "pak.zip");
        const auto master_document = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex index(master_document);
        const torchlight::SpawnClassCatalog spawn_classes(archive);
        torchlight::UnitDefinitionLoader loader(archive);
        for (const auto& record : index.records()) {
            static_cast<void>(loader.load(record));
        }
        const torchlight::UnitTypeHierarchy unit_type_hierarchy(archive);
        const torchlight::UnitTypeResourceIndex unit_types(
            archive, unit_type_hierarchy, index, loader);
        const torchlight::LevelsetCatalog levelsets(archive);
        const torchlight::LevelSceneLoader scene_loader(archive);
        const auto players = torchlight::load_playable_players(archive, index, loader);
        if (players.empty()) {
            throw DesktopError("no playable player definitions were resolved");
        }

        torchlight::DungeonAddress initial_address{u"Town", 0};
        if (options.main_stratum) {
            const auto main = scene_loader.load_dungeon(u"media/dungeons/MAIN.DAT");
            if (*options.main_stratum >= main.strata.size()) {
                throw DesktopError("main stratum index is out of range");
            }
            std::int64_t depth = 1;
            for (std::size_t stratum = 0; stratum < *options.main_stratum; ++stratum) {
                depth += main.strata[stratum].floors;
            }
            if (depth > std::numeric_limits<std::int32_t>::max()) {
                throw DesktopError("main stratum depth exceeds the 32-bit range");
            }
            initial_address = {main.name, static_cast<std::int32_t>(depth)};
        }
        const torchlight::OgreMaterialCatalog materials(archive);
        DesktopWindow window(1280, 720);
        torchlight::LevelTransitionState transitions(initial_address);
        std::uint64_t total_frames = 0;
        std::size_t completed_transitions = 0;
        bool app_running = true;

        while (app_running) {
            auto level = load_desktop_level(
                archive, levelsets, scene_loader,
                transitions.current(), options.seed);
            if (level.address.dungeon_name != transitions.current().dungeon_name ||
                level.address.depth != transitions.current().depth) {
                transitions.commit(level.address);
            }
            torchlight::ActorMotion player_motion(
                level.player_start, players.front().running_speed);
            auto interactions = collect_unit_triggers(level.layout);
            std::optional<LevelInteraction> active_interaction;
            std::optional<std::uint64_t> active_pickup;
            std::vector<std::array<float, 3>> active_path;
            std::size_t next_path_node = 0;

            torchlight::LogicRuntime logic_runtime(
                level.layout, level_seed(options.seed, level.address.depth));
            torchlight::RuntimeEntityWorld entity_world(
                level.layout, index, loader, spawn_classes, unit_types,
                level_seed(options.seed, level.address.depth),
                std::max(1, level.address.depth));
            level.placed_monster_count = torchlight::append_layout_monster_geometry(
                archive, index, loader, level.layout, level.geometry, 0, &entity_world);
            torchlight::append_player_geometry(
                archive, players.front(), level.player_start, level.geometry);
            const auto player_instance_index = level.geometry.instances.size() - 1U;
            torchlight::CombatController combat(
                players.front(), level_seed(options.seed, level.address.depth));
            torchlight::PlayerCombatState player_combat(
                players.front(), level_seed(options.seed, level.address.depth));
            torchlight::EnemyController enemies(
                level_seed(options.seed, level.address.depth) ^ 0x9e3779b9U);
            std::optional<torchlight::GlesSceneRenderer> renderer;
            std::optional<torchlight::WarpRequest> pending_warp;
            std::unordered_map<std::uint64_t, std::size_t> runtime_instance_indices;

            std::size_t logic_event_count = 0;
            std::size_t logic_invocation_count = 0;
            std::size_t spawn_request_count = 0;
            std::size_t spawned_entity_count = 0;
            std::size_t resolved_unit_type_count = 0;
            std::size_t unresolved_unit_type_count = 0;
            std::size_t missing_spawn_resource_count = 0;
            std::size_t processed_entity_count = entity_world.placed_entity_count();
            std::size_t runtime_model_count = 0;
            std::size_t missing_runtime_model_count = 0;
            std::size_t renderer_rebuild_count = 0;
            std::size_t warp_request_count = 0;
            std::size_t selected_target_count = 0;
            std::size_t interaction_count = 0;
            std::size_t pickup_count = 0;
            std::size_t equipped_armor_count = 0;
            std::size_t equipped_weapon_count = 0;
            std::size_t combat_attack_count = 0;
            std::size_t combat_kill_count = 0;
            std::size_t enemy_chase_count = 0;
            std::size_t enemy_attack_count = 0;
            std::size_t player_death_count = 0;
            std::uint64_t level_frames = 0;

            for (std::size_t instance_index = 0;
                 instance_index < level.geometry.instances.size(); ++instance_index) {
                const auto entity_id = level.geometry.instances[instance_index].runtime_entity_id;
                if (entity_id != 0) {
                    runtime_instance_indices.emplace(entity_id, instance_index);
                }
            }

            auto drain_logic = [&] {
                for (std::size_t pass = 0;; ++pass) {
                    const auto requests = logic_runtime.take_spawn_requests();
                    if (requests.empty()) {
                        break;
                    }
                    if (pass >= 64U) {
                        throw DesktopError("level logic produced an unbounded spawn chain");
                    }
                    const auto stats =
                        entity_world.consume_spawn_requests(requests, logic_runtime);
                    spawn_request_count += stats.requests;
                    spawned_entity_count += stats.entities_created;
                    resolved_unit_type_count += stats.resolved_unit_types;
                    unresolved_unit_type_count += stats.unresolved_unit_types;
                    missing_spawn_resource_count += stats.missing_resources;
                }
                bool geometry_changed = false;
                while (processed_entity_count < entity_world.entities().size()) {
                    const auto instance = torchlight::append_runtime_entity_geometry(
                        archive, index, loader,
                        entity_world.entities()[processed_entity_count], level.geometry);
                    runtime_model_count += static_cast<std::size_t>(instance.has_value());
                    missing_runtime_model_count +=
                        static_cast<std::size_t>(!instance.has_value());
                    if (instance) {
                        runtime_instance_indices.emplace(
                            entity_world.entities()[processed_entity_count].id, *instance);
                    }
                    geometry_changed = geometry_changed || instance.has_value();
                    ++processed_entity_count;
                }
                if (geometry_changed && renderer) {
                    renderer.emplace(level.geometry, archive, materials);
                    ++renderer_rebuild_count;
                    renderer->set_camera_target(
                        player_motion.position(), kCameraVerticalSpan);
                }
                logic_event_count += logic_runtime.take_events().size();
                logic_invocation_count += logic_runtime.take_invocations().size();
                auto warps = logic_runtime.take_warp_requests();
                warp_request_count += warps.size();
                if (!warps.empty() && !pending_warp) {
                    pending_warp = std::move(warps.front());
                }
            };

            logic_runtime.activate_level();
            logic_runtime.update_player_position(player_motion.position());
            drain_logic();
            renderer.emplace(level.geometry, archive, materials);
            renderer->set_camera_target(player_motion.position(), kCameraVerticalSpan);
            bool rendered_once = false;
            auto previous_frame = std::chrono::steady_clock::now();

            while (!pending_warp) {
                if (!window.process_events()) {
                    app_running = false;
                    break;
                }
                const auto current_frame = std::chrono::steady_clock::now();
                const float elapsed =
                    std::chrono::duration<float>(current_frame - previous_frame).count();
                previous_frame = current_frame;
                if (const auto click = window.take_left_click();
                    click && rendered_once && player_combat.alive()) {
                    auto destination = renderer->ground_position_at_pixel(
                        (*click)[0], window.height() - 1 - (*click)[1], window.width(),
                        window.height(), player_motion.position()[1]);
                    if (combat.select_target(entity_world, destination, 2.0F)) {
                        const auto* selected = combat.target(entity_world);
                        destination = selected->position;
                        active_interaction.reset();
                        active_pickup.reset();
                        ++selected_target_count;
                        std::cout << "selected_target=" << selected->id
                                  << " health=" << selected->health << '/'
                                  << selected->maximum_health << '\n';
                    } else if (const auto* item = entity_world.nearest_alive_item(
                                   destination, 2.0F)) {
                        combat.clear_target();
                        active_interaction.reset();
                        active_pickup = item->id;
                        destination = item->position;
                        std::cout << "selected_item=" << item->id
                                  << " name=" << narrow_ascii(item->name) << '\n';
                    } else if (const auto* interaction = nearest_interaction(
                                   interactions, destination, 3.0F)) {
                        combat.clear_target();
                        active_pickup.reset();
                        active_interaction = *interaction;
                        destination = interaction->position;
                        std::cout << "selected_interaction=" << interaction->object_id << '\n';
                    } else {
                        combat.clear_target();
                        active_interaction.reset();
                        active_pickup.reset();
                    }
                    active_path = level.navigation.find_path(
                        player_motion.position(), destination);
                    std::cout << "click_destination=" << destination[0] << ',' << destination[1]
                              << ',' << destination[2]
                              << " path_nodes=" << active_path.size() << '\n';
                    std::cout.flush();
                    next_path_node = active_path.size() > 1U ? 1U : active_path.size();
                    if (next_path_node < active_path.size()) {
                        auto waypoint = active_path[next_path_node];
                        waypoint[1] += level.player_floor_offset;
                        player_motion.set_destination(waypoint);
                    } else {
                        player_motion.stop();
                    }
                }
                player_motion.advance(std::min(elapsed, 0.1F));
                while (!player_motion.moving() && next_path_node < active_path.size()) {
                    ++next_path_node;
                    if (next_path_node < active_path.size()) {
                        auto waypoint = active_path[next_path_node];
                        waypoint[1] += level.player_floor_offset;
                        player_motion.set_destination(waypoint);
                    }
                }
                level.geometry.instances[player_instance_index].transform.position =
                    player_motion.position();
                renderer->set_instance_position(player_instance_index, player_motion.position());
                renderer->set_camera_target(
                    player_motion.position(), kCameraVerticalSpan);

                if (active_interaction) {
                    const auto dx = active_interaction->position[0] - player_motion.position()[0];
                    const auto dz = active_interaction->position[2] - player_motion.position()[2];
                    if (std::hypot(dx, dz) <= 2.25F) {
                        player_motion.stop();
                        active_path.clear();
                        next_path_node = 0;
                        logic_runtime.trigger(active_interaction->object_id);
                        ++interaction_count;
                        active_interaction.reset();
                        drain_logic();
                    }
                }
                if (active_pickup) {
                    const auto* item = entity_world.find(*active_pickup);
                    if (item == nullptr || !item->alive ||
                        item->kind != torchlight::MasterResourceKind::item) {
                        active_pickup.reset();
                    } else {
                        const auto dx = item->position[0] - player_motion.position()[0];
                        const auto dz = item->position[2] - player_motion.position()[2];
                        if (std::hypot(dx, dz) <= 2.25F) {
                            const auto item_id = item->id;
                            const auto item_name = item->name;
                            const auto armor_item = item->armor_item;
                            const auto weapon_item = item->weapon_item;
                            player_motion.stop();
                            active_path.clear();
                            next_path_node = 0;
                            if (entity_world.pick_up(item_id, logic_runtime)) {
                                ++pickup_count;
                                if (armor_item) {
                                    player_combat.equip(*armor_item);
                                    ++equipped_armor_count;
                                }
                                if (weapon_item) {
                                    combat.equip(*weapon_item);
                                    ++equipped_weapon_count;
                                }
                                const auto instance = runtime_instance_indices.find(item_id);
                                if (instance != runtime_instance_indices.end()) {
                                    level.geometry.instances[instance->second].visible = false;
                                    renderer->set_instance_visible(instance->second, false);
                                }
                                std::cout << "picked_up=" << item_id
                                          << " name=" << narrow_ascii(item_name)
                                          << " armor="
                                          << (armor_item ? armor_item->armor : 0)
                                          << " player_armor="
                                          << player_combat.armor_class()
                                          << " attack_damage="
                                          << combat.minimum_damage() << '-'
                                          << combat.maximum_damage()
                                          << " attack_range="
                                          << combat.attack_range() << '\n';
                            }
                            active_pickup.reset();
                            drain_logic();
                        }
                    }
                }
                if (!pending_warp) {
                    const auto update = combat.update(
                        std::min(elapsed, 0.1F), player_motion.position(),
                        entity_world, logic_runtime);
                    if (update.state == torchlight::CombatState::waiting ||
                        update.state == torchlight::CombatState::attacked ||
                        update.state == torchlight::CombatState::killed) {
                        player_motion.stop();
                        active_path.clear();
                        next_path_node = 0;
                    }
                    if (update.state == torchlight::CombatState::attacked ||
                        update.state == torchlight::CombatState::killed) {
                        ++combat_attack_count;
                        std::cout << "combat_hit=" << update.target_id
                                  << " damage=" << update.damage
                                  << " remaining_health=" << update.remaining_health
                                  << '\n';
                    }
                    if (update.state == torchlight::CombatState::killed) {
                        ++combat_kill_count;
                        const auto instance = runtime_instance_indices.find(
                            update.target_id);
                        if (instance != runtime_instance_indices.end()) {
                            level.geometry.instances[instance->second].visible = false;
                            renderer->set_instance_visible(instance->second, false);
                        }
                    }
                    const auto enemy_updates = enemies.update(
                        std::min(elapsed, 0.1F), player_motion.position(),
                        player_combat, entity_world, &level.navigation);
                    for (const auto& enemy_update : enemy_updates) {
                        if (enemy_update.state == torchlight::EnemyAiState::chasing &&
                            enemy_update.position_changed) {
                            ++enemy_chase_count;
                            const auto instance = runtime_instance_indices.find(
                                enemy_update.entity_id);
                            const auto* enemy = entity_world.find(enemy_update.entity_id);
                            if (instance != runtime_instance_indices.end() && enemy != nullptr) {
                                level.geometry.instances[instance->second].transform.position =
                                    enemy->position;
                                renderer->set_instance_position(
                                    instance->second, enemy->position);
                            }
                        }
                        if (enemy_update.state == torchlight::EnemyAiState::attacked ||
                            enemy_update.state == torchlight::EnemyAiState::player_killed) {
                            ++enemy_attack_count;
                            std::cout << "enemy_hit=" << enemy_update.entity_id
                                      << " damage=" << enemy_update.damage
                                      << " player_health=" << enemy_update.player_health
                                      << '\n';
                        }
                        if (enemy_update.state ==
                            torchlight::EnemyAiState::player_killed) {
                            ++player_death_count;
                            player_motion.stop();
                            active_path.clear();
                            next_path_node = 0;
                            combat.clear_target();
                            std::cout << "player_killed=1\n";
                        }
                    }
                    logic_runtime.update(std::min(elapsed, 0.1F));
                    logic_runtime.update_player_position(player_motion.position());
                    drain_logic();
                }
                window.draw_scene_frame(*renderer);
                rendered_once = true;
                ++level_frames;
                ++total_frames;
                if (options.frame_limit != 0 && total_frames >= options.frame_limit) {
                    app_running = false;
                    break;
                }
            }

            const auto& render_stats = renderer->stats();
            std::cout << "desktop_state=" << level.scene_state
                      << " dungeon=" << narrow_ascii(level.address.dungeon_name)
                      << " depth=" << level.address.depth
                      << " resources=" << index.records().size()
                      << " cached_unit_files=" << loader.cached_definition_count()
                      << " level_pieces=" << levelsets.pieces().size()
                      << " chunks=" << level.chunk_count
                      << " player=" << narrow_ascii(players.front().name)
                      << " weapon="
                      << (players.front().starting_weapon
                              ? narrow_ascii(players.front().starting_weapon->name)
                              : "none")
                      << " attack_damage=" << combat.minimum_damage() << '-'
                      << combat.maximum_damage()
                      << " attack_range=" << combat.attack_range()
                      << " layout_objects=" << level.layout.objects.size()
                      << " expanded_layout_links=" << level.expanded_layout_link_count
                      << " placed_monsters=" << level.placed_monster_count
                      << " meshes=" << render_stats.mesh_resources
                      << " instances=" << render_stats.instances
                      << " draw_batches=" << render_stats.draw_batches
                      << " textures=" << render_stats.texture_resources
                      << " textured_batches=" << render_stats.textured_batches
                      << " placed_triangles=" << render_stats.placed_triangles
                      << " logic_events=" << logic_event_count
                      << " logic_invocations=" << logic_invocation_count
                      << " spawn_requests=" << spawn_request_count
                      << " runtime_entities=" << entity_world.entities().size()
                      << " spawned_entities=" << spawned_entity_count
                      << " resolved_unit_types=" << resolved_unit_type_count
                      << " unresolved_unit_types=" << unresolved_unit_type_count
                      << " missing_spawn_resources=" << missing_spawn_resource_count
                      << " runtime_models=" << runtime_model_count
                      << " missing_runtime_models=" << missing_runtime_model_count
                      << " renderer_rebuilds=" << renderer_rebuild_count
                      << " selected_targets=" << selected_target_count
                      << " interactions=" << interaction_count
                      << " pickups=" << pickup_count
                      << " equipped_armor=" << equipped_armor_count
                      << " equipped_weapons=" << equipped_weapon_count
                      << " combat_attacks=" << combat_attack_count
                      << " combat_kills=" << combat_kill_count
                      << " player_health=" << player_combat.health() << '/'
                      << player_combat.maximum_health()
                      << " player_armor=" << player_combat.armor_class()
                      << " alerted_enemies=" << enemies.alerted_count()
                      << " enemy_chases=" << enemy_chase_count
                      << " enemy_attacks=" << enemy_attack_count
                      << " player_deaths=" << player_death_count
                      << " warp_requests=" << warp_request_count
                      << " frames=" << level_frames
                      << " total_frames=" << total_frames
                      << " player_position=" << player_motion.position()[0] << ','
                      << player_motion.position()[1] << ',' << player_motion.position()[2]
                      << " navigation_cells=" << level.navigation.walkable_cell_count()
                      << '\n';

            if (!app_running || !pending_warp) {
                break;
            }
            auto destination = transitions.resolve(*pending_warp);
            const auto target_dungeon = scene_loader.load_dungeon(
                dungeon_data_file(destination.dungeon_name));
            const auto target_floor = torchlight::select_dungeon_floor(
                target_dungeon, destination.depth);
            destination = {target_dungeon.name, target_floor.depth};
            transitions.commit(destination);
            ++completed_transitions;
            std::cout << "level_transition=" << completed_transitions
                      << " dungeon=" << narrow_ascii(destination.dungeon_name)
                      << " depth=" << destination.depth
                      << " warp_name=" << narrow_ascii(pending_warp->warp_name)
                      << '\n';
            std::cout.flush();
        }
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "desktop failed: " << error.what() << '\n';
        return 1;
    }
}
