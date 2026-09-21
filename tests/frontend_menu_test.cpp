#include "torchlight/frontend.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace {
unsigned checks = 0;
void require(bool b, const char *s) { ++checks; if (!b) throw std::runtime_error(s); }
const FrontendButton &button(const FrontendFrame &f, const std::string &id) {
    const auto it = std::find_if(f.buttons.begin(), f.buttons.end(), [&](const auto &b) { return b.id == id; });
    if (it == f.buttons.end()) throw std::runtime_error("missing button: " + id);
    return *it;
}
const UiResolvedWidget &text(const FrontendFrame &f, const std::string &name) {
    const auto it = std::find_if(f.texts.begin(), f.texts.end(), [&](const auto &w) { return w.name == "Root/" + name; });
    if (it == f.texts.end()) throw std::runtime_error("missing text: " + name);
    return *it;
}
void click(Frontend &f, const std::string &id) {
    auto b = button(f.frame(1024,768), id);
    f.click(b.rect.x + b.rect.width/2, b.rect.y + b.rect.height/2);
}
}
int main(int argc, char **argv) {
    try {
        if (argc != 2) throw std::runtime_error("expected authored menu pak");
        PakArchive pak(argv[1]); UiResources resources(pak);
        Frontend f(resources, {{1,"Destroyer"},{2,"Vanquisher"},{3,"Alchemist"}});
        auto m = f.frame(1024,768);
        require(m.original_layout && m.title.empty(), "resource page got synthetic title");
        require(m.texts.size() == 3, "lost/duplicated static text or leaked placeholder/hidden label");
        require(text(m,"CopyrightInfo").text == "(v1.15) Torchlight (C) 2009 Runic Games Inc.",
                "controller copyright write missing");
        require(text(m,"CopyrightInfo").font == "Fixture", "resource text font lost");
        require(text(m,"TabTextB").type == "GuiLook/StaticTextOutline", "outline label dropped");
        const auto b = button(m,"new");
        require(b.text == "New resource character" && !b.supplemental, "button label replaced by port text");
        require(b.image == "set:Author image:Normal" && b.hover_image == "set:Author image:Hover" &&
                b.pushed_image == "set:Author image:Pushed" && b.disabled_image == "set:Author image:Disabled",
                "look defaults / quote parsing / direct-child scope wrong");
        require(button(m,"settings").enabled, "settings stayed a disabled control");
        const auto builds = f.frame_build_count();
        for (int i=0; i<100; ++i) static_cast<void>(f.frame(1024,768));
        require(f.frame_build_count()==builds, "unchanged menu rebuilt");
        static_cast<void>(f.frame(512,384));
        require(f.frame_build_count()==builds+1, "resize reused stale geometry");
        static_cast<void>(f.frame(1024,768));
        // Paint list is per window across all kinds, preserving one cache for
        // a widget which appears in both image and text compatibility views.
        {
            FrontendFrame mixed;
            UiResolvedWidget front, back;
            front.name="front"; front.paint_order=2; front.text="front text";
            back.name="back"; back.paint_order=0; back.text="back text";
            mixed.decorations={front}; mixed.texts={back,front};
            FrontendButton middle; middle.widget.name="middle"; middle.widget.paint_order=1;
            middle.text="live label"; middle.enabled=false;
            mixed.buttons={middle};
            const auto paint=frontend_paint_list(mixed);
            require(paint.size()==3 && paint[0].widget.name=="back" &&
                    paint[1].widget.name=="middle" && paint[2].widget.name=="front",
                    "window order split by renderer type or duplicate cache");
            require(!paint[1].widget.enabled && paint[1].widget.text=="live label",
                    "painter lost controller overrides");
        }
        click(f,"settings");
        require(f.page() == FrontendPage::settings, "settings page did not open");
        require(!f.take_request(), "settings entry dispatched a command");
        require(!button(f.frame(1024,768),"setting-FULLSCREEN").selected,
                "default fullscreen draft wrong");
        click(f,"setting-FULLSCREEN");
        require(button(f.frame(1024,768),"setting-FULLSCREEN").selected,
                "checkbox toggle lost");
        click(f,"apply");
        {
            auto r = f.take_request();
            require(r && r->command == FrontendCommand::apply_settings &&
                        r->settings.fullscreen && r->settings.show_blood,
                    "settings apply did not carry the draft");
        }
        click(f,"decline-settings");
        require(f.page() == FrontendPage::main, "settings decline did not return");
        f.key(FrontendKey::back);
        require(f.page() == FrontendPage::main, "settings back did not return");
        auto small = f.frame(512,384);
        // original-code: CMainMenu::createMenus scales mainmenuframe offsets
        // by YRATIO (convertToScreenScale call @0xc52bd5); at 512x384 the
        // nested 470px chain resolves to exactly half, 235.
        require(text(small,"CopyrightInfo").rect.x == 235.0F,
                "main menu offsets ignore YRATIO");
        click(f,"new");
        require(text(f.frame(1024,768),"CharacterName").text == "Hero", "name field not bound");
        const auto creation=f.frame(1024,768);
        require(std::none_of(creation.buttons.begin(),creation.buttons.end(),
                             [](const auto&b){return b.id=="class-1";}),
                "hidden source button resurrected as fallback");
        f.text('X');
        require(text(f.frame(1024,768),"CharacterName").text == "HeroX", "name edit not reflected");
        click(f,"class-2"); click(f,"create");
        auto r=f.take_request();
        require(r && r->class_guid == 3 && r->name == "HeroX", "creation semantics regressed");
        f.entered_game(); f.pause(); m=f.frame(1024,768);
        require(m.original_layout && m.title.empty() && text(m,"Title").text == "Options", "options layout/title missing");
        require(button(m,"resume").rect.x == 386 && button(m,"resume").text == "Return to game", "resume not mapped by guiCloseMenu");
        require(!button(m,"unsupported:Root/ExitGame").enabled, "unverified guiExitGame repurposed");
        require(button(m,"save-menu").supplemental && button(m,"save-menu").text.find("PORT:") == 0,
                ".otc action presented as original");
        click(f,"save-menu"); r=f.take_request();
        require(r && r->command == FrontendCommand::save_and_menu, "portable save action lost");
        f.error("DISK FULL");
        require(f.page() == FrontendPage::pause, "save failure left pause");
        click(f,"resume"); require(f.page() == FrontendPage::playing, "resource resume failed");
        f.show_main();
        // Rectangles from the previous page cannot be reused before a new frame.
        f.click(b.rect.x+2,b.rect.y+2);
        require(f.page()==FrontendPage::main, "external page transition retained stale buttons");
        std::vector<SaveSlotInfo> saves(7);
        for (std::size_t i=0;i<saves.size();++i) {
            saves[i].slot="slot-"+std::to_string(i); saves[i].name="Name "+std::to_string(i); saves[i].class_guid=1;
        }
        saves[2].error="damaged slot";
        f.set_saves(saves);
        require(!button(f.frame(1024,768),"continue").enabled,
                "disabled source control resurrected after saves arrived");
        click(f,"loads"); m=f.frame(1024,768);
        require(text(m,"Player1Name").text=="Name 0" && button(m,"slot-0").text.empty(), "slot label duplicated or not bound");
        require(text(m,"Player3Desc").text=="PORT SAVE: UNREADABLE", "corrupt slot warning missing");
        require(text(m,"CharacterModsWarning").text=="Resource warning", "static load warning lost");
        click(f,"slot-2"); require(!button(f.frame(1024,768),"load").enabled, "corrupt slot load enabled");
        click(f,"scroll-down"); m=f.frame(1024,768);
        require(text(m,"Player1Name").text=="Name 1" && button(m,"slot-1").text.empty(), "scroll did not rebind names");
        click(f,"slot-5"); click(f,"load"); r=f.take_request();
        require(r && r->slot=="slot-5", "load selected wrong .otc after scroll");
        std::cout << checks << " authored menu checks passed; no original pak parity claim\n";
        return 0;
    } catch(const std::exception &e) { std::cerr << e.what() << '\n'; return 1; }
}
