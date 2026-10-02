#include "torchlight/lifted_address_space.hpp"

#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

namespace {
using torchlight::pcode::AddressSpace;
using Initialization = AddressSpace::Initialization;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

template<class Action> void rejected(Action action, const char* message) {
    bool failed = false;
    try { action(); }
    catch (const std::exception&) { failed = true; }
    require(failed, message);
}

void snapshots_and_cross_segment_access() {
    AddressSpace memory({32, 128, 16});
    std::vector<std::uint8_t> source{0x11, 0x22, 0x33};
    memory.map_snapshot(0x1000, source, true);
    source[0] = 0xee;
    memory.map_snapshot(0x1003, {0x44, 0x55, 0x66, 0x77, 0x88}, true);
    require(memory.read(0x1000, 8) == UINT64_C(0x8877665544332211),
            "snapshot aliasing, cross-segment access or little-endian order changed");
    const std::uint64_t expected[] = {
        0x11, 0x2211, 0x332211, 0x44332211,
        UINT64_C(0x5544332211), UINT64_C(0x665544332211),
        UINT64_C(0x77665544332211), UINT64_C(0x8877665544332211)};
    for (std::size_t width = 1; width <= 8; ++width)
        require(memory.read(0x1000, width) == expected[width - 1], "scalar read width changed");
    memory.write(0x1001, 6, UINT64_C(0xffa6a5a4a3a2a1));
    require(memory.read(0x1000, 8) == UINT64_C(0x88a6a5a4a3a2a111),
            "cross-segment write changed unrelated bytes or stored excess value bits");
    memory.allocate(0x2000, 8, Initialization::zero);
    require(memory.read(0x2000, 8) == 0, "explicit zero initialization was not readable");
    memory.map_snapshot(0x3000, {0x5a}); // Default snapshot is read-only.
    rejected([&] { memory.write(0x3000, 1, 0); }, "default snapshot was writable");
    require(memory.read(0x3000, 1) == 0x5a, "read-only snapshot changed");
    rejected([&] { memory.read(0x1000, 0); }, "zero-width read accepted");
    rejected([&] { memory.write(0x1000, 9, 0); }, "wide scalar write accepted");
    rejected([&] { memory.read(0x0fff, 2); }, "read crossed an unmapped initial byte");
}

void unknown_bytes_and_atomic_writes() {
    AddressSpace memory({16, 64, 8});
    memory.allocate(0x100, 4, Initialization::unknown);
    rejected([&] { memory.read(0x100, 1); }, "unknown byte became a zero-default read");
    memory.write(0x100, 2, 0x2211);
    require(memory.read(0x100, 2) == 0x2211, "written unknown bytes stayed unreadable");
    rejected([&] { memory.read(0x100, 4); }, "partially initialized range was readable");
    memory.map_snapshot(0x104, {0x55, 0x66});
    rejected([&] { memory.write(0x100, 6, UINT64_C(0xabcdefabcdef)); },
             "write crossed a read-only neighbor");
    require(memory.read(0x100, 2) == 0x2211 && memory.read(0x104, 2) == 0x6655,
            "rejected read-only crossing partially mutated initialized bytes");
    rejected([&] { memory.read(0x102, 1); }, "rejected write initialized an unknown byte");
    memory.write(0x102, 2, 0x4433);
    require(memory.read(0x100, 4) == 0x44332211, "partial initialization could not be completed");

    memory.allocate(0x200, 2, Initialization::unknown);
    memory.map_snapshot(0x203, {0x77}, true); // The byte at 0x202 is a gap.
    rejected([&] { memory.write(0x200, 4, 0x12345678); }, "write crossed a gap");
    rejected([&] { memory.read(0x200, 1); }, "gap failure initialized its writable prefix");
    require(memory.read(0x203, 1) == 0x77, "gap failure mutated its mapped suffix");
    rejected([&] { memory.read(0x201, 3); }, "read crossed unknown bytes and a gap");
}

void overlap_limits_and_release() {
    AddressSpace memory({8, 12, 2});
    memory.map_snapshot(0x100, {1, 2, 3, 4}, true);
    rejected([&] { memory.allocate(0x0ff, 2, Initialization::zero); }, "left overlap accepted");
    rejected([&] { memory.allocate(0x103, 2, Initialization::zero); }, "right overlap accepted");
    rejected([&] { memory.allocate(0x100, 4, Initialization::zero); }, "duplicate mapping accepted");
    rejected([&] { memory.allocate(0x101, 1, Initialization::zero); }, "contained overlap accepted");
    rejected([&] { memory.allocate(0x200, 9, Initialization::zero); }, "region size limit ignored");
    rejected([&] { memory.allocate(0x200, 0, Initialization::zero); }, "empty allocation accepted");
    memory.allocate(0x104, 8, Initialization::zero);
    require(memory.region_count() == 2 && memory.allocated_bytes() == 12,
            "failed maps changed accounting or adjacent maps were rejected");
    rejected([&] { memory.allocate(0x300, 1, Initialization::zero); }, "total/count limits ignored");
    rejected([&] { memory.release(0x105); }, "interior pointer released a region");
    require(memory.read(0x104, 8) == 0, "interior release changed its region");
    memory.release(0x104);
    rejected([&] { memory.read(0x104, 1); }, "released byte stayed mapped");
    rejected([&] { memory.write(0x104, 1, 1); }, "released byte stayed writable");
    rejected([&] { memory.release(0x104); }, "double release accepted");
    require(memory.region_count() == 1 && memory.allocated_bytes() == 4 && memory.read(0x100, 4) == 0x04030201,
            "release damaged a neighbor or accounting");
    memory.allocate(0x104, 8, Initialization::unknown);
    rejected([&] { memory.read(0x104, 1); }, "explicit remap retained released initialization");
    AddressSpace count_limited({8, 32, 1});
    count_limited.allocate(0, 1, Initialization::zero);
    rejected([&] { count_limited.allocate(2, 1, Initialization::zero); }, "region count limit ignored");
    AddressSpace total_limited({8, 9, 8});
    total_limited.allocate(0, 8, Initialization::zero);
    rejected([&] { total_limited.allocate(16, 2, Initialization::zero); }, "total byte limit ignored");
}

void address_overflow_and_import_boundary() {
    constexpr auto top = std::numeric_limits<std::uint64_t>::max();
    AddressSpace memory({16, 32, 8});
    memory.map_snapshot(top - 3, {1, 2, 3, 4}, true);
    require(memory.read(top - 3, 4) == 0x04030201 && memory.read(top, 1) == 4,
            "valid top-of-address-space bytes were rejected");
    rejected([&] { memory.allocate(top - 1, 3, Initialization::zero); }, "mapping overflow accepted");
    rejected([&] { memory.read(top, 2); }, "read address overflow accepted");
    rejected([&] { memory.write(top - 1, 4, 0); }, "write address overflow accepted");
    require(memory.read(top - 3, 4) == 0x04030201, "overflow write partially changed memory");
    memory.write(top, 1, 0xaa);
    require(memory.read(top, 1) == 0xaa, "last uint64 address could not be written");
    memory.allocate(0, 1, Initialization::zero);
    require(memory.read(0, 1) == 0, "guest address zero was mistaken for a host null pointer");
    torchlight::pcode::RegisterFile arguments, result;
    rejected([&] { memory.invoke_import({1, 2, 0, 3}, arguments, result); },
             "unknown import silently became a stub");
    rejected([] { AddressSpace invalid({0, 8, 1}); }, "zero region limit accepted");
    rejected([] { AddressSpace invalid({8, 0, 1}); }, "zero total limit accepted");
    rejected([] { AddressSpace invalid({8, 8, 0}); }, "zero count limit accepted");
}
}

int main() {
    try {
        snapshots_and_cross_segment_access();
        unknown_bytes_and_atomic_writes();
        overlap_limits_and_release();
        address_overflow_and_import_boundary();
        std::cout << "PASS: bounded guest snapshots, initialization, atomic cross-region writes and release\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
