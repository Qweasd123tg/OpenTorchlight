#include "torchlight/panel_open.hpp"
#include <array>
#include <iostream>
int main() {
    const std::array<const torchlight::PanelProfile*,4> profiles{{
        &torchlight::panel_profile_inventory(),&torchlight::panel_profile_merchant(),
        &torchlight::panel_profile_quest(),&torchlight::panel_profile_skill()}};
    std::size_t bank;bool opened;
    while(std::cin>>bank>>opened) {
        if(bank>=profiles.size())return 1;
        torchlight::PanelOpenState state(*profiles[bank]);
        if(opened)static_cast<void>(state.set_open(true,false));
        const auto effects=state.set_open(false,false);
        std::cout<<effects.sound_sample<<' '<<state.open()<<' '<<state.aux()<<' '<<effects.blend_close<<'\n';
    }
}
