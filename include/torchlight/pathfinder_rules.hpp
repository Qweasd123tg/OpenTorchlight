#pragma once

#include <cstddef>
#include <cstdint>

namespace torchlight {

[[nodiscard]] std::uint32_t path_tile_index(std::uint32_t width, std::uint32_t x,
                                            std::uint32_t z) noexcept;
[[nodiscard]] bool path_tile_free(std::uint32_t width, std::uint32_t height,
                                  const std::int16_t* primary,
                                  const std::int16_t* secondary, bool primary_only,
                                  std::uint32_t x, std::uint32_t z) noexcept;
[[nodiscard]] float path_node_center(std::uint32_t coordinate, float cell_size,
                                     float origin) noexcept;
[[nodiscard]] float path_node_priority(float parent_cost, std::uint32_t x, std::uint32_t z,
                                       std::uint32_t goal_x, std::uint32_t goal_z) noexcept;

} // namespace torchlight
