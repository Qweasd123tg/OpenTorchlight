#include "ai_cooldown_fixture.hpp"
#include "torchlight/character_stats.hpp"
#include "torchlight/player_session.hpp"
#include "torchlight/save_store.hpp"
#include "torchlight/scene_animation.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
using namespace torchlight;
namespace {
unsigned checks=0;
void require(bool ok, const char* message) { ++checks; if(!ok) throw std::runtime_error(message); }
PlayerPrototype prototype(test_fixture::World& f) {
    for(const auto& p:load_playable_players(f.archive,f.resources,f.definitions))
        if(p.name==u"STAT_PLAYER") return p;
    throw std::runtime_error("authored stat player absent");
}
InventoryId pickup(test_fixture::World& f, PlayerSession& p, const char16_t* name) {
    require(f.world.consume_spawn_requests({{42,name,u"Items",1}},f.logic).entities_created==1,"stat item spawn");
    auto id=p.pick_up(f.world,f.world.entities().back().id,f.logic); require(id!=0,"stat item pickup"); return id;
}
PlayerSession prepared(test_fixture::World& f, const PlayerPrototype& proto) {
    PlayerSession p(proto,42,&f.hierarchy);
    require(p.health().armor_class()==33,"class flat armor/DEF order");
    const auto id=pickup(f,p,u"STAT_CHEST");
    require(p.equip(id)==InventoryChange::changed,"stat chest equip");
    // base=(UNIT10+item100); +50%=165; +class20+flat7=192;
    // DEF=10+ceil(10*(ALL10+wildcard10)/100)+ceil(2.1)=15;
    // AC=192+ceil(192*15/100)-ceil(1.1)=219. Flat armor is not multiplied.
    require(p.health().armor_class()==219,"equipped effects not used by original physical AC pipeline");
    require(p.health().movement_speed(proto.running_speed)==1.5F,"gear movement effect omitted");
    TorchlightRandom rng(7), expected_rng(7); DamageDefense reference; reference.natural_armor=219;
    const auto expected=mitigate_damage(100,100,DamageType::physical,1,reference,expected_rng);
    const auto damage=p.health().apply_damage(100,100,DamageType::physical,rng);
    require(damage==expected.applied&&damage==1,"cached AC not used by received damage");
    require(p.health().health()==99,"stat recalculation unexpectedly healed");
    return p;
}
CampaignCheckpoint campaign(const PlayerPrototype& proto,const PlayerSession& p) {
    CampaignCheckpoint c;c.slot="stats";c.class_guid=proto.guid;c.resource_identity=1;c.character_name="Stats";
    FloorCheckpoint floor;floor.address={u"Town",0};floor.layout_identity=1;c.floors.push_back(floor);
    c.player=CheckpointAccess::capture(p);return c;
}
void verify_restored(test_fixture::World& f,const PlayerPrototype& proto,const PlayerCheckpoint& saved) {
    auto p=CheckpointAccess::restore_player(proto,saved,987,&f.hierarchy);
    require(p.health().armor_class()==219,"restored armor doubled/lost flat effect");
    require(p.health().movement_speed(proto.running_speed)==1.5F,"restored gear speed missing");
    const auto now=CheckpointAccess::capture(p);
    require(now.health==saved.health&&now.mana==saved.mana&&now.combat_random==saved.combat_random,
            "restore changed vitals/RNG");
    require(now.base_defense.natural_armor==30,"derived armor leaked into stored raw base");
    const auto* chest=p.inventory().equipped(InventorySlot::chest);
    require(chest!=nullptr,"restored chest absent");
    const auto id=chest->id;
    require(p.unequip(id)==InventoryChange::changed,"restored unequip");
    require(p.health().armor_class()==33&&p.health().movement_speed(proto.running_speed)==1,
            "removed stat effects still active");
}
void run(const char* path) {
    require(evaluated_movement_speed(6,-50,50)==4.5F,"slow resistance arithmetic");
    require(evaluated_movement_speed(6,-150,0)==0,"negative speed not clamped");
    require(evaluated_movement_speed(6,50,100)==9,"slow resistance changed a positive bonus");
    bool invalid=false;try{(void)evaluated_movement_speed(6,std::numeric_limits<float>::infinity(),0);}catch(const std::invalid_argument&){invalid=true;}
    require(invalid,"nonfinite stat accepted");
    ActorMotion motion({},1);motion.set_destination(100,0);motion.advance(1);motion.set_speed(1.5F);motion.advance(1);
    require(motion.position()[0]==2.5F&&motion.destination()[0]==100&&motion.moving(),"speed update reset movement");
    motion.set_speed(0);motion.advance(1);require(motion.position()[0]==2.5F&&motion.moving(),"zero speed lost destination");
    motion.set_speed(std::numeric_limits<float>::quiet_NaN());require(motion.speed()==0,"invalid speed committed");
    test_fixture::World f(path);auto proto=prototype(f);auto p=prepared(f,proto);
    const auto prior=encode_checkpoint(campaign(proto,p));const auto bad=pickup(f,p,u"BAD_STAT_CHEST");
    const auto before=encode_checkpoint(campaign(proto,p));invalid=false;
    try{(void)p.equip(bad);}catch(const std::invalid_argument&){invalid=true;}
    require(invalid&&before==encode_checkpoint(campaign(proto,p)),"invalid stat item partially changed equipment/state");
    // Public low-level setters must also leave the old state intact on failure.
    auto direct=p.health();auto invalid_armor=*direct.equipped(ArmorSlot::chest);
    invalid_armor.damage_defense.natural_armor=std::numeric_limits<std::int32_t>::max();
    invalid=false;try{direct.equip(invalid_armor);}catch(const std::invalid_argument&){invalid=true;}
    require(invalid&&direct.armor_class()==219&&direct.equipped(ArmorSlot::chest)->damage_defense.natural_armor==100,
            "low-level failed equip partially committed");
    invalid=false;try{direct.set_defense_attribute(std::numeric_limits<std::int32_t>::max());}catch(const std::invalid_argument&){invalid=true;}
    require(invalid&&direct.armor_class()==219&&direct.health()==p.health().health(),"failed DEF setter changed state");
    verify_restored(f,proto,decode_checkpoint(prior).player);
    // Saved class roll is recovered rather than rerolled using the restore seed.
    auto variable_proto=proto;variable_proto.minimum_armor_bonus=10;variable_proto.maximum_armor_bonus=30;
    PlayerSession variable(variable_proto,44,&f.hierarchy);auto old=CheckpointAccess::capture(variable);
    auto resumed=CheckpointAccess::restore_player(variable_proto,old,999,&f.hierarchy);
    require(resumed.health().armor_class()==variable.health().armor_class(),"restore rerolled innate armor");
    // Real controller movement path, no separate test-only movement implementation.
    test_fixture::World ef(path);ef.spawn(u"MOVEMENT_BONUS");
    const auto id=ef.world.entities()[0].id;EnemyController enemies(1);PlayerCombatState victim(proto,1);
    require(ef.world.find(id)->attack_character.effects.get(0x15)==50,"SAVE metadata discarded constant speed effect");
    auto updates=enemies.update(1,{8,0,0},victim,ef.world);
    require(!updates.empty()&&updates[0].position_changed&&ef.world.find(id)->position[0]==1.5F,"enemy ignored evaluated running speed");
    // A strongly armored monster must receive minimum physical damage at HIT.
    test_fixture::World fight(path);fight.spawn(u"ARMOR_BONUS_MONSTER");const auto target=fight.world.entities()[0].id;
    fight.world.find(target)->position={.5F,0,0};PlayerSession striker(proto,1,&fight.hierarchy);AttackAnimationCatalog clips(fight.archive);
    striker.combat().set_animation_resolver([&](auto m,auto prefix){return clips.resolve(m,prefix);});
    require(striker.combat().select_target(fight.world,{},2),"armored enemy targeting");
    require(striker.combat().update(0,{},fight.world).state==CombatState::attacking,"armored enemy attack start");
    striker.combat().advance_animation(.3F);bool hit=false;
    for(const auto& event:striker.combat().action().playback().frame_events())if(event.key.name=="HIT"){
        const auto result=striker.combat().perform_attack(event,{},fight.world,fight.logic);
        require(result.damage==1,"enemy flat armor effect not applied at HIT");hit=true;
    }
    require(hit,"test hit missing");
}
void original(const char* path) {
    PakArchive pak(path);UnitDefinitionLoader definitions(pak);auto effects=AttackEffectCatalog::discover(pak);
    require(bool(effects),"real effect catalog missing");
    const auto def=definitions.load(u"media/units/monsters/Zombie/ZOMBIEPALE2.DAT");
    const auto values=load_attack_character_values(*def,&*effects);
    require(values.effects.get(0x15)==50,"real constant ZombiePale2 speed ignored due to SAVE");
    require(evaluated_movement_speed(6,values.effects)==9,"real evaluated speed contribution");
    MasterResourceIndex resources(parse_adm(pak.read_normalized("media/MASTERRESOURCEUNITS.DAT.ADM")));
    unsigned players=0;
    for(const auto& p:load_playable_players(pak,resources,definitions)) {
        if(p.minimum_armor_bonus==20&&p.maximum_armor_bonus==20) {
            PlayerSession session(p,42);const auto raw=p.damage_defense.natural_armor;
            const auto expected=evaluated_physical_armor(raw,p.defense,0,20,0);
            require(session.health().armor_class()==expected,"real class innate armor duplicated");++players;
        }
    }
    require(players>=3,"real playable class checks incomplete");
}
}
int main(int argc,char**argv) {try {
    if(argc==2)run(argv[1]);
    else if(argc==3&&std::string(argv[1])=="--original")original(argv[2]);
    else if(argc==4) {
        test_fixture::World f(argv[2]);auto proto=prototype(f);
        if(std::string(argv[1])=="--write") {
            auto p=prepared(f,proto);const auto data=encode_checkpoint(campaign(proto,p));
            std::ofstream out(argv[3],std::ios::binary);out.write(reinterpret_cast<const char*>(data.data()),data.size());
            require(bool(out),"cannot write stat checkpoint");
        } else if(std::string(argv[1])=="--read") {
            std::ifstream in(argv[3],std::ios::binary);require(bool(in),"cannot read stat checkpoint");
            std::vector<std::uint8_t> data((std::istreambuf_iterator<char>(in)),{});
            verify_restored(f,proto,decode_checkpoint(data).player);
        } else throw std::runtime_error("unknown mode");
    } else throw std::runtime_error("arguments");
    std::cout<<"character_stats: "<<checks<<" checks passed\n";return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
