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
struct UiHudFrame {
    std::vector<UiResolvedWidget> images, texts;
    std::vector<UiHudBar> bars;
};
class UiHud {
  public:
    explicit UiHud(UiResources &resources) : resources_(&resources) {}
    // Absent layout or unresolvable widgets yield an empty frame, never a
    // fabricated replacement HUD.
    [[nodiscard]] UiHudFrame frame(int width, int height, const UiHudValues &values) const;

  private:
    UiResources *resources_;
};
} // namespace torchlight
