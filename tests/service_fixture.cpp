// Explicit test-only preparation. Uses earned XP and gold injection to reach
// Infuse's source gate without claiming to have played the campaign to level 10.
// Input is a real application-created checkpoint; no world/NPC/skill/gear injection.
#include "torchlight/save_store.hpp"
#include <iostream>
using namespace torchlight;
int main(int argc,char**argv) {
    try {
        if(argc!=3)throw std::invalid_argument("service_fixture PAK SAVE_DIR");
        PakArchive pak(argv[1]);MasterResourceIndex index(parse_adm(pak.read_normalized("media/masterresourceunits.dat.adm")));
        UnitDefinitionLoader loader(pak);UnitTypeHierarchy types(pak);SaveStore saves(argv[2]);
        auto slots=saves.list(checkpoint_resource_identity(pak));
        if(slots.size()!=1||!slots[0].loadable())throw std::invalid_argument("exactly one loadable fixture slot required");
        auto c=saves.read(slots[0].slot);const auto players=load_playable_players(pak,index,loader);
        for(const auto& proto:players)if(proto.guid==c.class_guid) {
            auto session=CheckpointAccess::restore_player(proto,c.player,c.seed,&types);
            session.attach_skill_catalog(std::make_shared<SkillCatalog>(pak));
            bool infuse=false;for(const auto& skill:session.skills().skills)infuse|=skill.name==u"INFUSE";
            if(!infuse)throw std::invalid_argument("fixture must select the Alchemist class");
            if(session.progression().level!=1)throw std::invalid_argument("fixture must start at level 1");
            while(session.progression().level<10) {
                const auto gate=session.progression_rules()->gate(session.progression().level);
                if(!session.award_experience(gate-session.progression().experience))throw std::runtime_error("XP gate failed");
            }
            session.give_gold(10000);c.player=CheckpointAccess::capture(session);
            const auto revision=saves.write(c);
            std::cout<<"TEST FIXTURE ONLY: earned XP to level 10 + 10000 gold; revision="<<revision<<'\n';return 0;
        }
        throw std::runtime_error("fixture class missing");
    } catch(const std::exception&e) {std::cerr<<e.what()<<'\n';return 1;}
}
