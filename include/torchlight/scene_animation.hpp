#pragma once

#include "torchlight/animation_manifest.hpp"
#include "torchlight/ogre_skeleton.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/randomizer.hpp"
#include "torchlight/scene_geometry.hpp"
#include "torchlight/skeletal_animation.hpp"

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace torchlight {

enum class SceneAnimationKind {
    idle,
    run,
    attack,
    hit,
    death,
};

struct SceneMeshAnimation {
    std::size_t mesh_index = 0;
    SceneAnimationKind kind = SceneAnimationKind::idle;
    OgreSkeleton bind_skeleton;
    OgreSkeleton animation_skeleton;
    std::string animation_name;
    std::string manifest_path;
    std::string skeleton_path;
    std::vector<AnimationEventKey> event_keys;
    float duration = 0.0F;
};

struct ModelAnimationClip {
    OgreSkeleton animation_skeleton;
    std::string animation_name;
    std::string manifest_path;
    std::string skeleton_path;
    std::vector<AnimationEventKey> event_keys;
    float duration = 0.0F;
};

// Resolves a clip through the original sibling .animation manifest. Missing
// clips are allowed because not every model supports every runtime state.
[[nodiscard]] std::optional<ModelAnimationClip> load_model_animation(
    const PakArchive& archive, std::string_view mesh_path,
    std::string_view bind_skeleton_file, SceneAnimationKind kind);

// Returns every manifest clip whose skeleton filename starts with prefix, in
// manifest order. CGenericModel::findRandomAnimation searches this same list.
[[nodiscard]] std::vector<ModelAnimationClip> load_model_animations_by_prefix(
    const PakArchive& archive, std::string_view mesh_path,
    std::string_view bind_skeleton_file, std::string_view prefix);

// CGenericModel::findRandomAnimation keeps the first prefix match, then gives
// every subsequent match an independent 50% chance to replace it.
[[nodiscard]] std::size_t select_original_random_animation(
    std::size_t clip_count, TorchlightRandom& random);

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
