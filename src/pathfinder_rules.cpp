#include "torchlight/pathfinder_rules.hpp"

namespace torchlight {

std::uint32_t path_tile_index(std::uint32_t width, std::uint32_t x,
                              std::uint32_t z) noexcept {
    return z * width + x;
}

bool path_tile_free(std::uint32_t width, std::uint32_t height,
                    const std::int16_t* primary, const std::int16_t* secondary,
                    bool primary_only, std::uint32_t x, std::uint32_t z) noexcept {
    if (x >= width || z >= height || primary == nullptr) {
        return false;
    }
    const auto offset = static_cast<std::size_t>(x) * height + z;
    if (primary[offset] > 0) {
        return false;
    }
    return primary_only || secondary == nullptr || secondary[offset] <= 0;
}

float path_node_center(std::uint32_t coordinate, float cell_size, float origin) noexcept {
    const float coordinate_offset = static_cast<float>(coordinate) * cell_size;
    const float half_cell = cell_size * 0.5F;
    return (coordinate_offset + half_cell) + origin;
}

float path_node_priority(float parent_cost, std::uint32_t x, std::uint32_t z,
                         std::uint32_t goal_x, std::uint32_t goal_z) noexcept {
    const float difference_x = static_cast<float>(static_cast<std::int64_t>(x) - goal_x);
    const float difference_z = static_cast<float>(static_cast<std::int64_t>(z) - goal_z);
    return parent_cost + 1.0F +
           difference_x * difference_x + difference_z * difference_z;
}

} // namespace torchlight
