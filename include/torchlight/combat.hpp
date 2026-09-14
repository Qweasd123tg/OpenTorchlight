#pragma once

#include "torchlight/entity_world.hpp"
#include "torchlight/player.hpp"
#include "torchlight/randomizer.hpp"

#include <array>
#include <cstdint>

namespace torchlight {

enum class CombatState {
    idle,
    approaching,
    waiting,
    attacked,
    killed,
};

struct CombatUpdate {
    CombatState state = CombatState::idle;
    std::uint64_t target_id = 0;
    std::int32_t damage = 0;
    float remaining_health = 0.0F;
};

class CombatController {
public:
    CombatController(const PlayerPrototype& player, std::uint32_t random_seed);

    [[nodiscard]] bool select_target(RuntimeEntityWorld& world,
                                     const std::array<float, 3>& position,
                                     float maximum_distance) noexcept;
    void clear_target() noexcept;
    void equip(const WeaponItem& item) noexcept;
    [[nodiscard]] const RuntimeEntity* target(
        const RuntimeEntityWorld& world) const noexcept;
    [[nodiscard]] std::uint64_t target_id() const noexcept { return target_id_; }
    [[nodiscard]] float attack_range() const noexcept { return attack_range_; }
    [[nodiscard]] float attack_interval() const noexcept { return attack_interval_; }
    [[nodiscard]] std::int32_t minimum_damage() const noexcept {
        return minimum_damage_;
    }
    [[nodiscard]] std::int32_t maximum_damage() const noexcept {
        return maximum_damage_;
    }

    [[nodiscard]] CombatUpdate update(float seconds,
                                      const std::array<float, 3>& player_position,
                                      RuntimeEntityWorld& world,
                                      LogicRuntime& logic);

private:
    TorchlightRandom random_;
    std::uint64_t target_id_ = 0;
    std::int32_t minimum_damage_ = 1;
    std::int32_t maximum_damage_ = 1;
    float attack_range_ = 1.0F;
    float attack_interval_ = 1.0F;
    float reach_bonus_ = 0.0F;
    float cooldown_ = 0.0F;
};

} // namespace torchlight
