#include "torchlight/input_state.hpp"

namespace torchlight {

void InputState::update_cursor_position(std::int64_t x, std::int64_t y) noexcept {
    cursor_ = {x, y};
}

int InputState::get_cursor_position(Point& point) const noexcept {
    point = cursor_;
    // The inspected Linux shim copies both coordinates and returns zero.
    return 0;
}

int InputState::set_cursor_position(std::int32_t, std::int32_t) noexcept {
    // The original Linux function is a no-op; this is not a cursor setter.
    return 0;
}

bool InputState::update_key_state(std::uint32_t key, bool down) noexcept {
    if (key >= keys_.size()) {
        return false;
    }
    keys_[key] = down ? 1 : 0;
    return true;
}

std::int16_t InputState::get_key_state(std::uint32_t key) const noexcept {
    return key < keys_.size() && keys_[key] != 0 ? std::int16_t{-32768} : std::int16_t{0};
}

std::int16_t InputState::get_async_key_state(std::uint32_t key) const noexcept {
    // The Linux shim has no consumed-edge bit: repeated reads are identical.
    return get_key_state(key);
}

void InputState::clear_key_state() noexcept {
    keys_.fill(0);
    // The original clears exactly 256 bytes of keys, retaining the cursor.
}

} // namespace torchlight
