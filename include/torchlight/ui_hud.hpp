#pragma once
#include "torchlight/ui_layout.hpp"
#include <optional>
#include <string>
#include <vector>

namespace torchlight {
// Portable HUD policy over the original bottomhud.layout geometry. Dynamic bar
// behavior is bounded and marked in research/ui-visuals.md; this is not the
// full CGameUI::updateIngameUI.
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
