// Compile this same probe against the immutable previous build and the new one.
// Uses public APIs available in both; fixtures are authored, not original assets.
#include "ai_cooldown_fixture.hpp"
#include "torchlight/player_session.hpp"
#include "torchlight/save_store.hpp"
#include <fstream>
#include <iostream>
using namespace torchlight;
int main(int argc,char**argv){try {
    if(argc!=3)throw std::runtime_error("usage: probe stats-fixture save.otc");
    test_fixture::World f(argv[1]);PlayerPrototype proto;bool found=false;
    for(const auto&p:load_playable_players(f.archive,f.resources,f.definitions))if(p.name==u"STAT_PLAYER"){proto=p;found=true;}
    if(!found)throw std::runtime_error("missing fixture player");
    PlayerSession p(proto,42,&f.hierarchy);
    if(f.world.consume_spawn_requests({{42,u"STAT_CHEST",u"Items",1}},f.logic).entities_created!=1)
        throw std::runtime_error("missing stat item");
    const auto id=p.pick_up(f.world,f.world.entities().back().id,f.logic);
    if(!id||p.equip(id)!=InventoryChange::changed)throw std::runtime_error("cannot equip stat item");
    TorchlightRandom rng(7);(void)p.health().apply_damage(1,1,DamageType::physical,rng);
    CampaignCheckpoint c;c.slot="stats";c.class_guid=proto.guid;c.resource_identity=1;c.character_name="Stats";
    FloorCheckpoint floor;floor.address={u"Town",0};floor.layout_identity=1;c.floors.push_back(floor);
    c.player=CheckpointAccess::capture(p);
    const auto data=encode_checkpoint(c);std::ofstream out(argv[2],std::ios::binary);
    out.write(reinterpret_cast<const char*>(data.data()),data.size());if(!out)throw std::runtime_error("save failed");
    test_fixture::World ef(argv[1]);ef.spawn(u"MOVEMENT_BONUS");const auto enemy=ef.world.entities()[0].id;
    EnemyController enemies(1);PlayerCombatState target(proto,1);
    const auto update=enemies.update(1,{8,0,0},target,ef.world);
    if(update.empty())throw std::runtime_error("AI not updated");
    std::cout<<"{\"equipped_physical_AC\":"<<p.health().armor_class()
      <<",\"saved_raw_base_armor\":"<<c.player.base_defense.natural_armor
      <<",\"saved_health\":"<<c.player.health
      <<",\"loaded_SAVE_speed_percent\":"<<ef.world.find(enemy)->attack_character.effects.get(0x15)
      <<",\"enemy_distance_in_one_second\":"<<ef.world.find(enemy)->position[0]<<"}\n";
    return 0;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
