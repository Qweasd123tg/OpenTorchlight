#include "torchlight/typed_damage.hpp"
#include "torchlight/character_stats.hpp"

#include <algorithm>
#include <cstring>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace torchlight {
namespace {
std::int32_t checked(float value) {
    if (!std::isfinite(value) || static_cast<double>(value) < std::numeric_limits<std::int32_t>::min() ||
        static_cast<double>(value) > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("damage arithmetic outside int32");
    return static_cast<std::int32_t>(value);
}
std::int32_t add(std::int32_t a, std::int32_t b) {
    const auto result = static_cast<std::int64_t>(a) + b;
    if (result < std::numeric_limits<std::int32_t>::min() || result > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("damage sum outside int32");
    return static_cast<std::int32_t>(result);
}
// Explicit cvttss2si semantics avoid C++ float->int UB for original 0/0
// in a pure-elemental weapon's zero physical base. No fast-math is permitted.
std::int32_t sse_trunc(float value) noexcept {
    if (!std::isfinite(value) || value < -2147483648.0F || value >= 2147483648.0F)
        return std::numeric_limits<std::int32_t>::min();
    return static_cast<std::int32_t>(value);
}
std::int32_t minimum(std::int32_t maximum) { return checked(std::ceil(static_cast<float>(maximum) * 0.5F)); }
std::int32_t combat_attribute(const AttackCharacterValues& c, const AttackEffects& e, bool ranged) {
    const auto base = ranged ? c.dexterity : c.strength;
    return add(add(base, checked(std::ceil(static_cast<float>(base) * e.get(ranged ? 0x48 : 0x47) / 100.0F))),
        checked(std::ceil(e.get(ranged ? 0x46 : 0x45))));
}
} // namespace

std::int32_t evaluated_magic(std::int32_t base, const AttackEffects& e) {
    // magic @0x8144c0: multiply before divide, two independent ceilings.
    return add(add(base, checked(std::ceil(static_cast<float>(base) * e.get(0x12) / 100.0F))),
        checked(std::ceil(e.get(3))));
}
EvaluatedDamageDefense evaluate_damage_defense(const DamageDefense& raw, const AttackEffects& e) {
    EvaluatedDamageDefense result;
    result.maximum[0] = evaluated_character_armor(raw.natural_armor, raw.defense_attribute, e);
    const auto def = evaluated_defense_attribute(raw.defense_attribute, e.get(0x11), e.get(0x11, 6), e.get(2));
    // gDAMAGE_DEFENSE_EFFECT_TYPES @0xfcdd40; slot 6 is actually effect 0.
    constexpr std::array<std::uint16_t, 7> flat_effects{35, 36, 37, 38, 39, 40, 0};
    for (std::size_t i = 0; i < result.maximum.size(); ++i) {
        const auto type = static_cast<std::uint8_t>(i);
        result.percent_taken[i] = checked(std::ceil(e.get(0x1a, type) + e.get(0x1a, 6)));
        if (i == 0) continue;
        // damageDefense @0x815910: preserve the fractional bucket until the
        // outer ceiling. Reusing physical AC prematurely rounds this value.
        const auto base = static_cast<float>(raw.elemental_armor[i]);
        const auto scaled = std::max(0.0F, base + ((e.get(0x17, type) + e.get(0x17, 6)) / 100.0F) * base);
        const auto bucket = scaled + e.get(flat_effects[i]);
        const auto attribute = checked(std::ceil((static_cast<float>(def) / 100.0F) * bucket));
        const auto degraded = checked(std::ceil(e.get(0x42)));
        const auto value = checked(std::ceil((static_cast<float>(attribute) + bucket) - static_cast<float>(degraded)));
        // modifyDamage converts the getter to float and back before clamping.
        result.maximum[i] = std::max(0, checked(static_cast<float>(value)));
    }
    return result;
}
DamageMitigation mitigate_evaluated_damage(std::int32_t damage, std::int32_t maximum_damage,
    DamageType type, float multiplier, const EvaluatedDamageDefense& defense, TorchlightRandom& random) noexcept {
    DamageMitigation result;
    const auto index = static_cast<std::size_t>(type);
    if (index >= defense.maximum.size() || damage < 0 || maximum_damage < 0 || !std::isfinite(multiplier) || multiplier < 0)
        return result; // Out-of-domain callers do not consume randomness.
    result.incoming = damage;
    const auto maximum = std::max(0, defense.maximum[index]);
    const auto low = sse_trunc(std::ceil(static_cast<float>(maximum) * 0.5F));
    result.rolled_defense = random.integer_between(low, maximum);
    // Original executes this even for incoming==maximum==0. Emulate x86
    // conversion/wrapping explicitly, rather than invent a minimum denominator.
    const auto ratio = static_cast<float>(damage) / static_cast<float>(maximum_damage);
    const auto reduction = sse_trunc(static_cast<float>(result.rolled_defense) * multiplier * ratio);
    const auto wrapped = static_cast<std::uint32_t>(damage) - static_cast<std::uint32_t>(reduction);
    std::int32_t remaining; std::memcpy(&remaining, &wrapped, sizeof(remaining));
    const auto value = static_cast<float>(remaining);
    const auto percent = static_cast<float>(defense.percent_taken[index]) / 100.0F;
    const auto applied = sse_trunc(percent * value + value);
    result.applied = type == DamageType::physical ? std::max(1, applied) : std::max(0, applied);
    return result;
}

namespace {
OrdinaryDamagePlan attack_damage_plan(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character,
    float fraction = 1.0F, bool use_dps = false, float speed = 1.0F) {
    // original-code: 0xfce530 is float bits 0x3f3bbbbc. Decimal 0.7333333F
    // is the adjacent float and changes ceil(99 / divisor) from 135 to 136.
    const float divisor = speed * 0x1.777778p-1F;
    if (use_dps && (!(divisor > 0.0F) || !std::isfinite(divisor)))
        throw std::invalid_argument("skill DPS speed must be positive");
    const auto scale = [fraction](std::int32_t value) {
        return fraction == 1.0F ? value : checked(static_cast<float>(value) * fraction);
    };
    const auto dps = [use_dps, divisor](std::int32_t value) {
        return use_dps ? checked(std::ceil(static_cast<float>(value) / divisor)) : value;
    };
    const auto base = ordinary_physical_damage(selected, loadout, character);
    const auto base_maximum = dps(scale(base[1]));
    const auto base_minimum = minimum(base_maximum); // @0x844180, after both scales
    OrdinaryDamagePlan result;
    result.channels[result.count++] = {DamageType::physical, base_minimum, base_maximum};
    result.maximum = base_maximum; result.minimum = base_minimum;
    const auto global = total_attack_effects(loadout, character);
    const bool weapon = selected.hand != AttackHand::innate;
    const auto attribute = combat_attribute(character, global, selected.traits.ranged);
    for (std::size_t i = 0; i < selected.damage_bonus.size(); ++i) {
        const auto raw_bonus = selected.damage_bonus[i];
        const auto flat = checked(std::ceil(global.get(10, static_cast<std::uint8_t>(i))));
        if (raw_bonus <= 0 && flat <= 0) continue;
        // @0x8442bc and @0x844738 scale the raw bonus before enhancement.
        const auto bonus = scale(raw_bonus);
        // rollAttack @0x8442db..0x844524 / @0x844838..0x844d8b.
        // Unlike maxDamage, these additions include both hands' evaluated effects.
        auto percent = global.get(0x19, static_cast<std::uint8_t>(i)) / 100.0F;
        percent = global.get(0x19, 6) / 100.0F + percent;
        percent = global.get(selected.traits.ranged ? 0x10 : 0x0f) / 100.0F + percent;
        percent += static_cast<float>(attribute) / 100.0F;
        if (weapon && selected.traits.melee_specialization) percent += global.get(0x63) / 100.0F;
        if (weapon && selected.traits.ranged_specialization) percent += global.get(0x66) / 100.0F;
        if (weapon && selected.traits.shared_specialization) percent += global.get(0x67) / 100.0F;
        if (weapon && i > 0) percent += static_cast<float>(evaluated_magic(character.magic, global)) / 100.0F;
        if (loadout.left && loadout.right) percent += global.get(0x58) / 100.0F;
        const auto enhanced = add(bonus, checked(std::ceil(static_cast<float>(bonus) * percent)));
        // The original's two passes differ: total maximum adds flat AFTER
        // DPS (@0x8444e2..0x84451e), channel roll BEFORE (@0x844958..0x844995).
        // Preserve this distinction for the elemental mitigation denominator.
        const auto maximum = dps(add(enhanced, flat));
        // Negative raw contributions are not new healing semantics for attacks.
        if (maximum < 0) throw std::invalid_argument("negative ordinary channel damage");
        const auto low = minimum(maximum);
        result.channels[result.count++] = {static_cast<DamageType>(i), low, maximum};
        result.maximum = add(result.maximum, add(dps(enhanced), flat));
        result.minimum = add(result.minimum, low);
    }
    return result;
}
} // namespace
OrdinaryDamagePlan ordinary_damage_plan(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character) {
    return attack_damage_plan(selected, loadout, character);
}
namespace {
// Shared channel roll/mitigation loop for the ordinary HIT branch and the
// missile impact twin (gates differ; the math is one implementation).
OrdinaryDamageResult roll_planned_damage(const OrdinaryDamagePlan& plan,
    const EvaluatedDamageDefense& defense, TorchlightRandom& random, float armor_multiplier) {
    auto staged = random;
    OrdinaryDamageResult result;
    result.count = plan.count; result.maximum = plan.maximum;
    for (std::size_t i = 0; i < plan.count; ++i) {
        const auto& channel = plan.channels[i];
        result.types[i] = channel.type;
        const auto rolled = staged.integer_between(channel.minimum, channel.maximum);
        result.rolled = add(result.rolled, rolled);
        if (i == 0 || rolled > 0)
            result.channels[i] = mitigate_evaluated_damage(rolled, i == 0 ? rolled : plan.maximum,
                channel.type, armor_multiplier, defense, staged);
        result.applied = add(result.applied, result.channels[i].applied);
    }
    random = staged; // Failed evaluation cannot leave a half-consumed stream.
    return result;
}
} // namespace
OrdinaryDamageResult roll_ordinary_damage(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character,
    const EvaluatedDamageDefense& defense, TorchlightRandom& random) {
    if (!ordinary_delivery_supported(selected)) throw std::invalid_argument("unsupported ordinary damage delivery");
    return roll_planned_damage(ordinary_damage_plan(selected, loadout, character), defense, random,
                               1.0F);
}
// Missile impact delivery (original doDamageToCharacter role at impact time;
// research/missile-runtime.md §5): the missile carries the wielding weapon's
// ordinary channels to the victim, rolled per victim like the direct path.
// The original graph-level decomposition (graph value at target stat,
// per-missile random range/multiplier) stays open — this maps the observable
// contract (wand deals wand damage), not the formula. The ordinary gate
// above is untouched: silent substitution stays forbidden.
OrdinaryDamageResult roll_missile_impact_damage(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character,
    const EvaluatedDamageDefense& defense, TorchlightRandom& random) {
    if (selected.delivery != WeaponDelivery::missile)
        throw std::invalid_argument("missile impact roll needs missile delivery");
    return roll_planned_damage(ordinary_damage_plan(selected, loadout, character), defense, random,
                               1.0F);
}
OrdinaryDamageResult roll_skill_weapon_damage(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character,
    const EvaluatedDamageDefense& defense, const SkillWeaponRoll& roll,
    TorchlightRandom& random) {
    // Reachable rollAttack slice for the skill missile path. The caller owns
    // weapon selection and the performAttack preconditions (single ranged
    // weapon, live foe, in range): this maps the roll, not the gates.
    // original-code: @0x844150 compares the fraction with 1, not 0;
    // @0x845338 truncates base*frac. See research/skill-weapon-oracle.md.
    const float fraction = std::max(0.0F, roll.weapon_damage_pct / 100.0F);
    const auto plan = attack_damage_plan(selected, loadout, character,
                                        fraction, roll.use_dps, roll.dps_speed);
    // SOAK @0x844226/@0x844a05: the mitigate multiplier (ctor-role fraction).
    const float soak = std::max(0.0F, roll.soak_scale_pct / 100.0F);
    return roll_planned_damage(plan, defense, random, soak);
}
} // namespace torchlight
