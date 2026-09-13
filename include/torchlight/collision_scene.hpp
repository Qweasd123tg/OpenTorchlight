#pragma once

#include "torchlight/level_scene.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/random_level.hpp"

#include <array>
#include <cstddef>
#include <vector>

namespace torchlight {

struct CollisionTriangle {
    std::array<std::array<float, 3>, 3> vertices{};
};

struct CollisionScene {
    std::vector<CollisionTriangle> triangles;
    std::size_t source_meshes = 0;
    std::size_t instances = 0;
    std::size_t missing_instances = 0;
    std::size_t degenerate_triangles = 0;
};

[[nodiscard]] CollisionScene build_generated_level_collision(
    const PakArchive& archive, const LevelsetCatalog& levelsets,
    const LevelSceneLoader& loader, const GeneratedLevel& level);

[[nodiscard]] CollisionScene build_fixed_level_collision(
    const PakArchive& archive, const LevelsetCatalog& levelsets,
    const FixedLevelScene& scene);

} // namespace torchlight
