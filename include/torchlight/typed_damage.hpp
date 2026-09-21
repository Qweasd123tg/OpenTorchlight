#pragma once

#include "torchlight/attack_action.hpp"
#include "torchlight/damage.hpp"

namespace torchlight {

// original-code: CCharacter::damageDefense / damageDefensePercent and AC.
// These are evaluated values, not additional raw armor or persistent effects.
struct EvaluatedDamageDefense {
    std::array<std::int32_t, 7> maximum{};
    std::array<std::int32_t, 7> percent_taken{};
};
[[nodiscard]] std::int32_t evaluated_magic(std::int32_t base, const AttackEffects& effects);
[[nodiscard]] EvaluatedDamageDefense evaluate_damage_defense(
    const DamageDefense& raw, const AttackEffects& effects);
[[nodiscard]] DamageMitigation mitigate_evaluated_damage(
    std::int32_t damage, std::int32_t maximum_damage, DamageType type,
    float armor_multiplier, const EvaluatedDamageDefense& defense,
    TorchlightRandom& random) noexcept;

struct OrdinaryDamageChannel {
    DamageType type = DamageType::physical;
    std::int32_t minimum = 0;
    std::int32_t maximum = 0;
};
struct OrdinaryDamagePlan {
    // The original always emits a base pair, then optional bonus channels 0..6.
    std::array<OrdinaryDamageChannel, 8> channels{};
    std::size_t count = 0;
    std::int32_t maximum = 0;
    std::int32_t minimum = 0;
};
struct OrdinaryDamageResult {
    std::array<DamageType, 8> types{};
    std::array<DamageMitigation, 8> channels{};
    std::size_t count = 0;
    std::int32_t maximum = 0;
    std::int32_t rolled = 0;
    std::int32_t applied = 0;
};
// Bounded ordinary HIT branch of CCharacter::rollAttack. Excludes criticals,
// glancing/block/reflect/procs, special attack flags, missiles and weapon skills.
// The base description and bonus-channel denominators intentionally differ.
[[nodiscard]] OrdinaryDamagePlan ordinary_damage_plan(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character);
[[nodiscard]] OrdinaryDamageResult roll_ordinary_damage(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character,
    const EvaluatedDamageDefense& defense, TorchlightRandom& random);
[[nodiscard]] OrdinaryDamageResult roll_missile_impact_damage(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character,
    const EvaluatedDamageDefense& defense, TorchlightRandom& random);

// Skill weapon-applier profile of CCharacter::rollAttack: the reachable slice
// from CSkillEvent::applyWeaponDamage in the missile path (performAttack
// @0x847280 flags 0x171F -> rollAttack @0x843ed0; research/skill-effect-
// dispatch.md §8). Shared plan/roll/mitigation core; percentage and DPS affect
// base AND bonus channels, with recomputed minima and separate total/roll
// flat-bonus ordering. research/skill-weapon-oracle.md records original-call
// comparisons, including the exact DPS constant bits 0x3f3bbbbc @0xfce530
// and soak (@0x844226/@0x844a05). Excludes criticals, glancing/block/reflect, procs,
// special flags and the equipment-missile sibling call.
struct SkillWeaponRoll {
    float weapon_damage_pct = 0.0F; // WEAPONDAMAGEPCT rung, resource units
    float soak_scale_pct = 0.0F; // SOAKSCALEPCT rung, resource units
    bool use_dps = false; // USEDPS rung flag
    // Native attackDesc+0x70 SPEED units (rollAttack 0x98(rsp) spill). The
    // production mapping is equipment.SPEED / 100 (calculateCombatStats);
    // research/skill-production-dispatch.md records the original stores.
    float dps_speed = 1.0F;
};
[[nodiscard]] OrdinaryDamageResult roll_skill_weapon_damage(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character,
    const EvaluatedDamageDefense& defense, const SkillWeaponRoll& roll,
    TorchlightRandom& random);

} // namespace torchlight
