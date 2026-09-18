#include "torchlight/character_stats.hpp"
#include <cstdint>
#include <cstring>
#include <exception>
#include <iostream>
float value(std::uint32_t bits) { float result; std::memcpy(&result, &bits, sizeof(result)); return result; }
std::uint32_t bits(float value) { std::uint32_t result; std::memcpy(&result, &value, sizeof(result)); return result; }
int main() {
    try {
        int op;
        while (std::cin >> op) {
            if (op == 0) {
                std::uint32_t a, b, c; if (!(std::cin >> a >> b >> c)) return 2;
                std::cout << bits(torchlight::evaluated_movement_speed(value(a), value(b), value(c))) << '\n';
            } else if (op == 1) {
                std::int32_t base; std::uint32_t a, b, c; if (!(std::cin >> base >> a >> b >> c)) return 2;
                std::cout << torchlight::evaluated_defense_attribute(base, value(a), value(b), value(c)) << '\n';
            } else if (op == 2) {
                std::int32_t base, defense; std::uint32_t a, b, c, d;
                if (!(std::cin >> base >> defense >> a >> b >> c >> d)) return 2;
                std::cout << torchlight::evaluated_physical_armor(base, defense, value(a), value(b), value(c), value(d)) << '\n';
            } else return 2;
        }
        return std::cin.eof() ? 0 : 2;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
