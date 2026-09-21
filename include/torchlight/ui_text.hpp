#pragma once
#include <functional>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
namespace torchlight {
// Bounded UTF-8 decoding. Invalid bytes become U+FFFD; no locale or char casts.
[[nodiscard]] std::u32string ui_decode_utf8(std::string_view text);
struct UiTextLine {
    std::u32string text;
    float width = 0;
    // One entry per codepoint in text. nullopt means the caller's base colour.
    std::vector<std::optional<std::uint32_t>> colors;
};
[[nodiscard]] bool ui_font_uses_inline_colours(std::string_view font_name);
// Port formatting subset, not CEGUI's full shaping/markup engine. The supplied
// advance function may rasterize glyphs; callers must sync the atlas afterwards.
[[nodiscard]] std::vector<UiTextLine> ui_text_lines(
    std::string_view text, float width, bool wrap,
    const std::function<float(char32_t)> &advance,
    bool inline_markup = false);
} // namespace torchlight
