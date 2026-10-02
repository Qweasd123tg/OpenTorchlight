#pragma once

#include "torchlight/pcode_runtime.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <map>
#include <stdexcept>
#include <utility>
#include <vector>

namespace torchlight::pcode {

// Guest addresses are integers, never host pointers. Each region owns its byte
// storage and initialization flags. This is a bounded runtime memory owner, not
// an inferred original object layout or allocator. Calls retain Memory's default
// rejecting import boundary unless a production subclass explicitly overrides it.
// The owner is single-threaded; mapping changes must not race with execution.
class AddressSpace : public Memory {
public:
    struct Limits {
        std::size_t max_region_bytes;
        std::size_t max_total_bytes;
        std::size_t max_regions;
    };
    enum class Initialization { unknown, zero };

    explicit AddressSpace(Limits limits) : limits_(limits) {
        if (!limits.max_region_bytes || !limits.max_total_bytes || !limits.max_regions)
            throw std::invalid_argument("guest memory limits must be positive");
    }
    AddressSpace(const AddressSpace&) = delete;
    AddressSpace& operator=(const AddressSpace&) = delete;
    AddressSpace(AddressSpace&&) = delete;
    AddressSpace& operator=(AddressSpace&&) = delete;

    // The caller selects every guest address and initialization policy. Unknown
    // bytes remain unreadable until written; their backing storage is not a
    // zero-default guest value. Read-only unknown regions are allowed explicitly.
    void allocate(std::uint64_t base, std::size_t size,
                  Initialization initialization, bool writable = true) {
        if (initialization != Initialization::unknown && initialization != Initialization::zero)
            throw std::invalid_argument("unknown guest initialization policy");
        validate_mapping(base, size);
        Region region{std::vector<std::uint8_t>(size),
                      std::vector<std::uint8_t>(size, initialization == Initialization::zero ? 1 : 0),
                      writable};
        regions_.emplace(base, std::move(region));
        total_bytes_ += size;
    }

    // Copy the complete initialized snapshot; no borrowed host memory overlay.
    void map_snapshot(std::uint64_t base, const std::vector<std::uint8_t>& bytes,
                      bool writable = false) {
        validate_mapping(base, bytes.size());
        Region region{bytes, std::vector<std::uint8_t>(bytes.size(), 1), writable};
        regions_.emplace(base, std::move(region));
        total_bytes_ += bytes.size();
    }

    // Only an exact region start may be released. Its bytes immediately become
    // unmapped. Raw addresses have no generation tag: explicit later remapping
    // installs a new region at that address, as directed by the caller.
    void release(std::uint64_t base) {
        const auto found = regions_.find(base);
        if (found == regions_.end())
            throw std::runtime_error("guest release requires an exact mapped region start");
        total_bytes_ -= found->second.bytes.size();
        regions_.erase(found);
    }

    std::size_t region_count() const noexcept { return regions_.size(); }
    std::size_t allocated_bytes() const noexcept { return total_bytes_; }

    std::uint64_t read(std::uint64_t address, std::size_t width) override {
        validate_access(address, width);
        std::uint64_t result = 0;
        for (std::size_t i = 0; i < width; ++i) {
            const auto byte = locate(address + i);
            if (!byte.region->initialized[byte.offset])
                throw std::runtime_error("guest read of uninitialized byte");
            result |= std::uint64_t{byte.region->bytes[byte.offset]} << (8 * i);
        }
        return result;
    }

    // Adjacent segments may participate in one access. Check the full range,
    // including permissions, before publishing any byte or initialization flag.
    void write(std::uint64_t address, std::size_t width, std::uint64_t value) override {
        validate_access(address, width);
        std::array<ByteReference, 8> bytes{};
        for (std::size_t i = 0; i < width; ++i) {
            bytes[i] = locate(address + i);
            if (!bytes[i].region->writable)
                throw std::runtime_error("guest write to read-only region");
        }
        for (std::size_t i = 0; i < width; ++i) {
            bytes[i].region->bytes[bytes[i].offset] = static_cast<std::uint8_t>(value >> (8 * i));
            bytes[i].region->initialized[bytes[i].offset] = 1;
        }
    }

private:
    struct Region {
        std::vector<std::uint8_t> bytes;
        std::vector<std::uint8_t> initialized;
        bool writable;
    };
    struct ByteReference {
        Region* region = nullptr;
        std::size_t offset = 0;
    };
    Limits limits_;
    std::map<std::uint64_t, Region> regions_;
    std::size_t total_bytes_ = 0;

    static void validate_extent(std::uint64_t base, std::size_t size) {
        static_assert(sizeof(std::size_t) <= sizeof(std::uint64_t));
        if (!size) throw std::invalid_argument("guest region must not be empty");
        if (size - 1 > std::numeric_limits<std::uint64_t>::max() - base)
            throw std::runtime_error("guest address range overflows uint64");
    }

    static void validate_access(std::uint64_t base, std::size_t width) {
        if (!width || width > 8)
            throw std::invalid_argument("guest scalar width must be 1..8");
        validate_extent(base, width);
    }

    void validate_mapping(std::uint64_t base, std::size_t size) const {
        validate_extent(base, size);
        if (size > limits_.max_region_bytes ||
            size > limits_.max_total_bytes - total_bytes_ ||
            regions_.size() >= limits_.max_regions)
            throw std::runtime_error("guest region exceeds configured memory limits");
        const auto last = base + static_cast<std::uint64_t>(size - 1);
        auto next = regions_.lower_bound(base);
        if (next != regions_.end() && next->first <= last)
            throw std::runtime_error("guest regions overlap");
        if (next != regions_.begin()) {
            --next;
            const auto previous_last = next->first + (next->second.bytes.size() - 1);
            if (previous_last >= base) throw std::runtime_error("guest regions overlap");
        }
    }

    ByteReference locate(std::uint64_t address) {
        auto found = regions_.upper_bound(address);
        if (found == regions_.begin()) throw std::runtime_error("guest access to unmapped byte");
        --found;
        const auto offset = address - found->first;
        if (offset >= found->second.bytes.size())
            throw std::runtime_error("guest access to unmapped byte");
        return {&found->second, static_cast<std::size_t>(offset)};
    }
};

} // namespace torchlight::pcode
