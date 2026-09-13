#include "torchlight/randomizer.hpp"
#include "torchlight/random_level.hpp"

#include <cstdint>
#include <memory>

namespace {
std::unique_ptr<torchlight::TorchlightRandom> randomizer;
}

extern "C" {

bool recovered_random_seed(std::uint32_t seed) {
    if (seed == 0) {
        return false;
    }
    randomizer = std::make_unique<torchlight::TorchlightRandom>(seed);
    return true;
}

std::int32_t recovered_random_integer_between(std::int32_t low, std::int32_t high) {
    return randomizer->integer_between(low, high);
}

float recovered_random_between(float low, float high) {
    return randomizer->between(low, high);
}

std::size_t recovered_weighted_index(const float* weights, std::size_t count) {
    return torchlight::weighted_index(std::vector<float>(weights, weights + count), *randomizer);
}

std::uint64_t recovered_random_state() {
    return randomizer->state();
}

bool recovered_chunks_intersect(float tile_basis, float width_basis, float height_basis,
                                std::int32_t left_width, std::int32_t left_height,
                                float left_x, float left_y, float left_z,
                                std::int32_t right_width, std::int32_t right_height,
                                float right_x, float right_y, float right_z) {
    torchlight::LevelRules rules;
    rules.tile_basis = tile_basis;
    rules.chunk_width_basis = width_basis;
    rules.chunk_height_basis = height_basis;
    torchlight::ChunkType left;
    left.width = left_width;
    left.height = left_height;
    torchlight::ChunkType right;
    right.width = right_width;
    right.height = right_height;
    return torchlight::generated_chunks_intersect(
        rules, left, {left_x, left_y, left_z}, right, {right_x, right_y, right_z});
}

}
