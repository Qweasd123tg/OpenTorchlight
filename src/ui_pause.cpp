#include "torchlight/ui_pause.hpp"

namespace torchlight {
bool ui_both_covered_partial(const UiPausePanel* panels, std::size_t count) noexcept {
    bool left = false, right = false;
    // Preserve the original two-pass query shape. No early exit is added to
    // either side's scan; original virtual getters have been evaluated by callers.
    for (std::size_t i = 0; i < count; ++i)
        if (!panels[i].right && panels[i].open_partial) left = true;
    for (std::size_t i = 0; i < count; ++i)
        if (panels[i].right && panels[i].open_partial) right = true;
    return left && right;
}
bool ui_game_is_paused(const UiPauseInputs& state, const UiPausePanel* panels, std::size_t count) noexcept {
    if (state.forced) return true;
    if (!state.ui_present) return false;
    if (ui_both_covered_partial(panels, count)) return true;
    if (state.console_open && state.console_no_pause == 0) return true;
    if (state.modal_partial) return true;
    return state.explicit_pause;
}
} // namespace torchlight
