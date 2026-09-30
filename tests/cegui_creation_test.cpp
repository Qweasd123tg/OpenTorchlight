#include "torchlight/frontend.hpp"
#include "torchlight/application_keys.hpp"
#include <CEGUI.h>
#include <algorithm>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace {
void require(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
CEGUI::Window* window(const char* name) { return CEGUI::WindowManager::getSingleton().getWindow(std::string("__cegui/create/") + name); }
CEGUI::Editbox* edit(const char* name) { return static_cast<CEGUI::Editbox*>(window(name)); }
void key(Frontend& ui, std::uint32_t value) {
    ui.keyboard_event({UiKeyboardEventKind::key_down, value, {}});
    ui.keyboard_event({UiKeyboardEventKind::key_up, value, {}});
}
void text(Frontend& ui, const std::string& value) { ui.keyboard_event({UiKeyboardEventKind::text, 0, value}); }
void click(Frontend& ui, CEGUI::Window* target) {
    const auto r = target->getUnclippedPixelRect();
    ui.pointer_event({UiPointerEventKind::button_down, (r.d_left+r.d_right)/2, (r.d_top+r.d_bottom)/2});
    ui.pointer_event({UiPointerEventKind::button_up, (r.d_left+r.d_right)/2, (r.d_top+r.d_bottom)/2});
}
void open(Frontend& ui) {
    const auto f = ui.frame(1024, 768);
    const auto it = std::find_if(f.buttons.begin(), f.buttons.end(), [](const auto& b) { return b.id == "new"; });
    require(it != f.buttons.end(), "original New command absent");
    const auto r = it->rect;
    ui.pointer_event({UiPointerEventKind::button_down, r.x+r.width/2, r.y+r.height/2});
    ui.pointer_event({UiPointerEventKind::button_up, r.x+r.width/2, r.y+r.height/2});
    static_cast<void>(ui.frame(1024, 768));
}
void select_all(Frontend& ui) {
    key(ui, physical_key::END);
    ui.keyboard_event({UiKeyboardEventKind::key_down, 42, {}}); // LeftShift, library scan 0x2a
    key(ui, physical_key::HOME);
    ui.keyboard_event({UiKeyboardEventKind::key_up, 42, {}});
}
}
int main(int argc, char** argv) { try {
    require(argc == 2, "expected external pak.zip");
    PakArchive pak(argv[1]); UiResources resources(pak);
    Frontend ui(resources, {{11,"Vanquisher","Vanquisher description","Vanquisher"},
        {12,"Alchemist","Alchemist description É","Alchimiste Érudit"}, {13,"Destroyer","Destroyer description","Destroyer"}});
    open(ui);
    require(ui.page() == FrontendPage::create && ui.character_name().empty(), "setOpen did not clear original name");
    require(edit("EditBox")->hasInputFocus(), "setOpen did not activate original Editbox");
    require(edit("EditBoxPet")->getText() == "Spot", "original ff3168 pet name differs");
    require(!window("CreatePlayer")->isVisible(false), "empty name did not hide OK");
    require(window("CharacterClass")->getText() == "Destroyer", "original default class was replaced by catalog order");
    require(ui.frame(1024,768).cegui && frontend_paint_list(ui.frame(1024,768)).empty(), "create uses a duplicate custom painter");
    auto* font = edit("EditBox")->getFont();
    require(font->isCodepointAvailable(0xe9), "external edit font lacks the test glyph");
    require(font->getCharAtPixel(CEGUI::String("|cFFFF0000ABC"), std::size_t{0}, 0.0F, 1.0F) == 0, "unreviewed colour-tag caret adaptation survived");
    require(font->isCodepointAvailable('|') && font->getCharAtPixel(CEGUI::String("|cFFFF0000ABC"), std::size_t{0}, .001F, 1.0F) == 0,
        "shipped literal-glyph caret contract differs");
    text(ui, "ééééééééééééé");
    require(edit("EditBox")->getText().length() == 12, "resource UTF-32 name limit became byte count");
    require(ui.character_name() == "éééééééééééé", "native UTF-8 name has no controller consumer");
    select_all(ui);
    require(edit("EditBox")->getSelectionLength() == 12, "stock Shift/Home selection was bypassed");
    text(ui, "Éclair");
    require(ui.character_name() == "Éclair", "replacement did not consume native selection");
    key(ui, physical_key::HOME); text(ui, "X");
    require(ui.character_name() == "XÉclair", "native caret insertion was replaced by append");
    key(ui, physical_key::HOME); key(ui, physical_key::DELETE);
    require(ui.character_name() == "Éclair", "native Delete mapping differs");
    key(ui, physical_key::END); key(ui, physical_key::BACKSPACE);
    require(ui.character_name() == "Éclai", "Backspace did not use UTF-32 caret");
    click(ui, window("Alchemist"));
    require(edit("EditBox")->hasInputFocus() && ui.character_name() == "Éclai", "class selection lost original editor activation/name");
    require(window("CharacterClass")->getText() == CEGUI::String(reinterpret_cast<const CEGUI::utf8*>("Alchimiste Érudit")) &&
        window("CharacterClassDescription")->getText() == CEGUI::String(reinterpret_cast<const CEGUI::utf8*>("Alchemist description É")),
        "UTF-8 class text producer has no native consumer");
    key(ui, physical_key::ENTER);
    require(edit("EditBoxPet")->hasInputFocus() && !ui.take_request(), "handle_Submit did not activate pet-name field");
    select_all(ui); key(ui, physical_key::BACKSPACE);
    require(!window("CreatePlayer")->isVisible(false), "empty second name did not hide OK");
    key(ui, physical_key::ENTER); require(!ui.take_request(), "empty pet name submitted creation");
    text(ui, "Spot");
    require(window("CreatePlayer")->isVisible(false), "restored name failed original length gate");
    key(ui, physical_key::ENTER);
    auto request = ui.take_request();
    require(request && request->command == FrontendCommand::create && request->class_guid == 12 &&
        request->name == "Éclai", "original submit path has no typed creation consumer");
    ui.show_main(); open(ui);
    require(ui.character_name().empty() && window("CharacterClass")->getText() == "Destroyer", "reopen retained name/class contrary to setOpen");
    text(ui, "   ");
    click(ui, window("CreatePlayer"));
    request = ui.take_request();
    require(request && request->name == "   ", "portable trim replaced original nonempty/raw-text gate");
    ui.show_main(); open(ui);
    ui.keyboard_event({UiKeyboardEventKind::key_down, 42, {}});
    ui.keyboard_event({UiKeyboardEventKind::leave, 0, {}});
    text(ui, "abc"); key(ui, physical_key::HOME); key(ui, physical_key::RIGHT);
    require(edit("EditBox")->getCaratIndex() == 1 && !edit("EditBox")->getSelectionLength(), "keyboard leave retained Shift state");
    ui.key(FrontendKey::back);
    require(ui.page() == FrontendPage::main, "creation cancel failed");
    std::cout << "PASS: original create resource Editbox/class/focus/submit gates and UTF-8 typed consumer; no GL or pet gameplay claim\n";
    return 0;
} catch (const CEGUI::Exception& e) { std::cerr << e.getMessage().c_str() << '\n'; return 1;
} catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; } }
