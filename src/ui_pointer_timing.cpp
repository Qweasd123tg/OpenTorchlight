#include "torchlight/ui_pointer_timing.hpp"

#include <stdexcept>

namespace torchlight {

UiPointerDispatchKind UiPointerDownDecision::dispatch_kind(bool wants_multi_clicks) const noexcept {
    if (wants_multi_clicks && click_count == 2) return UiPointerDispatchKind::double_click;
    if (wants_multi_clicks && click_count == 3) return UiPointerDispatchKind::triple_click;
    return UiPointerDispatchKind::button_down;
}

void UiPointerTiming::set_single_click_timeout(double seconds) noexcept {
    single_click_timeout_ = seconds;
}

void UiPointerTiming::set_multi_click_timeout(double seconds) noexcept {
    multi_click_timeout_ = seconds;
}

void UiPointerTiming::set_multi_click_area(float width, float height) noexcept {
    multi_click_width_ = width;
    multi_click_height_ = height;
}

std::size_t UiPointerTiming::checked_button(std::uint8_t button) {
    if (button >= 5) throw std::out_of_range("CEGUI mouse button is outside [0, 5)");
    return button;
}

bool UiPointerTiming::contains(const ClickTracker& tracker, float x, float y) noexcept {
    return x >= tracker.left && x < tracker.right &&
           y >= tracker.top && y < tracker.bottom;
}

UiPointerDownDecision UiPointerTiming::button_down(
    std::uint8_t button, float x, float y, double time_seconds,
    std::optional<std::size_t> target) {
    auto& tracker = trackers_[checked_button(button)];
    ++tracker.count;

    bool reset = false;
    if (multi_click_timeout_ > 0.0 && time_seconds - tracker.last_down_time > multi_click_timeout_)
        reset = true;
    else if (!contains(tracker, x, y) || tracker.target != target || tracker.count > 3)
        reset = true;

    if (reset) {
        tracker.count = 1;
        tracker.left = x;
        tracker.top = y;
        tracker.right = x + multi_click_width_;
        tracker.bottom = y + multi_click_height_;
        tracker.target = target;
    }

    // System::injectMouseButtonDown samples currentTime after dispatch. The
    // host timestamp represents this physical injection point for the port.
    tracker.last_down_time = time_seconds;
    return {tracker.count};
}

UiPointerUpDecision UiPointerTiming::button_up(
    std::uint8_t button, float x, float y, double time_seconds,
    std::optional<std::size_t> target) const {
    const auto& tracker = trackers_[checked_button(button)];
    bool eligible = true;
    if (single_click_timeout_ != 0.0 &&
        time_seconds - tracker.last_down_time > single_click_timeout_)
        eligible = false;
    if (!contains(tracker, x, y) || tracker.target != target) eligible = false;
    return {tracker.count, eligible};
}

void UiAutoRepeatTiming::set_enabled(bool enabled) noexcept {
    if (enabled_ == enabled) return;
    enabled_ = enabled;
    repeat_button_ = no_button;
}

void UiAutoRepeatTiming::set_delay(float seconds) noexcept {
    delay_ = seconds;
}

void UiAutoRepeatTiming::set_rate(float seconds) noexcept {
    rate_ = seconds;
}

bool UiAutoRepeatTiming::wants_capture_on_down() const noexcept {
    return enabled_ && repeat_button_ == no_button;
}

void UiAutoRepeatTiming::button_down(std::uint8_t button, bool capture_is_self) noexcept {
    if (!enabled_) return;
    if (repeat_button_ != button && capture_is_self) {
        repeat_button_ = button;
        elapsed_ = 0.0F;
        repeating_ = false;
    }
}

bool UiAutoRepeatTiming::button_up() noexcept {
    if (!enabled_ || repeat_button_ == no_button) return false;
    repeat_button_ = no_button;
    return true;
}

void UiAutoRepeatTiming::capture_lost() noexcept {
    repeat_button_ = no_button;
}

std::optional<std::uint8_t> UiAutoRepeatTiming::advance(float seconds) noexcept {
    if (!enabled_ || repeat_button_ == no_button) return std::nullopt;
    elapsed_ += seconds;
    if (repeating_) {
        if (!(elapsed_ > rate_)) return std::nullopt;
        elapsed_ -= rate_;
        return repeat_button_;
    }
    if (!(elapsed_ > delay_)) return std::nullopt;
    elapsed_ = 0.0F;
    repeating_ = true;
    return repeat_button_;
}

} // namespace torchlight
