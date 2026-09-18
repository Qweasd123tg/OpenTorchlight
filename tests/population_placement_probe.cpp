#include "torchlight/population.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
namespace {
float number(std::uint32_t bits) { float value; std::memcpy(&value, &bits, 4); return value; }
std::uint32_t bits(float value) { std::uint32_t n; std::memcpy(&n, &value, 4); return n; }
} // namespace
// 'o' seed cx cy cz minR maxR -> x y z rng_state (all as bits/u64).
// Mirrors only one polar candidate PREFIX, NOT a complete randomOpenPositionRange call:
// r in [minR, maxR], angle in [0, 360), polar offset, y passthrough.
int main() {
    try {
        char kind;
        while (std::cin >> kind) {
            if (kind != 'o') return 2;
            std::uint32_t seed, cx, cy, cz, minr, maxr;
            if (!(std::cin >> seed >> cx >> cy >> cz >> minr >> maxr)) return 2;
            torchlight::TorchlightRandom rng(seed);
            const float z = number(cz);
            const float x = number(cx);
            const torchlight::PolarPick pick =
                torchlight::random_open_offset(number(minr), number(maxr), rng);
            std::cout << bits(x + pick.dx) << ' ' << bits(number(cy)) << ' '
                      << bits(z + pick.dz) << ' ' << rng.state() << '\n';
        }
        return std::cin.eof() ? 0 : 2;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
