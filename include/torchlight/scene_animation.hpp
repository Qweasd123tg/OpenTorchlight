#pragma once

#include "torchlight/ogre_skeleton.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/scene_geometry.hpp"
#include "torchlight/skeletal_animation.hpp"

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace torchlight {

enum class SceneAnimationKind {
    idle,
    run,
    attack,
};

struct SceneMeshAnimation {
    std::size_t mesh_index = 0;
    SceneAnimationKind kind = SceneAnimationKind::idle;
    OgreSkeleton bind_skeleton;
    OgreSkeleton animation_skeleton;
    std::string animation_name;
    float duration = 0.0F;
};

// Resolves conventional sibling Idle*.SKELETON clips for every animated mesh.
// Missing clips are allowed because scenery and equipment can also be skinned.
[[nodiscard]] std::vector<SceneMeshAnimation> load_scene_idle_animations(
    const PakArchive& archive, const FixedSceneGeometry& geometry,
    std::optional<std::size_t> excluded_mesh_index = std::nullopt);

[[nodiscard]] std::vector<SceneMeshAnimation> load_scene_animations(
    const PakArchive& archive, const FixedSceneGeometry& geometry,
    SceneAnimationKind kind,
    std::optional<std::size_t> excluded_mesh_index = std::nullopt);

[[nodiscard]] OgreMeshPose sample_scene_mesh_animation(
    const FixedSceneGeometry& geometry, const SceneMeshAnimation& animation,
    float time_seconds);

} // namespace torchlight
