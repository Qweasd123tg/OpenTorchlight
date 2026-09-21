#pragma once
#include "torchlight/inventory_menu.hpp"
#include "torchlight/ui_hud.hpp"

namespace torchlight {
struct UiInventoryFrame {
    std::vector<UiResolvedWidget> widgets, targets;
};
enum class InventoryUiAction { none, tab, close };
struct InventoryUiPress {
    InventoryUiAction action = InventoryUiAction::none;
    int function = -1;
};
// Opt-in diagnostic presentation, NOT original animated inventory rendering.
// XML coordinates/images are resource-derived; original update overwrites
// positions from tag_topinventory/tag_bottominventory, still open here.
class UiInventoryPreview {
public:
    explicit UiInventoryPreview(UiResources&);
    [[nodiscard]] UiInventoryFrame frame(int width, int height,
        const InventoryMenuState&, const UiPointerState& = {}) const;
    [[nodiscard]] static InventoryUiPress press(const UiInventoryFrame&, float x, float y);
    [[nodiscard]] const std::vector<std::size_t>& subscriptions() const { return subscriptions_; }
private:
    UiResources* resources_;
    const UiLayout* layout_;
    std::vector<std::size_t> subscriptions_;
};
} // namespace torchlight
