#include "torchlight/ui_layout.hpp"
#include <cstdio>
#include <cstring>
#include <stdexcept>

int main(int argc, char** argv) {
    try {
        if (argc != 2) throw std::runtime_error("usage: ui_font_probe pak.zip");
        const torchlight::PakArchive archive(argv[1]);
        torchlight::UiResources resources(archive);
        int fonts = 0, glyphs = 0;
        for (const char* name : {"Serif", "SerifBig", "SerifHuge", "SerifSmall", "FrizQuadrata",
                                 "FrizQuadrataSmall", "FrizQuadrataBig"}) {
            auto* font = resources.font(name);
            if (font == nullptr) throw std::runtime_error(std::string("font missing: ") + name);
            if (!font->valid()) throw std::runtime_error(std::string("font invalid: ") + name);
            font->notify_screen_size(1024, 768);
            int count = 0;
            for (char32_t codepoint = 32; codepoint < 127; ++codepoint)
                if (font->glyph(codepoint) != nullptr) ++count;
            if (count < 90) throw std::runtime_error(std::string("sparse atlas: ") + name);
            const auto& definition = font->definition();
            if (font->line_height() <= 0 || font->ascent() <= 0)
                throw std::runtime_error(std::string("degenerate metrics: ") + name);
            std::printf("%s size=%.0f native=%.0fx%.0f auto=%d aa=%d glyphs=%d line=%.2f ascent=%.2f\n",
                        name, definition.size, definition.native_horz, definition.native_vert,
                        definition.auto_scaled ? 1 : 0, definition.antialias ? 1 : 0, count,
                        font->line_height(), font->ascent());
            glyphs += count;
            ++fonts;
        }
        std::printf("PASS: %d original fonts, %d rasterized ASCII glyphs at 1024x768; "
                    "FreeType atlas semantics only, NOT original OGRE/CEGUI framebuffer parity\n",
                    fonts, glyphs);
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAIL: %s\n", e.what());
        return 1;
    }
}
