// original-code: the shipped libCEGUIBase.so.1 loads every glyph with
// FT_LOAD_FORCE_AUTOHINT (0x20); see research/ui-font-autohint.md.
// This test pins the port to the same flag: port glyphs must equal a direct
// system-FreeType render with 0x20 (same library, same inputs), and at least
// one sampled UI glyph must differ from FT_LOAD_DEFAULT (the flag is
// load-bearing on real UI data, not vacuous).
#include "torchlight/pak_archive.hpp"
#include "torchlight/ui_layout.hpp"
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <vector>
#ifdef TORCHLIGHT_HAVE_FREETYPE
#include <ft2build.h>
#include FT_FREETYPE_H
#endif

namespace {
unsigned checks = 0;
void require(bool b, const char* what) {
    ++checks;
    if (!b)
        throw std::runtime_error(what);
}
} // namespace

int main(int argc, char** argv) {
    try {
#ifndef TORCHLIGHT_HAVE_FREETYPE
        static_cast<void>(argc);
        static_cast<void>(argv);
        std::puts("SKIP: FreeType SDK absent; flag behavior untestable");
        return 77;
#else
        if (argc != 3 || std::string(argv[1]) != "--original")
            throw std::runtime_error("usage: ui_font_load_flags_test --original /path/to/pak.zip");
        const torchlight::PakArchive archive(argv[2]);
        torchlight::UiResources resources(archive);
        const auto* entry = archive.find_normalized("media/UI/BRLNSDB.TTF");
        if (entry == nullptr)
            throw std::runtime_error("UI font bytes missing");
        const auto file_bytes = archive.read(*entry);
        FT_Library library = nullptr;
        if (FT_Init_FreeType(&library) != 0)
            throw std::runtime_error("FreeType init failed");
        struct FaceGuard {
            FT_Face face = nullptr;
            ~FaceGuard() {
                if (face)
                    FT_Done_Face(face);
            }
        };
        struct LibraryGuard {
            FT_Library library = nullptr;
            ~LibraryGuard() {
                if (library)
                    FT_Done_FreeType(library);
            }
        } library_guard;
        library_guard.library = library;
        const struct Case {
            const char* font;
            int pixels;
            char32_t codepoints[4];
        } cases[] = {
            {"Serif", 11, {0x22, 0x23, 0x24, 0x30}},
            {"SerifBig", 16, {0x21, 0x22, 0x30, 0x36}},
        };
        bool saw_difference = false;
        for (const auto& test_case : cases) {
            auto* font = resources.font(test_case.font);
            if (font == nullptr || !font->valid())
                throw std::runtime_error(std::string("font missing: ") + test_case.font);
            font->notify_screen_size(1024, 768);
            FaceGuard face_guard;
            if (FT_New_Memory_Face(library, file_bytes.data(),
                                   static_cast<FT_Long>(file_bytes.size()), 0,
                                   &face_guard.face) != 0)
                throw std::runtime_error("direct face failed");
            const auto size = static_cast<FT_F26Dot6>(test_case.pixels * 64);
            if (FT_Set_Char_Size(face_guard.face, size, size, 96, 96) != 0)
                throw std::runtime_error("direct char size failed");
            for (const char32_t codepoint : test_case.codepoints) {
                const auto* port = font->glyph(codepoint);
                if (port == nullptr)
                    throw std::runtime_error("port glyph missing");
                // Oracle render with the original 0x20 flags.
                if (FT_Load_Char(face_guard.face, static_cast<FT_ULong>(codepoint),
                                 FT_LOAD_FORCE_AUTOHINT) != 0)
                    throw std::runtime_error("direct 0x20 load failed");
                const auto oracle_advance =
                    static_cast<float>(face_guard.face->glyph->advance.x) / 64.0F;
                if (FT_Render_Glyph(face_guard.face->glyph, FT_RENDER_MODE_NORMAL) != 0)
                    throw std::runtime_error("direct 0x20 render failed");
                const auto& bitmap = face_guard.face->glyph->bitmap;
                require(port->advance == oracle_advance, "port advance != 0x20 advance");
                require(port->bearing_x ==
                            static_cast<float>(face_guard.face->glyph->bitmap_left),
                        "port bearing_x != 0x20 bearing");
                require(port->bearing_y ==
                            static_cast<float>(face_guard.face->glyph->bitmap_top),
                        "port bearing_y != 0x20 bearing");
                require(port->width == static_cast<float>(bitmap.width) &&
                            port->height == static_cast<float>(bitmap.rows),
                        "port bitmap size != 0x20 bitmap size");
                // Same-library DEFAULT render: must differ somewhere, or the
                // flag change would be unproven on this data.
                if (FT_Load_Char(face_guard.face, static_cast<FT_ULong>(codepoint),
                                 FT_LOAD_DEFAULT) != 0)
                    throw std::runtime_error("direct default load failed");
                const bool advance_differs =
                    face_guard.face->glyph->advance.x !=
                    static_cast<FT_Pos>(oracle_advance * 64.0F);
                if (FT_Render_Glyph(face_guard.face->glyph, FT_RENDER_MODE_NORMAL) != 0)
                    throw std::runtime_error("direct default render failed");
                const auto& plain = face_guard.face->glyph->bitmap;
                bool bitmap_differs = plain.width != bitmap.width || plain.rows != bitmap.rows;
                if (!bitmap_differs && plain.width > 0 && plain.rows > 0) {
                    for (unsigned row = 0; row < plain.rows && !bitmap_differs; ++row)
                        if (std::memcmp(plain.buffer +
                                            static_cast<std::ptrdiff_t>(row) * plain.pitch,
                                        bitmap.buffer +
                                            static_cast<std::ptrdiff_t>(row) * bitmap.pitch,
                                        plain.width) != 0)
                            bitmap_differs = true;
                }
                if (advance_differs || bitmap_differs)
                    saw_difference = true;
            }
        }
        require(saw_difference, "0x20 indistinguishable from DEFAULT on sampled UI glyphs");
        std::printf("PASS: %u port-vs-0x20 glyph checks; flag proven load-bearing\n", checks);
        return 0;
#endif
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAIL: %s\n", e.what());
        return 1;
    }
}
