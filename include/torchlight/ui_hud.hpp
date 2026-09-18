#pragma once
#include "torchlight/ui_layout.hpp"
#include <optional>
#include <string>
#include <vector>

namespace torchlight {
// Fraction policy is original-code: CGameUI::updateIngameUI @0xab8100 low-clamps
// with max(fraction, 0.0) and leaves overfill to parent clipping; geometry
// (UVector2 trunc/setPosition/setSize) remains port-bound. See
// research/ui-hud-bars.md and research/ui-visuals.md.
struct UiHudValues {
    float health_fraction = 1.0F, mana_fraction = 1.0F, experience_fraction = 0.0F;
    std::optional<float> target_health_fraction;
    std::string level_name;
};
struct UiHudBar {
    UiResolvedWidget widget;
    float fraction = 0.0F;
    bool vertical = false, bottom_anchored = false;
};
// Physical pointer state supplied by the host, not keyboard focus. A press
// origin lets a captured button distinguish Pushed from PushedOff.
struct UiPointerState {
    std::optional<std::array<float, 2>> position, left_press_origin;
};
struct UiPointerClick {
    std::array<float, 2> press, release;
};
struct UiHudFrame {
    std::vector<UiResolvedWidget> images, texts, buttons;
    std::vector<UiHudBar> bars;
};
// Topmost visible callback target; disabled targets still block world input.
[[nodiscard]] const UiResolvedWidget *hud_button_at(const UiHudFrame &, float x, float y);
// Original CGameUI::mapEventHandlers maps onClick to MouseButtonDown.
// Dispatch once at the press position, not at release; release never repeats it.
[[nodiscard]] std::optional<std::string> hud_press_callback(const UiHudFrame &, float x, float y);
class UiHud {
  public:
    explicit UiHud(UiResources &resources) : resources_(&resources) {}
    // Absent layout or unresolvable widgets yield an empty frame, never a
    // fabricated replacement HUD.
    [[nodiscard]] UiHudFrame frame(int width, int height, const UiHudValues &values,
                                   const UiPointerState &pointer = {}) const;

  private:
    UiResources *resources_;
};
} // namespace torchlight
