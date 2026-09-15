#include "ai_cooldown_fixture.hpp"
#include "torchlight/player_session.hpp"
#include "torchlight/scene_animation.hpp"
#include "torchlight/level_transition.hpp"
#include "torchlight/original_combat_inputs.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <type_traits>

using namespace torchlight;
namespace {
std::size_t checks=0;
void require(bool v,const char* message) {++checks;if(!v)throw std::runtime_error(message);}
void near(float a,float b,const char* message) {require(std::fabs(a-b)<0.00001F,message);}
PlayerPrototype prototype(test_fixture::World& f) {
    return load_playable_players(f.archive,f.resources,f.definitions).front();
}
void kill_player(PlayerCombatState& player) {
    TorchlightRandom random(71);
    static_cast<void>(player.apply_damage(1000000,1000000,DamageType::physical,random));
    require(!player.alive(),"fixture player did not die");
}

void original_inputs(const char* path) {
    test_fixture::World f(path);
    const auto catalog=AttackEffectCatalog::discover(f.archive);
    require(catalog && catalog->find(u"FIXTURE_HASTE")==0x16,"exact effect catalog lost to decoy");
    require(catalog->find(u"FIXTURE_MANA_PERCENT")==0x13 && catalog->find(u"FIXTURE_MANA_FLAT")==4,
        "mana effect ordinals incorrect");
    f.spawn(u"DEFAULT_RANGES");
    auto& e=f.world.entities().front();
    require(e.attacks.innate.size()==1,"default innate description missing");
    const auto& d=e.attacks.innate.front();
    near(d.range,.375F,"wrong original innate range default");
    near(d.strike_range,.5F,"wrong original innate strike default");
    require(d.unavailable_reason.empty(),"missing optional defaults still deny attack");
    AttackAnimationCatalog clips(f.archive);
    PlayerCombatState player(prototype(f),1);
    EnemyController enemies(1);
    enemies.set_animation_resolver([&](std::string_view m,std::string_view p){return clips.resolve(m,p);});
    require(enemies.update(0,{},player,f.world).front().state==EnemyAiState::attacking,
        "default-range monster unable to begin attack");
    enemies.advance_animations(.3F,f.world,player);
    const auto hit=enemies.action(e.id)->playback().frame_events().front();
    require(enemies.perform_attack(e.id,hit,{},player,f.world).damage>0,"default-range HIT did not execute");
    bool rejected=false;
    try {f.spawn(u"BAD_RANGE");} catch(const std::exception&) {rejected=true;}
    require(rejected,"explicit malformed range treated as an absent default");

    for(bool flag:{false,true}) {
        AttackEffects slowed;slowed.add(0x16,-1000);
        near(ordinary_attack_speed(1,slowed,flag),flag?.3F:.2F,"AI flag must multiply after minimum clamp");
        near(ordinary_attack_speed(2,{},flag),flag?.75F:.5F,"AI flag factor or weapon denominator wrong");
    }
    for(bool ranged:{false,true}) {
        for(float y:{-2.5F,2.5F})
            require(within_character_attack_reach({}, {0,y,0},.25F,.25F,.5F,ranged),"vertical boundary excluded");
        for(float y:{std::nextafter(2.5F,3.0F),std::nextafter(-2.5F,-3.0F),100.0F})
            require(within_character_attack_reach({}, {0,y,0},.25F,.25F,.5F,ranged)==ranged,
                "vertical cutoff leaked or applied to ranged");
        require(!within_character_attack_reach({}, {5,0,0},.25F,.25F,.5F,ranged),"horizontal range ignored");
        require(!within_character_attack_reach({}, {0,std::numeric_limits<float>::quiet_NaN(),0},0,0,1,ranged),
            "nonfinite geometry accepted");
    }
    AttackLoadout mixed;AttackDescription melee,ranged;ranged.traits.ranged=true;
    mixed.right=melee;mixed.left=ranged;
    require(has_ranged_weapon(mixed),"left ranged hand lost in approach test");
    mixed.left.reset();require(!has_ranged_weapon(mixed),"removed ranged hand still affects height");
    mixed.right=ranged;require(has_ranged_weapon(mixed),"right ranged hand lost in approach test");
}

void flag_and_vertical_delivery(const char* path) {
    for(bool flag:{false,true}) {
        test_fixture::World f(path);f.spawn(u"ARMED");
        auto& entity=f.world.entities().front();entity.attack_character.ai_flag_one=flag;
        const auto id=entity.id;
        AttackAnimationCatalog clips(f.archive);EnemyController enemies(1);
        enemies.set_animation_resolver([&](std::string_view m,std::string_view p){return clips.resolve(m,p);});
        PlayerCombatState player(prototype(f),1);
        require(enemies.update(0,{},player,f.world).front().state==EnemyAiState::attacking,"flag action failed");
        near(enemies.action(id)->playback().playback_speed(),flag?.75F:.5F,"runtime did not forward evaluated AI flag");
        entity.attack_character.ai_flag_one=!flag;
        near(enemies.action(id)->playback().playback_speed(),flag?.75F:.5F,"flag change rewrote launched clock");
        enemies.advance_animations(.5F,f.world,player);
        const auto event=enemies.action(id)->playback().frame_events().front();
        const auto hp=player.health();
        require(enemies.perform_attack(id,event,{0,3,0},player,f.world).state==EnemyAiState::missed,
            "enemy melee hit through vertical separation");
        require(enemies.perform_attack(id,event,{},player,f.world).damage==0 && player.health()==hp,
            "height miss left a replayable HIT");
    }
    test_fixture::World f(path);f.spawn(u"INNATE");const auto id=f.world.entities().front().id;
    AttackAnimationCatalog clips(f.archive);PlayerSession session(prototype(f),1,&f.hierarchy);
    session.combat().set_animation_resolver([&](std::string_view m,std::string_view p){return clips.resolve(m,p);});
    require(session.combat().select_target(f.world,{},1),"target selection failed");
    require(session.combat().update(0,{},f.world).state==CombatState::attacking,"player height fixture start");
    session.combat().advance_animation(.2F);const auto e=session.combat().action().playback().frame_events().front();
    f.world.find(id)->position[1]=3;
    require(session.combat().perform_attack(e,{},f.world,f.logic).damage==0,"player hits upward too far");
    f.world.find(id)->position[1]=0;
    require(session.combat().perform_attack(e,{},f.world,f.logic).damage==0,"player vertical miss replayed");
}

void mana_and_wallet(const char* path) {
    test_fixture::World f(path);auto p=prototype(f);
    require(p.base_mana && *p.base_mana==31,"MANA_GRAPH default/ceil not loaded");
    require(p.starting_gold==109,"UNIT GOLD missing");
    PlayerSession session(p,1,&f.hierarchy);require(session.gold()==109,"session initial gold");
    require(session.health().mana()==31 && session.health().maximum_mana()==31,"initial mana");
    require(session.health().spend_mana(10) && session.health().mana()==21,"mana spending");
    for(float amount:{-1.0F,22.0F,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()})
        require(!session.health().spend_mana(amount) && session.health().mana()==21,"invalid spend changed mana");
    auto spawn=f.world.consume_spawn_requests({{42,u"MANA_CHEST",u"Items",1}},f.logic);
    require(spawn.entities_created==1,"mana armor not spawned");
    const auto id=session.pick_up(f.world,f.world.entities().back().id,f.logic);
    require(id && session.equip(id)==InventoryChange::changed,"mana armor not equipped");
    require(session.health().maximum_mana()==36 && session.health().mana()==21,"mana effect order/current preservation");
    for(int i=0;i<32;++i) {
        require(session.unequip(id)==InventoryChange::changed && session.health().maximum_mana()==31,"mana removal");
        require(session.equip(id)==InventoryChange::changed && session.health().maximum_mana()==36,"mana bonus accumulated");
        require(session.health().mana()==21,"equipping restored spent mana");
    }
    require(f.world.consume_spawn_requests({{42,u"INVALID_MANA_CHEST",u"Items",1}},f.logic).entities_created==1,
        "invalid-stat fixture missing");
    const auto invalid_id=session.pick_up(f.world,f.world.entities().back().id,f.logic);
    const auto armor_before=session.health().armor_class();const auto damage_before=session.combat().maximum_damage();
    bool rejected=false;try {static_cast<void>(session.equip(invalid_id));}catch(const std::invalid_argument&){rejected=true;}
    require(rejected && session.inventory().equipped(InventorySlot::chest)->id==id &&
        session.health().armor_class()==armor_before && session.combat().maximum_damage()==damage_before &&
        session.health().maximum_mana()==36 && session.health().mana()==21,
        "failed mana evaluation partially changed live equipment/stat state");
    require(session.inventory().find(invalid_id)!=nullptr,"rejected item disappeared from bag");
    session.enter_level();require(session.health().mana()==21,"floor entry refilled mana");
    ActorMotion motion({},1);EnemyController enemies(1);kill_player(session.health());
    require(!session.health().spend_mana(0),"dead actor may consume mana");
    require(session.recover_at_entry(enemies,motion,{}).status==RecoveryStatus::recovered,"mana recovery failed");
    require(session.health().mana()==36 && session.gold()==99,"recovery did not refill evaluated mana/pay fee");
    require(session.unequip(id)==InventoryChange::changed && session.health().mana()==31,"mana not clamped to lower capacity");
    session.give_gold(std::numeric_limits<std::int32_t>::max());
    require(session.gold()==std::numeric_limits<std::int32_t>::max(),"positive gold overflow");
    session.give_gold(std::numeric_limits<std::int32_t>::min());require(session.gold()==0,"negative gold clamp");
    p.base_mana.reset();PlayerSession unknown(p,1);require(!unknown.health().mana() && !unknown.health().spend_mana(0),"unknown mana fabricated");
}

void death_continuation(const char* path) {
    test_fixture::World f(path);f.spawn(u"ARMED");f.spawn(u"ARMED");f.spawn(u"INNATE");
    std::vector<std::uint64_t> ids;for(const auto& e:f.world.entities())ids.push_back(e.id);
    const auto corpse=ids.back();require(f.world.kill(corpse,f.logic),"dead-world fixture failed");
    static_cast<void>(f.world.resolve_death_loot(f.logic));
    auto p=prototype(f);PlayerSession session(p,9,&f.hierarchy);EnemyController enemies(9);AttackAnimationCatalog clips(f.archive);
    auto resolver=[&](std::string_view m,std::string_view family){return clips.resolve(m,family);};
    enemies.set_animation_resolver(resolver);session.combat().set_animation_resolver(resolver);
    const auto spawn=f.world.consume_spawn_requests({{42,u"SWORD",u"Items",1}},f.logic);
    require(spawn.entities_created==1,"persistent sword missing");
    const auto iid=session.pick_up(f.world,f.world.entities().back().id,f.logic);
    require(iid && session.equip(iid)==InventoryChange::changed,"persistent sword not equipped");
    const auto damage=session.weapon()->weapon->maximum_damage;
    const auto count=f.world.entities().size();
    const auto world_hp=f.world.find(ids[0])->health;
    ActorMotion motion({0,0,0},1);motion.set_destination(100,100);
    require(session.combat().select_target(f.world,{},1),"pending target selection failed");
    require(session.combat().update(0,{},f.world).state==CombatState::attacking,"player pending action missing");
    session.combat().advance_animation(.5F);const auto stale_player=session.combat().action().playback().frame_events().front();
    require(enemies.update(0,{},session.health(),f.world).size()==2,"multiple actor fixture missing");
    enemies.advance_animations(.5F,f.world,session.health());
    std::vector<AnimationEventOccurrence> stale;
    for(std::size_t i=0;i<2;++i) {
        require(enemies.action(ids[i]) && enemies.action(ids[i])->active(),"multiple enemy attack not pending");
        stale.push_back(enemies.action(ids[i])->playback().frame_events().front());
    }
    const auto cooldown=enemies.ai_cooldown_remaining(ids[0]);
    const std::array<float,3> anchor{25,2,30};
    kill_player(session.health());
    const auto recovery=session.recover_at_entry(enemies,motion,anchor);
    require(recovery.status==RecoveryStatus::recovered && recovery.gold_lost==10,"entry recovery fee or status");
    require(motion.position()==anchor && !motion.moving(),"old navigation resumed after recovery");
    require(session.health().health()==session.health().maximum_health() && session.health().mana()==31,"vitals not restored");
    require(f.world.entities().size()==count && !f.world.find(corpse)->alive && f.world.find(ids[0])->health==world_hp,
        "recovery rebuilt or healed enemy world");
    require(session.inventory().items().size()==1 && session.weapon()->id==iid && session.weapon()->weapon->maximum_damage==damage,
        "recovery changed item instance or rerolled weapon");
    require(!session.combat().attack_in_progress() && session.combat().target_id()==0,"player action/target survived reset");
    require(session.combat().perform_attack(stale_player,{},f.world,f.logic).damage==0,"old player HIT survived recovery");
    require(enemies.alerted_count()==0,"enemy target state survived restart");
    near(enemies.ai_cooldown_remaining(ids[0]),cooldown,"restart erased independent AI clock");
    for(std::size_t i=0;i<2;++i)
        require(!enemies.action(ids[i])->active() && enemies.perform_attack(ids[i],stale[i],{},session.health(),f.world).damage==0,
            "queued enemy HIT survived recovery");
    require(session.recover_at_entry(enemies,motion,{}).status==RecoveryStatus::alive && session.gold()==99 && motion.position()==anchor,
        "repeated recovery charged or moved living player");
    require(session.combat().select_target(f.world,{},1),"pending target selection failed");require(session.combat().update(0,{},f.world).state==CombatState::attacking,
        "restart erased player's live clip resolver");
    // The same IDs/controller remain live; old occurrences must still not alias a new action.
    require(session.combat().perform_attack(stale_player,{},f.world,f.logic).damage==0,"stale player HIT aliases new execution");
    static_cast<void>(enemies.update(cooldown,{},session.health(),f.world));
    for(std::size_t i=0;i<2;++i) {
        require(enemies.action(ids[i])->active(),"enemy unable to resume after reset");
        require(enemies.perform_attack(ids[i],stale[i],{},session.health(),f.world).damage==0,"old enemy HIT aliases new action");
    }
    // Repeat with the same floor, inventory, ID space and controllers.
    for(int i=0;i<64;++i) {
        kill_player(session.health());const auto gold=session.gold();
        const auto result=session.recover_at_entry(enemies,motion,anchor);
        require(result.status==RecoveryStatus::recovered && session.gold()==gold-gold/10,"repeated-cycle fee drift");
        require(f.world.entities().size()==count && !f.world.find(corpse)->alive && session.weapon()->id==iid,
            "repeated cycle resurrected floor/replaced inventory");
    }
    kill_player(session.health());const auto gold=session.gold();
    require(session.recover_at_entry(enemies,motion,{std::numeric_limits<float>::quiet_NaN(),0,0}).status==RecoveryStatus::invalid_anchor &&
        session.gold()==gold && !session.health().alive(),"invalid destination partially committed revival");
    p.hardcore=true;PlayerSession hardcore(p,9);kill_player(hardcore.health());
    require(hardcore.recover_at_entry(enemies,motion,{}).status==RecoveryStatus::hardcore && hardcore.gold()==109 && !hardcore.health().alive(),
        "hardcore character resurrected");
}

AdmProperty text_property(const char16_t* name,const char16_t* value) {
    AdmProperty p;p.name=name;p.type=AdmValueType::string;p.value=std::u16string(value);return p;
}
void recovery_anchor() {
    LayoutManifest layout;
    LayoutObject marker;marker.id=1;marker.descriptor=u"Property Node";marker.position_x=1;marker.position_y=0;marker.position_z=2;
    marker.properties.push_back(text_property(u"TYPE",u"Entrance"));layout.objects.push_back(marker);
    LayoutObject warp;warp.id=2;warp.descriptor=u"Warper";warp.name=u"BACK";warp.position_x=40;warp.position_y=0;warp.position_z=50;layout.objects.push_back(warp);
    LevelEntryRequest entry;entry.source={u"MAIN",1};entry.destination={u"MAIN",2};entry.warp.level_delta=1;entry.warp.warp_name=u"BACK";
    const auto arrived=find_same_dungeon_level_arrival(layout,entry);
    const auto anchor=find_same_dungeon_entry_anchor(layout,entry);
    require(arrived && arrived->marker_id==2 && anchor && anchor->marker_id==1,"entry anchor overwritten by matched Warper");
    require(arrived->position==std::array<float,3>{40,0,50} && anchor->position==std::array<float,3>{1,0,2},"anchor transform incorrect");
}
}
int main(int argc,char**argv) {
    try {if(argc!=2)return 2;original_inputs(argv[1]);flag_and_vertical_delivery(argv[1]);mana_and_wallet(argv[1]);
        death_continuation(argv[1]);recovery_anchor();
        std::cout<<"PASS: "<<checks<<" gameplay continuation assertions (authored resources, no original runtime)\n";
        return 0;
    }catch(const std::exception& e){std::cerr<<"FAIL after "<<checks<<": "<<e.what()<<'\n';return 1;}
}
