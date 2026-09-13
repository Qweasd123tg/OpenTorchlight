#include "torchlight/pointer_movement.hpp"

namespace torchlight {

bool PointerMovementController::move_to_pointer(bool legacy_argument, bool actor_projection_mode,
                                                PointerMovementServices& services) noexcept {
    (void)legacy_argument;

    WorldPosition destination;
    if (!services.find_world_location(destination, actor_projection_mode)) {
        return false;
    }

    const WorldPosition actor = services.actor_position(true);
    const bool same_position = destination.x == actor.x && destination.y == actor.y &&
                               destination.z == actor.z;

    // The original uses an ordered floating-point comparison. A NaN delay,
    // like a positive delay, suppresses a changed destination.
    if (!same_position && !(repath_delay_ <= 0.0f)) {
        return false;
    }

    services.set_destination(destination.x, destination.z);
    repath_delay_ = repath_delay_seconds;
    return true;
}

} // namespace torchlight
