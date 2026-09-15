#include "torchlight/scene_animation.hpp"
#include "torchlight/attack_action.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace torchlight;
namespace {
std::size_t assertions = 0;
void require(bool condition, const char* message) {
    ++assertions;
    if (!condition) throw std::runtime_error(message);
}
AttackClip clip(std::string name="RSLASH_A", float duration=1.0F) {
    auto c = std::make_shared<ModelAnimationClip>();
    c->animation_name=name; c->skeleton_path="fixture/"+name+".skeleton"; c->duration=duration;
    for (float frame : {3.0F, 6.0F, 30.0F}) {
        AnimationEventKey key; key.name="HIT"; key.frame=frame; c->event_keys.push_back(key);
    }
    AnimationEventKey foot; foot.name="FOOTSTEP"; foot.frame=4; c->event_keys.push_back(foot);
    return c;
}
void clock_and_hits() {
    OrdinaryAttackAction action;
    AttackDescription d; d.animation_prefix="RSLASH"; d.speed_denominator=2;
    action.start(11, 42, d, clip(), .5F);
    require(action.active() && action.playback().frame_events().empty(), "start dealt a hit");
    action.advance(.19F);
    require(action.playback().frame_events().empty(), "early HIT");
    action.advance(.22F);
    const auto events=action.playback().frame_events();
    require(events.size()==3, "crossed multiple keys were lost");
    auto bad=events[0]; bad.source_clip="other";
    require(!action.consume_hit(bad),"wrong clip accepted");
    bad=events[0]; ++bad.execution_id;
    require(!action.consume_hit(bad),"foreign execution accepted");
    bad=events[0]; bad.key_index=2;
    require(!action.consume_hit(bad),"future key fabricated");
    require(action.consume_hit(events[0]),"first HIT rejected");
    require(!action.consume_hit(events[0]),"duplicate first HIT accepted");
    require(action.consume_hit(events[1]),"second HIT blocked by first");
    require(!action.consume_hit(events[2]),"FOOTSTEP dealt damage");
    require(action.playback().frame_events().size()==3,"consumption destroyed shared events");
    action.advance(10);
    require(action.playback().time_seconds()==1 && action.playback().finished() && action.active(),
        "final keys must survive until finish_frame");
    const auto end=action.playback().frame_events()[0];
    require(action.consume_hit(end),"HIT at exact clip end was lost");
    action.finish_frame();
    require(!action.active() && !action.consume_hit(end),"closed action replay");
    action.start(12,42,d,clip(),1); action.advance(.2F);
    const auto stale=action.playback().frame_events()[0]; action.cancel();
    require(!action.consume_hit(stale),"cancelled HIT accepted");
    action.start(13,42,d,clip(),1); action.advance(.2F);
    require(!action.consume_hit(stale),"old event hit reused target ID");
    bool rejected=false;
    try { action.start(14,42,d,clip("ATTACK_A"),1); }
    catch(const std::invalid_argument&) { rejected=true; }
    require(rejected && action.id()==13,"wrong-family clip mutated active action");
}
void effects_and_selection() {
    AttackEffects speed;
    speed.add(0x16,50);
    require(ordinary_attack_speed(2,speed)==.75F,"positive speed effect ignored");
    speed.values.clear(); speed.add(0x16,-60); speed.add(0x8c,50);
    require(std::fabs(ordinary_attack_speed(2,speed)-.35F)<1e-6F,"slow resistance ordering wrong");
    speed.values.back().value=200;
    require(ordinary_attack_speed(2,speed)==.5F,"resistance upper clamp");
    speed.values.back().value=-200;
    require(ordinary_attack_speed(2,speed)==.2F,"minimum speed/resistance lower clamp");
    speed.values[0].value=100;
    require(ordinary_attack_speed(2,speed)==1,"resistance must not modify positive haste");
    AttackLoadout loadout; AttackDescription innate; innate.maximum_damage=10;
    innate.range=1; innate.strike_range=2; loadout.innate.push_back(innate);
    TorchlightRandom random(1);
    require(select_ordinary_attack(loadout,false,random)->hand==AttackHand::innate,"innate selection");
    loadout.no_unarmed_attacks=true;
    require(!select_ordinary_attack(loadout,false,random),"NO_UNARMED_ATTACKS ignored");
    AttackDescription r; r.hand=AttackHand::right; r.animation_prefix="RSLASH";
    r.maximum_damage=24; r.range=2; r.strike_range=3;
    auto l=r; l.hand=AttackHand::left; l.animation_prefix="LSLASH"; l.range=1;
    loadout.right=r; loadout.left=l;
    require(select_ordinary_attack(loadout,false,random)->animation_prefix=="RSLASH", "right choice");
    require(select_ordinary_attack(loadout,true,random)->animation_prefix=="LSLASH", "left choice");
    AttackCharacterValues character; character.strength=6; character.reach_bonus=.5F;
    auto damage=ordinary_physical_damage(r,loadout,character);
    require(damage[0]==13 && damage[1]==26,"STR/ceil physical damage");
    loadout.use_weapon_damage=false;
    require(ordinary_physical_damage(r,loadout,character)[1]==11,"innate damage base override");
    loadout.use_weapon_damage=true;
    require(std::fabs(ordinary_attack_range(r,loadout,character)-1.7F)<1e-6F,"dual melee minimum range");
    require(std::fabs(ordinary_strike_range(r,character,{})-3.7F)<1e-6F,"strike range confused with approach");
    require(within_horizontal_reach({0,0,0},{3,0,0},.5F,.5F,2),"collision radii omitted");
    require(!within_horizontal_reach({0,0,0},{3.01F,0,0},.5F,.5F,2),"outside reach accepted");
    require(weapon_attack_prefix(WeaponAttackFamily::bow,AttackHand::right).empty(),"invalid bow hand");
    require(weapon_attack_prefix(WeaponAttackFamily::bow,AttackHand::left)=="BOW", "bow prefix");
    require(weapon_attack_prefix(WeaponAttackFamily::polearm,AttackHand::right)=="POLEARM", "polearm prefix");
    require(weapon_attack_prefix(WeaponAttackFamily::pistol,AttackHand::left)=="LPISTOL", "left pistol prefix");
}
void channel_effects_and_guards() {
    AttackDescription right; right.hand=AttackHand::right; right.animation_prefix="RSLASH";
    right.maximum_damage=100;
    AttackDescription left=right; left.hand=AttackHand::left; left.animation_prefix="LSLASH";
    left.effects.add(0x19, 500, 0); left.effects.add(10, 300, 0);
    AttackLoadout loadout; loadout.right=right; loadout.left=left;
    AttackCharacterValues c;
    require(ordinary_physical_damage(right,loadout,c)[1]==100,"opposite hand physical effect leaked");
    require(ordinary_physical_damage(left,loadout,c)[1]==900,"selected hand physical effect missing");
    loadout.left->effects.add(0x19,25,6);
    require(ordinary_physical_damage(right,loadout,c)[1]==125,"ALL-channel bonus from opposite hand lost");
    loadout.left.reset();
    c.strength=10; c.effects.add(0x47,50); c.effects.add(0x45,2.1F);
    require(ordinary_physical_damage(right,loadout,c)[1]==118,"attribute ceil/percentage/flat order");
    c={}; c.effects.add(0,2.1F); c.effects.add(10,3.9F,0);
    require(ordinary_physical_damage(right,loadout,c)[1]==106,"flat damage ceil/trunc ordering");
    c.damage_multiplier=.5F;
    require(ordinary_physical_damage(right,loadout,c)[1]==53,"final damage multiplier ordering");
    c={}; loadout.left=left; loadout.left->effects={}; c.effects.add(0x58,50);
    require(ordinary_physical_damage(right,loadout,c)[1]==150,"dual bonus missing");
    loadout.left.reset();
    require(ordinary_physical_damage(right,loadout,c)[1]==100,"dual bonus on single hand");
    right.traits.melee_specialization=true; right.traits.shared_specialization=true;
    c={}; c.effects.add(0x63,25); c.effects.add(0x67,50);
    require(ordinary_physical_damage(right,loadout,c)[1]==175,"weapon specialization effects missing");
    right.traits={}; right.traits.ranged=true; c={}; c.strength=99; c.dexterity=20;
    require(ordinary_physical_damage(right,loadout,c)[1]==120,"ranged arithmetic did not choose DEX");
    // Ranged arithmetic is tested in isolation; missile execution remains unavailable.
    right.traits={}; right.maximum_damage=16777216; c={}; c.effects.add(0,1); c.effects.add(10,1,0);
    require(ordinary_physical_damage(right,loadout,c)[1]==16777218,"integer additions rounded separately");
    bool rejected=false;
    try { c.effects.add(0x16,std::numeric_limits<float>::infinity()); }
    catch(const std::invalid_argument&) { rejected=true; }
    require(rejected,"nonfinite effect accepted");
    rejected=false;
    try { (void)ordinary_attack_speed(0,{}); }
    catch(const std::invalid_argument&) { rejected=true; }
    require(rejected,"zero weapon speed denominator accepted");
    rejected=false; right.maximum_damage=2147483520; c={}; c.effects.add(0,256);
    try { (void)ordinary_physical_damage(right,loadout,c); }
    catch(const std::overflow_error&) { rejected=true; }
    require(rejected,"out-of-domain damage overflow accepted");
}

}
int main() {
    try { clock_and_hits(); effects_and_selection(); channel_effects_and_guards();
        std::cout<<"PASS: "<<assertions<<" shared attack assertions\n"; return 0;
    } catch(const std::exception& e) { std::cerr<<"FAIL: "<<e.what()<<'\n'; return 1; }
}
