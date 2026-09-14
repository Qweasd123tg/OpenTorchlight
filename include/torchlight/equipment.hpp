#pragma once

#include "torchlight/damage.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/randomizer.hpp"
#include "torchlight/stat_graph.hpp"
#include "torchlight/unit_definition.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace torchlight {

enum class ArmorSlot : std::size_t {
    chest,
    boots,
    gloves,
    helmet,
    shoulders,
    belt,
    shield,
    count,
};

struct ArmorItem {
    std::int64_t guid = 0;
    std::u16string name;
    std::u16string display_name;
    ArmorSlot slot = ArmorSlot::chest;
    std::int32_t level = 1;
    std::int32_t armor = 0;
    DamageDefense damage_defense;
};

[[nodiscard]] std::optional<ArmorSlot> armor_slot_for_unit_type(
    std::u16string_view unit_type) noexcept;

// Recreates CEquipment::calculateCombatStats and setGraphAC for armor items.
// rarity_rank is the generated item's quality rank (0..5), separate from the
// RARITY weight stored in its data file.
[[nodiscard]] std::optional<ArmorItem> roll_armor_item(
    const MasterResourceRecord& resource, const UnitDefinition& definition,
    const StatGraph& armor_graph, TorchlightRandom& random,
    std::int32_t rarity_rank = 0);

} // namespace torchlight
