#include "torchlight/combat.hpp"
#include "torchlight/scene_animation.hpp"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace torchlight {
CombatController::CombatController(const PlayerPrototype& player, std::uint32_t seed)
    : random_(seed), mesh_path_(player.mesh_path), loadout_(player.attacks),
      character_(player.attack_character) {
    // Directly constructed prototypes are explicit synthetic/programmatic data.
    // Resource loading always fills innate descriptions (including missing-field diagnostics).
    if (loadout_.innate.empty()) {
        AttackDescription innate;
        innate.minimum_damage = player.minimum_damage; innate.maximum_damage = player.maximum_damage;
        loadout_.innate.push_back(innate);
    }
    character_.strength = player.strength; character_.dexterity = player.dexterity;
    character_.reach_bonus = player.reach_bonus;
    base_effects_ = character_.effects;
    if (player.starting_weapon) equip(roll_weapon_item(*player.starting_weapon, random_));
    else refresh_attack_values();
}
void CombatController::refresh_attack_values() {
    const auto* selected = loadout_.right ? &*loadout_.right :
        loadout_.left ? &*loadout_.left : loadout_.innate.empty() ? nullptr : &loadout_.innate.front();
    if (!selected) { minimum_damage_ = maximum_damage_ = 0; attack_range_ = 0; return; }
    const auto damage = ordinary_physical_damage(*selected, loadout_, character_);
    minimum_damage_ = damage[0]; maximum_damage_ = damage[1];
    attack_range_ = ordinary_attack_range(*selected, loadout_, character_);
    attack_playback_speed_ = ordinary_attack_speed(selected->speed_denominator,
                                                   total_attack_effects(loadout_, character_), character_.ai_flag_one);
}
void CombatController::equip(const WeaponItem& item) {
    if (action_.active()) throw std::logic_error("cannot replace equipment during an attack");
    auto description = describe_weapon_attack(item, item.prototype.attack_hand);
    // Validate before replacing current equipment.
    static_cast<void>(ordinary_attack_speed(description.speed_denominator, description.effects));
    std::optional<AttackDescription> replacement(std::move(description));
    if (replacement->hand == AttackHand::left) {
        loadout_.right.reset();
        loadout_.left.swap(replacement);
    } else {
        loadout_.left.reset();
        loadout_.right.swap(replacement);
    }
    refresh_attack_values();
}
void CombatController::unequip() {
    if (action_.active()) throw std::logic_error("cannot remove equipment during an attack");
    loadout_.right.reset(); loadout_.left.reset(); refresh_attack_values();
}
void CombatController::set_external_attack_effects(const AttackEffects& effects) {
    character_.effects = base_effects_; character_.effects.append(effects); refresh_attack_values();
}
void CombatController::set_animation_resolver(AttackClipResolver resolver) { resolver_ = std::move(resolver); }
void CombatController::reset_level_context() noexcept {
    target_id_ = 0; action_.cancel(); resolver_ = {};
    // Equipment, effects, RNG and next execution ID survive a level change.
}
void CombatController::interrupt_attack() noexcept { action_.cancel(); }
bool CombatController::select_target(RuntimeEntityWorld& world, const std::array<float, 3>& position,
                                     float maximum_distance) noexcept {
    const auto* selected = world.nearest_alive_monster(position, maximum_distance);
    target_id_ = selected ? selected->id : 0; return selected != nullptr;
}
void CombatController::clear_target() noexcept { target_id_ = 0; }
const RuntimeEntity* CombatController::target(const RuntimeEntityWorld& world) const noexcept {
    const auto* selected = world.find(target_id_);
    return selected && selected->alive && selected->enabled && selected->combat_targetable &&
        selected->kind == MasterResourceKind::monster ? selected : nullptr;
}
CombatUpdate CombatController::update(float seconds, const std::array<float, 3>& position,
                                     RuntimeEntityWorld& world) {
    static_cast<void>(seconds); // Clock belongs to the animation phase, not a second action timer.
    const auto* selected = target(world);
    if (!selected) { clear_target(); return {}; }
    if (action_.active()) return {CombatState::waiting, selected->id, 0, selected->health, action_.id()};
    const auto* description = select_ordinary_attack(loadout_, prefer_left_, random_);
    if (!description) { last_attack_issue_ = "no ordinary attack description"; return {CombatState::unavailable, selected->id}; }
    attack_range_ = ordinary_attack_range(*description, loadout_, character_);
    if (!within_character_attack_reach(position, selected->position, character_.collision_radius,
                                 selected->attack_character.collision_radius, attack_range_, has_ranged_weapon(loadout_)))
        return {CombatState::approaching, selected->id, 0, selected->health};
    if (!description->unavailable_reason.empty() || description->animation_prefix.empty() ||
        description->traits.ranged) {
        last_attack_issue_ = description->traits.ranged ? "ranged attack needs missile/weapon-skill runtime" :
            !description->unavailable_reason.empty() ? description->unavailable_reason : "weapon has no description in this hand";
        return {CombatState::unavailable, selected->id};
    }
    AttackClips clips;
    try { if (resolver_) clips = resolver_(mesh_path_, description->animation_prefix); }
    catch (const std::runtime_error& e) { last_attack_issue_ = e.what(); return {CombatState::unavailable, selected->id}; }
    if (clips.empty()) { last_attack_issue_ = "no loaded clip for " + description->animation_prefix; return {CombatState::unavailable, selected->id}; }
    const auto effects = total_attack_effects(loadout_, character_);
    const auto speed = ordinary_attack_speed(description->speed_denominator, effects, character_.ai_flag_one);
    const auto clip = clips[select_original_random_animation(clips.size(), random_)];
    if (!next_execution_id_) throw std::overflow_error("player attack execution IDs exhausted");
    action_.start(next_execution_id_, selected->id, *description, clip, speed);
    ++next_execution_id_;
    attack_playback_speed_ = speed;
    last_attack_issue_ = effects.unresolved.empty() ? "" :
        "partial effects: " + std::to_string(effects.unresolved.size()) + " unresolved resource records";
    return {CombatState::attacking, selected->id, 0, selected->health, action_.id()};
}
void CombatController::advance_animation(float seconds) {
    action_.advance(std::isfinite(seconds) && seconds > 0 ? seconds : 0);
}
CombatUpdate CombatController::perform_attack(const AnimationEventOccurrence& event,
    const std::array<float, 3>& position, RuntimeEntityWorld& world, LogicRuntime& logic) {
    if (!action_.consume_hit(event)) return {};
    prefer_left_ = !prefer_left_; // Original performAttack toggles per HIT, not per clip start.
    const auto* selected = world.find(action_.target_id());
    if (!selected || selected->id != target_id_ || !selected->alive || !selected->enabled ||
        !selected->combat_targetable || selected->kind != MasterResourceKind::monster)
        return {CombatState::missed, action_.target_id(), 0, 0, event.execution_id};
    const auto reach = ordinary_strike_range(action_.description(), character_, total_attack_effects(loadout_, character_));
    if (!within_character_attack_reach(position, selected->position, character_.collision_radius,
                                 selected->attack_character.collision_radius, reach, action_.description().traits.ranged))
        return {CombatState::missed, selected->id, 0, selected->health, event.execution_id};
    const auto damage = ordinary_physical_damage(action_.description(), loadout_, character_);
    const auto rolled = random_.integer_between(damage[0], damage[1]);
    const auto mitigation = mitigate_damage(rolled, rolled, DamageType::physical, 1,
                                            selected->damage_defense, random_);
    const auto id = selected->id;
    const auto result = world.apply_damage(id, static_cast<float>(mitigation.applied), logic, true);
    if (!result.accepted) return {CombatState::missed, id, 0, result.remaining_health, event.execution_id};
    if (result.killed) target_id_ = 0;
    return {result.killed ? CombatState::killed : CombatState::attacked, id,
            mitigation.applied, result.remaining_health, event.execution_id};
}
void CombatController::set_attributes(std::int32_t strength, std::int32_t dexterity) {
    character_.strength = strength;
    character_.dexterity = dexterity;
    refresh_attack_values();
}
void CombatController::finish_animation_frame() noexcept { action_.finish_frame(); }
} // namespace torchlight
