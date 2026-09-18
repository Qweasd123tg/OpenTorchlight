#include "torchlight/panel_open.hpp"
#include "torchlight/ui_screen_scale.hpp"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
// Code-first family transfer test: panel setOpen skeleton shared by
// CInventoryMenu @0xb4eb70, CMerchantMenu @0xb6a220, CPetMenu @0xb92aa0,
// CQuestMenu @0xbc2550, CSkillMenu @0xbe1130, CJournalMenu @0xe3a680
// (ELF SHA-256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88
// b5d41724b; analysis research/panel-open.md).
//
// The shared 4-path skeleton is asserted per profile in a loop; each member's
// delta gets its own checks. Pet viewport literals come from numpy binary32
// emulation with pet consts (97/166/135/169, base -5000.0f); inventory
// literals live in tests/inventory_menu_test.cpp and are not duplicated here.
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
bool no_effects(const PanelOpenEffects &fx) {
    return !fx.update_layout && fx.sound_sample == -1 && !fx.blend_open && !fx.play_open &&
           !fx.queue_idle && !fx.blend_close && !fx.viewport_recompute && fx.tip == -1 &&
           !fx.detach_child && fx.tab_index == -1;
}
void check_skeleton(const PanelProfile &profile) {
    // Closed + closed: store 0, nothing else.
    {
        PanelOpenState menu(profile);
        require(no_effects(menu.set_open(false, false)) && !menu.open(), "closed+closed");
    }
    // Closed + open: sample 0x16, OPEN by play (CLOSE idle), IDLE always.
    {
        PanelOpenState menu(profile);
        const PanelOpenEffects fx = menu.set_open(true, false);
        require(menu.open(), "open flag");
        require(fx.sound_sample == 0x16 && !fx.blend_open && fx.play_open && fx.queue_idle &&
                    !fx.blend_close,
                "open samples/animation");
        require(fx.viewport_recompute == profile.has_viewport,
                "viewport recompute flag follows the block");
        require(fx.update_layout, "open path refreshes layout");
        if (profile.has_viewport)
            require(menu.ensure_viewport(1920, 1080, 1.40625F) &&
                        !menu.ensure_viewport(1920, 1080, 1.40625F),
                    "viewport latches once");
        else
            require(!menu.ensure_viewport(1920, 1080, 1.40625F), "no viewport without block");
    }
    // Already open + open: store; layout refresh per profile.
    {
        PanelOpenState menu(profile);
        menu.set_open(true, false);
        const PanelOpenEffects fx = menu.set_open(true, false);
        require(menu.open() && fx.sound_sample == -1 && !fx.blend_open && !fx.play_open &&
                    !fx.queue_idle && !fx.viewport_recompute && fx.tip == -1,
                "reopen reports nothing but layout");
        require(fx.update_layout == profile.refresh_on_reopen, "reopen refresh rule");
    }
    // Open + close: sample 0x42, CLOSE blend, flags cleared, no layout.
    {
        PanelOpenState menu(profile);
        menu.set_open(true, false);
        const PanelOpenEffects fx = menu.set_open(false, false);
        require(!menu.open() && !menu.aux(), "close clears flags");
        require(fx.sound_sample == 0x42 && fx.blend_close && !fx.update_layout &&
                    fx.detach_child == profile.close_detaches,
                "close effects");
    }
}
void check_pet_viewport(int width, int height, const char *x, const char *y, const char *w,
                        const char *h) {
    const float yratio = ui_screen_ratio(width, height, UiScreenScaleRatio::y_ratio);
    const PanelViewport got =
        panel_viewport(panel_profile_pet().viewport_consts, width, height, yratio);
    require(bits(got.x) == bits(lit(x)), "pet viewport x mismatch");
    require(bits(got.y) == bits(lit(y)), "pet viewport y mismatch");
    require(bits(got.width) == bits(lit(w)), "pet viewport width mismatch");
    require(bits(got.height) == bits(lit(h)), "pet viewport height mismatch");
}
} // namespace
int main() {
    try {
        check_skeleton(panel_profile_inventory());
        check_skeleton(panel_profile_merchant());
        check_skeleton(panel_profile_pet());
        check_skeleton(panel_profile_quest());
        check_skeleton(panel_profile_skill());
        check_skeleton(panel_profile_journal());
        // Pet parks at the LEFT edge (base -5000.0f), not the inventory sliver.
        check_pet_viewport(1024, 768, "0x0.0p+0", "0x1.baaaaa0000000p-3",
                           "0x1.0e00000000000p-3", "0x1.c2aaaa0000000p-3");
        check_pet_viewport(1920, 1080, "0x0.0p+0", "0x1.baaaaa0000000p-3",
                           "0x1.9500000000000p-4", "0x1.c2aaaa0000000p-3");
        check_pet_viewport(1023, 767, "0x0.0p+0", "0x1.baaaac0000000p-3",
                           "0x1.0de97a0000000p-3", "0x1.c2aaac0000000p-3");
        check_pet_viewport(7680, 4320, "0x0.0p+0", "0x1.baaaaa0000000p-3",
                           "0x1.9500000000000p-4", "0x1.c2aaaa0000000p-3");
        // Merchant tab index follows the owner default (1/2/other->0).
        {
            PanelOpenState menu(panel_profile_merchant());
            require(menu.set_open(true, false, 1).tab_index == 1, "merchant tab 1");
            PanelOpenState second(panel_profile_merchant());
            require(second.set_open(true, false, 2).tab_index == 2, "merchant tab 2");
            PanelOpenState other(panel_profile_merchant());
            require(other.set_open(true, false, 7).tab_index == 0, "merchant tab default 0");
        }
        // Merchant tip switch: ISA(0x7f) selects 0x0c, else 0x05.
        {
            PanelOpenState menu(panel_profile_merchant());
            require(menu.set_open(true, false, 0, true).tip == 0x0c, "merchant tip ISA");
            PanelOpenState plain(panel_profile_merchant());
            require(plain.set_open(true, false, 0, false).tip == 0x05, "merchant tip plain");
        }
        // Skill index persists (open path never writes it); writer is open.
        {
            PanelOpenState menu(panel_profile_skill());
            menu.set_tab_index(2);
            require(menu.set_open(true, false).tab_index == -1, "skill open reports no index");
            require(menu.tab_index() == 2, "skill index preserved");
        }
        // Pet state gate: 0x29/0x2a veto the open sequence (meanings open).
        {
            PanelOpenState menu(panel_profile_pet());
            const PanelOpenEffects fx = menu.set_open(true, false, 0, false, 0x29);
            require(menu.open() && no_effects(fx), "pet gate 0x29 stores silently");
            PanelOpenState second(panel_profile_pet());
            const PanelOpenEffects other = second.set_open(true, false, 0, false, 0x28);
            require(other.sound_sample == 0x16 && other.update_layout, "pet gate passes 0x28");
        }
        // Inventory tip is unconditional 0 on open; quest/skill/journal have none.
        {
            PanelOpenState menu(panel_profile_inventory());
            require(menu.set_open(true, false).tip == 0, "inventory tip 0");
            PanelOpenState quest(panel_profile_quest());
            require(quest.set_open(true, false).tip == -1, "quest has no tip");
        }
        std::cout << "panel_open: " << checks
                  << " assertions; shared setOpen skeleton x6 profiles plus deltas\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
