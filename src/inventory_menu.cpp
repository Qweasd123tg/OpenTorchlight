#include "torchlight/inventory_menu.hpp"

namespace torchlight {
InventoryMenuEffects InventoryMenuState::set_open(bool open, bool close_playing) {
    const PanelOpenEffects got = state_.set_open(open, close_playing);
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
    if (!state_.open())
        return false; // site 0xb4f57c: clicks ignored unless open
    const auto tab = static_cast<InventoryMenuTab>(layout_function);
    if (tab != InventoryMenuTab::backpack && tab != InventoryMenuTab::spells &&
        tab != InventoryMenuTab::fish)
        return false; // unknown values fall through to `return 1`
    tab_ = tab;
    return true;
}

bool InventoryMenuState::ensure_viewport(int width_px, int height_px, float yratio) {
    return state_.ensure_viewport(width_px, height_px, yratio);
}
} // namespace torchlight
