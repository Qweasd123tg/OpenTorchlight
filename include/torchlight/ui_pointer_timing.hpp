#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>

namespace torchlight {

enum class UiPointerDispatchKind { button_down, double_click, triple_click };

struct UiPointerDownDecision {
    std::uint32_t click_count = 1;

    [[nodiscard]] UiPointerDispatchKind dispatch_kind(bool wants_multi_clicks) const noexcept;
};

struct UiPointerUpDecision {
    std::uint32_t click_count = 0;
    bool click_eligible = false;
};

// The shipped CEGUI 0.6.2 System keeps one click tracker for each of its five
// MouseButton enum values. The target is a stable Window identity supplied by
// the caller; the timing helper never owns or dereferences it.
class UiPointerTiming {
public:
    static constexpr double default_single_click_timeout = 0.2;
    static constexpr double default_multi_click_timeout = 0.33;
    static constexpr float default_multi_click_width = 12.0F;
    static constexpr float default_multi_click_height = 12.0F;

    void set_single_click_timeout(double seconds) noexcept;
    void set_multi_click_timeout(double seconds) noexcept;
    void set_multi_click_area(float width, float height) noexcept;

    [[nodiscard]] UiPointerDownDecision button_down(
        std::uint8_t button, float x, float y, double time_seconds,
        std::optional<std::size_t> target);
    [[nodiscard]] UiPointerUpDecision button_up(
        std::uint8_t button, float x, float y, double time_seconds,
        std::optional<std::size_t> target) const;

private:
    struct ClickTracker {
        double last_down_time = 0.0;
        std::uint32_t count = 0;
        float left = 0.0F, top = 0.0F, right = 0.0F, bottom = 0.0F;
        std::optional<std::size_t> target;
    };

    [[nodiscard]] static std::size_t checked_button(std::uint8_t button);
    [[nodiscard]] static bool contains(const ClickTracker&, float x, float y) noexcept;

    std::array<ClickTracker, 5> trackers_{};
    double single_click_timeout_ = default_single_click_timeout;
    double multi_click_timeout_ = default_multi_click_timeout;
    float multi_click_width_ = default_multi_click_width;
    float multi_click_height_ = default_multi_click_height;
};

// Per-Window mouse auto-repeat state. Capture remains owned by UiWindowRuntime;
// the booleans returned/accepted here preserve the original call ordering.
class UiAutoRepeatTiming {
public:
    static constexpr std::uint8_t no_button = 6;
    static constexpr float default_delay = 0.3F;
    static constexpr float default_rate = 0.06F;

    void set_enabled(bool enabled) noexcept;
    void set_delay(float seconds) noexcept;
    void set_rate(float seconds) noexcept;

    [[nodiscard]] bool enabled() const noexcept { return enabled_; }
    [[nodiscard]] float delay() const noexcept { return delay_; }
    [[nodiscard]] float rate() const noexcept { return rate_; }
    [[nodiscard]] std::uint8_t repeat_button() const noexcept { return repeat_button_; }
    [[nodiscard]] bool repeating() const noexcept { return repeating_; }
    [[nodiscard]] float elapsed() const noexcept { return elapsed_; }

    [[nodiscard]] bool wants_capture_on_down() const noexcept;
    void button_down(std::uint8_t button, bool capture_is_self) noexcept;
    [[nodiscard]] bool button_up() noexcept;
    void capture_lost() noexcept;
    [[nodiscard]] std::optional<std::uint8_t> advance(float seconds) noexcept;

private:
    bool enabled_ = false;
    bool repeating_ = false;
    float delay_ = default_delay;
    float rate_ = default_rate;
    float elapsed_ = 0.0F;
    std::uint8_t repeat_button_ = no_button;
};

} // namespace torchlight
