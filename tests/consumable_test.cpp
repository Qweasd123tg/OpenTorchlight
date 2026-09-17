#include "ai_cooldown_fixture.hpp"
#include "torchlight/save_store.hpp"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
using namespace torchlight;
namespace {
unsigned checks=0;
void require(bool b,const char* s) { ++checks; if(!b) throw std::runtime_error(s); }
void near(float a,float b,const char* s) { require(std::abs(a-b)<.002F,s); }
PlayerPrototype hero(test_fixture::World& f) {
    auto players=load_playable_players(f.archive,f.resources,f.definitions);
    for(auto& p:players) if(p.name==u"TEST_PLAYER") return p;
    throw std::runtime_error("fixture hero missing");
}
InventoryId pickup(test_fixture::World& f, PlayerSession& p,const char16_t* name) {
    const auto spawned=f.world.consume_spawn_requests({{42,name,u"Items",1}},f.logic);
    require(spawned.entities_created==1,"potion not created by resource pipeline");
    const auto entity=f.world.entities().back().id;
    const auto id=p.pick_up(f.world,entity,f.logic);
    require(id!=0,"potion not transferred");
    require(!p.pick_up(f.world,entity,f.logic),"world item picked twice");
    return id;
}
CampaignCheckpoint checkpoint(const PlayerSession& p) {
    CampaignCheckpoint c; c.slot="potions";c.class_guid=1;c.character_name="Potion Hero";c.resource_identity=1;
    c.player=CheckpointAccess::capture(p);FloorCheckpoint f;f.address={u"Town",0};f.layout_identity=1;c.floors.push_back(f);return c;
}
void wound(PlayerSession& p,int n) { TorchlightRandom r(7);static_cast<void>(p.health().apply_damage(n,n,DamageType::physical,r)); }
void cycle(const char* path) {
    test_fixture::World f(path);auto proto=hero(f);PlayerSession p(proto,7,&f.hierarchy);
    auto hp=pickup(f,p,u"HP_POTION");
    require(p.inventory().find(hp)->consumable->effects[0].type==124,"catalog ordinal lost");
    auto same=pickup(f,p,u"HP_POTION");require(hp==same && p.inventory().find(hp)->consumable->count==2,"identical bottles did not stack");
    same=pickup(f,p,u"HP_POTION");require(hp==same && p.inventory().find(hp)->consumable->count==3,"stack capacity handling");
    const auto overflow=pickup(f,p,u"HP_POTION");require(overflow!=hp,"full stack swallowed bottle");
    auto before=encode_checkpoint(checkpoint(p));
    require(p.use_consumable(hp)==ConsumableUse::full_or_active,"full HP potion accepted");
    require(encode_checkpoint(checkpoint(p))==before,"rejected use mutated state");
    wound(p,60);near(p.health().health(),40,"authored injury");
    require(p.use_consumable(hp)==ConsumableUse::used,"wounded potion rejected");
    require(p.inventory().find(hp)->consumable->count==2 && p.active_recovery().size()==1,"use debited wrong quantity");
    near(p.health().health(),40,"finite potion applied instant heal");
    const auto big=pickup(f,p,u"BIG_POTION");
    require(p.use_consumable(big)==ConsumableUse::full_or_active,"same named recovery refreshed/stacked");
    before=encode_checkpoint(checkpoint(p));require(p.update_vitals(0),"paused timer update");
    require(!p.update_vitals(-1) && !p.update_vitals(std::numeric_limits<float>::quiet_NaN()),"invalid delta accepted");
    require(before==encode_checkpoint(checkpoint(p)),"pause/invalid delta changed timers");
    require(p.update_vitals(.5F),"recovery advance");near(p.health().health(),50,"finite recovery scalar incorrect");
    near(p.active_recovery()[0].remaining,1.5F,"timer not reduced");
    require(p.health().spend_mana(20),"mana spend");
    auto mixed=pickup(f,p,u"MIX_POTION");
    require(p.use_consumable(mixed)==ConsumableUse::used,"mixed potion rejected eligible mana effect");
    require(!p.inventory().find(mixed) && p.active_recovery().size()==2,"mixed bottle not exactly once / duplicate HP");
    auto saved=checkpoint(p);auto bytes=encode_checkpoint(saved);require(bytes[8]==4,"not save v4");
    auto loaded=CheckpointAccess::restore_player(proto,decode_checkpoint(bytes).player,99,&f.hierarchy);
    require(encode_checkpoint(checkpoint(loaded))==bytes,"load rerolled or healed potion state");
    require(loaded.update_vitals(3) && p.update_vitals(3),"expiry spanning update");
    require(encode_checkpoint(checkpoint(loaded))==encode_checkpoint(checkpoint(p)),"timer continuation diverged");
    near(p.health().health(),80,"over-time recovery beyond expiry");
    near(*p.health().mana(),*p.health().maximum_mana(),"mixed mana not restored/clamped");
    require(p.active_recovery().empty(),"expired effects not removed");
    require(p.use_consumable(big)==ConsumableUse::used,"expired NAME still blocks use");
    require(!p.inventory().find(big),"last bottle not deleted");
    const auto bad=pickup(f,p,u"BAD_POTION"),conditional=pickup(f,p,u"CONDITIONAL_POTION"),level=pickup(f,p,u"LEVEL_POTION");
    before=encode_checkpoint(checkpoint(p));
    require(p.use_consumable(bad)==ConsumableUse::unsupported && p.use_consumable(conditional)==ConsumableUse::unsupported,"unsupported partial potion accepted");
    require(p.use_consumable(level)==ConsumableUse::level_required,"level gate ignored");
    require(before==encode_checkpoint(checkpoint(p)),"failed items were consumed");
    auto tampered=saved.player;tampered.active_recovery[0].remaining=99;
    bool rejected=false;try { static_cast<void>(CheckpointAccess::restore_player(proto,tampered,1)); } catch(const CheckpointError&) { rejected=true; }
    require(rejected,"bad saved timer accepted");
    tampered=saved.player;tampered.inventory.items[0].consumable->count=999;
    rejected=false;try { CheckpointAccess::validate(tampered); } catch(const CheckpointError&) { rejected=true; }
    require(rejected,"bad saved stack accepted");
    wound(p,10000);before=encode_checkpoint(checkpoint(p));
    require(p.use_consumable(hp)==ConsumableUse::dead && before==encode_checkpoint(checkpoint(p)),"dead potion consumed or revived");
    require(p.update_vitals(1) && !p.health().alive() && p.active_recovery().empty(),"dead recovery not cleared");
    // Legacy owned potion hydration resolves only absent descriptors, with no grants.
    auto old=saved.player;old.active_recovery.clear();for(auto& i:old.inventory.items)i.consumable.reset();
    auto legacy=CheckpointAccess::restore_player(proto,old,7,&f.hierarchy);
    legacy.hydrate_consumables(f.definitions,f.resources);
    require(legacy.inventory().items().size()==old.inventory.items.size(),"legacy hydration granted items");
    require(legacy.inventory().find(hp)->consumable.has_value(),"legacy bottle stayed view-only");
    const auto hydrated=encode_checkpoint(checkpoint(legacy));legacy.hydrate_consumables(f.definitions,f.resources);
    require(hydrated==encode_checkpoint(checkpoint(legacy)),"hydration re-evaluated saved descriptor");
    // Shared bag operation: partial stack transfer, uses, infinite sentinel, mismatch.
    PlayerInventory bag;InventoryItem i;i.resource_guid=9;i.consumable=ConsumableItem{};
    i.consumable->maximum_stack=3;i.consumable->count=2;i.consumable->effects={{u"HP",124,2,100}};
    auto a=bag.store(i);auto b=bag.store(i);
    require(a==b && bag.items().size()==2 && bag.find(a)->consumable->count==3 && bag.items()[1].consumable->count==1,"partial stack merge lost remainder");
    i.consumable->effects[0].value=101;require(bag.store(i)!=a,"different effect instances merged");
    i.consumable->count=1;i.consumable->uses=-9999;auto infinite=bag.store(i);
    require(bag.consume_one(infinite)&&bag.find(infinite),"infinite item exhausted");
    i.consumable->uses=2;auto multi=bag.store(i);require(bag.consume_one(multi)&&bag.find(multi)->consumable->uses==1,"uses not decremented");
    require(bag.consume_one(multi)&&!bag.find(multi),"last use retained");
}
void original(const char* path) {
    PakArchive archive(path);MasterResourceIndex index(parse_adm(archive.read_normalized("media/MASTERRESOURCEUNITS.DAT.ADM")));
    UnitDefinitionLoader loader(archive);auto catalog=AttackEffectCatalog::discover(archive);require(bool(catalog),"original catalog missing");
    unsigned supported=0, unsupported=0;
    for(const auto& r:index.records()) {
        if(r.kind!=MasterResourceKind::item) continue;
        const auto c=load_consumable(archive,*loader.load(r),&*catalog);
        if(!c)continue;
        if(c->unavailable_reason.empty()) { ++supported;validate_consumable(*c); }
        else ++unsupported;
        if(r.name==u"Health Potion") {
            require(c->unavailable_reason.empty() && c->maximum_stack==20 && c->uses==1 && c->dont_use_on_full,"original health potion metadata");
            require(c->level_required==0,"item LEVEL confused with requirement");
            require(c->effects.size()==1 && c->effects[0].duration==4 && c->effects[0].type==124,"original health effect");
            const auto graph=find_named_stat_graph(archive,"HEALTH_PLAYER_GENERIC");require(bool(graph),"original health graph");
            near(c->effects[0].value,(3124.F/100.F)*graph->value(0),"original graph effect value");
        }
    }
    require(supported>=12,"fewer than twelve actual recovery potions supported");
    std::cout<<"original_supported_consumables="<<supported<<" explicitly_unsupported="<<unsupported<<'\n';
}
void process(const char* mode,const char* fixture,const char* directory) {
    test_fixture::World f(fixture);auto proto=hero(f);SaveStore store(directory);
    if(std::string(mode)=="--write") {
        PlayerSession p(proto,7,&f.hierarchy);const auto id=pickup(f,p,u"HP_POTION");static_cast<void>(pickup(f,p,u"HP_POTION"));
        wound(p,60);require(p.use_consumable(id)==ConsumableUse::used && p.update_vitals(.5F),"prepare timed save");
        auto c=checkpoint(p);c.revision=store.write(c);std::cout<<"written_revision="<<c.revision<<'\n';
    } else {
        auto c=store.read("potions",1);auto p=CheckpointAccess::restore_player(proto,c.player,777,&f.hierarchy);
        near(p.health().health(),50,"new-process load healed player");require(p.active_recovery().size()==1,"new-process timer lost");
        near(p.active_recovery()[0].remaining,1.5F,"new-process remaining time changed");
        require(p.inventory().items().back().consumable->count==1,"new-process stack restored wrong");
        require(p.update_vitals(10),"new-process recovery");near(p.health().health(),80,"new-process over-heal");
        require(p.active_recovery().empty(),"new-process stale timer");
    }
}
}
int main(int argc,char**argv) { try {
    if(argc==3 && std::string(argv[1])=="--original")original(argv[2]);
    else if(argc==4)process(argv[1],argv[2],argv[3]);
    else if(argc==2)cycle(argv[1]);else throw std::runtime_error("arguments");
    std::cout<<"checks="<<checks<<" passed\n";return 0;
} catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;} }
