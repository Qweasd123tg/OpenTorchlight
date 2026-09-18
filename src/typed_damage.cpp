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

OrdinaryDamagePlan ordinary_damage_plan(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character) {
    const auto base = ordinary_physical_damage(selected, loadout, character);
    OrdinaryDamagePlan result;
    result.channels[result.count++] = {DamageType::physical, base[0], base[1]};
    result.maximum = base[1]; result.minimum = base[0];
    const auto global = total_attack_effects(loadout, character);
    const bool weapon = selected.hand != AttackHand::innate;
    const auto attribute = combat_attribute(character, global, selected.traits.ranged);
    for (std::size_t i = 0; i < selected.damage_bonus.size(); ++i) {
        const auto bonus = selected.damage_bonus[i];
        const auto flat = checked(std::ceil(global.get(10, static_cast<std::uint8_t>(i))));
        if (bonus <= 0 && flat <= 0) continue;
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
        const auto maximum = add(enhanced, flat);
        // Negative raw contributions are not new healing semantics for attacks.
        if (maximum < 0) throw std::invalid_argument("negative ordinary channel damage");
        const auto low = minimum(maximum);
        result.channels[result.count++] = {static_cast<DamageType>(i), low, maximum};
        result.maximum = add(result.maximum, maximum);
        result.minimum = add(result.minimum, low);
    }
    return result;
}
OrdinaryDamageResult roll_ordinary_damage(const AttackDescription& selected,
    const AttackLoadout& loadout, const AttackCharacterValues& character,
    const EvaluatedDamageDefense& defense, TorchlightRandom& random) {
    if (!ordinary_delivery_supported(selected)) throw std::invalid_argument("unsupported ordinary damage delivery");
    const auto plan = ordinary_damage_plan(selected, loadout, character);
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
                channel.type, 1.0F, defense, staged);
        result.applied = add(result.applied, result.channels[i].applied);
    }
    random = staged; // Failed evaluation cannot leave a half-consumed stream.
    return result;
}
} // namespace torchlight
