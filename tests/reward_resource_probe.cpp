#include "torchlight/player.hpp"
#include "torchlight/progression.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
int main(int argc, char** argv) {
    try {
        if(argc!=2) throw std::runtime_error("usage: reward_resource_probe pak.zip");
        const torchlight::PakArchive archive(argv[1]);
        const torchlight::MasterResourceIndex resources(torchlight::parse_adm(
            archive.read_normalized("media/MASTERRESOURCEUNITS.DAT.ADM")));
        torchlight::UnitDefinitionLoader definitions(archive);
        const auto players=torchlight::load_playable_players(archive,resources,definitions);
        if(players.empty()) throw std::runtime_error("no playable resource templates");
        const auto gold=torchlight::find_named_stat_graph(archive,"GOLDDROP");
        const auto experience=torchlight::find_named_stat_graph(archive,"EXPERIENCE_MONSTER");
        if(!gold || !experience) throw std::runtime_error("Normal reward graphs missing");
        std::size_t levels=0;
        for(const auto& player:players) {
            if(!player.progression_rules) throw std::runtime_error("player progression graphs unavailable");
            const auto& rules=*player.progression_rules;
            if(rules.at(1).base_mana!=player.base_mana) throw std::runtime_error("initial mana graph resolution disagrees");
            torchlight::ProgressionState state;
            const auto crossed=torchlight::advance_progression(state,rules,std::numeric_limits<std::int32_t>::max());
            if(state.level!=rules.maximum_level() || crossed!=static_cast<std::uint32_t>(rules.maximum_level()-1))
                throw std::runtime_error("cannot traverse resource level gates");
            for(std::int32_t i=1;i<=rules.maximum_level();++i) {
                static_cast<void>(torchlight::evaluated_world_gold(gold->value(static_cast<float>(i)),100));
                static_cast<void>(torchlight::original_monster_experience(experience->value(static_cast<float>(i))));
                ++levels;
            }
            std::cout<<"class_guid="<<player.guid<<" max_level="<<rules.maximum_level()
                     <<" cap="<<state.experience<<" awarded_stats="<<state.stat_points
                     <<" awarded_skills="<<state.skill_points<<'\n';
        }
        std::cout<<"PASS: "<<players.size()<<" class templates, "<<levels
                 <<" level-graph samples; resource compatibility only, XP scalar formula original-code, NOT full original parity\n";
    } catch(const std::exception& e) {std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
