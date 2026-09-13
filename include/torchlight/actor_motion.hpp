#pragma once

#include <array>

namespace torchlight {

class ActorMotion {
public:
    ActorMotion(std::array<float, 3> position, float speed);

    void set_destination(float x, float z) noexcept;
    void set_destination(const std::array<float, 3>& destination) noexcept;
    void stop() noexcept;
    void advance(float seconds) noexcept;

    [[nodiscard]] const std::array<float, 3>& position() const noexcept { return position_; }
    [[nodiscard]] const std::array<float, 3>& destination() const noexcept {
        return destination_;
    }
    [[nodiscard]] float speed() const noexcept { return speed_; }
    [[nodiscard]] bool moving() const noexcept { return moving_; }

private:
    std::array<float, 3> position_{};
    std::array<float, 3> destination_{};
    float speed_ = 0.0F;
    bool moving_ = false;
};

} // namespace torchlight
