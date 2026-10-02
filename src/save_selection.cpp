#include "torchlight/save_store.hpp"
#include "torchlight/generated/ui_state_queries.hpp"
#include <cstring>
#include <limits>
#include <stdexcept>

namespace torchlight {
namespace {
constexpr std::uint64_t object = 0x10000, stack = 0x20000;
constexpr std::uint64_t manager = 0x40000, ui = 0x50000;
constexpr std::uint64_t vector_base = 0x30000, save_base = 0x100000000, sentinel = 0x7ff00000;
class SelectionMemory final : public pcode::Memory {
    const std::vector<SaveSlotInfo>& saves_;
    std::size_t selected_;
public:
    SelectionMemory(const std::vector<SaveSlotInfo>& saves, std::size_t selected)
        : saves_(saves), selected_(selected) {}
    std::uint64_t read(std::uint64_t address, std::size_t width) override {
        if (address == stack && width == 8) return sentinel;
        if (address == ui + 0x588 && width == 8) return manager;
        if (address == manager + 0xde8 && width == 8) return object;
        if (address == object + 0x1e8 && width == 8) return vector_base;
        if (address == object + 0x1f0 && width == 8) return vector_base + saves_.size() * 8;
        if (address == object + 0xc8 && width == 4) return selected_;
        if (address == vector_base + selected_ * 8 && width == 8 && selected_ < saves_.size())
            return save_base;
        if (address == save_base + 0xe0 && width == 4 && selected_ < saves_.size()) {
            std::uint32_t bits = 0;
            static_assert(sizeof(bits) == sizeof(saves_[selected_].health));
            std::memcpy(&bits, &saves_[selected_].health, sizeof(bits));
            return bits;
        }
        // original-code: binary32 +0 literal @0xfa47f8, pinned by native comparison.
        if (address == 0xfa47f8 && width == 4) return 0;
        throw std::logic_error("Continue p-code read outside reviewed binding");
    }
    void write(std::uint64_t, std::size_t, std::uint64_t) override {
        throw std::logic_error("Continue query attempted a memory write");
    }
};
class FilenameCountMemory final : public pcode::Memory {
    std::size_t count_;
public:
    explicit FilenameCountMemory(std::size_t count) : count_(count) {}
    std::uint64_t read(std::uint64_t address, std::size_t width) override {
        if (address == stack && width == 8) return sentinel;
        if (address == ui + 0x588 && width == 8) return manager;
        if (address == manager + 0xde8 && width == 8) return object;
        if (address == object + 0x218 && width == 8) return vector_base;
        if (address == object + 0x220 && width == 8)
            return vector_base + static_cast<std::uint64_t>(count_) * 8;
        throw std::logic_error("canLoad p-code read outside filename-count binding");
    }
    void write(std::uint64_t, std::size_t, std::uint64_t) override {
        throw std::logic_error("canLoad query attempted a memory write");
    }
};
} // namespace
bool save_list_can_load(std::size_t filename_count) noexcept {
    FilenameCountMemory memory(filename_count);
    pcode::RegisterFile registers;
    registers.write(0x38, 8, ui);
    registers.write(0x20, 8, stack);
    return pcode_generated::fn_00a84d20(memory, registers, sentinel) != 0;
}
const SaveSlotInfo* selected_continue_save(const std::vector<SaveSlotInfo>& saves,
                                         std::size_t selected) noexcept {
    // Portable input boundary: reject indices outside the original signed32
    // domain, and OTC rows the codec could not read. Never choose another row.
    if (selected >= saves.size() || saves.size() > static_cast<std::size_t>(std::numeric_limits<std::int32_t>::max()))
        return nullptr;
    const auto& save = saves[selected];
    if (!save.loadable()) return nullptr;
    SelectionMemory memory(saves, selected);
    pcode::RegisterFile registers;
    registers.write(0x38, 8, ui);
    registers.write(0x20, 8, stack);
    return pcode_generated::fn_00a84d30(memory, registers, sentinel) != 0 ? &save : nullptr;
}
} // namespace torchlight
