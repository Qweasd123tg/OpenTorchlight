#include "torchlight/ui_screen_scale.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

namespace {
float value(std::uint32_t bits) {
    float result;
    static_assert(sizeof(result)==sizeof(bits));
    std::memcpy(&result,&bits,sizeof(result));
    return result;
}
std::uint32_t bits(float number) {
    std::uint32_t result;
    std::memcpy(&result,&number,sizeof(result));
    return result;
}
}

int main() {
    char operation;
    while (std::cin >> operation) {
        if (operation=='s') {
            std::uint32_t offset,ratio;
            if (!(std::cin >> offset >> ratio)) return 2;
            std::cout << bits(torchlight::ui_scale_offset(value(offset),value(ratio))) << '\n';
        } else if (operation=='g') {
            std::size_t count;
            std::uint32_t index;
            if (!(std::cin >> count >> index)) return 2;
            std::vector<float> values(count);
            for (auto& number : values) {
                std::uint32_t raw;
                if (!(std::cin >> raw)) return 2;
                number=value(raw);
            }
            std::cout << bits(torchlight::ui_float_property(values.data(),values.size(),index)) << '\n';
        } else return 2;
    }
    return std::cin.eof() ? 0 : 2;
}
