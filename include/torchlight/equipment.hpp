#pragma once

#include "torchlight/attack_action.hpp"
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

struct WeaponPrototype {
    std::int64_t guid = 0;
    std::u16string name;
    std::u16string display_name;
    std::u16string unit_type;
    std::string mesh_path;
    std::int32_t level = 1;
    std::int32_t minimum_damage_percent = 0;
    std::int32_t maximum_damage_percent = 0;
    std::int32_t rarity_damage_modifier = 100;
    std::int32_t speed_damage_modifier = 100;
    std::int32_t speed = 100;
    float range = 0.0F;
    float strike_range = 0.0F;
    float base_weapon_damage = 0.0F;
    WeaponAttackTraits attack_traits;
    AttackHand attack_hand = AttackHand::right;
    AttackEffects attack_effects;
    float ai_attack_cooldown = 0.0F;
};

struct WeaponItem {
    WeaponPrototype prototype;
    std::int32_t minimum_damage = 1;
    std::int32_t maximum_damage = 1;
};

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
    AttackEffects attack_effects;
};

[[nodiscard]] AttackDescription describe_weapon_attack(const WeaponItem& item, AttackHand hand);

// Resource-derived path only; does not load geometry or invent a replacement.
[[nodiscard]] std::string unit_model_path(const UnitDefinition& definition);

[[nodiscard]] std::optional<ArmorSlot> armor_slot_for_unit_type(
    std::u16string_view unit_type) noexcept;

// Recreates CEquipment::calculateCombatStats and setGraphAC for armor items.
// rarity_rank is the generated item's quality rank (0..5), separate from the
// RARITY weight stored in its data file.
[[nodiscard]] std::optional<ArmorItem> roll_armor_item(
    const MasterResourceRecord& resource, const UnitDefinition& definition,
    const StatGraph& armor_graph, TorchlightRandom& random,
    std::int32_t rarity_rank = 0);

[[nodiscard]] std::optional<WeaponPrototype> load_weapon_prototype(
    const MasterResourceRecord& resource, const UnitDefinition& definition,
    const StatGraph& damage_graph);

[[nodiscard]] WeaponItem roll_weapon_item(
    const WeaponPrototype& prototype, TorchlightRandom& random,
    std::int32_t rarity_rank = 0) noexcept;

} // namespace torchlight
