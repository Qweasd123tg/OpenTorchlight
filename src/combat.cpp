#include "torchlight/combat.hpp"
#include "torchlight/character_stats.hpp"
#include "torchlight/typed_damage.hpp"
#include "torchlight/scene_animation.hpp"
#include "torchlight/skill_event_runtime.hpp"

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
    character_.strength = player.strength; character_.dexterity = player.dexterity; character_.magic = player.magic; character_.magic_known = true;
    character_.reach_bonus = player.reach_bonus;
    base_effects_ = character_.effects;
    if (player.starting_weapon) equip(roll_weapon_item(*player.starting_weapon, random_));
    else refresh_attack_values();
}
void CombatController::refresh_attack_values() {
    const auto* selected = loadout_.right ? &*loadout_.right :
        loadout_.left ? &*loadout_.left : loadout_.innate.empty() ? nullptr : &loadout_.innate.front();
    if (!selected) { minimum_damage_ = maximum_damage_ = 0; attack_range_ = 0; return; }
    const auto damage = ordinary_damage_plan(*selected, loadout_, character_);
    minimum_damage_ = damage.minimum; maximum_damage_ = damage.maximum;
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
    target_id_ = 0; action_.cancel(); resolver_ = {}; line_of_sight_ = {};
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
    // Missile delivery is supported through the frame runtime (spawn at HIT,
    // damage at impact); every other gate (range/reach/LOS/clips) applies.
    const bool missile_delivery = description->delivery == WeaponDelivery::missile;
    if ((!ordinary_delivery_supported(*description) && !missile_delivery) ||
        !description->unavailable_reason.empty() || description->animation_prefix.empty() ||
        (description->traits.ranged && !line_of_sight_)) {
        last_attack_issue_ = (!ordinary_delivery_supported(*description) && !missile_delivery) ?
            weapon_delivery_issue(description->delivery) :
            !description->unavailable_reason.empty() ? description->unavailable_reason :
            description->animation_prefix.empty() ? "weapon has no description in this hand" : "ranged collision context is missing";
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
    if (action_.description().traits.ranged && (!line_of_sight_ || !line_of_sight_(position, selected->position)))
        return {CombatState::missed, selected->id, 0, selected->health, event.execution_id};
    const auto defense = evaluate_damage_defense(selected->damage_defense,
        total_attack_effects(selected->attacks, selected->attack_character));
    const auto mitigation = roll_ordinary_damage(action_.description(), loadout_, character_, defense, random_);
    const auto id = selected->id;
    const auto result = world.apply_damage(id, static_cast<float>(mitigation.applied), logic, true);
    if (!result.accepted) return {CombatState::missed, id, 0, result.remaining_health, event.execution_id};
    if (result.killed) target_id_ = 0;
    return {result.killed ? CombatState::killed : CombatState::attacked, id,
            mitigation.applied, result.remaining_health, event.execution_id};
}
void CombatController::set_attributes(std::int32_t strength, std::int32_t dexterity, std::int32_t magic) {
    character_.strength = strength;
    character_.dexterity = dexterity;
    character_.magic = magic;
    character_.magic_known = true;
    refresh_attack_values();
}
void CombatController::finish_animation_frame() noexcept { action_.finish_frame(); }
std::optional<CombatController::MissileShot> CombatController::begin_missile_attack(
    const AnimationEventOccurrence& event, const std::array<float, 3>& position,
    RuntimeEntityWorld& world) {
    // Same gates as perform_attack: consume the HIT, then re-verify the
    // target at event time. A consumed miss stays consumed, never delayed.
    if (!action_.consume_hit(event)) return std::nullopt;
    prefer_left_ = !prefer_left_; // Original performAttack toggles per HIT, not per clip start.
    const auto* selected = world.find(action_.target_id());
    if (!selected || selected->id != target_id_ || !selected->alive || !selected->enabled ||
        !selected->combat_targetable || selected->kind != MasterResourceKind::monster)
        return std::nullopt;
    const auto reach = ordinary_strike_range(action_.description(), character_,
                                             total_attack_effects(loadout_, character_));
    if (!within_character_attack_reach(position, selected->position, character_.collision_radius,
                                 selected->attack_character.collision_radius, reach,
                                 action_.description().traits.ranged))
        return std::nullopt;
    if (action_.description().traits.ranged && (!line_of_sight_ || !line_of_sight_(position, selected->position)))
        return std::nullopt;
    MissileShot shot;
    shot.description = action_.description();
    shot.loadout = loadout_;
    shot.character = character_;
    shot.target_id = selected->id;
    return shot;
}
CombatUpdate CombatController::apply_missile_impact(const MissileShot& shot, std::uint64_t victim_id,
    RuntimeEntityWorld& world, LogicRuntime& logic) {
    // Mirrors the perform_attack tail: defense at impact time, roll, apply.
    // Damage is computed at impact (original doDamageToCharacter), not at HIT.
    const auto* victim = world.find(victim_id);
    if (!victim || !victim->alive || !victim->enabled || !victim->combat_targetable ||
        victim->kind != MasterResourceKind::monster)
        return {CombatState::missed, victim_id, 0, 0, 0};
    const auto defense = evaluate_damage_defense(victim->damage_defense,
        total_attack_effects(victim->attacks, victim->attack_character));
    const auto mitigation = roll_missile_impact_damage(shot.description, shot.loadout, shot.character,
                                                       defense, random_);
    const auto result = world.apply_damage(victim_id, static_cast<float>(mitigation.applied), logic, true);
    if (!result.accepted) return {CombatState::missed, victim_id, 0, result.remaining_health, 0};
    if (result.killed) target_id_ = 0;
    return {result.killed ? CombatState::killed : CombatState::attacked, victim_id,
            mitigation.applied, result.remaining_health, 0};
}
CombatUpdate CombatController::apply_skill_weapon_impact(const SkillWeaponDamageRequest& request,
    RuntimeEntityWorld& world, LogicRuntime& logic) {
    const auto* victim = world.find(request.victim_id);
    const auto* weapon=loadout_.right ? &*loadout_.right : loadout_.left ? &*loadout_.left : nullptr;
    // Bounded single-weapon branch (right, otherwise left). Native applyWeaponDamage reads current
    // equipment at impact, not the ordinary missile's attack snapshot.
    if (request.blocked || request.expired || !victim || !victim->alive || !victim->enabled ||
        !victim->combat_targetable || victim->kind != MasterResourceKind::monster ||
        !weapon || (loadout_.right && loadout_.left) || !weapon->traits.ranged ||
        !ordinary_delivery_supported(*weapon))
        return {CombatState::missed, request.victim_id, 0, 0, 0};
    const auto defense = evaluate_damage_defense(victim->damage_defense,
        total_attack_effects(victim->attacks, victim->attack_character));
    const SkillWeaponRoll profile{request.weapon_damage_pct, request.soak_scale_pct,
        request.use_dps, weapon->speed_denominator};
    const auto damage = roll_skill_weapon_damage(*weapon, loadout_, character_, defense, profile, random_);
    const auto result = world.apply_damage(request.victim_id, static_cast<float>(damage.applied), logic, true);
    if (!result.accepted) return {CombatState::missed, request.victim_id, 0, result.remaining_health, 0};
    if (result.killed && target_id_ == request.victim_id) target_id_ = 0;
    return {result.killed ? CombatState::killed : CombatState::attacked, request.victim_id,
        damage.applied, result.remaining_health, 0};
}
} // namespace torchlight
