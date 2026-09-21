#include "torchlight/ui_text.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <optional>
#include <stdexcept>
namespace torchlight {
bool ui_font_uses_inline_colours(std::string_view font_name) {
    return font_name == "Serif" || font_name == "SerifBig" ||
           font_name == "SerifHuge" || font_name == "SerifSmall";
}
std::u32string ui_decode_utf8(std::string_view text) {
    if (text.size() > 1024U * 1024U)
        throw std::invalid_argument("UI text exceeds portable limit");
    std::u32string result;
    for (std::size_t i = 0; i < text.size();) {
        const auto c = static_cast<unsigned char>(text[i]);
        if (c < 0x80) { result += c; ++i; continue; }
        const unsigned n = c >= 0xc2 && c <= 0xdf ? 2 :
                           c >= 0xe0 && c <= 0xef ? 3 :
                           c >= 0xf0 && c <= 0xf4 ? 4 : 0;
        char32_t code = n == 2 ? c & 0x1f : n == 3 ? c & 0x0f : c & 0x07;
        bool valid = n != 0 && i + n <= text.size();
        for (unsigned j = 1; valid && j < n; ++j) {
            const auto next = static_cast<unsigned char>(text[i + j]);
            valid = (next & 0xc0) == 0x80;
            code = (code << 6) | (next & 0x3f);
        }
        valid = valid && code >= (n == 2 ? 0x80U : n == 3 ? 0x800U : 0x10000U) &&
                code <= 0x10ffff && !(code >= 0xd800 && code <= 0xdfff);
        result += valid ? code : U'\ufffd';
        i += valid ? n : 1;
    }
    return result;
}
std::vector<UiTextLine> ui_text_lines(std::string_view input, float width, bool wrap,
                                     const std::function<float(char32_t)> &advance,
                                     bool inline_markup) {
    if (!std::isfinite(width) || width <= 0) return {};
    const auto text = ui_decode_utf8(input);
    std::vector<UiTextLine> lines;
    UiTextLine line;
    std::optional<std::uint32_t> colour;
    const auto measure = [&](char32_t c) {
        const float value = advance(c);
        if (!std::isfinite(value) || value < 0)
            throw std::invalid_argument("invalid UI glyph advance");
        return value;
    };
    const auto flush = [&] {
        lines.push_back(std::move(line));
        line = {};
        // drawTextLine receives each wrapped physical line independently.
        colour.reset();
    };
    const auto append = [&](char32_t c) {
        line.text += c;
        line.colors.push_back(colour);
    };
    const auto hex_value = [](const std::u32string &value, std::size_t begin) {
        std::uint32_t result = 0;
        bool any = false;
        for (std::size_t n = 0; n < 8; ++n) {
            const char32_t c = value[begin + n];
            unsigned digit = 0;
            if (c >= U'0' && c <= U'9') digit = static_cast<unsigned>(c - U'0');
            else if (c >= U'a' && c <= U'f') digit = static_cast<unsigned>(c - U'a' + 10);
            else if (c >= U'A' && c <= U'F') digit = static_cast<unsigned>(c - U'A' + 10);
            else break;
            result = (result << 4) | digit;
            any = true;
        }
        return any ? result : 0U;
    };
    const auto is_tag_at = [&](std::size_t at) {
        return inline_markup && at < text.size() && text[at] == U'|' &&
               ((at + 1 < text.size() && text[at + 1] == U'u') ||
                (at + 9 < text.size() && text[at + 1] == U'c'));
    };
    for (std::size_t i = 0; i < text.size();) {
        const char32_t c = text[i];
        if (c == U'\r' || c == U'\n') {
            ++i;
            if (c == U'\r' && i < text.size() && text[i] == U'\n') ++i;
            flush();
            continue;
        }
        if (inline_markup && c == U'|' && i + 1 < text.size() && text[i + 1] == U'u') {
            colour.reset();
            i += 2;
            continue;
        }
        if (inline_markup && c == U'|' && i + 9 < text.size() && text[i + 1] == U'c') {
            colour = hex_value(text, i + 2);
            i += 10;
            continue;
        }
        if (c == U' ' || c == U'\t') {
            const int count = c == U'\t' ? 4 : 1; // portable tab fallback
            for (int n = 0; n < count; ++n) {
                const auto a = measure(U' ');
                if (!wrap || line.width + a <= width) {
                    append(U' '); line.width += a;
                }
            }
            ++i;
            continue;
        }
        std::size_t end = i;
        float word_width = 0;
        std::vector<float> widths;
        while (end < text.size() && text[end] != U'\n' && text[end] != U'\r' &&
               text[end] != U' ' && text[end] != U'\t' && !is_tag_at(end)) {
            widths.push_back(measure(text[end++]));
            word_width += widths.back();
        }
        if (wrap && !line.text.empty() && line.width + word_width > width) {
            while (!line.text.empty() && line.text.back() == U' ') {
                line.text.pop_back(); line.width = std::max(0.0F, line.width - measure(U' '));
            }
            if (!line.text.empty()) flush();
            else line.width = 0;
        }
        for (std::size_t n = 0; i < end; ++i, ++n) {
            if (wrap && !line.text.empty() && line.width + widths[n] > width) flush();
            append(text[i]); line.width += widths[n];
        }
    }
    if (!text.empty()) flush();
    return lines;
}
} // namespace torchlight
