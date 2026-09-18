#include "torchlight/equipment.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace torchlight;
namespace { void require(bool b,const char* m){if(!b)throw std::runtime_error(m);} }
int main(){try {
    require(item_graph_stat(21,100,0,false)==21,"damage graph");
    require(item_graph_stat(0,100,0,false)==0,"damage incorrectly clamped to one");
    require(item_graph_stat(0,100,0,true)==1,"armor minimum");
    require(item_graph_stat(100,100,5,true)==150&&item_graph_stat(100,100,10,true)==150,"heirloom cap");
    require(item_graph_stat(100,30,0,true)==31,"division-before-multiply rounding");
    bool bad=false;try{(void)item_graph_stat(1,100,-1,false);}catch(const std::runtime_error&){bad=true;}
    require(bad,"negative count accepted");
    bad=false;try{(void)item_graph_stat(std::numeric_limits<float>::infinity(),100,0,false);}catch(const std::runtime_error&){bad=true;}
    require(bad,"nonfinite graph accepted");
    bad=false;try{(void)item_graph_stat(1e30F,100,0,false);}catch(const std::runtime_error&){bad=true;}
    require(bad,"out of range graph accepted");
    WeaponPrototype w;w.minimum_damage_percent=50;w.maximum_damage_percent=100;
    w.base_weapon_damage=100;w.rarity_damage_modifier=100;w.speed_damage_modifier=100;
    TorchlightRandom rng(42), reference(42);(void)reference.integer_between(50,100);
    const auto item=roll_weapon_item(w,rng,3);
    require(item.maximum_damage==130&&item.minimum_damage==65,"heirloom weapon max");
    require(rng.state()==reference.state(),"heirloom incorrectly skipped RNG draw");
    w.minimum_damage_percent=w.maximum_damage_percent=0;
    require(roll_weapon_item(w,rng).maximum_damage==0,"zero damage graph lost in item roll");
    std::cout<<"item_graph: 11 checks passed\n";return 0;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
