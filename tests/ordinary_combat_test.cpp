#include "ai_cooldown_fixture.hpp"
#include "torchlight/scene_animation.hpp"
#include "torchlight/player_session.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace torchlight;
namespace {
std::size_t checks=0;
void require(bool value, const char* message) { ++checks; if (!value) throw std::runtime_error(message); }
void near(float a,float b,const char* message) { require(std::fabs(a-b)<.00001F,message); }
PlayerPrototype health_prototype() { PlayerPrototype p; p.minimum_health=p.maximum_health=10000; p.attack_character.collision_radius=.25F; return p; }
struct Scene {
    test_fixture::World f;
    AttackAnimationCatalog catalog;
    PlayerCombatState player{health_prototype(),7};
    EnemyController enemies{7};
    explicit Scene(const char* path,const char16_t* name=u"ARMED") : f(path),catalog(f.archive) {
        f.spawn(name); enemies.set_animation_resolver([this](std::string_view m,std::string_view p){return catalog.resolve(m,p);});
    }
    std::uint64_t id() const {return f.world.entities().front().id;}
    RuntimeEntity& entity() {return f.world.entities().front();}
    EnemyAiUpdate start(float dt=0,const std::array<float,3>& pos={}) {
        const auto updates=enemies.update(dt,pos,player,f.world);
        require(updates.size()==1,"missing ordinary AI update"); return updates.front();
    }
    const OrdinaryAttackAction& action() const {const auto* a=enemies.action(id()); if(!a)throw std::runtime_error("missing action");return *a;}
    std::vector<AnimationEventOccurrence> advance(float dt) {
        enemies.advance_animations(dt,f.world,player); return action().playback().frame_events();
    }
    EnemyAiUpdate hit(const AnimationEventOccurrence& e,const std::array<float,3>& pos={}) {
        return enemies.perform_attack(id(),e,pos,player,f.world);
    }
};

void resource_chain(const char* path) {
    Scene s(path);
    require(s.start().state==EnemyAiState::attacking,"resource-backed armed start");
    require(s.player.health()==10000,"damage before HIT");
    require(s.action().description().animation_prefix=="RSLASH" && s.action().clip()->animation_name=="RSLASH_A",
        "selected first Attack rather than weapon family");
    require(s.action().clip()->bind_skeleton && s.action().clip()->bind_skeleton->bones.size()==1,
        "model without Idle lost bind pose");
    near(s.action().playback().playback_speed(),.5F,"weapon SPEED did not drive clock");
    near(s.enemies.ai_cooldown_remaining(s.id()),2,"selected weapon cooldown not included");
    require(s.start(0).state==EnemyAiState::waiting,"active action replaced");
    require(s.advance(.39F).empty(),"enemy HIT too early");
    const auto first=s.advance(.02F); require(first.size()==1,"first manifest HIT missing");
    auto foreign=first[0]; ++foreign.execution_id;
    require(s.hit(foreign).damage==0,"foreign ID accepted");
    const auto first_hit=s.hit(first[0]); require(first_hit.state==EnemyAiState::attacked && first_hit.damage>=10 && first_hit.damage<=20,
        "HIT did not use selected weapon damage");
    require(s.hit(first[0]).damage==0,"same key damaged twice");
    const auto crossed=s.advance(2); require(crossed.size()==3,"multiple crossed keys or terminal HIT lost");
    int hits=0;
    for(const auto& event:crossed) {
        const auto update=s.hit(event);
        if(update.damage>0)++hits;
        require(s.hit(event).damage==0,"duplicate multi-key event accepted");
    }
    require(hits==2 && s.action().active() && s.action().playback().finished(),"final HIT closed before delivery");
    const auto model=parse_ogre_mesh(s.f.archive.read_normalized(s.entity().mesh_path));
    const auto& c=*s.action().clip();
    const auto pose=sample_ogre_mesh_animation(model,*c.bind_skeleton,c.animation_skeleton,c.animation_name,
        s.action().playback().time_seconds(),AnimationPlaybackMode::clamp);
    near(pose.bones.at(0).position[0],20,"HIT/pose time or selected clip diverged at last key");
    near(pose.geometries.at(0).positions.at(0)[0],20,"skinned vertex not driven by same action");
    s.enemies.finish_animation_frame();
    require(!s.action().active(),"terminal action not finished");
    // Animation steps do not silently tick AI. The next AI update consumes the same elapsed interval.
    require(s.start(2).state==EnemyAiState::attacking,"AI and animation gates were added in series");

    for(const auto* name:{u"LEFT",u"SPAWNED_WEAPON",u"INNATE"}) {
        Scene other(path,name); require(other.start().state==EnemyAiState::attacking,"left/spawn/innate path rejected");
        const auto expected=std::u16string_view(name)==u"LEFT"?"LSLASH":std::u16string_view(name)==u"INNATE"?"ATTACK":"RSLASH";
        require(other.action().description().animation_prefix==expected,"description source ignored");
    }
    Scene dual(path,u"DUAL"); require(dual.start().state==EnemyAiState::attacking,"dual start");
    const auto events=dual.advance(2.1F); for(const auto& e:events)static_cast<void>(dual.hit(e));
    dual.enemies.finish_animation_frame(); require(dual.start(2.1F).state==EnemyAiState::attacking,"left alternate start");
    require(dual.action().description().hand==AttackHand::left && dual.action().clip()->animation_name=="LSLASH_A",
        "three HITs must toggle selection to left");
    near(dual.action().playback().playback_speed(),2,"left hand speed ignored");
    near(dual.enemies.ai_cooldown_remaining(dual.id()),3,"AI used right-hand cooldown for left attack");
}

void misses_and_cancellation(const char* path) {
    Scene miss(path); require(miss.start().state==EnemyAiState::attacking,"miss fixture start");
    const auto first=miss.advance(.5F).at(0);
    require(miss.hit(first,{5,0,0}).state==EnemyAiState::missed,"target leaving strike reach did not miss");
    require(miss.hit(first).damage==0 && miss.player.health()==10000,"missed key replayed after target returned");
    const auto later=miss.advance(.5F);
    require(later.size()==2,"next frame keys missing");
    require(miss.hit(later.back()).damage>0,"later distinct HIT incorrectly blocked by a miss");
    miss.enemies.interrupt_attack(miss.id());
    require(!miss.action().active() && miss.hit(later.back()).damage==0,"interrupted key replayed");
    near(miss.enemies.ai_cooldown_remaining(miss.id()),2,"interrupt reset separate AI cooldown");
    require(miss.start(1).state==EnemyAiState::waiting,"interrupt bypassed AI cooldown");
    require(miss.start(1).state==EnemyAiState::attacking,"interrupt permanently disabled next action");
    const auto now=miss.advance(.5F).at(0);
    require(miss.hit(first).damage==0 && miss.hit(now).damage>0,"old execution accepted after restart");
    for(int mode=0;mode<3;++mode) {
        Scene s(path); require(s.start().state==EnemyAiState::attacking,"cancel fixture start");
        const auto e=s.advance(.5F).at(0);
        if(mode==0) static_cast<void>(s.f.world.kill(s.id(),s.f.logic));
        if(mode==1) s.entity().enabled=false;
        if(mode==2) {TorchlightRandom r(1); static_cast<void>(s.player.apply_damage(1000000,1000000,DamageType::physical,r));}
        const auto hp=s.player.health();
        require(s.hit(e).damage==0 && s.player.health()==hp && !s.action().active(),"death/disable permitted queued HIT");
    }
    Scene old(path),fresh(path);
    require(old.start().state==EnemyAiState::attacking && fresh.start().state==EnemyAiState::attacking,"floor fixtures");
    const auto stale=old.advance(.5F).at(0),live=fresh.advance(.5F).at(0);
    require(stale.execution_id==live.execution_id && old.id()==fresh.id(),"fixture does not reuse IDs");
    require(fresh.hit(stale).damage==0 && fresh.hit(live).damage>0,"previous controller/floor event accepted");
    Scene denied(path,u"NO_CLIP");
    for(int i=0;i<5;++i) {
        require(denied.start(.1F).state==EnemyAiState::unavailable,"missing clip invented an action");
        require(!denied.action().active() && denied.enemies.ai_cooldown_remaining(denied.id())<=0,"failed start armed AI");
    }
    for(const auto* name:{u"NO_UNARMED",u"RANGED"}) {
        Scene s(path,name);const auto decision=s.start();
        if(decision.state!=EnemyAiState::unavailable) std::cerr << "denied case=" << (name==std::u16string_view(u"NO_UNARMED") ? "no unarmed" : "ranged") << " state=" << static_cast<int>(decision.state) << "\n";
        require(decision.state==EnemyAiState::unavailable,"unsupported action silently approximated");
        require(!s.enemies.last_attack_issue(s.id()).empty(),"unsupported action has no diagnostic");
    }
    Scene nohit(path,u"NO_HIT");require(nohit.start().state==EnemyAiState::attacking,"no-HIT clip must still play");
    for(const auto& e:nohit.advance(2))require(nohit.hit(e).damage==0,"non-HIT clip dealt invented damage");
    nohit.enemies.finish_animation_frame();require(!nohit.action().active() && nohit.player.health()==10000,"no-HIT clip never finishes");
}

void effects_and_player(const char* path) {
    for(const auto& [name,speed]:std::vector<std::pair<const char16_t*,float>>{{u"HASTE",1},{u"INHERITED_HASTE",1},{u"SLOW_RESIST",.3F}}) {
        Scene s(path,name);require(s.start().state==EnemyAiState::attacking,"effect actor failed");
        near(s.action().playback().playback_speed(),speed,"resource passive speed/resistance not evaluated");
    }
    Scene conditional(path,u"CONDITIONAL");require(conditional.start().state==EnemyAiState::attacking,"partial effect actor failed");
    near(conditional.action().playback().playback_speed(),1,"conditional effect was applied unconditionally");
    require(!conditional.enemies.last_attack_issue(conditional.id()).empty(),"unsupported effect disappeared silently");
    Scene s(path,u"INNATE");
    const auto catalog=AttackEffectCatalog::discover(s.f.archive);
    require(catalog && catalog->find(u"FIXTURE_HASTE")==0x16,"catalog child order/type mapping changed");
    require(s.catalog.resolve("media/mismatch/Creature.mesh","ATTACK").empty(),"wrong named animation substituted");
    require(s.catalog.resolve("media/unrelated/Creature.mesh","ATTACK").empty(),"unrelated sibling manifest substituted");
    const auto players=load_playable_players(s.f.archive,s.f.resources,s.f.definitions);
    require(players.size()==2,"player UNIT loading failed");
    require(players[1].starting_weapon && players[1].starting_weapon->attack_hand==AttackHand::left,
        "explicit starting LEFTHAND was silently turned into right hand");
    near(players[0].attack_character.effects.get(0x16),50,"player passive effect lost");
    PlayerSession session(players[0],11,&s.f.hierarchy);
    session.combat().set_animation_resolver([&](std::string_view m,std::string_view p){return s.catalog.resolve(m,p);});
    require(session.combat().select_target(s.f.world,{},1),"player target selection");
    require(session.combat().update(0,{},s.f.world).state==CombatState::attacking,"shared player action failed");
    near(session.combat().action().playback().playback_speed(),1.5F,"effect 0x16 zeroed on player");
    require(s.entity().health==100,"player damaged target at start");
    session.combat().advance_animation(.2F);
    const auto e=session.combat().action().playback().frame_events().at(0);
    const auto hit=session.combat().perform_attack(e,{},s.f.world,s.f.logic);
    require(hit.damage>=6 && hit.damage<=11,"player STR-derived damage not applied at HIT");
    require(session.combat().perform_attack(e,{},s.f.world,s.f.logic).damage==0,"player duplicated key");
    AttackEffects bonus;bonus.add(0x16,50);
    session.combat().set_external_attack_effects(bonus);
    near(session.combat().action().playback().playback_speed(),1.5F,"mid-action effect rewrote running clock");
    session.combat().advance_animation(2);
    session.combat().finish_animation_frame();
    require(session.combat().update(0,{},s.f.world).state==CombatState::attacking,"player next action failed");
    near(session.combat().action().playback().playback_speed(),2,"next action ignored updated effects");
    session.combat().advance_animation(.2F);
    const auto stale=session.combat().action().playback().frame_events().at(0);
    const auto health=session.health().health();session.enter_level();
    require(session.health().health()==health,"floor transition altered persistent HP");
    require(session.combat().perform_attack(stale,{},s.f.world,s.f.logic).damage==0,"stale player event survived floor entry");
    // Store passive armor per rolled instance, then restore it through PlayerSession.
    const auto spawned=s.f.world.consume_spawn_requests({{42,u"HASTE_CHEST",u"Items",1}},s.f.logic);
    require(spawned.entities_created==1,"armor instance fixture failed");
    const auto armor_id=s.f.world.entities().back().id;
    const auto inventory_id=session.pick_up(s.f.world,armor_id,s.f.logic);
    require(inventory_id && session.equip(inventory_id)==InventoryChange::changed,"armor did not enter session");
    near(session.combat().attack_playback_speed(),2,"equipped armor effect not included exactly once");
    require(session.equip(inventory_id)==InventoryChange::unchanged,"same armor effect stacked");
    session.enter_level();near(session.combat().attack_playback_speed(),2,"floor change lost armor speed effect");
    require(session.unequip(inventory_id)==InventoryChange::changed,"armor unequip");
    near(session.combat().attack_playback_speed(),1.5F,"unequip retained stale effect");
}
}
int main(int argc,char**argv) {
    try {if(argc!=2)return 2;resource_chain(argv[1]);misses_and_cancellation(argv[1]);effects_and_player(argv[1]);
        std::cout<<"PASS: "<<checks<<" resource-backed ordinary combat assertions (authored fixture)\n";return 0;
    }catch(const std::exception& e){std::cerr<<"FAIL after "<<checks<<": "<<e.what()<<'\n';return 1;}
}
