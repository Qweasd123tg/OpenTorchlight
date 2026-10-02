#include "torchlight/ui_game_state.hpp"
#include "torchlight/generated/ui_state_queries.hpp"
#include <stdexcept>

namespace torchlight {
namespace {
constexpr std::uint64_t object = 0x10000, stack = 0x20000, sentinel = 0x7ff00000;
class RequestMemory final : public pcode::Memory {
    UiGameStateRequest& owner_;
public:
    explicit RequestMemory(UiGameStateRequest& owner) : owner_(owner) {}
    std::uint64_t read(std::uint64_t address, std::size_t width) override {
        if (address == stack && width == 8) return sentinel;
        throw std::logic_error("UI request p-code read outside reviewed binding");
    }
    void write(std::uint64_t address, std::size_t width, std::uint64_t value) override {
        if (width == 4 && address == object + 0x1914)
            owner_.state = static_cast<std::uint32_t>(value);
        else if (width == 4 && address == object + 0x1918)
            owner_.menu = static_cast<std::uint32_t>(value);
        else throw std::logic_error("UI request p-code write outside reviewed binding");
    }
};
void initialize(pcode::RegisterFile& registers) {
    registers.write(0x38, 8, object); // RDI: semantic owner base
    registers.write(0x20, 8, stack); // RSP: explicit private return slot
}
} // namespace
void ui_request_game_state(UiGameStateRequest& owner, std::uint32_t state, std::uint32_t menu) {
    RequestMemory memory(owner);
    pcode::RegisterFile registers;
    initialize(registers);
    registers.write(0x30, 4, state); // ESI
    registers.write(0x10, 4, menu); // EDX
    pcode_generated::fn_00a828f0(memory, registers, sentinel);
}
void ui_clear_game_state_request(UiGameStateRequest& owner) {
    RequestMemory memory(owner);
    pcode::RegisterFile registers;
    initialize(registers);
    pcode_generated::fn_00a82900(memory, registers, sentinel);
}
} // namespace torchlight
