#include "torchlight/gles_ui_renderer.hpp"
#include <GLES2/gl2.h>
#include <algorithm>
#include <cstdio>
#include <stdexcept>
using namespace torchlight;
extern "C" int render_frontend_probe(const char *pak, int width, int height, int page,
                                     unsigned char *out, char *error, unsigned error_capacity) {
    try {
        PakArchive archive(pak);
        UiResources resources(archive);
        Frontend ui(resources, {{1, "DESTROYER"}, {2, "VANQUISHER"}, {3, "ALCHEMIST"}});
        auto frame = ui.frame(width, height);
        if (page == 1) {
            const auto i = std::find_if(frame.buttons.begin(), frame.buttons.end(),
                                        [](const auto &b) { return b.id == "new"; });
            ui.click(i->rect.x + i->rect.width / 2, i->rect.y + i->rect.height / 2);
            frame = ui.frame(width, height);
        }
        if (page == 2) {
            ui.entered_game();
            ui.pause();
            frame = ui.frame(width, height);
        }
        GlesUiRenderer renderer(archive, resources);
        renderer.draw(frame, width, height);
        glFinish();
        if (glGetError() != GL_NO_ERROR)
            throw std::runtime_error("real GLES render error");
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, out);
        if (glGetError() != GL_NO_ERROR)
            throw std::runtime_error("real GLES readback error");
        return 0;
    } catch (const std::exception &e) {
        if (error && error_capacity)
            std::snprintf(error, error_capacity, "%s", e.what());
        return 1;
    }
}
