#pragma once
#include "torchlight/ui_layout.hpp"
#include <memory>

namespace torchlight {
// Shared bounded XML parser, also used by layout loading. Names remain case-sensitive.
struct UiSkinNode {
    std::string tag;
    std::map<std::string, std::string> attributes;
    int parent = -1;
};
std::vector<UiSkinNode> ui_skin_xml(const std::vector<std::uint8_t>&);
using UiColour = std::array<float, 4>;
using UiColours = std::array<UiColour, 4>; // top-left, top-right, bottom-left, bottom-right
[[nodiscard]] UiColours ui_white();
[[nodiscard]] UiColours ui_colours(const std::string&); // CEGUI AARRGGBB or tl:/tr:/bl:/br:
[[nodiscard]] UiColours ui_colour_subrectangle(const UiColours&, float left, float right,
                                               float top, float bottom);
[[nodiscard]] UiRect ui_intersect(UiRect a, UiRect b);
[[nodiscard]] float ui_pixel_aligned(float value);
struct UiSkinState {
    bool hover = false, pushed = false, selected = false;
};
struct UiSkinDraw {
    enum class Kind { image, text } kind = Kind::image;
    // Image source is in texture pixels, destination and clip in screen pixels.
    UiRect destination, source, clip;
    UiColours colours = ui_white();
    std::string texture, text, font, section;
    UiTextStyle text_style;
};
struct UiSkinFrame {
    bool handled = false;
    std::vector<UiSkinDraw> draws;
    std::vector<std::string> states, diagnostics;
};
// Resource-driven Falagard command compiler. No OpenGL, game singleton or save
// access. Unsupported auto children / state machines are reported explicitly.
// This is NOT the full CEGUI runtime. See research/ui-skin-continuation.md.
class UiSkin {
  public:
    explicit UiSkin(const PakArchive&);
    ~UiSkin();
    [[nodiscard]] UiSkinFrame compile(UiResources&, const UiResolvedWidget&, UiSkinState,
                                      int width, int height) const;
    [[nodiscard]] std::string renderer(const std::string& type) const;
    [[nodiscard]] std::vector<std::string> states(const std::string& type) const;
    [[nodiscard]] std::size_t automatic_children(const std::string& type) const;
  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace torchlight
