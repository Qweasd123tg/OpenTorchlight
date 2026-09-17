#include "ai_cooldown_fixture.hpp"
#include "torchlight/scene_animation.hpp"
#include "torchlight/player_session.hpp"
#include "torchlight/save_store.hpp"
#include "torchlight/inventory_view.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace torchlight;
namespace {
std::size_t checks = 0;
void require(bool b, const char* message) { ++checks; if (!b) throw std::runtime_error(message); }
template<class F> void rejects(F f, const char* message) {
    try { f(); } catch (const std::invalid_argument&) { ++checks; return; }
    catch (const CheckpointError&) { ++checks; return; }
    throw std::runtime_error(message);
}
PlayerPrototype prototype(test_fixture::World& f) {
    const auto players = load_playable_players(f.archive, f.resources, f.definitions);
    const auto found = std::find_if(players.begin(), players.end(), [](const auto& p){return p.name == u"TEST_PLAYER";});
    if (found == players.end()) throw std::runtime_error("missing authored player");
    return *found;
}
std::uint64_t spawn_item(test_fixture::World& f, const char16_t* name) {
    const auto result = f.world.consume_spawn_requests({{42, name, u"Items", 1}}, f.logic);
    require(result.entities_created == 1, "authored item not spawned");
    return f.world.entities().back().id;
}
void numeric() {
    require(evaluated_world_gold(19.2F,125) == 24, "gold operation order / ceil");
    require(evaluated_world_gold(0,100) == 0 && evaluated_world_gold(100,0) == 0, "zero gold");
    require(original_monster_experience(200.9F) == 403, "original XP scaling / trunc");
    require(original_monster_experience(100) == 100 && original_monster_experience(150) == 225 &&
        original_monster_experience(0) == 0, "original XP square/100 curve");
    require(experience_with_bonus(original_monster_experience(200.9F),0)==403, "XP bonus baseline");
    require(checked_reward_integer(100.75F,false)==100 && checked_reward_integer(100.75F,true)==101,
        "gate trunc and point ceil conflated");
    require(experience_with_bonus(1,.1F)==2 && experience_with_bonus(100,12.5F)==113, "ceil XP bonus");
    for (float bad : {-1.F, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::quiet_NaN()}) {
        rejects([&]{static_cast<void>(evaluated_world_gold(bad,100));},"invalid gold graph accepted");
        rejects([&]{static_cast<void>(evaluated_world_gold(100,bad));},"invalid gold percent accepted");
    }
    rejects([]{static_cast<void>(evaluated_world_gold(2147483648.F,100));},"gold int32 overflow accepted");
    rejects([]{static_cast<void>(experience_with_bonus(1,std::numeric_limits<float>::infinity()));},"invalid XP bonus accepted");
    rejects([]{static_cast<void>(original_monster_experience(-1.F));},"negative XP graph accepted");
    rejects([]{static_cast<void>(original_monster_experience(std::numeric_limits<float>::quiet_NaN()));},
        "NaN XP graph accepted");
    rejects([]{static_cast<void>(original_monster_experience(1e30F));},"XP int32 overflow accepted");
    ProgressionRules rules({{100,0,0,100,31},{250,3,1,151,41},{500,4,2,221,51},{1000,5,3,300,61}});
    require(rules.gate(0)==0 && rules.gate(999)==1000 && rules.maximum_level()==4, "gate clamp/count");
    rejects([&]{static_cast<void>(rules.gate(-1));},"negative graph level");
    ProgressionState state;
    require(advance_progression(state,rules,99)==0 && state.experience==99, "early level up");
    require(advance_progression(state,rules,1)==1 && state.level==2 && state.stat_points==3 && state.skill_points==1,
        "exact threshold / new-level points");
    require(advance_progression(state,rules,401)==2 && state.level==4 && state.stat_points==12 && state.skill_points==6,
        "multi-level reward dropped thresholds");
    require(advance_progression(state,rules,std::numeric_limits<std::int32_t>::max())==0 && state.experience==1000,
        "XP saturation / cap");
    require(advance_progression(state,rules,std::numeric_limits<std::int32_t>::min())==0 && state.experience==0 && state.level==4,
        "negative XP should clamp without level-down");
    auto invalid=state; invalid.allocated[0]=1;
    rejects([&]{validate_progression(invalid,rules);},"unfunded attribute accepted");
    rejects([]{ProgressionRules bad({{100,0,0,100,{}},{100,0,0,100,{}}});},"duplicate gates accepted");
    ProgressionRules overflow({{1,0,0,1,{}},{2,std::numeric_limits<std::int32_t>::max(),0,1,{}},{3,1,0,1,{}}});
    ProgressionState unchanged;
    rejects([&]{static_cast<void>(advance_progression(unchanged,overflow,3));},"point overflow accepted");
    require(unchanged.level==1 && unchanged.experience==0 && unchanged.stat_points==0,"overflow partially committed");
}
struct Cycle {
    test_fixture::World f;
    PlayerPrototype proto;
    PlayerSession player;
    AttackAnimationCatalog clips;
    EnemyController enemies{1};
    std::uint64_t corpse=0, gold=0, range_gold=0;
    explicit Cycle(const char* path) : f(path),proto(prototype(f)),player(proto,1,&f.hierarchy),clips(f.archive) {
        player.combat().set_animation_resolver([this](std::string_view m,std::string_view p){return clips.resolve(m,p);});
    }
    void play() {
        const auto* rules=player.progression_rules();
        require(rules && rules->maximum_level()==4 && rules->gate(1)==100,"resource progression not loaded");
        require(rules->at(2).stat_points==3 && rules->at(2).maximum_health==151,"resource ceil missing");
        require(!player.allocate_attribute(0),"point spent without balance");
        const auto armor_entity=spawn_item(f,u"MANA_CHEST");
        const auto armor=player.pick_up(f.world,armor_entity,f.logic);
        require(armor && player.equip(armor)==InventoryChange::changed,"equip mana armor");
        require(player.health().maximum_mana()==36 && player.health().spend_mana(20),"initial gear mana");
        f.spawn(u"REWARD_DUMMY"); corpse=f.world.entities().back().id;
        require(f.world.find(corpse)->experience_reward==403,"resource XP not evaluated at spawn");
        require(player.combat().select_target(f.world,{},1),"reward target selection");
        require(player.combat().update(0,{},f.world).state==CombatState::attacking,"reward action not started");
        const auto execution=player.combat().action().id();
        player.combat().advance_animation(.2F);
        const auto events=player.combat().action().playback().frame_events();
        require(!events.empty(),"authored HIT event missing");
        const auto hit=player.combat().perform_attack(events.front(),{},f.world,f.logic);
        require(hit.state==CombatState::killed && f.world.find(corpse)->player_kill,"lethal HIT did not attribute credit");
        require(player.progression().experience==0,"reward applied before safe phase");
        const auto reward=player.collect_kill_rewards(f.world);
        require(reward.kills==1 && reward.levels==2 && reward.experience==403,"kill-to-progression chain");
        require(player.progression().level==3 && player.progression().stat_points==7 && player.progression().skill_points==3,
                "new levels/points incorrect");
        require(player.health().health()==221 && player.health().maximum_health()==221,"level-up HP graph/refill");
        require(player.health().mana()==59 && player.health().maximum_mana()==59,"level-up lost equipped mana effects");
        require(player.combat().action().active() && player.combat().action().id()==execution,
                "level-up replaced active attack");
        require(player.combat().perform_attack(events.front(),{},f.world,f.logic).damage==0,"replayed HIT reissued damage");
        require(player.collect_kill_rewards(f.world).kills==0 && player.progression().experience==403,"duplicate XP");
        require(!player.allocate_attribute(0),"allocation rewrites active action");
        player.combat().advance_animation(2); player.combat().finish_animation_frame();
        require(!player.combat().attack_in_progress(),"attack never finished");
        const auto before=player.attributes();
        for(std::size_t i=0;i<4;++i) require(player.allocate_attribute(i),"attribute allocation failed");
        for(std::size_t i=0;i<4;++i) require(player.attributes()[i]==before[i]+1,"wrong attribute increment");
        require(player.progression().stat_points==3 && !player.allocate_attribute(4),"points/index validation");
        require(player.combat().attack_character().strength==before[0]+1 &&
                player.combat().attack_character().dexterity==before[1]+1,"combat attributes stale");
        require(CheckpointAccess::capture(player).base_defense.defense_attribute==before[3]+1,"defense attribute stale");
        const auto loot=f.world.resolve_death_loot(f.logic);
        require(loot.deaths==1 && loot.spawns.entities_created==1,"death did not produce gold");
        gold=f.world.entities().back().id;
        require(f.world.find(gold)->gold_amount==24 && f.world.find(gold)->loot_source_id==corpse,
                "gold amount / loot provenance incorrect");
        require(!f.world.find(gold)->inventory_eligible && !player.pick_up(f.world,gold,f.logic),"gold became equipment");
        require(f.world.nearest_alive_item({},1,true)->id==gold,"gold cannot be selected for pickup");
        const auto bag=player.inventory().items().size(), wallet=static_cast<std::size_t>(player.gold());
        require(player.pick_up_gold(f.world,gold,f.logic)==24,"gold pickup failed");
        require(player.gold()==static_cast<std::int32_t>(wallet+24) && player.inventory().items().size()==bag,
                "gold did not transfer solely to wallet");
        require(!player.pick_up_gold(f.world,gold,f.logic),"gold pickup repeated");
        const auto zero=spawn_item(f,u"ZERO_GOLD");
        require(player.pick_up_gold(f.world,zero,f.logic)==0 && !f.world.find(zero)->alive,"zero gold not consumed");
        range_gold=spawn_item(f,u"RANGE_GOLD");
        require(f.world.find(range_gold)->gold_amount && *f.world.find(range_gold)->gold_amount>=5 &&
                *f.world.find(range_gold)->gold_amount<=34,"rolled gold bounds");
        // Script death is deliberately separate from the player's HIT path.
        f.spawn(u"REWARD_DUMMY");
        require(f.world.kill(f.world.entities().back().id,f.logic),"script death failed");
        require(player.collect_kill_rewards(f.world).kills==0,"script death granted XP");
        static_cast<void>(f.world.resolve_death_loot(f.logic));
        const auto xp=player.progression().experience;
        player.enter_level(); require(player.progression().experience==xp && player.gold()==133,"floor reset lost progression");
        InventoryView view; const auto lines=view.lines(player);
        require(lines.size()>4 && lines[1].text.find("LEVEL 3")!=std::string::npos,"HUD progression absent");
    }
    CampaignCheckpoint checkpoint() {
        FloorCheckpoint floor; floor.address={u"Town",0}; floor.layout_identity=checkpoint_layout_identity(f.manifest);
        floor.world=CheckpointAccess::capture(f.world); floor.logic=CheckpointAccess::capture(f.logic);
        floor.enemies=CheckpointAccess::capture(enemies);
        CampaignCheckpoint c; c.slot="reward-test";c.character_name="Reward fixture";c.class_guid=proto.guid;
        c.resource_identity=checkpoint_resource_identity(f.archive);c.player=CheckpointAccess::capture(player);
        c.floors.push_back(floor); CheckpointAccess::validate(c); return c;
    }
};
void restored(const char* path, const CampaignCheckpoint& c) {
    Cycle r(path);
    auto player=CheckpointAccess::restore_player(r.proto,c.player,1,&r.f.hierarchy);
    CheckpointAccess::restore_floor(c.floors.front(),r.f.world,r.f.logic,r.enemies);
    require(player.progression().level==3 && player.progression().experience==403 && player.progression().stat_points==3,
            "saved progression lost");
    require(player.progression().allocated==std::array<std::int32_t,4>{1,1,1,1},"allocated points not persisted");
    require(player.health().maximum_health()==221 && player.health().maximum_mana()==59 && player.gold()==133,
            "loaded vitals/gear/wallet changed");
    const auto before=CheckpointAccess::capture(r.f.world);
    require(player.collect_kill_rewards(r.f.world).kills==0 && player.progression().experience==403,"load repeated death XP");
    bool found=false;
    for(const auto& e:before.entities) {
        const auto* actual=r.f.world.find(e.id);
        require(actual && actual->gold_amount==e.gold_amount && actual->experience_reward==e.experience_reward &&
                actual->player_kill==e.player_kill && actual->reward_claimed==e.reward_claimed,"entity reward state changed");
        if(e.name==u"RANGE_GOLD" && e.alive) {
            require(player.pick_up_gold(r.f.world,e.id,r.f.logic)==e.gold_amount,"saved rolled gold changed at pickup");
            found=true;
        }
        if(e.gold_amount && !e.alive) require(!player.pick_up_gold(r.f.world,e.id,r.f.logic),"consumed gold revived");
    }
    require(found,"missing saved uncollected rolled gold");
    require(CheckpointAccess::capture(r.f.world).random_state==before.random_state,"load/pickup advanced world RNG");
    auto bad=c.player; ++bad.progression->stat_points;
    rejects([&]{static_cast<void>(CheckpointAccess::restore_player(r.proto,bad,1));},"forged point balance accepted");
    bad=c.player; ++bad.maximum_health;
    rejects([&]{static_cast<void>(CheckpointAccess::restore_player(r.proto,bad,1));},"forged level HP accepted");
    bad=c.player; bad.progression->allocated[0]=-1;
    rejects([&]{CheckpointAccess::validate(bad);},"negative allocation accepted");
    auto world_bad=c; auto& first=world_bad.floors.front().world.entities.front(); first.gold_amount=1;
    rejects([&]{static_cast<void>(encode_checkpoint(world_bad));},"equipment/monster gold accepted");
}
void unavailable(const char* path) {
    test_fixture::World f(path);
    auto p=prototype(f); PlayerSession player(p,1,&f.hierarchy);
    require(!player.progression_rules(),"missing progression graphs fabricated rules");
    require(player.award_experience(1000)==0 && player.progression().experience==0,
            "missing graphs fabricated XP thresholds");
    require(!player.allocate_attribute(0),"unknown progression awarded points");
    f.spawn(u"INNATE");const auto id=f.world.entities().back().id;
    require(!f.world.find(id)->experience_reward,"missing monster graph fabricated a reward");
    require(f.world.apply_damage(id,10000,f.logic,true).killed,"unavailable fixture kill failed");
    const auto result=player.collect_kill_rewards(f.world);
    require(result.unavailable==1 && result.kills==0 && f.world.find(id)->reward_claimed,
            "unknown reward not explicitly consumed as unavailable");
    require(player.collect_kill_rewards(f.world).unavailable==0,"unknown reward repeatedly reported");
}
void exclusions(const char* path) {
    Cycle c(path);
    const auto gold=spawn_item(c.f,u"GOLD");
    c.player.give_gold(std::numeric_limits<std::int32_t>::max());
    require(c.player.pick_up_gold(c.f.world,gold,c.f.logic)==24 && c.player.gold()==std::numeric_limits<std::int32_t>::max(),
            "wallet overflow or pickup duplicate risk");
    c.f.spawn(u"REWARD_DUMMY");const auto target=c.f.world.entities().back().id;
    require(c.f.world.apply_damage(target,1000,c.f.logic,true).killed,"dead-player fixture kill failed");
    TorchlightRandom rng(1);
    static_cast<void>(c.player.health().apply_damage(100000,100000,DamageType::physical,rng));
    require(!c.player.health().alive(),"fixture player did not die");
    require(c.player.collect_kill_rewards(c.f.world).unavailable==1 && c.player.progression().experience==0,
            "dead player rewarded");
    const auto pending_gold=spawn_item(c.f,u"GOLD");
    require(!c.player.pick_up_gold(c.f.world,pending_gold,c.f.logic),"dead player picks gold");
    ActorMotion motion({},1);
    require(c.player.recover_at_entry(c.enemies,motion,{}).status==RecoveryStatus::recovered,"recovery failed");
    require(c.player.collect_kill_rewards(c.f.world).kills==0 && c.player.progression().experience==0,
            "recovery resurrected forfeited reward");
    bool invalid_gold_rejected=false;
    try { static_cast<void>(spawn_item(c.f,u"BAD_GOLD")); }
    catch(const std::runtime_error& error) { invalid_gold_rejected=std::string(error.what())=="invalid gold MINVALUE/MAXVALUE"; }
    require(invalid_gold_rejected,"invalid gold range accepted or unexpected resource failure");
}
}
int main(int argc, char** argv) {
    try {
        if(argc==2 && std::string(argv[1])=="--numeric") numeric();
        else if(argc==3 && std::string(argv[1])=="--unavailable") unavailable(argv[2]);
        else if(argc==2) {
            Cycle c(argv[1]);c.play();auto data=c.checkpoint();
            const auto bytes=encode_checkpoint(data);
            require(bytes[8]==kCheckpointFormatVersion,"checkpoint writer did not use current version");
            const auto decoded=decode_checkpoint(bytes);
            require(encode_checkpoint(decoded)==bytes,"current-version roundtrip not canonical");
            restored(argv[1],decoded);exclusions(argv[1]);
        } else if(argc==4) {
            const std::string mode=argv[3];SaveStore store(argv[2]);
            if(mode=="write") {Cycle c(argv[1]);c.play();static_cast<void>(store.write(c.checkpoint()));}
            else if(mode=="read") {Cycle c(argv[1]);restored(argv[1],store.read("reward-test",checkpoint_resource_identity(c.f.archive)));}
            else throw std::runtime_error("unknown reward probe mode");
        } else throw std::runtime_error("usage: reward_cycle_test fixture [save-dir write|read] | --numeric");
        std::cout<<"reward cycle: "<<checks<<" assertions passed; authored resources, NOT original gameplay parity\n";
    } catch(const std::exception& e) {std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
