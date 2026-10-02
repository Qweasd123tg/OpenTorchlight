#include "torchlight/save_store.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::size_t count = 0, selected = 0;
    while (std::cin >> count >> selected) {
        if (count > 128) return 2;
        std::vector<torchlight::SaveSlotInfo> saves(count);
        for (auto& save : saves) {
            std::uint32_t bits = 0;
            if (!(std::cin >> bits)) return 2;
            static_assert(sizeof(save.health) == sizeof(bits));
            std::memcpy(&save.health, &bits, sizeof(bits));
        }
        std::cout << (torchlight::selected_continue_save(saves, selected) != nullptr) << '\n';
    }
    return std::cin.eof() ? 0 : 2;
}
