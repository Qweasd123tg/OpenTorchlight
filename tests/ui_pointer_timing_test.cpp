#include "torchlight/ui_pointer_timing.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

void require_near(float actual, float expected, const char* message) {
    if (std::fabs(actual - expected) > 0.00001F) throw std::runtime_error(message);
}

void click_tracker_boundaries() {
    torchlight::UiPointerTiming timing;
    const auto first = timing.button_down(0, 10.0F, 20.0F, 0.0, 41);
    require(first.click_count == 1, "first press was not a single click");
    require(first.dispatch_kind(true) == torchlight::UiPointerDispatchKind::button_down,
            "first press changed dispatch kind");

    // Equality is accepted by both timeout and the inclusive lower bounds.
    const auto second = timing.button_down(0, 10.0F, 20.0F,
        torchlight::UiPointerTiming::default_multi_click_timeout, 41);
    require(second.click_count == 2, "multi-click timeout equality reset the sequence");
    require(second.dispatch_kind(true) == torchlight::UiPointerDispatchKind::double_click,
            "second wanted press was not double-click");
    require(second.dispatch_kind(false) == torchlight::UiPointerDispatchKind::button_down,
            "unwanted multi-click suppressed ordinary down");

    const auto third = timing.button_down(0, 21.999F, 31.999F, 0.50, 41);
    require(third.click_count == 3 &&
            third.dispatch_kind(true) == torchlight::UiPointerDispatchKind::triple_click,
            "point inside half-open tolerance did not complete triple-click");

    // A fourth valid press starts a new sequence; CEGUI never emits a fourth-click event.
    const auto fourth = timing.button_down(0, 10.0F, 20.0F, 0.60, 41);
    require(fourth.click_count == 1, "fourth press did not wrap to one");

    const auto right_edge = timing.button_down(0, 22.0F, 20.0F, 0.70, 41);
    require(right_edge.click_count == 1, "exclusive right edge remained in tolerance area");
    const auto wrong_target = timing.button_down(0, 22.0F, 20.0F, 0.80, 42);
    require(wrong_target.click_count == 1, "target identity did not reset sequence");
    const auto too_late = timing.button_down(0, 22.0F, 20.0F, 1.131, 42);
    require(too_late.click_count == 1, "strictly expired multi-click remained grouped");
}

void independent_buttons_and_disabled_timeout() {
    torchlight::UiPointerTiming timing;
    static_cast<void>(timing.button_down(0, 1, 1, 5.0, 7));
    static_cast<void>(timing.button_down(1, 1, 1, 5.1, 7));
    require(timing.button_down(0, 1, 1, 5.2, 7).click_count == 2,
            "right-button activity corrupted left tracker");
    require(timing.button_down(1, 1, 1, 5.3, 7).click_count == 2,
            "left-button activity corrupted right tracker");

    timing.set_multi_click_timeout(0.0);
    require(timing.button_down(2, 4, 4, 10.0, 9).click_count == 1,
            "first timeout-disabled press invalid");
    require(timing.button_down(2, 4, 4, 1000.0, 9).click_count == 2,
            "zero multi-click timeout did not disable only the time check");
    require(timing.button_down(2, 16, 4, 1001.0, 9).click_count == 1,
            "zero timeout incorrectly disabled area reset");

    bool threw = false;
    try { static_cast<void>(timing.button_down(5, 0, 0, 0, {})); }
    catch (const std::out_of_range&) { threw = true; }
    require(threw, "out-of-range button silently aliased a tracker");
}

void release_click_eligibility() {
    torchlight::UiPointerTiming timing;
    static_cast<void>(timing.button_down(0, 100, 50, 0.0, 3));
    auto up = timing.button_up(0, 111.999F, 61.999F,
        torchlight::UiPointerTiming::default_single_click_timeout, 3);
    require(up.click_eligible && up.click_count == 1,
            "single-click timeout equality or interior point was rejected");
    require(!timing.button_up(0, 112.0F, 50, 0.1, 3).click_eligible,
            "release accepted exclusive tolerance edge");
    require(!timing.button_up(0, 100, 50, 0.20001, 3).click_eligible,
            "release after single-click timeout remained eligible");
    require(!timing.button_up(0, 100, 50, 0.1, 4).click_eligible,
            "release on a different target remained eligible");

    timing.set_single_click_timeout(0.0);
    require(timing.button_up(0, 100, 50, 10000.0, 3).click_eligible,
            "zero single-click timeout did not disable its time check");
}

void auto_repeat_capture_and_update() {
    torchlight::UiAutoRepeatTiming repeat;
    require(!repeat.enabled() && repeat.repeat_button() == repeat.no_button,
            "auto-repeat defaults drifted");
    require_near(repeat.delay(), 0.3F, "default repeat delay drifted");
    require_near(repeat.rate(), 0.06F, "default repeat rate drifted");

    repeat.set_enabled(true);
    require(repeat.wants_capture_on_down(), "first enabled down did not request capture");
    repeat.button_down(0, false);
    require(repeat.repeat_button() == repeat.no_button,
            "failed capture armed repeat state");
    repeat.button_down(0, true);
    require(repeat.repeat_button() == 0 && !repeat.repeating(),
            "successful capture did not arm the pressed button");

    require(!repeat.advance(0.3F), "repeat fired at delay equality");
    require(repeat.advance(0.0001F) == 0 && repeat.repeating(),
            "repeat did not fire after strict delay boundary");
    require_near(repeat.elapsed(), 0.0F, "initial repeat retained delay overshoot");
    require(!repeat.advance(0.06F), "repeat fired at rate equality");
    require(repeat.advance(0.1201F) == 0, "large step did not emit one repeat");
    require_near(repeat.elapsed(), 0.1201F, "rate subtraction did not retain one-step surplus");
    require(repeat.advance(0.0F) == 0, "retained surplus was incorrectly drained in prior update");
    require_near(repeat.elapsed(), 0.0601F, "second update did not subtract exactly one rate");

    // A second physical button replaces the active repeat and resets timing.
    repeat.button_down(1, true);
    require(repeat.repeat_button() == 1 && !repeat.repeating() && repeat.elapsed() == 0.0F,
            "different captured button did not reset repeat phase");
    require(repeat.button_up(), "active repeat mouse-up did not request releaseInput");
    require(repeat.repeat_button() == repeat.no_button,
            "mouse-up did not clear repeat button");
    require(!repeat.button_up(), "inactive mouse-up repeated releaseInput request");
}

void auto_repeat_loss_and_configuration() {
    torchlight::UiAutoRepeatTiming repeat;
    repeat.set_enabled(true);
    repeat.set_delay(0.5F);
    repeat.set_rate(0.1F);
    repeat.button_down(2, true);
    static_cast<void>(repeat.advance(0.4F));
    repeat.capture_lost();
    require(repeat.repeat_button() == repeat.no_button && !repeat.advance(10.0F),
            "capture loss left repeat armed");

    // Native capture loss and enabled toggle clear only the button sentinel.
    repeat.button_down(2, true);
    static_cast<void>(repeat.advance(0.6F));
    require(repeat.repeating(), "configured delay did not enter repeat phase");
    repeat.set_enabled(false);
    require(repeat.repeat_button() == repeat.no_button && repeat.repeating(),
            "disable reset fields beyond the native repeat-button write");
    repeat.set_enabled(true);
    repeat.button_down(2, true);
    require(!repeat.repeating() && repeat.elapsed() == 0.0F,
            "new captured press did not initialize retained phase state");
}

} // namespace

int main() {
    try {
        click_tracker_boundaries();
        independent_buttons_and_disabled_timeout();
        release_click_eligibility();
        auto_repeat_capture_and_update();
        auto_repeat_loss_and_configuration();
        std::cout << "PASS: shipped CEGUI click grouping and per-window mouse auto-repeat timing\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
