#pragma once

#include "torchlight/level_scene.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/ogre_mesh.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/random_level.hpp"
#include "torchlight/unit_definition.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace torchlight {

struct SceneMeshResource {
    std::int64_t guid = 0;
    std::string source_path;
    OgreMesh mesh;
};

struct SceneMeshInstance {
    std::size_t layout_index = 0;
    std::size_t object_index = 0;
    std::size_t mesh_index = 0;
    LayoutWorldTransform transform;
};

struct FixedSceneGeometry {
    std::vector<SceneMeshResource> meshes;
    std::vector<SceneMeshInstance> instances;
    std::uint64_t unique_vertex_count = 0;
    std::uint64_t unique_index_count = 0;
};

[[nodiscard]] FixedSceneGeometry build_room_piece_geometry(
    const PakArchive& archive, const LevelsetCatalog& levelsets,
    const FixedLevelScene& scene);

[[nodiscard]] FixedSceneGeometry build_generated_level_geometry(
    const PakArchive& archive, const LevelsetCatalog& levelsets,
    const LevelSceneLoader& loader, const LevelRules& rules,
    const GeneratedLevel& level);

[[nodiscard]] std::size_t append_layout_monster_geometry(
    const PakArchive& archive, const MasterResourceIndex& resources,
    UnitDefinitionLoader& definitions, const LayoutManifest& layout,
    FixedSceneGeometry& geometry, std::size_t layout_index = 0);

} // namespace torchlight
