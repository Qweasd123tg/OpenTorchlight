// Test-only scalar adapter. Integer bit patterns keep float32 inputs/outputs exact.
#include "torchlight/enemy_ai.hpp"

#include <cstdint>
#include <cstring>
#include <iostream>
#include <optional>

namespace {
float decode(std::uint32_t bits) {
    float result;
    static_assert(sizeof(result) == sizeof(bits));
    std::memcpy(&result, &bits, sizeof(bits));
    return result;
}
std::uint32_t encode(float value) {
    std::uint32_t result;
    std::memcpy(&result, &value, sizeof(value));
    return result;
}
} // namespace

int main() {
    int operation = 0;
    int has_equipment = 0;
    std::uint32_t remaining = 0, unit_or_delta = 0, weapon = 0;
    while (std::cin >> operation) {
        if (!(std::cin >> remaining >> unit_or_delta >> weapon >> has_equipment) ||
            (operation != 0 && operation != 1) ||
            (has_equipment != 0 && has_equipment != 1)) return 2;
        torchlight::MonsterAiCooldown timer;
        timer.remaining = decode(remaining);
        if (operation == 0) timer.update(decode(unit_or_delta));
        else timer.attack_started(decode(unit_or_delta), has_equipment
                ? std::optional<float>{decode(weapon)} : std::nullopt);
        std::cout << encode(timer.remaining) << '\n';
    }
    return std::cin.eof() ? 0 : 2;
}
