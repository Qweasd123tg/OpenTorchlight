#include "torchlight/player_session.hpp"
#include "torchlight/save_store.hpp"
#include "torchlight/scene_animation.hpp"
#include "torchlight/missile_runtime.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace torchlight;
namespace {
unsigned checks=0;
void require(bool value,const char* message) { ++checks; if(!value) throw std::runtime_error(message); }
template<class F> void rejects(F f,const char* message) {
    bool rejected=false; try { f(); } catch(const std::exception&) { rejected=true; }
    require(rejected,message);
}
void run(const char* path) {
    PakArchive pak(path);
    MasterResourceIndex resources(parse_adm(pak.read_normalized("media/masterresourceunits.dat.adm")));
    UnitDefinitionLoader definitions(pak); SpawnClassCatalog spawns(pak);
    UnitTypeHierarchy hierarchy(pak); UnitTypeResourceIndex types(pak,hierarchy,resources,definitions);
    const auto players=load_playable_players(pak,resources,definitions);
    const auto found=std::find_if(players.begin(),players.end(),[](const auto& p){return p.name==u"Vanquisher";});
    require(found!=players.end(),"Vanquisher unavailable");
    auto catalog=std::make_shared<SkillCatalog>(pak);
    const auto* def=catalog->find(u"Seeking Shot");
    require(def && def->rank(1) && def->rank(1)->event_program,"resource program not wired to catalog");
    PlayerSession session(*found,91,&hierarchy); session.attach_skill_catalog(catalog);
    while(session.progression().level<10) {
        const auto gate=session.progression_rules()->gate(session.progression().level);
        require(session.award_experience(std::max(1,gate-session.progression().experience))>0,"level progression");
    }
    require(session.invest_skill(u"Seeking Shot")==SkillUse::learned,"Seeking investment unavailable");
    auto saved=CheckpointAccess::capture(session);
    auto restored=CheckpointAccess::restore_player(*found,saved,91);
    restored.attach_skill_catalog(catalog);
    require(restored.skills().skills.size()==session.skills().skills.size(),"purchased event rank restore");
    const auto layout=LevelSceneLoader(pak).load_layout("media/layouts/test/LOGICTEST.LAYOUT.adm");
    LogicRuntime logic(layout,31); RuntimeEntityWorld world(layout,resources,definitions,spawns,types,31,10);
    require(world.consume_spawn_requests({{4789864784197325278LL,u"Skeletal Warrior",u"Monsters",1}},logic).entities_created==1,"monster spawn");
    auto& victim=world.entities().front();
    // Controlled kill fixture, not a claim about original monster HP/armor.
    victim.position={0,0,2}; victim.health=victim.maximum_health=1;
    victim.damage_defense={}; victim.attack_character.effects={}; victim.attacks={};
    AttackAnimationCatalog animations(pak);
    const auto resolve=[&](auto mesh,auto prefix){return animations.resolve(mesh,prefix);};
    SkillCastContext context; context.caster_id=7;
    const auto mana=*session.health().mana();
    require(session.begin_skill(u"Seeking Shot",resolve)==SkillUse::unsupported && *session.health().mana()==mana,
        "invalid context debited mana");
    const auto start=session.begin_skill(u"Seeking Shot",resolve,context);
    if(start!=SkillUse::started) {
        const auto& loadout=session.combat().attack_loadout();
        std::cerr<<"right="<<loadout.right.has_value()<<" left="<<loadout.left.has_value();
        if(loadout.right) std::cerr<<" ranged="<<loadout.right->traits.ranged<<" delivery="<<static_cast<int>(loadout.right->delivery)<<" prefix="<<loadout.right->animation_prefix;
        std::cerr<<'\n';
        throw std::runtime_error(std::string("real Seeking cast: ")+skill_use_message(start));
    }
    require(*session.health().mana()==mana-def->rank(1)->mana_cost,"mana not taken once at admission");
    const auto starts=session.take_skill_events();
    require(starts.size()==1 && starts[0].type==SkillEventType::start && !session.has_pending_skill_missiles(),"START fired TRIGGER scene");
    require(victim.health==1,"START damaged victim");
    session.advance_skill_animation(0);
    require(session.skill_cast().playback().frame_events().empty(),"paused cast emits HIT");
    require(session.begin_skill(u"Seeking Shot",resolve,context)==SkillUse::busy,"double cast accepted");
    session.advance_skill_animation(10);
    const auto events=session.skill_cast().playback().frame_events(); unsigned hits=0;
    for(const auto& event:events) if(event.key.name=="HIT") {
        auto forged=event; ++forged.playback_generation;
        require(!session.perform_skill_event(forged),"forged HIT accepted");
        require(session.perform_skill_event(event),"real HIT failed");
        require(!session.perform_skill_event(event),"duplicate HIT accepted"); ++hits;
    }
    require(hits>0 && session.has_pending_skill_missiles() && victim.health==1,"HIT failed launch or applied early damage");
    session.finish_skill_frame();
    require(!session.skill_cast().active() && session.has_pending_skill_missiles(),"last-frame launch discarded");
    rejects([&]{(void)CheckpointAccess::capture(session);},"save silently discarded in-flight skill");
    MissileRuntime missiles; std::vector<std::uint64_t> launched;
    session.drain_skill_launches([&](const SkillMissileLaunch& launch) {
        require(launch.missile_resource=="SEEKINGSHOT" && launch.spawner_count==3 && launch.repeated_count_open,"resource launch drift");
        const auto model=load_missile_template(pak,launch.missile_resource); require(model.has_value(),"template refused");
        MissileSpawn spawn; spawn.origin=launch.origin; spawn.direction=launch.direction;
        const auto id=missiles.spawn(*model,spawn); require(id!=0,"missile refused"); launched.push_back(id);
        return SkillMissileFireOutcome{id,{}};
    });
    require(!launched.empty(),"no resource-driven missiles");
    // A later cast must not replace ownership of an earlier in-flight missile.
    require(session.begin_skill(u"Seeking Shot",resolve,context)==SkillUse::started,"second cast after animation");
    const auto position=missiles.position(launched[0]);
    missiles.step(0,{{victim.id,victim.position,0.5F,true}},{});
    require(missiles.position(launched[0])==position && missiles.take_impacts().empty(),"paused missile advanced");
    unsigned applied=0;
    for(unsigned frame=0;frame<1000 && !missiles.empty();++frame) {
        missiles.step(.02F,{{victim.id,victim.position,0.5F,victim.alive}},{});
        std::vector<std::uint64_t> spent;
        for(const auto& impact:missiles.take_impacts()) {
            require(session.notify_skill_missile_impact(impact.missile_id,impact.victim_id,impact.blocked,impact.expired,
                [&](const SkillWeaponDamageRequest& request) {
                    require(request.weapon_damage_pct==40 && request.soak_scale_pct==60 && request.use_dps,"rank profile lost");
                    const auto result=session.combat().apply_skill_weapon_impact(request,world,logic);
                    const bool accepted=result.state==CombatState::attacked || result.state==CombatState::killed;
                    if(accepted) { ++applied; require(result.damage>0,"no weapon damage"); }
                    return SkillWeaponDamageOutcome{accepted,result.state==CombatState::killed};
                }),"in-flight ownership lost between casts");
            spent.push_back(impact.missile_id);
        }
        for(auto id:spent) session.retire_skill_missile(id);
    }
    require(applied==1 && !victim.alive && victim.player_kill && victim.health==0,"damage did not reach HP/death/credit");
    const auto posts=session.take_skill_events();
    const auto death=std::find_if(posts.begin(),posts.end(),[](const auto& p){return p.type==SkillEventType::unit_die;});
    require(death!=posts.end() && !death->damage_application_open,"death post absent after actual kill");
    session.cancel_skill();
    require(!session.has_pending_skill_missiles() && !session.skill_cast().active(),"cancel retained cast");
    (void)CheckpointAccess::capture(session);
    // Unknown projectiles never call the sink, including stale floor-local IDs.
    require(!session.notify_skill_missile_impact(launched.front(),victim.id,false,false,
        [](const auto&)->SkillWeaponDamageOutcome { throw std::runtime_error("stale sink invoked"); }),"stale impact accepted");
    require(session.begin_skill(u"Seeking Shot",resolve,context)==SkillUse::started,"cast before floor reset");
    session.enter_level(); require(!session.skill_cast().active() && !session.has_pending_skill_missiles(),"floor reset retained skill");
    const auto* weapon=session.weapon(); require(weapon!=nullptr,"starting weapon absent"); const auto weapon_id=weapon->id;
    require(session.unequip(weapon_id)==InventoryChange::changed,"unequip fixture");
    const auto before=session.health().mana();
    require(session.begin_skill(u"Seeking Shot",resolve,context)==SkillUse::unsupported && session.health().mana()==before,"nonranged cast spent mana");
}
}
int main(int argc,char** argv) {
    try { if(argc!=2) return 77; run(argv[1]); std::cout<<"PASS skill production checks="<<checks<<'\n'; return 0; }
    catch(const std::exception& e) { std::cerr<<e.what()<<'\n'; return 1; }
}
