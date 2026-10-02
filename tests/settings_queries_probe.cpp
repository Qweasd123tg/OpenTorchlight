#include "torchlight/ui_int_property.hpp"
#include "torchlight/ui_dropdown.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    char operation;
    while (std::cin >> operation) {
        if (operation == 'g') {
            std::uint64_t count, index;
            if (!(std::cin >> count >> index) || count > 4096 ||
                index > std::numeric_limits<std::uint32_t>::max()) return 2;
            std::vector<std::int32_t> values(static_cast<std::size_t>(count));
            for (auto& value : values) {
                std::uint64_t incoming;
                if (!(std::cin >> incoming) || incoming > std::numeric_limits<std::uint32_t>::max()) return 2;
                const auto raw = static_cast<std::uint32_t>(incoming);
                static_assert(sizeof(raw) == sizeof(value));
                std::memcpy(&value, &raw, sizeof(value));
            }
            const auto result = torchlight::ui_int_property(values.data(), values.size(),
                static_cast<std::uint32_t>(index));
            std::uint32_t bits;
            static_assert(sizeof(result) == sizeof(bits));
            std::memcpy(&bits, &result, sizeof(bits));
            std::cout << bits << '\n';
        } else if (operation == 'd') {
            std::cout << static_cast<unsigned>(torchlight::dropdown_default_double_click()) << '\n';
        } else return 2;
    }
    return std::cin.eof() ? 0 : 2;
}
