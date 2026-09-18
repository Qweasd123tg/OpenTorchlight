#include "torchlight/ui_hud.hpp"
#include <algorithm>
#include <cctype>

namespace torchlight {
namespace {
std::string upper(std::string s) {
    for (auto &c : s)
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return s;
}
std::string leaf_upper(const std::string &name) {
    const auto p = name.find_last_of('/');
    return upper(p == std::string::npos ? name : name.substr(p + 1));
}
bool hotkey_label(const std::string &name) {
    return name.find("HOTKEY") != std::string::npos;
}
// original-code: CGameUI::updateIngameUI @0xab8100 low-clamps fraction with
// max(fraction, 0.0) via cmpnltss/andps/andnps/orps (HP 0xab846b..0xab8476,
// mana 0xab88c7..0xab88e5). No high-clamp to 1.0 is present in either path:
// the only rodata floats touched are 0.0 ([rsp+0x98]), 0.5 ([rsp+0xa0]=fa4810)
// for UDim rounding and -0.5 (fa86f4) for layout bias. Overfill (>1) is left
// to CEGUI parent clipping. See research/ui-hud-bars.md.
float clamp_fraction_low(float value) {
    if (!(value >= 0.0F))
        return 0.0F;
    return value;
}
} // namespace
const UiResolvedWidget *hud_button_at(const UiHudFrame &frame, float x, float y) {
    for (auto it = frame.buttons.rbegin(); it != frame.buttons.rend(); ++it)
        if (it->visible && it->rect.contains(x, y) &&
            (!it->has_clip || it->clip.contains(x, y))) return &*it;
    return nullptr;
}
std::optional<std::string> hud_press_callback(const UiHudFrame &frame, float x, float y) {
    const auto *pressed = hud_button_at(frame, x, y);
    if (!pressed || !pressed->enabled || pressed->callback.empty())
        return std::nullopt;
    return pressed->callback;
}
UiHudFrame UiHud::frame(int width, int height, const UiHudValues &values,
                        const UiPointerState &pointer) const {
    UiHudFrame result;
    if (width <= 0 || height <= 0)
        return result;
    const auto *layout = resources_->layout("media/UI/bottomhud.layout");
    if (layout == nullptr)
        return result;
    const bool target_present = values.target_health_fraction.has_value();
    for (const auto &widget : layout->resolve(width, height)) {
        if (!widget.visible)
            continue;
        const auto name = leaf_upper(widget.name);
        if (name.rfind("TARGET", 0) == 0 && !target_present)
            continue;
        if (name == "PLAYERHEALTHBARSUB")
            result.bars.push_back({widget, clamp_fraction_low(values.health_fraction), true, true});
        else if (name == "PLAYERMANABARSUB")
            result.bars.push_back({widget, clamp_fraction_low(values.mana_fraction), true, true});
        else if (name == "EXPERIENCEBARSUB")
            result.bars.push_back({widget, clamp_fraction_low(values.experience_fraction), false, false});
        else if (name == "TARGETHEALTHBARSUB" && target_present)
            result.bars.push_back(
                {widget, clamp_fraction_low(*values.target_health_fraction), false, false});
        else if (!widget.callback.empty())
            // resource-derived: several bottomhud ImageButtons intentionally
            // have NormalImage="". The callback/hit rectangle still exists.
            result.buttons.push_back(widget);
        else if (!widget.image.empty())
            result.images.push_back(widget);
        else if (name == "LEVELNAME" && !values.level_name.empty()) {
            auto text_widget = widget;
            text_widget.text = values.level_name;
            result.texts.push_back(std::move(text_widget));
        } else if (!widget.text.empty() && widget.text != "1" && hotkey_label(name))
            result.texts.push_back(widget);
    }
    const auto *hover = pointer.position ? hud_button_at(result, (*pointer.position)[0],
                                                         (*pointer.position)[1]) : nullptr;
    const auto *pressed = pointer.left_press_origin
        ? hud_button_at(result, (*pointer.left_press_origin)[0], (*pointer.left_press_origin)[1])
        : nullptr;
    for (auto &button : result.buttons) {
        // Bounded original ImageButton look only. RadioButton selection,
        // script-updated visibility and other widget types remain separate.
        if (upper(button.type) != "GUILOOK/IMAGEBUTTON") continue;
        const char *property = !button.enabled ? "DisabledImage"
            : &button == pressed ? (&button == hover ? "PushedImage" : "HoverImage")
            : &button == hover ? "HoverImage" : "NormalImage";
        // GuiLook/ImageButton StateImagery PushedOff references section hover.
        const auto value = button.properties.find(property);
        button.image = value != button.properties.end() ? value->second
            : resources_->look_default(button.type, property);
    }
    return result;
}
} // namespace torchlight
