#include "torchlight/mouse_manager.hpp"

#include <cmath>
#include <limits>

namespace torchlight {
namespace {
std::int32_t truncate_original_coordinate(float value) noexcept {
    // Original cvttss2si returns INT32_MIN on NaN, infinity and overflow.
    // Check before converting so the portable implementation has no float-cast UB.
    if (!std::isfinite(value) || value < -2147483648.0f || value >= 2147483648.0f) {
        return std::numeric_limits<std::int32_t>::min();
    }
    return static_cast<std::int32_t>(value);
}
} // namespace

void MouseManager::mouse_event(std::uint32_t message, std::uint32_t parameter) noexcept {
    if (message == 0x20a) {
        const auto high = static_cast<std::int32_t>(parameter >> 16);
        const auto delta = high >= 0x8000 ? high - 0x10000 : high;
        pending_wheel_ += static_cast<std::uint32_t>(delta);
        return;
    }
    if (message < 0x201 || message > 0x208) {
        return; // The original also ignores the middle-double-click message 0x209.
    }
    const auto button = (message - 0x201) / 3;
    switch ((message - 0x201) % 3) {
    case 0:
        if (!pending_held_[button]) {
            pending_pressed_[button] = 1;
        }
        pending_held_[button] = 1;
        break;
    case 1:
        pending_held_[button] = 0;
        break;
    case 2:
        pending_double_click_[button] = 1;
        break;
    }
}

void MouseManager::capture() noexcept {
    held_ = pending_held_;
    pressed_ = pending_pressed_;
    double_click_ = pending_double_click_;
    wheel_ = pending_wheel_;
    flush();
}

void MouseManager::flush() noexcept {
    pending_wheel_ = 0;
    pending_pressed_.fill(0);
    pending_double_click_.fill(0);
}

void MouseManager::flush_all() noexcept {
    pending_held_.fill(0);
    flush();
}

void MouseManager::update(const InputState& input) noexcept {
    (void)input.get_cursor_position(position_);
}

const Point& MouseManager::virtual_mouse_position(float source_width, float source_height,
                                                 float target_width, float target_height) noexcept {
    const float x = static_cast<float>(position_.x) * (target_width / source_width);
    const float y = static_cast<float>(position_.y) * (target_height / source_height);
    virtual_position_ = {truncate_original_coordinate(x), truncate_original_coordinate(y)};
    return virtual_position_;
}

bool MouseManager::button_pressed(MouseButton button) const noexcept {
    const auto index = static_cast<std::uint32_t>(button);
    return index < pressed_.size() && pressed_[index] == 1;
}

bool MouseManager::button_held(MouseButton button) const noexcept {
    const auto index = static_cast<std::uint32_t>(button);
    return index < held_.size() && (held_[index] == 1 || pressed_[index] == 1);
}

bool MouseManager::button_double_click(MouseButton button) const noexcept {
    const auto index = static_cast<std::uint32_t>(button);
    return index < double_click_.size() && double_click_[index] == 1;
}

std::int32_t MouseManager::wheel_delta() const noexcept {
    if (wheel_ <= 0x7fffffffU) {
        return static_cast<std::int32_t>(wheel_);
    }
    return -1 - static_cast<std::int32_t>(0xffffffffU - wheel_);
}

} // namespace torchlight
