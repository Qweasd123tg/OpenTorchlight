#include "torchlight/gles_ui_renderer.hpp"
#include "torchlight/dds_texture.hpp"
#include "torchlight/png_texture.hpp"
#include <GLES2/gl2.h>
#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <map>
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
} // namespace
struct GlesUiRenderer::Impl {
    const PakArchive *archive;
    UiResources *resources;
    GLuint program = 0, buffer = 0;
    GLint screen = -1, color = -1, textured = -1, sampler = -1;
    std::map<std::string, Texture> textures;
    std::set<std::string> failed;
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
    // prototype: fallback palette, diagnostic glyphs and button chrome. The
    // resource-derived rectangles and images are not a complete CEGUI skin.
    void draw(const FrontendFrame &frame, int width, int height) {
        glViewport(0, 0, width, height);
        glDisable(GL_SCISSOR_TEST);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glClearColor(.045F, .055F, .065F, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        for (const auto &w : frame.decorations) {
            const auto image = resources->image(w.image);
            if (!image)
                continue;
            auto *texture = load(image->texture_path);
            if (!texture)
                continue;
            if (image->x + image->width > texture->width ||
                image->y + image->height > texture->height)
                continue;
            std::vector<Vertex> v;
            quad(v, w.rect,
                 {image->x / texture->width, image->y / texture->height,
                  image->width / texture->width, image->height / texture->height});
            draw_batch(v, {1, 1, 1, 1}, texture->id);
        }
        const int scale = width >= 950 ? 2 : 1;
        std::vector<Vertex> letters;
        text(letters, frame.title, 24, 20, scale, width);
        for (const auto &button : frame.buttons) {
            std::vector<Vertex> v;
            quad(v, button.rect);
            draw_batch(v, button.enabled
                              ? (button.focused ? std::array<float, 4>{.32F, .30F, .21F, .95F}
                                                : std::array<float, 4>{.12F, .15F, .17F, .95F})
                              : std::array<float, 4>{.08F, .09F, .1F, .85F});
            text(letters, (button.selected ? "[X] " : "") + button.text, button.rect.x + 8,
                 button.rect.y + (button.rect.height - 7 * scale) * .5F, scale,
                 static_cast<int>(
                     std::min(static_cast<float>(width), button.rect.x + button.rect.width)));
        }
        float y = 48.0F;
        for (const auto &line : frame.notes) {
            text(letters, line.text, 24, y, scale, width);
            y += 9 * scale;
        }
        draw_batch(letters, {.92F, .90F, .82F, 1});
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glUseProgram(0);
        glDisable(GL_BLEND);
    }
};
GlesUiRenderer::GlesUiRenderer(const PakArchive &a, UiResources &r)
    : impl_(std::make_unique<Impl>(a, r)) {
}
GlesUiRenderer::~GlesUiRenderer() = default;
void GlesUiRenderer::draw(const FrontendFrame &f, int w, int h) {
    impl_->draw(f, w, h);
}
void draw_inventory_overlay(const std::vector<InventoryViewLine>& lines,
                            bool inventory_open, int width, int height) {
    const auto fill_rectangle = [](int x, int y, int w, int h, float r, float g, float b) {
        glScissor(x, y, w, h); glClearColor(r, g, b, 1.0F); glClear(GL_COLOR_BUFFER_BIT);
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
            fill_rectangle(12, 12, std::max(0, width - 24), std::max(0, height - 24),
                           0.075F, 0.070F, 0.060F);
            top = height - 26;
        }
        for (const auto& line : lines) {
            if (top - line_height < 12) break;
            if (line.selected)
                fill_rectangle(left - 6, top - line_height + 3,
                               std::max(0, width - 2 * left), line_height,
                               0.28F, 0.20F, 0.08F);
            const auto columns = static_cast<std::size_t>(std::max(0, width - 2 * left) / (6 * scale));
            int x = left;
            for (const char c : line.text.substr(0, columns)) {
                const auto glyph = torchlight::inventory_glyph(c);
                for (int row = 0; row < 7; ++row) {
                    for (int column = 0; column < 5; ++column) {
                        if (glyph[row] & (1U << (4 - column)))
                            fill_rectangle(x + column * scale, top - (row + 1) * scale,
                                           scale, scale, 0.93F, 0.88F, 0.72F);
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
