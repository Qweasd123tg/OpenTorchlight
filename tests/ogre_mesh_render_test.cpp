#include "torchlight/ogre_mesh.hpp"
#include "torchlight/pak_archive.hpp"

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

constexpr int kWidth = 96;
constexpr int kHeight = 96;

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

class HeadlessContext {
public:
    HeadlessContext() {
        display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        require(display_ != EGL_NO_DISPLAY, "eglGetDisplay failed");
        require(eglInitialize(display_, nullptr, nullptr) == EGL_TRUE, "eglInitialize failed");
        require(eglBindAPI(EGL_OPENGL_ES_API) == EGL_TRUE, "eglBindAPI failed");
        const EGLint config_attributes[] = {
            EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_NONE,
        };
        EGLConfig config = nullptr;
        EGLint count = 0;
        require(eglChooseConfig(display_, config_attributes, &config, 1, &count) == EGL_TRUE &&
                    count == 1,
                "eglChooseConfig failed");
        const EGLint surface_attributes[] = {
            EGL_WIDTH, kWidth,
            EGL_HEIGHT, kHeight,
            EGL_NONE,
        };
        surface_ = eglCreatePbufferSurface(display_, config, surface_attributes);
        require(surface_ != EGL_NO_SURFACE, "eglCreatePbufferSurface failed");
        const EGLint context_attributes[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        context_ = eglCreateContext(display_, config, EGL_NO_CONTEXT, context_attributes);
        require(context_ != EGL_NO_CONTEXT, "eglCreateContext failed");
        require(eglMakeCurrent(display_, surface_, surface_, context_) == EGL_TRUE,
                "eglMakeCurrent failed");
    }

    HeadlessContext(const HeadlessContext&) = delete;
    HeadlessContext& operator=(const HeadlessContext&) = delete;

    ~HeadlessContext() {
        if (display_ != EGL_NO_DISPLAY) {
            eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (context_ != EGL_NO_CONTEXT) {
                eglDestroyContext(display_, context_);
            }
            if (surface_ != EGL_NO_SURFACE) {
                eglDestroySurface(display_, surface_);
            }
            eglTerminate(display_);
        }
    }

private:
    EGLDisplay display_ = EGL_NO_DISPLAY;
    EGLSurface surface_ = EGL_NO_SURFACE;
    EGLContext context_ = EGL_NO_CONTEXT;
};

GLuint compile_shader(GLenum type, const char* source) {
    const auto shader = glCreateShader(type);
    require(shader != 0, "glCreateShader failed");
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE) {
        glDeleteShader(shader);
        throw std::runtime_error("OpenGL ES shader compilation failed");
    }
    return shader;
}

GLuint create_program() {
    constexpr const char* vertex_source =
        "attribute vec2 position;"
        "void main() { gl_Position = vec4(position, 0.0, 1.0); }";
    constexpr const char* fragment_source =
        "precision mediump float;"
        "void main() { gl_FragColor = vec4(0.82, 0.49, 0.12, 1.0); }";
    const auto vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
    const auto fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
    const auto program = glCreateProgram();
    require(program != 0, "glCreateProgram failed");
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glBindAttribLocation(program, 0, "position");
    glLinkProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    GLint linked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE) {
        glDeleteProgram(program);
        throw std::runtime_error("OpenGL ES program link failed");
    }
    return program;
}

const torchlight::OgreGeometry& geometry_for(const torchlight::OgreMesh& mesh,
                                             const torchlight::OgreSubmesh& submesh) {
    if (submesh.uses_shared_vertices) {
        require(mesh.shared_geometry.has_value(), "submesh has no shared geometry");
        return *mesh.shared_geometry;
    }
    require(submesh.geometry.has_value(), "submesh has no local geometry");
    return *submesh.geometry;
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: ogre_mesh_render_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const auto mesh = torchlight::parse_ogre_mesh(archive.read_normalized(
            "media/levelsets/town1/building_bank.mesh"));
        require(!mesh.submeshes.empty(), "bank mesh has no submeshes");

        float minimum_x = std::numeric_limits<float>::max();
        float maximum_x = std::numeric_limits<float>::lowest();
        float minimum_z = std::numeric_limits<float>::max();
        float maximum_z = std::numeric_limits<float>::lowest();
        for (const auto& submesh : mesh.submeshes) {
            const auto& geometry = geometry_for(mesh, submesh);
            for (const auto& position : geometry.positions) {
                minimum_x = std::min(minimum_x, position[0]);
                maximum_x = std::max(maximum_x, position[0]);
                minimum_z = std::min(minimum_z, position[2]);
                maximum_z = std::max(maximum_z, position[2]);
            }
        }
        require(minimum_x < maximum_x && minimum_z < maximum_z,
                "bank mesh has degenerate XZ bounds");
        const float center_x = (minimum_x + maximum_x) * 0.5F;
        const float center_z = (minimum_z + maximum_z) * 0.5F;
        const float scale = 1.8F / std::max(maximum_x - minimum_x, maximum_z - minimum_z);

        HeadlessContext context;
        const auto program = create_program();
        glUseProgram(program);
        glViewport(0, 0, kWidth, kHeight);
        glClearColor(0.035F, 0.043F, 0.031F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(0);

        std::size_t drawn_triangles = 0;
        for (const auto& submesh : mesh.submeshes) {
            if (submesh.operation_type != 4 || submesh.indices.empty()) {
                continue;
            }
            const auto& geometry = geometry_for(mesh, submesh);
            std::vector<float> positions;
            positions.reserve(geometry.positions.size() * 2U);
            for (const auto& position : geometry.positions) {
                positions.push_back((position[0] - center_x) * scale);
                positions.push_back((position[2] - center_z) * scale);
            }
            std::vector<std::uint16_t> indices;
            indices.reserve(submesh.indices.size());
            for (const auto index : submesh.indices) {
                require(index <= std::numeric_limits<std::uint16_t>::max(),
                        "bank mesh requires 32-bit GLES indices");
                indices.push_back(static_cast<std::uint16_t>(index));
            }
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, positions.data());
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_SHORT,
                           indices.data());
            drawn_triangles += indices.size() / 3U;
        }
        glDisableVertexAttribArray(0);
        glDeleteProgram(program);
        require(glGetError() == GL_NO_ERROR, "OpenGL ES mesh draw failed");
        require(drawn_triangles > 0, "bank mesh drew no triangles");

        std::array<std::uint8_t, kWidth * kHeight * 4> pixels{};
        glReadPixels(0, 0, kWidth, kHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        require(glGetError() == GL_NO_ERROR, "OpenGL ES mesh readback failed");
        std::size_t colored_pixels = 0;
        for (std::size_t offset = 0; offset < pixels.size(); offset += 4U) {
            if (pixels[offset] > 100U && pixels[offset + 1] > 50U) {
                ++colored_pixels;
            }
        }
        require(colored_pixels > 100, "rendered OGRE mesh produced no visible geometry");
        std::cout << "PASS: rendered original building_bank OGRE geometry, triangles="
                  << drawn_triangles << " colored_pixels=" << colored_pixels << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
