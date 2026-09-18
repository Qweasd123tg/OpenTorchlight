#include "torchlight/ui_font.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <string>

#ifdef TORCHLIGHT_HAVE_FREETYPE
#include <ft2build.h>
#include FT_FREETYPE_H
#endif

namespace torchlight {
namespace {
std::string to_utf8(const std::vector<std::uint8_t> &bytes) {
    if (bytes.size() >= 2 && bytes[0] == 0xff && bytes[1] == 0xfe) {
        std::string out;
        for (std::size_t i = 2; i + 1 < bytes.size(); i += 2) {
            const unsigned c = bytes[i] | (unsigned(bytes[i + 1]) << 8);
            if (c < 0x80)
                out.push_back(static_cast<char>(c));
            else if (c < 0x800) {
                out.push_back(static_cast<char>(0xc0 | (c >> 6)));
                out.push_back(static_cast<char>(0x80 | (c & 63)));
            } else {
                out.push_back(static_cast<char>(0xe0 | (c >> 12)));
                out.push_back(static_cast<char>(0x80 | ((c >> 6) & 63)));
                out.push_back(static_cast<char>(0x80 | (c & 63)));
            }
        }
        return out;
    }
    const std::size_t start = bytes.size() >= 3 && bytes[0] == 0xef && bytes[1] == 0xbb &&
                                      bytes[2] == 0xbf
                                  ? 3
                                  : 0;
    return {bytes.begin() + static_cast<std::ptrdiff_t>(start), bytes.end()};
}
std::string attribute(std::string_view text, std::string_view key) {
    const std::string needle = std::string(key) + "=\"";
    const auto start = text.find(needle);
    if (start == std::string_view::npos)
        return {};
    const auto value = start + needle.size();
    const auto end = text.find('"', value);
    if (end == std::string_view::npos)
        throw std::invalid_argument("unterminated font attribute");
    return std::string(text.substr(value, end - value));
}
float number(const std::string &value, const char *label) {
    if (value.empty())
        throw std::invalid_argument(std::string("missing font ") + label);
    std::size_t consumed = 0;
    const float result = std::stof(value, &consumed);
    if (consumed != value.size() || !std::isfinite(result) || result <= 0)
        throw std::invalid_argument(std::string("invalid font ") + label);
    return result;
}
bool boolean(const std::string &value, bool fallback) {
    if (value.empty())
        return fallback;
    std::string lowered(value);
    for (auto &c : lowered)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    if (lowered == "true")
        return true;
    if (lowered == "false")
        return false;
    throw std::invalid_argument("invalid font boolean");
}
} // namespace

UiFontDefinition parse_ui_font_definition(const std::vector<std::uint8_t> &bytes,
                                          std::string_view source) {
    const auto text = to_utf8(bytes);
    const auto root = text.find("<Font");
    if (root == std::string::npos)
        throw std::invalid_argument("font XML root missing: " + std::string(source));
    const auto end = text.find('>', root);
    if (end == std::string::npos)
        throw std::invalid_argument("font XML root unterminated: " + std::string(source));
    const std::string_view tag(text.data() + static_cast<std::ptrdiff_t>(root),
                               end - root);
    UiFontDefinition definition;
    definition.name = attribute(tag, "Name");
    definition.filename = attribute(tag, "Filename");
    definition.size = number(attribute(tag, "Size"), "size");
    if (definition.name.empty() || definition.filename.empty())
        throw std::invalid_argument("font name/file missing: " + std::string(source));
    const auto native_horz = attribute(tag, "NativeHorzRes");
    const auto native_vert = attribute(tag, "NativeVertRes");
    if (!native_horz.empty())
        definition.native_horz = number(native_horz, "native width");
    if (!native_vert.empty())
        definition.native_vert = number(native_vert, "native height");
    definition.auto_scaled = boolean(attribute(tag, "AutoScaled"), false);
    definition.antialias = boolean(attribute(tag, "AntiAlias"), false);
    return definition;
}

namespace {
#ifdef TORCHLIGHT_HAVE_FREETYPE
FT_Library shared_library() {
    struct Library {
        FT_Library value = nullptr;
        Library() { if (FT_Init_FreeType(&value) != 0) value = nullptr; }
        ~Library() { if (value) FT_Done_FreeType(value); }
    };
    static Library library;
    return library.value;
}
#endif
constexpr int kAtlasSize = 512;
constexpr int kAtlasPadding = 1;
} // namespace

struct UiFont::Impl {
    UiFontDefinition definition;
    std::vector<std::uint8_t> file_bytes;
    bool ready = false;
    float horz_scale = 1, vert_scale = 1;
    float line_height = 0, ascent = 0;
    std::vector<std::uint8_t> atlas =
        std::vector<std::uint8_t>(static_cast<std::size_t>(kAtlasSize) * kAtlasSize * 4, 0);
    std::map<char32_t, UiGlyph> glyphs;
    int pack_x = kAtlasPadding, pack_y = kAtlasPadding, row_height = 0;
    std::uint64_t revision = 1;
#ifdef TORCHLIGHT_HAVE_FREETYPE
    FT_Face face = nullptr;
#endif
    ~Impl() {
#ifdef TORCHLIGHT_HAVE_FREETYPE
        if (face)
            FT_Done_Face(face);
#endif
    }
    void set_char_size() {
#ifdef TORCHLIGHT_HAVE_FREETYPE
        if (face == nullptr)
            return;
        const float points = definition.size * 64.0F;
        const float sx = points * (definition.auto_scaled ? horz_scale : 1.0F);
        const float sy = points * (definition.auto_scaled ? vert_scale : 1.0F);
        // Port bound: reject dimensions exceeding the fixed atlas before float
        // to integer conversion. Do not pass NaN/overflow to FreeType.
        if (!std::isfinite(sx) || !std::isfinite(sy) || sx <= 0 || sy <= 0 ||
            sx > kAtlasSize * 64.0F || sy > kAtlasSize * 64.0F) {
            ready = false;
            return;
        }
        const auto char_width = static_cast<FT_F26Dot6>(std::trunc(sx));
        const auto char_height = static_cast<FT_F26Dot6>(std::trunc(sy));
        // library-derived: both pinned CEGUI renderers return 96.
        // OgreCEGUIRenderer::getHorz/VertScreenDPI (0x6d30/0x6d40) and
        // OpenGLRenderer::getHorz/VertScreenDPI (0x281d0/0x281e0) do
        // `mov $0x60,%eax`. Formula Size*64 + trunc((Size*64)*scale) is
        // FreeTypeFont::updateFont @0xe07b0; scales are
        // Font::notifyScreenResolution @0xd18e0. See research/ui-font-dpi.md.
        if (FT_Set_Char_Size(face, char_width, char_height, 96, 96) != 0) {
            ready = false;
            return;
        }
        const auto &metrics = face->size->metrics;
        ascent = static_cast<float>(metrics.ascender) / 64.0F;
        line_height = static_cast<float>(metrics.height) / 64.0F;
        ready = true;
#else
        ready = false;
#endif
    }
    const UiGlyph *rasterize(char32_t codepoint) {
        if (!ready)
            return nullptr;
        if (const auto it = glyphs.find(codepoint); it != glyphs.end())
            return &it->second;
#ifdef TORCHLIGHT_HAVE_FREETYPE
        // original-code: CEGUI::FreeTypeFont::updateFont in the shipped
        // libCEGUIBase.so.1 (SHA-256 57a888d7…dda2aa) loads every glyph with
        // flags 0x20 (mov edx,0x20 before FT_Load_Char at 0xe0997/0xe099f).
        // 0x20 is FT_LOAD_FORCE_AUTOHINT. Research: research/ui-font-autohint.md.
        if (FT_Load_Char(face, codepoint, FT_LOAD_FORCE_AUTOHINT) != 0)
            return nullptr;
        if (FT_Render_Glyph(face->glyph,
                            definition.antialias ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO) != 0)
            return nullptr;
        const auto &bitmap = face->glyph->bitmap;
        UiGlyph glyph;
        glyph.advance = static_cast<float>(face->glyph->advance.x) / 64.0F;
        glyph.bearing_x = static_cast<float>(face->glyph->bitmap_left);
        glyph.bearing_y = static_cast<float>(face->glyph->bitmap_top);
        glyph.width = static_cast<float>(bitmap.width);
        glyph.height = static_cast<float>(bitmap.rows);
        if (bitmap.width > 0 && bitmap.rows > 0) {
            if (bitmap.width > kAtlasSize - 2 * kAtlasPadding ||
                bitmap.rows > kAtlasSize - 2 * kAtlasPadding)
                return nullptr;
            if (pack_x + static_cast<int>(bitmap.width) + kAtlasPadding > kAtlasSize) {
                pack_x = kAtlasPadding;
                pack_y += row_height + kAtlasPadding;
                row_height = 0;
            }
            if (pack_y + static_cast<int>(bitmap.rows) + kAtlasPadding > kAtlasSize)
                return nullptr; // bounded atlas; no growth policy in this pass
            for (unsigned row = 0; row < bitmap.rows; ++row) {
                const auto *source = bitmap.buffer + static_cast<std::ptrdiff_t>(row) * bitmap.pitch;
                for (unsigned column = 0; column < bitmap.width; ++column) {
                    const auto alpha = bitmap.pixel_mode == FT_PIXEL_MODE_MONO
                                           ? ((source[column / 8] >> (7 - (column % 8))) & 1) * 255
                                           : source[column];
                    const auto x = pack_x + static_cast<int>(column);
                    const auto y = pack_y + static_cast<int>(row);
                    const auto offset = (static_cast<std::size_t>(y) * kAtlasSize + x) * 4;
                    atlas[offset + 0] = 255;
                    atlas[offset + 1] = 255;
                    atlas[offset + 2] = 255;
                    atlas[offset + 3] = static_cast<std::uint8_t>(alpha);
                }
            }
            glyph.u0 = static_cast<float>(pack_x) / kAtlasSize;
            glyph.v0 = static_cast<float>(pack_y) / kAtlasSize;
            glyph.u1 = static_cast<float>(pack_x + static_cast<int>(bitmap.width)) / kAtlasSize;
            glyph.v1 = static_cast<float>(pack_y + static_cast<int>(bitmap.rows)) / kAtlasSize;
            pack_x += static_cast<int>(bitmap.width) + kAtlasPadding;
            row_height = std::max(row_height, static_cast<int>(bitmap.rows));
            ++revision;
        }
        return &glyphs.emplace(codepoint, glyph).first->second;
#else
        static_cast<void>(codepoint);
        return nullptr;
#endif
    }
};

UiFont::UiFont(const PakArchive &archive, UiFontDefinition definition)
    : impl_(std::make_unique<Impl>()) {
    impl_->definition = std::move(definition);
#ifdef TORCHLIGHT_HAVE_FREETYPE
    const auto *entry = archive.find_normalized(impl_->definition.filename);
    if (!entry)
        return;
    impl_->file_bytes = archive.read(*entry);
    const auto library = shared_library();
    if (library == nullptr)
        return;
    if (FT_New_Memory_Face(library, impl_->file_bytes.data(),
                           static_cast<FT_Long>(impl_->file_bytes.size()), 0, &impl_->face) != 0) {
        impl_->face = nullptr;
        return;
    }
    impl_->set_char_size();
#else
    static_cast<void>(archive);
#endif
}
UiFont::~UiFont() = default;
UiFont::UiFont(UiFont &&) noexcept = default;
UiFont &UiFont::operator=(UiFont &&) noexcept = default;

const UiFontDefinition &UiFont::definition() const noexcept {
    return impl_->definition;
}
bool UiFont::valid() const noexcept {
    return impl_->ready;
}
void UiFont::notify_screen_size(float width, float height) {
    if (!std::isfinite(width) || !std::isfinite(height) || width <= 0 || height <= 0 ||
        impl_->definition.native_horz <= 0 || impl_->definition.native_vert <= 0)
        return;
    const float sx = width / impl_->definition.native_horz;
    const float sy = height / impl_->definition.native_vert;
    if (sx == impl_->horz_scale && sy == impl_->vert_scale)
        return;
    impl_->horz_scale = sx;
    impl_->vert_scale = sy;
    ++impl_->revision;
    impl_->glyphs.clear();
    impl_->pack_x = kAtlasPadding;
    impl_->pack_y = kAtlasPadding;
    impl_->row_height = 0;
    std::fill(impl_->atlas.begin(), impl_->atlas.end(), 0);
    impl_->set_char_size();
}
float UiFont::line_height() const noexcept {
    return impl_->line_height;
}
float UiFont::ascent() const noexcept {
    return impl_->ascent;
}
const UiGlyph *UiFont::glyph(char32_t codepoint) {
    return impl_->rasterize(codepoint);
}
float UiFont::advance(char32_t codepoint) {
    const auto *result = impl_->rasterize(codepoint);
    return result ? result->advance : 0.0F;
}
const std::vector<std::uint8_t> &UiFont::atlas_rgba() const noexcept {
    return impl_->atlas;
}
int UiFont::atlas_width() const noexcept {
    return kAtlasSize;
}
int UiFont::atlas_height() const noexcept {
    return kAtlasSize;
}
std::uint64_t UiFont::atlas_revision() const noexcept {
    return impl_->revision;
}
} // namespace torchlight
