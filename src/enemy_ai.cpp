#include "torchlight/enemy_ai.hpp"

#include <algorithm>
#include <cmath>

namespace torchlight {

PlayerCombatState::PlayerCombatState(const PlayerPrototype& prototype,
                                     std::uint32_t random_seed) {
    TorchlightRandom random(random_seed);
    const auto low = std::max(
        1.0F, std::min(prototype.minimum_health, prototype.maximum_health));
    const auto high = std::max(
        low, std::max(prototype.minimum_health, prototype.maximum_health));
    const auto rolled = high > low ? random.between(low, high) : low;
    maximum_health_ = std::max(1.0F, std::trunc(rolled));
    health_ = maximum_health_;
    base_damage_defense_ = prototype.damage_defense;
    base_damage_defense_.natural_armor += random.integer_between(
        std::min(prototype.minimum_armor_bonus, prototype.maximum_armor_bonus),
        std::max(prototype.minimum_armor_bonus, prototype.maximum_armor_bonus));
    refresh_damage_defense();
}

void PlayerCombatState::equip(const ArmorItem& item) noexcept {
    equipped_armor_[static_cast<std::size_t>(item.slot)] = item;
    refresh_damage_defense();
}

void PlayerCombatState::refresh_damage_defense() noexcept {
    damage_defense_ = base_damage_defense_;
    for (const auto& item : equipped_armor_) {
        if (!item) {
            continue;
        }
        damage_defense_.natural_armor += item->damage_defense.natural_armor;
        for (std::size_t index = 0;
             index < damage_defense_.elemental_armor.size(); ++index) {
            damage_defense_.elemental_armor[index] +=
                item->damage_defense.elemental_armor[index];
        }
    }
}

std::int32_t PlayerCombatState::apply_damage(
    std::int32_t damage, std::int32_t maximum_damage, DamageType type,
    TorchlightRandom& random) noexcept {
    if (!alive()) {
        return 0;
    }
    const auto result = mitigate_damage(
        damage, maximum_damage, type, 1.0F, damage_defense_, random);
    health_ = std::max(0.0F, health_ - static_cast<float>(result.applied));
    return result.applied;
}

float EnemyController::distance_xz(const std::array<float, 3>& left,
                                   const std::array<float, 3>& right) noexcept {
    return std::hypot(left[0] - right[0], left[2] - right[2]);
}

bool EnemyController::advance_toward_player(
    float seconds, const std::array<float, 3>& player_position,
    float stopping_distance, RuntimeEntity& entity, State& state) noexcept {
    auto travel = entity.running_speed * seconds;
    const auto remaining_to_player =
        std::max(0.0F, distance_xz(entity.position, player_position) - stopping_distance);
    travel = std::min(travel, remaining_to_player);
    bool changed = false;
    while (travel > 0.0F && state.next_path_node < state.path.size()) {
        const auto& waypoint = state.path[state.next_path_node];
        const auto delta_x = waypoint[0] - entity.position[0];
        const auto delta_z = waypoint[2] - entity.position[2];
        const auto distance = std::hypot(delta_x, delta_z);
        if (distance <= 0.001F) {
            ++state.next_path_node;
            continue;
        }
        const auto step = std::min(travel, distance);
        entity.position[0] += delta_x * (step / distance);
        entity.position[2] += delta_z * (step / distance);
        travel -= step;
        changed = true;
        if (step >= distance) {
            ++state.next_path_node;
        }
    }
    return changed;
}

std::vector<EnemyAiUpdate> EnemyController::update(
    float seconds, const std::array<float, 3>& player_position,
    PlayerCombatState& player, RuntimeEntityWorld& world,
    const NavigationGrid* navigation) {
    const auto elapsed = std::isfinite(seconds) && seconds > 0.0F
                             ? std::min(seconds, 0.1F)
                             : 0.0F;
    std::vector<EnemyAiUpdate> updates;
    for (auto& entity : world.entities()) {
        if (!entity.alive || !entity.combat_targetable ||
            entity.kind != MasterResourceKind::monster) {
            states_.erase(entity.id);
            continue;
        }
        auto& state = states_[entity.id];
        state.cooldown = std::max(0.0F, state.cooldown - elapsed);
        state.repath_after = std::max(0.0F, state.repath_after - elapsed);
        if (!player.alive()) {
            state.alerted = false;
            state.path.clear();
            continue;
        }

        const auto distance = distance_xz(entity.position, player_position);
        if (!state.alerted && entity.sight_radius > 0.0F &&
            distance <= entity.sight_radius) {
            state.alerted = true;
        }
        const auto follow_radius = entity.follow_radius > 0.0F
                                       ? entity.follow_radius
                                       : entity.sight_radius;
        if (!state.alerted || (follow_radius > 0.0F && distance > follow_radius)) {
            state.alerted = false;
            state.path.clear();
            updates.push_back(
                {EnemyAiState::idle, entity.id, false, 0, player.health()});
            continue;
        }

        const auto attack_range = entity.attack_range;
        if (distance <= attack_range) {
            state.path.clear();
            if (state.cooldown > 0.0F || entity.attack_speed <= 0.0F ||
                entity.maximum_damage <= 0) {
                updates.push_back(
                    {EnemyAiState::waiting, entity.id, false, 0, player.health()});
                continue;
            }
            const auto rolled_damage = random_.integer_between(
                entity.minimum_damage, entity.maximum_damage);
            const auto damage = player.apply_damage(
                rolled_damage, rolled_damage, DamageType::physical,
                random_);
            state.cooldown = std::max(0.1F, 100.0F / entity.attack_speed);
            updates.push_back({player.alive() ? EnemyAiState::attacked
                                              : EnemyAiState::player_killed,
                               entity.id, false, damage, player.health()});
            continue;
        }

        if (state.repath_after <= 0.0F ||
            state.next_path_node >= state.path.size()) {
            state.path = navigation == nullptr
                             ? std::vector<std::array<float, 3>>{
                                   entity.position, player_position}
                             : navigation->find_path(entity.position, player_position);
            state.next_path_node = state.path.size() > 1U ? 1U : state.path.size();
            state.repath_after = 0.25F;
        }
        const auto moved = advance_toward_player(
            elapsed, player_position, attack_range, entity, state);
        updates.push_back(
            {EnemyAiState::chasing, entity.id, moved, 0, player.health()});
    }
    return updates;
}

std::size_t EnemyController::alerted_count() const noexcept {
    return static_cast<std::size_t>(std::count_if(
        states_.begin(), states_.end(),
        [](const auto& entry) { return entry.second.alerted; }));
}

} // namespace torchlight
