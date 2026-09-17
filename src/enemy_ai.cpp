#include "torchlight/enemy_ai.hpp"
#include "torchlight/scene_animation.hpp"
#include <stdexcept>

#include <algorithm>
#include <cmath>
#include <limits>

namespace torchlight {

std::int32_t evaluated_maximum_mana(std::int32_t raw_base, float growth,
    const AttackEffects& effects) {
    const auto checked = [](float value) {
        if (!std::isfinite(value) || static_cast<double>(value) < std::numeric_limits<std::int32_t>::min() ||
            static_cast<double>(value) > std::numeric_limits<std::int32_t>::max())
            throw std::invalid_argument("invalid evaluated mana contribution");
        return static_cast<std::int32_t>(value);
    };
    // Preserve int -> float add -> trunc int and two SEPARATE ceil operations.
    const auto base = std::max(1, checked(static_cast<float>(raw_base) + growth));
    const auto percent = checked(std::ceil(static_cast<float>(base) * effects.get(0x13) / 100.0F));
    const auto flat = checked(std::ceil(effects.get(4)));
    const auto total = static_cast<std::int64_t>(base) + percent + flat;
    if (total < 0 || total > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("invalid evaluated maximum mana");
    return static_cast<std::int32_t>(total);
}

PlayerCombatState::PlayerCombatState(const PlayerPrototype& prototype,
                                     std::uint32_t random_seed) {
    collision_radius_ = prototype.attack_character.collision_radius;
    TorchlightRandom random(random_seed);
    if (!std::isfinite(prototype.minimum_health) || !std::isfinite(prototype.maximum_health))
        throw std::invalid_argument("nonfinite player health range");
    const auto low = std::max(
        1.0F, std::min(prototype.minimum_health, prototype.maximum_health));
    const auto high = std::max(
        low, std::max(prototype.minimum_health, prototype.maximum_health));
    const auto rolled = high > low ? random.between(low, high) : low;
    if (!std::isfinite(rolled) || static_cast<double>(std::trunc(rolled)) > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("player health roll exceeds int32");
    base_health_ = static_cast<std::int32_t>(std::max(1.0F, std::trunc(rolled)));
    maximum_health_ = static_cast<float>(base_health_);
    health_ = maximum_health_;
    base_damage_defense_ = prototype.damage_defense;
    base_damage_defense_.natural_armor += random.integer_between(
        std::min(prototype.minimum_armor_bonus, prototype.maximum_armor_bonus),
        std::max(prototype.minimum_armor_bonus, prototype.maximum_armor_bonus));
    refresh_damage_defense();
    base_mana_ = prototype.base_mana;
    recovery_rules_ = prototype.recovery_rules;
    validate_vital_recovery_rules(recovery_rules_);
    base_vital_effects_ = prototype.attack_character.effects;
    set_equipment_vital_effects({});
    restore_after_death();
}

bool PlayerCombatState::spend_mana(float amount) noexcept {
    if (!alive() || !mana_ || !std::isfinite(amount) || amount < 0 || *mana_ < amount) return false;
    *mana_ -= amount;
    return true;
}
bool PlayerCombatState::update_vitals(float seconds) noexcept {
    if (!std::isfinite(seconds) || seconds < 0) return false;
    if (seconds == 0 || !alive()) return true;
    const auto health = advance_health(health_, maximum_health_,
        recovery_rules_.health_percent_per_second, health_per_second_, seconds);
    std::optional<float> mana;
    if (mana_ && maximum_mana_)
        mana = advance_vital(*mana_, *maximum_mana_,
            recovery_rules_.mana_percent_per_second, mana_per_second_, seconds);
    if (!health || (mana_ && !mana)) return false;
    health_ = *health;
    if (mana_) mana_ = mana;
    return true;
}
void PlayerCombatState::set_equipment_vital_effects(const AttackEffects& equipment) {
    auto next_equipment = equipment;
    auto effects = base_vital_effects_;
    effects.append(equipment);
    const auto health_max = static_cast<float>(evaluated_maximum_health(base_health_, 0, effects));
    std::optional<float> mana_max;
    if (base_mana_) mana_max = static_cast<float>(evaluated_maximum_mana(*base_mana_, 0, effects));
    const auto health_rate = evaluated_health_rate(effects);
    const auto mana_rate = evaluated_mana_rate(effects);
    if (!std::isfinite(health_rate) || !std::isfinite(mana_rate))
        throw std::invalid_argument("nonfinite combined passive recovery rate");
    // All allocations/validation finish before committing any derived field.
    using std::swap;
    swap(equipment_vital_effects_, next_equipment);
    maximum_health_ = health_max;
    health_ = std::min(health_, maximum_health_);
    maximum_mana_ = mana_max;
    if (mana_) mana_ = mana_max ? std::optional<float>(std::min(*mana_, *mana_max)) : std::nullopt;
    health_per_second_ = health_rate;
    mana_per_second_ = mana_rate;
}
void PlayerCombatState::set_progression_vitals(std::int32_t maximum_health,
                                              std::optional<std::int32_t> base_mana) {
    if (maximum_health < 1 || (base_mana && *base_mana < 0))
        throw std::invalid_argument("invalid progression vitals");
    auto staged = *this;
    staged.base_health_ = maximum_health;
    staged.base_mana_ = base_mana;
    staged.set_equipment_vital_effects(staged.equipment_vital_effects_);
    staged.restore_after_death(); // CCharacter::levelUp refills vitals; no reroll.
    using std::swap;
    swap(*this, staged);
}
void PlayerCombatState::set_defense_attribute(std::int32_t value) noexcept {
    base_damage_defense_.defense_attribute = value;
    refresh_damage_defense();
}
void PlayerCombatState::restore_after_death() noexcept {
    health_ = maximum_health_;
    mana_ = maximum_mana_;
}

void PlayerCombatState::equip(const ArmorItem& item) noexcept {
    const auto index = static_cast<std::size_t>(item.slot);
    if (index >= equipped_armor_.size()) return;
    equipped_armor_[index] = item;
    refresh_damage_defense();
}

void PlayerCombatState::unequip(ArmorSlot slot) noexcept {
    const auto index = static_cast<std::size_t>(slot);
    if (index >= equipped_armor_.size()) return;
    equipped_armor_[index].reset();
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

void MonsterAiCooldown::update(float seconds) noexcept {
    // CMonster::updateAI @0x8e3a5b: subtraction happens before think gating;
    // negative elapsed remainder is retained until the next successful attack.
    remaining -= seconds;
}

void MonsterAiCooldown::attack_started(
    float unit_cooldown, std::optional<float> equipment_cooldown) noexcept {
    // CMonster::attackAI @0x8e00e6..0x8e013d, only after attack() succeeds.
    if (equipment_cooldown) {
        remaining = std::max(0.0F, remaining) + *equipment_cooldown;
    }
    remaining = std::max(0.0F, remaining) + unit_cooldown;
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
                             ? seconds
                             : 0.0F;
    std::vector<EnemyAiUpdate> updates;
    for (auto& entity : world.entities()) {
        if (!entity.alive || !entity.enabled || !entity.combat_targetable ||
            entity.kind != MasterResourceKind::monster) {
            states_.erase(entity.id);
            continue;
        }
        auto& state = states_[entity.id];
        state.ai_cooldown.update(elapsed);

        state.repath_after = std::max(0.0F, state.repath_after - elapsed);
        if (!player.alive()) {
            state.alerted = false;
            state.path.clear();
            state.action.cancel();
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

        if (state.action.active()) {
            updates.push_back({EnemyAiState::waiting, entity.id, false, 0, player.health()});
            continue;
        }
        const auto* description = select_ordinary_attack(entity.attacks, state.prefer_left, random_);
        if (!description) {
            state.attack_issue = "no ordinary attack description";
            updates.push_back({EnemyAiState::unavailable, entity.id, false, 0, player.health()});
            continue;
        }
        const auto attack_range = ordinary_attack_range(*description, entity.attacks, entity.attack_character);
        if (within_character_attack_reach(entity.position, player_position,
                entity.attack_character.collision_radius, player.collision_radius(), attack_range, has_ranged_weapon(entity.attacks))) {
            state.path.clear();
            if (state.ai_cooldown.blocks_attack()) {
                updates.push_back({EnemyAiState::waiting, entity.id, false, 0, player.health()});
                continue;
            }
            if (description->traits.ranged || !description->unavailable_reason.empty() ||
                description->animation_prefix.empty()) {
                state.attack_issue = description->traits.ranged ? "ranged attack needs missile/weapon-skill runtime" :
                    !description->unavailable_reason.empty() ? description->unavailable_reason : "no weapon description in selected hand";
                updates.push_back({EnemyAiState::unavailable, entity.id, false, 0, player.health()});
                continue;
            }
            AttackClips clips;
            try { if (resolver_) clips = resolver_(entity.mesh_path, description->animation_prefix); }
            catch (const std::runtime_error& error) { state.attack_issue = error.what(); }
            if (clips.empty()) {
                if (state.attack_issue.empty()) state.attack_issue = "no loaded clip for " + description->animation_prefix;
                updates.push_back({EnemyAiState::unavailable, entity.id, false, 0, player.health()});
                continue;
            }
            const auto effects = total_attack_effects(entity.attacks, entity.attack_character);
            const auto speed = ordinary_attack_speed(description->speed_denominator, effects, entity.attack_character.ai_flag_one);
            const auto selected_clip = clips[select_original_random_animation(clips.size(), random_)];
            if (!next_execution_id_) throw std::overflow_error("enemy attack execution IDs exhausted");
            state.action.start(next_execution_id_, 1, *description, selected_clip, speed);
            ++next_execution_id_;
            state.ai_cooldown.attack_started(entity.ai_attack_cooldown, description->equipment_ai_cooldown);
            state.attack_issue = effects.unresolved.empty() ? "" :
                "partial effects: " + std::to_string(effects.unresolved.size()) + " unresolved resource records";
            updates.push_back({EnemyAiState::attacking, entity.id, false, 0, player.health()});
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

void EnemyController::advance_animations(float seconds, const RuntimeEntityWorld& world,
                                         const PlayerCombatState& player) {
    const auto elapsed = std::isfinite(seconds) && seconds > 0 ? seconds : 0;
    for (auto& [id, state] : states_) {
        const auto* entity = world.find(id);
        if (!entity || !entity->alive || !entity->enabled || !entity->combat_targetable || !player.alive())
            state.action.cancel();
        else state.action.advance(elapsed);
    }
}
EnemyAiUpdate EnemyController::perform_attack(std::uint64_t entity_id, const AnimationEventOccurrence& event,
    const std::array<float, 3>& player_position, PlayerCombatState& player, RuntimeEntityWorld& world) {
    const auto found = states_.find(entity_id);
    if (found == states_.end()) return {};
    auto& state = found->second;
    const auto* entity = world.find(entity_id);
    if (!entity || !entity->alive || !entity->enabled || !entity->combat_targetable || !player.alive()) {
        state.action.cancel(); return {};
    }
    if (!state.action.consume_hit(event)) return {};
    state.prefer_left = !state.prefer_left;
    const auto reach = ordinary_strike_range(state.action.description(), entity->attack_character,
        total_attack_effects(entity->attacks, entity->attack_character));
    if (!within_character_attack_reach(entity->position, player_position,
            entity->attack_character.collision_radius, player.collision_radius(), reach, state.action.description().traits.ranged))
        return {EnemyAiState::missed, entity_id, false, 0, player.health()};
    const auto damage = ordinary_physical_damage(state.action.description(), entity->attacks, entity->attack_character);
    const auto rolled = random_.integer_between(damage[0], damage[1]);
    const auto applied = player.apply_damage(rolled, rolled, DamageType::physical, random_);
    return {player.alive() ? EnemyAiState::attacked : EnemyAiState::player_killed,
        entity_id, false, applied, player.health()};
}
void EnemyController::finish_animation_frame() noexcept {
    for (auto& entry : states_) entry.second.action.finish_frame();
}
void EnemyController::level_resetting() noexcept {
    for (auto& entry : states_) {
        auto& state = entry.second;
        state.action.cancel();
        state.alerted = false;
        state.path.clear();
        state.next_path_node = 0;
        state.repath_after = 0;
        state.attack_issue.clear();
    }
}

void EnemyController::interrupt_attack(std::uint64_t id) noexcept {
    const auto found = states_.find(id);
    if (found != states_.end()) found->second.action.cancel();
}
const OrdinaryAttackAction* EnemyController::action(std::uint64_t id) const noexcept {
    const auto found = states_.find(id);
    return found == states_.end() ? nullptr : &found->second.action;
}
const std::string& EnemyController::last_attack_issue(std::uint64_t id) const noexcept {
    static const std::string empty;
    const auto found = states_.find(id);
    return found == states_.end() ? empty : found->second.attack_issue;
}
float EnemyController::ai_cooldown_remaining(std::uint64_t id) const noexcept {
    const auto found = states_.find(id);
    return found == states_.end() ? 0 : found->second.ai_cooldown.remaining;
}

std::size_t EnemyController::alerted_count() const noexcept {
    return static_cast<std::size_t>(std::count_if(
        states_.begin(), states_.end(),
        [](const auto& entry) { return entry.second.alerted; }));
}

} // namespace torchlight
