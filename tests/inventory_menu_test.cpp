#include "torchlight/inventory_menu.hpp"
#include "torchlight/ui_screen_scale.hpp"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
// Code-first transfer test for CInventoryMenu::setOpen @0xb4eb70, tab dispatch
// from onClick @0xb4f570 and toggleInventory @0xa8ea20 (ELF SHA-256
// 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b).
//
// Viewport literals below are the output of tools/emulate_inventory_viewport.py
// (numpy binary32, op-for-op against sites 0xb4eef2-0xb4f004), NOT a second copy
// of the port formula. State-path expectations come from the recorded ASM
// behavior in research/inventory-open.md.
using namespace torchlight;
namespace {
unsigned checks = 0;
void require(bool value, const char *message) {
    ++checks;
    if (!value)
        throw std::runtime_error(message);
}
std::uint32_t bits(float value) {
    std::uint32_t out = 0;
    std::memcpy(&out, &value, sizeof(out));
    return out;
}
float lit(const char *hexfloat) { return std::strtof(hexfloat, nullptr); }
void check_viewport(int width, int height, const char *x, const char *y, const char *w,
                    const char *h) {
    const float yratio = ui_screen_ratio(width, height, UiScreenScaleRatio::y_ratio);
    const InventoryMenuViewport got = inventory_menu_viewport(width, height, yratio);
    require(bits(got.x) == bits(lit(x)), "viewport x mismatch");
    require(bits(got.y) == bits(lit(y)), "viewport y mismatch");
    require(bits(got.width) == bits(lit(w)), "viewport width mismatch");
    require(bits(got.height) == bits(lit(h)), "viewport height mismatch");
}
} // namespace
int main() {
    try {
        // Provisional sliver: base x 5000.0f collapses every case to a ~1px
        // right-edge strip. That is the recorded original behavior, not a bug
        // in the port; per-frame positioning lives in update() @0xb4f9d0.
        check_viewport(1024, 768, "0x1.ff80000000000p-1", "0x1.6000000000000p-3",
                       "0x1.0000000000000p-10", "0x1.0000000000000p-2");
        check_viewport(1280, 720, "0x1.ff999a0000000p-1", "0x1.6000000000000p-3",
                       "0x1.99999a0000000p-11", "0x1.0000000000000p-2");
        check_viewport(1920, 1080, "0x1.ffbbbc0000000p-1", "0x1.6000000000000p-3",
                       "0x1.1111120000000p-11", "0x1.0000000000000p-2");
        check_viewport(2560, 1440, "0x1.ffcccc0000000p-1", "0x1.6000000000000p-3",
                       "0x1.99999a0000000p-12", "0x1.0000000000000p-2");
        check_viewport(800, 600, "0x1.ff5c280000000p-1", "0x1.6000000000000p-3",
                       "0x1.47ae140000000p-10", "0x1.0000000000000p-2");
        check_viewport(1023, 767, "0x1.ff7fe00000000p-1", "0x1.6000000000000p-3",
                       "0x1.0040100000000p-10", "0x1.0000000000000p-2");
        check_viewport(1366, 768, "0x1.ffa00c0000000p-1", "0x1.6000000000000p-3",
                       "0x1.7fd0060000000p-11", "0x1.0000000000000p-2");
        check_viewport(3840, 2160, "0x1.ffddde0000000p-1", "0x1.6000000000000p-3",
                       "0x1.1111120000000p-12", "0x1.0000000000000p-2");
        // 8K: base x no longer overflows the unit square, so neither clamp
        // fires and the W reload @0xb4eff7 path is exercised (other cases take
        // the min-width branch and cannot distinguish it).
        check_viewport(7680, 4320, "0x1.7bd5560000000p-1", "0x1.6000000000000p-3",
                       "0x1.f200000000000p-4", "0x1.0000000000000p-2");
        // Closed + closed: store 0, no effects (site 0xb4ec55).
        {
            InventoryMenuState menu;
            const InventoryMenuEffects fx = menu.set_open(false, false);
            require(!menu.open(), "closed+closed must stay closed");
            require(!fx.update_layout && fx.sound_sample == -1 && !fx.blend_open &&
                        !fx.play_open && !fx.queue_idle && !fx.blend_close &&
                        !fx.viewport_recompute && !fx.queue_tip,
                    "closed+closed must report no effects");
        }
        // Closed + open, CLOSE playing: sample 0x16, blend OPEN, IDLE, tip,
        // viewport once, updateLayout (sites 0xb4ec90-0xb4ee6e).
        {
            InventoryMenuState menu;
            const InventoryMenuEffects fx = menu.set_open(true, true);
            require(menu.open(), "open path must set the flag");
            require(fx.sound_sample == 0x16 && fx.blend_open && !fx.play_open &&
                        fx.queue_idle && fx.viewport_recompute && fx.queue_tip &&
                        fx.update_layout && !fx.blend_close,
                    "open path effects mismatch (CLOSE playing)");
            require(menu.ensure_viewport(1920, 1080, 1.40625F), "first viewport computes");
            require(!menu.ensure_viewport(1920, 1080, 1.40625F), "viewport computes once");
            require(menu.viewport_ready(), "viewport must latch");
        }
        // Closed + open, CLOSE idle: playAnimation instead of blend.
        {
            InventoryMenuState menu;
            const InventoryMenuEffects fx = menu.set_open(true, false);
            require(menu.open() && !fx.blend_open && fx.play_open &&
                        fx.sound_sample == 0x16 && fx.queue_idle && fx.update_layout,
                    "open path effects mismatch (CLOSE idle)");
        }
        // Already open + open: store flag, only updateLayout (site 0xb4ee64).
        {
            InventoryMenuState menu;
            menu.set_open(true, false);
            const InventoryMenuEffects fx = menu.set_open(true, false);
            require(menu.open() && fx.update_layout && fx.sound_sample == -1 &&
                        !fx.blend_open && !fx.play_open && !fx.queue_idle &&
                        !fx.viewport_recompute && !fx.queue_tip,
                    "already-open path must only refresh layout");
        }
        // Open + close: sample 0x42, blend CLOSE, clear both flags, no layout/tip.
        {
            InventoryMenuState menu;
            menu.set_open(true, false);
            const InventoryMenuEffects fx = menu.set_open(false, false);
            require(!menu.open() && !menu.aux(), "close path must clear flags");
            require(fx.sound_sample == 0x42 && fx.blend_close && !fx.update_layout &&
                        !fx.queue_tip && !fx.blend_open && !fx.play_open,
                    "close path effects mismatch");
        }
        // Tabs: ignored unless open; 0x0e/0x0f/0x10 switch; 0x59 (the slot
        // value, which routes via handle_onClick, not onClick directly) does not.
        {
            InventoryMenuState menu;
            require(!menu.click_tab(0x0e), "tabs ignored unless open");
            menu.set_open(true, false);
            require(menu.click_tab(0x0f) && menu.tab() == InventoryMenuTab::spells,
                    "tab 0x0f must select spells");
            require(menu.click_tab(0x10) && menu.tab() == InventoryMenuTab::fish,
                    "tab 0x10 must select fish");
            require(menu.click_tab(0x0e) && menu.tab() == InventoryMenuTab::backpack,
                    "tab 0x0e must select backpack");
            require(!menu.click_tab(0x59) && menu.tab() == InventoryMenuTab::backpack,
                    "slot value 0x59 must not switch tabs");
            require(!menu.click_tab(0x00), "unknown tab value must be ignored");
        }
        std::cout << "inventory_menu: " << checks
                  << " assertions; original-code CInventoryMenu::setOpen paths, "
                     "onClick tabs and provisional viewport math\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
