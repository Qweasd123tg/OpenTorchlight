#include "torchlight/player.hpp"

#include "torchlight/ogre_mesh.hpp"

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
        player.strength = integer(*definition, u"STRENGTH");
        player.dexterity = integer(*definition, u"DEXTERITY");
        player.magic = integer(*definition, u"MAGIC");
        player.defense = integer(*definition, u"DEFENSE");
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
