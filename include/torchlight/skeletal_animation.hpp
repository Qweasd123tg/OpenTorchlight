#pragma once

#include "torchlight/ogre_mesh.hpp"
#include "torchlight/ogre_skeleton.hpp"

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace torchlight {

struct OgreGeometryPose {
    const OgreGeometry* source = nullptr;
    std::vector<std::array<float, 3>> positions;
    std::vector<std::array<float, 3>> normals;
};

struct OgreBonePose {
    std::string name;
    std::uint16_t handle = 0;
    std::array<float, 3> position{};
    std::array<float, 4> orientation{1.0F, 0.0F, 0.0F, 0.0F};
    std::array<float, 3> scale{1.0F, 1.0F, 1.0F};
};

struct OgreMeshPose {
    std::vector<OgreGeometryPose> geometries;
    std::vector<OgreBonePose> bones;
};

[[nodiscard]] OgreMeshPose sample_ogre_mesh_animation(
    const OgreMesh& mesh, const OgreSkeleton& bind_skeleton,
    const OgreSkeleton& animation_skeleton, std::string_view animation_name,
    float time_seconds);

// Applies two OGRE AnimationState layers to the bind skeleton before skinning.
// Translation and rotation weights follow OGRE 1.6 NodeAnimationTrack::applyToNode.
[[nodiscard]] OgreMeshPose sample_ogre_mesh_animation_blend(
    const OgreMesh& mesh, const OgreSkeleton& bind_skeleton,
    const OgreSkeleton& first_animation_skeleton,
    std::string_view first_animation_name, float first_time_seconds,
    float first_weight, const OgreSkeleton& second_animation_skeleton,
    std::string_view second_animation_name, float second_time_seconds,
    float second_weight);

[[nodiscard]] OgreMeshPose blend_ogre_mesh_poses(
    const OgreMeshPose& first, const OgreMeshPose& second, float second_weight);

} // namespace torchlight
