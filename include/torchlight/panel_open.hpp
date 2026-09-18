#pragma once

namespace torchlight {
// original-code: panel setOpen family — CInventoryMenu @0xb4eb70,
// CMerchantMenu @0xb6a220, CPetMenu @0xb92aa0, CQuestMenu @0xbc2550,
// CSkillMenu @0xbe1130, CJournalMenu @0xe3a680 (ELF SHA-256
// 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b;
// analysis research/inventory-open.md, research/panel-open.md).
//
// One shared flag machine with a per-menu parameter table. Field OFFSETS are
// never transferred (each class has its own layout); only roles, order,
// constants and branch conditions are. Boundary per member is in its profile:
// CEGUI windows, Ogre viewport/camera creation, model animation, sound
// samples, tips and updateLayout contents are reported as effects, not
// executed. Viewport math is exact (see inventory_menu_viewport precedent);
// the rect stays provisional (per-frame positioning lives in update()).
struct PanelViewportConsts {
    float a = 0.0F; // first scaledY const
    float b = 0.0F; // second scaledY const
    float c = 0.0F; // third scaledY const
    float d = 0.0F; // fourth scaledY const
    float base_x = 0.0F; // viewport x base field (+0x9184 inventory, +0x91b4 pet)
};

struct PanelViewport {
    float x = 0.0F;
    float y = 0.0F;
    float width = 0.0F;
    float height = 0.0F;
};

// Exact SSE op order of the setOpen viewport block (inventory sites
// 0xb4eef2-0xb4f004, pet 0xb92e33-0xb92f49), one rounding per statement,
// NaN behavior mirrors ucomiss/maxss/cmpnltss (strict >/<, unordered skips,
// NaN keeps its side). Compare against tools/emulate_inventory_viewport.py
// literals (it takes the same consts), not against this comment.
[[nodiscard]] PanelViewport panel_viewport(const PanelViewportConsts &consts, int width_px,
                                           int height_px, float yratio);

struct PanelProfile {
    const char *menu = ""; // working name only
    bool has_viewport = false;
    PanelViewportConsts viewport_consts{};
    int tab_triples = 0; // radio/visible triple groups written on open
    bool tab_indexed = false; // merchant/skill selected-index int
    bool tab_default_on_open = false; // merchant: index := default on open; skill: preserved
    int tip_open = -1; // queueTip id on open path, -1 none
    bool tip_isa_switched = false; // merchant: 0x0c vs 0x05 by owner ISA(0x7f)
    bool close_detaches = false; // removeChildWindow on close path
    bool refresh_on_reopen = true; // updateLayout on already-open+open
    bool state_gate = false; // pet: companion state can veto opening (open)
    int open_sound = -1; // playSample id on open path, -1 none (verified 22)
    int close_sound = -1; // playSample id on close path, -1 none (66/12/21)
};

[[nodiscard]] const PanelProfile &panel_profile_inventory();
[[nodiscard]] const PanelProfile &panel_profile_merchant();
[[nodiscard]] const PanelProfile &panel_profile_pet();
[[nodiscard]] const PanelProfile &panel_profile_quest();
[[nodiscard]] const PanelProfile &panel_profile_skill();
[[nodiscard]] const PanelProfile &panel_profile_journal();

struct PanelOpenEffects {
    bool update_layout = false; // virtual slot +0x48
    int sound_sample = -1; // profile open/close id, -1 none (open: no sink)
    bool blend_open = false; // OPEN blend when CLOSE is playing (open)
    bool play_open = false; // OPEN play otherwise (open)
    bool queue_idle = false; // IDLE queued (open)
    bool blend_close = false; // CLOSE blend (open)
    bool viewport_recompute = false; // lazy viewport was null (open)
    int tip = -1; // queueTip id, -1 none (open: no sink)
    bool detach_child = false; // removeChildWindow taken (open: no CEGUI)
    int tab_index = -1; // selected tab index, -1 n/a
};

// Inputs the port cannot observe yet are explicit parameters, never guessed:
// close_playing = animationPlaying("CLOSE"); default_tab = merchant owner
// default (1/2/other, source open); isa_merchant = owner ISA(0x7f) for the
// merchant tip switch; companion_mode = pet [[0x58]+0x330] raw value, opening
// is vetoed for 0x29/0x2a whose meaning is open.
class PanelOpenState {
public:
    explicit PanelOpenState(const PanelProfile &profile) noexcept : profile_(&profile) {}
    [[nodiscard]] bool open() const noexcept { return open_; }
    [[nodiscard]] bool aux() const noexcept { return aux_; }
    [[nodiscard]] int tab_index() const noexcept { return tab_index_; }
    [[nodiscard]] bool viewport_ready() const noexcept { return viewport_ready_; }
    [[nodiscard]] const PanelViewport &viewport() const noexcept { return viewport_; }
    // Skill index writer lives in its createMenus (open); exposed for it.
    void set_tab_index(int index) noexcept { tab_index_ = index; }

    PanelOpenEffects set_open(bool open, bool close_playing, int default_tab = 0,
                              bool isa_merchant = false, unsigned companion_mode = 0);
    bool ensure_viewport(int width_px, int height_px, float yratio);

private:
    const PanelProfile *profile_;
    bool open_ = false; // flag byte
    bool aux_ = false; // second flag byte: cleared on close, setter open
    int tab_index_ = -1;
    bool viewport_ready_ = false;
    PanelViewport viewport_{};
};
} // namespace torchlight
