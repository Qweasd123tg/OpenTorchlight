#include "torchlight/frontend.hpp"
#include "torchlight/ui_skin.hpp"
#include <CEGUI.h>
#include <falagard/CEGUIFalWidgetLookManager.h>
#include <falagard/CEGUIFalWidgetLookFeel.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace torchlight;
namespace {
void require(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
CEGUI::Window* window(const std::string& page, const std::string& name) {
    return CEGUI::WindowManager::getSingleton().getWindow("__cegui/" + page + "/" + name);
}
void event(Frontend& ui, UiPointerEventKind kind, CEGUI::Window* w) {
    const auto r = w->getUnclippedPixelRect();
    ui.pointer_event({kind, (r.d_left + r.d_right) / 2, (r.d_top + r.d_bottom) / 2});
}
void click(Frontend& ui, CEGUI::Window* w) {
    event(ui, UiPointerEventKind::button_down, w);
    event(ui, UiPointerEventKind::button_up, w);
}
void command(Frontend& ui, const std::string& id) {
    const auto f = ui.frame(1024, 768);
    const auto it = std::find_if(f.buttons.begin(), f.buttons.end(), [&](const auto& b) {
        return b.id == id && b.owner == ui.page();
    });
    require(it != f.buttons.end(), "native command absent");
    const auto r = it->rect;
    ui.pointer_event({UiPointerEventKind::button_down, r.x + r.width / 2, r.y + r.height / 2});
    ui.pointer_event({UiPointerEventKind::button_up, r.x + r.width / 2, r.y + r.height / 2});
}
CEGUI::Combobox* combo(const char* name) { return static_cast<CEGUI::Combobox*>(window("settings", name)); }
void choose(Frontend& ui, CEGUI::Combobox* c, std::size_t row) {
    click(ui, c->getPushButton());
    require(CEGUI::Window::getCaptureWindow() == c->getDropList(), "native popup did not capture");
    const auto& look = CEGUI::WidgetLookManager::getSingleton().getWidgetLook(c->getDropList()->getLookNFeel());
    const auto area = look.getNamedArea("ItemRenderingArea").getArea().getPixelRect(*c->getDropList());
    const auto position = c->getDropList()->getUnclippedPixelRect().getPosition();
    float y = position.d_y + area.d_top;
    for (std::size_t n = 0; n < row; ++n) y += c->getListboxItemFromIndex(n)->getPixelSize().d_height;
    y += c->getListboxItemFromIndex(row)->getPixelSize().d_height / 2;
    const float x = position.d_x + (area.d_left + area.d_right) / 2;
    ui.pointer_event({UiPointerEventKind::move, x, y});
    ui.pointer_event({UiPointerEventKind::button_down, x, y});
    ui.pointer_event({UiPointerEventKind::button_up, x, y});
    require(!CEGUI::Window::getCaptureWindow() && !c->getDropList()->isVisible(false), "accepted popup retained capture");
    require(c->getSelectedItem()->getID() == row, "native popup selected wrong ID");
}
}
int main(int argc, char** argv) { try {
    require(argc == 2, "expected external pak.zip");
    PakArchive pak(argv[1]); UiResources resources(pak); Frontend ui(resources, {{1, "Destroyer"}});
    DisplaySettings settings; settings.res_width = 1024; settings.res_height = 768;
    settings.music_volume = .4F; settings.sound_volume = .6F; settings.fsaa = 0;
    ui.sync_settings(settings); ui.set_resolutions({{1024, 768}, {1280, 720}});
    command(ui, "settings");
    const auto f = ui.frame(1024, 768);
    require(f.cegui && frontend_paint_list(f).empty(), "Settings has a second custom painter");
    require(window("settings", "root")->getParent() == window("main", "root")->getParent(), "Settings/Main sheet ownership differs");
    require(window("settings", "Frame")->getParent() == window("settings", "content"), "Settings bypassed content");
    require(window("settings", "Title")->getText() == "Settings", "original constructor title was lost");
    require(!window("settings", "HardwareSkinning")->isVisible(false), "bd8027 hidden checkbox became visible");
    static_cast<void>(ui.frame(640, 480));
    const auto small = window("settings", "Fullscreen")->getArea();
    static_cast<void>(ui.frame(1024, 768));
    static_cast<void>(ui.frame(640, 480));
    const auto repeated = window("settings", "Fullscreen")->getArea();
    require(repeated.d_min.d_x.d_offset == small.d_min.d_x.d_offset &&
        repeated.d_min.d_y.d_offset == small.d_min.d_y.d_offset &&
        repeated.d_max.d_x.d_offset == small.d_max.d_x.d_offset &&
        repeated.d_max.d_y.d_offset == small.d_max.d_y.d_offset,
        "native resize compounded source position/size offsets");
    static_cast<void>(ui.frame(1024, 768));
    auto* blood = static_cast<CEGUI::Checkbox*>(window("settings", "ShowBlood"));
    event(ui, UiPointerEventKind::button_down, blood);
    require(blood->isSelected(), "checkbox toggled before its native release");
    event(ui, UiPointerEventKind::button_up, blood);
    require(!blood->isSelected() && !ui.audio_settings().show_blood, "native checkbox state has no draft consumer");
    click(ui, window("settings", "Antialiasing"));
    require(ui.audio_settings().fsaa == 1, "ASM bool FSAA mapping lost");
    choose(ui, combo("ShadowDropdown"), 5);
    require(ui.audio_settings().shadows_detail == 5 && ui.audio_settings().shadow_resolution == 1024,
        "shadow ID table has no consumer");
    const char* expected[] = {"Off", "Lighting Only", "Low", "Medium", "High", "Very High"};
    for (std::size_t n = 0; n < 6; ++n)
        require(combo("ShadowDropdown")->getListboxItemFromIndex(n)->getText() == expected[n], "original constructor text differs");
    auto* shadow = combo("ShadowDropdown");
    click(ui, shadow->getPushButton());
    require(CEGUI::Window::getCaptureWindow() == shadow->getDropList(), "popup lost capture before dismissal");
    ui.pointer_event({UiPointerEventKind::button_down, 1, 1});
    ui.pointer_event({UiPointerEventKind::button_up, 1, 1});
    require(!CEGUI::Window::getCaptureWindow() && shadow->getSelectedItem()->getID() == 5,
        "dismissed popup lost accepted selection");
    choose(ui, combo("ParticleDropdown"), 2);
    require(ui.audio_settings().particle_fps == 40 && ui.audio_settings().particle_percent == 100, "particle table differs");
    auto* music = static_cast<CEGUI::Slider*>(window("settings", "MusicVolume"));
    auto* thumb = music->getThumb();
    event(ui, UiPointerEventKind::button_down, thumb);
    require(CEGUI::Window::getCaptureWindow() == thumb, "native slider did not capture thumb");
    ui.pointer_event({UiPointerEventKind::move, 10000, thumb->getUnclippedPixelRect().d_top + 2});
    require(ui.audio_settings().music_volume == 1, "live slider has no audio consumer");
    ui.pointer_event({UiPointerEventKind::button_up, 10000, 100});
    require(!CEGUI::Window::getCaptureWindow(), "slider release outside retained capture");
    command(ui, "decline-settings");
    require(ui.page() == FrontendPage::main && ui.audio_settings().music_volume == .4F && ui.audio_settings().show_blood,
        "Cancel did not restore saved values");
    require(!ui.take_request(), "Cancel queued persistence");
    command(ui, "settings");
    click(ui, window("settings", "NetbookMode"));
    command(ui, "apply");
    require(ui.page() == FrontendPage::main, "accepted original command did not close Settings");
    const auto request = ui.take_request();
    require(request && request->command == FrontendCommand::apply_settings, "Apply has no persistence consumer");
    const auto& applied = request->settings;
    require(applied.netbook_mode && applied.fsaa == 0 && !applied.rimlights && !applied.render_behind &&
        applied.shadows_detail == 0 && applied.shadow_resolution == 128 && !applied.shadows_enabled && !applied.lighting_enabled &&
        applied.particle_fps == 20 && applied.particle_percent == 10, "ASM netbook override differs");
    ui.applied();
    ui.entered_game(); ui.pause(); ui.advance(1);
    auto options = ui.frame(1024, 768);
    require(options.cegui && !options.dropdown_meshes.empty(), "Options animation/model consumer missing");
    require(window("options", "Frame")->getParent() == window("options", "content"), "Options bypassed animated content");
    require(window("options", "root")->getParent() != window("settings", "root")->getParent(), "Options lost ingame sheet");
    command(ui, "settings");
    require(ui.page() == FrontendPage::settings && ui.has_closing_windows(), "Options did not retain close during Settings");
    ui.advance(1);
    require(!window("options", "root")->getParent(), "completed Options close retained root");
    command(ui, "decline-settings"); ui.advance(1); static_cast<void>(ui.frame(1024, 768));
    command(ui, "resume");
    require(ui.page() == FrontendPage::playing && ui.has_closing_windows(), "ReturnToGame lost animated close");
    ui.advance(1);
    require(!ui.has_closing_windows() && !ui.take_request(), "ordinary Options close requested exit");
    ui.pause(); ui.advance(1); static_cast<void>(ui.frame(1024, 768)); command(ui, "exit-game");
    require(!ui.take_request(), "ExitToTitle bypassed original CLOSE gate");
    ui.advance(1); require(ui.take_request()->command == FrontendCommand::save_and_menu, "closed Options exit has no app consumer");
    std::cout << "PASS: native settings controls/capture/value consumers, Apply/Cancel and Options animation lifecycle; no GL\n";
    return 0;
} catch (const CEGUI::Exception& e) { std::cerr << e.getMessage().c_str() << '\n'; return 1;
} catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; } }
