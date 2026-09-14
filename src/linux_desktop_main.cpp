#include "torchlight/actor_motion.hpp"
#include "torchlight/adm_document.hpp"
#include "torchlight/collision_scene.hpp"
#include "torchlight/gles_scene_renderer.hpp"
#include "torchlight/level_scene.hpp"
#include "torchlight/logic_runtime.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/navigation_grid.hpp"
#include "torchlight/ogre_material.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/player.hpp"
#include "torchlight/random_level.hpp"
#include "torchlight/scene_geometry.hpp"
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
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <unistd.h>
#include <vector>

namespace {

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

} // namespace

int main(int argc, char** argv) {
    try {
        const auto options = parse_options(argc, argv);
        const torchlight::PakArchive archive(options.game_directory / "pak.zip");
        const auto master_document = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex index(master_document);
        torchlight::UnitDefinitionLoader loader(archive);
        for (const auto& record : index.records()) {
            static_cast<void>(loader.load(record));
        }
        const torchlight::LevelsetCatalog levelsets(archive);
        const torchlight::LevelSceneLoader scene_loader(archive);
        torchlight::FixedSceneGeometry geometry;
        std::string scene_state;
        std::size_t chunk_count = 1;
        std::size_t layout_object_count = 0;
        std::size_t placed_monster_count = 0;
        std::string player_name = "none";
        std::optional<torchlight::ActorMotion> player_motion;
        std::optional<std::size_t> player_instance_index;
        std::optional<torchlight::NavigationGrid> navigation;
        std::optional<torchlight::FixedLevelScene> fixed_scene;
        std::vector<std::array<float, 3>> active_path;
        std::size_t next_path_node = 0;
        float player_floor_offset = 0.0F;
        if (options.main_stratum) {
            const auto main = scene_loader.load_dungeon(u"media/dungeons/MAIN.DAT");
            if (*options.main_stratum >= main.strata.size()) {
                throw DesktopError("main stratum index is out of range");
            }
            const auto rules = scene_loader.load_rules(main.strata[*options.main_stratum].ruleset);
            const torchlight::RandomLevelGenerator generator(scene_loader);
            const auto generated = generator.generate(rules, options.seed);
            chunk_count = generated.chunks.size();
            for (const auto& chunk : generated.chunks) {
                layout_object_count += scene_loader.load_layout(chunk.layout_path).objects.size();
            }
            geometry = torchlight::build_generated_level_geometry(
                archive, levelsets, scene_loader, rules, generated);
            const auto players = torchlight::load_playable_players(archive, index, loader);
            if (players.empty()) {
                throw DesktopError("no playable player definitions were resolved");
            }
            const auto player_start = torchlight::generated_player_start(scene_loader, generated);
            torchlight::append_player_geometry(archive, players.front(), player_start, geometry);
            player_instance_index = geometry.instances.size() - 1U;
            player_motion.emplace(player_start, players.front().running_speed);
            const auto collision = torchlight::build_generated_level_collision(
                archive, levelsets, scene_loader, generated);
            navigation = torchlight::NavigationGrid::build(collision);
            if (const auto start_cell = navigation->nearest_walkable(player_start)) {
                player_floor_offset =
                    player_start[1] - navigation->cell((*start_cell)[0], (*start_cell)[1]).height;
            }
            player_name.assign(players.front().name.begin(), players.front().name.end());
            scene_state = "generated-dungeon-preview";
        } else {
            fixed_scene.emplace(scene_loader.load_fixed_scene(u"media/dungeons/TOWN.DAT"));
            const auto& town = *fixed_scene;
            layout_object_count = town.layout.objects.size();
            geometry = torchlight::build_room_piece_geometry(archive, levelsets, town);
            placed_monster_count = torchlight::append_layout_monster_geometry(
                archive, index, loader, town.layout, geometry);
            const auto players = torchlight::load_playable_players(archive, index, loader);
            if (players.empty()) {
                throw DesktopError("no playable player definitions were resolved");
            }
            const auto player_start = torchlight::layout_player_start(town.layout);
            torchlight::append_player_geometry(archive, players.front(), player_start, geometry);
            player_instance_index = geometry.instances.size() - 1U;
            player_motion.emplace(player_start, players.front().running_speed);
            const auto collision =
                torchlight::build_fixed_level_collision(archive, levelsets, town);
            navigation = torchlight::NavigationGrid::build(collision);
            if (const auto start_cell = navigation->nearest_walkable(player_start)) {
                player_floor_offset =
                    player_start[1] - navigation->cell((*start_cell)[0], (*start_cell)[1]).height;
            }
            player_name.assign(players.front().name.begin(), players.front().name.end());
            scene_state = "town-playable-preview";
        }
        const torchlight::OgreMaterialCatalog materials(archive);

        DesktopWindow window(1280, 720);
        torchlight::GlesSceneRenderer renderer(geometry, archive, materials);
        std::optional<torchlight::LogicRuntime> logic_runtime;
        std::size_t logic_event_count = 0;
        std::size_t logic_invocation_count = 0;
        std::size_t spawn_request_count = 0;
        std::size_t warp_request_count = 0;
        auto drain_logic = [&] {
            if (!logic_runtime) {
                return;
            }
            logic_event_count += logic_runtime->take_events().size();
            logic_invocation_count += logic_runtime->take_invocations().size();
            spawn_request_count += logic_runtime->take_spawn_requests().size();
            warp_request_count += logic_runtime->take_warp_requests().size();
        };
        if (fixed_scene) {
            logic_runtime.emplace(fixed_scene->layout, options.seed);
            logic_runtime->activate_level();
            if (player_motion) {
                logic_runtime->update_player_position(player_motion->position());
            }
            drain_logic();
        }
        if (player_motion) {
            renderer.set_camera_target(player_motion->position(), 32.0F);
        }
        std::uint64_t frames = 0;
        bool rendered_once = false;
        auto previous_frame = std::chrono::steady_clock::now();
        while (window.process_events()) {
            const auto current_frame = std::chrono::steady_clock::now();
            const float elapsed = std::chrono::duration<float>(current_frame - previous_frame).count();
            previous_frame = current_frame;
            if (player_motion && player_instance_index) {
                if (const auto click = window.take_left_click(); click && rendered_once) {
                    const auto destination = renderer.ground_position_at_pixel(
                        (*click)[0], window.height() - 1 - (*click)[1], window.width(),
                        window.height(), player_motion->position()[1]);
                    active_path = navigation->find_path(player_motion->position(), destination);
                    std::cout << "click_destination=" << destination[0] << ',' << destination[1]
                              << ',' << destination[2]
                              << " path_nodes=" << active_path.size() << '\n';
                    std::cout.flush();
                    next_path_node = active_path.size() > 1U ? 1U : active_path.size();
                    if (next_path_node < active_path.size()) {
                        auto waypoint = active_path[next_path_node];
                        waypoint[1] += player_floor_offset;
                        player_motion->set_destination(waypoint);
                    } else {
                        player_motion->stop();
                    }
                }
                player_motion->advance(std::min(elapsed, 0.1F));
                while (!player_motion->moving() && next_path_node < active_path.size()) {
                    ++next_path_node;
                    if (next_path_node < active_path.size()) {
                        auto waypoint = active_path[next_path_node];
                        waypoint[1] += player_floor_offset;
                        player_motion->set_destination(waypoint);
                    }
                }
                renderer.set_instance_position(*player_instance_index, player_motion->position());
                renderer.set_camera_target(player_motion->position(), 32.0F);
                if (logic_runtime) {
                    logic_runtime->update(std::min(elapsed, 0.1F));
                    logic_runtime->update_player_position(player_motion->position());
                    drain_logic();
                }
            }
            window.draw_scene_frame(renderer);
            rendered_once = true;
            ++frames;
            if (options.frame_limit != 0 && frames >= options.frame_limit) {
                break;
            }
        }
        const auto& render_stats = renderer.stats();
        std::cout << "desktop_state=" << scene_state << " resources=" << index.records().size()
                  << " cached_unit_files=" << loader.cached_definition_count()
                  << " level_pieces=" << levelsets.pieces().size()
                  << " chunks=" << chunk_count
                  << " player=" << player_name
                  << " layout_objects=" << layout_object_count
                  << " placed_monsters=" << placed_monster_count
                  << " meshes=" << render_stats.mesh_resources
                  << " instances=" << render_stats.instances
                  << " draw_batches=" << render_stats.draw_batches
                  << " textures=" << render_stats.texture_resources
                  << " textured_batches=" << render_stats.textured_batches
                  << " placed_triangles=" << render_stats.placed_triangles
                  << " logic_events=" << logic_event_count
                  << " logic_invocations=" << logic_invocation_count
                  << " spawn_requests=" << spawn_request_count
                  << " warp_requests=" << warp_request_count
                  << " frames=" << frames;
        if (player_motion) {
            std::cout << " player_position=" << player_motion->position()[0] << ','
                      << player_motion->position()[1] << ',' << player_motion->position()[2];
            std::cout << " navigation_cells=" << navigation->walkable_cell_count();
        }
        std::cout << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "desktop failed: " << error.what() << '\n';
        return 1;
    }
}
