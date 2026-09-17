// Frozen author-owned v2 fixtures are generated ONLY against unmodified fresh.
// Not an original Torchlight save generator. Not part of the current build.
#include "ai_cooldown_fixture.hpp"
#include "torchlight/save_store.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
int main(int argc,char**argv) {
    using namespace torchlight;
    static_assert(kCheckpointFormatVersion==2,"Use unchanged fresh baseline, not current code");
    try {
        if(argc!=4) throw std::runtime_error("usage: v2-writer fixture output level(1|3)");
        test_fixture::World f(argv[1]);
        const auto players=load_playable_players(f.archive,f.resources,f.definitions);
        const auto proto=std::find_if(players.begin(),players.end(),[](const auto& p){return p.name==u"TEST_PLAYER";});
        if(proto==players.end())throw std::runtime_error("no hero");
        PlayerSession player(*proto,9);
        const auto result=f.world.consume_spawn_requests({{42,u"VITAL_CHEST",u"Items",1}},f.logic);
        if(result.entities_created!=1)throw std::runtime_error("no item");
        const auto item=player.pick_up(f.world,f.world.entities().back().id,f.logic);
        if(player.equip(item)!=InventoryChange::changed)throw std::runtime_error("cannot equip");
        const bool high=std::string(argv[3])=="3";
        if(high && player.award_experience(403)!=2)throw std::runtime_error("cannot level");
        if(!player.health().spend_mana(17))throw std::runtime_error("cannot spend mana");
        TorchlightRandom random(32);
        static_cast<void>(player.health().apply_damage(27,27,DamageType::physical,random));
        player.give_gold(37);
        CampaignCheckpoint c;c.slot="vitals-test";c.class_guid=1;c.character_name="V2 Hero";c.resource_identity=1;
        c.player=CheckpointAccess::capture(player);
        FloorCheckpoint floor;floor.address={u"Town",0};floor.layout_identity=1;c.floors.push_back(floor);
        const auto bytes=encode_checkpoint(c);
        std::ofstream out(argv[2],std::ios::binary);out.write(reinterpret_cast<const char*>(bytes.data()),bytes.size());out.close();
        if(!out)throw std::runtime_error("cannot write fixture");
        std::cout<<"v2 level="<<player.progression().level<<" hp="<<player.health().health()<<" max="<<player.health().maximum_health()
            <<" mana="<<*player.health().mana()<<" gold="<<player.gold()<<" bytes="<<bytes.size()<<'\n';
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 1;}
}
