#include "torchlight/ui_int_property.hpp"
#include "torchlight/generated/ui_state_queries.hpp"
#include <cstring>
#include <limits>
#include <stdexcept>

namespace torchlight {
namespace {
constexpr std::uint64_t properties = 0x10000, integer_array = 0x40000;
constexpr std::uint64_t stack_entry = 0x20000, return_sentinel = 0x7ff00000;

class IntPropertyMemory final : public pcode::Memory {
    const std::int32_t* values_;
    std::uint64_t end_;
    pcode::ByteState<8> return_slot_;
public:
    IntPropertyMemory(const std::int32_t* values, std::size_t count) : values_(values) {
        constexpr auto maximum_count =
            (std::numeric_limits<std::uint64_t>::max() - integer_array) / sizeof(std::int32_t);
        if (count > maximum_count)
            throw std::invalid_argument("UI int property table exceeds pointer64 bounds");
        if (count && !values)
            throw std::invalid_argument("UI int property table is null but nonempty");
        end_ = integer_array + static_cast<std::uint64_t>(count) * sizeof(std::int32_t);
        return_slot_.write(0, 8, return_sentinel);
    }
    std::uint64_t read(std::uint64_t address, std::size_t width) override {
        if (address == stack_entry && width == 8)
            return return_slot_.read(0, 8, "UI int query read of uninitialized return slot");
        if (address == properties + 0x40 && width == 8) return integer_array;
        if (address == properties + 0x48 && width == 8) return end_;
        if (width == 4 && address >= integer_array && address < end_ &&
            (address - integer_array) % sizeof(std::int32_t) == 0) {
            const auto index = static_cast<std::size_t>((address - integer_array) / sizeof(std::int32_t));
            std::uint32_t bits = 0;
            std::memcpy(&bits, &values_[index], sizeof(bits));
            return bits;
        }
        throw std::logic_error("UI int property read outside reviewed binding");
    }
    void write(std::uint64_t, std::size_t, std::uint64_t) override {
        throw std::logic_error("UI int property query attempted a memory write");
    }
};
} // namespace

std::int32_t ui_int_property(const std::int32_t* values, std::size_t count, std::uint32_t index) {
    IntPropertyMemory memory(values, count);
    pcode::RegisterFile registers;
    registers.write(0x38, 8, properties); // RDI: borrowed property-vector owner view
    registers.write(0x30, 4, index); // ESI: original unsigned32 index
    registers.write(0x20, 8, stack_entry); // RSP: actual private RET memory slot
    const auto scalar = static_cast<std::uint32_t>(
        pcode_generated::fn_00c6e440(memory, registers, return_sentinel));
    std::int32_t value = 0;
    std::memcpy(&value, &scalar, sizeof(value));
    return value;
}
} // namespace torchlight
