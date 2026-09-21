#pragma once
#include "torchlight/ui_layout.hpp"
#include <memory>
#include <string_view>

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
// Screen-space thumb left -> value for the pinned full-width, horizontal,
// non-reversed slider. Degenerate/non-finite input returns zero (port safety).
[[nodiscard]] float ui_slider_value_from_thumb(float pixel_x, const UiRect& parent,
                                               float thumb_width, float max = 1);
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
// RenderCache's default TopLeftToBottomRight quad split, shared with GLES.
struct UiSkinVertex {
    float x, y, u, v;
    UiColour colour{1, 1, 1, 1};
};
[[nodiscard]] std::array<UiSkinVertex, 6> ui_quad_vertices(
    UiRect destination, UiRect uv, const UiColours& colours = ui_white());
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
    [[nodiscard]] std::optional<UiRect> named_area(
        UiResources&, const UiResolvedWidget&, const std::string& name,
        int width, int height) const;
    // Bounded ListboxTextItem consumer used by the settings ComboDropList.
    // Those original items have a null selection brush, so selected/hovered
    // rows intentionally add no invented highlight imagery.
    [[nodiscard]] UiSkinDraw combobox_text_item(
        std::string_view text, UiRect row, UiRect clip,
        float effective_alpha = 1.0F) const;
    [[nodiscard]] std::optional<UiResolvedWidget> slider_thumb(
        UiResources&, const UiResolvedWidget& parent, float value, float max,
        int width, int height) const;
  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
// Port-native bounded cache. Resources belong to one immutable archive;
// every input consumed by the compiler and viewport is part of validation.
class UiSkinCache {
  public:
    explicit UiSkinCache(UiResources& resources);
    ~UiSkinCache();
    UiSkinCache(const UiSkinCache&) = delete;
    UiSkinCache& operator=(const UiSkinCache&) = delete;
    const UiSkinFrame& compile(const UiResolvedWidget&, UiSkinState, int width, int height);
    [[nodiscard]] std::size_t compile_count() const noexcept { return compile_count_; }
  private:
    struct Entry {
        UiResolvedWidget widget;
        UiSkinState state;
        int width = 0, height = 0;
        UiSkinFrame frame;
    };
    UiResources* resources_;
    std::size_t subscription_ = 0;
    std::map<std::string, Entry> entries_;
    std::size_t compile_count_ = 0;
};
} // namespace torchlight
