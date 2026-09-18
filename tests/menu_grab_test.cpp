// Tests for the generated grab-only createMenus tables.
// original-code: dialog/die/fishing/interactive/modal/options/settings/
// continue/difficulty/mainmenu/newgame/tip/cinematic/waypoint createMenus
// (machine code of the pinned ELF, transcribed by
// tools/gen_menu_profiles.py --grab-only from batch extractor output).
#include "torchlight/menu_grab_tables.hpp"

#include <cstdio>
#include <string>
#include <vector>

namespace {
int failures = 0;
int assertions = 0;
void require(bool cond, const char* what) {
    ++assertions;
    if (!cond) {
        ++failures;
        std::printf("FAIL: %s\n", what);
    }
}
const torchlight::MenuGrabTable* find(
    const std::vector<torchlight::MenuGrabTable>& ts, const char* cls) {
    for (const auto& t : ts)
        if (std::string(t.menu_class) == cls)
            return &t;
    return nullptr;
}
bool has_grab(const torchlight::MenuGrabTable& t, const char* key,
              const char* field) {
    for (const auto& g : t.grabs)
        if (std::string(g.key) == key && std::string(g.menu_field) == field)
            return true;
    return false;
}
} // namespace

int main() {
    using namespace torchlight;
    auto tables = menu_grab_tables();
    require(tables.size() == 14, "fourteen grab-only tables");

    const auto* settings = find(tables, "CSettingsMenu");
    require(settings && settings->grabs.size() == 18, "settings 18 grabs");
    require(has_grab(*settings, "ShowTips", "0x130"), "settings ShowTips");
    require(has_grab(*settings, "ResolutionDropdown", "0xf8"),
            "settings ResolutionDropdown");
    require(has_grab(*settings, "MusicVolume", "0x110"), "settings MusicVolume");

    const auto* cont = find(tables, "CContinueGameMenu");
    require(cont && cont->grabs.size() == 27, "continue 27 grabs");
    {
        bool p3 = false, del = false;
        for (const auto& g : cont->grabs) {
            if (std::string(g.key) == "Player3Name")
                p3 = true;
            if (std::string(g.key) == "DeleteConfirm")
                del = true;
        }
        require(p3 && del, "continue Player3/DeleteConfirm");
    }

    const auto* modal = find(tables, "CModalMenu");
    require(modal && modal->grabs.size() == 5, "modal 5 grabs");
    require(has_grab(*modal, "Dialog", "0xe0"), "modal Dialog");

    const auto* die = find(tables, "CDieMenu");
    require(die && die->grabs.size() == 7, "die 7 grabs");

    const auto* wp = find(tables, "CWaypointMenu");
    require(wp && wp->grabs.size() == 3, "waypoint 3 grabs");
    require(has_grab(*wp, "dynamic:Button+GetValueAsString(counter)", "0xc8"),
            "waypoint Button+N");
    require(has_grab(*wp, "dynamic:Choice+GetValueAsString(counter)", "0x258"),
            "waypoint Choice+N");

    const auto* fish = find(tables, "CFishingMenu");
    const auto* inter = find(tables, "CInteractiveMenu");
    require(fish && fish->grabs.empty(), "fishing: pipeline only, no grabs");
    require(inter && inter->grabs.empty(), "interactive: no grabs yet");

    const auto* ng = find(tables, "CNewGameMenu");
    require(has_grab(*ng, "EditBoxPet", "0xd8") && ng->grabs.size() == 6,
            "newgame 6 grabs");

    const auto* cine = find(tables, "CCinematicMenu");
    require(has_grab(*cine, "Skip", "0xc0") && cine->grabs.size() == 3,
            "cinematic 3 grabs");

    if (failures == 0)
        std::printf("menu_grab: %d assertions; 14 grab-only tables\n",
                    assertions);
    return failures == 0 ? 0 : 1;
}
