#include "torchlight/gles_ui_renderer.hpp"
#include <GLES2/gl2.h>
#include <algorithm>
#include <cstdio>
#include <stdexcept>
using namespace torchlight;
extern "C" int render_hud_probe(const char *pak, int width, int height, float health,
                                float mana, float experience, unsigned char *out, char *error,
                                unsigned error_capacity) {
    try {
        PakArchive archive(pak);
        UiResources resources(archive);
        UiHud hud(resources);
        UiHudValues values;
        values.health_fraction = health;
        values.mana_fraction = mana;
        values.experience_fraction = experience;
        GlesUiRenderer renderer(archive, resources);
        glViewport(0, 0, width, height);
        glClearColor(.045F, .055F, .065F, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer.draw_hud(hud.frame(width, height, values), width, height);
        glFinish();
        if (glGetError() != GL_NO_ERROR)
            throw std::runtime_error("real GLES HUD render error");
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, out);
        if (glGetError() != GL_NO_ERROR)
            throw std::runtime_error("real GLES HUD readback error");
        return 0;
    } catch (const std::exception &e) {
        if (error && error_capacity)
            std::snprintf(error, error_capacity, "%s", e.what());
        return 1;
    }
}
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
        if (page == 3) {
            std::vector<SaveSlotInfo> saves(7);
            for (std::size_t n=0;n<saves.size();++n) {
                saves[n].slot="slot-"+std::to_string(n);
                saves[n].name="Name "+std::to_string(n);
                saves[n].class_guid=1;
            }
            ui.set_saves(saves);
            frame=ui.frame(width,height);
            const auto i=std::find_if(frame.buttons.begin(),frame.buttons.end(),
                                     [](const auto &b){return b.id=="loads";});
            if(i==frame.buttons.end())throw std::runtime_error("load button absent");
            ui.click(i->rect.x+i->rect.width/2,i->rect.y+i->rect.height/2);
            frame=ui.frame(width,height);
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

// Same renderer/resource objects survive all preceding steps: this catches
// first-use upload, late glyph insertion and resize invalidation, not just load.
extern "C" int render_font_sequence_probe(const char *pak, int step, unsigned char *out,
                                           char *error, unsigned error_capacity) {
    try {
        PakArchive archive(pak); UiResources resources(archive);
        auto *font = resources.font("Fixture");
        if (!font || !font->valid()) throw std::runtime_error("real FreeType test font unavailable");
        GlesUiRenderer renderer(archive, resources);
        int width=1024, height=768;
        for (int n=0;n<=step;++n) {
            width=n==3?512:1024; height=n==3?384:768;
            glViewport(0,0,width,height);
            glClearColor(.045F,.055F,.065F,1);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
            UiHudFrame frame;
            UiResolvedWidget w;
            w.font="Fixture"; w.visible=true;
            w.rect=w.clip={40,20,80,80};
            w.text=n==0?"A":n==2?"Π":"AB";
            if(n==5){w.text="A\nB";w.rect=w.clip={40,20,40,80};}
            if(n==6){w.text="B";w.clip={44,25,8,10};}
            if(n==7){w.text="A A A";w.rect=w.clip={40,20,20,80};w.properties["HorzFormatting"]="WordWrapLeftAligned";}
            frame.texts.push_back(w);
            renderer.draw_hud(frame,width,height);
        }
        glFinish();
        if(glGetError()!=GL_NO_ERROR)throw std::runtime_error("font sequence GLES draw failed");
        glReadPixels(0,0,width,height,GL_RGBA,GL_UNSIGNED_BYTE,out);
        if(glGetError()!=GL_NO_ERROR)throw std::runtime_error("font sequence GLES readback failed");
        return 0;
    }catch(const std::exception&e){
        if(error&&error_capacity) std::snprintf(error,error_capacity,"%s",e.what());
        return 1;
    }
}
