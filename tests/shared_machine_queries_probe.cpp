// Engine calibration only: original field offsets are explicit fixture data,
// not reconstructed C++ objects or a new Application binding.
#include "torchlight/lifted_address_space.hpp"
#include "torchlight/generated/shared_machine.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace {
constexpr std::uint64_t owner = 0x10000, elements = 0x30000;
constexpr std::uint64_t stack = 0x50000, sentinel = 0x7ff00000;
void put(std::vector<std::uint8_t>& bytes, std::size_t at,
         std::size_t width, std::uint64_t bits) {
    for (std::size_t n = 0; n < width; ++n)
        bytes.at(at + n) = static_cast<std::uint8_t>(bits >> (n * 8));
}
}
int main() { try {
    std::string command;
    while (std::cin >> command) {
        torchlight::pcode::AddressSpace memory({65536, 131072, 8});
        torchlight::pcode::RegisterFile machine;
        memory.allocate(stack, 128, torchlight::pcode::AddressSpace::Initialization::unknown);
        memory.write(stack + 64, 8, sentinel);
        machine.write(0x20, 8, stack + 64);
        if (command == "g") {
            std::size_t count;
            std::uint32_t index;
            if (!(std::cin >> count >> index) || count > 4096)
                throw std::runtime_error("invalid engine int fixture");
            std::vector<std::uint8_t> properties(128), values(count * 4);
            put(properties, 0x40, 8, elements);
            put(properties, 0x48, 8, elements + count * 4);
            for (std::size_t n = 0; n < count; ++n) {
                std::uint32_t bits;
                if (!(std::cin >> bits)) throw std::runtime_error("missing engine int value");
                put(values, n * 4, 4, bits);
            }
            memory.map_snapshot(owner, properties);
            if (count) memory.map_snapshot(elements, values);
            machine.write(0x38, 8, owner);
            machine.write(0x30, 4, index);
            torchlight::pcode_machine::fn_00c6e440(memory, machine, sentinel);
            std::cout << machine.read(0, 4) << '\n';
        } else if (command == "d") {
            torchlight::pcode_machine::fn_00b05e80(memory, machine, sentinel);
            std::cout << machine.read(0, 1) << '\n';
        } else throw std::runtime_error("unknown engine fixture command");
        if (machine.read(0x20, 8) != stack + 72 || machine.read(0x288, 8) != sentinel)
            throw std::runtime_error("shared machine RET state differs");
    }
    return 0;
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }
