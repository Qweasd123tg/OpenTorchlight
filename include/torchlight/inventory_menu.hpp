#pragma once
#include "torchlight/panel_open.hpp"
#include "torchlight/inventory_events.hpp"
#include <array>

namespace torchlight {
// original-code: CInventoryMenu::setOpen @0xb4eb70 with tabs from onClick
// @0xb4f570 and toggleInventory @0xa8ea20 (ELF SHA-256
// 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b;
// analysis research/inventory-open.md).
//
// Thin inventory adapter over the shared panel_open machine: the flag machine,
// samples, animation selection, tip and provisional viewport all delegate to
// PanelOpenState with the inventory profile, so there is exactly one
// implementation of the family skeleton. Tab clicks stay here: values
// 0x0e/0x0f/0x10 come from the analyzed inventory onClick only.
// Boundary: see panel_open.hpp and research/inventory-ui-preview.md. Tab
// imagery/visibility has an opt-in static-resource consumer. Full CEGUI,
// Ogre/model/sound/tip sinks and original animated positioning remain open.
enum class InventoryMenuTab : int {
    backpack = 0x0e, // TabBackpack strings precede the +0x9120 writer
    spells = 0x0f, // TabSpell strings precede the +0x9128 writer
    fish = 0x10, // TabFish strings precede the +0x9130 writer
};

struct InventoryMenuViewport {
    float x = 0.0F;
    float y = 0.0F;
    float width = 0.0F;
    float height = 0.0F;
};

// Same contract as PanelOpenState::panel_viewport with the inventory consts
// (124/132/166/192, base 5000.0f); kept so existing callers do not churn.
[[nodiscard]] inline InventoryMenuViewport inventory_menu_viewport(int width_px, int height_px,
                                                                  float yratio) {
    const PanelViewport got =
        panel_viewport(panel_profile_inventory().viewport_consts, width_px, height_px, yratio);
    return {got.x, got.y, got.width, got.height};
}

struct InventoryMenuEffects {
    bool update_layout = false;
    int sound_sample = -1; // 0x16 open, 0x42 close, -1 none (open: no sink)
    bool blend_open = false;
    bool play_open = false;
    bool queue_idle = false;
    bool blend_close = false;
    bool viewport_recompute = false;
    bool queue_tip = false;
};

class InventoryMenuState : private InventoryTabSink {
public:
    [[nodiscard]] bool open() const noexcept { return state_.open(); }
    [[nodiscard]] bool aux() const noexcept { return state_.aux(); }
    [[nodiscard]] InventoryMenuTab tab() const noexcept { return tab_; }
    [[nodiscard]] bool viewport_ready() const noexcept { return state_.viewport_ready(); }
    [[nodiscard]] const PanelViewport &viewport() const noexcept { return state_.viewport(); }

    InventoryMenuEffects set_open(bool open, bool close_playing);
    // Called by the opt-in resource UI's real MouseButtonDown route.
    bool click_tab(int layout_function);
    bool ensure_viewport(int width_px, int height_px, float yratio);
    [[nodiscard]] bool tab_selected(std::size_t i) const { return selected_.at(i); }
    [[nodiscard]] bool container_visible(std::size_t i) const { return visible_.at(i); }
    [[nodiscard]] bool tab_alert(std::size_t i) const { return alerts_.at(i); }
    [[nodiscard]] bool restored_image(std::size_t i) const { return restored_.at(i); }
    [[nodiscard]] unsigned layout_revision() const { return layout_revision_; }

private:
    void select(std::size_t i, bool value) override { selected_.at(i) = value; }
    void show(std::size_t i, bool value) override { visible_.at(i) = value; }
    void clear_alert(std::size_t i) override { alerts_.at(i) = false; }
    void restore_unselected_image(std::size_t i) override { restored_.at(i) = true; }
    // Consumer re-resolves the resource UI from this state; full original
    // icon/tooltip updateLayout effects remain open.
    void update_layout() override { ++layout_revision_; }
    PanelOpenState state_{panel_profile_inventory()};
    InventoryMenuTab tab_ = InventoryMenuTab::backpack;
    std::array<bool, 3> selected_{true, false, false}, visible_{true, false, false};
    std::array<bool, 3> alerts_{}, restored_{};
    unsigned layout_revision_ = 0;
};
} // namespace torchlight
