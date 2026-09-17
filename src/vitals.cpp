#include "torchlight/vitals.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace torchlight {
namespace {
std::optional<float> rate(const AdmGroup& group, const char16_t* name) {
    const auto* property = group.find_property(name);
    if (!property) return std::nullopt;
    double value = 0;
    switch (property->type) {
    case AdmValueType::floating: value = std::get<float>(property->value); break;
    case AdmValueType::double_precision: value = std::get<double>(property->value); break;
    case AdmValueType::integer: value = std::get<std::int32_t>(property->value); break;
    case AdmValueType::unsigned_integer: value = std::get<std::uint32_t>(property->value); break;
    case AdmValueType::integer64: value = static_cast<double>(std::get<std::int64_t>(property->value)); break;
    default: throw std::invalid_argument("GLOBALS recharge rate is not numeric");
    }
    if (!std::isfinite(value) || std::abs(value) > std::numeric_limits<float>::max())
        throw std::invalid_argument("GLOBALS recharge rate is not finite float32");
    return static_cast<float>(value);
}
std::int32_t checked(float value) {
    if (!std::isfinite(value) || static_cast<double>(value) < std::numeric_limits<std::int32_t>::min() ||
        static_cast<double>(value) > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("invalid evaluated health contribution");
    return static_cast<std::int32_t>(value);
}
}
void validate_vital_recovery_rules(const VitalRecoveryRules& rules) {
    for (const auto value : {rules.health_percent_per_second, rules.pet_health_percent_per_second,
                             rules.mana_percent_per_second})
        if (value && !std::isfinite(*value))
            throw std::invalid_argument("nonfinite recharge rule");
}
VitalRecoveryRules parse_vital_recovery_rules(const AdmDocument& document) {
    if (document.root.name != u"GLOBALS")
        throw std::invalid_argument("recharge rules require GLOBALS root");
    return {rate(document.root, u"HP_RECHARGE_RATE"),
            rate(document.root, u"PET_HP_RECHARGE_RATE"),
            rate(document.root, u"MANA_RECHARGE_RATE")};
}
VitalRecoveryRules load_vital_recovery_rules(const PakArchive& archive) {
    const auto* entry = archive.find_normalized("media/globals.dat.adm");
    if (!entry) return {};
    return parse_vital_recovery_rules(parse_adm(archive.read(*entry)));
}
std::int32_t evaluated_maximum_health(std::int32_t raw_base, std::int32_t growth,
                                     const AttackEffects& effects) {
    const auto wide = static_cast<std::int64_t>(raw_base) + growth;
    if (wide < std::numeric_limits<std::int32_t>::min() || wide > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("health base/growth overflow");
    const auto base = std::max(1, static_cast<std::int32_t>(wide));
    const auto percent = checked(std::ceil(static_cast<float>(base) * (effects.get(0x14) / 100.0F)));
    const auto flat = checked(std::ceil(effects.get(5)));
    const auto total = static_cast<std::int64_t>(base) + percent + flat;
    if (total < 1 || total > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("invalid evaluated maximum health");
    return static_cast<std::int32_t>(total);
}
float evaluated_health_rate(const AttackEffects& effects) noexcept {
    auto damage = effects.get(0x34);
    if (damage > 0) damage = -damage;
    return (effects.get(0x7c) + effects.get(7)) + damage;
}
float evaluated_mana_rate(const AttackEffects& effects) noexcept {
    return effects.get(0x7b) + effects.get(6);
}
namespace {
std::optional<float> advance(float current, float maximum,
    std::optional<float> percent, float flat, float seconds, bool health) noexcept {
    if (!std::isfinite(current) || !std::isfinite(maximum) || maximum < 0 || current < 0 || current > maximum ||
        !std::isfinite(seconds) || seconds < 0 || !std::isfinite(flat) ||
        (percent && !std::isfinite(*percent))) return std::nullopt;
    if (health && maximum < 1) return std::nullopt;
    if (seconds == 0) return current;
    const auto apply = [maximum, health](float value, float delta) {
        if (health && value <= 0 && delta > 0 && delta < maximum) return value;
        return std::clamp(value + delta, 0.0F, maximum);
    };
    if (percent) {
        const auto delta = ((maximum / 100.0F) * *percent) * seconds;
        const auto value = current + delta;
        if (!std::isfinite(delta) || !std::isfinite(value)) return std::nullopt;
        current = apply(current, delta);
    }
    const auto delta = flat * seconds;
    const auto value = current + delta;
    if (!std::isfinite(delta) || !std::isfinite(value)) return std::nullopt;
    return apply(current, delta);
}
} // namespace
std::optional<float> advance_vital(float current, float maximum,
    std::optional<float> percent, float flat, float seconds) noexcept {
    return advance(current, maximum, percent, flat, seconds, false);
}
std::optional<float> advance_health(float current, float maximum,
    std::optional<float> percent, float flat, float seconds) noexcept {
    return advance(current, maximum, percent, flat, seconds, true);
}
} // namespace torchlight
