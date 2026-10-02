#pragma once
#include <cstddef>

namespace torchlight {
struct UiPausePanel {
    bool right = false;
    bool open_partial = false;
};
struct UiPauseInputs {
    bool forced = false; // CGameClient+0x10bb
    bool ui_present = true; // CGameClient+0x78
    bool console_open = false;
    int console_no_pause = 0; // CDynamicPropertyFile::GetInt result, any nonzero bypasses
    bool modal_partial = false; // CGameUI::modalDialogOpenPartial
    bool explicit_pause = false; // CGameUI+0x1999; valid initialized bool domain
};
// original-code: bothCoveredPartial @0xa82ae0 / getIsPaused @0x56e570.
// Evaluated, immutable queries only; dynamic list mutation/lifetimes and
// console/modal property owners remain with the caller, not inferred here.
[[nodiscard]] bool ui_both_covered_partial(const UiPausePanel*, std::size_t count) noexcept;
[[nodiscard]] bool ui_game_is_paused(const UiPauseInputs&, const UiPausePanel*, std::size_t count) noexcept;
} // namespace torchlight
