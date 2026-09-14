#pragma once

#include "torchlight/level_scene.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace torchlight {

struct GeneratedExitMatch {
    std::size_t chunk = 0;
    std::size_t exit = 0;
};

struct GeneratedChunk {
    std::size_t type = 0;
    std::string layout_path;
    std::array<float, 3> position{};
    std::vector<std::optional<GeneratedExitMatch>> matched_exits;
};

struct GeneratedLevel {
    std::uint32_t seed = 0;
    std::int32_t requested_middle_chunks = 0;
    std::size_t placement_attempts = 0;
    std::vector<GeneratedChunk> chunks;
};

struct GeneratedLayoutObjectOrigin {
    std::size_t chunk = 0;
    std::int64_t original_object_id = 0;
};

struct GeneratedLevelLayout {
    LayoutManifest layout;
    // Aligned with layout.objects. Runtime IDs are unique across repeated
    // chunks while this table preserves the original resource identity.
    std::vector<GeneratedLayoutObjectOrigin> object_origins;
};

class RandomLevelGenerator {
public:
    explicit RandomLevelGenerator(const LevelSceneLoader& loader) : loader_(loader) {}

    [[nodiscard]] GeneratedLevel generate(const LevelRules& rules, std::uint32_t seed) const;

private:
    const LevelSceneLoader& loader_;
};

[[nodiscard]] std::array<float, 3> generated_exit_position(const LevelRules& rules,
                                                            const GeneratedLevel& level,
                                                            std::size_t chunk,
                                                            std::size_t exit);

[[nodiscard]] bool generated_chunks_intersect(
    const LevelRules& rules, const ChunkType& left_type,
    const std::array<float, 3>& left_position, const ChunkType& right_type,
    const std::array<float, 3>& right_position) noexcept;

[[nodiscard]] GeneratedLevelLayout compose_generated_level_layout(
    const LevelSceneLoader& loader, const GeneratedLevel& level);

} // namespace torchlight
