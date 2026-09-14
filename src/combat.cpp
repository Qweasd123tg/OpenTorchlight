#include "torchlight/combat.hpp"

#include <algorithm>
#include <cmath>

namespace torchlight {

CombatController::CombatController(const PlayerPrototype& player,
                                   std::uint32_t random_seed)
    : random_(random_seed) {
    minimum_damage_ = std::max(1, std::min(player.minimum_damage,
                                           player.maximum_damage));
    maximum_damage_ = std::max(1, std::max(player.minimum_damage,
                                           player.maximum_damage));
    reach_bonus_ = player.reach_bonus;
    attack_range_ = std::max(0.5F, reach_bonus_ + 1.0F);
    if (player.starting_weapon) {
        equip(roll_weapon_item(*player.starting_weapon, random_));
    }
    attack_interval_ = player.attack_speed > 0.0F
                           ? std::max(0.1F, 100.0F / player.attack_speed)
                           : 1.0F;
}

void CombatController::equip(const WeaponItem& item) noexcept {
    minimum_damage_ = std::max(1, item.minimum_damage);
    maximum_damage_ = std::max(minimum_damage_, item.maximum_damage);
    // CCharacter::attackRange adds the weapon range, scaled REACH_BONUS and
    // the original 0.2 world-unit contact allowance. Player scale is 1 here.
    attack_range_ = std::max(
        0.5F, item.prototype.range + reach_bonus_ + 0.2F);
}

bool CombatController::select_target(RuntimeEntityWorld& world,
                                     const std::array<float, 3>& position,
                                     float maximum_distance) noexcept {
    const auto* selected = world.nearest_alive_monster(position, maximum_distance);
    target_id_ = selected == nullptr ? 0 : selected->id;
    return selected != nullptr;
}

void CombatController::clear_target() noexcept {
    target_id_ = 0;
}

const RuntimeEntity* CombatController::target(
    const RuntimeEntityWorld& world) const noexcept {
    const auto* selected = world.find(target_id_);
    return selected != nullptr && selected->alive && selected->combat_targetable &&
                   selected->kind == MasterResourceKind::monster
               ? selected
               : nullptr;
}

CombatUpdate CombatController::update(float seconds,
                                      const std::array<float, 3>& player_position,
                                      RuntimeEntityWorld& world,
                                      LogicRuntime& logic) {
    if (std::isfinite(seconds) && seconds > 0.0F) {
        cooldown_ = std::max(0.0F, cooldown_ - seconds);
    }
    const auto* selected = target(world);
    if (selected == nullptr) {
        clear_target();
        return {};
    }
    const auto selected_id = selected->id;
    const auto delta_x = selected->position[0] - player_position[0];
    const auto delta_z = selected->position[2] - player_position[2];
    if (std::hypot(delta_x, delta_z) > attack_range_) {
        return {CombatState::approaching, selected_id, 0, selected->health};
    }
    if (cooldown_ > 0.0F) {
        return {CombatState::waiting, selected_id, 0, selected->health};
    }

    const auto rolled_damage = random_.integer_between(
        minimum_damage_, maximum_damage_);
    const auto mitigation = mitigate_damage(
        rolled_damage, rolled_damage, DamageType::physical, 1.0F,
        selected->damage_defense, random_);
    const auto result = world.apply_damage(
        selected_id, static_cast<float>(mitigation.applied), logic);
    cooldown_ = attack_interval_;
    if (!result.accepted) {
        clear_target();
        return {};
    }
    const auto state = result.killed ? CombatState::killed : CombatState::attacked;
    if (result.killed) {
        target_id_ = 0;
    }
    return {state, selected_id, mitigation.applied, result.remaining_health};
}

} // namespace torchlight
