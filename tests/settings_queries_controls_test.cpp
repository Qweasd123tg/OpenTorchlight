#include "torchlight/cegui_menu.hpp"
#include "torchlight/ui_int_property.hpp"
#include "torchlight/ui_dropdown.hpp"
#include <CEGUI.h>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace torchlight;
namespace {
void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}
CEGUI::Window* window(const char* name) {
    return CEGUI::WindowManager::getSingleton().getWindow(std::string("__cegui/settings/") + name);
}
bool selected(const char* name) {
    return static_cast<CEGUI::Checkbox*>(window(name))->isSelected();
}
unsigned row(const char* name) {
    auto* item = static_cast<CEGUI::Combobox*>(window(name))->getSelectedItem();
    if (!item) throw std::runtime_error("settings combo has no selected item");
    return item->getID();
}
unsigned observed_subscribers = 0;
bool default_result(const CEGUI::EventArgs&) { return dropdown_default_double_click(); }
bool following_subscriber(const CEGUI::EventArgs& args) {
    require(args.handled, "generated default did not set the library handled flag");
    ++observed_subscribers;
    return false;
}
}
int main(int argc, char** argv) { try {
    require(argc == 2, "expected external pak.zip");
    PakArchive archive(argv[1]);
    CeguiMenu menu(archive, [](CeguiPage, const std::string&, UiLayoutFunction) {
        throw std::runtime_error("property population unexpectedly emitted an input command");
    });
    CEGUI::Event event("OriginalDropdownDefaultContract");
    event.subscribe(0, CEGUI::Event::Subscriber(&default_result));
    event.subscribe(1, CEGUI::Event::Subscriber(&following_subscriber));
    CEGUI::EventArgs args;
    event(args);
    require(args.handled && observed_subscribers == 1,
            "library handled accumulation stopped the remaining subscribers");
    const std::vector<UiResolution> modes{{1024, 768}, {800, 600}, {1280, 720}};
    DisplaySettings value;
    value.fullscreen = true;
    value.fsaa = 7; // Original TEST/SETNE accepts every nonzero int, not just 1.
    value.vsync = false;
    value.shadows_detail = 5;
    value.res_width = 1280;
    value.res_height = 720;
    menu.settings_state(true, value, modes);
    require(selected("Fullscreen") && selected("Antialiasing") && !selected("VSync"),
            "generated int values did not reach native checkboxes");
    require(row("ShadowDropdown") == 5 && row("ResolutionDropdown") == 2,
            "generated int values did not reach native combo selection");
    const auto result = menu.settings_values(value);
    require(result.fullscreen && result.fsaa == 1 && !result.vsync && result.shadows_detail == 5 &&
            result.res_width == 1280 && result.res_height == 720,
            "native settings readback lost generated values");
    menu.settings_state(false, value, modes);
    value.fullscreen = false;
    value.fsaa = 0;
    value.vsync = true;
    value.shadows_detail = -1;
    value.res_width = 333;
    value.res_height = 222;
    menu.settings_state(true, value, modes);
    require(!selected("Fullscreen") && !selected("Antialiasing") && selected("VSync"),
            "reopen reused the preceding evaluated int table");
    require(row("ShadowDropdown") == 0 && row("ResolutionDropdown") == 0,
            "unmatched integers lost the existing default-row policy");
    menu.settings_state(false, value, modes);
    value.fsaa = std::numeric_limits<std::int32_t>::min();
    value.shadows_detail = 6;
    value.res_width = 800;
    value.res_height = 600;
    menu.settings_state(true, value, modes);
    require(selected("Antialiasing") && row("ShadowDropdown") == 0 && row("ResolutionDropdown") == 1,
            "int32 sign/nonzero or resolution matching changed");
    require(ui_int_property(nullptr, 0, UINT32_MAX) == -1, "empty borrowed view lost original fallback");
    bool null_rejected = false;
    try { static_cast<void>(ui_int_property(nullptr, 1, 0)); }
    catch (const std::invalid_argument&) { null_rejected = true; }
    require(null_rejected, "invalid borrowed owner reached the generated reader");
    std::cout << "PASS generated settings controls/readback and library default-result consumer; no input, frame or GL\n";
    return 0;
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }
