#include "torchlight/scene_geometry.hpp"

#include <algorithm>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

namespace torchlight {
namespace {

class SceneGeometryError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

std::string ascii_path(std::u16string_view path) {
    std::string result;
    result.reserve(path.size());
    for (const auto character : path) {
        if (character > 0x7fU) {
            throw SceneGeometryError("Scene mesh path contains a non-ASCII character");
        }
        result.push_back(static_cast<char>(character));
    }
    return result;
}

void add_mesh_counts(const OgreMesh& mesh, FixedSceneGeometry& scene_geometry) {
    if (mesh.shared_geometry.has_value()) {
        scene_geometry.unique_vertex_count += mesh.shared_geometry->vertex_count;
    }
    for (const auto& submesh : mesh.submeshes) {
        scene_geometry.unique_index_count += submesh.indices.size();
        if (submesh.geometry.has_value()) {
            scene_geometry.unique_vertex_count += submesh.geometry->vertex_count;
        }
    }
}

void append_layout_geometry(const PakArchive& archive, const LevelsetCatalog& levelsets,
                            const LayoutManifest& layout, std::size_t layout_index,
                            const std::array<float, 3>& offset, FixedSceneGeometry& result,
                            std::unordered_map<std::int64_t, std::size_t>& mesh_by_guid) {
    const auto transforms = resolve_layout_world_transforms(layout);
    for (std::size_t object_index = 0; object_index < layout.objects.size(); ++object_index) {
        const auto& object = layout.objects[object_index];
        if (object.descriptor != u"Room Piece") {
            continue;
        }
        if (!object.piece_guid.has_value()) {
            throw SceneGeometryError("Room piece has no GUID");
        }
        auto found = mesh_by_guid.find(*object.piece_guid);
        if (found == mesh_by_guid.end()) {
            const auto* piece = levelsets.find(*object.piece_guid);
            if (piece == nullptr) {
                throw SceneGeometryError("Room piece GUID is absent from levelsets");
            }
            const auto mesh_path = ascii_path(piece->mesh_file);
            const auto* entry = archive.find_normalized(mesh_path);
            if (mesh_path.empty() || entry == nullptr) {
                throw SceneGeometryError("Room piece mesh is absent from pak.zip: " + mesh_path);
            }
            SceneMeshResource resource;
            resource.guid = *object.piece_guid;
            resource.source_path = entry->name;
            resource.mesh = parse_ogre_mesh(archive.read(*entry));
            add_mesh_counts(resource.mesh, result);
            const auto mesh_index = result.meshes.size();
            result.meshes.push_back(std::move(resource));
            found = mesh_by_guid.emplace(*object.piece_guid, mesh_index).first;
        }
        auto transform = transforms[object_index];
        for (std::size_t axis = 0; axis < transform.position.size(); ++axis) {
            transform.position[axis] += offset[axis];
        }
        result.instances.push_back(
            SceneMeshInstance{layout_index, object_index, found->second, transform});
    }
}

const std::u16string& definition_text(const UnitDefinition& definition,
                                      const char16_t* name) {
    const auto* property = definition.find_property(name);
    if (property == nullptr ||
        (property->type != AdmValueType::string &&
         property->type != AdmValueType::translation &&
         property->type != AdmValueType::note)) {
        throw SceneGeometryError("Placed monster has no valid mesh path property");
    }
    return std::get<std::u16string>(property->value);
}

std::string monster_mesh_path(const UnitDefinition& definition) {
    auto directory = ascii_path(definition_text(definition, u"RESOURCEDIRECTORY"));
    std::replace(directory.begin(), directory.end(), '\\', '/');
    if (!directory.empty() && directory.back() != '/') {
        directory.push_back('/');
    }
    auto mesh = ascii_path(definition_text(definition, u"MESHFILE"));
    std::replace(mesh.begin(), mesh.end(), '\\', '/');
    std::string result = directory + mesh;
    if (result.size() < 5U || result.substr(result.size() - 5U) != ".mesh") {
        result += ".mesh";
    }
    return result;
}

std::optional<std::string> runtime_unit_mesh_path(const UnitDefinition& definition) {
    const auto* directory_property = definition.find_property(u"RESOURCEDIRECTORY");
    const auto* mesh_property = definition.find_property(u"MESHFILE");
    if (directory_property == nullptr || mesh_property == nullptr ||
        (directory_property->type != AdmValueType::string &&
         directory_property->type != AdmValueType::translation &&
         directory_property->type != AdmValueType::note) ||
        (mesh_property->type != AdmValueType::string &&
         mesh_property->type != AdmValueType::translation &&
         mesh_property->type != AdmValueType::note)) {
        return std::nullopt;
    }
    auto directory = ascii_path(std::get<std::u16string>(directory_property->value));
    std::replace(directory.begin(), directory.end(), '\\', '/');
    if (!directory.empty() && directory.back() != '/') {
        directory.push_back('/');
    }
    auto mesh = ascii_path(std::get<std::u16string>(mesh_property->value));
    std::replace(mesh.begin(), mesh.end(), '\\', '/');
    std::string result = directory + mesh;
    if (result.size() < 5U || result.substr(result.size() - 5U) != ".mesh") {
        result += ".mesh";
    }
    return result;
}

} // namespace

FixedSceneGeometry build_room_piece_geometry(const PakArchive& archive,
                                             const LevelsetCatalog& levelsets,
                                             const FixedLevelScene& scene) {
    FixedSceneGeometry result;
    std::unordered_map<std::int64_t, std::size_t> mesh_by_guid;
    mesh_by_guid.reserve(scene.layout.objects.size());
    append_layout_geometry(archive, levelsets, scene.layout, 0, {0.0F, 0.0F, 0.0F}, result,
                           mesh_by_guid);
    return result;
}

FixedSceneGeometry build_generated_level_geometry(const PakArchive& archive,
                                                  const LevelsetCatalog& levelsets,
                                                  const LevelSceneLoader& loader,
                                                  const LevelRules& rules,
                                                  const GeneratedLevel& level) {
    FixedSceneGeometry result;
    std::unordered_map<std::int64_t, std::size_t> mesh_by_guid;
    for (std::size_t chunk = 0; chunk < level.chunks.size(); ++chunk) {
        const auto& placed = level.chunks[chunk];
        if (placed.type >= rules.chunk_types.size()) {
            throw SceneGeometryError("Generated chunk type is out of range");
        }
        const auto layout = loader.load_layout(placed.layout_path);
        append_layout_geometry(archive, levelsets, layout, chunk, placed.position, result,
                               mesh_by_guid);
    }
    return result;
}

std::size_t append_layout_monster_geometry(const PakArchive& archive,
                                           const MasterResourceIndex& resources,
                                           UnitDefinitionLoader& definitions,
                                           const LayoutManifest& layout,
                                           FixedSceneGeometry& geometry,
                                           std::size_t layout_index) {
    const auto transforms = resolve_layout_world_transforms(layout);
    std::unordered_map<std::string, std::size_t> meshes;
    meshes.reserve(geometry.meshes.size() + layout.objects.size());
    for (std::size_t index = 0; index < geometry.meshes.size(); ++index) {
        meshes.emplace(geometry.meshes[index].source_path, index);
    }
    std::size_t appended = 0;
    for (std::size_t object_index = 0; object_index < layout.objects.size(); ++object_index) {
        const auto& object = layout.objects[object_index];
        if (object.descriptor != u"Monster" || object.monster.empty()) {
            continue;
        }
        const auto* record = resources.find(MasterResourceKind::monster, object.monster);
        if (record == nullptr) {
            throw SceneGeometryError("Placed monster is absent from master resources");
        }
        const auto definition = definitions.load(*record);
        const auto requested_path = monster_mesh_path(*definition);
        const auto* entry = archive.find_normalized(requested_path);
        if (entry == nullptr) {
            throw SceneGeometryError("Placed monster mesh is absent from pak.zip: " +
                                     requested_path);
        }
        auto found = meshes.find(entry->name);
        if (found == meshes.end()) {
            SceneMeshResource resource;
            resource.guid = record->guid;
            resource.source_path = entry->name;
            resource.mesh = parse_ogre_mesh(archive.read(*entry));
            add_mesh_counts(resource.mesh, geometry);
            const auto mesh_index = geometry.meshes.size();
            geometry.meshes.push_back(std::move(resource));
            found = meshes.emplace(entry->name, mesh_index).first;
        }
        geometry.instances.push_back(
            SceneMeshInstance{layout_index, object_index, found->second,
                              transforms[object_index]});
        ++appended;
    }
    return appended;
}

std::optional<std::size_t> append_runtime_entity_geometry(
    const PakArchive& archive, const MasterResourceIndex& resources,
    UnitDefinitionLoader& definitions, const RuntimeEntity& entity,
    FixedSceneGeometry& geometry) {
    const auto* record = resources.find(entity.resource_guid);
    if (record == nullptr || record->do_not_create) {
        return std::nullopt;
    }
    const auto definition = definitions.load(*record);
    const auto requested_path = runtime_unit_mesh_path(*definition);
    if (!requested_path) {
        return std::nullopt;
    }
    const auto* entry = archive.find_normalized(*requested_path);
    if (entry == nullptr) {
        return std::nullopt;
    }

    auto mesh = std::find_if(geometry.meshes.begin(), geometry.meshes.end(),
                             [&](const auto& resource) {
                                 return resource.source_path == entry->name;
                             });
    std::size_t mesh_index = 0;
    if (mesh == geometry.meshes.end()) {
        SceneMeshResource resource;
        resource.guid = record->guid;
        resource.source_path = entry->name;
        resource.mesh = parse_ogre_mesh(archive.read(*entry));
        add_mesh_counts(resource.mesh, geometry);
        mesh_index = geometry.meshes.size();
        geometry.meshes.push_back(std::move(resource));
    } else {
        mesh_index = static_cast<std::size_t>(mesh - geometry.meshes.begin());
    }

    LayoutWorldTransform transform;
    transform.position = entity.position;
    geometry.instances.push_back(SceneMeshInstance{
        std::numeric_limits<std::size_t>::max(), 0, mesh_index, transform, entity.id});
    return geometry.instances.size() - 1U;
}

} // namespace torchlight
