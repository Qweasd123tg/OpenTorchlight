#include "torchlight/character_stats.hpp"
#include "torchlight/attack_action.hpp"
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace torchlight {
namespace {
void finite(std::initializer_list<float> values) {
    for (const auto value : values)
        if (!std::isfinite(value)) throw std::invalid_argument("nonfinite character stat input");
}
std::int32_t integer(float value) {
    if (!std::isfinite(value) || static_cast<double>(value) < std::numeric_limits<std::int32_t>::min() ||
        static_cast<double>(value) > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("character stat outside int32 domain");
    return static_cast<std::int32_t>(value);
}
std::int32_t sum(std::initializer_list<std::int64_t> values) {
    std::int64_t result = 0;
    for (const auto value : values) result += value;
    if (result < std::numeric_limits<std::int32_t>::min() || result > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("character stat integer overflow");
    return static_cast<std::int32_t>(result);
}
}
float evaluated_movement_speed(float base, float percent, float slow_resistance) {
    finite({base, percent, slow_resistance});
    if (base < 0) throw std::invalid_argument("negative base movement speed");
    if (percent < 0) percent *= 1.0F - std::clamp(slow_resistance / 100.0F, 0.0F, 1.0F);
    // Preserve mul -> div -> add; base * (1 + percent / 100) rounds differently.
    const auto result = (base * percent) / 100.0F + base;
    finite({result});
    return std::max(0.0F, result);
}
float evaluated_movement_speed(float base, const AttackEffects& effects) {
    return evaluated_movement_speed(base, effects.get(0x15), effects.get(0x8c));
}
std::int32_t evaluated_defense_attribute(std::int32_t base,
    float percent, float all_percent, float flat) {
    finite({percent, all_percent, flat});
    const auto bonus = integer(std::ceil(static_cast<float>(base) * ((all_percent + percent) / 100.0F)));
    return sum({base, bonus, integer(std::ceil(flat))});
}
std::int32_t evaluated_defense_attribute(std::int32_t base, const AttackEffects& effects) {
    return evaluated_defense_attribute(base, effects.get(0x11), effects.get(0x11, 6), effects.get(2));
}
std::int32_t evaluated_physical_armor(std::int32_t base_armor, std::int32_t defense,
    float armor_percent, float flat_armor, float degrade_armor, float owner_armor_percent) {
    finite({armor_percent, flat_armor, degrade_armor, owner_armor_percent});
    const auto percent = armor_percent / 100.0F + owner_armor_percent / 100.0F;
    const auto armor = sum({base_armor, integer(std::ceil(static_cast<float>(base_armor) * percent)),
        integer(std::ceil(flat_armor))});
    const auto attribute = integer(std::ceil(static_cast<float>(armor) * (static_cast<float>(defense) / 100.0F)));
    const auto result = sum({armor, attribute, -static_cast<std::int64_t>(integer(std::ceil(degrade_armor)))});
    return std::max(0, result);
}
std::int32_t evaluated_character_armor(std::int32_t base_armor,
    std::int32_t base_defense, const AttackEffects& effects) {
    return evaluated_physical_armor(base_armor, evaluated_defense_attribute(base_defense, effects),
        effects.get(0x17), effects.get(8), effects.get(0x42));
}
} // namespace torchlight
