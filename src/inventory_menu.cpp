#include "torchlight/inventory_menu.hpp"

namespace torchlight {
InventoryMenuEffects InventoryMenuState::set_open(bool open, bool close_playing) {
    const bool fresh_open = open && !state_.open();
    const PanelOpenEffects got = state_.set_open(open, close_playing);
    if (fresh_open) {
        // setOpen b4edf9..b4ee4a resets the visible/selected group on EVERY
        // fresh open, not only on construction. Reopening does not clear alerts.
        selected_ = visible_ = {true, false, false};
        tab_ = InventoryMenuTab::backpack;
    }
    if (got.update_layout) update_layout();
    InventoryMenuEffects effects;
    effects.update_layout = got.update_layout;
    effects.sound_sample = got.sound_sample;
    effects.blend_open = got.blend_open;
    effects.play_open = got.play_open;
    effects.queue_idle = got.queue_idle;
    effects.blend_close = got.blend_close;
    effects.viewport_recompute = got.viewport_recompute;
    effects.queue_tip = got.tip != -1;
    return effects;
}

bool InventoryMenuState::click_tab(int layout_function) {
    if (!dispatch_inventory_tab(state_.open(), layout_function, *this)) return false;
    tab_ = static_cast<InventoryMenuTab>(layout_function);
    return true;
}

bool InventoryMenuState::ensure_viewport(int width_px, int height_px, float yratio) {
    return state_.ensure_viewport(width_px, height_px, yratio);
}
} // namespace torchlight
