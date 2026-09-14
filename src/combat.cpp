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
    attack_range_ = std::max(0.5F, player.reach_bonus + 1.0F);
    if (player.starting_weapon) {
        const auto& weapon = *player.starting_weapon;
        // CEquipment::calculateCombatStats first rolls the data-file percentage,
        // applies rarity and speed modifiers, truncates it, then setGraphDamage
        // scales BASE_WEAPON_DAMAGE and rounds the result upward.
        const auto raw_damage = random_.integer_between(
            weapon.minimum_damage_percent, weapon.maximum_damage_percent);
        const auto scaled_percent = static_cast<std::int32_t>(
            static_cast<float>(raw_damage) *
            (static_cast<float>(weapon.rarity_damage_modifier) / 100.0F) *
            (static_cast<float>(weapon.speed_damage_modifier) / 100.0F));
        const auto damage = static_cast<std::int32_t>(std::ceil(
            weapon.base_weapon_damage * static_cast<float>(scaled_percent) / 100.0F));
        minimum_damage_ = std::max(1, damage);
        maximum_damage_ = minimum_damage_;
        // CCharacter::attackRange adds the weapon range, scaled REACH_BONUS and
        // the original 0.2 world-unit contact allowance. Player scale is 1 here.
        attack_range_ = std::max(
            0.5F, weapon.range + player.reach_bonus + 0.2F);
    }
    attack_interval_ = player.attack_speed > 0.0F
                           ? std::max(0.1F, 100.0F / player.attack_speed)
                           : 1.0F;
}

bool CombatController::select_target(RuntimeEntityWorld& world,
                                     const std::array<float, 3>& position,
                                     float maximum_distance) noexcept {
    const auto* selected = world.nearest_alive_monster(position, maximum_distance);
    target_id_ = selected == nullptr ? 0 : selected->id;
    cooldown_ = 0.0F;
    return selected != nullptr;
}

void CombatController::clear_target() noexcept {
    target_id_ = 0;
    cooldown_ = 0.0F;
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

    const auto damage = random_.integer_between(minimum_damage_, maximum_damage_);
    const auto result = world.apply_damage(selected_id, static_cast<float>(damage), logic);
    cooldown_ = attack_interval_;
    if (!result.accepted) {
        clear_target();
        return {};
    }
    const auto state = result.killed ? CombatState::killed : CombatState::attacked;
    if (result.killed) {
        target_id_ = 0;
    }
    return {state, selected_id, damage, result.remaining_health};
}

} // namespace torchlight
