#include "ai_cooldown_fixture.hpp"
#include "torchlight/player_session.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace {
std::size_t checks=0;
void require(bool v,const char* message){++checks;if(!v)throw std::runtime_error(message);}
std::size_t count_events(const std::vector<LogicEvent>& events,std::u16string_view name) {
    return static_cast<std::size_t>(std::count_if(events.begin(),events.end(),[&](const auto& e){return e.output_name==name;}));
}
LayoutManifest layout() {
    auto result=test_fixture::layout();
    LayoutObject next=result.objects.front();next.id=43;
    next.properties[0].value=std::u16string(u"DEFAULT");result.objects.push_back(next);
    LayoutLogicGroup graph;graph.object_id=100;
    graph.nodes={{1,42,0,0,{{2,u"Monster Killed",u"Spawn Units"}}},{2,43,0,0,{}}};
    result.logic_groups.push_back(graph);return result;
}
void single(const char* pak,bool no_drop) {
    test_fixture::World f(pak);auto manifest=layout();LogicRuntime logic(manifest,5);
    RuntimeEntityWorld world(manifest,f.resources,f.definitions,f.spawn_classes,f.types,5,1);
    require(world.consume_spawn_requests({{42,u"EXPLICIT",u"Monsters",1}},logic).entities_created==1,"spawn failed");
    static_cast<void>(logic.take_events());static_cast<void>(logic.take_spawn_requests());
    const auto id=world.entities().front().id;world.find(id)->drops_loot=!no_drop;
    const std::array<float,3> origin{10,2,30};world.find(id)->position=origin;
    auto* stable_before_flush=world.find(id);
    require(world.apply_damage(id,100000,logic).killed,"death failed");
    require(world.find(id)==stable_before_flush && world.entities().size()==1,"damage invalidated vector views");
    require(!world.kill(id,logic),"duplicate kill accepted");
    require(count_events(logic.take_events(),u"Monster Killed")==0 && logic.take_spawn_requests().empty(),
        "kill callback escaped before item generation phase");
    require(logic.state(42)->active_spawned_units==1,"spawner lifecycle completed before loot");
    world.find(id)->position={99,0,99}; // pending data is immutable, no dangling corpse pointer
    const auto result=world.resolve_death_loot(logic);
    require(result.spawns.entities_created==(no_drop?0U:6U),"death loot quantity mismatch");
    require(result.deaths==(no_drop?0U:1U),"no-loot death rolled treasure");
    const auto events=logic.take_events();
    require(count_events(events,u"Monster Killed")==1 && count_events(events,u"All Monsters Dead")==1,
        "post-loot callback lost/duplicated, including no-loot branch");
    require(logic.state(42)->active_spawned_units==0,"source spawner not finalized");
    std::vector<std::uint64_t> loot_ids;
    for(const auto& entity:world.entities())if(entity.loot_source_id==id) {
        require(entity.position==origin && entity.spawner_id==0,"drop lost original snapshot/ownership");
        loot_ids.push_back(entity.id);
    }
    const auto callback_requests=logic.take_spawn_requests();
    require(callback_requests.size()==1 && callback_requests.front().spawner_id==43,"callback graph did not continue");
    require(world.consume_spawn_requests(callback_requests,logic).entities_created==1,"callback spawn failed");
    const auto callback_id=world.entities().back().id;
    for(auto loot_id:loot_ids)require(loot_id<callback_id,"script spawn ran before loot allocation");
    static_cast<void>(logic.take_events());
    require(world.resolve_death_loot(logic).deaths==0 && logic.take_events().empty(),"drain replayed lifecycle callback");
    static_cast<void>(world.consume_spawn_requests({{42,u"",u"",0,SpawnAction::destroy}},logic));
    for(auto loot_id:loot_ids)require(world.find(loot_id)->alive,"source-spawner cleanup destroyed loot");
}
void batch(const char* pak) {
    test_fixture::World f(pak);f.spawn(u"EXPLICIT");f.spawn(u"EXPLICIT");
    const auto first=f.world.entities()[0].id,second=f.world.entities()[1].id;
    f.world.find(first)->position={1,0,0};f.world.find(second)->position={2,0,0};
    static_cast<void>(f.logic.take_events());
    require(f.world.kill(first,f.logic) && f.world.kill(second,f.logic),"batch deaths");
    require(f.world.entities().size()==2 && f.logic.take_events().empty(),"batch invalidated early");
    require(f.world.resolve_death_loot(f.logic).spawns.entities_created==12,"batch lost one death");
    auto events=f.logic.take_events();require(count_events(events,u"Monster Killed")==2 && count_events(events,u"All Monsters Dead")==1,
        "batch callback count");
    std::size_t a=0,b=0;
    for(const auto& e:f.world.entities()) {
        if(e.loot_source_id==first){++a;require(e.position[0]==1,"batch snapshot A");}
        if(e.loot_source_id==second){++b;require(e.position[0]==2,"batch snapshot B");}
    }
    require(a==6 && b==6,"batch ownership differs");
    require(f.world.resolve_death_loot(f.logic).deaths==0 && f.logic.take_events().empty(),"batch repeated");
}
}
int main(int argc,char** argv){
    try{if(argc!=2)return 2;single(argv[1],false);single(argv[1],true);batch(argv[1]);
        std::cout<<"PASS: "<<checks<<" deferred death/loot/callback assertions (authored resource graph)\n";return 0;
    }catch(const std::exception& e){std::cerr<<"FAIL after "<<checks<<": "<<e.what()<<'\n';return 1;}
}
