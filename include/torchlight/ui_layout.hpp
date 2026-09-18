#pragma once
#include "torchlight/pak_archive.hpp"
#include "torchlight/ui_font.hpp"
#include <map>
#include <array>
#include <limits>
#include <memory>
#include <optional>

namespace torchlight {
// Bounded subset of original CEGUI XML; not a replacement for the full skin engine.
struct UiRect {
    float x = 0, y = 0, width = 0, height = 0;
    [[nodiscard]] bool contains(float px, float py) const noexcept {
        return width > 0 && height > 0 && px >= x && py >= y && px < x + width && py < y + height;
    }
};
struct UiWidget {
    std::string name, type;
    std::int32_t parent = -1;
    std::map<std::string, std::string> properties;
    [[nodiscard]] std::string property(const std::string &key) const;
};
enum class UiTextHorizontal { left, centre, right };
enum class UiTextVertical { top, centre, bottom };
struct UiTextStyle {
    UiTextHorizontal horizontal = UiTextHorizontal::left;
    UiTextVertical vertical = UiTextVertical::top;
    bool wrap = false;
};
// Falagard skin compiler (additive donor module); full CEGUI runtime is out
// of scope, see research/ui-skin-continuation.md.
class UiSkin;
struct UiResolvedWidget {
    std::string name, type, text, callback, image, font;
    UiRect rect;
    bool visible = true, enabled = true;
    std::int32_t parent = -1;
    UiRect clip;
    // Resolved resource widgets have an authoritative clip, including an empty one.
    // Hand-authored PORT widgets may omit it; empty must never mean "unclipped".
    bool has_clip = false;
    std::map<std::string, std::string> properties;
    [[nodiscard]] std::string property(const std::string &key) const;
    [[nodiscard]] UiTextStyle text_style() const;
    float effective_alpha = 1.0F;
    // Initial CEGUI sibling draw list: normal children, then AlwaysOnTop,
    // recursively. Runtime moveToFront / reparenting is outside this subset.
    std::size_t paint_order = std::numeric_limits<std::size_t>::max();
};
// Bounded port of the intersection/UV adjustment in CEGUI::Imageset::draw
// (bundled libCEGUIBase.so.1 @0xe6f20). Not pixel-rounding/colour parity.
struct UiImageGeometry {
    UiRect destination, source;
};
[[nodiscard]] std::optional<UiImageGeometry> clip_ui_image(
    UiRect destination, UiRect source, const UiRect *clip = nullptr);
// Runtime resolve overrides (donor ui_skin merge). Axis refers to the game's
// scale, NOT CEGUI's per-axis relative coordinates.
enum class UiScreenScale { none, height, width };
struct UiLayoutState {
    UiScreenScale screen_scale = UiScreenScale::none;
    std::map<std::string, bool> visibility;
    std::optional<float> offset_ratio; // one resolved scale, not an additional multiplier
};
class UiLayout {
  public:
    [[nodiscard]] static UiLayout parse(const std::vector<std::uint8_t> &bytes);
    [[nodiscard]] std::vector<UiResolvedWidget> resolve(int width, int height) const;
    // original-code: CGameUI::convertToScreenScale @0xa83ed0 scales the four
    // UDim offset members by one ratio before CEGUI resolution, scales
    // untouched. A ratio of 1 reproduces the legacy unscaled resolve exactly.
    // The parsed document is never mutated, so repeated calls cannot
    // accumulate scaling (the original instead recreates UI on resize via
    // CGameClient::rescaleUI).
    [[nodiscard]] std::vector<UiResolvedWidget> resolve(int width, int height,
                                                        float screen_scale_ratio) const;
    // Runtime overrides are separate from immutable resource defaults.
    // Re-resolving starts from the XML each time; it cannot compound a
    // previous screen scale. (Donor ui_skin merge; explicit ratio replaces,
    // never multiplies, the state's screen-scale policy.)
    [[nodiscard]] std::vector<UiResolvedWidget> resolve(
        int width, int height, const UiLayoutState &state) const;
    [[nodiscard]] const std::vector<UiWidget> &widgets() const noexcept {
        return widgets_;
    }

  private:
    std::vector<UiWidget> widgets_;
};
struct UiImage {
    std::string texture_path;
    float x = 0, y = 0, width = 0, height = 0;
    // original-code: CEGUI::Imageset::Image render offsets (XOffset/YOffset
    // XML attrs, 0 when absent) and per-imageset native resolution/autoscale
    // (NativeHorzRes/NativeVertRes/AutoScaled; defaults 640x480 from the
    // vendored Imageset constructor immediates 0x44200000/0x43f00000).
    float offset_x = 0, offset_y = 0;
    float native_horz = 640.0F, native_vert = 480.0F;
    bool auto_scaled = false;
    // Image::setHorz/VertScaling rounds native dimensions AND offsets.
    [[nodiscard]] std::array<float, 4> scaled_metrics(int w, int h) const;
};
// original-code: vendored CEGUI::Image::setHorzScaling @0xe59e0 (vert +0x80)
// in the shipped libCEGUIBase.so.1: (float)(int)(v + (v > 0 ? +0.5 : -0.5))
// with +0.5 @0x1d6c6c and -0.5 @0x1d6c68. NaN takes the -0.5 branch and the
// cvttss2si converts to INT_MIN; both replicated explicitly because the C++
// conversion is UB on overflow. noexcept: never throws, even on NaN/inf.
[[nodiscard]] float pixel_align_ui(float value) noexcept;
// Scaled render offset of an image for the current screen, in whole pixels.
// Factors are screen/native per axis when auto-scaled, else 1
// (CEGUI::Imageset::updateImageScalingFactors). Applied to the destination
// rect before clipping (CEGUI::Image::draw offsets dest, then Imageset::draw
// clips). Library-derived: upstream CEGUI v0-6-2 CEGUIImageset.cpp /
// CEGUIImage.cpp, confirmed against the shipped-library ASM above.
[[nodiscard]] std::array<float, 2> ui_image_render_offset(const UiImage &image, float screen_width,
                                                          float screen_height) noexcept;
// Bounded GuiLook.looknfeel extraction for widget types this renderer draws.
struct UiWidgetImages {
    std::string normal, hover, pushed, disabled;
};
// resource-derived: one Falagard TextComponent pass. Coordinates are absolute
// pixels plus a multiple of the widget size (LeftEdge/TopEdge AbsoluteDim and
// UnifiedDim(scale, Width|Height) with Add/Subtract); colour names a
// TextColour-like widget property resolved against the widget, then the look
// default. Checkbox labels live past the box (x + width + 5).
struct UiTextPass {
    float dx = 0, dy = 0;
    float x_scale = 0, y_scale = 0;
    std::string colour_property;
    std::string colour_default{"FFFFFFFF"};
    // resource-derived: per-TextComponent VertFormat/HorzFormat type.
    // Unset means the component defers to the widget formatting properties
    // (HorzFormatProperty/VertFormatProperty, e.g. StaticText/ItemText).
    std::optional<UiTextHorizontal> horz;
    std::optional<UiTextVertical> vert;
};
// resource-derived: wrap width of the look's first TextComponent Area
// (Width, or RightEdge minus LeftEdge). Non-positive means the area is
// degenerate and text runs to the viewport edge (Checkbox labels).
struct UiTextLayout {
    float width_abs = 0, width_scale = 0;
};
class UiResources {
  public:
    explicit UiResources(const PakArchive &archive) : archive_(&archive) {
    }
    [[nodiscard]] const UiLayout *layout(const std::string &path);
    [[nodiscard]] std::optional<UiImage> image(const std::string &reference);
    [[nodiscard]] UiSkin& skin();
    // Case-insensitive lookup by the original CEGUI <Font Name=...>. The
    // returned cache is mutated by rasterization; callers own the screen size.
    [[nodiscard]] UiFont *font(const std::string &name);
    // WidgetLook PropertyDefinition initialValue from media/UI/GuiLook.looknfeel.
    [[nodiscard]] std::optional<UiWidgetImages> widget_images(const std::string &type);
    // Ordered Falagard TextComponent passes for the look (shadow/outline first,
    // main text last). Absent when the look defines none: the caller keeps its
    // single-pass fallback instead of inventing geometry.
    [[nodiscard]] std::optional<std::vector<UiTextPass>> widget_text_passes(
        const std::string &type);
    [[nodiscard]] std::optional<UiTextLayout> widget_text_layout(const std::string &type);
    // PropertyDefinition initialValue for the look ("" when absent).
    [[nodiscard]] std::string look_default(const std::string &type,
                                           const std::string &key);
    [[nodiscard]] const std::vector<std::string> &diagnostics() const noexcept {
        return diagnostics_;
    }

  private:
    void ensure_looknfeel();
    const PakArchive *archive_;
    std::map<std::string, UiLayout> layouts_;
    std::map<std::string, UiImage> images_;
    std::map<std::string, UiFont> fonts_;
    std::map<std::string, UiWidgetImages> widget_images_;
    std::map<std::string, std::vector<UiTextPass>> widget_text_;
    std::map<std::string, UiTextLayout> widget_text_origin_;
    std::map<std::string, std::map<std::string, std::string>> look_defaults_;
    std::shared_ptr<UiSkin> skin_;
    std::vector<std::string> diagnostics_;
    bool images_loaded_ = false, fonts_loaded_ = false, looknfeel_loaded_ = false;
};
} // namespace torchlight
