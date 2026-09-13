#include "torchlight/pathfinder_rules.hpp"

#include <cstdint>

extern "C" {

std::uint32_t recovered_path_tile_index(std::uint32_t width, std::uint32_t x,
                                        std::uint32_t z) {
    return torchlight::path_tile_index(width, x, z);
}

bool recovered_path_tile_free(std::uint32_t width, std::uint32_t height,
                              const std::int16_t* primary, const std::int16_t* secondary,
                              bool primary_only, std::uint32_t x, std::uint32_t z) {
    return torchlight::path_tile_free(width, height, primary, secondary, primary_only, x, z);
}

float recovered_path_node_center(std::uint32_t coordinate, float cell_size, float origin) {
    return torchlight::path_node_center(coordinate, cell_size, origin);
}

}
