#pragma once

#include "torchlight/input_state.hpp"

namespace torchlight {

enum class MouseButton : std::uint32_t { left = 0, right = 1, middle = 2 };

class MouseManager {
public:
    void mouse_event(std::uint32_t message, std::uint32_t parameter) noexcept;
    void capture() noexcept;
    void flush() noexcept;
    void flush_all() noexcept;
    void update(const InputState& input) noexcept;
    const Point& virtual_mouse_position(float source_width, float source_height,
                                        float target_width, float target_height) noexcept;

    [[nodiscard]] bool button_pressed(MouseButton button) const noexcept;
    [[nodiscard]] bool button_held(MouseButton button) const noexcept;
    [[nodiscard]] bool button_double_click(MouseButton button) const noexcept;
    [[nodiscard]] std::int32_t wheel_delta() const noexcept;
    [[nodiscard]] const Point& position() const noexcept { return position_; }

private:
    using Buttons = std::array<std::uint8_t, 3>;
    Buttons pressed_{};
    Buttons held_{};
    Buttons double_click_{};
    Buttons pending_pressed_{};
    Buttons pending_held_{};
    Buttons pending_double_click_{};
    std::uint32_t wheel_ = 0;
    std::uint32_t pending_wheel_ = 0;
    Point position_{};
    Point virtual_position_{};
};

} // namespace torchlight
