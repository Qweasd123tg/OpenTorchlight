#include "torchlight/equipment.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
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

float optional_floating(const UnitDefinition& definition, const char16_t* name,
                        float fallback) {
    const auto* property = definition.find_property(name);
    if (property == nullptr) {
        return fallback;
    }
    if (property->type != AdmValueType::floating) {
        throw EquipmentError("Weapon combat property is not a float");
    }
    return std::get<float>(property->value);
}

} // namespace

std::string unit_model_path(const UnitDefinition& definition) {
    const auto text = [&](const char16_t* name) {
        const auto* property = definition.find_property(name);
        if (!property) return std::string{};
        if (property->type != AdmValueType::string &&
            property->type != AdmValueType::translation &&
            property->type != AdmValueType::note)
            throw EquipmentError("Item model property must be text");
        std::string result;
        for (const auto ch : std::get<std::u16string>(property->value)) {
            if (ch > 127) throw EquipmentError("Item model path is not ASCII");
            result.push_back(ch == u'\\' ? '/' : static_cast<char>(ch));
        }
        return result;
    };
    auto directory = text(u"RESOURCEDIRECTORY");
    auto mesh = text(u"MESHFILE");
    if (mesh.empty()) return {};
    if (!directory.empty() && directory.back() != '/') directory.push_back('/');
    auto path = directory + mesh;
    auto suffix = path.size() >= 5 ? path.substr(path.size() - 5) : std::string{};
    for (auto& ch : suffix) if (ch >= 'A' && ch <= 'Z') ch += 'a' - 'A';
    if (suffix != ".mesh") path += ".mesh";
    return path;
}

WeaponDelivery load_weapon_delivery(const UnitDefinition& definition) {
    // doWeaponSkill runs before fireMissiles. Conservative refusal is deliberate:
    // partial skill support must not become an extra ordinary physical attack.
    for (const auto& group : definition.root.groups)
        if (normalized(group.name) == u"SKILLS" || normalized(group.name) == u"SKILL")
            return WeaponDelivery::weapon_skill;
    if (const auto* missile = definition.find_property(u"MISSILE")) {
        if (missile->type != AdmValueType::string && missile->type != AdmValueType::translation &&
            missile->type != AdmValueType::note) throw EquipmentError("MISSILE must be text");
        if (!std::get<std::u16string>(missile->value).empty()) return WeaponDelivery::missile;
    }
    // Only names actually read by calculateCombatStats are supported. Do not
    // guess that similarly named mod fields mean the same damage channel.
    for (const auto* key : {u"DAMAGE_ELECTRICAL", u"DAMAGE_UNDEFINED"}) {
        const auto* value = definition.find_property(key);
        if (value && (value->type != AdmValueType::integer || std::get<std::int32_t>(value->value) != 0))
            return WeaponDelivery::unsupported_damage;
    }
    const auto percent = load_weapon_damage_percent(definition);
    const bool elemental = percent[2] > 0 || percent[3] > 0 || percent[4] > 0 || percent[5] > 0;
    if (elemental || (percent[0] >= 0 && percent[0] != 100)) return WeaponDelivery::direct_typed;
    return definition.find_property(u"DAMAGE_PHYSICAL") ? WeaponDelivery::direct_physical : WeaponDelivery::unverified;
}
const char* weapon_delivery_issue(WeaponDelivery delivery) noexcept {
    switch (delivery) {
        case WeaponDelivery::direct_physical: return "";
        case WeaponDelivery::direct_typed: return "";
        case WeaponDelivery::missile: return "weapon requires missile runtime";
        case WeaponDelivery::weapon_skill: return "weapon requires skill runtime";
        case WeaponDelivery::unsupported_damage: return "weapon uses unsupported damage allocation metadata";
        case WeaponDelivery::unverified: return "weapon delivery metadata is unverified";
    }
    return "invalid weapon delivery";
}

std::array<std::int32_t, 7> load_weapon_damage_percent(const UnitDefinition& definition) {
    std::array<std::int32_t, 7> result{};
    result[0] = optional_integer(definition, u"DAMAGE_PHYSICAL", -1);
    result[2] = optional_integer(definition, u"DAMAGE_FIRE", 0);
    result[3] = optional_integer(definition, u"DAMAGE_ICE", 0);
    result[4] = optional_integer(definition, u"DAMAGE_ELECTRIC", 0);
    result[5] = optional_integer(definition, u"DAMAGE_POISON", 0);
    return result;
}
WeaponDamageAllocation allocate_weapon_damage(std::int32_t graph_damage,
    const std::array<std::int32_t, 7>& percent) {
    if (graph_damage < 0 || percent[1] != 0 || percent[6] != 0)
        throw EquipmentError("unsupported weapon damage allocation");
    const auto factor = static_cast<float>(graph_damage) / 100.0F;
    const auto convert = [&](std::int32_t value) {
        const auto result = static_cast<float>(value) * factor;
        if (!std::isfinite(result) || result < 0 || static_cast<double>(result) > std::numeric_limits<std::int32_t>::max())
            throw EquipmentError("weapon allocation outside int32");
        return static_cast<std::int32_t>(result);
    };
    WeaponDamageAllocation result;
    result.physical = percent[0] < 0 ? graph_damage : convert(percent[0]);
    for (std::size_t i = 2; i <= 5; ++i) if (percent[i] > 0) result.bonus[i] = convert(percent[i]);
    return result;
}
void hydrate_weapon_damage(WeaponItem& item, const UnitDefinition& definition) {
    if (item.prototype.damage_percent) return; // Already split; never apply a second time.
    const auto percent = load_weapon_damage_percent(definition);
    const auto allocation = allocate_weapon_damage(item.maximum_damage, percent);
    const auto delivery = load_weapon_delivery(definition);
    item.maximum_damage = allocation.physical;
    item.minimum_damage = static_cast<std::int32_t>(std::ceil(static_cast<float>(allocation.physical) * 0.5F));
    item.damage_bonus = allocation.bonus;
    item.prototype.damage_percent = percent;
    item.prototype.delivery = delivery;
}
void hydrate_attack_damage(AttackDescription& attack, const UnitDefinition& definition) {
    if (attack.damage_allocation_known) return;
    const auto allocation = allocate_weapon_damage(attack.maximum_damage, load_weapon_damage_percent(definition));
    const auto delivery = load_weapon_delivery(definition);
    attack.maximum_damage = allocation.physical;
    attack.minimum_damage = static_cast<std::int32_t>(std::ceil(static_cast<float>(allocation.physical) * 0.5F));
    attack.damage_bonus = allocation.bonus;
    attack.damage_allocation_known = true;
    attack.delivery = delivery;
}

AttackDescription describe_weapon_attack(const WeaponItem& item, AttackHand hand) {
    AttackDescription result;
    result.hand = hand; result.source_guid = item.prototype.guid;
    result.traits = item.prototype.attack_traits;
    result.animation_prefix = weapon_attack_prefix(result.traits.family, hand);
    result.minimum_damage = item.minimum_damage; result.maximum_damage = item.maximum_damage;
    result.range = item.prototype.range; result.strike_range = item.prototype.strike_range;
    result.speed_denominator = static_cast<float>(item.prototype.speed) / 100.0F;
    result.equipment_ai_cooldown = item.prototype.ai_attack_cooldown;
    result.effects = item.prototype.attack_effects;
    result.delivery = item.prototype.delivery;
    result.damage_bonus = item.damage_bonus;
    result.damage_allocation_known = item.prototype.damage_percent.has_value();
    return result;
}

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

std::int32_t item_graph_stat(float graph_value, std::uint32_t scaled_percent,
                             std::int32_t heirloom_count, bool armor) {
    if (!std::isfinite(graph_value) || heirloom_count < 0)
        throw EquipmentError("Invalid item graph input");
    // Match original uint32 addition, then cvtsi2ss of the zero-extended value.
    const auto percent = scaled_percent + static_cast<std::uint32_t>(
        std::min(heirloom_count, 5) * 10);
    const float multiplier = static_cast<float>(percent) / 100.0F;
    const float value = std::ceil(graph_value * multiplier);
    if (!std::isfinite(value) || static_cast<double>(value) < std::numeric_limits<std::int32_t>::min() ||
        static_cast<double>(value) > std::numeric_limits<std::int32_t>::max())
        throw EquipmentError("Item graph result exceeds int32");
    const auto result = static_cast<std::int32_t>(value);
    return armor ? std::max(1, result) : result;
}

std::optional<ArmorItem> roll_armor_item(
    const MasterResourceRecord& resource, const UnitDefinition& definition,
    const StatGraph& armor_graph, TorchlightRandom& random,
    std::int32_t heirloom_count) {
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
    const auto armor = item_graph_stat(armor_graph.value(static_cast<float>(level)),
        static_cast<std::uint32_t>(scaled_percent), heirloom_count, true);

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

std::optional<WeaponPrototype> load_weapon_prototype(
    const MasterResourceRecord& resource, const UnitDefinition& definition,
    const StatGraph& damage_graph) {
    const auto* minimum = definition.find_property(u"MINDAMAGE");
    const auto* maximum = definition.find_property(u"MAXDAMAGE");
    const auto* range = definition.find_property(u"RANGE");
    if (minimum == nullptr || maximum == nullptr || range == nullptr) {
        return std::nullopt;
    }
    WeaponPrototype weapon;
    weapon.delivery = load_weapon_delivery(definition);
    weapon.damage_percent = load_weapon_damage_percent(definition);
    weapon.guid = resource.guid;
    weapon.name = resource.name;
    weapon.display_name = resource.display_name;
    weapon.unit_type = resource.unit_type;
    weapon.mesh_path = unit_model_path(definition);
    weapon.level = optional_integer(definition, u"LEVEL", 1);
    weapon.minimum_damage_percent = optional_integer(definition, u"MINDAMAGE", 0);
    weapon.maximum_damage_percent = optional_integer(definition, u"MAXDAMAGE", 0);
    weapon.rarity_damage_modifier = optional_integer(
        definition, u"RARITY_DMG_MOD", 100);
    weapon.speed_damage_modifier = optional_integer(
        definition, u"SPEED_DMG_MOD", 100);
    weapon.speed = optional_integer(definition, u"SPEED", 100);
    weapon.range = optional_floating(definition, u"RANGE", 0.0F);
    weapon.strike_range = optional_floating(
        definition, u"STRIKERANGE", weapon.range);
    weapon.base_weapon_damage = damage_graph.value(
        static_cast<float>(weapon.level));
    if (weapon.level < 1 || weapon.minimum_damage_percent < 0 ||
        weapon.maximum_damage_percent < weapon.minimum_damage_percent ||
        weapon.rarity_damage_modifier < 0 || weapon.speed_damage_modifier < 0 ||
        weapon.speed <= 0 ||
        !std::isfinite(weapon.range) || weapon.range < 0.0F ||
        !std::isfinite(weapon.strike_range) || weapon.strike_range < 0.0F ||
        !std::isfinite(weapon.base_weapon_damage) ||
        !(weapon.base_weapon_damage > 0.0F)) {
        throw EquipmentError("Weapon combat properties are invalid");
    }
    return weapon;
}

WeaponItem roll_weapon_item(const WeaponPrototype& prototype,
                            TorchlightRandom& random,
                            std::int32_t heirloom_count) {
    if (heirloom_count < 0) throw EquipmentError("Negative heirloom count");
    // original-code: calculateCombatStats @0x8815d8 calls the RNG BEFORE
    // choosing MAXDAMAGE for a previously inherited weapon. Do not skip its draw.
    const auto rolled = random.integer_between(prototype.minimum_damage_percent,
                                                prototype.maximum_damage_percent);
    const auto raw_damage = heirloom_count > 0 ? prototype.maximum_damage_percent : rolled;
    const auto scaled_percent = static_cast<std::int32_t>(
        static_cast<float>(raw_damage) *
        (static_cast<float>(prototype.rarity_damage_modifier) / 100.0F) *
        (static_cast<float>(prototype.speed_damage_modifier) / 100.0F));
    const auto maximum_damage = item_graph_stat(prototype.base_weapon_damage,
        static_cast<std::uint32_t>(scaled_percent), heirloom_count, false);
    WeaponItem item;
    item.prototype = prototype;
    const auto allocation = prototype.damage_percent ? allocate_weapon_damage(maximum_damage, *prototype.damage_percent)
        : WeaponDamageAllocation{maximum_damage, {}};
    item.maximum_damage = allocation.physical;
    item.damage_bonus = allocation.bonus;
    item.minimum_damage = static_cast<std::int32_t>(std::ceil(
        static_cast<float>(item.maximum_damage) * 0.5F));
    return item;
}

} // namespace torchlight
