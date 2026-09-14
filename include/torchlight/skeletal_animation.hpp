#pragma once

#include "torchlight/ogre_mesh.hpp"
#include "torchlight/ogre_skeleton.hpp"

#include <array>
#include <string_view>
#include <vector>

namespace torchlight {

struct OgreGeometryPose {
    const OgreGeometry* source = nullptr;
    std::vector<std::array<float, 3>> positions;
    std::vector<std::array<float, 3>> normals;
};

struct OgreMeshPose {
    std::vector<OgreGeometryPose> geometries;
};

[[nodiscard]] OgreMeshPose sample_ogre_mesh_animation(
    const OgreMesh& mesh, const OgreSkeleton& bind_skeleton,
    const OgreSkeleton& animation_skeleton, std::string_view animation_name,
    float time_seconds);

[[nodiscard]] OgreMeshPose blend_ogre_mesh_poses(
    const OgreMeshPose& first, const OgreMeshPose& second, float second_weight);

} // namespace torchlight
