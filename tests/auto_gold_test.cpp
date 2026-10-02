#include "torchlight/player_session.hpp"
#include "torchlight/save_store.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
using namespace torchlight;
namespace {
void require(bool good,const char* message){if(!good)throw std::runtime_error(message);}
void core() {
    const std::vector<GoldPickupPoint> points{{1,{2.999999761581421F,900,0},true},
        {2,{3,0,0},true},{3,{1,0,0},false},{4,{0,-900,2},true}};
    require(auto_gold_targets({},true,true,points)==std::vector<std::uint64_t>({1,4}),"strict XZ/type selector");
    require(auto_gold_targets({},true,false,points).empty(),"stationary player auto picks gold");
    require(auto_gold_targets({},false,true,points).empty(),"dead player auto picks gold");
}
void real(const char* path) {
    PakArchive pak(path);MasterResourceIndex index(parse_adm(pak.read_normalized("media/masterresourceunits.dat.adm")));
    UnitDefinitionLoader loader(pak);SpawnClassCatalog classes(pak);UnitTypeHierarchy hierarchy(pak);
    UnitTypeResourceIndex types(pak,hierarchy,index,loader);
    const auto record=std::find_if(index.records().begin(),index.records().end(),[&](const auto& item){
        return item.kind==MasterResourceKind::item&&!item.do_not_create&&hierarchy.is_a_id(item.unit_type,0x22);
    });
    require(record!=index.records().end(),"original gold type resource absent");
    LayoutManifest layout;LayoutObject spawner;spawner.id=42;spawner.descriptor=u"Unit Spawner";layout.objects.push_back(spawner);
    LogicRuntime logic(layout);RuntimeEntityWorld world(layout,index,loader,classes,types,41,1);
    const auto spawn=[&](std::array<float,3> position){
        require(world.consume_spawn_requests({{42,record->name,u"Items",1}},logic).entities_created==1,"original gold spawn failed");
        auto& item=world.entities().back();item.position=position;
        require(item.gold_amount.has_value(),"gold graph/context absent");return item.id;
    };
    const auto near=spawn({2.99F,1000,0}),boundary=spawn({3,0,0}),hidden=spawn({0,0,1}),zero=spawn({0,0,2});
    // Explicit already evaluated onscreen-list fixture, not a camera assertion.
    const std::vector<std::uint64_t> onscreen{near,boundary,hidden,zero};
    world.find(hidden)->visible=false;world.find(zero)->gold_amount=0;
    const auto players=load_playable_players(pak,index,loader);require(!players.empty(),"original player absent");
    PlayerSession session(players.front(),41,&hierarchy);
    const auto before=session.gold();const auto amount=*world.find(near)->gold_amount;
    require(session.auto_pick_up_gold(world,logic,{},false,onscreen).entities.empty()&&session.gold()==before,"stationary pickup changed ownership");
    require(session.auto_pick_up_gold(world,logic,{},true,{}).entities.empty()&&session.gold()==before,"absent onscreen list replaced by all world items");
    const auto collected=session.auto_pick_up_gold(world,logic,{},true,onscreen);
    require(collected.entities==std::vector<std::uint64_t>({near,zero})&&collected.amount==amount,
            "auto pickup lost available gold order/zero-amount entity");
    require(session.gold()==before+amount&&!world.find(near)->alive&&!world.find(zero)->alive&&
            world.find(boundary)->alive&&world.find(hidden)->alive,"auto pickup wallet/world effects differ");
    require(session.auto_pick_up_gold(world,logic,{},true,onscreen).entities.empty()&&session.gold()==before+amount,
            "auto pickup repeated consumed gold");
    const auto checkpoint=CheckpointAccess::capture(world);
    require(!checkpoint.entities[0].alive&&checkpoint.entities[1].alive,"save lost auto pickup lifetime flags");
    const auto overflow=spawn({1,0,1});session.give_gold(std::numeric_limits<std::int32_t>::max());
    require(session.auto_pick_up_gold(world,logic,{},true,{overflow}).entities==std::vector<std::uint64_t>({overflow})&&
            session.gold()==std::numeric_limits<std::int32_t>::max()&&!world.find(overflow)->alive,"wallet saturation duplicates gold");
    const auto pending=spawn({0,0,0});TorchlightRandom random(1);
    static_cast<void>(session.health().apply_damage(100000000,100000000,DamageType::physical,random));
    require(!session.health().alive()&&session.auto_pick_up_gold(world,logic,{},true,{pending}).entities.empty()&&
            world.find(pending)->alive,"dead player consumed world gold");
    std::cout<<"Original gold resource tested; radius boundary, owned wallet and consumed world entities\n";
}
}
int main(int argc,char** argv){try{core();if(argc==2)real(argv[1]);std::cout<<"PASS auto gold production collection\n";return 0;}
    catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
