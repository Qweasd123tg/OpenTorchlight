#include "torchlight/progression.hpp"
#include <cstring>
#include <iostream>
int main() {
    try {
        std::uint32_t a, b;
        while (std::cin >> a >> b) {
            float value, percent;
            std::memcpy(&value, &a, 4); std::memcpy(&percent, &b, 4);
            std::cout << torchlight::evaluated_world_gold(value, percent) << '\n';
        }
        if (!std::cin.eof()) return 2;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
