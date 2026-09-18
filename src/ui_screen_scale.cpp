#include "torchlight/ui_screen_scale.hpp"
#include <cmath>
#include <stdexcept>

namespace torchlight {
namespace {
constexpr float kBaseHeight = 768.0F;
constexpr float kBaseWidth = 1024.0F;
} // namespace

float ui_screen_ratio(int width, int height, UiScreenScaleRatio which) {
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("invalid UI viewport");
    const float value = which == UiScreenScaleRatio::x_ratio
        ? static_cast<float>(width) / kBaseWidth
        : static_cast<float>(height) / kBaseHeight;
    if (!std::isfinite(value))
        throw std::invalid_argument("non-finite screen ratio");
    return value;
}

void ui_scale_area_offsets(std::array<float, 8> &area, float ratio) {
    // original-code: convertToScreenScale scales only the two UDim offsets of
    // getPosition() and then only the two UDim offsets of getSize().
    for (const std::size_t i : {1U, 3U, 5U, 7U})
        area[i] *= ratio;
}

void ui_scale_vector_offsets(std::array<float, 4> &vector, float ratio) {
    vector[1] *= ratio;
    vector[3] *= ratio;
}

std::optional<UiScreenScaleRatio> ui_screen_scale_for_layout(const std::string &layout_path) {
    // All confirmed call sites pass `false`, i.e. YRATIO for both axes.
    const auto leaf = layout_path.substr(layout_path.find_last_of('/') + 1);
    for (const char *name : {"bottomhud.layout", "pethud.layout", "inventorymenu.layout",
                             "merchantmenu.layout", "petmenu.layout", "journalmenu.layout",
                             "questmenu.layout", "stashmenu.layout", "enchantmenu.layout",
                             "combinemenu.layout"})
        if (leaf == name)
            return UiScreenScaleRatio::y_ratio;
    return std::nullopt;
}
} // namespace torchlight
