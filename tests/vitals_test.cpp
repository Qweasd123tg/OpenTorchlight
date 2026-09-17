#include "ai_cooldown_fixture.hpp"
#include "torchlight/save_store.hpp"
#include "torchlight/vitals.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace torchlight;
namespace {
std::size_t checks = 0;
void require(bool value, const char* message) {
    ++checks; if (!value) throw std::runtime_error(message);
}
void near(float actual, float expected, const char* message) {
    require(std::abs(actual - expected) <= 0.0001F, message);
}
template<class F> void rejects(F f, const char* message) {
    bool rejected = false;
    try { f(); } catch (const std::invalid_argument&) { rejected = true; }
    catch (const CheckpointError&) { rejected = true; }
    require(rejected, message);
}
void scalar_tests() {
    AttackEffects effects;
    effects.add(0x14,12.5F); effects.add(5,10.2F);
    require(evaluated_maximum_health(100,0,effects)==124,"HP separate ceil contributions");
    require(evaluated_maximum_health(90,10,effects)==124,"HP integer growth lost");
    require(evaluated_maximum_health(-4,0,{})==1,"HP base minimum");
    effects={}; effects.add(0x14,-20); effects.add(5,-.1F);
    require(evaluated_maximum_health(100,0,effects)==80,"negative HP contributions");
    rejects([&]{static_cast<void>(evaluated_maximum_health(std::numeric_limits<int>::max(),1,{}));},"HP base overflow");
    effects.values.front().value=std::numeric_limits<float>::infinity();
    rejects([&]{static_cast<void>(evaluated_maximum_health(100,0,effects));},"infinite HP effect");
    effects={}; effects.add(5,-1000);
    rejects([&]{static_cast<void>(evaluated_maximum_health(100,0,effects));},"unsupported nonpositive HP max");
    // The old math must not be used for HP: locate float32 order discriminators.
    unsigned discriminators=0;
    for (int base=1; base<2000; ++base) {
        for (float percent : {1.F,3.F,7.F,11.F,14.F,28.F,37.F,49.F,53.F,99.F,65.4F,std::nextafter(30.F,100.F)}) {
            effects={}; effects.add(0x14,percent);
            const auto expected=base+static_cast<int>(std::ceil(static_cast<float>(base)*(percent/100.F)));
            require(evaluated_maximum_health(base,0,effects)==expected,"HP division/multiplication order");
            const auto alternative=base+static_cast<int>(std::ceil((static_cast<float>(base)*percent)/100.F));
            if(expected!=alternative)++discriminators;
        }
    }
    require(discriminators>0,"numeric sample never distinguished HP/MANA operation order");
    effects={}; effects.add(7,2); effects.add(0x7c,3); effects.add(0x34,4);
    require(evaluated_health_rate(effects)==1,"positive damage must subtract from regen");
    effects.values.back().value=-4;
    require(evaluated_health_rate(effects)==1,"negative damage must not double-negate");
    effects.add(6,2); effects.add(0x7b,3); effects.add(5,999);
    require(evaluated_mana_rate(effects)==5 && evaluated_health_rate(effects)==1,"max-HP effect confused with recovery");
    require(advance_vital(95,100,10,-5,1)==95,"recovery sources were summed before clamp");
    require(advance_vital(5,100,-10,5,1)==5,"lower-bound clamp ordering");
    require(advance_health(5,100,-10,5,1)==0,"partial regen revived HP after the first source killed");
    require(advance_health(0,100,std::nullopt,99,1)==0,"partial heal revived a dead character");
    require(advance_health(0,100,std::nullopt,100,1)==100,"raw max-heal gate differs from original arithmetic");
    require(!advance_health(0,0,0,0,1),"zero health maximum accepted");
    require(advance_vital(0,100,std::nullopt,2,.5F)==1,"unknown globals disabled known passive effects");
    require(advance_vital(37,100,0,0,1)==37,"explicit zero rate changed state");
    require(advance_vital(37,100,10,5,0)==37,"paused frame changed state");
    for (float bad : {-1.F,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()})
        require(!advance_vital(50,100,1,2,bad),"invalid delta accepted");
    require(!advance_vital(101,100,1,2,1),"invalid input vitals accepted");
    require(!advance_vital(1,100,1,std::numeric_limits<float>::max(),2),"overflow was accepted");
}
void globals_tests() {
    AdmDocument doc; doc.root.name=u"GLOBALS";
    auto rules=parse_vital_recovery_rules(doc);
    require(!rules.health_percent_per_second && !rules.mana_percent_per_second && !rules.pet_health_percent_per_second,
            "missing globals received invented defaults");
    doc.root.properties={{0,u"HP_RECHARGE_RATE",AdmValueType::floating,0.F},
        {0,u"PET_HP_RECHARGE_RATE",AdmValueType::integer,std::int32_t{7}},
        {0,u"MANA_RECHARGE_RATE",AdmValueType::double_precision,10.5}};
    rules=parse_vital_recovery_rules(doc);
    require(rules.health_percent_per_second==0 && rules.pet_health_percent_per_second==7 &&
        rules.mana_percent_per_second==10.5F,"numeric recharge resource values lost");
    doc.root.properties[0].type=AdmValueType::string;doc.root.properties[0].value=std::u16string(u"bad");
    rejects([&]{static_cast<void>(parse_vital_recovery_rules(doc));},"text rate accepted");
    doc.root.properties[0].type=AdmValueType::floating;doc.root.properties[0].value=std::numeric_limits<float>::quiet_NaN();
    rejects([&]{static_cast<void>(parse_vital_recovery_rules(doc));},"NaN rate accepted");
    doc.root.name=u"UNIT";
    rejects([&]{static_cast<void>(parse_vital_recovery_rules(doc));},"wrong globals root accepted");
}
PlayerPrototype hero(test_fixture::World& fixture) {
    const auto players=load_playable_players(fixture.archive,fixture.resources,fixture.definitions);
    const auto found=std::find_if(players.begin(),players.end(),[](const auto& p){return p.name==u"TEST_PLAYER";});
    if(found==players.end()) throw std::runtime_error("authored hero absent");
    return *found;
}
InventoryId pick(test_fixture::World& fixture, PlayerSession& player, const char16_t* name) {
    const auto result=fixture.world.consume_spawn_requests({{42,name,u"Items",1}},fixture.logic);
    require(result.entities_created==1,"vital equipment not spawned");
    const auto id=player.pick_up(fixture.world,fixture.world.entities().back().id,fixture.logic);
    require(id!=0,"vital equipment pickup failed");
    return id;
}
CampaignCheckpoint checkpoint(const PlayerSession& player) {
    CampaignCheckpoint c; c.slot="vitals-test";c.character_name="Vitals Hero";c.class_guid=1;c.resource_identity=1;
    c.player=CheckpointAccess::capture(player);
    FloorCheckpoint f; f.address={u"Town",0};f.layout_identity=1;c.floors.push_back(f);
    return c;
}
void state_tests(const char* file) {
    test_fixture::World f(file);auto proto=hero(f);PlayerSession player(proto,19,&f.hierarchy);
    require(proto.recovery_rules.health_percent_per_second==2.5F && proto.recovery_rules.mana_percent_per_second==10 &&
        proto.recovery_rules.pet_health_percent_per_second==7,"globals not connected to player prototype");
    const auto armor=pick(f,player,u"VITAL_CHEST");
    require(player.equip(armor)==InventoryChange::changed,"cannot equip supported HP armor");
    require(player.health().health()==100 && player.health().maximum_health()==124 && player.health().base_health()==100,
        "equipping armor filled HP or lost base/max separation");
    require(player.health().spend_mana(20),"cannot spend fixture mana");
    require(player.health().update_vitals(1),"valid player recovery rejected");
    near(player.health().health(),106.1F,"resource HP recovery rate/equipment effect");
    near(*player.health().mana(),16.1F,"resource mana recovery rate/equipment effect");
    const auto before=encode_checkpoint(checkpoint(player));
    require(player.health().update_vitals(0),"paused frame rejected");
    require(!player.health().update_vitals(std::numeric_limits<float>::quiet_NaN()),"NaN frame accepted");
    require(encode_checkpoint(checkpoint(player))==before,"paused/invalid frame mutated player");
    const auto invalid=pick(f,player,u"INVALID_HP_CHEST");
    const auto before_invalid=encode_checkpoint(checkpoint(player));
    rejects([&]{static_cast<void>(player.equip(invalid));},"bad health equipment committed");
    require(encode_checkpoint(checkpoint(player))==before_invalid,"failed equip partially updated health/mana/slots");
    require(player.award_experience(403)==2,"vitals test progression failed");
    require(player.health().base_health()==221 && player.health().maximum_health()==260 && player.health().health()==260,
        "level up lost HP effects or did not refill");
    TorchlightRandom random(7);
    static_cast<void>(player.health().apply_damage(100,100,DamageType::physical,random));
    require(player.health().spend_mana(20),"level mana spend");
    auto saved=checkpoint(player);auto bytes=encode_checkpoint(saved);
    require(bytes[8]==kCheckpointFormatVersion && saved.player.base_health==221,"pre-effect base HP not saved in v3");
    auto loaded=CheckpointAccess::restore_player(proto,decode_checkpoint(bytes).player,999,&f.hierarchy);
    require(encode_checkpoint(checkpoint(loaded))==bytes,"load doubled bonus/rerolled base/filled vitals");
    require(loaded.health().update_vitals(.25F) && player.health().update_vitals(.25F),"post-load recovery failed");
    require(encode_checkpoint(checkpoint(loaded))==encode_checkpoint(checkpoint(player)),"recovery diverged after load");
    auto tampered=saved.player;++tampered.maximum_health;
    rejects([&]{static_cast<void>(CheckpointAccess::restore_player(proto,tampered,19,&f.hierarchy));},"mismatched v3 maxHP accepted");
    tampered=saved.player;++*tampered.base_health;
    rejects([&]{static_cast<void>(CheckpointAccess::restore_player(proto,tampered,19,&f.hierarchy));},"mismatched level baseHP accepted");
    require(loaded.unequip(armor)==InventoryChange::changed,"unequip health armor");
    require(loaded.health().maximum_health()==221,"unequipping did not remove HP bonus");
    static_cast<void>(loaded.health().apply_damage(10000,10000,DamageType::physical,random));
    require(!loaded.health().alive(),"fixture player did not die");
    const auto dead=loaded.health().health();
    require(loaded.health().update_vitals(100) && loaded.health().health()==dead,"dead player regenerated");
    EnemyController enemies(1);ActorMotion motion({},1);
    require(loaded.recover_at_entry(enemies,motion,{}).status==RecoveryStatus::recovered && loaded.health().health()==221,
            "explicit death recovery failed after HP effect changes");
    // Lower max HP clamps; removing a penalty never grants a free heal.
    const auto penalty=pick(f,loaded,u"NEGATIVE_HP_CHEST");
    require(loaded.equip(penalty)==InventoryChange::changed,"negative HP equipment rejected");
    require(loaded.health().maximum_health()==166 && loaded.health().health()==166,"lower maxHP failed to clamp health");
    require(loaded.unequip(penalty)==InventoryChange::changed && loaded.health().health()==166 && loaded.health().maximum_health()==221,
        "removing health penalty refilled player");
    // Character effects and weapon/armor effects share the vitals manager.
    PlayerPrototype passive;passive.minimum_health=passive.maximum_health=100;passive.base_mana=31;
    passive.attack_character.effects.add(5,.2F);passive.attack_character.effects.add(0x14,12.5F);
    passive.attack_character.effects.add(7,2);passive.attack_character.effects.add(6,3);
    PlayerCombatState base_effects(passive,1);
    require(base_effects.health()==114 && base_effects.maximum_health()==114,"class HP effects not applied at creation");
    static_cast<void>(base_effects.apply_damage(10,10,DamageType::physical,random));
    require(base_effects.spend_mana(10) && base_effects.update_vitals(1),"class recovery step");
    require(base_effects.health()==106 && base_effects.mana()==24,"class flat recovery missing");
    auto invalid_proto=passive;invalid_proto.maximum_health=std::numeric_limits<float>::quiet_NaN();
    rejects([&]{PlayerCombatState bad(invalid_proto,1);},"NaN range hidden by min/max");
    // Integer HP and its float maximum can differ by rounding even within
    // the checkpoint's 1e9 scalar limit. Preserve the explicit v3 base.
    auto large_proto=passive;large_proto.attack_character.effects={};
    PlayerSession large(large_proto,1);
    constexpr std::int32_t large_base=999999999;
    large.health().set_progression_vitals(large_base,31);
    const auto large_saved=CheckpointAccess::capture(large);
    require(static_cast<double>(large_saved.maximum_health)>large_base,
            "large maxHP case did not distinguish integer base from float maximum");
    auto large_loaded=CheckpointAccess::restore_player(large_proto,large_saved,2);
    require(large_loaded.health().base_health()==large_base &&
            large_loaded.health().maximum_health()==large_saved.maximum_health,
            "v3 lost integer base precision through its float maximum");
    auto invalid_legacy=large_saved;invalid_legacy.base_health.reset();
    invalid_legacy.maximum_health=static_cast<float>(std::numeric_limits<std::int32_t>::max());
    rejects([&]{static_cast<void>(CheckpointAccess::restore_player(large_proto,invalid_legacy,2));},
            "legacy maximum outside the checkpoint scalar limit was accepted");
    // Damage-bearing passives participate in the same signed scalar rate.
    auto hurt=passive;hurt.attack_character.effects={};hurt.recovery_rules={};PlayerSession harmed(hurt,1);
    auto harmful=pick(f,harmed,u"HARMFUL_CHEST");require(harmed.equip(harmful)==InventoryChange::changed,"harmful effect equip");
    require(harmed.health().update_vitals(1) && harmed.health().health()==95.5F,"damage effect sign/rate missing");
    // No arbitrary fallback rates: flat passives still recover without GLOBALS.
    auto no_globals=proto;no_globals.recovery_rules={};PlayerSession unknown(no_globals,1);
    const auto chest=pick(f,unknown,u"VITAL_CHEST");require(unknown.equip(chest)==InventoryChange::changed,"unknown-rate equip");
    require(unknown.health().spend_mana(20) && unknown.health().update_vitals(1),"unknown-rate tick");
    require(unknown.health().health()==103 && unknown.health().mana()==13,"missing rate guessed instead of omitted");
}
void legacy(const char* fixture,const char* save_file) {
    test_fixture::World f(fixture);const auto proto=hero(f);
    std::ifstream stream(save_file,std::ios::binary);
    const std::vector<std::uint8_t> bytes{std::istreambuf_iterator<char>(stream),std::istreambuf_iterator<char>()};
    require(!stream.bad() && bytes.size()>20 && bytes[8]==2,"frozen fixture is not a real v2 payload");
    const auto old=decode_checkpoint(bytes);
    require(!old.player.base_health && old.player.progression,"v2 manufactured base HP/progression");
    auto player=CheckpointAccess::restore_player(proto,old.player,777,&f.hierarchy);
    const bool high=old.player.progression->level==3;
    require(player.health().base_health()==(high?221:100),"v2 migration rerolled the old base");
    require(player.health().maximum_health()==(high?260:124),"v2 migration lost/doubled equipped HP bonus");
    require(player.health().health()==old.player.health && player.health().mana()==old.player.mana && player.gold()==146,
        "v2 migration refilled current vitals or changed wallet");
    require(player.inventory().items().size()==1 && player.inventory().equipped(InventorySlot::chest),"v2 inventory/slot lost");
    auto current=old;current.player=CheckpointAccess::capture(player);
    const auto upgraded=encode_checkpoint(current);
    require(upgraded[8]==kCheckpointFormatVersion,"legacy recapture did not write current version");
    auto again=CheckpointAccess::restore_player(proto,decode_checkpoint(upgraded).player,999,&f.hierarchy);
    current.player=CheckpointAccess::capture(again);
    require(encode_checkpoint(current)==upgraded,"second migration applied HP bonus twice");
    const auto hp=again.health().health();
    require(again.health().update_vitals(.5F),"v2 migrated recovery unavailable");
    near(again.health().health(),hp+((again.health().maximum_health()/100.F)*2.5F+3)*.5F,"v2 lost passive recovery");
}
void process(const char* fixture,const char* directory,bool write) {
    test_fixture::World f(fixture);auto proto=hero(f);SaveStore store(directory);
    if(write) {
        PlayerSession p(proto,9);auto id=pick(f,p,u"VITAL_CHEST");require(p.equip(id)==InventoryChange::changed,"process equip");
        require(p.award_experience(403)==2,"process level up");
        TorchlightRandom random(42);static_cast<void>(p.health().apply_damage(57,57,DamageType::physical,random));
        require(p.health().spend_mana(30),"process mana");
        require(p.health().update_vitals(.25F),"process recovery");
        static_cast<void>(store.write(checkpoint(p)));
    } else {
        auto save=store.read("vitals-test");auto p=CheckpointAccess::restore_player(proto,save.player,999);
        require(p.health().maximum_health()==260 && p.health().base_health()==221,"fresh process maxHP/base mismatch");
        require(CheckpointAccess::capture(p).health==save.player.health && p.health().mana()==save.player.mana,"fresh process refilled vitals");
        const auto hp=p.health().health(),mana=*p.health().mana();
        require(p.health().update_vitals(.5F),"fresh process regen");
        near(p.health().health(),hp+4.75F,"fresh process lost health rate");
        near(*p.health().mana(),mana+3.55F,"fresh process lost mana rate");
    }
}
}
int main(int argc,char** argv) {
    try {
        if(argc==2 && std::string(argv[1])=="--numeric") {scalar_tests();globals_tests();}
        else if(argc==2) state_tests(argv[1]);
        else if(argc==4 && std::string(argv[1])=="--legacy") legacy(argv[2],argv[3]);
        else if(argc==5 && std::string(argv[1])=="--process") process(argv[2],argv[3],std::string(argv[4])=="write");
        else throw std::runtime_error("usage: vitals_test --numeric | fixture | --process fixture savedir write|read");
        std::cout<<"PASS: "<<checks<<" authored vitals checks; not original ELF execution\n";
    } catch(const std::exception& e) {std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
