#include "torchlight/player.hpp"

#include "torchlight/ogre_mesh.hpp"
#include "torchlight/stat_graph.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <string_view>

namespace torchlight {
namespace {

class PlayerError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

const AdmProperty& required(const UnitDefinition& definition, const char16_t* name) {
    const auto* property = definition.find_property(name);
    if (property == nullptr) {
        throw PlayerError("Playable player property is missing");
    }
    return *property;
}

const std::u16string& text(const UnitDefinition& definition, const char16_t* name) {
    const auto& property = required(definition, name);
    if (property.type != AdmValueType::string && property.type != AdmValueType::translation &&
        property.type != AdmValueType::note) {
        throw PlayerError("Playable player text property has the wrong type");
    }
    return std::get<std::u16string>(property.value);
}

float floating(const UnitDefinition& definition, const char16_t* name) {
    const auto& property = required(definition, name);
    if (property.type != AdmValueType::floating) {
        throw PlayerError("Playable player float property has the wrong type");
    }
    return std::get<float>(property.value);
}

float optional_floating(const UnitDefinition& definition, const char16_t* name,
                        float fallback) {
    const auto* property = definition.find_property(name);
    if (property == nullptr) {
        return fallback;
    }
    if (property->type != AdmValueType::floating) {
        throw PlayerError("Playable player optional float has the wrong type");
    }
    return std::get<float>(property->value);
}

std::int32_t integer(const UnitDefinition& definition, const char16_t* name) {
    const auto& property = required(definition, name);
    if (property.type != AdmValueType::integer) {
        throw PlayerError("Playable player integer property has the wrong type");
    }
    return std::get<std::int32_t>(property.value);
}

bool is_text(AdmValueType type) noexcept {
    return type == AdmValueType::string || type == AdmValueType::translation ||
           type == AdmValueType::note;
}

std::int32_t numeric_integer(const AdmProperty& property) {
    switch (property.type) {
    case AdmValueType::integer:
        return std::get<std::int32_t>(property.value);
    case AdmValueType::floating:
        return static_cast<std::int32_t>(std::get<float>(property.value));
    case AdmValueType::double_precision:
        return static_cast<std::int32_t>(std::get<double>(property.value));
    default:
        throw PlayerError("Passive player effect value is not numeric");
    }
}

std::array<std::int32_t, 2> passive_armor_bonus(
    const UnitDefinition& definition) {
    std::array<std::int32_t, 2> result{};
    for (const auto& group : definition.root.groups) {
        if (group.name != u"EFFECT") {
            continue;
        }
        const auto* activation = group.find_property(u"ACTIVATION");
        const auto* duration = group.find_property(u"DURATION");
        const auto* type = group.find_property(u"TYPE");
        if (activation == nullptr || duration == nullptr || type == nullptr ||
            !is_text(activation->type) || !is_text(duration->type) ||
            !is_text(type->type) ||
            std::get<std::u16string>(activation->value) != u"PASSIVE" ||
            std::get<std::u16string>(duration->value) != u"ALWAYS" ||
            std::get<std::u16string>(type->value) != u"ARMOR BONUS") {
            continue;
        }
        const auto* minimum = group.find_property(u"MIN");
        const auto* maximum = group.find_property(u"MAX");
        if (minimum == nullptr && maximum == nullptr) {
            continue;
        }
        const auto low = numeric_integer(minimum != nullptr ? *minimum : *maximum);
        const auto high = numeric_integer(maximum != nullptr ? *maximum : *minimum);
        result[0] += std::min(low, high);
        result[1] += std::max(low, high);
    }
    return result;
}

std::optional<std::pair<std::u16string, AttackHand>> starting_weapon_name(const UnitDefinition& definition) {
    for (auto group = definition.root.groups.rbegin();
         group != definition.root.groups.rend(); ++group) {
        if (group->name != u"EQUIPMENT") {
            continue;
        }
        for (const auto slot : {u"RIGHTHAND", u"LEFTHAND"}) {
            const auto* property = group->find_property(slot);
            if (property == nullptr) {
                continue;
            }
            if (property->type != AdmValueType::string &&
                property->type != AdmValueType::translation &&
                property->type != AdmValueType::note) {
                throw PlayerError("Starting equipment slot is not text");
            }
            return std::make_pair(std::get<std::u16string>(property->value),
                                  std::u16string_view(slot) == u"LEFTHAND" ? AttackHand::left : AttackHand::right);
        }
    }
    return std::nullopt;
}

std::string ascii(std::u16string_view value) {
    std::string result;
    result.reserve(value.size());
    for (const auto character : value) {
        if (character > 0x7fU) {
            throw PlayerError("Playable player resource path is not ASCII");
        }
        result.push_back(character == u'\\' ? '/' : static_cast<char>(character));
    }
    return result;
}

std::optional<std::string> optional_resource_path(
    const PakArchive& archive, const UnitDefinition& definition,
    const char16_t* name) {
    const auto* property = definition.find_property(name);
    if (property == nullptr) {
        return std::nullopt;
    }
    if (!is_text(property->type)) {
        throw PlayerError("Playable player wardrobe property is not text");
    }
    const auto path = ascii(std::get<std::u16string>(property->value));
    if (path.empty()) {
        return std::nullopt;
    }
    const auto* entry = archive.find_normalized(path);
    if (entry == nullptr) {
        throw PlayerError("Playable player wardrobe texture is absent from pak.zip: " + path);
    }
    return entry->name;
}

void add_mesh_counts(const OgreMesh& mesh, FixedSceneGeometry& geometry) {
    if (mesh.shared_geometry) {
        geometry.unique_vertex_count += mesh.shared_geometry->vertex_count;
    }
    for (const auto& submesh : mesh.submeshes) {
        geometry.unique_index_count += submesh.indices.size();
        if (submesh.geometry) {
            geometry.unique_vertex_count += submesh.geometry->vertex_count;
        }
    }
}

} // namespace

std::vector<PlayerPrototype> load_playable_players(const PakArchive& archive,
                                                   const MasterResourceIndex& resources,
                                                   UnitDefinitionLoader& definitions) {
    std::vector<PlayerPrototype> result;
    const auto recovery_rules = load_vital_recovery_rules(archive);
    const UnitTypeHierarchy attack_hierarchy(archive);
    const auto attack_catalog = AttackEffectCatalog::discover(archive);
    const StatGraph damage_graph(
        archive, "media/graphs/stats/BASE_WEAPON_DAMAGE.DAT.adm");
    for (const auto& record : resources.records()) {
        if (record.kind != MasterResourceKind::player || record.do_not_create) {
            continue;
        }
        const auto definition = definitions.load(record);
        if (definition->find_property(u"RESOURCEDIRECTORY") == nullptr ||
            definition->find_property(u"MESHFILE") == nullptr) {
            continue;
        }
        PlayerPrototype player;
        player.guid = record.guid;
        player.progression_rules = load_progression_rules(archive, *definition);
        player.name = text(*definition, u"NAME");
        player.display_name = text(*definition, u"DISPLAYNAME");
        auto directory = ascii(text(*definition, u"RESOURCEDIRECTORY"));
        if (!directory.empty() && directory.back() != '/') {
            directory.push_back('/');
        }
        player.mesh_path = directory + ascii(text(*definition, u"MESHFILE")) + ".mesh";
        const auto* mesh = archive.find_normalized(player.mesh_path);
        if (mesh == nullptr) {
            throw PlayerError("Playable player mesh is absent from pak.zip: " + player.mesh_path);
        }
        player.mesh_path = mesh->name;
        // CWardrobe stores CHEST, GLOVES and BOOTS in slot order and composites
        // their base images over WARDROBE_BASE in update(nullptr).
        for (const auto* property :
             {u"WARDROBE_BASE", u"CHEST_BASE", u"GLOVES_BASE", u"BOOTS_BASE"}) {
            if (auto path = optional_resource_path(archive, *definition, property)) {
                player.wardrobe_texture_layers.push_back(std::move(*path));
            }
        }
        player.recovery_rules = recovery_rules;
        player.walking_speed = floating(*definition, u"WALKINGSPEED");
        player.running_speed = floating(*definition, u"RUNNINGSPEED");
        player.attack_speed = floating(*definition, u"ATTACKSPEED");
        player.weapon_scale = optional_floating(*definition, u"WEAPON_SCALE", 1.0F);
        player.reach_bonus = floating(*definition, u"REACH_BONUS");
        const auto health_graph_name = ascii(text(*definition, u"HEALTH_GRAPH"));
        const StatGraph health_graph(
            archive, "media/graphs/stats/" + health_graph_name + ".DAT.adm");
        const auto health_scale = health_graph.value(1.0F);
        const auto minimum_health_percent = floating(*definition, u"MINHP");
        const auto maximum_health_percent = floating(*definition, u"MAXHP");
        player.minimum_health = health_scale *
            std::min(minimum_health_percent, maximum_health_percent) / 100.0F;
        player.maximum_health = health_scale *
            std::max(minimum_health_percent, maximum_health_percent) / 100.0F;
        player.starting_gold = definition->find_property(u"GOLD") ?
            std::max(0, integer(*definition, u"GOLD")) : 0;
        const auto mana_name = definition->find_property(u"MANA_GRAPH") ?
            ascii(text(*definition, u"MANA_GRAPH")) : std::string("MANA_PLAYER_DESTROYER");
        const auto mana_path = "media/graphs/stats/" + mana_name + ".DAT.adm";
        if (!mana_name.empty() && archive.find_normalized(mana_path)) {
            const auto mana = std::ceil(StatGraph(archive, mana_path).value(1.0F));
            if (!std::isfinite(mana) || static_cast<double>(mana) < std::numeric_limits<std::int32_t>::min() ||
                static_cast<double>(mana) > std::numeric_limits<std::int32_t>::max())
                throw PlayerError("Playable player mana exceeds int32");
            player.base_mana = static_cast<std::int32_t>(mana);
        }
        player.minimum_damage = integer(*definition, u"MINDAMAGE");
        player.maximum_damage = integer(*definition, u"MAXDAMAGE");
        player.strength = integer(*definition, u"STRENGTH");
        player.dexterity = integer(*definition, u"DEXTERITY");
        player.magic = integer(*definition, u"MAGIC");
        player.defense = integer(*definition, u"DEFENSE");
        player.attacks.innate.push_back(load_innate_attack(*definition, player.minimum_damage, player.maximum_damage));
        player.attacks.no_unarmed_attacks = attack_unit_bool(*definition, u"NO_UNARMED_ATTACKS", false);
        player.attacks.use_weapon_damage = attack_unit_bool(*definition, u"USEWEAPONDAMAGE", true);
        player.attack_character = load_attack_character_values(*definition, attack_catalog ? &*attack_catalog : nullptr);
        player.damage_defense.natural_armor = integer(*definition, u"ARMOR");
        player.damage_defense.defense_attribute = player.defense;
        const auto armor_bonus = passive_armor_bonus(*definition);
        player.minimum_armor_bonus = armor_bonus[0];
        player.maximum_armor_bonus = armor_bonus[1];
        if (!std::isfinite(player.minimum_health) ||
            !std::isfinite(player.maximum_health) ||
            player.minimum_health <= 0.0F ||
            player.maximum_health < player.minimum_health) {
            throw PlayerError("Playable player health is invalid");
        }
        if (const auto weapon_name = starting_weapon_name(*definition)) {
            const auto* record = resources.find_case_insensitive(
                MasterResourceKind::item, weapon_name->first);
            if (record == nullptr || record->do_not_create ||
                record->create_as != u"EQUIPMENT") {
                throw PlayerError("Starting weapon is absent from equipment resources");
            }
            const auto weapon_definition = definitions.load(*record);
            player.starting_weapon = load_weapon_prototype(
                *record, *weapon_definition, damage_graph);
            if (!player.starting_weapon) {
                throw PlayerError("Starting equipment is not a weapon");
            }
            player.starting_weapon->attack_traits = weapon_attack_traits(record->unit_type, attack_hierarchy);
            player.starting_weapon->attack_hand = weapon_name->second;
            player.starting_weapon->attack_effects = load_constant_attack_effects(
                *weapon_definition, attack_catalog ? &*attack_catalog : nullptr);
            player.starting_weapon->ai_attack_cooldown = optional_floating(*weapon_definition, u"AI_ATTACKCOOLDOWN", 0);
            auto weapon_directory =
                ascii(text(*weapon_definition, u"RESOURCEDIRECTORY"));
            if (!weapon_directory.empty() && weapon_directory.back() != '/') {
                weapon_directory.push_back('/');
            }
            auto weapon_file = ascii(text(*weapon_definition, u"MESHFILE"));
            if (weapon_file.size() < 5U ||
                weapon_file.substr(weapon_file.size() - 5U) != ".mesh") {
                weapon_file += ".mesh";
            }
            const auto* weapon_mesh =
                archive.find_normalized(weapon_directory + weapon_file);
            if (weapon_mesh == nullptr) {
                throw PlayerError("Starting weapon mesh is absent from pak.zip");
            }
            player.starting_weapon->mesh_path = weapon_mesh->name;
        }
        result.push_back(std::move(player));
    }
    return result;
}

void append_player_geometry(const PakArchive& archive, const PlayerPrototype& player,
                            const std::array<float, 3>& position,
                            FixedSceneGeometry& geometry) {
    const auto* entry = archive.find_normalized(player.mesh_path);
    if (entry == nullptr) {
        throw PlayerError("Playable player mesh disappeared from pak.zip");
    }
    SceneMeshResource resource;
    resource.guid = player.guid;
    resource.source_path = entry->name;
    resource.texture_layers = player.wardrobe_texture_layers;
    resource.mesh = parse_ogre_mesh(archive.read(*entry));
    add_mesh_counts(resource.mesh, geometry);
    const auto mesh_index = geometry.meshes.size();
    geometry.meshes.push_back(std::move(resource));
    LayoutWorldTransform transform;
    transform.position = position;
    geometry.instances.push_back(
        SceneMeshInstance{0, 0, mesh_index, transform, 0, true, std::nullopt});
}

std::optional<std::size_t> append_player_weapon_geometry(
    const PakArchive& archive, const PlayerPrototype& player,
    const std::array<float, 3>& position, FixedSceneGeometry& geometry) {
    if (!player.starting_weapon || player.starting_weapon->mesh_path.empty()) {
        return std::nullopt;
    }
    const auto* entry = archive.find_normalized(player.starting_weapon->mesh_path);
    if (entry == nullptr) {
        throw PlayerError("Starting weapon mesh disappeared from pak.zip");
    }
    SceneMeshResource resource;
    resource.guid = player.starting_weapon->guid;
    resource.source_path = entry->name;
    resource.mesh = parse_ogre_mesh(archive.read(*entry));
    add_mesh_counts(resource.mesh, geometry);
    const auto mesh_index = geometry.meshes.size();
    geometry.meshes.push_back(std::move(resource));
    LayoutWorldTransform transform;
    transform.position = position;
    transform.scale = {player.weapon_scale, player.weapon_scale, player.weapon_scale};
    const auto instance_index = geometry.instances.size();
    geometry.instances.push_back(
        SceneMeshInstance{0, 0, mesh_index, transform, 0, true, std::nullopt});
    return instance_index;
}

std::array<float, 3> layout_player_start(const LayoutManifest& layout) {
    auto marker = find_layout_world_transform(layout, u"Editor Player Start");
    if (!marker) {
        const auto transforms = resolve_layout_world_transforms(layout);
        for (std::size_t index = 0; index < layout.objects.size(); ++index) {
            const auto& object = layout.objects[index];
            if (object.descriptor == u"EditorPlayerStart" || object.name == u"PlayerStart") {
                marker = transforms[index];
                break;
            }
        }
    }
    if (!marker) {
        const auto transforms = resolve_layout_world_transforms(layout);
        for (std::size_t index = 0; index < layout.objects.size(); ++index) {
            const auto& object = layout.objects[index];
            const auto* type = object.find_property(u"TYPE");
            if (object.descriptor == u"Property Node" && type != nullptr &&
                (type->type == AdmValueType::string ||
                 type->type == AdmValueType::translation ||
                 type->type == AdmValueType::note) &&
                std::get<std::u16string>(type->value) == u"Entrance") {
                marker = transforms[index];
                break;
            }
        }
    }
    if (!marker) {
        const auto transforms = resolve_layout_world_transforms(layout);
        for (std::size_t index = 0; index < layout.objects.size(); ++index) {
            if (layout.objects[index].descriptor == u"Pathing" &&
                layout.objects[index].name == u"PlayerWalksHalfway") {
                marker = transforms[index];
                break;
            }
        }
    }
    if (!marker) {
        const auto transforms = resolve_layout_world_transforms(layout);
        for (std::size_t index = 0; index < layout.objects.size(); ++index) {
            if (layout.objects[index].descriptor == u"Warper" &&
                layout.objects[index].name == u"WarperMain") {
                marker = transforms[index];
                break;
            }
        }
    }
    if (!marker) {
        throw PlayerError("Layout has no Editor Player Start marker");
    }
    return marker->position;
}

std::array<float, 3> generated_player_start(const LevelSceneLoader& loader,
                                            const GeneratedLevel& level) {
    if (level.chunks.empty()) {
        throw PlayerError("Generated level has no entrance chunk");
    }
    const auto layout = loader.load_layout(level.chunks.front().layout_path);
    auto position = layout_player_start(layout);
    for (std::size_t axis = 0; axis < position.size(); ++axis) {
        position[axis] += level.chunks.front().position[axis];
    }
    return position;
}

} // namespace torchlight
