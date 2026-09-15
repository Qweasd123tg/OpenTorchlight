#include "torchlight/interaction.hpp"
#include "torchlight/frontend.hpp"
#include "torchlight/gles_ui_renderer.hpp"
#include "torchlight/checkpoint.hpp"
#include "torchlight/save_store.hpp"
#include <random>
#include "torchlight/actor_motion.hpp"
#include "torchlight/adm_document.hpp"
#include "torchlight/animation_events.hpp"
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
#include "torchlight/ogre_mesh.hpp"
#include "torchlight/ogre_skeleton.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/player.hpp"
#include "torchlight/player_session.hpp"
#include "torchlight/inventory_view.hpp"
#include "torchlight/random_level.hpp"
#include "torchlight/scene_animation.hpp"
#include "torchlight/scene_geometry.hpp"
#include "torchlight/skeletal_animation.hpp"
#include "torchlight/spawn_class.hpp"
#include "torchlight/unit_definition.hpp"
#include "torchlight/unit_type.hpp"

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
#include <type_traits>

namespace {

constexpr float kCameraDistance = 28.5F;

class DesktopError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct Options {
    std::filesystem::path game_directory;
    std::uint64_t frame_limit = 0;
    std::optional<std::size_t> main_stratum;
    std::uint32_t seed = 42;
    std::optional<std::filesystem::path> save_directory;
};

Options parse_options(int argc, char** argv) {
    if (argc < 2) {
        throw DesktopError(
            "usage: torchlight_desktop /path/to/Torchlight/game "
            "[--save-dir PATH] [--frames N] [--main-stratum N --seed N]");
    }
    Options options;
    options.game_directory = argv[1];
    for (int argument = 2; argument < argc; argument += 2) {
        if (argument + 1 >= argc) {
            throw DesktopError("desktop option has no value");
        }
        const std::string name = argv[argument];
        const std::string value = argv[argument + 1];
        if (name == "--save-dir") {
            if (value.empty()) throw DesktopError("empty save directory");
            options.save_directory = value;
        } else if (name == "--frames") {
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

    [[nodiscard]] std::vector<std::uint32_t> take_key_presses() {
        auto keys = std::move(key_presses_);
        key_presses_.clear();
        return keys;
    }

    void draw_scene_frame(torchlight::GlesSceneRenderer& renderer,
                          const std::vector<torchlight::InventoryViewLine>& lines,
                          bool inventory_open) {
        renderer.draw(width_, height_);
        glEnable(GL_SCISSOR_TEST);
        const int top_height = std::max(54, height_ / 12);
        fill_rectangle(0, height_ - top_height, width_, top_height, 0.18F, 0.105F, 0.035F);
        const int status_size = std::max(12, std::min(width_, height_) / 45);
        fill_rectangle(status_size, height_ - top_height / 2 - status_size / 2, status_size,
                       status_size, 0.72F, 0.43F, 0.10F);
        // prototype: diagnostic overlay geometry/colors, not original UI metrics.
        const int scale = width_ >= 950 ? 2 : 1;
        const int line_height = 11 * scale;
        const int left = 24;
        int top = height_ - 12;
        if (inventory_open) {
            fill_rectangle(12, 12, std::max(0, width_ - 24), std::max(0, height_ - 24),
                           0.075F, 0.070F, 0.060F);
            top = height_ - 26;
        }
        for (const auto& line : lines) {
            if (top - line_height < 12) break;
            if (line.selected)
                fill_rectangle(left - 6, top - line_height + 3,
                               std::max(0, width_ - 2 * left), line_height,
                               0.28F, 0.20F, 0.08F);
            const auto columns = static_cast<std::size_t>(std::max(0, width_ - 2 * left) / (6 * scale));
            int x = left;
            for (const char c : line.text.substr(0, columns)) {
                const auto glyph = torchlight::inventory_glyph(c);
                for (int row = 0; row < 7; ++row) {
                    for (int column = 0; column < 5; ++column) {
                        if (glyph[row] & (1U << (4 - column)))
                            fill_rectangle(x + column * scale, top - (row + 1) * scale,
                                           scale, scale, 0.93F, 0.88F, 0.72F);
                    }
                }
                x += 6 * scale;
            }
            top -= line_height;
        }
        glDisable(GL_SCISSOR_TEST);
        if (glGetError() != GL_NO_ERROR) {
            throw DesktopError("OpenGL ES failed while drawing the scene preview");
        }
        require_egl(eglSwapBuffers(egl_display_, egl_surface_) == EGL_TRUE, "eglSwapBuffers");
    }

    void draw_menu_frame(torchlight::GlesUiRenderer& renderer, const torchlight::FrontendFrame& frame) {
        renderer.draw(frame, width_, height_);
        if (glGetError() != GL_NO_ERROR) throw DesktopError("OpenGL ES failed while drawing the frontend");
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
        if (state == WL_KEYBOARD_KEY_STATE_PRESSED)
            static_cast<DesktopWindow*>(data)->key_presses_.push_back(key);
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
    std::vector<std::uint32_t> key_presses_;
};

// Prototype text input: physical US A-Z / digits. Arbitrary UTF-8 save names are
// retained by the codec; full compositor/IME input is a separate UI boundary.
void frontend_key(torchlight::Frontend& frontend, std::uint32_t key) {
    using K = torchlight::FrontendKey;
    if (key == KEY_ESC) frontend.key(K::back);
    else if (key == KEY_UP) frontend.key(K::previous);
    else if (key == KEY_DOWN || key == KEY_TAB) frontend.key(K::next);
    else if (key == KEY_ENTER || key == KEY_KPENTER) frontend.key(K::accept);
    else if (key == KEY_BACKSPACE) frontend.key(K::backspace);
    else {
        static const std::pair<std::uint32_t,char> keys[] = {
            {KEY_A,'a'},{KEY_B,'b'},{KEY_C,'c'},{KEY_D,'d'},{KEY_E,'e'},{KEY_F,'f'},
            {KEY_G,'g'},{KEY_H,'h'},{KEY_I,'i'},{KEY_J,'j'},{KEY_K,'k'},{KEY_L,'l'},
            {KEY_M,'m'},{KEY_N,'n'},{KEY_O,'o'},{KEY_P,'p'},{KEY_Q,'q'},{KEY_R,'r'},
            {KEY_S,'s'},{KEY_T,'t'},{KEY_U,'u'},{KEY_V,'v'},{KEY_W,'w'},{KEY_X,'x'},
            {KEY_Y,'y'},{KEY_Z,'z'},{KEY_0,'0'},{KEY_1,'1'},{KEY_2,'2'},{KEY_3,'3'},
            {KEY_4,'4'},{KEY_5,'5'},{KEY_6,'6'},{KEY_7,'7'},{KEY_8,'8'},{KEY_9,'9'},
            {KEY_SPACE,' '},{KEY_MINUS,'-'}};
        for (const auto& pair : keys) if (pair.first == key) frontend.text(pair.second);
    }
}

struct LoadedDesktopLevel {
    torchlight::DungeonAddress address;
    torchlight::DungeonManifest dungeon;
    torchlight::LevelRules rules;
    torchlight::LayoutManifest layout;
    torchlight::FixedSceneGeometry geometry;
    torchlight::NavigationGrid navigation;
    std::array<float, 3> player_start{};
    float player_start_angle = 0.0F;
    std::array<float, 3> recovery_anchor{};
    float recovery_angle = 0.0F;
    bool recovery_anchor_resolved = false;
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
    std::uint32_t base_seed,
    const torchlight::LevelEntryRequest* entry) {
    LoadedDesktopLevel result;
    result.dungeon = loader.load_dungeon(
        dungeon_data_file(requested_address.dungeon_name));
    const auto floor = torchlight::select_dungeon_floor(
        result.dungeon, requested_address.depth);
    result.address = {result.dungeon.name, floor.depth};
    result.rules = loader.load_rules(result.dungeon.strata[floor.stratum_index].ruleset);
    const auto seed = level_seed(base_seed, floor.depth);
    const auto resolve_transition_start = [&]() {
        if (entry == nullptr) {
            return false;
        }
        auto normalized_entry = *entry;
        normalized_entry.destination = result.address;
        if (const auto anchor = torchlight::find_same_dungeon_entry_anchor(result.layout, normalized_entry)) {
            result.recovery_anchor = anchor->position;
            result.recovery_angle = anchor->angle_degrees;
            result.recovery_anchor_resolved = true;
        }
        const auto arrival = torchlight::find_same_dungeon_level_arrival(
            result.layout, normalized_entry);
        if (!arrival) {
            return false;
        }
        result.player_start = arrival->position;
        result.player_start_angle = arrival->angle_degrees;
        return true;
    };

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
        if (!resolve_transition_start()) {
            result.player_start = torchlight::generated_player_start(loader, generated);
        }
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
        if (!resolve_transition_start()) {
            result.player_start = torchlight::layout_player_start(result.layout);
        }
        collision = torchlight::build_fixed_level_collision(archive, levelsets, scene);
        result.scene_state = result.dungeon.strata[floor.stratum_index].is_town
                                 ? "town-playable"
                                 : "fixed-dungeon";
    }

    // Initial boot / special entry paths still use the existing prototype start.
    // Ordinary in-dungeon transitions preserve the separate original level anchor.
    if (!result.recovery_anchor_resolved) {
        result.recovery_anchor = result.player_start;
        result.recovery_angle = result.player_start_angle;
    }
    result.navigation = torchlight::NavigationGrid::build(collision);
    if (const auto start_cell = result.navigation.nearest_walkable(result.player_start)) {
        result.player_floor_offset =
            result.player_start[1] -
            result.navigation.cell((*start_cell)[0], (*start_cell)[1]).height;
    }
    return result;
}

struct PlayerAnimationResources {
    torchlight::OgreSkeleton bind;
    torchlight::OgreSkeleton idle;
    torchlight::OgreSkeleton run;
    std::vector<torchlight::ModelAnimationClip> attacks;
    std::optional<torchlight::ModelAnimationClip> death;
    std::string idle_name;
    std::string run_name;
};

PlayerAnimationResources load_player_animations(
    const torchlight::PakArchive& archive, const torchlight::PlayerPrototype& player,
    const torchlight::UnitTypeHierarchy& unit_types) {
    const auto* mesh_entry = archive.find_normalized(player.mesh_path);
    if (mesh_entry == nullptr) {
        throw DesktopError("player animation mesh is absent from pak.zip");
    }
    const auto mesh = torchlight::parse_ogre_mesh(archive.read(*mesh_entry));
    const auto slash = mesh_entry->name.find_last_of("/\\");
    const auto directory = slash == std::string::npos
                               ? std::string{}
                               : mesh_entry->name.substr(0, slash + 1U);
    const auto load = [&](const std::string& name) {
        const auto* entry = archive.find_normalized(directory + name);
        if (entry == nullptr) {
            throw DesktopError("player animation resource is absent from pak.zip: " + name);
        }
        return torchlight::parse_ogre_skeleton(archive.read(*entry));
    };
    if (mesh.skeleton_file.empty()) {
        throw DesktopError("player mesh has no OGRE skeleton link");
    }
    auto idle = torchlight::load_model_animation(
        archive, mesh_entry->name, mesh.skeleton_file,
        torchlight::SceneAnimationKind::idle);
    auto run = torchlight::load_model_animation(
        archive, mesh_entry->name, mesh.skeleton_file,
        torchlight::SceneAnimationKind::run);
    const auto attack_prefix = player.starting_weapon ?
        torchlight::weapon_attack_prefix(
            torchlight::weapon_attack_traits(player.starting_weapon->unit_type, unit_types).family,
            player.starting_weapon->attack_hand) : std::string("ATTACK");
    auto attacks = torchlight::load_model_animations_by_prefix(
        archive, mesh_entry->name, mesh.skeleton_file, attack_prefix);
    if (!idle || !run || attacks.empty()) {
        throw DesktopError(
            "player animation manifest lacks idle, run, or attack clips");
    }
    PlayerAnimationResources result;
    result.bind = load(mesh.skeleton_file);
    result.idle = std::move(idle->animation_skeleton);
    result.run = std::move(run->animation_skeleton);
    result.attacks = std::move(attacks);
    result.death = torchlight::load_model_animation(archive, mesh_entry->name,
        mesh.skeleton_file, torchlight::SceneAnimationKind::death);
    result.idle_name = std::move(idle->animation_name);
    result.run_name = std::move(run->animation_name);
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
        torchlight::UiResources ui_resources(archive);
        torchlight::GlesUiRenderer ui_renderer(archive, ui_resources);
        std::vector<torchlight::FrontendClass> frontend_classes;
        for (const auto& p : players) frontend_classes.push_back({p.guid, narrow_ascii(p.name)});
        torchlight::Frontend frontend(ui_resources, std::move(frontend_classes));
        torchlight::SaveStore saves(options.save_directory ? *options.save_directory : torchlight::SaveStore::default_directory());
        const auto resource_identity = torchlight::checkpoint_resource_identity(archive);
        const auto refresh_saves = [&] {
            try { frontend.set_saves(saves.list(resource_identity)); }
            catch (const std::exception& e) { frontend.set_saves({}); frontend.error(e.what()); }
        };
        refresh_saves();
        torchlight::PlayerPrototype selected_player = players.front();
        torchlight::LevelTransitionState transitions(initial_address);
        std::optional<torchlight::LevelEntryRequest> pending_entry;
        std::uint64_t total_frames = 0;
        std::size_t completed_transitions = 0;
        bool app_running = true;
        const bool direct_preview = options.main_stratum.has_value() || options.frame_limit != 0;
        bool gameplay_active = direct_preview;
        bool resume_saved_position = false;
        std::uint32_t campaign_seed = options.seed;
        torchlight::CampaignCheckpoint campaign;
        campaign.slot = "preview"; campaign.seed = campaign_seed; campaign.class_guid = selected_player.guid;
        campaign.character_name = "Preview"; campaign.resource_identity = resource_identity; campaign.current = initial_address;
        torchlight::PlayerSession session(selected_player, level_seed(campaign_seed, initial_address.depth), &unit_type_hierarchy);
        torchlight::InventoryView inventory_view;
        if (direct_preview) frontend.entered_game();
        const auto visual_prototype = [&](const torchlight::PlayerInventory& inventory) {
            auto prototype = selected_player;
            prototype.starting_weapon.reset();
            if (const auto* item = inventory.equipped(torchlight::InventorySlot::weapon);
                item && item->weapon) prototype.starting_weapon = item->weapon->prototype;
            return prototype;
        };
        while (app_running) {
            if (!gameplay_active) {
                if (!window.process_events()) break;
                static_cast<void>(frontend.frame(window.width(), window.height()));
                for (const auto key : window.take_key_presses()) { frontend_key(frontend, key); static_cast<void>(frontend.frame(window.width(), window.height())); }
                if (const auto click = window.take_left_click()) frontend.click(static_cast<float>((*click)[0]), static_cast<float>((*click)[1]));
                if (frontend.page() == torchlight::FrontendPage::quit) break;
                if (const auto request = frontend.take_request()) {
                    try {
                        torchlight::CampaignCheckpoint candidate;
                        if (request->command == torchlight::FrontendCommand::load) candidate = saves.read(request->slot, resource_identity);
                        else if (request->command == torchlight::FrontendCommand::create) {
                            candidate.slot = saves.allocate_slot(); candidate.class_guid = request->class_guid;
                            candidate.character_name = request->name; candidate.resource_identity = resource_identity;
                            std::random_device entropy;
                            do { candidate.seed = entropy(); } while (candidate.seed == 0);
                        } else throw DesktopError("unexpected command outside gameplay");
                        const auto chosen = std::find_if(players.begin(), players.end(), [&](const auto& p) { return p.guid == candidate.class_guid; });
                        if (chosen == players.end()) throw DesktopError("saved class is unavailable in this resource set");
                        auto candidate_session = request->command == torchlight::FrontendCommand::load
                            ? torchlight::CheckpointAccess::restore_player(*chosen, candidate.player, candidate.seed, &unit_type_hierarchy)
                            : torchlight::PlayerSession(*chosen, candidate.seed, &unit_type_hierarchy);
                        auto candidate_transitions = request->command == torchlight::FrontendCommand::load
                            ? torchlight::CheckpointAccess::restore_transitions(candidate)
                            : torchlight::LevelTransitionState(candidate.current);
                        selected_player = *chosen; session = std::move(candidate_session); campaign = std::move(candidate);
                        campaign_seed = campaign.seed; transitions = std::move(candidate_transitions); pending_entry.reset();
                        resume_saved_position = request->command == torchlight::FrontendCommand::load;
                        gameplay_active = true; frontend.entered_game(); inventory_view.status.clear();
                    } catch (const std::exception& e) { frontend.error(std::string("CANNOT OPEN GAME: ") + e.what()); }
                }
                if (!gameplay_active) window.draw_menu_frame(ui_renderer, frontend.frame(window.width(), window.height()));
                continue;
            }
            try {
            session.enter_level();
            inventory_view.open = false;
            auto player_visual = visual_prototype(session.inventory());
            auto player_animations = load_player_animations(
                archive, player_visual, unit_type_hierarchy);
            auto level = load_desktop_level(
                archive, levelsets, scene_loader,
                transitions.current(), campaign_seed,
                pending_entry ? &*pending_entry : nullptr);
            if (level.address.dungeon_name != transitions.current().dungeon_name ||
                level.address.depth != transitions.current().depth) {
                transitions.commit(level.address);
            }
            pending_entry.reset();
            torchlight::ActorMotion player_motion(
                level.player_start, selected_player.running_speed);
            std::optional<torchlight::InteractionRequest> active_interaction;
            std::optional<std::uint64_t> active_pickup;
            std::vector<std::array<float, 3>> active_path;
            std::size_t next_path_node = 0;

            torchlight::LogicRuntime logic_runtime(
                level.layout, level_seed(campaign_seed, level.address.depth));
            torchlight::RuntimeEntityWorld entity_world(
                level.layout, index, loader, spawn_classes, unit_types,
                level_seed(campaign_seed, level.address.depth),
                std::max(1, level.address.depth));
            torchlight::EnemyController enemies(level_seed(campaign_seed, level.address.depth) ^ 0x9e3779b9U);
            const auto* saved_floor = torchlight::find_floor(campaign, level.address);
            if (saved_floor) {
                torchlight::CheckpointAccess::restore_floor(*saved_floor, entity_world, logic_runtime, enemies);
                if (resume_saved_position) {
                    if (!torchlight::checkpoint_position_walkable(level.navigation, saved_floor->player_position, saved_floor->floor_offset))
                        throw DesktopError("saved position is not walkable in the regenerated layout");
                    level.player_start = saved_floor->player_position; level.player_start_angle = saved_floor->player_angle;
                    level.recovery_anchor = saved_floor->recovery_anchor; level.recovery_angle = saved_floor->recovery_angle;
                    level.recovery_anchor_resolved = saved_floor->original_recovery_anchor;
                    level.player_floor_offset = saved_floor->floor_offset;
                    player_motion = torchlight::ActorMotion(level.player_start, selected_player.running_speed);
                }
            } else if (resume_saved_position) throw DesktopError("save does not contain the current floor");
            resume_saved_position = false;
            torchlight::InteractionDispatcher interactions(level.layout, entity_world, logic_runtime);
            level.placed_monster_count = torchlight::append_layout_monster_geometry(
                archive, index, loader, level.layout, level.geometry, 0, &entity_world);
            for (auto& instance : level.geometry.instances) if (const auto* e = entity_world.find(instance.runtime_entity_id)) {
                instance.transform.position = e->position; instance.visible = e->visible && e->alive;
            }
            torchlight::append_player_geometry(
                archive, selected_player, level.player_start, level.geometry);
            const auto player_instance_index = level.geometry.instances.size() - 1U;
            level.geometry.instances[player_instance_index].transform.orientation =
                torchlight::yaw_rotation(level.player_start_angle);
            const auto player_mesh_index =
                level.geometry.instances[player_instance_index].mesh_index;
            auto player_weapon_instance_index =
                torchlight::append_player_weapon_geometry(
                    archive, player_visual, level.player_start, level.geometry);
            std::unordered_map<std::string, std::size_t> weapon_instance_cache;
            if (player_weapon_instance_index && player_visual.starting_weapon)
                weapon_instance_cache.emplace(player_visual.starting_weapon->mesh_path,
                                              *player_weapon_instance_index);
            if (player_weapon_instance_index) {
                level.geometry.instances[*player_weapon_instance_index]
                    .transform.orientation =
                    torchlight::yaw_rotation(level.player_start_angle);
            }
            auto scene_idle_animations = torchlight::load_scene_idle_animations(
                archive, level.geometry, player_mesh_index);
            auto scene_run_animations = torchlight::load_scene_animations(
                archive, level.geometry, torchlight::SceneAnimationKind::run,
                player_mesh_index);
            auto scene_hit_animations = torchlight::load_scene_animations(
                archive, level.geometry, torchlight::SceneAnimationKind::hit,
                player_mesh_index);
            auto scene_death_animations = torchlight::load_scene_animations(
                archive, level.geometry, torchlight::SceneAnimationKind::death,
                player_mesh_index);
            auto& combat = session.combat();
            auto& player_combat = session.health();
            torchlight::AttackAnimationCatalog attack_catalog(archive);
            const auto resolve_attack = [&](std::string_view mesh, std::string_view prefix) {
                return attack_catalog.resolve(mesh, prefix);
            };
            combat.set_animation_resolver(resolve_attack);
            enemies.set_animation_resolver(resolve_attack);
            std::unordered_map<std::uint64_t, std::string> reported_attack_issues;
            std::optional<torchlight::GlesSceneRenderer> renderer;
            std::optional<torchlight::WarpRequest> pending_warp;
            std::unordered_map<std::uint64_t, std::size_t> runtime_instance_indices;

            std::size_t logic_event_count = 0;
            std::size_t logic_invocation_count = 0;
            std::size_t spawn_request_count = 0;
            std::size_t spawn_control_request_count = 0;
            std::size_t spawned_entity_count = 0;
            std::size_t hidden_spawned_entity_count = 0;
            std::size_t destroyed_spawned_entity_count = 0;
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
            std::size_t loot_death_count = 0;
            std::size_t loot_entity_count = 0;
            std::size_t missing_loot_class_count = 0;
            std::size_t equipped_armor_count = 0;
            std::size_t equipped_weapon_count = 0;
            std::size_t combat_attack_count = 0;
            std::size_t combat_kill_count = 0;
            std::size_t enemy_chase_count = 0;
            std::size_t enemy_attack_count = 0;
            std::size_t player_death_count = 0;
            std::uint64_t level_frames = 0;
            std::size_t player_animation_updates = 0;
            std::size_t scene_animation_updates = 0;
            std::size_t enemy_animation_updates = 0;
            float player_animation_time = 0.0F;
            float player_transition_time = 0.0F;
            float scene_animation_time = 0.0F;
            enum class PlayerAnimationState { idle, run, attack, death };
            PlayerAnimationState player_animation_state = PlayerAnimationState::idle;
            PlayerAnimationState player_transition_from_state =
                PlayerAnimationState::idle;
            bool player_attack_animation_active = false;
            torchlight::AttackClip player_pose_attack_clip;
            torchlight::AttackClip player_previous_pose_clip;
            torchlight::AttackClip player_transition_attack_clip;
            float player_previous_attack_speed = 1.0F;
            float player_transition_attack_speed = 1.0F;
            bool player_transition_active = false;
            float player_transition_from_time = 0.0F;
            enum class EnemyAnimationState { idle, run, attack, hit, death, hidden };
            struct EnemyAnimationPlayback {
                EnemyAnimationState state = EnemyAnimationState::idle;
                float time = 0.0F;
            };
            std::unordered_map<std::uint64_t, EnemyAnimationPlayback>
                enemy_animation_playback;

            for (std::size_t instance_index = 0;
                 instance_index < level.geometry.instances.size(); ++instance_index) {
                const auto entity_id = level.geometry.instances[instance_index].runtime_entity_id;
                if (entity_id != 0) {
                    runtime_instance_indices.emplace(entity_id, instance_index);
                }
            }

            const auto rebuild_renderer = [&] {
                renderer.emplace(level.geometry, archive, materials);
                ++renderer_rebuild_count;
                scene_idle_animations = torchlight::load_scene_idle_animations(
                    archive, level.geometry, player_mesh_index);
                scene_run_animations = torchlight::load_scene_animations(
                    archive, level.geometry, torchlight::SceneAnimationKind::run, player_mesh_index);
                scene_hit_animations = torchlight::load_scene_animations(
                    archive, level.geometry, torchlight::SceneAnimationKind::hit, player_mesh_index);
                scene_death_animations = torchlight::load_scene_animations(
                    archive, level.geometry, torchlight::SceneAnimationKind::death, player_mesh_index);
                renderer->set_camera_target(player_motion.position(), kCameraDistance);
            };
            auto drain_logic = [&] {
                // Flush only after callers release pointers into entities_.
                const auto loot = entity_world.resolve_death_loot(logic_runtime);
                loot_death_count += loot.deaths;
                loot_entity_count += loot.spawns.entities_created;
                missing_loot_class_count += loot.missing_classes;
                resolved_unit_type_count += loot.spawns.resolved_unit_types;
                unresolved_unit_type_count += loot.spawns.unresolved_unit_types;
                missing_spawn_resource_count += loot.spawns.missing_resources;
                bool entity_visibility_changed = false;
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
                    spawn_request_count += stats.spawn_requests;
                    spawn_control_request_count += stats.control_requests;
                    spawned_entity_count += stats.entities_created;
                    hidden_spawned_entity_count += stats.entities_hidden;
                    destroyed_spawned_entity_count += stats.entities_destroyed;
                    entity_visibility_changed = entity_visibility_changed ||
                                                stats.entities_hidden != 0 ||
                                                stats.entities_destroyed != 0;
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
                if (geometry_changed && renderer) rebuild_renderer();
                if (entity_visibility_changed) {
                    for (const auto& entity : entity_world.entities()) {
                        const auto instance = runtime_instance_indices.find(entity.id);
                        if (instance == runtime_instance_indices.end()) {
                            continue;
                        }
                        const bool visible = entity.alive && entity.visible;
                        level.geometry.instances[instance->second].visible = visible;
                        if (renderer) {
                            renderer->set_instance_visible(instance->second, visible);
                        }
                    }
                }
                logic_event_count += logic_runtime.take_events().size();
                logic_invocation_count += logic_runtime.take_invocations().size();
                auto warps = logic_runtime.take_warp_requests();
                warp_request_count += warps.size();
                if (!warps.empty() && !pending_warp) {
                    pending_warp = std::move(warps.front());
                }
            };

            // Restored object flags/counters/timers must not be overwritten by activation.
            if (!saved_floor) {
                logic_runtime.activate_level();
                logic_runtime.update_player_position(player_motion.position());
            }
            drain_logic();
            renderer.emplace(level.geometry, archive, materials);
            renderer->set_camera_target(player_motion.position(), kCameraDistance);
            bool return_to_menu = false;
            const auto capture_floor = [&] {
                torchlight::FloorCheckpoint state; state.address = level.address;
                state.layout_identity = torchlight::checkpoint_layout_identity(level.layout);
                state.player_position = player_motion.position(); state.recovery_anchor = level.recovery_anchor;
                state.recovery_angle = level.recovery_angle; state.floor_offset = level.player_floor_offset;
                state.original_recovery_anchor = level.recovery_anchor_resolved;
                const auto& rotation = level.geometry.instances.at(player_instance_index).transform.orientation;
                state.player_angle = std::atan2(rotation[2], rotation[8]) * 57.295779513082320876F;
                state.world = torchlight::CheckpointAccess::capture(entity_world);
                state.logic = torchlight::CheckpointAccess::capture(logic_runtime);
                state.enemies = torchlight::CheckpointAccess::capture(enemies);
                return state;
            };
            const auto checkpoint_now = [&] {
                if (pending_warp) throw DesktopError("finish the pending transition before saving");
                auto candidate = campaign;
                candidate.current = transitions.current(); candidate.last_dungeon = transitions.last_dungeon();
                candidate.player = torchlight::CheckpointAccess::capture(session);
                torchlight::remember_floor(candidate, capture_floor());
                candidate.revision = saves.write(candidate);
                campaign = std::move(candidate);
                std::cout << "checkpoint_saved=" << campaign.slot << " revision=" << campaign.revision << '\n';
            };
            const auto face_instance_toward = [&](std::size_t instance_index,
                                                  const std::array<float, 3>& target) {
                auto& transform = level.geometry.instances.at(instance_index).transform;
                const float delta_x = target[0] - transform.position[0];
                const float delta_z = target[2] - transform.position[2];
                if (std::hypot(delta_x, delta_z) <= 0.00001F) {
                    return;
                }
                constexpr float kRadiansToDegrees = 57.295779513082320876F;
                const float angle = std::remainder(
                    std::atan2(delta_x, delta_z) * kRadiansToDegrees,
                    360.0F);
                transform.orientation = torchlight::yaw_rotation(angle);
                renderer->set_instance_angle(instance_index, angle);
            };
            const auto animation_for_mesh = [](
                                                const auto& animations,
                                                std::size_t mesh_index)
                -> const torchlight::SceneMeshAnimation* {
                const auto found = std::find_if(
                    animations.begin(), animations.end(), [&](const auto& animation) {
                        return animation.mesh_index == mesh_index;
                    });
                return found == animations.end() ? nullptr : &*found;
            };
            const auto change_equipment = [&](bool remove) {
                const auto id = inventory_view.selected_id(session.inventory());
                if (!player_combat.alive() || combat.attack_in_progress()) {
                    inventory_view.status = torchlight::inventory_change_message(
                        !player_combat.alive() ? torchlight::InventoryChange::dead
                                              : torchlight::InventoryChange::busy);
                    return;
                }
                // Validate all derived stats on a private candidate BEFORE adding
                // cached render instances; a rejected item changes neither side.
                auto candidate_session = session;
                torchlight::InventoryChange proposed;
                try { proposed = remove ? candidate_session.unequip(id) : candidate_session.equip(id); }
                catch (const std::exception& error) {
                    inventory_view.status = std::string("EQUIPMENT REJECTED: ") + error.what();
                    std::cerr << "inventory_stats_error=" << error.what() << '\n';
                    return;
                }
                const auto& preview = candidate_session.inventory();
                if (proposed != torchlight::InventoryChange::changed) {
                    inventory_view.status = torchlight::inventory_change_message(proposed);
                    return;
                }
                const auto* before_weapon = session.weapon();
                const auto* after_weapon = preview.equipped(torchlight::InventorySlot::weapon);
                const bool weapon_changed = (before_weapon ? before_weapon->id : 0) !=
                                            (after_weapon ? after_weapon->id : 0);
                auto candidate_visual = visual_prototype(preview);
                std::optional<PlayerAnimationResources> candidate_animations;
                auto candidate_instance = player_weapon_instance_index;
                bool geometry_added = false;
                if (weapon_changed) {
                    try {
                        candidate_animations = load_player_animations(
                            archive, candidate_visual, unit_type_hierarchy);
                        candidate_instance.reset();
                        if (candidate_visual.starting_weapon) {
                            const auto& path = candidate_visual.starting_weapon->mesh_path;
                            const auto cached = weapon_instance_cache.find(path);
                            if (cached != weapon_instance_cache.end()) candidate_instance = cached->second;
                            else {
                                if (path.empty()) throw DesktopError("equipped weapon has no mesh path");
                                candidate_instance = torchlight::append_player_weapon_geometry(
                                    archive, candidate_visual, player_motion.position(), level.geometry);
                                if (!candidate_instance) throw DesktopError("equipped weapon model is missing");
                                weapon_instance_cache.emplace(path, *candidate_instance);
                                level.geometry.instances[*candidate_instance].visible = false;
                                geometry_added = true;
                            }
                        }
                    } catch (const std::exception& error) {
                        inventory_view.status = "EQUIP REJECTED: MODEL/ANIMATION UNAVAILABLE. ITEM KEPT.";
                        std::cerr << "inventory_visual_error=" << error.what() << '\n';
                        return;
                    }
                }
                static_assert(std::is_nothrow_move_assignable_v<torchlight::PlayerSession>);
                session = std::move(candidate_session);
                inventory_view.status = torchlight::inventory_change_message(proposed);
                if (weapon_changed) {
                    if (player_weapon_instance_index) {
                        level.geometry.instances[*player_weapon_instance_index].visible = false;
                        renderer->set_instance_visible(*player_weapon_instance_index, false);
                    }
                    player_weapon_instance_index = candidate_instance;
                    player_visual = std::move(candidate_visual);
                    player_animations = std::move(*candidate_animations);
                    player_animation_state = PlayerAnimationState::idle;
                    player_transition_active = false;
                    player_animation_time = 0.0F;
                    player_attack_animation_active = false;
                    if (player_weapon_instance_index)
                        level.geometry.instances[*player_weapon_instance_index].visible = true;
                    if (geometry_added) rebuild_renderer();
                    else if (player_weapon_instance_index)
                        renderer->set_instance_visible(*player_weapon_instance_index, true);
                    ++equipped_weapon_count;
                } else ++equipped_armor_count;
            };
            bool rendered_once = false;
            bool saved_for_exit = false;
            auto previous_frame = std::chrono::steady_clock::now();

            while (!pending_warp) {
                if (!window.process_events()) {
                    app_running = false;
                    break;
                }
                if (frontend.page() == torchlight::FrontendPage::pause) {
                    static_cast<void>(frontend.frame(window.width(), window.height()));
                    for (const auto key : window.take_key_presses()) { frontend_key(frontend, key); static_cast<void>(frontend.frame(window.width(), window.height())); }
                    if (const auto click = window.take_left_click()) frontend.click(static_cast<float>((*click)[0]), static_cast<float>((*click)[1]));
                    if (const auto request = frontend.take_request()) {
                        try { checkpoint_now(); frontend.saved(request->command); saved_for_exit = request->command == torchlight::FrontendCommand::save_and_quit; }
                        catch (const std::exception& e) { frontend.error(std::string("SAVE FAILED: ") + e.what()); }
                    }
                    if (frontend.page() == torchlight::FrontendPage::main) { return_to_menu = true; break; }
                    if (frontend.page() == torchlight::FrontendPage::quit) { app_running = false; break; }
                    if (frontend.page() == torchlight::FrontendPage::pause)
                        window.draw_menu_frame(ui_renderer, frontend.frame(window.width(), window.height()));
                    previous_frame = std::chrono::steady_clock::now();
                    continue;
                }
                const auto current_frame = std::chrono::steady_clock::now();
                const float elapsed =
                    std::chrono::duration<float>(current_frame - previous_frame).count();
                previous_frame = current_frame;
                for (const auto key : window.take_key_presses()) {
                    if (!player_combat.alive()) {
                        if (key == KEY_ESC) { frontend.pause(); continue; }
                        if (key != KEY_R) continue;
                        const auto recovery = session.recover_at_entry(enemies, player_motion, level.recovery_anchor);
                        if (recovery.status != torchlight::RecoveryStatus::recovered) continue;
                        inventory_view.open = false;
                        active_interaction.reset(); interactions.cancel(); active_pickup.reset(); active_path.clear(); next_path_node = 0;
                        player_attack_animation_active = false;
                        player_animation_state = player_transition_from_state = PlayerAnimationState::idle;
                        player_animation_time = player_transition_time = 0;
                        player_transition_active = false;
                        player_pose_attack_clip.reset(); player_previous_pose_clip.reset(); player_transition_attack_clip.reset();
                        for (auto& pair : enemy_animation_playback) {
                            const auto* entity = entity_world.find(pair.first);
                            if (entity && entity->alive && entity->enabled) pair.second = {};
                        }
                        level.geometry.instances[player_instance_index].transform.orientation =
                            torchlight::yaw_rotation(level.recovery_angle);
                        renderer->set_instance_angle(player_instance_index, level.recovery_angle);
                        if (const auto cell = level.navigation.nearest_walkable(player_motion.position()))
                            level.player_floor_offset = player_motion.position()[1] -
                                level.navigation.cell((*cell)[0], (*cell)[1]).height;
                        inventory_view.status = "RECOVERED AT ENTRY. GOLD LOST " + std::to_string(recovery.gold_lost);
                        std::cout << "player_recovered=1 gold_lost=" << recovery.gold_lost << " gold=" << session.gold()
                                  << " original_entry_anchor=" << level.recovery_anchor_resolved << '\n';
                        continue;
                    }
                    if (key == KEY_I) inventory_view.open = !inventory_view.open;
                    else if (key == KEY_ESC) {
                        if (inventory_view.open) inventory_view.open = false;
                        else frontend.pause();
                    } else if (inventory_view.open) {
                        if (key == KEY_UP) inventory_view.move(-1, session.inventory());
                        else if (key == KEY_DOWN) inventory_view.move(1, session.inventory());
                        else if (key == KEY_ENTER || key == KEY_KPENTER) change_equipment(false);
                        else if (key == KEY_U) change_equipment(true);
                    }
                }
                if (!app_running) break;
                if (frontend.page() == torchlight::FrontendPage::pause) { static_cast<void>(window.take_left_click()); continue; }
                // prototype: pause while inspecting the bag; do not replay HITs
                // or run zero-period logic timers while this overlay is open.
                // prototype UI policy: pause simulation while dead; death pose still advances.
                const float simulation_elapsed = inventory_view.open || !player_combat.alive() ? 0.0F : std::min(elapsed, 0.1F);
                if (const auto click = window.take_left_click();
                    click && rendered_once && !inventory_view.open && player_combat.alive()) {
                    auto destination = renderer->ground_position_at_pixel(
                        (*click)[0], window.height() - 1 - (*click)[1], window.width(),
                        window.height(), player_motion.position()[1]);
                    if (combat.select_target(entity_world, destination, 2.0F)) {
                        const auto* selected = combat.target(entity_world);
                        destination = selected->position;
                        active_interaction.reset(); interactions.cancel();
                        active_pickup.reset();
                        ++selected_target_count;
                        std::cout << "selected_target=" << selected->id
                                  << " health=" << selected->health << '/'
                                  << selected->maximum_health << '\n';
                    } else if (const auto* item = entity_world.nearest_alive_item(
                                   destination, 2.0F, true)) {
                        combat.clear_target();
                        active_interaction.reset(); interactions.cancel();
                        active_pickup = item->id;
                        destination = item->position;
                        std::cout << "selected_item=" << item->id
                                  << " name=" << narrow_ascii(item->name) << '\n';
                    } else if (const auto interaction = interactions.select(destination, 3.0F)) {
                        combat.clear_target();
                        active_pickup.reset();
                        active_interaction = *interaction;
                        destination = interaction->position;
                        inventory_view.status = "SELECTED: " + narrow_ascii(interaction->label);
                        std::cout << "selected_interaction=" << interaction->object_id << '\n';
                    } else {
                        combat.clear_target();
                        active_interaction.reset(); interactions.cancel();
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
                const auto previous_player_position = player_motion.position();
                player_motion.advance(simulation_elapsed);
                while (player_combat.alive() && !inventory_view.open && !player_motion.moving() && next_path_node < active_path.size()) {
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
                const float player_dx =
                    player_motion.position()[0] - previous_player_position[0];
                const float player_dz =
                    player_motion.position()[2] - previous_player_position[2];
                if (std::hypot(player_dx, player_dz) > 0.00001F) {
                    constexpr float kRadiansToDegrees = 57.295779513082320876F;
                    const float player_angle =
                        std::remainder(
                            std::atan2(player_dx, player_dz) * kRadiansToDegrees,
                            360.0F);
                    level.geometry.instances[player_instance_index].transform.orientation =
                        torchlight::yaw_rotation(player_angle);
                    renderer->set_instance_angle(player_instance_index, player_angle);
                }
                renderer->set_camera_target(
                    player_motion.position(), kCameraDistance);

                if (!inventory_view.open && active_interaction) {
                    const auto result = interactions.dispatch(*active_interaction, player_motion.position(), player_combat.alive(), 2.25F);
                    if (result != torchlight::InteractionResult::approaching) {
                        player_motion.stop(); active_path.clear(); next_path_node = 0;
                        inventory_view.status = torchlight::interaction_result_message(result);
                        if (result == torchlight::InteractionResult::triggered) ++interaction_count;
                        active_interaction.reset(); drain_logic();
                    }
                }
                if (player_combat.alive() && !inventory_view.open && active_pickup) {
                    const auto* item = entity_world.find(*active_pickup);
                    if (item == nullptr || !item->alive ||
                        item->kind != torchlight::MasterResourceKind::item) {
                        active_pickup.reset();
                    } else {
                        const auto dx = item->position[0] - player_motion.position()[0];
                        const auto dz = item->position[2] - player_motion.position()[2];
                        if (std::hypot(dx, dz) <= 2.25F) {
                            const auto item_id = item->id;
                            player_motion.stop();
                            active_path.clear();
                            next_path_node = 0;
                            const auto inventory_id = session.pick_up(entity_world, item_id, logic_runtime);
                            if (inventory_id != 0) {
                                ++pickup_count;
                                inventory_view.status = "PICKED UP ITEM #" + std::to_string(inventory_id) + ". PRESS I TO EQUIP.";
                                const auto instance = runtime_instance_indices.find(item_id);
                                if (instance != runtime_instance_indices.end()) {
                                    level.geometry.instances[instance->second].visible = false;
                                    renderer->set_instance_visible(instance->second, false);
                                }
                                std::cout << "picked_up=" << item_id << " inventory_id=" << inventory_id
                                          << " bag_count=" << session.inventory().items().size() << '\n';
                            } else inventory_view.status = "CANNOT PICK UP: NOT SUPPORTED EQUIPMENT OR PLAYER DEAD.";
                            active_pickup.reset();
                            drain_logic();
                        }
                    }
                }
                if (!pending_warp && !inventory_view.open && player_combat.alive()) {
                    std::optional<std::array<float, 3>> combat_target_position;
                    if (const auto* target = combat.target(entity_world)) {
                        combat_target_position = target->position;
                    }
                    const auto update = player_combat.alive() ? combat.update(
                        simulation_elapsed, player_motion.position(), entity_world) : torchlight::CombatUpdate{};
                    if (update.state == torchlight::CombatState::unavailable)
                        inventory_view.status = "ATTACK UNAVAILABLE: " + combat.last_attack_issue();
                    if (update.state == torchlight::CombatState::waiting ||
                        update.state == torchlight::CombatState::attacking) {
                        player_motion.stop();
                        active_path.clear();
                        next_path_node = 0;
                    }
                    if (update.state == torchlight::CombatState::attacking) {
                        player_attack_animation_active = true;
                        player_pose_attack_clip = combat.action().clip();
                        if (player_animation_state == PlayerAnimationState::attack)
                            player_animation_time = 0.0F;
                        if (!combat.last_attack_issue().empty())
                            inventory_view.status = combat.last_attack_issue();
                    }
                    if (combat_target_position &&
                        update.state != torchlight::CombatState::approaching &&
                        update.state != torchlight::CombatState::idle) {
                        const float target_dx =
                            (*combat_target_position)[0] - player_motion.position()[0];
                        const float target_dz =
                            (*combat_target_position)[2] - player_motion.position()[2];
                        if (std::hypot(target_dx, target_dz) > 0.00001F) {
                            constexpr float kRadiansToDegrees = 57.295779513082320876F;
                            const float player_angle = std::remainder(
                                std::atan2(target_dx, target_dz) * kRadiansToDegrees,
                                360.0F);
                            level.geometry.instances[player_instance_index].transform.orientation =
                                torchlight::yaw_rotation(player_angle);
                            renderer->set_instance_angle(player_instance_index, player_angle);
                        }
                    }
                    const auto enemy_updates = enemies.update(
                        simulation_elapsed, player_motion.position(),
                        player_combat, entity_world, &level.navigation);
                    for (const auto& enemy_update : enemy_updates) {
                        // Report unresolved resource inputs once per changed reason, not every frame.
                        const auto& issue = enemies.last_attack_issue(enemy_update.entity_id);
                        auto& reported = reported_attack_issues[enemy_update.entity_id];
                        if (issue != reported) {
                            if (!issue.empty())
                                std::cerr << "enemy_attack_issue=" << enemy_update.entity_id
                                          << " reason=" << issue << '\n';
                            reported = issue;
                        }
                        auto& playback =
                            enemy_animation_playback[enemy_update.entity_id];
                        const auto change_enemy_animation = [&](EnemyAnimationState state) {
                            if (playback.state != state) {
                                playback.state = state;
                                playback.time = 0.0F;
                            }
                        };
                        if (enemy_update.state == torchlight::EnemyAiState::chasing &&
                            enemy_update.position_changed) {
                            if (playback.state != EnemyAnimationState::hit &&
                                playback.state != EnemyAnimationState::death) {
                                change_enemy_animation(EnemyAnimationState::run);
                            }
                            ++enemy_chase_count;
                            const auto instance = runtime_instance_indices.find(
                                enemy_update.entity_id);
                            const auto* enemy = entity_world.find(enemy_update.entity_id);
                            if (instance != runtime_instance_indices.end() && enemy != nullptr) {
                                face_instance_toward(instance->second, enemy->position);
                                level.geometry.instances[instance->second].transform.position =
                                    enemy->position;
                                renderer->set_instance_position(
                                    instance->second, enemy->position);
                            }
                        }
                        if (enemy_update.state == torchlight::EnemyAiState::attacking) {
                            if (playback.state != EnemyAnimationState::death) {
                                playback.state = EnemyAnimationState::attack;
                                playback.time = 0.0F;
                            }
                            const auto instance = runtime_instance_indices.find(enemy_update.entity_id);
                            if (instance != runtime_instance_indices.end())
                                face_instance_toward(instance->second, player_motion.position());
                            const auto* action = enemies.action(enemy_update.entity_id);
                            std::cout << "enemy_attack_start=" << enemy_update.entity_id
                                      << " clip=" << action->clip()->skeleton_path
                                      << " speed=" << action->playback().playback_speed() << '\n';
                        } else if (enemy_update.state == torchlight::EnemyAiState::idle &&
                                   playback.state != EnemyAnimationState::hit &&
                                   playback.state != EnemyAnimationState::death) {
                            change_enemy_animation(EnemyAnimationState::idle);
                        } else if (enemy_update.state == torchlight::EnemyAiState::waiting &&
                                   playback.state != EnemyAnimationState::attack &&
                                   playback.state != EnemyAnimationState::hit &&
                                   playback.state != EnemyAnimationState::death) {
                            change_enemy_animation(EnemyAnimationState::idle);
                        }

                    }
                    logic_runtime.update(simulation_elapsed);
                    logic_runtime.update_player_position(player_motion.position());
                    drain_logic();
                }
                const float animation_elapsed = simulation_elapsed;
                if (!player_combat.alive()) { combat.clear_target(); combat.interrupt_attack(); }
                combat.advance_animation(animation_elapsed);
                enemies.advance_animations(animation_elapsed, entity_world, player_combat);
                player_attack_animation_active = combat.attack_in_progress();
                for (auto& [entity_id, playback] : enemy_animation_playback) {
                    const auto* action = enemies.action(entity_id);
                    if (action && action->active()) {
                        playback.state = EnemyAnimationState::attack;
                        playback.time = action->playback().time_seconds();
                        continue; // Losing sight does not replace the pose of a running action.
                    }
                    if (playback.state == EnemyAnimationState::attack) {
                        playback.state = EnemyAnimationState::idle;
                        playback.time = 0.0F;
                    }
                    playback.time += animation_elapsed;
                    if (playback.state != EnemyAnimationState::attack &&
                        playback.state != EnemyAnimationState::hit &&
                        playback.state != EnemyAnimationState::death) {
                        continue;
                    }
                    const auto instance = runtime_instance_indices.find(entity_id);
                    if (instance == runtime_instance_indices.end()) {
                        continue;
                    }
                    const auto mesh_index =
                        level.geometry.instances[instance->second].mesh_index;
                    const torchlight::SceneMeshAnimation* one_shot = nullptr;
                    if (playback.state == EnemyAnimationState::hit) {
                        one_shot = animation_for_mesh(scene_hit_animations, mesh_index);
                    } else {
                        one_shot = animation_for_mesh(
                            scene_death_animations, mesh_index);
                    }
                    if (one_shot == nullptr || playback.time >= one_shot->duration) {
                        if (playback.state == EnemyAnimationState::death) {
                            playback.state = EnemyAnimationState::hidden;
                            level.geometry.instances[instance->second].visible = false;
                            renderer->set_instance_visible(instance->second, false);
                            continue;
                        }
                        playback.state = EnemyAnimationState::idle;
                        playback.time = 0.0F;
                    }
                }
                scene_animation_time += animation_elapsed;
                for (const auto& animation : scene_idle_animations) {
                    renderer->set_mesh_pose(torchlight::sample_scene_mesh_animation(
                        level.geometry, animation, scene_animation_time));
                }
                scene_animation_updates += scene_idle_animations.size();
                for (const auto& [entity_id, playback] : enemy_animation_playback) {
                    const auto instance = runtime_instance_indices.find(entity_id);
                    const auto* entity = entity_world.find(entity_id);
                    if (instance == runtime_instance_indices.end() ||
                        entity == nullptr ||
                        playback.state == EnemyAnimationState::hidden ||
                        (playback.state != EnemyAnimationState::death &&
                         (!entity->alive || !entity->combat_targetable))) {
                        continue;
                    }
                    const auto mesh_index =
                        level.geometry.instances[instance->second].mesh_index;
                    const torchlight::SceneMeshAnimation* animation = nullptr;
                    if (playback.state == EnemyAnimationState::run) {
                        animation = animation_for_mesh(scene_run_animations, mesh_index);
                    } else if (playback.state == EnemyAnimationState::attack) {
                        const auto* action = enemies.action(entity_id);
                        if (action && action->clip() && action->clip()->bind_skeleton) {
                            renderer->set_instance_pose(instance->second,
                                torchlight::sample_ogre_mesh_animation(
                                    level.geometry.meshes[mesh_index].mesh, *action->clip()->bind_skeleton,
                                    action->clip()->animation_skeleton, action->clip()->animation_name,
                                    action->playback().time_seconds(), torchlight::AnimationPlaybackMode::clamp));
                            ++enemy_animation_updates;
                            continue;
                        }
                    } else if (playback.state == EnemyAnimationState::hit) {
                        animation = animation_for_mesh(scene_hit_animations, mesh_index);
                    } else if (playback.state == EnemyAnimationState::death) {
                        animation = animation_for_mesh(scene_death_animations, mesh_index);
                    }
                    if (animation == nullptr) {
                        animation = animation_for_mesh(scene_idle_animations, mesh_index);
                    }
                    if (animation != nullptr) {
                        renderer->set_instance_pose(
                            instance->second,
                            torchlight::sample_scene_mesh_animation(
                                level.geometry, *animation, playback.time));
                        ++enemy_animation_updates;
                    }
                }
                const auto next_animation_state = !player_combat.alive()
                                                      ? PlayerAnimationState::death
                                                      : player_attack_animation_active
                                                      ? PlayerAnimationState::attack
                                                      : player_motion.moving()
                                                            ? PlayerAnimationState::run
                                                            : PlayerAnimationState::idle;
                if (next_animation_state != player_animation_state) {
                    player_transition_from_state = player_animation_state;
                    player_transition_from_time = player_animation_time;
                    player_transition_attack_clip = player_previous_pose_clip;
                    player_transition_attack_speed = player_previous_attack_speed;
                    player_transition_time = 0.0F;
                    player_transition_active = next_animation_state != PlayerAnimationState::death;
                    player_animation_time = 0.0F;
                    player_animation_state = next_animation_state;
                }
                if (!inventory_view.open && player_animation_state == PlayerAnimationState::attack &&
                    player_attack_animation_active) {
                    player_animation_time = combat.action().playback().time_seconds();
                } else {
                    player_animation_time += player_animation_state == PlayerAnimationState::death ?
                        std::min(elapsed, 0.1F) : animation_elapsed;
                }
                const auto animation_skeleton = [&](PlayerAnimationState state, bool previous = false)
                    -> const torchlight::OgreSkeleton& {
                    if (state == PlayerAnimationState::attack) {
                        const auto& clip = previous ? player_transition_attack_clip : player_pose_attack_clip;
                        if (clip) return clip->animation_skeleton;
                    }
                    if (state == PlayerAnimationState::death && player_animations.death)
                        return player_animations.death->animation_skeleton;
                    if (state == PlayerAnimationState::run) {
                        return player_animations.run;
                    }
                    return player_animations.idle;
                };
                const auto animation_name = [&](PlayerAnimationState state, bool previous = false)
                    -> const std::string& {
                    if (state == PlayerAnimationState::attack) {
                        const auto& clip = previous ? player_transition_attack_clip : player_pose_attack_clip;
                        if (clip) return clip->animation_name;
                    }
                    if (state == PlayerAnimationState::death && player_animations.death)
                        return player_animations.death->animation_name;
                    if (state == PlayerAnimationState::run) {
                        return player_animations.run_name;
                    }
                    return player_animations.idle_name;
                };
                const auto animation_playback_mode = [](PlayerAnimationState state) {
                    return state == PlayerAnimationState::attack || state == PlayerAnimationState::death
                               ? torchlight::AnimationPlaybackMode::clamp
                               : torchlight::AnimationPlaybackMode::loop;
                };
                torchlight::OgreMeshPose player_pose;
                if (player_transition_active) {
                    constexpr float kPlayerTransitionDuration = 0.2F;
                    player_transition_time += animation_elapsed;
                    player_transition_from_time += animation_elapsed *
                        (player_transition_from_state == PlayerAnimationState::attack ? player_transition_attack_speed : 1.0F);
                    const float linear_amount = std::min(
                        1.0F, player_transition_time / kPlayerTransitionDuration);
                    player_pose = torchlight::sample_ogre_mesh_animation_blend(
                        level.geometry.meshes[player_mesh_index].mesh,
                        player_animations.bind,
                        animation_skeleton(player_transition_from_state, true),
                        animation_name(player_transition_from_state, true),
                        player_transition_from_time, 1.0F - linear_amount,
                        animation_skeleton(player_animation_state),
                        animation_name(player_animation_state), player_animation_time,
                        linear_amount,
                        animation_playback_mode(player_transition_from_state),
                        animation_playback_mode(player_animation_state));
                    if (linear_amount >= 1.0F) {
                        player_transition_active = false;
                    }
                } else {
                    player_pose = torchlight::sample_ogre_mesh_animation(
                        level.geometry.meshes[player_mesh_index].mesh,
                        player_animations.bind,
                        animation_skeleton(player_animation_state),
                        animation_name(player_animation_state), player_animation_time,
                        animation_playback_mode(player_animation_state));
                }
                renderer->set_mesh_pose(player_pose);
                if (player_weapon_instance_index) {
                    const bool left_weapon = session.weapon() && session.weapon()->weapon &&
                        session.weapon()->weapon->prototype.attack_hand == torchlight::AttackHand::left;
                    const auto tag = std::find_if(player_pose.bones.begin(), player_pose.bones.end(),
                        [&](const auto& bone) { return bone.name == (left_weapon ? "tag_lefthand" : "tag_righthand"); });
                    if (tag == player_pose.bones.end()) {
                        throw DesktopError(
                            "player skeleton lacks the selected equipment hand tag");
                    }
                    const auto& body_transform =
                        level.geometry.instances[player_instance_index].transform;
                    torchlight::LayoutWorldTransform weapon_transform;
                    weapon_transform.position = torchlight::transform_point(
                        body_transform.position, body_transform.orientation,
                        body_transform.scale, tag->position);
                    weapon_transform.orientation = torchlight::compose_rotation(
                        body_transform.orientation,
                        torchlight::quaternion_rotation(tag->orientation));
                    for (std::size_t axis = 0; axis < 3; ++axis) {
                        weapon_transform.scale[axis] =
                            body_transform.scale[axis] * tag->scale[axis] *
                            selected_player.weapon_scale;
                    }
                    level.geometry.instances[*player_weapon_instance_index].transform =
                        weapon_transform;
                    renderer->set_instance_transform(
                        *player_weapon_instance_index, weapon_transform);
                }
                player_previous_pose_clip = player_pose_attack_clip;
                player_previous_attack_speed = combat.action().playback().playback_speed();
                // The global enemy-before-player order is retained explicitly;
                // per-character order is advance -> pose -> HIT -> finish.
                if (!inventory_view.open) {
                    for (const auto& entity : entity_world.entities()) {
                        const auto* action = enemies.action(entity.id);
                        if (!action || !action->active()) continue;
                        const auto events = action->playback().frame_events();
                        for (const auto& event : events) {
                            if (event.key.name != "HIT") continue;
                            const auto hit = enemies.perform_attack(entity.id, event,
                                player_motion.position(), player_combat, entity_world);
                            if (hit.state != torchlight::EnemyAiState::attacked &&
                                hit.state != torchlight::EnemyAiState::player_killed) continue;
                            ++enemy_attack_count;
                            std::cout << "enemy_hit=" << entity.id << " damage=" << hit.damage
                                      << " player_health=" << hit.player_health << " clip=" << event.source_clip
                                      << " key=" << event.key_index << '\n';
                            if (hit.state == torchlight::EnemyAiState::player_killed) {
                                ++player_death_count; player_motion.stop(); active_path.clear(); next_path_node = 0;
                                combat.clear_target(); combat.interrupt_attack(); player_attack_animation_active = false;
                                active_interaction.reset(); interactions.cancel(); active_pickup.reset(); inventory_view.open = false;
                                std::cout << "player_killed=1\n";
                                break;
                            }
                        }
                    }
                    enemies.finish_animation_frame();
                }
                bool player_hit_processed = false;
                if (!inventory_view.open && player_animation_state == PlayerAnimationState::attack &&
                    player_attack_animation_active) {
                    for (const auto& event : combat.action().playback().frame_events()) {
                        if (event.key.name != "HIT") {
                            continue;
                        }
                        const auto hit = combat.perform_attack(
                            event, player_motion.position(), entity_world, logic_runtime);
                        if (hit.state != torchlight::CombatState::attacked &&
                            hit.state != torchlight::CombatState::killed) {
                            continue;
                        }
                        auto& playback = enemy_animation_playback[hit.target_id];
                        if (hit.state == torchlight::CombatState::killed) {
                            enemies.interrupt_attack(hit.target_id);
                            playback.state = EnemyAnimationState::death; playback.time = 0.0F;
                        } else {
                            const auto* active_attack = enemies.action(hit.target_id);
                            // Do not invent unconditional stagger: ordinary damage
                            // alone must not replace a still-running attack clip.
                            if (!active_attack || !active_attack->active()) {
                                playback.state = EnemyAnimationState::hit; playback.time = 0.0F;
                            }
                        }
                        ++combat_attack_count;
                        combat_kill_count += static_cast<std::size_t>(
                            hit.state == torchlight::CombatState::killed);
                        player_hit_processed = true;
                        std::cout << "combat_hit=" << hit.target_id
                                  << " damage=" << hit.damage
                                  << " remaining_health=" << hit.remaining_health
                                  << " clip=" << event.source_clip
                                  << " key=" << event.key_index << '\n';
                    }
                    combat.finish_animation_frame();
                    player_attack_animation_active = combat.attack_in_progress();
                }
                if (player_hit_processed) {
                    drain_logic();
                    renderer->set_mesh_pose(player_pose);
                }
                ++player_animation_updates;
                auto overlay = inventory_view.lines(session,
                    static_cast<std::size_t>(std::max(1, window.height() / (window.width() >= 950 ? 22 : 11) - 10)));
                if (!inventory_view.open) {
                    overlay.resize(1);
                    overlay.push_back({inventory_view.status.empty()
                        ? "I INVENTORY | ESC PAUSE / SAVE | CLICK TO MOVE / ATTACK / PICK UP"
                        : inventory_view.status, false});
                }
                if (!player_combat.alive()) {
                    overlay.resize(1);
                    overlay.push_back({"PLAYER DIED - SIMULATION PAUSED", false});
                    overlay.push_back({session.hardcore() ? "HARDCORE: RECOVERY DISABLED. ESC FOR MENU." :
                        "R: RECOVER AT LEVEL ENTRY | ESC: PAUSE / SAVE", true});
                    if (!session.hardcore()) overlay.push_back({"COST " + std::to_string(session.gold() / 10) +
                        " GOLD. INVENTORY AND FLOOR ARE RETAINED.", false});
                }
                window.draw_scene_frame(*renderer, overlay, inventory_view.open || !player_combat.alive());
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
                      << " inventory_items=" << session.inventory().items().size()
                      << " loot_deaths=" << loot_death_count
                      << " loot_items=" << loot_entity_count
                      << " missing_loot_classes=" << missing_loot_class_count
                      << " dungeon=" << narrow_ascii(level.address.dungeon_name)
                      << " depth=" << level.address.depth
                      << " resources=" << index.records().size()
                      << " cached_unit_files=" << loader.cached_definition_count()
                      << " level_pieces=" << levelsets.pieces().size()
                      << " chunks=" << level.chunk_count
                      << " player=" << narrow_ascii(selected_player.name)
                      << " weapon="
                      << (session.weapon()
                              ? narrow_ascii(session.weapon()->name)
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
                      << " shadow_instances=" << render_stats.shadow_instances
                      << " placed_triangles=" << render_stats.placed_triangles
                      << " logic_events=" << logic_event_count
                      << " logic_invocations=" << logic_invocation_count
                      << " spawn_requests=" << spawn_request_count
                      << " spawn_control_requests=" << spawn_control_request_count
                      << " runtime_entities=" << entity_world.entities().size()
                      << " spawned_entities=" << spawned_entity_count
                      << " hidden_spawned_entities=" << hidden_spawned_entity_count
                      << " destroyed_spawned_entities="
                      << destroyed_spawned_entity_count
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
                      << " player_animation_updates=" << player_animation_updates
                      << " idle_animation_meshes=" << scene_idle_animations.size()
                      << " scene_animation_updates=" << scene_animation_updates
                      << " enemy_animation_updates=" << enemy_animation_updates
                      << " warp_requests=" << warp_request_count
                      << " frames=" << level_frames
                      << " total_frames=" << total_frames
                      << " player_position=" << player_motion.position()[0] << ','
                      << player_motion.position()[1] << ',' << player_motion.position()[2]
                      << " navigation_cells=" << level.navigation.walkable_cell_count()
                      << '\n';

            if (return_to_menu) {
                gameplay_active = false; refresh_saves(); continue;
            }
            if (!app_running) {
                if (!direct_preview && !pending_warp && !saved_for_exit) {
                    try { checkpoint_now(); }
                    catch (const std::exception& e) { std::cerr << "exit_checkpoint_failed=" << e.what() << '\n'; }
                }
                break;
            }
            if (!pending_warp) break;
            // Cache departure only at a settled boundary; do not discard floor state.
            torchlight::remember_floor(campaign, capture_floor());
            campaign.player = torchlight::CheckpointAccess::capture(session);
            auto entry = transitions.resolve_entry(*pending_warp);
            const auto target_dungeon = scene_loader.load_dungeon(
                dungeon_data_file(entry.destination.dungeon_name));
            const auto target_floor = torchlight::select_dungeon_floor(
                target_dungeon, entry.destination.depth);
            entry.destination = {target_dungeon.name, target_floor.depth};
            transitions.commit(entry.destination);
            pending_entry = entry;
            ++completed_transitions;
            std::cout << "level_transition=" << completed_transitions
                      << " dungeon=" << narrow_ascii(entry.destination.dungeon_name)
                      << " depth=" << entry.destination.depth
                      << " warp_name=" << narrow_ascii(pending_warp->warp_name)
                      << '\n';
            std::cout.flush();
            } catch (const std::exception& e) {
                if (direct_preview) throw;
                gameplay_active = false; frontend.show_main(); refresh_saves();
                frontend.error(std::string("LEVEL LOAD/RUNTIME FAILED: ") + e.what());
                std::cerr << "frontend_game_error=" << e.what() << '\n';
            }
        }
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "desktop failed: " << error.what() << '\n';
        return 1;
    }
}
