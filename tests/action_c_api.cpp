#include "torchlight/pointer_movement.hpp"

#include <cstdint>

namespace {

struct ActionResult {
    std::uint32_t find_calls = 0;
    std::uint32_t position_calls = 0;
    std::uint32_t destination_calls = 0;
    std::uint32_t projection_mode = 0;
    std::uint32_t current_position = 0;
    std::uint32_t moved = 0;
    float cooldown = 0.0f;
    float destination_x = 0.0f;
    float destination_z = 0.0f;
};

class TestMovementServices final : public torchlight::PointerMovementServices {
public:
    TestMovementServices(bool projection_result, torchlight::WorldPosition projected,
                         torchlight::WorldPosition actor, ActionResult& result) noexcept
        : projection_result_(projection_result), projected_(projected), actor_(actor), result_(result) {}

    bool find_world_location(torchlight::WorldPosition& position,
                             bool actor_projection_mode) override {
        ++result_.find_calls;
        result_.projection_mode = actor_projection_mode;
        position = projected_;
        return projection_result_;
    }

    torchlight::WorldPosition actor_position(bool current) override {
        ++result_.position_calls;
        result_.current_position = current;
        return actor_;
    }

    void set_destination(float x, float z) override {
        ++result_.destination_calls;
        result_.destination_x = x;
        result_.destination_z = z;
    }

private:
    bool projection_result_;
    torchlight::WorldPosition projected_;
    torchlight::WorldPosition actor_;
    ActionResult& result_;
};

} // namespace

extern "C" void recovered_move_to_pointer(bool projection_result, float projected_x,
                                           float projected_y, float projected_z, float actor_x,
                                           float actor_y, float actor_z, bool legacy_argument,
                                           bool actor_projection_mode, float cooldown,
                                           ActionResult* result) {
    *result = {};
    TestMovementServices services(projection_result, {projected_x, projected_y, projected_z},
                                  {actor_x, actor_y, actor_z}, *result);
    torchlight::PointerMovementController controller;
    controller.set_repath_delay(cooldown);
    result->moved = controller.move_to_pointer(legacy_argument, actor_projection_mode, services);
    result->cooldown = controller.repath_delay();
}
