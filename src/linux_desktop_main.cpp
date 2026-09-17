#include "torchlight/application.hpp"
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
#include "torchlight/settings.hpp"
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
#include <pointer-constraints-unstable-v1-client-protocol.h>

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


class DesktopError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

using Options = torchlight::ApplicationOptions;

Options parse_options(int argc, char** argv) {
    if (argc < 2) {
        throw DesktopError(
            "usage: torchlight_desktop /path/to/Torchlight/game "
            "[--save-dir PATH] [--settings-dir PATH] [--debug-ui 0|1] [--frames N] [--main-stratum N --seed N]");
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
        } else if (name == "--settings-dir") {
            if (value.empty()) throw DesktopError("empty settings directory");
            options.settings_directory = value;
        } else if (name == "--debug-ui") {
            if (value != "0" && value != "1")
                throw DesktopError("--debug-ui must be 0 or 1");
            options.debug_ui = value == "1";
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

class DesktopWindow : public torchlight::ApplicationHost {
public:
    DesktopWindow(torchlight::DisplaySettings display_settings)
        : display_settings_(display_settings),
          width_(display_settings.res_width),
          height_(display_settings.res_height) {
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
        confined_listener_.confined = confined_confined;
        confined_listener_.unconfined = confined_unconfined;
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
        // Port policy, not original fullscreen: the original starts fullscreen
        // from settings (FULLSCREEN:1 observed). Ours stays windowed unless the
        // settings file asks, so no one is trapped without a settings menu.
        if (display_settings_.fullscreen)
            xdg_toplevel_set_fullscreen(toplevel_, nullptr);
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
        eglSwapInterval(egl_display_, display_settings_.vsync ? 1 : 0);
        maybe_confine();
        if (constraints_ == nullptr) {
            std::cerr << "desktop notice: compositor lacks pointer-constraints, "
                         "the mouse stays unconfined (original grabs it)\n";
        }
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
        if (confined_ != nullptr) {
            zwp_confined_pointer_v1_destroy(confined_);
        }
        if (constraints_ != nullptr) {
            zwp_pointer_constraints_v1_destroy(constraints_);
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

    double clock_seconds() override {
        return std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }
    std::uint32_t new_campaign_seed() override {
        std::random_device entropy;
        std::uint32_t seed = 0;
        do { seed = entropy(); } while (seed == 0);
        return seed;
    }

    bool process_events() override {
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

    std::optional<torchlight::UiPointerClick> take_ui_click() override {
        auto click = ui_click_; ui_click_.reset(); return click;
    }
    torchlight::UiPointerState ui_pointer_state() const noexcept override {
        torchlight::UiPointerState state;
        if (pointer_inside_) state.position = std::array<float, 2>{
            static_cast<float>(pointer_x_), static_cast<float>(pointer_y_)};
        state.left_press_origin = ui_press_origin_;
        return state;
    }
    [[nodiscard]] int width() const noexcept { return width_; }
    [[nodiscard]] int height() const noexcept { return height_; }

    [[nodiscard]] std::vector<std::uint32_t> take_key_presses() {
        auto keys = std::move(key_presses_);
        key_presses_.clear();
        return keys;
    }

    void draw_scene_frame(torchlight::GlesSceneRenderer& renderer,
                          torchlight::GlesUiRenderer& ui_renderer,
                          const std::vector<torchlight::InventoryViewLine>& lines,
                          bool inventory_open, const torchlight::UiHudFrame& hud) {
        renderer.draw(width_, height_);
        ui_renderer.draw_hud(hud, width_, height_);
        ui_renderer.draw_overlay(lines, inventory_open, width_, height_);
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
        } else if (interface_name == zwp_pointer_constraints_v1_interface.name) {
            self.constraints_ = static_cast<zwp_pointer_constraints_v1*>(wl_registry_bind(
                registry, name, &zwp_pointer_constraints_v1_interface, 1));
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
    // original-code: the SDL2 original grabs the mouse at window creation
    // (SDL_SetWindowGrab(1)); on Wayland that is pointer confinement to our
    // surface with persistent lifetime. The compositor still releases it while
    // the surface is inactive. Without the protocol we stay unconfined.
    void maybe_confine() {
        if (confined_ != nullptr || constraints_ == nullptr || pointer_ == nullptr ||
            surface_ == nullptr) {
            return;
        }
        confined_ = zwp_pointer_constraints_v1_confine_pointer(
            constraints_, surface_, pointer_, nullptr,
            ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
        if (confined_ != nullptr) {
            zwp_confined_pointer_v1_add_listener(confined_, &confined_listener_, this);
        }
    }
    static void confined_confined(void* data, zwp_confined_pointer_v1*) {
        static_cast<DesktopWindow*>(data)->confined_active_ = true;
    }
    static void confined_unconfined(void* data, zwp_confined_pointer_v1*) {
        static_cast<DesktopWindow*>(data)->confined_active_ = false;
    }
    static void seat_capabilities(void* data, wl_seat* seat, std::uint32_t capabilities) {
        auto& self = *static_cast<DesktopWindow*>(data);
        if ((capabilities & WL_SEAT_CAPABILITY_POINTER) != 0 && self.pointer_ == nullptr) {
            self.pointer_ = wl_seat_get_pointer(seat);
            wl_pointer_add_listener(self.pointer_, &self.pointer_listener_, &self);
            self.maybe_confine();
        }
        if ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) != 0 && self.keyboard_ == nullptr) {
            self.keyboard_ = wl_seat_get_keyboard(seat);
            wl_keyboard_add_listener(self.keyboard_, &self.keyboard_listener_, &self);
        }
    }
    static void seat_name(void*, wl_seat*, const char*) {}
    static void pointer_enter(void* data, wl_pointer*, std::uint32_t, wl_surface*, wl_fixed_t x,
                              wl_fixed_t y) {
        static_cast<DesktopWindow*>(data)->pointer_inside_ = true;
        pointer_motion(data, nullptr, 0, x, y);
    }
    static void pointer_leave(void* data, wl_pointer*, std::uint32_t, wl_surface*) {
        auto &self = *static_cast<DesktopWindow*>(data);
        self.pointer_inside_ = false;
        self.ui_press_origin_.reset(); self.ui_click_.reset();
    }
    static void pointer_motion(void* data, wl_pointer*, std::uint32_t, wl_fixed_t x,
                               wl_fixed_t y) {
        auto& self = *static_cast<DesktopWindow*>(data);
        self.pointer_x_ = wl_fixed_to_int(x);
        self.pointer_y_ = wl_fixed_to_int(y);
    }
    static void pointer_button(void* data, wl_pointer*, std::uint32_t, std::uint32_t,
                               std::uint32_t button, std::uint32_t state) {
        auto& self = *static_cast<DesktopWindow*>(data);
        if (button != BTN_LEFT) return;
        if (state == WL_POINTER_BUTTON_STATE_PRESSED) {
            self.left_click_ = {self.pointer_x_, self.pointer_y_};
            self.ui_press_origin_ = std::array<float, 2>{
                static_cast<float>(self.pointer_x_), static_cast<float>(self.pointer_y_)};
        } else if (state == WL_POINTER_BUTTON_STATE_RELEASED) {
            if (self.pointer_inside_ && self.ui_press_origin_)
                self.ui_click_ = torchlight::UiPointerClick{*self.ui_press_origin_,
                    {static_cast<float>(self.pointer_x_), static_cast<float>(self.pointer_y_)}};
            self.ui_press_origin_.reset();
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
    torchlight::DisplaySettings display_settings_{};
    zwp_pointer_constraints_v1* constraints_ = nullptr;
    zwp_confined_pointer_v1* confined_ = nullptr;
    bool confined_active_ = false;
    wl_egl_window* native_window_ = nullptr;
    wl_registry_listener registry_listener_{};
    xdg_wm_base_listener wm_base_listener_{};
    xdg_surface_listener xdg_surface_listener_{};
    xdg_toplevel_listener toplevel_listener_{};
    wl_seat_listener seat_listener_{};
    wl_pointer_listener pointer_listener_{};
    wl_keyboard_listener keyboard_listener_{};
    zwp_confined_pointer_v1_listener confined_listener_{};
    EGLDisplay egl_display_ = EGL_NO_DISPLAY;
    EGLConfig configuration_ = nullptr;
    EGLSurface egl_surface_ = EGL_NO_SURFACE;
    EGLContext egl_context_ = EGL_NO_CONTEXT;
    int width_ = 1280;
    int height_ = 720;
    int pointer_x_ = 0;
    int pointer_y_ = 0;
    bool pointer_inside_ = false;
    std::optional<std::array<float, 2>> ui_press_origin_;
    std::optional<torchlight::UiPointerClick> ui_click_;
    bool configured_ = false;
    bool running_ = true;
    std::optional<std::array<int, 2>> left_click_;
    std::vector<std::uint32_t> key_presses_;
};

} // namespace

int main(int argc, char** argv) {
    try {
        auto options = parse_options(argc, argv);
        const auto settings_dir =
            options.settings_directory ? *options.settings_directory
                                       : torchlight::settings_directory();
        torchlight::DisplaySettings display;
        try {
            display = torchlight::load_display_settings(settings_dir);
        } catch (const std::exception& error) {
            std::cerr << "desktop notice: settings unreadable (" << error.what()
                      << "), using portable defaults\n";
        }
        DesktopWindow window(display);
        options.music_enabled = true;
        options.music_directory = options.game_directory / "music";
        options.music_volume = display.music_volume;
        options.music_mute = display.music_mute;
        options.settings = display;
        return torchlight::run_application(options, window);
    } catch (const std::exception& error) {
        std::cerr << "desktop failed: " << error.what() << '\n';
        return 1;
    }
}
