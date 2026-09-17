#pragma once
#include <array>
#include <optional>
#include <string>

namespace torchlight {
// original-code: CGameUI::convertToScreenScale @0xa83ed0 with scaledX @0xa83ea0
// and scaledY @0xa83e70 (ELF Torchlight.bin.x86_64, SHA-256
// 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b;
// decompiled research/decompiled-core/game_ui.c:1256-1346).
//
// After loading several layouts the original scales the four OFFSET members
// of the window position/size UDim values by a single ratio and leaves the
// four RELATIVE (scale) members unchanged. Children are visited before their
// parent. Per-widget the transform below is order-free; the child-first order
// matters only for the original in-place CEGUI tree mutation, which the port
// does not perform: the parsed layout document stays pristine and the ratio
// is applied transiently at resolve time, so re-resolving (resize) can never
// accumulate scaling. See research/ui-scale-p1/NOTES.md.
enum class UiScreenScaleRatio { y_ratio, x_ratio };

// YRATIO = height / 768, XRATIO = width / 1024. The original settings keys
// are KSETTINGS_YRATIO/KSETTINGS_XRATIO (game.c:530,593,5150) and the rodata
// constants are 768.0f @0xfa4804 and 1/1024 @0xfa4808.
[[nodiscard]] float ui_screen_ratio(int width, int height, UiScreenScaleRatio which);

// UnifiedAreaRect {min_x_scale, min_x_offset, min_y_scale, min_y_offset,
// max_x_scale, max_x_offset, max_y_scale, max_y_offset}: scale the offsets
// at indices 1, 3, 5, 7, preserve the scales.
void ui_scale_area_offsets(std::array<float, 8> &area, float ratio);
// UnifiedPosition/UnifiedSize {x_scale, x_offset, y_scale, y_offset}: scale
// the offsets at indices 1 and 3, preserve the scales.
void ui_scale_vector_offsets(std::array<float, 4> &vector, float ratio);

// Confirmed per-controller convertToScreenScale call sites. `false` in the
// original call means YRATIO for both axes, `true` XRATIO for both axes.
// Confirmed `false`: bottomhud (game_ui.c:9464), pethud (:9663), inventory
// (inventory_menu.c:7876), merchant (merchant_menu.c:6430), pet
// (pet_menu.c:3928), journal (journal_menu.c:2064), quest (quest_menu.c:5571),
// stash (stash_menu.c:6331), enchant (enchant_menu.c:8169), combine
// (combine_menu.c:4881). Layouts absent here (e.g. main menu, character
// screens) have unknown policy: no scaling is applied for them rather than
// an invented one.
[[nodiscard]] std::optional<UiScreenScaleRatio> ui_screen_scale_for_layout(
    const std::string &layout_path);
} // namespace torchlight
