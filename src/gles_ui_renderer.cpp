#include "torchlight/gles_ui_renderer.hpp"
#include "torchlight/dds_texture.hpp"
#include "torchlight/png_texture.hpp"
#include "torchlight/ui_text.hpp"
#include <cmath>
#include <GLES2/gl2.h>
#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>

namespace torchlight {
namespace {
GLuint shader(GLenum kind, const char *source) {
    const auto handle = glCreateShader(kind);
    glShaderSource(handle, 1, &source, nullptr);
    glCompileShader(handle);
    GLint ok = 0;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[2048]{};
        glGetShaderInfoLog(handle, sizeof(log), nullptr, log);
        glDeleteShader(handle);
        throw std::runtime_error(std::string("UI shader: ") + log);
    }
    return handle;
}
struct Vertex {
    float x, y, u, v;
};
struct Texture {
    GLuint id = 0;
    int width = 0, height = 0;
};
struct FontTexture {
    GLuint id = 0;
    UiFont *font = nullptr;
    int width = 0, height = 0;
    float screen_width = 0, screen_height = 0;
    std::uint64_t uploaded_revision = 0;
};
std::string upper(std::string s) {
    for (auto &c : s)
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return s;
}
// resource-derived: CEGUI 0.6.2 TextColour-family values are AARRGGBB hex.
std::optional<std::array<float, 4>> parse_text_argb(const std::string &raw) {
    auto hex = [](char c) -> int {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return -1;
    };
    if (raw.size() != 8)
        return std::nullopt;
    int v[8];
    for (int i = 0; i < 8; ++i)
        if ((v[i] = hex(raw[static_cast<std::size_t>(i)])) < 0)
            return std::nullopt;
    return std::array<float, 4>{static_cast<float>(v[2] * 16 + v[3]) / 255.0F,
                                static_cast<float>(v[4] * 16 + v[5]) / 255.0F,
                                static_cast<float>(v[6] * 16 + v[7]) / 255.0F,
                                static_cast<float>(v[0] * 16 + v[1]) / 255.0F};
}
// resource-derived + library-derived: CEGUI 0.6.2 TextColour is AARRGGBB hex
// (layout Value like FFFFFFFF, c2FFFFFF, FFFF0000); Font::DefaultColour is
// 0xFFFFFFFF (white). Replaces the prototype warm tint.
std::array<float, 4> text_colour(const UiResolvedWidget &w) {
    return parse_text_argb(w.property("TextColour")).value_or(std::array<float, 4>{1, 1, 1, 1});
}
} // namespace
struct GlesUiRenderer::Impl {
    const PakArchive *archive;
    UiResources *resources;
    GLuint program = 0, buffer = 0;
    GLint screen = -1, color = -1, textured = -1, sampler = -1;
    std::map<std::string, Texture> textures;
    std::set<std::string> failed;
    std::map<std::string, FontTexture> fonts;
    std::set<std::string> failed_fonts;
    int viewport_width = 0, viewport_height = 0;
    explicit Impl(const PakArchive &a, UiResources &r) : archive(&a), resources(&r) {
        const char *vs = "attribute vec2 position; attribute vec2 texcoord; uniform vec2 screen; "
                         "varying vec2 uv; void "
                         "main(){uv=texcoord;gl_Position=vec4(position.x*2.0/"
                         "screen.x-1.0,1.0-position.y*2.0/screen.y,0.0,1.0);}";
        const char *fs = "precision mediump float; varying vec2 uv; uniform vec4 color; uniform "
                         "sampler2D image; uniform bool textured; void "
                         "main(){gl_FragColor=textured?texture2D(image,uv)*color:color;}";
        const auto vertex = shader(GL_VERTEX_SHADER, vs);
        GLuint fragment = 0;
        try {
            fragment = shader(GL_FRAGMENT_SHADER, fs);
        } catch (...) {
            glDeleteShader(vertex);
            throw;
        }
        program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glBindAttribLocation(program, 0, "position");
        glBindAttribLocation(program, 1, "texcoord");
        glLinkProgram(program);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        GLint linked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if (!linked) {
            glDeleteProgram(program);
            program = 0;
            throw std::runtime_error("UI program link failed");
        }
        screen = glGetUniformLocation(program, "screen");
        color = glGetUniformLocation(program, "color");
        textured = glGetUniformLocation(program, "textured");
        sampler = glGetUniformLocation(program, "image");
        glGenBuffers(1, &buffer);
    }
    ~Impl() {
        for (auto &pair : textures)
            glDeleteTextures(1, &pair.second.id);
        for (auto &pair : fonts)
            glDeleteTextures(1, &pair.second.id);
        if (buffer)
            glDeleteBuffers(1, &buffer);
        if (program)
            glDeleteProgram(program);
    }
    static void quad(std::vector<Vertex> &out, UiRect r, UiRect uv = {0, 0, 1, 1}) {
        out.insert(out.end(), {{r.x, r.y, uv.x, uv.y},
                               {r.x + r.width, r.y, uv.x + uv.width, uv.y},
                               {r.x, r.y + r.height, uv.x, uv.y + uv.height},
                               {r.x, r.y + r.height, uv.x, uv.y + uv.height},
                               {r.x + r.width, r.y, uv.x + uv.width, uv.y},
                               {r.x + r.width, r.y + r.height, uv.x + uv.width, uv.y + uv.height}});
    }
    void begin_state(int width, int height) {
        viewport_width = width;
        viewport_height = height;
        glViewport(0, 0, width, height);
        glDisable(GL_SCISSOR_TEST);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUseProgram(program);
        glUniform2f(screen, static_cast<float>(width), static_cast<float>(height));
        glUniform1i(sampler, 0);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<const void *>(2 * sizeof(float)));
    }
    void begin(int width, int height) {
        begin_state(width, height);
        glClearColor(.045F, .055F, .065F, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void end() {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glUseProgram(0);
        glDisable(GL_BLEND);
        glDisable(GL_SCISSOR_TEST);
    }
    void draw_batch(const std::vector<Vertex> &vertices, std::array<float, 4> tint,
                    GLuint texture = 0) {
        if (vertices.empty())
            return;
        glUniform4fv(color, 1, tint.data());
        glUniform1i(textured, texture != 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)),
                     vertices.data(), GL_STREAM_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
    }
    Texture *load(const std::string &path) {
        if (auto it = textures.find(path); it != textures.end())
            return &it->second;
        if (failed.count(path))
            return nullptr;
        try {
            const auto *entry = archive->find_normalized(path);
            if (!entry)
                throw std::runtime_error("missing image texture");
            const auto bytes = archive->read(*entry);
            Texture result;
            std::vector<std::uint8_t> rgba;
            if (bytes.size() >= 4 && bytes[0] == 'D' && bytes[1] == 'D' && bytes[2] == 'S' &&
                bytes[3] == ' ') {
                auto image = decode_dds(bytes);
                result.width = static_cast<int>(image.width);
                result.height = static_cast<int>(image.height);
                rgba = std::move(image.rgba);
            } else {
                auto image = decode_png(bytes);
                result.width = static_cast<int>(image.width);
                result.height = static_cast<int>(image.height);
                rgba = std::move(image.rgba);
            }
            GLint maximum = 0;
            glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maximum);
            if (result.width <= 0 || result.height <= 0 || result.width > maximum ||
                result.height > maximum)
                throw std::runtime_error("image exceeds texture limit");
            glGenTextures(1, &result.id);
            glBindTexture(GL_TEXTURE_2D, result.id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, result.width, result.height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, rgba.data());
            return &textures.emplace(path, result).first->second;
        } catch (const std::exception &e) {
            failed.insert(path);
            std::cerr << "ui_texture_error=" << path << ": " << e.what() << '\n';
            return nullptr;
        }
    }
    FontTexture *load_font(const std::string &name) {
        if (name.empty())
            return nullptr;
        const auto key = upper(name);
        if (auto it = fonts.find(key); it != fonts.end())
            return &it->second;
        if (failed_fonts.count(key))
            return nullptr;
        auto *font = resources->font(key);
        if (font == nullptr || !font->valid()) {
            failed_fonts.insert(key);
            return nullptr;
        }
        FontTexture result;
        result.font = font;
        result.width = font->atlas_width();
        result.height = font->atlas_height();
        glGenTextures(1, &result.id);
        return &fonts.emplace(key, result).first->second;
    }
    // Screen notification may reset the CPU atlas. Upload is deferred until
    // glyphs used by this draw have actually been rasterized.
    FontTexture *prepare_font(const std::string &name, int width, int height) {
        auto *texture = load_font(name);
        if (texture == nullptr) return nullptr;
        if (texture->screen_width != static_cast<float>(width) ||
            texture->screen_height != static_cast<float>(height)) {
            texture->font->notify_screen_size(static_cast<float>(width), static_cast<float>(height));
            texture->screen_width = static_cast<float>(width);
            texture->screen_height = static_cast<float>(height);
        }
        return texture->font->valid() ? texture : nullptr;
    }
    void sync_font(FontTexture *texture) {
        if (!texture || texture->uploaded_revision == texture->font->atlas_revision()) return;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA,
                    GL_UNSIGNED_BYTE, texture->font->atlas_rgba().data());
        texture->uploaded_revision = texture->font->atlas_revision();
    }
    // Returns false when no glyph atlas is available and the prototype
    // diagnostic glyphs must be used instead.
    bool text_run(FontTexture *texture, std::string_view text, float x, float y, float max_x,
                  std::vector<Vertex> &out) {
        if (texture == nullptr)
            return false;
        const float baseline = y + texture->font->ascent();
        for (const auto character : ui_decode_utf8(text)) {
            if (character == U'\r' || character == U'\n') break;
            const auto *glyph = texture->font->glyph(character);
            if (glyph == nullptr)
                continue;
            if (x + glyph->advance > max_x)
                break;
            if (glyph->width > 0 && glyph->height > 0)
                quad(out,
                     {x + glyph->bearing_x, baseline - glyph->bearing_y, glyph->width,
                      glyph->height},
                     {glyph->u0, glyph->v0, glyph->u1 - glyph->u0, glyph->v1 - glyph->v0});
            x += glyph->advance;
        }
        sync_font(texture);
        return true;
    }
    bool draw_text(const std::string &font_name, std::string_view text, float x, float y,
                   float max_x, std::array<float, 4> tint) {
        auto *texture = prepare_font(font_name, viewport_width, viewport_height);
        if (texture == nullptr)
            return false;
        std::vector<Vertex> vertices;
        if (!text_run(texture, text, x, y, max_x, vertices))
            return false;
        draw_batch(vertices, tint, texture->id);
        return true;
    }
    static void text(std::vector<Vertex> &v, std::string_view s, float x, float y, int scale,
                     int width) {
        for (const auto c : s) {
            if (x + 6 * scale > width - 8)
                break;
            const auto glyph = inventory_glyph(c);
            for (std::size_t row = 0; row < glyph.size(); ++row)
                for (int col = 0; col < 5; ++col)
                    if (glyph[row] & (1U << (4 - col)))
                        quad(v, {x + col * scale, y + static_cast<float>(row * scale),
                                 static_cast<float>(scale), static_cast<float>(scale)});
            x += 6 * scale;
        }
    }
    void scissor(UiRect clip) {
        const int x0 = std::clamp(static_cast<int>(std::ceil(clip.x)), 0, viewport_width);
        const int y0 = std::clamp(static_cast<int>(std::ceil(clip.y)), 0, viewport_height);
        const int x1 = std::clamp(static_cast<int>(std::floor(clip.x + clip.width)), 0, viewport_width);
        const int y1 = std::clamp(static_cast<int>(std::floor(clip.y + clip.height)), 0, viewport_height);
        glEnable(GL_SCISSOR_TEST);
        glScissor(x0, viewport_height - y1, std::max(0, x1 - x0), std::max(0, y1 - y0));
    }
    void draw_widget_text(const UiResolvedWidget &w) {
        if (!w.visible || w.text.empty() || w.rect.width <= 0 || w.rect.height <= 0) return;
        // original-code: CEGUI default font is Serif
        // (CGameUI::create @0xa9f007 setDefaultFont("Serif", rodata 0xfe4944)).
        // Windows without Font inherit it; FrizQuadrata was a wrong fallback.
        auto *texture = prepare_font(w.font.empty() ? "Serif" : w.font,
                                     viewport_width, viewport_height);
        auto style = w.text_style();
        // resource-derived: an explicit per-TextComponent VertFormat/HorzFormat
        // (Checkbox Left/CentreAligned, StandardButton Centre/CentreAligned)
        // wins over the widget properties; components deferring through
        // *Property (StaticText/ItemText) keep the widget style. The last
        // specified pass is the main text.
        const auto passes = resources->widget_text_passes(w.type);
        if (passes && !passes->empty()) {
            for (const auto &pass : *passes) {
                if (pass.horz) style.horizontal = *pass.horz;
                if (pass.vert) style.vertical = *pass.vert;
            }
        }
        const int fallback_scale = viewport_width >= 950 ? 2 : 1;
        const float line_height = texture ? texture->font->line_height() : 8.0F * fallback_scale;
        // resource-derived: Falagard TextComponent passes from GuiLook.looknfeel
        // (shadow/outline offsets first, main text last). The look's first Area
        // sets the wrap width; a degenerate area (Checkbox labels past the box)
        // runs to the viewport edge. Unknown looks keep the widget-rect
        // single-pass fallback instead of invented geometry.
        const auto layout = resources->widget_text_layout(w.type);
        float wrap = w.rect.width;
        if (passes && !passes->empty() && layout) {
            const float candidate =
                layout->width_abs + layout->width_scale * w.rect.width;
            wrap = candidate > 0 ? candidate
                                 : static_cast<float>(viewport_width) - w.rect.x;
            if (!(wrap > 0)) wrap = w.rect.width;
        }
        const auto lines = ui_text_lines(w.text, wrap, style.wrap, [&](char32_t c) {
            return texture ? texture->font->advance(c) : 6.0F * fallback_scale;
        });
        float y = w.rect.y;
        const float height = static_cast<float>(lines.size()) * line_height;
        if (style.vertical == UiTextVertical::centre) y += (w.rect.height - height) * .5F;
        else if (style.vertical == UiTextVertical::bottom) y += w.rect.height - height;
        const float top = y;
        std::vector<Vertex> letters;
        for (const auto &line : lines) {
            float x = w.rect.x;
            if (style.horizontal == UiTextHorizontal::centre) x += (wrap - line.width) * .5F;
            else if (style.horizontal == UiTextHorizontal::right) x += wrap - line.width;
            for (const auto c : line.text) {
                if (texture) {
                    if (const auto *g = texture->font->glyph(c)) {
                        if (g->width > 0 && g->height > 0)
                            quad(letters, {x + g->bearing_x, y + texture->font->ascent() - g->bearing_y,
                                           g->width, g->height},
                                 {g->u0, g->v0, g->u1 - g->u0, g->v1 - g->v0});
                        x += g->advance;
                    }
                } else {
                    // Missing font: visible diagnostic glyph, never reinterpret UTF-8 bytes.
                    const char glyph = c >= 32 && c < 127 ? static_cast<char>(c) : '?';
                    text(letters, std::string(1, glyph), x, y, fallback_scale, viewport_width + 16);
                    x += 6.0F * fallback_scale;
                }
            }
            y += line_height;
        }
        sync_font(texture);
        if (!passes || passes->empty()) {
            scissor(w.clip);
            const auto base = text_colour(w);
            const std::array<float, 4> tint =
                w.enabled ? base
                          : std::array<float, 4>{base[0] * 0.55F, base[1] * 0.55F,
                                                 base[2] * 0.55F, base[3]};
            draw_batch(letters, tint, texture ? texture->id : 0);
        } else {
            // Text lives in the look Area, which may extend past the widget
            // (Checkbox labels); clip to the area against the viewport, not to
            // the widget box. Ancestor-container clipping stays open.
            float x0 = w.rect.x + passes->front().dx +
                       passes->front().x_scale * w.rect.width;
            float x1 = x0;
            float y0 = top;
            for (const auto &pass : *passes) {
                x0 = std::min(x0, w.rect.x + pass.dx + pass.x_scale * w.rect.width);
                x1 = std::max(x1, w.rect.x + pass.dx + pass.x_scale * w.rect.width);
                y0 = std::min(y0, top + pass.dy + pass.y_scale * w.rect.height);
            }
            UiRect area{x0, y0, (x1 - x0) + wrap, height + (top - y0)};
            area.x = std::max(area.x, 0.0F);
            area.y = std::max(area.y, 0.0F);
            area.width = std::min(area.width, static_cast<float>(viewport_width) - area.x);
            area.height = std::min(area.height, static_cast<float>(viewport_height) - area.y);
            scissor(area);
            for (const auto &pass : *passes) {
                std::array<float, 4> colour{1, 1, 1, 1};
                if (pass.colour_property.empty()) {
                    colour = text_colour(w);
                } else {
                    auto raw = w.property(pass.colour_property);
                    if (raw.empty())
                        raw = resources->look_default(w.type, pass.colour_property);
                    colour = parse_text_argb(raw).value_or(std::array<float, 4>{1, 1, 1, 1});
                }
                if (!w.enabled) {
                    colour[0] *= 0.55F;
                    colour[1] *= 0.55F;
                    colour[2] *= 0.55F;
                }
                const float sx = pass.dx + pass.x_scale * w.rect.width;
                const float sy = pass.dy + pass.y_scale * w.rect.height;
                if (sx == 0 && sy == 0) {
                    draw_batch(letters, colour, texture ? texture->id : 0);
                } else {
                    std::vector<Vertex> shifted;
                    shifted.reserve(letters.size());
                    for (const auto &v : letters)
                        shifted.push_back({v.x + sx, v.y + sy, v.u, v.v});
                    draw_batch(shifted, colour, texture ? texture->id : 0);
                }
            }
        }
        glDisable(GL_SCISSOR_TEST);
    }
    bool draw_image(const UiResolvedWidget &widget, UiRect source_rect) {
        if (widget.image.empty())
            return false;
        const auto image = resources->image(widget.image);
        if (!image)
            return false;
        auto *texture = load(image->texture_path);
        if (!texture)
            return false;
        UiRect region{image->x / texture->width, image->y / texture->height,
                      image->width / texture->width, image->height / texture->height};
        if (source_rect.width > 0 && source_rect.height > 0)
            region = {region.x + region.width * source_rect.x, region.y + region.height * source_rect.y,
                      region.width * source_rect.width, region.height * source_rect.height};
        const auto geometry = clip_ui_image(widget.rect, region,
                                             widget.has_clip ? &widget.clip : nullptr);
        // A valid image entirely outside its clip is successfully handled,
        // not a missing skin that should produce a fallback rectangle.
        if (!geometry) return true;
        std::vector<Vertex> vertices;
        quad(vertices, geometry->destination, geometry->source);
        draw_batch(vertices, {1, 1, 1, 1}, texture->id);
        return true;
    }
    // prototype: fallback palette, diagnostic glyphs and button chrome. The
    // resource-derived rectangles, images and fonts are not a complete CEGUI skin.
    void draw(const FrontendFrame &frame, int width, int height) {
        begin(width, height);
        for (const auto &w : frame.decorations)
            draw_image(w, {});
        if (!draw_text("FrizQuadrataBig", frame.title, 24, 16, static_cast<float>(width) - 24,
                       {.92F, .90F, .82F, 1})) {
            std::vector<Vertex> letters;
            text(letters, frame.title, 24, 20, width >= 950 ? 2 : 1, width);
            draw_batch(letters, {.92F, .90F, .82F, 1});
        }
        for (const auto &button : frame.buttons) {
            // resource-derived: checked GuiLook/Checkbox shows PushedImage
            // (UIIcons:CheckChecked, a complete checked box). Load slots and
            // class buttons carry selected without a pushed image, so they
            // keep the previous focus/normal choice.
            const auto explicit_state = [&](const char *name, const std::string &image) {
                return !image.empty() || (!button.supplemental &&
                    button.widget.properties.find(name) != button.widget.properties.end());
            };
            const std::string image_name = !button.enabled && explicit_state("DisabledImage", button.disabled_image)
                ? button.disabled_image : button.selected && button.enabled && explicit_state("PushedImage", button.pushed_image)
                ? button.pushed_image : button.focused && button.enabled && explicit_state("HoverImage", button.hover_image)
                ? button.hover_image : button.image;
            auto background = button.widget;
            background.rect = button.rect;
            background.image = image_name;
            // Keep the pre-existing diagnostic fallback for a genuinely
            // missing look (e.g. minimal authored fixtures). A known look or
            // an explicit image property, even empty, must never acquire it.
            const bool missing_look = !button.widget.type.empty() &&
                !resources->widget_images(button.widget.type) &&
                button.widget.properties.count("NormalImage") == 0 &&
                button.widget.properties.count("Image") == 0;
            if (!draw_image(background, {}) && (button.supplemental || missing_look)) {
                std::vector<Vertex> v; quad(v, button.rect);
                draw_batch(v, button.enabled
                    ? (button.focused ? std::array<float, 4>{.32F, .30F, .21F, .95F}
                                      : std::array<float, 4>{.12F, .15F, .17F, .95F})
                    : std::array<float, 4>{.08F, .09F, .1F, .85F});
            }
            auto label = button.widget;
            label.rect = button.rect;
            label.text = button.text;
            label.font = button.font.empty() ? "Serif" : button.font;
            label.enabled = button.enabled;
            // Centring is a fallback-port policy only for controls whose look
            // defines no TextComponent area (supplemental buttons). Real looks
            // carry their own VertFormat/HorzFormat (Checkbox Left/Centre,
            // StandardButton Centre/Centre); forcing centre there pushed
            // checkbox labels hundreds of pixels right of the box.
            if (label.property("HorzFormatting").empty() && label.property("HorzTextFormatting").empty() &&
                (!resources->widget_text_passes(label.type) ||
                 resources->widget_text_passes(label.type)->empty()))
                label.properties["HorzFormatting"] = "CentreAligned";
            if (label.property("VertFormatting").empty() &&
                (!resources->widget_text_passes(label.type) ||
                 resources->widget_text_passes(label.type)->empty()))
                label.properties["VertFormatting"] = "VertCentred";
            draw_widget_text(label);
            // PORT selection chrome belongs only to PORT controls. An original
            // checkbox/tab must not acquire an invented gold border.
            if (button.selected && button.supplemental) {
                std::vector<Vertex> border;
                quad(border, {button.rect.x, button.rect.y, button.rect.width, 2});
                quad(border, {button.rect.x, button.rect.y + button.rect.height - 2, button.rect.width, 2});
                draw_batch(border, {.9F, .75F, .3F, 1});
            }
        }
        for (const auto &w : frame.texts) draw_widget_text(w);
        float y = 48.0F;
        auto *note_font = prepare_font("SerifSmall", width, height);
        for (const auto &line : frame.notes) {
            std::vector<Vertex> letters;
            if (note_font != nullptr &&
                text_run(note_font, line.text, 24, y, static_cast<float>(width) - 24, letters))
                draw_batch(letters, {.88F, .86F, .78F, 1}, note_font->id);
            else {
                text(letters, line.text, 24, y, width >= 950 ? 2 : 1, width);
                draw_batch(letters, {.92F, .90F, .82F, 1});
            }
            y += note_font != nullptr ? std::max(9.0F, note_font->font->line_height() + 2.0F)
                                      : 9.0F * (width >= 950 ? 2 : 1);
        }
        end();
    }
    // Composites over the current scene; never clears the framebuffer.
    void draw_hud(const UiHudFrame &frame, int width, int height) {
        begin_state(width, height);
        for (const auto &w : frame.images)
            draw_image(w, {});
        for (const auto &bar : frame.bars) {
            auto rect = bar.widget.rect;
            if (bar.vertical) {
                const float full = rect.height;
                rect.height = full * bar.fraction;
                if (bar.bottom_anchored)
                    rect.y += full - rect.height;
            } else
                rect.width *= bar.fraction;
            if (rect.width <= 0 || rect.height <= 0)
                continue;
            auto widget = bar.widget;
            widget.rect = rect;
            draw_image(widget, {});
        }
        for (const auto &w : frame.buttons) draw_image(w, {});
        for (const auto &w : frame.texts) draw_widget_text(w);
        end();
    }
    // The window frame geometry stays prototype; text uses the resource font.
    void draw_overlay(const std::vector<InventoryViewLine> &lines, bool inventory_open, int width,
                      int height) {
        if (lines.empty() && !inventory_open) return;
        const auto fill_rectangle = [](int x, int y, int w, int h, float r, float g, float b) {
            glEnable(GL_SCISSOR_TEST);
            glScissor(x, y, w, h);
            glClearColor(r, g, b, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT);
        };
        begin_state(width, height);
        glEnable(GL_SCISSOR_TEST);
        const int top_height = std::max(54, height / 12);
        fill_rectangle(0, height - top_height, width, top_height, 0.18F, 0.105F, 0.035F);
        const int status_size = std::max(12, std::min(width, height) / 45);
        fill_rectangle(status_size, height - top_height / 2 - status_size / 2, status_size,
                       status_size, 0.72F, 0.43F, 0.10F);
        const int left = 24;
        int top = height - 12;
        if (inventory_open) {
            fill_rectangle(12, 12, std::max(0, width - 24), std::max(0, height - 24), 0.075F,
                           0.070F, 0.060F);
            top = height - 26;
        }
        auto *texture = prepare_font("SerifSmall", width, height);
        const float line_height =
            texture != nullptr ? std::max(11.0F, texture->font->line_height() + 3.0F) : 11.0F;
        for (const auto &line : lines) {
            if (static_cast<float>(top) - line_height < 12)
                break;
            const int baseline_top = top - static_cast<int>(line_height) + 3;
            if (line.selected)
                fill_rectangle(left - 6, baseline_top, std::max(0, width - 2 * left),
                               static_cast<int>(line_height), 0.28F, 0.20F, 0.08F);
            glDisable(GL_SCISSOR_TEST);
            std::vector<Vertex> letters;
            if (texture != nullptr &&
                text_run(texture, line.text, static_cast<float>(left),
                         static_cast<float>(height - top),
                         static_cast<float>(width - left), letters))
                draw_batch(letters, {.93F, .88F, .72F, 1}, texture->id);
            else {
                const int scale = width >= 950 ? 2 : 1;
                int x = left;
                for (const char c : line.text.substr(
                         0, static_cast<std::size_t>(std::max(0, width - 2 * left) / (6 * scale)))) {
                    const auto glyph = inventory_glyph(c);
                    for (int row = 0; row < 7; ++row)
                        for (int column = 0; column < 5; ++column)
                            if (glyph[row] & (1U << (4 - column)))
                                fill_rectangle(x + column * scale,
                                               top - (row + 1) * scale, scale, scale, 0.93F,
                                               0.88F, 0.72F);
                    x += 6 * scale;
                }
            }
            top -= static_cast<int>(line_height);
        }
        glDisable(GL_SCISSOR_TEST);
        end();
        if (glGetError() != GL_NO_ERROR)
            throw std::runtime_error("OpenGL ES failed while drawing the scene preview");
    }
};
GlesUiRenderer::GlesUiRenderer(const PakArchive &a, UiResources &r)
    : impl_(std::make_unique<Impl>(a, r)) {
}
GlesUiRenderer::~GlesUiRenderer() = default;
void GlesUiRenderer::draw(const FrontendFrame &f, int w, int h) {
    impl_->draw(f, w, h);
}
void GlesUiRenderer::draw_hud(const UiHudFrame &f, int w, int h) {
    impl_->draw_hud(f, w, h);
}
void GlesUiRenderer::draw_overlay(const std::vector<InventoryViewLine> &lines, bool open, int w,
                                  int h) {
    impl_->draw_overlay(lines, open, w, h);
}
void draw_inventory_overlay(const std::vector<InventoryViewLine> &lines, bool inventory_open,
                            int width, int height) {
    if (lines.empty() && !inventory_open) return;
    const auto fill_rectangle = [](int x, int y, int w, int h, float r, float g, float b) {
        glScissor(x, y, w, h);
        glClearColor(r, g, b, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);
    };
    glEnable(GL_SCISSOR_TEST);
    const int top_height = std::max(54, height / 12);
    fill_rectangle(0, height - top_height, width, top_height, 0.18F, 0.105F, 0.035F);
    const int status_size = std::max(12, std::min(width, height) / 45);
    fill_rectangle(status_size, height - top_height / 2 - status_size / 2, status_size,
                   status_size, 0.72F, 0.43F, 0.10F);
    // prototype: diagnostic overlay geometry/colors, not original UI metrics.
    const int scale = width >= 950 ? 2 : 1;
    const int line_height = 11 * scale;
    const int left = 24;
    int top = height - 12;
    if (inventory_open) {
        fill_rectangle(12, 12, std::max(0, width - 24), std::max(0, height - 24), 0.075F, 0.070F,
                       0.060F);
        top = height - 26;
    }
    for (const auto &line : lines) {
        if (top - line_height < 12)
            break;
        if (line.selected)
            fill_rectangle(left - 6, top - line_height + 3, std::max(0, width - 2 * left),
                           line_height, 0.28F, 0.20F, 0.08F);
        const auto columns =
            static_cast<std::size_t>(std::max(0, width - 2 * left) / (6 * scale));
        int x = left;
        for (const char c : line.text.substr(0, columns)) {
            const auto glyph = torchlight::inventory_glyph(c);
            for (int row = 0; row < 7; ++row) {
                for (int column = 0; column < 5; ++column) {
                    if (glyph[row] & (1U << (4 - column)))
                        fill_rectangle(x + column * scale, top - (row + 1) * scale, scale, scale,
                                       0.93F, 0.88F, 0.72F);
                }
            }
            x += 6 * scale;
        }
        top -= line_height;
    }
    glDisable(GL_SCISSOR_TEST);
    if (glGetError() != GL_NO_ERROR) {
        throw std::runtime_error("OpenGL ES failed while drawing the scene preview");
    }
}
} // namespace torchlight
