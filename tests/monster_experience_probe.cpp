#include "torchlight/progression.hpp"
#include <cstring>
#include <iostream>
int main() {
    try {
        std::uint32_t bits;
        while (std::cin >> bits) {
            float graph_value;
            std::memcpy(&graph_value, &bits, 4);
            std::cout << torchlight::original_monster_experience(graph_value) << '\n';
        }
        if (!std::cin.eof()) return 2;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
