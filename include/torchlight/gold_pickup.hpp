#pragma once
#include <array>
#include <cstdint>
#include <vector>

namespace torchlight {
struct GoldPickupPoint {
    std::uint64_t id = 0;
    std::array<float,3> position{};
    bool gold = false; // evaluated original ISA(0x22), not name/mesh inference
};
// original-code: autoPickupGold @0x56e3a0. Evaluated alive/pathing and world
// positions; exact f32 XZ subtraction/square/add/sqrt, strict radius <3.0.
// Ownership, original linked-list lifetime and getItem effects are caller work.
[[nodiscard]] std::vector<std::uint64_t> auto_gold_targets(
    const std::array<float,3>& player, bool alive, bool moving,
    const std::vector<GoldPickupPoint>& items);
struct GoldCollection {
    std::vector<std::uint64_t> entities;
    std::int64_t amount = 0; // quoted amounts; wallet can saturate at INT_MAX
};
} // namespace torchlight
