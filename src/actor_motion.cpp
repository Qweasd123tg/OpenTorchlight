#include "torchlight/actor_motion.hpp"

#include <algorithm>
#include <cmath>

namespace torchlight {

ActorMotion::ActorMotion(std::array<float, 3> position, float speed)
    : position_(position), destination_(position), speed_(std::max(0.0F, speed)) {}

void ActorMotion::set_destination(float x, float z) noexcept {
    set_destination({x, position_[1], z});
}

void ActorMotion::set_destination(const std::array<float, 3>& destination) noexcept {
    if (!std::all_of(destination.begin(), destination.end(),
                     [](float value) { return std::isfinite(value); })) {
        return;
    }
    destination_ = destination;
    moving_ = destination_ != position_;
}

void ActorMotion::set_speed(float speed) noexcept {
    if (std::isfinite(speed) && speed >= 0.0F) speed_ = speed;
}

void ActorMotion::stop() noexcept {
    destination_ = position_;
    moving_ = false;
}

void ActorMotion::advance(float seconds) noexcept {
    if (!moving_ || !(seconds > 0.0F) || !std::isfinite(seconds) || speed_ <= 0.0F) {
        return;
    }
    const float delta_x = destination_[0] - position_[0];
    const float delta_y = destination_[1] - position_[1];
    const float delta_z = destination_[2] - position_[2];
    const float distance = std::hypot(delta_x, delta_z);
    if (!(distance > 0.0F) || !std::isfinite(distance)) {
        stop();
        return;
    }
    const float travel = speed_ * seconds;
    if (travel >= distance) {
        position_[0] = destination_[0];
        position_[1] = destination_[1];
        position_[2] = destination_[2];
        moving_ = false;
        return;
    }
    const float ratio = travel / distance;
    position_[0] += delta_x * ratio;
    position_[1] += delta_y * ratio;
    position_[2] += delta_z * ratio;
}

} // namespace torchlight
