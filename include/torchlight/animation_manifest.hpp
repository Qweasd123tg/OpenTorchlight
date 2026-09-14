#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace torchlight {

class AnimationManifestError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct AnimationEventKey {
    std::string name;
    float frame = 0.0F;
    std::int32_t particle_count = 0;
    bool particle_attaches = false;
    std::optional<std::string> sound;
    std::optional<std::string> layout;
    std::optional<std::string> unit_theme;
    std::optional<std::string> bone;
    std::optional<std::string> camera_shake;
    std::optional<float> camera_shake_duration;
    std::optional<std::array<float, 3>> bone_offset;
};

struct AnimationManifestClip {
    std::string file;
    std::vector<AnimationEventKey> keys;
};

struct AnimationManifest {
    std::vector<AnimationManifestClip> clips;
};

// Parses the UTF-16LE .animation files shipped in pak.zip. These manifests are
// the original model-to-skeleton binding and animation-event timeline.
[[nodiscard]] AnimationManifest parse_animation_manifest(
    const std::vector<std::uint8_t>& bytes);

} // namespace torchlight
