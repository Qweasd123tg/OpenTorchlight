#include "torchlight/input_state.hpp"
#include "torchlight/key_manager.hpp"
#include "torchlight/mouse_manager.hpp"

// Only the comparison test uses this C ABI. The core has no global state.
namespace {
torchlight::InputState state;
torchlight::KeyManager frames;
torchlight::MouseManager mouse;
}

extern "C" {

void recovered_update_cursor(std::int64_t x, std::int64_t y) {
    state.update_cursor_position(x, y);
}

int recovered_get_cursor(torchlight::Point* point) {
    return state.get_cursor_position(*point);
}

int recovered_set_cursor(std::int32_t x, std::int32_t y) {
    return state.set_cursor_position(x, y);
}

bool recovered_update_key(std::uint32_t key, bool down) {
    return state.update_key_state(key, down);
}

std::int16_t recovered_get_key(std::uint32_t key) {
    return state.get_key_state(key);
}

std::int16_t recovered_get_async_key(std::uint32_t key) {
    return state.get_async_key_state(key);
}

void recovered_clear_keys() {
    state.clear_key_state();
}

void recovered_frame_event(std::uint32_t message, std::uint32_t key, bool caps_key_down) {
    frames.key_event(message, key, caps_key_down);
}

void recovered_frame_capture() { frames.capture(); }
void recovered_frame_flush() { frames.flush(); }
void recovered_frame_flush_all() { frames.flush_all(); }
bool recovered_frame_pressed(std::uint32_t key) { return frames.key_pressed(key); }
bool recovered_frame_held(std::uint32_t key) { return frames.key_held(key); }
bool recovered_frame_released(std::uint32_t key) { return frames.key_released(key); }
bool recovered_frame_caps() { return frames.caps_key_down(); }

void recovered_mouse_event(std::uint32_t message, std::uint32_t parameter) {
    mouse.mouse_event(message, parameter);
}
void recovered_mouse_capture() { mouse.capture(); }
void recovered_mouse_flush() { mouse.flush(); }
void recovered_mouse_flush_all() { mouse.flush_all(); }
bool recovered_mouse_pressed(std::uint32_t button) {
    return mouse.button_pressed(static_cast<torchlight::MouseButton>(button));
}
bool recovered_mouse_held(std::uint32_t button) {
    return mouse.button_held(static_cast<torchlight::MouseButton>(button));
}
bool recovered_mouse_double(std::uint32_t button) {
    return mouse.button_double_click(static_cast<torchlight::MouseButton>(button));
}
std::int32_t recovered_mouse_wheel() { return mouse.wheel_delta(); }
void recovered_mouse_update(void*) { mouse.update(state); }
void recovered_mouse_position(torchlight::Point* point) { *point = mouse.position(); }
const torchlight::Point* recovered_mouse_virtual(float sw, float sh, float tw, float th) {
    return &mouse.virtual_mouse_position(sw, sh, tw, th);
}

}
