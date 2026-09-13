#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

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
        const EGLint surface_attributes[] = {EGL_WIDTH, 16, EGL_HEIGHT, 16, EGL_NONE};
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

bool near_byte(unsigned char actual, unsigned char expected) {
    return std::abs(static_cast<int>(actual) - static_cast<int>(expected)) <= 1;
}

} // namespace

int main() {
    try {
        HeadlessContext context;
        glViewport(0, 0, 16, 16);
        glClearColor(0.25F, 0.5F, 0.75F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);
        require(glGetError() == GL_NO_ERROR, "OpenGL ES clear failed");

        std::array<unsigned char, 4> pixel{};
        glReadPixels(8, 8, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel.data());
        require(glGetError() == GL_NO_ERROR, "OpenGL ES readback failed");
        require(near_byte(pixel[0], 64) && near_byte(pixel[1], 128) &&
                    near_byte(pixel[2], 191) && pixel[3] == 255,
                "OpenGL ES framebuffer contains the wrong color");
        std::cout << "PASS: rendered and read back an EGL/OpenGL ES 2 frame\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
