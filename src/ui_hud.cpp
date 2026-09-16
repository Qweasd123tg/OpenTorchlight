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
float clamp_fraction(float value) {
    if (!(value >= 0.0F))
        return 0.0F;
    return std::min(value, 1.0F);
}
} // namespace
UiHudFrame UiHud::frame(int width, int height, const UiHudValues &values) const {
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
            result.bars.push_back({widget, clamp_fraction(values.health_fraction), true, true});
        else if (name == "PLAYERMANABARSUB")
            result.bars.push_back({widget, clamp_fraction(values.mana_fraction), true, true});
        else if (name == "EXPERIENCEBARSUB")
            result.bars.push_back({widget, clamp_fraction(values.experience_fraction), false, false});
        else if (name == "TARGETHEALTHBARSUB" && target_present)
            result.bars.push_back(
                {widget, clamp_fraction(*values.target_health_fraction), false, false});
        else if (!widget.image.empty())
            result.images.push_back(widget);
        else if (name == "LEVELNAME" && !values.level_name.empty()) {
            auto text_widget = widget;
            text_widget.text = values.level_name;
            result.texts.push_back(std::move(text_widget));
        } else if (!widget.text.empty() && widget.text != "1" && hotkey_label(name))
            result.texts.push_back(widget);
    }
    return result;
}
} // namespace torchlight
