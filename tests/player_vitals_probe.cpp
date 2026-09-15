// Numeric adapter, not a simulation of CPlayer/CDieMenu. See compare_player_vitals.py.
#include "torchlight/player_session.hpp"
#include "torchlight/original_combat_inputs.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
float decode(std::uint32_t b) {float f;std::memcpy(&f,&b,4);return f;}
std::uint32_t encode(float f) {std::uint32_t b;std::memcpy(&b,&f,4);return b;}
int main(int argc,char**argv) {
    using namespace torchlight;
    if(argc==2 && std::string(argv[1])=="--constants") {
        using namespace original_combat_inputs;
        for(const auto x:{speed_one,percentage_divisor,minimum_attack_speed,innate_attack_range,
            innate_strike_range,melee_vertical_cutoff,ai_flag_one_speed_multiplier})std::cout<<encode(x)<<'\n';
        std::cout<<effect_catalog_path<<'\n';return 0;
    }
    int operation=0;
    try {
        while(std::cin>>operation) {
            if(operation==0) {
                std::int32_t gold,delta;if(!(std::cin>>gold>>delta))return 2;
                PlayerPrototype p;p.starting_gold=gold;PlayerSession session(p,1);session.give_gold(delta);
                std::cout<<session.gold()<<'\n';
            } else if(operation==1) {
                std::int32_t base;std::uint32_t growth,percent,flat;
                if(!(std::cin>>base>>growth>>percent>>flat))return 2;
                AttackEffects e;e.add(0x13,decode(percent));e.add(4,decode(flat));
                std::cout<<evaluated_maximum_mana(base,decode(growth),e)<<'\n';
            } else if(operation==2) {
                std::int32_t gold;if(!(std::cin>>gold))return 2;
                PlayerPrototype p;p.starting_gold=gold;PlayerSession session(p,1);EnemyController enemies(1);
                ActorMotion motion({},1);TorchlightRandom random(1);
                static_cast<void>(session.health().apply_damage(100,100,DamageType::physical,random));
                std::cout<<session.recover_at_entry(enemies,motion,{}).gold_lost<<'\n';
            } else return 2;
        }
    }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
    return std::cin.eof()?0:2;
}
