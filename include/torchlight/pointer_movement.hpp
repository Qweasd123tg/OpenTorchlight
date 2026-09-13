#pragma once

namespace torchlight {

struct WorldPosition {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

// Engine-facing operations used by the recovered CGameClient::moveToMouse.
// A desktop adapter can project a mouse cursor; an Android adapter can project
// a touch position without changing the movement decision below.
class PointerMovementServices {
public:
    virtual ~PointerMovementServices() = default;

    [[nodiscard]] virtual bool find_world_location(WorldPosition& position,
                                                   bool actor_projection_mode) = 0;
    [[nodiscard]] virtual WorldPosition actor_position(bool current) = 0;
    virtual void set_destination(float x, float z) = 0;
};

class PointerMovementController {
public:
    static constexpr float repath_delay_seconds = 0.1f;

    // legacy_argument is present in the original ABI, but the inspected build
    // does not read it. The projection mode comes from the controlled actor.
    [[nodiscard]] bool move_to_pointer(bool legacy_argument, bool actor_projection_mode,
                                       PointerMovementServices& services) noexcept;

    void set_repath_delay(float seconds) noexcept { repath_delay_ = seconds; }
    [[nodiscard]] float repath_delay() const noexcept { return repath_delay_; }

private:
    float repath_delay_ = 0.0f;
};

} // namespace torchlight
