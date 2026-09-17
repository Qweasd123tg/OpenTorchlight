#include "torchlight/ui_hud.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace {
unsigned checks=0;
void require(bool value,const char* message) { ++checks; if(!value) throw std::runtime_error(message); }
const UiResolvedWidget& named(const UiHudFrame& frame,const char* name) {
    const auto it=std::find_if(frame.buttons.begin(),frame.buttons.end(),[&](const auto&w){return w.name==name;});
    if(it==frame.buttons.end()) throw std::runtime_error(std::string("HUD button missing: ")+name);
    return *it;
}
}
int main(int argc,char**argv) {
    try {
        if(argc<2||argc>3) throw std::runtime_error("expected fixture or original pak [--original]");
        PakArchive archive(argv[1]); UiResources resources(archive); UiHud hud(resources);
        const auto frame=hud.frame(1280,720,{});
        const auto& inv=named(frame,"InventoryButton");
        require(inv.callback=="guiToggleInventory","resource callback changed");
        require(inv.image.empty(),"explicit empty NormalImage inherited a skin");
        const float x=inv.clip.x+inv.clip.width/2, y=inv.clip.y+inv.clip.height/2;
        require(inv.clip.width>0&&inv.clip.height>0,"inventory clip absent");
        require(hud_button_at(frame,x,y)==&inv,"transparent button lost hit area");
        const auto hover=hud.frame(1280,720,{},{{std::array<float,2>{x,y}},std::nullopt});
        require(named(hover,"InventoryButton").image==inv.property("HoverImage"),"hover not resource-derived");
        const auto pushed=hud.frame(1280,720,{},{{std::array<float,2>{x,y}},{std::array<float,2>{x,y}}});
        require(named(pushed,"InventoryButton").image==inv.property("PushedImage"),"pressed image lost");
        const auto off=hud.frame(1280,720,{},{{std::array<float,2>{-10,-10}},{std::array<float,2>{x,y}}});
        require(named(off,"InventoryButton").image==inv.property("HoverImage"),"PushedOff must reference hover section");
        require(hud_click_callback(frame,{{x,y},{x,y}})=="guiToggleInventory","matching release lost");
        require(!hud_click_callback(frame,{{x,y},{-10,-10}}),"release outside activated");
        require(!hud_click_callback(frame,{{-10,-10},{x,y}}),"world press dragged onto button activated");
        require(!hud_button_at(frame,inv.rect.x+inv.rect.width,inv.rect.y),"right edge inclusive");
        if(argc==2) {
            require(frame.buttons.size()==2,"hidden button resurrected");
            const auto& disabled=named(frame,"DisabledButton");
            require(disabled.image=="set:HudTest image:Disabled","disabled skin lost");
            require(hud_button_at(frame,100,40)==&disabled,"disabled area does not block world");
            require(!hud_click_callback(frame,{{100,40},{100,40}}),"disabled button activated");
            require(!hud_click_callback(frame,{{x,y},{100,40}}),"release on different button activated");
            auto clipped=frame; clipped.buttons[0].clip={0,0,0,0};
            require(!hud_button_at(clipped,x,y),"empty clip still hit-testable");
        } else {
            require(std::string(argv[2])=="--original","unknown flag");
            for(const auto *name:{"SkillsButton","JournalButton","PetButton","QuestButton","OptionsButton"})
                require(!named(frame,name).callback.empty(),"shipped hover-only callback dropped");
            require(named(frame,"JournalButton").callback!=named(frame,"QuestButton").callback,
                    "journal and quests incorrectly conflated");
        }
        std::cout<<"ui_hud_input: "<<checks<<" assertions; "<<(argc==3?"original resource":"authored fixture")
                 <<"; no full CEGUI event-pipeline parity claim\n";
        return 0;
    }catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}
}
