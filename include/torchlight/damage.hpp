#pragma once

#include "torchlight/randomizer.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

namespace torchlight {

enum class DamageType : std::size_t {
    physical,
    magical,
    fire,
    ice,
    electric,
    poison,
    all,
    count,
};

struct DamageDefense {
    std::int32_t natural_armor = 0;
    std::int32_t defense_attribute = 0;
    std::array<std::int32_t, static_cast<std::size_t>(DamageType::count)>
        elemental_armor{};

    [[nodiscard]] std::int32_t effective(DamageType type) const noexcept;
};

struct DamageMitigation {
    std::int32_t incoming = 0;
    std::int32_t rolled_defense = 0;
    std::int32_t applied = 0;
};

[[nodiscard]] DamageMitigation mitigate_damage(
    std::int32_t damage, std::int32_t maximum_damage, DamageType type,
    float armor_multiplier, const DamageDefense& defense,
    TorchlightRandom& random) noexcept;

} // namespace torchlight
