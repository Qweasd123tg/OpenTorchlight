#include "ai_cooldown_fixture.hpp"
#include "torchlight/player_session.hpp"
#include "torchlight/scene_animation.hpp"
#include "torchlight/collision_scene.hpp"
#include "torchlight/save_store.hpp"
#include "torchlight/typed_damage.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
using namespace torchlight;
namespace {
unsigned checks=0;
void require(bool value,const char* message) {++checks;if(!value)throw std::runtime_error(message);}
CollisionScene wall() {
    CollisionScene c;
    c.triangles.push_back({{{{2,-1,-2},{2,3,2},{2,3,-2}}}});
    c.triangles.push_back({{{{2,-1,-2},{2,-1,2},{2,3,2}}}});
    return c;
}
void geometry() {
    auto c=wall();
    require(!collision_segment_clear(c,{0,1,0},{4,1,0}),"wall penetration");
    require(!collision_segment_clear(c,{4,1,0},{0,1,0}),"one-sided collision ray");
    require(collision_segment_clear(c,{0,1,3},{4,1,3}),"missed triangle blocks sight");
    require(collision_segment_clear(c,{0,4,0},{4,4,0}),"over-wall sight blocked");
    require(collision_segment_clear(c,{0,1,0},{1,1,0}),"wall behind target blocks sight");
    require(collision_segment_clear(c,{0,1,0},{2,1,0}),"endpoint contact blocked");
    require(!collision_segment_clear(c,{2,1,-3},{2,1,3}),"coplanar wall penetration");
    require(collision_segment_clear(c,{2,4,-3},{2,4,3}),"distant coplanar wall blocks sight");
    require(collision_segment_clear(c,{0,1,0},{0,1,0}),"empty finite segment blocked");
    auto bad=std::array<float,3>{std::numeric_limits<float>::quiet_NaN(),0,0};
    require(!collision_segment_clear(c,bad,{0,1,0}),"NaN ray accepted");
    c.missing_instances=1;require(!collision_segment_clear(c,{0,1,0},{1,1,0}),"missing geometry silently bypassed");
    c=wall();TorchlightRandom random(42);
    for(int i=0;i<2000;++i){
        const std::array<float,3> a{random.between(-5,5),random.between(-5,5),random.between(-5,5)};
        const std::array<float,3> b{random.between(-5,5),random.between(-5,5),random.between(-5,5)};
        require(collision_segment_clear(c,a,b)==collision_segment_clear(c,b,a),"ray direction changes visibility");
    }
}
PlayerPrototype hero(test_fixture::World& f) {
    const auto players=load_playable_players(f.archive,f.resources,f.definitions);
    for(const auto& p:players)if(p.name==u"TEST_PLAYER")return p;
    throw std::runtime_error("fixture hero missing");
}
InventoryId pickup(test_fixture::World& f,PlayerSession& p,const char16_t* name) {
    require(f.world.consume_spawn_requests({{42,name,u"Items",1}},f.logic).entities_created==1,"weapon not created");
    const auto id=p.pick_up(f.world,f.world.entities().back().id,f.logic);
    require(id!=0,"weapon not picked up");return id;
}
AnimationEventOccurrence player_event(PlayerSession& p,test_fixture::World& f) {
    require(p.combat().update(0,{},f.world).state==CombatState::attacking,"direct shot did not start");
    p.combat().advance_animation(.3F);
    const auto events=p.combat().action().playback().frame_events();
    const auto hit=std::find_if(events.begin(),events.end(),[](const auto& e){return e.key.name=="HIT";});
    require(hit!=events.end(),"ranged HIT absent");return *hit;
}
void cycle(const char* path) {
    geometry();test_fixture::World f(path);f.spawn(u"INNATE");const auto target=f.world.entities()[0].id;
    f.world.find(target)->position={4,0,0};
    auto proto=hero(f);PlayerSession p(proto,42,&f.hierarchy);AttackAnimationCatalog clips(f.archive);
    p.combat().set_animation_resolver([&](auto m,auto prefix){return clips.resolve(m,prefix);});
    const auto weapon=pickup(f,p,u"DIRECT_PISTOL");
    require(p.inventory().find(weapon)->weapon->prototype.delivery==WeaponDelivery::direct_physical,"delivery metadata lost");
    require(p.equip(weapon)==InventoryChange::changed,"pistol not equipped");
    require(p.combat().select_target(f.world,{},10),"ranged target absent");
    require(p.combat().update(0,{},f.world).state==CombatState::unavailable,"ranged starts without collision context");
    bool blocked=false;int rays=0;
    p.combat().set_line_of_sight([&](auto from,auto to){++rays;from[1]+=.8F;to[1]+=.8F;return collision_segment_clear(blocked?wall():CollisionScene{},from,to);});
    const auto before=f.world.find(target)->health;
    auto hit=player_event(p,f);require(f.world.find(target)->health==before&&rays==0,"ranged damage or collision before HIT");
    blocked=true;
    require(p.combat().perform_attack(hit,{},f.world,f.logic).state==CombatState::missed,"wall does not block HIT");
    blocked=false;
    require(p.combat().perform_attack(hit,{},f.world,f.logic).damage==0&&f.world.find(target)->health==before,"blocked HIT replayed");
    p.combat().interrupt_attack();hit=player_event(p,f);
    const auto good=p.combat().perform_attack(hit,{},f.world,f.logic);
    require(good.damage>0&&f.world.find(target)->health<before,"clear ranged shot has no damage");
    require(p.combat().perform_attack(hit,{},f.world,f.logic).damage==0,"ranged duplicate HIT");
    p.combat().interrupt_attack();hit=player_event(p,f);f.world.find(target)->position={30,0,0};
    require(p.combat().perform_attack(hit,{},f.world,f.logic).state==CombatState::missed,"shot hits target outside strike range");
    f.world.find(target)->position={4,0,0};require(p.combat().perform_attack(hit,{},f.world,f.logic).damage==0,"out-of-range HIT replayed");
    p.combat().interrupt_attack();
    for(const auto* name:{u"SKILL_PISTOL",u"SKILL_SWORD"}){
        auto id=pickup(f,p,name);require(p.equip(id)==InventoryChange::changed,"unsupported weapon equip");
        const auto state=CheckpointAccess::capture(p);
        const auto hp=f.world.find(target)->health;
        require(p.combat().update(0,{},f.world).state==CombatState::unavailable,"skill became ordinary attack");
        const auto after=CheckpointAccess::capture(p);
        require(!p.combat().attack_in_progress()&&hp==f.world.find(target)->health&&
                state.combat_random==after.combat_random,"refused weapon started action, damaged or advanced RNG");
    }
    // Missile delivery now owns a real channel (spawn at HIT, damage at
    // impact through the frame runtime): the attack starts like an ordinary
    // one, but update alone deals no damage and fires no missile.
    for(const auto* name:{u"MISSILE_PISTOL",u"MISSILE_SWORD"}){
        auto id=pickup(f,p,name);require(p.equip(id)==InventoryChange::changed,"missile weapon equip");
        const auto hp=f.world.find(target)->health;
        require(p.combat().update(0,{},f.world).state==CombatState::attacking,"missile attack did not start");
        require(p.combat().attack_in_progress()&&hp==f.world.find(target)->health,"update dealt missile damage");
        p.combat().interrupt_attack();
    }
    // Original direct elemental delivery is now implemented, not merely unblocked.
    // Reuse the authored fixture and assert a distinct fire channel, no pre-HIT
    // damage, and one committed HP transaction for a multi-channel HIT.
    for (const auto* name : {u"ELEMENTAL_PISTOL", u"ELEMENTAL_SWORD"}) {
        const auto id=pickup(f,p,name); require(p.equip(id)==InventoryChange::changed,"typed weapon equip");
        const auto* description=&*p.combat().attack_loadout().right;
        require(description->delivery==WeaponDelivery::direct_typed && description->damage_allocation_known &&
            description->damage_bonus[2]>0, "elemental allocation was discarded");
        const auto plan=ordinary_damage_plan(*description,p.combat().attack_loadout(),p.combat().attack_character());
        require(plan.count==2 && plan.channels[1].type==DamageType::fire,"elemental branch became physical only");
        const auto hp=f.world.find(target)->health; auto typed_hit=player_event(p,f);
        require(f.world.find(target)->health==hp,"typed attack damages before HIT");
        const auto applied=p.combat().perform_attack(typed_hit,{},f.world,f.logic);
        require(applied.damage>0 && f.world.find(target)->health==hp-applied.damage,"typed HP transaction");
        require(p.combat().perform_attack(typed_hit,{},f.world,f.logic).damage==0,"typed duplicate HIT");
        p.combat().interrupt_attack();
    }
    const auto sword=pickup(f,p,u"DIRECT_SWORD");
    require(p.equip(sword)==InventoryChange::changed,"direct physical sword equip");
    require(p.combat().update(0,{},f.world).state==CombatState::attacking,"physical sword was overblocked");
    p.combat().interrupt_attack();
    require(p.equip(weapon)==InventoryChange::changed,"reequip pistol");
    for(const auto* name:{u"ENEMY_MISSILE_SWORD",u"ENEMY_SKILL_SWORD"}) {
        test_fixture::World ef(path); ef.spawn(name);
        EnemyController ai(42); PlayerPrototype dummy; dummy.minimum_health=dummy.maximum_health=1000;
        PlayerCombatState victim(dummy,42); ai.set_animation_resolver([&](auto m,auto prefix){return clips.resolve(m,prefix);});
        const auto updates=ai.update(0,{1,0,0},victim,ef.world);
        require(updates.size()==1&&updates[0].state==EnemyAiState::unavailable,"enemy melee bypassed delivery guard");
        require(victim.health()==1000&&ai.action(ef.world.entities()[0].id)&&!ai.action(ef.world.entities()[0].id)->active(),"refused enemy attack changed health/action");
    }
    // v4 metadata is serialized; legacy hydration changes neither rolled damage,
    // HP, weapon instance ID nor RNG. No second random weapon is generated.
    CampaignCheckpoint c;c.slot="ranged";c.class_guid=proto.guid;c.resource_identity=1;c.character_name="Ranged";
    FloorCheckpoint floor;floor.address={u"Town",0};floor.layout_identity=1;c.floors.push_back(floor);
    c.player=CheckpointAccess::capture(p);auto bytes=encode_checkpoint(c);auto saved=decode_checkpoint(bytes);
    require(saved.player.inventory.items[0].weapon->prototype.delivery==WeaponDelivery::direct_physical,"save lost ranged metadata");
    auto old=saved.player;for(auto& i:old.inventory.items)if(i.weapon && i.id==weapon) { i.weapon->prototype.delivery=WeaponDelivery::unverified; i.weapon->prototype.damage_percent.reset(); }
    auto restored=CheckpointAccess::restore_player(proto,old,7,&f.hierarchy);
    restored.hydrate_consumables(f.definitions,f.resources);
    auto current=CheckpointAccess::capture(restored);
    require(current.combat_random==old.combat_random&&current.health==old.health&&current.gold==old.gold,"hydration rerolled/healed");
    require(restored.weapon()->id==weapon&&restored.weapon()->weapon->minimum_damage==p.weapon()->weapon->minimum_damage,"legacy weapon changed");
    require(restored.combat().attack_loadout().right->delivery==WeaponDelivery::direct_physical,"equipped legacy shot not hydrated");
    // Enemy direct attacks use the same collision, HIT consumption and range gate.
    test_fixture::World enemy_world(path);enemy_world.spawn(u"RANGED_DIRECT");auto enemy_id=enemy_world.world.entities()[0].id;
    PlayerPrototype hp;hp.minimum_health=hp.maximum_health=10000;PlayerCombatState health(hp,1);EnemyController enemies(1);
    enemies.set_animation_resolver([&](auto m,auto prefix){return clips.resolve(m,prefix);});
    enemies.set_line_of_sight([&](auto from,auto to){from[1]+=.8F;to[1]+=.8F;return collision_segment_clear(blocked?wall():CollisionScene{},from,to);});
    const std::array<float,3> player{4,0,0};
    require(enemies.update(0,player,health,enemy_world.world).at(0).state==EnemyAiState::attacking,"enemy ranged start");
    enemies.advance_animations(.3F,enemy_world.world,health);hit=enemies.action(enemy_id)->playback().frame_events().at(0);blocked=true;
    require(enemies.perform_attack(enemy_id,hit,player,health,enemy_world.world).state==EnemyAiState::missed,"enemy wall penetration");
    blocked=false;require(enemies.perform_attack(enemy_id,hit,player,health,enemy_world.world).damage==0,"enemy blocked HIT replay");
    enemies.interrupt_attack(enemy_id);require(enemies.update(2,player,health,enemy_world.world).at(0).state==EnemyAiState::attacking,"enemy ranged restart");
    enemies.advance_animations(.3F,enemy_world.world,health);hit=enemies.action(enemy_id)->playback().frame_events().at(0);
    require(enemies.perform_attack(enemy_id,hit,player,health,enemy_world.world).damage>0,"enemy clear shot does not hit");
    require(enemies.perform_attack(enemy_id,hit,player,health,enemy_world.world).damage==0,"enemy duplicated damage");
    p.combat().reset_level_context();p.combat().set_animation_resolver([&](auto m,auto prefix){return clips.resolve(m,prefix);});
    require(p.combat().select_target(f.world,{},10),"floor reset target");
    require(p.combat().update(0,{},f.world).state==CombatState::unavailable,"previous floor collision callback survived reset");
}
void original(const char* path) {
    PakArchive archive(path);
    MasterResourceIndex resources(parse_adm(archive.read_normalized("media/MASTERRESOURCEUNITS.DAT.ADM")));
    UnitDefinitionLoader definitions(archive);SpawnClassCatalog classes(archive);UnitTypeHierarchy hierarchy(archive);
    UnitTypeResourceIndex types(archive,hierarchy,resources,definitions);auto manifest=test_fixture::layout();
    LogicRuntime logic(manifest,42);RuntimeEntityWorld world(manifest,resources,definitions,classes,types,42,1);
    auto players=load_playable_players(archive,resources,definitions);
    auto selected=std::find_if(players.begin(),players.end(),[](const auto& p){return p.starting_weapon && p.starting_weapon->attack_traits.ranged;});
    require(selected!=players.end(),"original ranged class missing");
    require(selected->starting_weapon->delivery==WeaponDelivery::direct_physical,"original starting bow misclassified");
    PlayerSession player(*selected,42,&hierarchy);AttackAnimationCatalog catalog(archive);
    player.combat().set_animation_resolver([&](auto m,auto prefix){return catalog.resolve(m,prefix);});
    bool blocked=false;
    player.combat().set_line_of_sight([&](auto from,auto to){from[1]+=.8F;to[1]+=.8F;return collision_segment_clear(blocked?wall():CollisionScene{},from,to);});
    std::u16string monster;
    for(const auto& r:resources.records())if(r.kind==MasterResourceKind::monster&&!r.do_not_create&&r.unit_type==u"MONSTER"){
        if(world.consume_spawn_requests({{42,r.name,u"Monsters",1}},logic).entities_created==1){monster=r.name;break;}
    }
    require(!monster.empty(),"original ordinary target missing");
    world.entities().back().position={4,0,0};
    const auto target=world.entities().back().id;
    // The exact original model manifest must provide the HIT; no invented timer.
    const auto fire=[&](){
        require(player.combat().select_target(world,{},20),"original ranged target unavailable");
        const auto start=player.combat().update(0,{},world);
        if(start.state!=CombatState::attacking)std::cerr<<player.combat().last_attack_issue()<<'\n';
        require(start.state==CombatState::attacking,"original ranged animation start failed");
        const auto before=world.find(target)->health;
        player.combat().advance_animation(10);
        require(world.find(target)->health==before,"original clip damaged before HIT delivery");
        auto events=player.combat().action().playback().frame_events();int damage=0,hits=0;
        for(const auto& e:events)if(e.key.name=="HIT"){
            ++hits;const auto result=player.combat().perform_attack(e,{},world,logic);damage+=result.damage;
            require(player.combat().perform_attack(e,{},world,logic).damage==0,"original clip HIT duplicated");
        }
        require(hits>0,"original selected ranged manifest has no HIT");
        player.combat().finish_animation_frame();return damage;
    };
    blocked=true;require(fire()==0,"original starting bow shot penetrated test wall");blocked=false;
    require(fire()>0,"original starting bow caused no direct damage");
    // Check data routing across real families. Projectile wands must not become
    // physical direct shots merely because their range is nonzero.
    std::array<unsigned,4> families{};unsigned missiles=0,skills=0,mixed=0;
    for(const auto& r:resources.records())if(r.kind==MasterResourceKind::item&&!r.do_not_create){
        const auto traits=weapon_attack_traits(r.unit_type,hierarchy);
        if(!traits.ranged)continue;
        const auto delivery=load_weapon_delivery(*definitions.load(r));
        if(delivery==WeaponDelivery::missile){++missiles;continue;}
        if(delivery==WeaponDelivery::weapon_skill){++skills;continue;}
        if(delivery==WeaponDelivery::unsupported_damage){++mixed;continue;}
        if(delivery!=WeaponDelivery::direct_physical)continue;
        if(traits.family==WeaponAttackFamily::pistol)++families[0];
        if(traits.family==WeaponAttackFamily::bow)++families[1];
        if(traits.family==WeaponAttackFamily::rifle)++families[2];
        if(traits.family==WeaponAttackFamily::crossbow)++families[3];
    }
    for(auto n:families)require(n>0,"original direct ranged family missing");
    require(missiles>0,"original missile weapons incorrectly accepted as direct");
    std::cout<<"original physical pistol="<<families[0]<<" bow="<<families[1]<<" rifle="<<families[2]
             <<" crossbow="<<families[3]<<" missile="<<missiles<<" skill="<<skills<<" mixed="<<mixed<<'\n';
}
}
int main(int argc,char**argv){try{
    if(argc==3&&std::string(argv[1])=="--original")original(argv[2]);
    else if(argc==2)cycle(argv[1]);else throw std::runtime_error("arguments");
    std::cout<<"ranged checks="<<checks<<" passed\n";return 0;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
