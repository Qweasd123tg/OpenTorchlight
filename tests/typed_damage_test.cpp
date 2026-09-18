#include "ai_cooldown_fixture.hpp"
#include "torchlight/typed_damage.hpp"
#include "torchlight/save_store.hpp"
#include "torchlight/scene_animation.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace torchlight;
namespace {
unsigned checks=0;
void require(bool condition, const char* message) { ++checks; if (!condition) throw std::runtime_error(message); }
template<class F> void rejects(F f, const char* message) {
    bool rejected=false; try { f(); } catch (const std::exception&) { rejected=true; } require(rejected,message);
}
AttackDescription poison() {
    AttackDescription a; a.hand=AttackHand::right; a.delivery=WeaponDelivery::direct_typed;
    a.damage_allocation_known=true; a.damage_bonus[5]=10; return a;
}
void numeric() {
    std::array<std::int32_t,7> split{50,0,50,0,0,0,0};
    const auto allocated=allocate_weapon_damage(49,split);
    require(allocated.physical==24 && allocated.bonus[2]==24,"allocation normalized or rounded up");
    split[0]=-1;split[2]=-100;
    const auto implicit=allocate_weapon_damage(49,split);
    require(implicit.physical==49 && implicit.bonus[2]==0,"negative/default percentage branch");
    split[1]=1; rejects([&]{static_cast<void>(allocate_weapon_damage(49,split));},"invented generic allocation");

    AttackCharacterValues c; c.strength=5;c.magic=10;c.magic_known=true;
    AttackLoadout loadout;loadout.right=poison();const auto& a=*loadout.right;
    auto plan=ordinary_damage_plan(a,loadout,c);
    require(plan.count==2 && plan.maximum==12 && plan.minimum==6 && plan.channels[0].maximum==0 &&
        plan.channels[1].type==DamageType::poison,"base/poison plan disagrees with original sample");
    TorchlightRandom random(1);
    auto hit=roll_ordinary_damage(a,loadout,c,{},random);
    // Frozen original-instruction sample, also checked in the differential suite.
    require(hit.maximum==12 && hit.rolled==9 && hit.applied==10 && hit.channels[0].applied==1 &&
        hit.channels[1].applied==9 && random.state()==UINT64_C(695696193),"original zero-base/poison sample");
    c.magic=110;require(ordinary_damage_plan(a,loadout,c).maximum==22,"MAGIC not connected to elemental weapon");
    c.magic=10;
    EvaluatedDamageDefense resistance;resistance.percent_taken[5]=-50;
    TorchlightRandom reduced_rng(1);hit=roll_ordinary_damage(a,loadout,c,resistance,reduced_rng);
    require(hit.channels[0].applied==1 && hit.channels[1].applied==4,"typed percent damage taken stage");
    resistance.percent_taken[5]=0;resistance.maximum[5]=100000;
    TorchlightRandom immune_rng(1);hit=roll_ordinary_damage(a,loadout,c,resistance,immune_rng);
    require(hit.applied==1 && hit.channels[1].applied==0,"elemental absorption borrowed physical minimum");
    DamageDefense raw;raw.elemental_armor[5]=13;raw.defense_attribute=25;
    AttackEffects e;e.add(0x17,20.5F,5);e.add(40,0.2F);e.add(0x42,1.1F);
    const auto evaluated=evaluate_damage_defense(raw,e);
    require(evaluated.maximum[5]==18 && evaluated.maximum[2]==0,"fractional elemental armor bucket");
    e.add(0x1a,-20.1F,5);e.add(0x1a,3.2F,6);
    const auto percent=evaluate_damage_defense(raw,e);
    require(percent.percent_taken[5]==-16 && percent.percent_taken[2]==4,"ceil of combined typed/all resistance");
    AttackEffects magic;magic.add(0x12,30);magic.add(3,0.1F);
    require(evaluated_magic(10,magic)==14,"MAGIC uses wrong percent/flat ceilings");
    auto unavailable=a;unavailable.delivery=WeaponDelivery::missile;
    const auto before=random.state();rejects([&]{static_cast<void>(roll_ordinary_damage(unavailable,loadout,c,{},random));},"missile became direct typed hit");
    require(random.state()==before,"unsupported delivery consumed randomness");
    c.effects.add(0x19,1.0e30F,5);
    rejects([&]{static_cast<void>(roll_ordinary_damage(a,loadout,c,{},random));},"invalid evaluated damage accepted");
    require(random.state()==before,"invalid plan consumed randomness");
}
void enemy_cycle(const char* path) {
    test_fixture::World f(path);f.spawn(u"ENEMY_ELEMENTAL_SWORD");
    const auto id=f.world.entities().front().id;
    require(f.world.entities().front().attacks.right && f.world.entities().front().attacks.right->damage_bonus[2]>0,
        "enemy lost inherited weapon allocation");
    PlayerPrototype proto;proto.minimum_health=proto.maximum_health=1000;
    proto.damage_defense.natural_armor=100000;
    PlayerCombatState player(proto,31);EnemyController ai(31);AttackAnimationCatalog clips(f.archive);
    ai.set_animation_resolver([&](auto mesh,auto prefix){return clips.resolve(mesh,prefix);});
    require(ai.update(0,{1,0,0},player,f.world).at(0).state==EnemyAiState::attacking,"typed enemy did not begin animation");
    require(player.health()==1000,"enemy damaged before HIT");
    ai.advance_animations(.3F,f.world,player);
    const auto events=ai.action(id)->playback().frame_events();
    const auto found=std::find_if(events.begin(),events.end(),[](const auto& event){return event.key.name=="HIT";});
    require(found!=events.end(),"fixture HIT missing");
    const auto hit=ai.perform_attack(id,*found,{1,0,0},player,f.world);
    require(hit.damage>1 && player.health()==1000-hit.damage,"enemy used physical armor for fire or committed HP twice");
    require(ai.perform_attack(id,*found,{1,0,0},player,f.world).damage==0,"enemy replayed composite HIT");
    AttackEffects e;e.add(0x1a,-100,2);player.set_equipment_vital_effects(e);
    require(player.evaluated_damage_defense().percent_taken[2]==-100,"equipment resistance not connected");
    const auto hp=player.health();const auto ac=player.armor_class();
    e.add(37,1e30F);
    rejects([&]{player.set_equipment_vital_effects(e);},"invalid resistance update accepted");
    require(player.health()==hp && player.armor_class()==ac && player.evaluated_damage_defense().percent_taken[2]==-100,
        "failed effects update changed live vitals/defense");
}
void metadata(const char* path) {
    test_fixture::World f(path);f.spawn(u"ENEMY_ELEMENTAL_SWORD");
    const auto* record=f.resources.find(f.world.entities().front().attacks.right->source_guid);
    require(record!=nullptr,"fixture weapon resource absent");
    const auto definition=f.definitions.load(*record);
    WeaponItem old;old.prototype.guid=record->guid;old.prototype.delivery=WeaponDelivery::unsupported_damage;
    old.maximum_damage=49;old.minimum_damage=25;
    hydrate_weapon_damage(old,*definition);
    require(old.maximum_damage==24 && old.damage_bonus[2]==24 && old.prototype.damage_percent &&
        old.prototype.delivery==WeaponDelivery::direct_typed,"legacy graph roll migration");
    hydrate_weapon_damage(old,*definition);
    require(old.maximum_damage==24 && old.damage_bonus[2]==24,"migration applied percentages twice");
    auto attack=describe_weapon_attack(old,AttackHand::right);
    hydrate_attack_damage(attack,*definition);
    require(attack.maximum_damage==24 && attack.damage_bonus[2]==24 && ordinary_delivery_supported(attack),"resolved description was re-split");
    attack.damage_allocation_known=false;
    require(!ordinary_delivery_supported(attack),"typed descriptor enabled before allocation hydration");
}
} // namespace
int main(int argc,char**argv) {
    try {
        if (argc!=2) throw std::invalid_argument("typed_damage_test authored-ranged.pak.zip");
        numeric();enemy_cycle(argv[1]);metadata(argv[1]);
        std::cout<<"PASS: "<<checks<<" typed damage, transaction, metadata and enemy-HIT checks\n";
    } catch(const std::exception& e) { std::cerr<<e.what()<<'\n';return 1; }
}
