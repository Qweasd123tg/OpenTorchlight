#include "torchlight/ui_inventory.hpp"
#include "torchlight/ui_screen_scale.hpp"
#include <algorithm>
#include <stdexcept>

namespace torchlight {
namespace {
std::string leaf(const std::string& name) {
    const auto slash = name.find_last_of('/');
    return slash == std::string::npos ? name : name.substr(slash + 1);
}
class LayoutEvents final : public InventoryEventTree {
public:
    LayoutEvents(const UiLayout& layout, std::vector<std::size_t>& output)
        : widgets_(layout.widgets()), children_(widgets_.size()), output_(output) {
        for (std::size_t i = 0; i < widgets_.size(); ++i)
            if (widgets_[i].parent >= 0) children_.at(widgets_[i].parent).push_back(i);
    }
    std::size_t child_count(Node n) const override { return children_.at(n).size(); }
    Node child(Node n, std::size_t i) const override { return children_.at(n).at(i); }
    bool has_click_property(Node n) const override { return widgets_.at(n).properties.count("onClick") != 0; }
    std::string click_property(Node n) const override { return widgets_.at(n).property("onClick"); }
    void subscribe_mouse_down(Node n) override { output_.push_back(n); }
private:
    const std::vector<UiWidget>& widgets_;
    std::vector<std::vector<Node>> children_;
    std::vector<std::size_t>& output_;
};
const UiResolvedWidget* at(const UiInventoryFrame& frame, float x, float y) {
    for (auto i = frame.targets.rbegin(); i != frame.targets.rend(); ++i)
        if (i->visible && i->rect.contains(x,y) && (!i->has_clip || i->clip.contains(x,y))) return &*i;
    return nullptr;
}
constexpr const char* tabs[] = {"TabBackpack", "TabSpell", "TabFish"};
constexpr const char* containers[] = {"SlotsEquipment", "SlotsSpells", "SlotsFish"};
} // namespace

UiInventoryPreview::UiInventoryPreview(UiResources& resources)
    : resources_(&resources), layout_(resources.layout("media/UI/inventorymenu.layout")) {
    if (!layout_) throw std::runtime_error("inventory UI preview: original layout unavailable");
    LayoutEvents tree(*layout_, subscriptions_);
    for (std::size_t i = 0; i < layout_->widgets().size(); ++i)
        if (layout_->widgets()[i].parent < 0) map_inventory_events(tree, i);
}

UiInventoryFrame UiInventoryPreview::frame(int width, int height,
    const InventoryMenuState& menu, const UiPointerState& pointer) const {
    UiInventoryFrame frame;
    if (!menu.open() || width <= 0 || height <= 0) return frame;
    UiLayoutState overrides;
    overrides.offset_ratio = ui_screen_ratio(width, height, UiScreenScaleRatio::y_ratio);
    for (const auto& w : layout_->widgets()) {
        for (std::size_t i = 0; i < 3; ++i)
            if (leaf(w.name) == containers[i]) overrides.visibility[w.name] = menu.container_visible(i);
        // Drag/hover glow has no original runtime owner in this preview.
        if (leaf(w.name) == "SlotGlow") overrides.visibility[w.name] = false;
    }
    auto widgets = layout_->resolve(width, height, overrides);
    // resolve preserves document indexing (paint_order is separate).
    for (std::size_t i = 0; i < widgets.size(); ++i) {
        const auto& w = widgets[i];
        if (!w.visible) continue;
        if (std::find(subscriptions_.begin(), subscriptions_.end(), i) != subscriptions_.end() ||
            leaf(w.name) == "Close") frame.targets.push_back(w);
    }
    std::stable_sort(frame.targets.begin(), frame.targets.end(), [](const auto& a, const auto& b) {
        return a.paint_order < b.paint_order;
    });
    const auto* hover = pointer.position ? at(frame, (*pointer.position)[0], (*pointer.position)[1]) : nullptr;
    const auto* down = pointer.left_press_origin ? at(frame, (*pointer.left_press_origin)[0], (*pointer.left_press_origin)[1]) : nullptr;
    for (auto& w : widgets) {
        if (!w.visible) continue;
        const auto name = leaf(w.name);
        const bool hot = hover && hover->name == w.name;
        const bool pushed = down && down->name == w.name;
        const char* property = nullptr;
        for (std::size_t i = 0; i < 3; ++i)
            if (name == tabs[i]) {
                // GuiLook RadioButton/RadioTab: both hover states use HoverImage;
                // both disabled states contain empty imagery. No invented tint.
                if (!w.enabled) { w.image.clear(); break; }
                property = hot ? "HoverImage" : menu.tab_selected(i) ? "SelectedImage" : "UnselectedImage";
                // The immutable XML holds the saved UnselectedImage used by
                // onClick; alerts/animation-driven image changes remain open.
            }
        if (w.type == "GuiLook/ImageButton")
            property = !w.enabled ? "DisabledImage" : pushed ? (hot ? "PushedImage" : "HoverImage")
                : hot ? "HoverImage" : "NormalImage";
        if (property) {
            const auto found = w.properties.find(property);
            w.image = found != w.properties.end() ? found->second : resources_->look_default(w.type, property);
        }
        frame.widgets.push_back(std::move(w));
    }
    std::stable_sort(frame.widgets.begin(), frame.widgets.end(), [](const auto& a, const auto& b) {
        return a.paint_order < b.paint_order;
    });
    return frame;
}

InventoryUiPress UiInventoryPreview::press(const UiInventoryFrame& frame, float x, float y) {
    const auto* w = at(frame,x,y);
    if (!w || !w->enabled) return {};
    if (leaf(w->name) == "Close") return {InventoryUiAction::close, -1};
    if (w->layout_function) return {InventoryUiAction::tab, static_cast<int>(*w->layout_function)};
    return {};
}
} // namespace torchlight
