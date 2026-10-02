#include "torchlight/ui_pause.hpp"
#include "torchlight/inventory_menu.hpp"
#include <array>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
int main() {
    try {
        InventoryMenuState inventory;
        PanelOpenState merchant(panel_profile_merchant()),quest(panel_profile_quest()),skill(panel_profile_skill());
        const auto paused=[&](UiPauseInputs state=UiPauseInputs{}) {
            const std::array<UiPausePanel,4> panels{{{true,inventory.open()},{false,merchant.open()},
                                                   {true,quest.open()},{true,skill.open()}}};
            return ui_game_is_paused(state,panels.data(),panels.size());
        };
        const auto require=[](bool good,const char* message){if(!good)throw std::runtime_error(message);};
        require(!paused(),"closed panels pause gameplay");
        inventory.set_open(true,false);require(!paused(),"single inventory freezes gameplay");
        quest.set_open(true,false);skill.set_open(true,false);
        require(!paused(),"several right-side panels masquerade as both sides");
        merchant.set_open(true,false);require(paused(),"both covered sides do not pause");
        inventory.set_open(false,false);quest.set_open(false,false);skill.set_open(false,false);
        require(!paused(),"single left-side merchant pauses gameplay");
        UiPauseInputs state;state.ui_present=false;state.explicit_pause=true;
        require(!paused(state),"absent UI incorrectly reads its explicit pause flag");
        state.forced=true;require(paused(state),"forced pause lost with absent UI");
        state={};state.console_open=true;require(paused(state),"console pause lost");
        state.console_no_pause=-1;require(!paused(state),"nonzero console no-pause is ignored");
        state.modal_partial=true;require(paused(state),"modal pause lost behind console bypass");
        std::cout<<"PASS UI pause production controller inputs\n";
        return 0;
    }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
