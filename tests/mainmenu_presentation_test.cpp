#include "torchlight/frontend.hpp"
#include <CEGUI.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace {
void require(bool v, const char* m) { if (!v) throw std::runtime_error(m); }
const UiResolvedWidget& widget(const FrontendFrame& f, const std::string& name) {
    require(f.cegui.has_value(), "production main menu did not use CEGUI");
    const auto& ws = f.cegui->widgets;
    const auto it = std::find_if(ws.begin(), ws.end(), [&](const auto& w) { return w.name == name; });
    require(it != ws.end(), "native menu window missing");
    return *it;
}
void inspect(const FrontendFrame& f) {
    require(f.original_layout && f.notes.empty(), "diagnostic chrome in native menu");
    require(f.cegui && !f.cegui->quads.empty(), "CEGUI produced no imagery");
    require(frontend_paint_list(f).empty(), "custom Falagard compiler still paints the native menu");
    for (const auto& q : f.cegui->quads) {
        require(q.texture && q.texture->width && q.texture->height, "library quad has no texture");
        require(q.texture->rgba.size() == static_cast<std::size_t>(q.texture->width) * q.texture->height * 4,
            "invalid atlas transport");
        require(std::isfinite(q.z) && std::isfinite(q.destination.x) && std::isfinite(q.destination.y) &&
            q.destination.width > 0 && q.destination.height > 0, "invalid clipped quad");
    }
}
void command(Frontend& ui, const std::string& id) {
    const auto f = ui.frame(1024, 768);
    const auto it = std::find_if(f.buttons.begin(), f.buttons.end(), [&](const auto& b) { return b.id == id; });
    require(it != f.buttons.end(), "bound command missing");
    const float x = it->rect.x + it->rect.width / 2, y = it->rect.y + it->rect.height / 2;
    ui.pointer_event({UiPointerEventKind::button_down, x, y});
    ui.pointer_event({UiPointerEventKind::button_up, x, y});
}
}
// Library/state/resource contract: no window, GL context or desktop input.
int main(int argc, char** argv) { try {
    if (argc == 3 && std::string(argv[1]) == "--invalid") {
        PakArchive broken(argv[2]);
        bool caught = false;
        try { CeguiMenu menu(broken, [](auto, const auto&, auto) {}); }
        catch (const std::runtime_error& e) { caught = std::string(e.what()).find("CEGUI:") == 0; }
        require(caught, "non-std library exception escaped the production boundary");
        require(!CEGUI::System::getSingletonPtr(), "failed resource load leaked System");
        std::cout << "PASS: CEGUI load failure translated and library owners released\n";
        return 0;
    }
    require(argc == 2, "expected external pak.zip");
    PakArchive pak(argv[1]);
    std::shared_ptr<const CeguiTextureData> retained;
    {
        UiResources resources(pak); Frontend ui(resources, {{1, "Destroyer"}});
        auto f = ui.frame(1024, 768); inspect(f);
        const auto target = std::find_if(f.buttons.begin(), f.buttons.end(), [](const auto& b) { return b.id == "new"; });
        require(target != f.buttons.end(), "new-game binding missing");
        const float tx = target->rect.x + target->rect.width / 2, ty = target->rect.y + target->rect.height / 2;
        for (std::uint8_t button : {std::uint8_t{1}, std::uint8_t{2}}) {
            ui.pointer_event({UiPointerEventKind::button_down, tx, ty, button});
            ui.pointer_event({UiPointerEventKind::button_up, tx, ty, button});
            require(ui.page() == FrontendPage::main, "non-left button executed a game command");
        }
        bool rejected = false;
        try { ui.pointer_event({UiPointerEventKind::button_down, tx, ty, 7}); }
        catch (const std::invalid_argument&) { rejected = true; }
        require(rejected && ui.page() == FrontendPage::main, "invalid button corrupted native routing");
        retained = f.cegui->quads.front().texture;
        for (const auto* name : {"DemoVersion", "CharacterModsWarning", "ContinueLast", "CreditFrame", "CreditFrameB"})
            require(!widget(f, name).visible, "initial controller visibility wrong");
        require(widget(f, "TabB").visible && widget(f, "TabTextB").visible, "Linux credit tab missing");
        const auto* layout = resources.layout("media/UI/mainmenuframe.layout");
        require(layout != nullptr, "resource oracle missing");
        const auto source = std::find_if(layout->widgets().begin(), layout->widgets().end(),
            [](const auto& w) { return w.name == "CreditsB"; });
        if (source != layout->widgets().end() && widget(f, "CreditsB").text != source->property("Text")) {
            const auto& native = widget(f, "CreditsB").text;
            const auto expected = source->property("Text");
            const auto pos = std::mismatch(native.begin(), native.end(), expected.begin(), expected.end());
            std::cerr << "Property body lengths " << native.size() << '/' << expected.size()
                      << " first mismatch at " << (pos.first - native.begin()) << '\n';
        }
        require(source != layout->widgets().end() && widget(f, "CreditsB").text == source->property("Text"),
            "XML Property body whitespace/entities changed");
        auto* serif = CEGUI::FontManager::getSingleton().getFont("Serif");
        require(serif->getTextExtent("|cFFFFBA00ABC|u") == serif->getTextExtent("ABC"), "tag advance wrong");
        require(serif->getTextExtent("|cGGGGGGGGABC|u") == serif->getTextExtent("ABC"), "malformed full tag not consumed");
        require(serif->getTextExtent("|cFF") > 0, "incomplete tag should stay literal");
        auto* plain = CEGUI::FontManager::getSingleton().getFont("FrizQuadrata");
        require(plain->getTextExtent("|cFFFFBA00ABC|u") > plain->getTextExtent("ABC"), "tag patch leaked to other fonts");
        static_cast<void>(ui.frame(1024, 768));
        const auto count = ui.frame_build_count(); static_cast<void>(ui.frame(1024, 768));
        require(ui.frame_build_count() == count, "idle transport rebuilt");
        SaveSlotInfo save; save.slot = "probe"; save.class_guid = 1; ui.set_saves({save});
        require(widget(ui.frame(1024, 768), "ContinueLast").visible, "save adapter not consumed");
        save.error = "unreadable"; ui.set_saves({save});
        require(!widget(ui.frame(1024, 768), "ContinueLast").visible, "bad save left Continue visible");
        for (const auto& c : {std::array<const char*, 4>{"credits-a", "credits-b", "CreditFrame", "Credits"},
                              std::array<const char*, 4>{"credits-c", "credits-d", "CreditFrameB", "CreditsB"}}) {
            command(ui, c[0]); f = ui.frame(1024, 768); inspect(f);
            require(widget(f, c[2]).visible && widget(f, c[3]).visible, "command/child visibility chain broken");
            require(widget(f, c[3]).text.find(std::string(c[3]) == "CreditsB" ? "OutOfOrder Games" : "Designed by Runic Games")
                != std::string::npos, "credit body missing");
            command(ui, c[1]); require(!widget(ui.frame(1024, 768), c[2]).visible, "credit close lost");
        }
        f = ui.frame(640, 480); inspect(f); const auto small = widget(f, "TabB").rect;
        static_cast<void>(ui.frame(1024, 768)); f = ui.frame(640, 480);
        require(widget(f, "TabB").rect.x == small.x && widget(f, "TabB").rect.width == small.width,
            "resize compounded original offsets");
        command(ui, "settings"); require(ui.page() == FrontendPage::settings, "application command not consumed");
        f = ui.frame(1024, 768);
        require(f.cegui && frontend_paint_list(f).empty(), "Settings used legacy skin compilation");
        ui.key(FrontendKey::back); command(ui, "new");
        require(ui.page() == FrontendPage::create && !ui.frame(1024, 768).cegui, "native detach/new-game dispatch failed");
        ui.key(FrontendKey::back); require(ui.frame(1024, 768).cegui.has_value(), "retained native tree failed to reopen");
    }
    require(!CEGUI::System::getSingletonPtr(), "System leaked after frontend teardown");
    require(retained && !retained->rgba.empty(), "submitted texture died after library teardown");
    { UiResources r(pak); Frontend ui(r, {{1, "Destroyer"}}); inspect(ui.frame(1024, 768)); }
    std::cout << "PASS: original menu through pinned CEGUI windows/events/Falagard/fonts, controller, resize and teardown; no GL\n";
    return 0;
} catch (const CEGUI::Exception& e) { std::cerr << e.getMessage().c_str() << '\n'; return 1;
} catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; } }
