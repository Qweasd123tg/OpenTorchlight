#include "torchlight/damage.hpp"

#include <algorithm>
#include <cmath>

namespace torchlight {

std::int32_t DamageDefense::effective(DamageType type) const noexcept {
    const auto index = static_cast<std::size_t>(type);
    if (index >= elemental_armor.size()) {
        return 0;
    }
    const auto base = type == DamageType::physical
                          ? natural_armor
                          : elemental_armor[index];
    if (base <= 0) {
        return 0;
    }
    const auto attribute_bonus = static_cast<std::int32_t>(std::ceil(
        static_cast<float>(base) *
        static_cast<float>(std::max(0, defense_attribute)) / 100.0F));
    return std::max(0, base + attribute_bonus);
}

DamageMitigation mitigate_damage(std::int32_t damage,
                                 std::int32_t maximum_damage,
                                 DamageType type, float armor_multiplier,
                                 const DamageDefense& defense,
                                 TorchlightRandom& random) noexcept {
    DamageMitigation result;
    result.incoming = std::max(0, damage);
    if (result.incoming == 0) {
        return result;
    }

    const auto maximum_defense = defense.effective(type);
    const auto minimum_defense = static_cast<std::int32_t>(
        std::ceil(static_cast<float>(maximum_defense) * 0.5F));
    result.rolled_defense = random.integer_between(
        minimum_defense, maximum_defense);

    const auto safe_maximum = std::max(1, maximum_damage);
    const auto multiplier = std::isfinite(armor_multiplier)
                                ? std::max(0.0F, armor_multiplier)
                                : 0.0F;
    const auto reduction = static_cast<std::int32_t>(
        static_cast<float>(result.rolled_defense) * multiplier *
        (static_cast<float>(result.incoming) /
         static_cast<float>(safe_maximum)));
    const auto reduced = result.incoming - reduction;
    result.applied = type == DamageType::physical
                         ? std::max(1, reduced)
                         : std::max(0, reduced);
    return result;
}

} // namespace torchlight
