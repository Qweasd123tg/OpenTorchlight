#include "torchlight/skills.hpp"
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
void require(bool v,const char* s){++checks;if(!v)throw std::runtime_error(s);}
template<class F>void rejects(F f,const char* s){bool caught=false;try{f();}catch(const std::exception&){caught=true;}require(caught,s);}
void core(){
 require(original_cast_speed(0,0,1)==1,"cast default");
 require(original_cast_speed(-200,0,1)==.2F,"cast minimum");
 require(original_cast_speed(-50,50,2)==1.5F,"cast slow resistance");
 require(original_cast_speed(50,100,1)==1.5F,"positive cast speed resisted");
 rejects([]{(void)original_cast_speed(0,0,0);},"zero cast multiplier");
 TimedSkillEffect a{u"SAME",{},0x0f,6,30,30,30,true,7};
 std::vector<TimedSkillEffect> active;add_timed_skill_effects(active,{a});
 auto b=a;b.type=0x10;add_timed_skill_effects(active,{b});require(active.size()==2,"exclusive matched name only");
 a.value=5;a.duration=10;a.remaining=10;add_timed_skill_effects(active,{a});require(active.size()==2,"exclusive duplicate not removed");
 require(skill_attack_effects(active).get(0x0f)==5,"exclusive retained stronger old effect");
 require(!advance_timed_skill_effects(active,0),"paused buffs expired");
 require(advance_timed_skill_effects(active,10)&&active.size()==1,"exact expiry");
 require(advance_timed_skill_effects(active,100)&&active.empty(),"long-frame expiry");
 add_timed_skill_effects(active,{b});auto invalid=b;invalid.remaining=-1;
 rejects([&]{add_timed_skill_effects(active,{invalid});},"negative effect timer");require(active.size()==1,"failed add mutated active list");
 auto clip=std::make_shared<ModelAnimationClip>();clip->duration=1;clip->skeleton_path="test.skeleton";clip->animation_name="test";
 AnimationEventKey key;key.name="HIT";key.frame=6;clip->event_keys.push_back(key);
 SkillCast cast;cast.start(1,u"TEST",{{b},false},clip,1);cast.advance(.3F);
 require(cast.playback().frame_events().size()==1,"cast HIT time");
 auto event=cast.playback().frame_events().front();auto forged=event;forged.playback_generation++;
 require(!cast.consume(forged),"forged cast event");require(cast.consume(event),"valid cast event");require(!cast.consume(event),"duplicate cast event");
 cast.cancel();cast.start(1,u"TEST",{{b},false},clip,1);cast.advance(.3F);require(!cast.consume(event),"old generation replay");
 cast.advance(5);cast.finish_frame();require(!cast.active(),"finished cast remains active");
}
PlayerPrototype alchemist(const PakArchive& pak,UnitDefinitionLoader& definitions,const MasterResourceIndex& index){
 const auto players=load_playable_players(pak,index,definitions);for(const auto& p:players)if(p.name==u"ALCHEMIST"||p.name==u"Alchemist")return p;
 throw std::runtime_error("Alchemist absent");
}
void real(const char* path){
 PakArchive pak(path);auto catalog=std::make_shared<SkillCatalog>(pak);
 require(catalog->definitions().size()==407,"unexpected real skill count");
 const auto* def=catalog->find(u"Infuse");require(def&&def->maximum_investment==10&&def->ranks.size()==12,"Infuse rank catalog");
 for(int n=1;n<=10;++n){const auto* r=def->rank(n);if(!r->self_buff)throw std::runtime_error(r->unavailable_reason);
  require(r->mana_cost==n+11,"Infuse mana source");require(r->self_buff->effects.size()==3,"Infuse missing effect");
  require(r->self_buff->effects[1].value==25+n*5&&r->self_buff->effects[1].duration==25+n*5,"Infuse magnitude/duration source");}
 const auto* ember=catalog->find(u"Ember Bolt");require(ember&&ember->rank(1)&&!ember->rank(1)->self_buff&&!ember->rank(1)->unavailable_reason.empty(),"Ember Bolt silently mapped to self buff");
 const MasterResourceIndex index(parse_adm(pak.read_normalized("media/masterresourceunits.dat.adm")));UnitDefinitionLoader loader(pak);
 const auto proto=alchemist(pak,loader,index);PlayerSession p(proto,91);p.attach_skill_catalog(catalog);
 require(p.invest_skill(u"Infuse")==SkillUse::level_required,"early Infuse unlocked");
 while(p.progression().level<10){const auto gate=p.progression_rules()->gate(p.progression().level);require(p.award_experience(std::max(1,gate-p.progression().experience))>0,"level progression");}
 const auto points=p.progression().skill_points;
 require(p.invest_skill(u"Infuse")==SkillUse::learned&&p.progression().skill_points==points-1,"skill investment debit");
 const auto before=p.health().mana();require(before.has_value(),"Alchemist mana absent");
 require(p.begin_skill(u"Infuse",{})==SkillUse::missing_animation&&p.health().mana()==before,"failed cast spent mana");
 AttackAnimationCatalog animations(pak);const auto resolve=[&](auto m,auto prefix){return animations.resolve(m,prefix);};
 const auto base=p.combat().maximum_damage();
 require(p.begin_skill(u"Infuse",resolve)==SkillUse::started,"Infuse start");
 require(*p.health().mana()==*before-12,"cast mana debit");
 require(p.begin_skill(u"Infuse",resolve)==SkillUse::busy&&*p.health().mana()==*before-12,"double cast/debit");
 rejects([&]{(void)CheckpointAccess::capture(p);},"mid-cast checkpoint accepted");
 require(p.skills().effects.empty(),"buff before HIT");
 p.advance_skill_animation(.5F);const auto events=p.skill_cast().playback().frame_events();bool hit=false;
 for(const auto& e:events)if(e.key.name=="HIT"){require(p.perform_skill_event(e),"Infuse HIT");require(!p.perform_skill_event(e),"duplicate Infuse HIT");hit=true;}
 require(hit&&p.skills().effects.size()==3&&p.combat().maximum_damage()>base,"buff not connected to physical damage");
 p.advance_skill_animation(5);p.finish_skill_frame();require(!p.skill_cast().active(),"cast never finished");
 require(p.update_vitals(2)&&p.skills().effects[0].remaining==28,"buff time");
 auto saved=CheckpointAccess::capture(p);auto copy=CheckpointAccess::restore_player(proto,saved,91);copy.attach_skill_catalog(catalog);
 require(copy.combat().maximum_damage()==p.combat().maximum_damage(),"buff load missing/doubled");
 require(copy.skills().effects[0].remaining==28&&copy.health().mana()==p.health().mana(),"buff load refreshed duration/mana");
 require(copy.update_vitals(28)&&copy.skills().effects.empty()&&copy.combat().maximum_damage()==base,"buff expiry did not undo damage");
 const auto before_level=copy.progression().level;
 const auto remaining_points=copy.progression().skill_points;
 require(copy.award_experience(copy.progression_rules()->gate(before_level)-copy.progression().experience)==1,"level-up after invested skill rejected");
 require(copy.progression().skill_points==remaining_points+1,"level-up restores spent skill point");
 require(copy.invest_skill(u"Infuse")==SkillUse::learned,"rank2 investment at source-required level");
 require(p.begin_skill(u"Ember Bolt",resolve)==SkillUse::unsupported,"unsupported skill executes partially");
 CampaignCheckpoint campaign;campaign.slot="skills";campaign.character_name="Skills";campaign.resource_identity=1;campaign.class_guid=proto.guid;
 FloorCheckpoint floor;floor.address={u"Town",0};floor.layout_identity=1;campaign.floors.push_back(floor);campaign.player=saved;
 auto forged=saved;
 for(auto& state:forged.skills->skills)if(state.name==u"INFUSE")state.cooldown=1;
 rejects([&]{auto bad=CheckpointAccess::restore_player(proto,forged,91);bad.attach_skill_catalog(catalog);},"forged resource cooldown accepted");
 forged=saved;
 for(auto& state:forged.skills->skills)if(state.name==u"INFUSE")state.invested=2;
 --forged.progression->skill_points;
 rejects([&]{auto bad=CheckpointAccess::restore_player(proto,forged,91);bad.attach_skill_catalog(catalog);},"rank2 below source gate accepted from save");
 auto bytes=encode_checkpoint(campaign);require(bytes[8]==kCheckpointFormatVersion,"new skill save version");
 auto decoded=decode_checkpoint(bytes);require(decoded.player.skills&&decoded.player.skills->effects[0].remaining==28,"skill codec loses timer");
 std::cout<<"catalog="<<catalog->definitions().size()<<" infuse_ranks=10\n";
}
}
int main(int argc,char**argv){try{core();if(argc==2)real(argv[1]);std::cout<<"PASS skills checks="<<checks<<'\n';return 0;}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
