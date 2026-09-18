#include "ai_cooldown_fixture.hpp"
#include "attack_fixture.hpp"
#include "torchlight/player_session.hpp"
#include "torchlight/scene_geometry.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace torchlight;
namespace {
std::size_t checks=0;
void require(bool value,const char* message) { ++checks; if(!value)throw std::runtime_error(message); }
PlayerPrototype prototype() {
    PlayerPrototype p;
    p.minimum_health=p.maximum_health=200;
    p.minimum_damage=p.maximum_damage=2;
    p.damage_defense.natural_armor=3;
    p.reach_bonus=0.5F;
    return p;
}
std::uint64_t named_entity(const RuntimeEntityWorld& world, const char16_t* name) {
    for(const auto& e:world.entities()) if(e.name==name && e.kind==MasterResourceKind::item) return e.id;
    throw std::runtime_error("Expected loot not generated");
}
InventoryId named_item(const PlayerSession& session,const char16_t* name) {
    for(const auto& i:session.inventory().items()) if(i.name==name) return i.id;
    throw std::runtime_error("Expected inventory item not stored");
}
void synthetic(const char* path) {
    test_fixture::World f(path,u"EXPLICIT");
    const auto corpse=f.world.entities().front().id;
    auto* monster=f.world.find(corpse);
    monster->position={10,2,30};
    require(f.world.resolve_death_loot(f.logic).deaths==0,"no phantom death");
    require(!f.world.apply_damage(corpse,1,f.logic).killed,"nonlethal damage");
    require(f.world.pending_loot_count()==0,"nonlethal no loot");
    require(f.world.apply_damage(corpse,10000,f.logic).killed,"lethal damage");
    require(f.world.entities().size()==1,"damage must not invalidate vector pointers");
    require(!f.world.kill(corpse,f.logic),"repeat death rejected");
    require(!f.world.apply_damage(corpse,10000,f.logic).accepted,"corpse damage rejected");
    const auto loot=f.world.resolve_death_loot(f.logic);
    require(loot.deaths==1 && loot.class_rolls==1,"one death one table invocation");
    require(loot.spawns.entities_created==6,"nested classes and mandatory leaves");
    require(loot.spawns.resolved_unit_types==1,"UNITTYPE uses hierarchy and level");
    require(f.world.resolve_death_loot(f.logic).deaths==0,"drain idempotent");
    FixedSceneGeometry geometry;
    PlayerSession session(prototype(),3,&f.hierarchy);
    std::vector<std::uint64_t> ids;
    for(const auto& e:f.world.entities()) {
        if(e.kind!=MasterResourceKind::item) continue;
        require(e.position==std::array<float,3>{10,2,30},"loot uses source position");
        require(e.loot_source_id==corpse && e.spawner_id==0,"loot ownership independent");
        require(e.inventory_eligible,"equipment eligible for bag");
        require(!e.mesh_path.empty(),"original-style UNIT model path retained");
        const auto instance=append_runtime_entity_geometry(f.archive,f.resources,f.definitions,e,geometry);
        require(instance.has_value(),"ground model loads");
        require(geometry.instances[*instance].transform.position==e.position,"model at loot position");
        require(geometry.meshes[geometry.instances[*instance].mesh_index].mesh.submeshes.at(0).indices.size()==3,
                "synthetic triangle is parsed, not a placeholder string");
        ids.push_back(e.id);
    }
    for(const auto id:ids) {
        const auto inventory_id=session.pick_up(f.world,id,f.logic);
        require(inventory_id!=0,"transfer to inventory");
        require(session.pick_up(f.world,id,f.logic)==0,"duplicate pickup rejected");
        require(!f.world.find(id)->alive && !f.world.find(id)->visible,"world instance retired");
    }
    require(session.inventory().items().size()==6,"bag owns all six distinct instances");
    require(session.health().armor_class()==3 && session.combat().maximum_damage()==2,"pickup does not auto-equip");
    const auto a=named_item(session,u"SWORD_A"), b=named_item(session,u"SWORD_B");
    const auto chest_a=named_item(session,u"CHEST_A"), chest_b=named_item(session,u"CHEST_B");
    const auto belt=named_item(session,u"BELT"), token=named_item(session,u"TOKEN");
    require(session.equip(a)==InventoryChange::changed,"equip first weapon");
    require(session.combat().maximum_damage()==20,"weapon damage from stored roll");
    require(session.combat().attack_playback_speed()==2,"weapon SPEED drives playback");
    require(std::abs(session.combat().attack_range()-2.7F)<0.00001F,"weapon RANGE drives reach");
    require(session.equip(b)==InventoryChange::changed,"replace weapon");
    require(session.combat().maximum_damage()==40 && session.combat().attack_playback_speed()==0.5F,"second roll and speed");
    require(std::abs(session.combat().attack_range()-4.7F)<0.00001F,"new range");
    require(session.equip(chest_a)==InventoryChange::changed,"equip first armor");
    require(session.health().armor_class()==13,"armor adds to base");
    require(session.equip(belt)==InventoryChange::changed,"other slot armor");
    require(session.health().armor_class()==18,"other armor combines");
    require(session.equip(chest_b)==InventoryChange::changed,"replace chest");
    // original-code setGraphAC divides percent before multiplying: in binary32
    // ceil(100 * (30 / 100)) = 31, not the old reassociated result 30.
    require(session.inventory().find(chest_b)->armor->armor==31,"original graph rounding for chest B");
    require(session.health().armor_class()==39,"replacement not cumulative stacking");
    require(session.equip(chest_b)==InventoryChange::unchanged && session.health().armor_class()==39,"idempotent defense");
    require(session.equip(token)==InventoryChange::unsupported,"unknown effects are not invented");
    // A selected model can be attached from the stored item, including after travel.
    auto equipped_visual = prototype();
    equipped_visual.starting_weapon = session.weapon()->weapon->prototype;
    const auto held = append_player_weapon_geometry(f.archive,equipped_visual,{0,0,0},geometry);
    require(held.has_value(), "selected weapon mesh can be attached from inventory instance");
    TorchlightRandom hit_random(2);
    require(session.health().apply_damage(100,100,DamageType::physical,hit_random)>0,"player takes damage");
    const auto hp=session.health().health();
    const auto max_hp=session.health().maximum_health();
    // Attack locks equipment and does not silently substitute another roll at HIT.
    f.spawn(u"DEFAULT");
    const auto target_id=f.world.entities().back().id;
    f.world.find(target_id)->position={0,0,0};
    require(session.combat().select_target(f.world,{0,0,0},1),"select target");
    session.combat().set_animation_resolver(test_fixture::clips());
    const auto attack=session.combat().update(0,{0,0,0},f.world);
    require(attack.state==CombatState::attacking,"start attack");
    require(session.equip(a)==InventoryChange::busy,"cannot change equipment within active HIT execution");
    require(session.unequip(b)==InventoryChange::busy,"cannot remove weapon within execution");
    session.combat().advance_animation(2);
    const auto stale_event = session.combat().action().playback().frame_events().at(0);
    // Simulate a normal floor unload/load. The next world's IDs can repeat.
    session.enter_level();
    test_fixture::World next(path,u"EXPLICIT");
    require(session.health().health()==hp && session.health().maximum_health()==max_hp,"transition cannot heal or reroll HP");
    require(session.inventory().items().size()==6 && session.weapon()->id==b,"transition retains ownership and slots");
    require(session.combat().maximum_damage()==40 && session.health().armor_class()==39,"transition retains derived stats");
    require(session.combat().target_id()==0 && !session.combat().attack_in_progress(),"floor references invalidated");
    require(session.combat().perform_attack(stale_event,{0,0,0},next.world,next.logic).state==CombatState::idle,"stale HIT cannot target reused ID");
    require(next.world.kill(next.world.entities().front().id,next.logic),"next floor death");
    require(next.world.resolve_death_loot(next.logic).spawns.entities_created==6,"next floor loot");
    const auto new_id=session.pick_up(next.world,named_entity(next.world,u"SWORD_A"),next.logic);
    require(new_id>6 && new_id!=a,"session IDs not keyed by floor or resource GUID");
    require(session.inventory().items().size()==7,"same GUID picked again retains both");
    require(session.unequip(chest_b)==InventoryChange::changed && session.health().armor_class()==8,"unequip removes only selected slot");
    require(session.unequip(b)==InventoryChange::changed && session.combat().maximum_damage()==2,"unarmed restores baseline without reroll");
    for(int i=0;i<100;++i) {
        session.enter_level();
        require(session.health().health()==hp,"repeated travel preserves HP");
        require(session.inventory().find(a)->weapon->maximum_damage==20,"repeated travel preserves rolls");
    }
    // Spawner Destroy/Hide are not deaths. They must not generate or own loot.
    for(const auto action:{SpawnAction::hide_and_disable,SpawnAction::destroy}) {
        test_fixture::World control(path); control.spawn(u"EXPLICIT");
        static_cast<void>(control.world.consume_spawn_requests({{42,u"",u"",0,action}},control.logic));
        require(control.world.resolve_death_loot(control.logic).deaths==0,"script control must not farm loot");
    }
    test_fixture::World ownership(path); ownership.spawn(u"EXPLICIT");
    require(ownership.world.kill(ownership.world.entities().front().id,ownership.logic),"spawner-owned death");
    require(ownership.world.resolve_death_loot(ownership.logic).spawns.entities_created==6,"spawner death loot");
    static_cast<void>(ownership.world.consume_spawn_requests({{42,u"",u"",0,SpawnAction::destroy}},ownership.logic));
    for(const auto& e:ownership.world.entities()) if(e.kind==MasterResourceKind::item)
        require(e.alive && e.enabled && e.visible,"spawner destroy leaves loot alive");
    struct Case { const char16_t* name; std::size_t count; };
    for(const auto& c:std::vector<Case>{{u"DEFAULT",1},{u"EMPTY",0},{u"ZERO",0},
                                      {u"REVERSED",2},{u"INHERITED",6},{u"DUPLICATE_GROUP",6},{u"MISSING_CLASS",1}}) {
        test_fixture::World branch(path,c.name);
        require(branch.world.kill(branch.world.entities().front().id,branch.logic),"branch kill");
        require(branch.world.resolve_death_loot(branch.logic).spawns.entities_created==c.count,"TREASURE branch semantics");
    }
    // CREATEAS may be absent in master and inherited from BASEFILE in UNIT.
    const auto inherited_stats=next.world.consume_spawn_requests({{42,u"INHERITED_ITEM",u"Items",1}},next.logic);
    require(inherited_stats.entities_created==1,"inherited equipment created");
    const auto inherited_id=next.world.entities().back().id;
    require(next.world.find(inherited_id)->inventory_eligible,"loaded BASEFILE CREATEAS determines pickup eligibility");
    require(session.pick_up(next.world,inherited_id,next.logic)!=0,"inherited item transfers with empty master CREATEAS");
    // Non-equipment currency is not silently consumed by the new bag API.
    static_cast<void>(next.world.consume_spawn_requests({{42,u"GOLD",u"Items",1}},next.logic));
    const auto gold=next.world.entities().back().id;
    require(session.pick_up(next.world,gold,next.logic)==0 && next.world.find(gold)->alive,"unsupported currency stays in world");
    const auto* selectable = next.world.nearest_alive_item({0,0,0},1,true);
    require(selectable && selectable->inventory_eligible && selectable->id != gold,
            "unsupported overlapping currency cannot block equipment selection");
    test_fixture::World no_drop(path,u"EXPLICIT");
    no_drop.world.entities().front().drops_loot=false;
    require(no_drop.world.kill(no_drop.world.entities().front().id,no_drop.logic),"no-drop unit dies normally");
    require(no_drop.world.resolve_death_loot(no_drop.logic).deaths==0,"explicit runtime no-loot flag suppresses request");
    static_cast<void>(session.health().apply_damage(1000000,1000000,DamageType::physical,hit_random));
    require(!session.health().alive(),"player dead");
    require(session.equip(a)==InventoryChange::dead,"dead player cannot equip");
    require(session.pick_up(next.world,named_entity(next.world,u"CHEST_A"),next.logic)==0,"dead player cannot pick up");
    std::cout<<"synthetic_cycle=death->model->pickup->bag->equip->travel checks="<<checks<<'\n';
}
}
int main(int argc,char**argv) {
    try { if(argc!=2) return 2; synthetic(argv[1]); return 0; }
    catch(const std::exception& e) {std::cerr<<"item_cycle: "<<e.what()<<'\n'; return 1;}
}
