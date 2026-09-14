#include "torchlight/equipment.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <stdexcept>

namespace torchlight {
namespace {

class EquipmentError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

std::u16string normalized(std::u16string_view value) {
    std::u16string result;
    result.reserve(value.size());
    for (const auto character : value) {
        result.push_back(character >= u'a' && character <= u'z'
                             ? static_cast<char16_t>(character - u'a' + u'A')
                             : character);
    }
    return result;
}

std::int32_t optional_integer(const UnitDefinition& definition,
                              const char16_t* name,
                              std::int32_t fallback) {
    const auto* property = definition.find_property(name);
    if (property == nullptr) {
        return fallback;
    }
    if (property->type != AdmValueType::integer) {
        throw EquipmentError("Armor combat property is not an integer");
    }
    return std::get<std::int32_t>(property->value);
}

} // namespace

std::optional<ArmorSlot> armor_slot_for_unit_type(
    std::u16string_view unit_type) noexcept {
    const auto type = normalized(unit_type);
    if (type.find(u"CHEST ARMOR") != std::u16string::npos) {
        return ArmorSlot::chest;
    }
    if (type.find(u"BOOTS") != std::u16string::npos) {
        return ArmorSlot::boots;
    }
    if (type.find(u"GLOVES") != std::u16string::npos) {
        return ArmorSlot::gloves;
    }
    if (type.find(u"HELMET") != std::u16string::npos) {
        return ArmorSlot::helmet;
    }
    if (type.find(u"SHOULDER ARMOR") != std::u16string::npos) {
        return ArmorSlot::shoulders;
    }
    if (type.find(u"BELT") != std::u16string::npos) {
        return ArmorSlot::belt;
    }
    if (type.find(u"SHIELD") != std::u16string::npos) {
        return ArmorSlot::shield;
    }
    return std::nullopt;
}

std::optional<ArmorItem> roll_armor_item(
    const MasterResourceRecord& resource, const UnitDefinition& definition,
    const StatGraph& armor_graph, TorchlightRandom& random,
    std::int32_t rarity_rank) {
    const auto slot = armor_slot_for_unit_type(resource.unit_type);
    if (!slot) {
        return std::nullopt;
    }
    const auto minimum_percent = optional_integer(definition, u"ARMORMIN", 0);
    const auto maximum_percent = optional_integer(
        definition, u"ARMORMAX", minimum_percent);
    if (minimum_percent <= 0 && maximum_percent <= 0) {
        return std::nullopt;
    }
    const auto low = std::min(minimum_percent, maximum_percent);
    const auto high = std::max(minimum_percent, maximum_percent);
    const auto rolled_percent = random.integer_between(low, high);
    const auto rarity_modifier = optional_integer(
        definition, u"RARITY_AMR_MOD", 100);
    const auto special_modifier = optional_integer(
        definition, u"SPECIAL_AMR_MOD", 100);
    const auto scaled_percent = static_cast<std::int32_t>(
        static_cast<float>(rolled_percent) *
        (static_cast<float>(rarity_modifier) / 100.0F) *
        (static_cast<float>(special_modifier) / 100.0F));
    const auto level = std::max(1, optional_integer(definition, u"LEVEL", 1));
    const auto graph_percent = scaled_percent +
        std::clamp(rarity_rank, 0, 5) * 10;
    const auto armor = std::max(1, static_cast<std::int32_t>(std::ceil(
        armor_graph.value(static_cast<float>(level)) *
        static_cast<float>(graph_percent) / 100.0F)));

    ArmorItem item;
    item.guid = resource.guid;
    item.name = resource.name;
    item.display_name = resource.display_name;
    item.slot = *slot;
    item.level = level;
    item.armor = armor;

    constexpr std::array<const char16_t*, 7> properties{
        u"ARMOR_PHYSICAL", u"ARMOR_MAGICAL", u"ARMOR_FIRE", u"ARMOR_ICE",
        u"ARMOR_ELECTRIC", u"ARMOR_POISON", u"ARMOR_ALL"};
    const auto all_percent = optional_integer(definition, u"ARMOR_ALL", 0);
    for (std::size_t index = 0; index + 1U < properties.size(); ++index) {
        const auto percent = optional_integer(definition, properties[index], 0) +
                             all_percent;
        const auto value = std::max(0, static_cast<std::int32_t>(std::ceil(
            static_cast<float>(armor) * static_cast<float>(percent) / 100.0F)));
        if (index == static_cast<std::size_t>(DamageType::physical)) {
            item.damage_defense.natural_armor = value;
        } else {
            item.damage_defense.elemental_armor[index] = value;
        }
    }
    return item;
}

} // namespace torchlight
