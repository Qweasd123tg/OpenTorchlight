# 05-font-and-text

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `src/ui_font.cpp:106–224`

SHA256 полного файла: `b46d696621add63b6376ed58dfdc38491dcc6478d89309b134782412b685bfb0`

```text
  106 |         FT_Library value = nullptr;
  107 |         Library() { if (FT_Init_FreeType(&value) != 0) value = nullptr; }
  108 |         ~Library() { if (value) FT_Done_FreeType(value); }
  109 |     };
  110 |     static Library library;
  111 |     return library.value;
  112 | }
  113 | #endif
  114 | constexpr int kAtlasSize = 512;
  115 | constexpr int kAtlasPadding = 1;
  116 | } // namespace
  117 | 
  118 | struct UiFont::Impl {
  119 |     UiFontDefinition definition;
  120 |     std::vector<std::uint8_t> file_bytes;
  121 |     bool ready = false;
  122 |     float horz_scale = 1, vert_scale = 1;
  123 |     float line_height = 0, ascent = 0;
  124 |     std::vector<std::uint8_t> atlas =
  125 |         std::vector<std::uint8_t>(static_cast<std::size_t>(kAtlasSize) * kAtlasSize * 4, 0);
  126 |     std::map<char32_t, UiGlyph> glyphs;
  127 |     int pack_x = kAtlasPadding, pack_y = kAtlasPadding, row_height = 0;
  128 |     std::uint64_t revision = 1;
  129 | #ifdef TORCHLIGHT_HAVE_FREETYPE
  130 |     FT_Face face = nullptr;
  131 | #endif
  132 |     ~Impl() {
  133 | #ifdef TORCHLIGHT_HAVE_FREETYPE
  134 |         if (face)
  135 |             FT_Done_Face(face);
  136 | #endif
  137 |     }
  138 |     void set_char_size() {
  139 | #ifdef TORCHLIGHT_HAVE_FREETYPE
  140 |         if (face == nullptr)
  141 |             return;
  142 |         const float points = definition.size * 64.0F;
  143 |         const float sx = points * (definition.auto_scaled ? horz_scale : 1.0F);
  144 |         const float sy = points * (definition.auto_scaled ? vert_scale : 1.0F);
  145 |         // Port bound: reject dimensions exceeding the fixed atlas before float
  146 |         // to integer conversion. Do not pass NaN/overflow to FreeType.
  147 |         if (!std::isfinite(sx) || !std::isfinite(sy) || sx <= 0 || sy <= 0 ||
  148 |             sx > kAtlasSize * 64.0F || sy > kAtlasSize * 64.0F) {
  149 |             ready = false;
  150 |             return;
  151 |         }
  152 |         const auto char_width = static_cast<FT_F26Dot6>(std::trunc(sx));
  153 |         const auto char_height = static_cast<FT_F26Dot6>(std::trunc(sy));
  154 |         // library-derived: both pinned CEGUI renderers return 96.
  155 |         // OgreCEGUIRenderer::getHorz/VertScreenDPI (0x6d30/0x6d40) and
  156 |         // OpenGLRenderer::getHorz/VertScreenDPI (0x281d0/0x281e0) do
  157 |         // `mov $0x60,%eax`. Formula Size*64 + trunc((Size*64)*scale) is
  158 |         // FreeTypeFont::updateFont @0xe07b0; scales are
  159 |         // Font::notifyScreenResolution @0xd18e0. See research/ui-font-dpi.md.
  160 |         if (FT_Set_Char_Size(face, char_width, char_height, 96, 96) != 0) {
  161 |             ready = false;
  162 |             return;
  163 |         }
  164 |         const auto &metrics = face->size->metrics;
  165 |         ascent = static_cast<float>(metrics.ascender) / 64.0F;
  166 |         line_height = static_cast<float>(metrics.height) / 64.0F;
  167 |         ready = true;
  168 | #else
  169 |         ready = false;
  170 | #endif
  171 |     }
  172 |     const UiGlyph *rasterize(char32_t codepoint) {
  173 |         if (!ready)
  174 |             return nullptr;
  175 |         if (const auto it = glyphs.find(codepoint); it != glyphs.end())
  176 |             return &it->second;
  177 | #ifdef TORCHLIGHT_HAVE_FREETYPE
  178 |         if (FT_Load_Char(face, codepoint, FT_LOAD_DEFAULT) != 0)
  179 |             return nullptr;
  180 |         if (FT_Render_Glyph(face->glyph,
  181 |                             definition.antialias ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO) != 0)
  182 |             return nullptr;
  183 |         const auto &bitmap = face->glyph->bitmap;
  184 |         UiGlyph glyph;
  185 |         glyph.advance = static_cast<float>(face->glyph->advance.x) / 64.0F;
  186 |         glyph.bearing_x = static_cast<float>(face->glyph->bitmap_left);
  187 |         glyph.bearing_y = static_cast<float>(face->glyph->bitmap_top);
  188 |         glyph.width = static_cast<float>(bitmap.width);
  189 |         glyph.height = static_cast<float>(bitmap.rows);
  190 |         if (bitmap.width > 0 && bitmap.rows > 0) {
  191 |             if (bitmap.width > kAtlasSize - 2 * kAtlasPadding ||
  192 |                 bitmap.rows > kAtlasSize - 2 * kAtlasPadding)
  193 |                 return nullptr;
  194 |             if (pack_x + static_cast<int>(bitmap.width) + kAtlasPadding > kAtlasSize) {
  195 |                 pack_x = kAtlasPadding;
  196 |                 pack_y += row_height + kAtlasPadding;
  197 |                 row_height = 0;
  198 |             }
  199 |             if (pack_y + static_cast<int>(bitmap.rows) + kAtlasPadding > kAtlasSize)
  200 |                 return nullptr; // bounded atlas; no growth policy in this pass
  201 |             for (unsigned row = 0; row < bitmap.rows; ++row) {
  202 |                 const auto *source = bitmap.buffer + static_cast<std::ptrdiff_t>(row) * bitmap.pitch;
  203 |                 for (unsigned column = 0; column < bitmap.width; ++column) {
  204 |                     const auto alpha = bitmap.pixel_mode == FT_PIXEL_MODE_MONO
  205 |                                            ? ((source[column / 8] >> (7 - (column % 8))) & 1) * 255
  206 |                                            : source[column];
  207 |                     const auto x = pack_x + static_cast<int>(column);
  208 |                     const auto y = pack_y + static_cast<int>(row);
  209 |                     const auto offset = (static_cast<std::size_t>(y) * kAtlasSize + x) * 4;
  210 |                     atlas[offset + 0] = 255;
  211 |                     atlas[offset + 1] = 255;
  212 |                     atlas[offset + 2] = 255;
  213 |                     atlas[offset + 3] = static_cast<std::uint8_t>(alpha);
  214 |                 }
  215 |             }
  216 |             glyph.u0 = static_cast<float>(pack_x) / kAtlasSize;
  217 |             glyph.v0 = static_cast<float>(pack_y) / kAtlasSize;
  218 |             glyph.u1 = static_cast<float>(pack_x + static_cast<int>(bitmap.width)) / kAtlasSize;
  219 |             glyph.v1 = static_cast<float>(pack_y + static_cast<int>(bitmap.rows)) / kAtlasSize;
  220 |             pack_x += static_cast<int>(bitmap.width) + kAtlasPadding;
  221 |             row_height = std::max(row_height, static_cast<int>(bitmap.rows));
  222 |             ++revision;
  223 |         }
  224 |         return &glyphs.emplace(codepoint, glyph).first->second;
```

## `src/ui_text.cpp:29–84`

SHA256 полного файла: `8db9589852de059b305f42bba9469f9841f793915f0466dfe4109783071d47c7`

```text
   29 | }
   30 | std::vector<UiTextLine> ui_text_lines(std::string_view input, float width, bool wrap,
   31 |                                      const std::function<float(char32_t)> &advance) {
   32 |     if (!std::isfinite(width) || width <= 0) return {};
   33 |     const auto text = ui_decode_utf8(input);
   34 |     std::vector<UiTextLine> lines;
   35 |     UiTextLine line;
   36 |     const auto measure = [&](char32_t c) {
   37 |         const float value = advance(c);
   38 |         if (!std::isfinite(value) || value < 0)
   39 |             throw std::invalid_argument("invalid UI glyph advance");
   40 |         return value;
   41 |     };
   42 |     const auto flush = [&] { lines.push_back(std::move(line)); line = {}; };
   43 |     for (std::size_t i = 0; i < text.size();) {
   44 |         const char32_t c = text[i];
   45 |         if (c == U'\r' || c == U'\n') {
   46 |             ++i;
   47 |             if (c == U'\r' && i < text.size() && text[i] == U'\n') ++i;
   48 |             flush();
   49 |             continue;
   50 |         }
   51 |         if (c == U' ' || c == U'\t') {
   52 |             const int count = c == U'\t' ? 4 : 1; // portable tab fallback
   53 |             for (int n = 0; n < count; ++n) {
   54 |                 const auto a = measure(U' ');
   55 |                 if (!wrap || line.width + a <= width) {
   56 |                     line.text += U' '; line.width += a;
   57 |                 }
   58 |             }
   59 |             ++i;
   60 |             continue;
   61 |         }
   62 |         std::size_t end = i;
   63 |         float word_width = 0;
   64 |         std::vector<float> widths;
   65 |         while (end < text.size() && text[end] != U'\n' && text[end] != U'\r' &&
   66 |                text[end] != U' ' && text[end] != U'\t') {
   67 |             widths.push_back(measure(text[end++]));
   68 |             word_width += widths.back();
   69 |         }
   70 |         if (wrap && !line.text.empty() && line.width + word_width > width) {
   71 |             while (!line.text.empty() && line.text.back() == U' ') {
   72 |                 line.text.pop_back(); line.width = std::max(0.0F, line.width - measure(U' '));
   73 |             }
   74 |             if (!line.text.empty()) flush();
   75 |             else line.width = 0;
   76 |         }
   77 |         for (std::size_t n = 0; i < end; ++i, ++n) {
   78 |             if (wrap && !line.text.empty() && line.width + widths[n] > width) flush();
   79 |             line.text += text[i]; line.width += widths[n];
   80 |         }
   81 |     }
   82 |     if (!text.empty()) flush();
   83 |     return lines;
   84 | }
```

