#include "torchlight/ui_text.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace torchlight {
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
                                     const std::function<float(char32_t)> &advance) {
    if (!std::isfinite(width) || width <= 0) return {};
    const auto text = ui_decode_utf8(input);
    std::vector<UiTextLine> lines;
    UiTextLine line;
    const auto measure = [&](char32_t c) {
        const float value = advance(c);
        if (!std::isfinite(value) || value < 0)
            throw std::invalid_argument("invalid UI glyph advance");
        return value;
    };
    const auto flush = [&] { lines.push_back(std::move(line)); line = {}; };
    for (std::size_t i = 0; i < text.size();) {
        const char32_t c = text[i];
        if (c == U'\r' || c == U'\n') {
            ++i;
            if (c == U'\r' && i < text.size() && text[i] == U'\n') ++i;
            flush();
            continue;
        }
        if (c == U' ' || c == U'\t') {
            const int count = c == U'\t' ? 4 : 1; // portable tab fallback
            for (int n = 0; n < count; ++n) {
                const auto a = measure(U' ');
                if (!wrap || line.width + a <= width) {
                    line.text += U' '; line.width += a;
                }
            }
            ++i;
            continue;
        }
        std::size_t end = i;
        float word_width = 0;
        std::vector<float> widths;
        while (end < text.size() && text[end] != U'\n' && text[end] != U'\r' &&
               text[end] != U' ' && text[end] != U'\t') {
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
            line.text += text[i]; line.width += widths[n];
        }
    }
    if (!text.empty()) flush();
    return lines;
}
} // namespace torchlight
