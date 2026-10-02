#include "torchlight/save_store.hpp"
#include <cstddef>
#include <iostream>

int main() {
    std::size_t filename_count = 0;
    while (std::cin >> filename_count)
        std::cout << torchlight::save_list_can_load(filename_count) << '\n';
    return std::cin.eof() ? 0 : 2;
}
