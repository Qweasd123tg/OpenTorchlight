#include "torchlight/frontend.hpp"
#include <CEGUI.h>
#include <algorithm>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace {
void require(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
CEGUI::Window* window(const std::string& name) {
    return CEGUI::WindowManager::getSingleton().getWindow("__cegui/load/" + name);
}
void click(Frontend& ui, CEGUI::Window* target, bool fresh = true) {
    static bool side=false;
    static CEGUI::Point point;
    if (fresh) ui.advance(1);
    if (fresh) static_cast<void>(ui.frame(1024,768));
    const auto r = target->getUnclippedPixelRect();
    // CEGUI's multi-click timer uses wall time, not injectTimePulse. Separate
    // intended single clicks spatially; a double uses the exact same point.
    if (fresh) { side=!side; point={(r.d_left+r.d_right)/2+(side?1:-1)*r.getWidth()*.2F,(r.d_top+r.d_bottom)/2}; }
    ui.pointer_event({UiPointerEventKind::button_down, point.d_x, point.d_y});
    ui.pointer_event({UiPointerEventKind::button_up, point.d_x, point.d_y});
}
void open(Frontend& ui) {
    ui.advance(1);
    const auto f = ui.frame(1024,768);
    const auto b = std::find_if(f.buttons.begin(),f.buttons.end(),[](const auto& b){return b.id=="loads";});
    require(b != f.buttons.end(), "source Load command missing");
    ui.click(b->rect.x+b->rect.width/2, b->rect.y+b->rect.height/2);
    require(ui.page()==FrontendPage::load, "Load did not attach native page");
    static_cast<void>(ui.frame(1024,768));
}
std::vector<SaveSlotInfo> saves() {
    std::vector<SaveSlotInfo> result;
    for (int i=0;i<7;++i) {
        SaveSlotInfo slot;
        slot.slot="slot"+std::to_string(i); slot.name=i==0?"Éclair":"Hero"+std::to_string(i);
        slot.class_guid=11; slot.level=i+1; result.push_back(slot);
    }
    return result;
}

}
int main(int argc,char** argv) { try {
    require(argc==2,"expected external pak.zip");
    PakArchive archive(argv[1]); UiResources resources(archive);
    Frontend ui(resources,{{11,"Destroyer","","Destroyer"}});
    auto entries=saves(); ui.set_saves(entries); open(ui);
    auto f=ui.frame(1024,768);
    require(f.cegui && !f.cegui->quads.empty() && frontend_paint_list(f).empty(), "Load uses duplicate painter");
    require(window("Player1Name")->getText()==CEGUI::String(reinterpret_cast<const CEGUI::utf8*>("Éclair")),"UTF-8 save name lost");
    require(window("CharacterName")->getText()==window("Player1Name")->getText(),"first save not selected on open");
    require(window("Player1Desc")->getText()=="Level 1 Destroyer","existing OTC descriptor has no native consumer");
    require(!window("Player1Name")->isAlwaysOnTop(),"malformed lowercase resource property was repaired");
    require(!window("ScrollUp")->isVisible(false) && window("ScrollDown")->isVisible(false),"initial scroll guards differ");
    require(!window("DeleteConfirm")->isVisible(false) && !window("CharacterModsWarning")->isVisible(false),"unproduced prompt/mod mismatch shown");
    require(window("PlayerHighlight1")->isMousePassThroughEnabled(),"source highlight blocks row input");
    click(ui,window("Player3"));
    require(window("PlayerHighlight3")->isVisible(false) && !window("PlayerHighlight1")->isVisible(false),"native row selection failed");
    require(window("CharacterName")->getText()=="Hero2","selected name consumer differs");
    click(ui,window("ScrollDown")); click(ui,window("ScrollDown"));
    require(window("Player1Name")->getText()=="Hero2" && !window("ScrollDown")->isVisible(false),"scroll window failed count-5 bound");
    require(window("PlayerHighlight1")->isVisible(false),"scroll overwrote absolute selected index");
    click(ui,window("Player5")); click(ui,window("Continue"));
    auto request=ui.take_request();
    require(request && request->command==FrontendCommand::load && request->slot=="slot6","Play loaded row number instead of absolute selected save");
    ui.show_main(); open(ui);
    require(window("Player1Name")->getText()==CEGUI::String(reinterpret_cast<const CEGUI::utf8*>("Éclair")) && window("PlayerHighlight1")->isVisible(false),"reopen did not reset scroll/selection");
    click(ui,window("Player5")); ui.advance(.1F); click(ui,window("Player5"),false);
    require(!ui.take_request(),"fifth row got invented double-click loading");
    click(ui,window("Player2")); ui.advance(.1F); click(ui,window("Player2"),false);
    request=ui.take_request();
    require(request && request->command==FrontendCommand::load && request->slot=="slot1","source row double-click has no load consumer");
    ui.show_main(); entries[1].health=0; entries[2].error="corrupt OTC"; ui.set_saves(entries); open(ui);
    click(ui,window("Player2")); click(ui,window("Continue")); require(!ui.take_request(),"dead save bypassed original health gate");
    click(ui,window("Player2")); ui.advance(.1F); click(ui,window("Player2"),false);
    require(!ui.take_request(),"dead save double-click bypassed health gate");
    click(ui,window("Player3")); click(ui,window("Continue"));
    require(!ui.take_request() && window("Player3Desc")->getText()=="PORT SAVE: UNREADABLE","unreadable OTC adapter boundary lost");
    click(ui,window("Delete")); require(window("DeleteConfirm")->isVisible(false),"delete did not show source prompt");
    click(ui,window("Player4"));
    require(window("CharacterName")->getText()=="Hero3" && window("DeleteConfirm")->isVisible(false),"invented confirmation lock prevents original selection");
    click(ui,window("Cancel")); require(!ui.take_request() && !window("DeleteConfirm")->isVisible(false),"decline deleted a save");
    click(ui,window("Delete")); click(ui,window("DeleteConfirmButton"));
    request=ui.take_request();
    require(request && request->command==FrontendCommand::remove && request->slot=="slot3" && !window("DeleteConfirm")->isVisible(false),"Accept did not hide then remove current selection");
    entries.erase(entries.begin()+3); ui.set_saves(entries); ui.removed();
    require(window("CharacterName")->getText()=="Hero2" && window("PlayerHighlight3")->isVisible(false),"successful delete did not select previous record");
    ui.set_saves({}); static_cast<void>(ui.frame(1024,768));
    require(!window("Continue")->isVisible(false) && !window("Delete")->isVisible(false),"empty list actions visible");
    for(int row=1;row<=5;++row) {
        const auto n=std::to_string(row);
        for(const auto& name:{"Player"+n,"Player"+n+"Name","Player"+n+"Desc","PlayerHighlight"+n})
            require(!window(name)->isVisible(false),"empty row remained visible");
    }
    require(window("CharacterName")->getText().empty(),"empty list retained preview name");
    click(ui,window("Back")); require(ui.page()==FrontendPage::main,"Back failed native detach");
    std::cout<<"PASS: native original five-row load resource, selection/scroll/health/double-click/delete gates and OTC consumer; no SVB/preview claim\n";
    return 0;
} catch(const CEGUI::Exception& e) { std::cerr<<e.getMessage().c_str()<<'\n'; return 1;
} catch(const std::exception& e) { std::cerr<<e.what()<<'\n'; return 1; } }
