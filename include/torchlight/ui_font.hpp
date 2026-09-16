#pragma once
#include "torchlight/pak_archive.hpp"
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace torchlight {
// CEGUI 0.6.2 <Font> resource. Semantics repeated from the pinned engine
// library libCEGUIBase.so.1; see research/ui-visuals.md for addresses.
struct UiFontDefinition {
    std::string name, filename;
    float size = 0, native_horz = 1024, native_vert = 768;
    bool auto_scaled = false, antialias = false;
};
[[nodiscard]] UiFontDefinition parse_ui_font_definition(const std::vector<std::uint8_t> &bytes,
                                                        std::string_view source);
struct UiGlyph {
    float u0 = 0, v0 = 0, u1 = 0, v1 = 0; // atlas texture coordinates
    float advance = 0, bearing_x = 0, bearing_y = 0;
    float width = 0, height = 0; // pixels
};
// Bounded bitmap-atlas font. Not the CEGUI Font object graph or its render cache.
class UiFont {
  public:
    UiFont(const PakArchive &archive, UiFontDefinition definition);
    ~UiFont();
    UiFont(const UiFont &) = delete;
    UiFont &operator=(const UiFont &) = delete;
    UiFont(UiFont &&) noexcept;
    UiFont &operator=(UiFont &&) noexcept;

    [[nodiscard]] const UiFontDefinition &definition() const noexcept;
    [[nodiscard]] bool valid() const noexcept;
    // CEGUI Font::notifyScreenResolution: per-axis scales feed FT_Set_Char_Size.
    void notify_screen_size(float width, float height);
    [[nodiscard]] float line_height() const noexcept;
    [[nodiscard]] float ascent() const noexcept;
    [[nodiscard]] const UiGlyph *glyph(char32_t codepoint);
    [[nodiscard]] float advance(char32_t codepoint);
    [[nodiscard]] const std::vector<std::uint8_t> &atlas_rgba() const noexcept;
    [[nodiscard]] int atlas_width() const noexcept;
    [[nodiscard]] int atlas_height() const noexcept;
    // Changes on atlas reset or insertion. Consumers upload AFTER rasterization.
    [[nodiscard]] std::uint64_t atlas_revision() const noexcept;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace torchlight
