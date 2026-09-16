#include "torchlight/level_transition.hpp"
#include <iostream>
#include <stdexcept>
using namespace torchlight;
int main(){
    try{
        const auto require=[](bool ok){if(!ok)throw std::runtime_error("parent dungeon route mismatch");};
        DungeonManifest main; main.name=u"Main";main.parent_dungeon=u"Town";
        main.strata.push_back({u"STRATA0",u"media/layouts/mine.dat",10,true,true,false});
        LevelTransitionState state({u"Main",1});WarpRequest back;back.level_delta=-1;
        auto e=state.resolve_entry(back,main);
        require(e.source.dungeon_name==u"Main" && e.source.depth==1 &&
                e.destination.dungeon_name==u"Town" && e.destination.depth==0 && e.warp.level_delta==-1);
        back.absolute_level=0;require(state.resolve_entry(back,main).destination.dungeon_name==u"Town");
        back.absolute_level=5;require(state.resolve_entry(back,main).destination.depth==5);
        back.absolute_level.reset();back.dungeon_name=u"Other";
        require(state.resolve_entry(back,main).destination.dungeon_name==u"Other");
        back.dungeon_name.clear();back.waypoint=true;
        require(state.resolve_entry(back,main).destination.dungeon_name==u"Main");
        back.waypoint=false;back.level_delta=-99;
        require(state.resolve_entry(back,main).destination.dungeon_name==u"Main");
        back.level_delta=-1;state.commit({u"Main",2});
        require(state.resolve_entry(back,main).destination.dungeon_name==u"Main" &&
                state.resolve_entry(back,main).destination.depth==1);
        state.commit({u"Main",1});main.parent_dungeon.clear();
        require(state.resolve_entry(back,main).destination.dungeon_name==u"Main");
        main.name=u"Wrong";bool rejected=false;
        try{(void)state.resolve_entry(back,main);}catch(const std::exception&){rejected=true;}
        require(rejected);
        std::cout<<"First-floor parent route, metadata identity and unsupported special modes checked\n";
        return 0;
    }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
