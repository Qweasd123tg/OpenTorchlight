#include "torchlight/player.hpp"

#include "torchlight/ogre_mesh.hpp"
#include "torchlight/stat_graph.hpp"

#include <algorithm>
#include <cmath>
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

std::int32_t integer(const UnitDefinition& definition, const char16_t* name) {
    const auto& property = required(definition, name);
    if (property.type != AdmValueType::integer) {
        throw PlayerError("Playable player integer property has the wrong type");
    }
    return std::get<std::int32_t>(property.value);
}

std::int32_t optional_integer(const UnitDefinition& definition,
                              const char16_t* name, std::int32_t fallback) {
    const auto* property = definition.find_property(name);
    if (property == nullptr) {
        return fallback;
    }
    if (property->type != AdmValueType::integer) {
        throw PlayerError("Equipment integer property has the wrong type");
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
        throw PlayerError("Equipment float property has the wrong type");
    }
    return std::get<float>(property->value);
}

std::optional<std::u16string> starting_weapon_name(const UnitDefinition& definition) {
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
            return std::get<std::u16string>(property->value);
        }
    }
    return std::nullopt;
}

WeaponPrototype load_weapon(const MasterResourceIndex& resources,
                            UnitDefinitionLoader& definitions,
                            const StatGraph& damage_graph,
                            std::u16string_view name) {
    const auto* record = resources.find_case_insensitive(
        MasterResourceKind::item, name);
    if (record == nullptr || record->do_not_create || record->create_as != u"EQUIPMENT") {
        throw PlayerError("Starting weapon is absent from equipment resources");
    }
    const auto definition = definitions.load(*record);
    WeaponPrototype weapon;
    weapon.guid = record->guid;
    weapon.name = record->name;
    weapon.display_name = record->display_name;
    weapon.unit_type = record->unit_type;
    weapon.level = optional_integer(*definition, u"LEVEL", 1);
    weapon.minimum_damage_percent = integer(*definition, u"MINDAMAGE");
    weapon.maximum_damage_percent = integer(*definition, u"MAXDAMAGE");
    weapon.rarity_damage_modifier = optional_integer(
        *definition, u"RARITY_DMG_MOD", 100);
    weapon.speed_damage_modifier = optional_integer(
        *definition, u"SPEED_DMG_MOD", 100);
    weapon.speed = optional_integer(*definition, u"SPEED", 100);
    weapon.range = optional_floating(*definition, u"RANGE", 0.0F);
    weapon.strike_range = optional_floating(*definition, u"STRIKERANGE", weapon.range);
    weapon.base_weapon_damage = damage_graph.value(static_cast<float>(weapon.level));
    if (weapon.minimum_damage_percent < 0 ||
        weapon.maximum_damage_percent < weapon.minimum_damage_percent ||
        weapon.rarity_damage_modifier < 0 || weapon.speed_damage_modifier < 0 ||
        !std::isfinite(weapon.range) || weapon.range < 0.0F ||
        !std::isfinite(weapon.strike_range) || weapon.strike_range < 0.0F ||
        !std::isfinite(weapon.base_weapon_damage) ||
        !(weapon.base_weapon_damage > 0.0F)) {
        throw PlayerError("Starting weapon combat properties are invalid");
    }
    return weapon;
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
        player.walking_speed = floating(*definition, u"WALKINGSPEED");
        player.running_speed = floating(*definition, u"RUNNINGSPEED");
        player.attack_speed = floating(*definition, u"ATTACKSPEED");
        player.reach_bonus = floating(*definition, u"REACH_BONUS");
        player.minimum_damage = integer(*definition, u"MINDAMAGE");
        player.maximum_damage = integer(*definition, u"MAXDAMAGE");
        player.strength = integer(*definition, u"STRENGTH");
        player.dexterity = integer(*definition, u"DEXTERITY");
        player.magic = integer(*definition, u"MAGIC");
        player.defense = integer(*definition, u"DEFENSE");
        if (const auto weapon_name = starting_weapon_name(*definition)) {
            player.starting_weapon = load_weapon(
                resources, definitions, damage_graph, *weapon_name);
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
    resource.mesh = parse_ogre_mesh(archive.read(*entry));
    add_mesh_counts(resource.mesh, geometry);
    const auto mesh_index = geometry.meshes.size();
    geometry.meshes.push_back(std::move(resource));
    LayoutWorldTransform transform;
    transform.position = position;
    geometry.instances.push_back(SceneMeshInstance{0, 0, mesh_index, transform});
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
