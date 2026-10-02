#pragma once
#include <cstdint>

namespace torchlight {
// original-code: CGameUI+0x1914/+0x1918 are u32 fields. Constructor
// @0xaa6838/@0xaa6847 initializes both to EGameState/EMenu sentinel 6.
// The port owns the pair; generated original operations access these members
// through a checked memory binding, without assuming the native object layout.
struct UiGameStateRequest {
    std::uint32_t state = 6;
    std::uint32_t menu = 6;
    [[nodiscard]] bool pending() const noexcept { return state != 6; }
};
// Whole writer bodies @0xa828f0 and @0xa82900, generated from raw p-code.
void ui_request_game_state(UiGameStateRequest&, std::uint32_t state, std::uint32_t menu);
void ui_clear_game_state_request(UiGameStateRequest&);
} // namespace torchlight
