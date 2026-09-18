#include "torchlight/equipment.hpp"
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdexcept>

int main() {
    try {
        unsigned operation;
        std::uint32_t graph_bits, percent;
        std::int32_t count;
        while (std::cin >> operation >> graph_bits >> percent >> count) {
            if (operation > 1) throw std::runtime_error("Invalid operation");
            float graph; std::memcpy(&graph, &graph_bits, sizeof(graph));
            const auto result = torchlight::item_graph_stat(graph, percent, count, operation == 1);
            // Regression witness only, not an alternate runtime implementation.
            const auto old = std::max(1, static_cast<std::int32_t>(std::ceil(
                graph * static_cast<float>(percent + std::clamp(count, 0, 5) * 10) / 100.0F)));
            std::cout << result << ' ' << old << '\n';
        }
        if (!std::cin.eof()) throw std::runtime_error("Malformed input");
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
