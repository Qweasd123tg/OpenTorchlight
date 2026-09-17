#include "ai_cooldown_fixture.hpp"
#include "torchlight/save_store.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace torchlight;
namespace {
void require(bool b,const char* s){if(!b)throw std::runtime_error(s);}
}
int main(int argc,char**argv){try{
    if(argc!=5)throw std::runtime_error("mode fixture save output");
    const bool continued=std::string(argv[1])=="--continued";
    test_fixture::World f(argv[2]);
    std::ifstream stream(argv[3],std::ios::binary);std::vector<std::uint8_t> bytes((std::istreambuf_iterator<char>(stream)),{});
    require(bytes.size()>12&&bytes[8]==(continued?4:3),"wrong fixture save version");
    auto checkpoint=decode_checkpoint(bytes);
    const auto players=load_playable_players(f.archive,f.resources,f.definitions);
    auto proto=std::find_if(players.begin(),players.end(),[&](const auto& p){return p.guid==checkpoint.class_guid;});
    require(proto!=players.end(),"legacy class lost");
    auto session=CheckpointAccess::restore_player(*proto,checkpoint.player,73,&f.hierarchy);
    session.hydrate_consumables(f.definitions,f.resources);
    EnemyController enemies(1);CheckpointAccess::restore_floor(checkpoint.floors.at(0),f.world,f.logic,enemies);
    require(session.gold()==146&&session.health().health()==(continued?50:40),"legacy load changed HP/gold");
    require(session.inventory().items().size()==(continued?3:4),"legacy item count changed");
    require(session.weapon()&&session.weapon()->id==4&&session.weapon()->weapon->prototype.delivery==WeaponDelivery::direct_physical,"legacy ranged item lost");
    require(session.combat().attack_loadout().right->delivery==WeaponDelivery::direct_physical,"legacy equipped delivery not hydrated");
    require(session.weapon()->weapon->minimum_damage==checkpoint.player.inventory.items.back().weapon->minimum_damage,"legacy damage rerolled");
    require(CheckpointAccess::capture(session).combat_random==checkpoint.player.combat_random,"legacy RNG rerolled");
    auto world=CheckpointAccess::capture(f.world);require(world.entities.size()==6&&world.population_generated,"legacy floor respawn marker not set");
    require(std::count_if(world.entities.begin(),world.entities.end(),[](const auto& e){return !e.alive;})==5,"legacy bodies/items resurrected");
    const auto enemy=std::find_if(world.entities.begin(),world.entities.end(),[](const auto& e){return e.alive&&e.attacks.right.has_value();});
    require(enemy!=world.entities.end()&&enemy->attacks.right->delivery==WeaponDelivery::direct_physical,"legacy enemy delivery missing");
    std::size_t potions=0;InventoryId potion=0;
    for(const auto& i:session.inventory().items())if(i.consumable){++potions;potion=i.id;require(i.consumable->count==1,"legacy hydration invented stack quantity");}
    require(potions==(continued?2:3),"legacy potions not hydrated");
    if(!continued){
        require(session.active_recovery().empty(),"old save invented active recovery");
        require(session.use_consumable(potion)==ConsumableUse::used,"legacy potion cannot be used");
    }else require(session.active_recovery().size()==1&&session.active_recovery()[0].remaining==1.5F,"upgraded active timer lost");
    require(session.update_vitals(.5F)&&session.health().health()==(continued?60:50),"legacy finite recovery incorrect");
    checkpoint.player=CheckpointAccess::capture(session);checkpoint.floors[0].world=CheckpointAccess::capture(f.world);
    bytes=encode_checkpoint(checkpoint);require(bytes[8]==4,"migration did not write v4");
    if(!continued){std::ofstream output(argv[4],std::ios::binary);output.write(reinterpret_cast<const char*>(bytes.data()),bytes.size());require(static_cast<bool>(output),"upgrade write");}
    std::cout<<"PASS legacy v3 "<<(continued?"v4 second process":"untouched writer migration")<<"; no refill, reroll, duplicate or respawn\n";
    return 0;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
