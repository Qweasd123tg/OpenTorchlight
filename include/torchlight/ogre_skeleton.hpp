#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace torchlight {

class OgreSkeletonError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct OgreSkeletonBone {
    std::string name;
    std::uint16_t handle = 0;
    std::array<float, 3> position{};
    std::array<float, 4> orientation{};
    std::array<float, 3> scale{1.0F, 1.0F, 1.0F};
    std::optional<std::uint16_t> parent_handle;
};

struct OgreSkeletonKeyframe {
    float time = 0.0F;
    std::array<float, 4> rotation{};
    std::array<float, 3> translation{};
    std::array<float, 3> scale{1.0F, 1.0F, 1.0F};
};

struct OgreSkeletonTrack {
    std::uint16_t bone_handle = 0;
    std::vector<OgreSkeletonKeyframe> keyframes;
};

struct OgreSkeletonAnimation {
    std::string name;
    float length = 0.0F;
    std::vector<OgreSkeletonTrack> tracks;
};

struct OgreSkeletonAnimationLink {
    std::string skeleton_file;
    float scale = 1.0F;
};

struct OgreSkeleton {
    std::string serializer_version;
    std::vector<OgreSkeletonBone> bones;
    std::vector<OgreSkeletonAnimation> animations;
    std::vector<OgreSkeletonAnimationLink> animation_links;
};

[[nodiscard]] OgreSkeleton parse_ogre_skeleton(
    const std::vector<std::uint8_t>& bytes);

} // namespace torchlight
