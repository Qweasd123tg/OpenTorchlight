#include "torchlight/panel_open.hpp"

namespace torchlight {
namespace {
// menu, viewport?, consts, triples, indexed, default-on-open, tip, isa-tip,
// detach, refresh, gate. Const sources: research/panel-open.md.
const PanelProfile kInventory{"inventory", true, {124.0F, 132.0F, 166.0F, 192.0F, 5000.0F}, 1,
                              false, false, 0, false, true, true, false};
const PanelProfile kMerchant{"merchant", false, {}, 2, true, true, -1, true, false, true,
                             false};
const PanelProfile kPet{"pet", true, {97.0F, 166.0F, 135.0F, 169.0F, -5000.0F}, 1, false,
                        false, 15, false, true, true, true};
const PanelProfile kQuest{"quest", false, {}, 0, false, false, -1, false, false, false, false};
const PanelProfile kSkill{"skill", false, {}, 3, true, false, -1, false, true, false, false};
const PanelProfile kJournal{"journal", false, {}, 0, false, false, -1, false, false, false, false};
} // namespace

const PanelProfile &panel_profile_inventory() { return kInventory; }
const PanelProfile &panel_profile_merchant() { return kMerchant; }
const PanelProfile &panel_profile_pet() { return kPet; }
const PanelProfile &panel_profile_quest() { return kQuest; }
const PanelProfile &panel_profile_skill() { return kSkill; }
const PanelProfile &panel_profile_journal() { return kJournal; }

PanelViewport panel_viewport(const PanelViewportConsts &consts, int width_px, int height_px,
                             float yratio) {
    const float width = static_cast<float>(width_px);
    const float height = static_cast<float>(height_px);
    const float a = consts.a * yratio;
    const float b = consts.b * yratio;
    const float c = consts.c * yratio;
    const float d = consts.d * yratio;
    float x = (consts.base_x + a) / width;
    float y = b / height;
    float w = c / width;
    float h = d / height;
    if (x + w > 1.0F)
        w = 1.0F - x;
    if (y + h > 1.0F)
        h = 1.0F - y;
    x = (x < 0.0F) ? 0.0F : x;
    y = (y <= 0.0F) ? 0.0F : y;
    const float e = 1.0F / width;
    if (w < e) {
        x = 1.0F - e;
        w = e;
    }
    return {x, y, w, h};
}

PanelOpenEffects PanelOpenState::set_open(bool open, bool close_playing, int default_tab,
                                          bool isa_merchant, unsigned companion_mode) {
    PanelOpenEffects effects;
    const bool was_open = open_;
    if (profile_->state_gate && open && (companion_mode == 0x29 || companion_mode == 0x2a)) {
        // Pet pre-header gate (site 0xb92ad9-0xb92ae1): store requested flag,
        // skip the whole open sequence. Meanings of 0x29/0x2a are open.
        open_ = open;
        return effects;
    }
    if (!open_) {
        if (!open) {
            open_ = false;
            return effects;
        }
        effects.sound_sample = 0x16;
        if (close_playing)
            effects.blend_open = true;
        else
            effects.play_open = true;
        effects.queue_idle = true;
        effects.viewport_recompute = profile_->has_viewport && !viewport_ready_;
        if (profile_->tip_isa_switched)
            effects.tip = isa_merchant ? 0x0c : 0x05;
        else
            effects.tip = profile_->tip_open;
        if (profile_->tab_indexed && profile_->tab_default_on_open) {
            tab_index_ = (default_tab == 1 || default_tab == 2) ? default_tab : 0;
            effects.tab_index = tab_index_; // decided by this call
        }
        if (profile_->close_detaches) {
            // Recorded for shape honesty; the CEGUI child chain has no port
            // sink (detach happens on close, not open — see blend_close).
        }
    } else if (!open) {
        effects.sound_sample = 0x42;
        effects.blend_close = true;
        effects.detach_child = profile_->close_detaches;
        aux_ = false;
        open_ = false;
        return effects;
    }
    open_ = open;
    // Trailing slot +0x48 sits on the open path of every member; the profile
    // flag governs only the already-open+open path.
    effects.update_layout = !was_open ? true : profile_->refresh_on_reopen;
    return effects;
}

bool PanelOpenState::ensure_viewport(int width_px, int height_px, float yratio) {
    if (!profile_->has_viewport || viewport_ready_)
        return false;
    viewport_ = panel_viewport(profile_->viewport_consts, width_px, height_px, yratio);
    viewport_ready_ = true;
    return true;
}
} // namespace torchlight
