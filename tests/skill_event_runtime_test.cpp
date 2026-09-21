// Bounded dispatch regression, not full original skill or renderer parity.
#include "torchlight/skill_event_runtime.hpp"
#include "torchlight/skills.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
namespace {
using namespace torchlight;
int checks=0;
void require(bool ok,const char* message){++checks;if(!ok)throw std::runtime_error(message);}
LayoutManifest scene(std::u16string group=u"Missiles",std::uint32_t count=1){
    LayoutManifest result;LayoutObject o;o.id=5;o.descriptor=u"Unit Spawner";o.name=u"Unit Spawner0";
    o.properties={{0,u"SPAWN ON CREATE",AdmValueType::boolean,true},
        {0,u"GROUP",AdmValueType::string,std::move(group)},
        {0,u"RESOURCE",AdmValueType::string,std::u16string(u"SHOT")},
        {0,u"COUNT",AdmValueType::unsigned_integer,count}};
    result.objects.push_back(std::move(o));return result;
}
std::shared_ptr<SkillEventProgram> program(LayoutManifest layout=scene()){
    auto p=std::make_shared<SkillEventProgram>();
    p->events.push_back({SkillEventType::trigger,"synthetic-trigger",std::move(layout),40,60,true,false});return p;
}
SkillCastContext context(){SkillCastContext c;c.caster_id=7;c.origin={1,2,3};c.direction={1,0,0};c.skill_level=2;c.cooldown_seconds=2.5F;return c;}
void fire(SkillEventRuntime& r,std::uint64_t id){
    require(r.start_skill(context()).started,"admission failed");
    require(r.take_missile_launches().empty(),"absent START manufactured TRIGGER");
    require(r.trigger(SkillEventType::trigger),"TRIGGER failed");
    r.drain_launches([id](const SkillMissileLaunch&){return SkillMissileFireOutcome{id,{}};});
    (void)r.take_skill_events();
}
void core(){
    require(skill_event_type_name(SkillEventType::trigger)==u"EVENT_TRIGGER","event names");
    require(skill_event_type_name(static_cast<SkillEventType>(-1)).empty()&&skill_event_type_name(static_cast<SkillEventType>(11)).empty(),"invalid event names");
    SkillEventRuntime absent("none",nullptr);
    require(absent.start_skill(context()).issue=="no_skill_program","null program");
    auto c=context();c.caster_id=0;require(absent.start_skill(c).issue=="no_caster","caster guard order");
    auto p=program();SkillEventRuntime gates("gates",p);
    c=context();c.caster_alive=false;require(gates.start_skill(c).issue=="caster_down","dead admission");
    c=context();c.chance_passed=false;require(gates.start_skill(c).issue=="chance","chance admission");
    c=context();c.cooldown_remaining=1;require(gates.start_skill(c).issue=="cooldown","cooldown admission");
    c=context();c.cooldown_remaining=-1;require(gates.start_skill(c).issue=="invalid_cooldown","negative cooldown");
    c=context();c.cooldown_seconds=std::numeric_limits<float>::infinity();require(gates.start_skill(c).issue=="invalid_cooldown","infinite cooldown");
    c=context();c.skill_level=0;require(gates.start_skill(c).issue=="level","zero rank");
    c=context();c.origin[0]=std::numeric_limits<float>::quiet_NaN();require(gates.start_skill(c).issue=="position","NaN origin");
    c=context();c.direction={};require(gates.start_skill(c).issue=="direction","zero direction");
    require(!gates.active()&&!gates.has_pending_missiles(),"refusal mutation");
    require(!gates.trigger(SkillEventType::trigger),"inactive trigger");
    require(gates.start_skill(context()).started&&gates.active(),"handlerless START must succeed");
    require(gates.cooldown_at_start()==2.5F&&gates.take_skill_events().empty(),"START snapshot");
    require(gates.start_skill(context()).issue=="busy","active recast");
    require(!gates.trigger(SkillEventType::end)&&!gates.trigger(static_cast<SkillEventType>(99)),"missing/invalid handler");
    gates.stop();require(gates.start_skill(context()).started,"stopped restart");

    SkillEventRuntime hits("hits",p);fire(hits,100);unsigned calls=0;
    const auto sink=[&](const SkillWeaponDamageRequest& q){
        ++calls;const auto before=hits.take_skill_events();
        require(before.size()==1&&before[0].type==SkillEventType::missile_hit,"MISSILEHIT must precede weapon sink");
        require(q.missile_id==100&&q.caster_id==7&&q.skill_level==2,"request identity");
        require(q.weapon_damage_pct==40&&q.soak_scale_pct==60&&q.use_dps,"request profile");
        return SkillWeaponDamageOutcome{true,q.victim_id==11};
    };
    require(hits.notify_missile_impact(100,11,false,false,sink),"first victim");auto events=hits.take_skill_events();
    require(events.size()==2&&events[0].type==SkillEventType::unit_hit&&events[1].type==SkillEventType::unit_die,"death post order");
    require(events[0].victim_id==11&&!events[0].damage_application_open,"applied identity");
    require(hits.has_pending_missiles(),"first victim retired missile");
    require(!hits.notify_missile_impact(100,11,false,false,sink)&&calls==1,"duplicate victim");
    require(hits.notify_missile_impact(100,12,false,false,sink),"second distinct victim");events=hits.take_skill_events();
    require(events.size()==1&&events[0].type==SkillEventType::unit_hit&&calls==2,"nonlethal post order");
    hits.stop();require(hits.has_pending_missiles(),"cast stop discarded live missile");
    require(hits.start_skill(context()).issue=="busy","in-flight reuse");hits.retire_missile(100);
    require(!hits.has_pending_missiles()&&!hits.notify_missile_impact(100,13,false,false,sink),"retired impact");

    SkillEventRuntime missing("missing",p);fire(missing,200);
    require(missing.notify_missile_impact(200,8,false,false,{}),"missing sink collision");events=missing.take_skill_events();
    require(events.size()==2&&events[0].type==SkillEventType::missile_hit&&events[1].damage_application_open,"missing sink falsely applied");
    require(missing.notify_missile_impact(200,9,false,false,[](const SkillWeaponDamageRequest&){return SkillWeaponDamageOutcome{false,true};}),"unapplied collision");
    events=missing.take_skill_events();require(events.size()==2&&events[0].type==SkillEventType::missile_hit&&events[1].type==SkillEventType::unit_hit,"unapplied death manufactured");
    require(missing.notify_missile_impact(200,0,true,false,{}),"blocked collision");events=missing.take_skill_events();
    require(events.size()==1&&events[0].type==SkillEventType::missile_die&&events[0].blocked&&!events[0].expired&&missing.has_pending_missiles(),"blocked batch ownership");
    require(!missing.notify_missile_impact(200,0,true,false,{}),"duplicate terminal collision");
    require(missing.notify_missile_impact(200,10,false,false,[](const auto&){return SkillWeaponDamageOutcome{true,false};}),"terminal discarded following splash victim");
    missing.retire_missile(200);require(!missing.has_pending_missiles(),"terminal batch not retired");

    auto timed=scene();timed.timeline_points.push_back({1,5,u"Spawn Units",0});
    timed.timeline_points.push_back({1,5,u"Spawn Units",.5F});timed.timeline_points.push_back({1,999,u"Spawn Units",0});
    SkillEventRuntime timeline("timeline",program(std::move(timed)));
    require(timeline.start_skill(context()).started&&timeline.trigger(SkillEventType::trigger),"timeline start");
    require(timeline.take_missile_launches().size()==2,"t=0 dispatch");
    require(timeline.take_deferred_timeline_points().size()==2,"deferred points executed");
    SkillEventRuntime unsupported("unsupported",program(scene(u"Particle")));
    require(unsupported.start_skill(context()).started&&unsupported.trigger(SkillEventType::trigger),"unsupported scene start");
    require(unsupported.take_missile_launches().empty()&&unsupported.take_unsupported_spawns().size()==1,"unsupported spawn hidden");
    SkillEventRuntime count("count",program(scene(u"Missiles",3)));
    require(count.start_skill(context()).started&&count.trigger(SkillEventType::trigger),"COUNT start");
    count.drain_launches({});require(count.has_pending_missiles(),"empty consumer lost launch");
    count.drain_launches([&](const SkillMissileLaunch& l){require(l.spawner_count==3&&l.repeated_count_open,"COUNT boundary");return SkillMissileFireOutcome{0,"template_missing"};});
    auto refused=count.take_refused_launches();require(refused.size()==1&&refused[0].issue=="template_missing"&&!count.has_pending_missiles(),"refusal lost");
    SkillEventRuntime zero("zero",program(scene(u"Missiles",0)));
    require(zero.start_skill(context()).started&&zero.trigger(SkillEventType::trigger)&&zero.take_missile_launches().empty(),"zero-count request manufactured missile");
    SkillEventRuntime duplicate("duplicate",p);fire(duplicate,300);
    require(duplicate.trigger(SkillEventType::trigger),"second trigger");
    duplicate.drain_launches([](const SkillMissileLaunch&){return SkillMissileFireOutcome{300,{}};});
    refused=duplicate.take_refused_launches();require(refused.size()==1&&refused[0].issue=="duplicate_missile_id","duplicate ID accepted");
}
void real(const char* directory){
    PakArchive archive(std::string(directory)+"/pak.zip");LevelSceneLoader loader(archive);SkillCatalog catalog(archive);
    const auto* skill=catalog.find(u"Seeking Shot");require(skill&&skill->rank(1),"real rank absent");
    auto p=std::make_shared<SkillEventProgram>(compile_skill_event_program(skill->rank(1)->resource,loader));
    SkillEventRuntime runtime("Seeking Shot",p);
    require(runtime.has_event(SkillEventType::start)&&runtime.has_event(SkillEventType::trigger),"real event handlers");
    require(runtime.start_skill(context()).started,"real START refused");
    require(runtime.take_missile_launches().empty(),"warmup START fired missile");auto events=runtime.take_skill_events();
    require(events.size()==1&&events[0].type==SkillEventType::start&&events[0].layout_path.find("warmup.layout")!=std::string::npos,"real START source");
    require(runtime.trigger(SkillEventType::trigger),"real TRIGGER refused");events=runtime.take_skill_events();
    require(events.size()==1&&events[0].type==SkillEventType::trigger&&events[0].layout_path.find("seeking.layout")!=std::string::npos,"real TRIGGER source");
    unsigned launches=0;
    runtime.drain_launches([&](const SkillMissileLaunch& l){++launches;
        require(l.missile_resource=="SEEKINGSHOT"&&l.caster_id==7&&l.origin==context().origin&&l.direction==context().direction,"real launch identity");
        require(l.spawner_count==3&&l.repeated_count_open,"real COUNT boundary hidden");return SkillMissileFireOutcome{400,{}};});
    require(launches==1,"real request count");
    require(runtime.notify_missile_impact(400,77,false,false,[&](const SkillWeaponDamageRequest& q){
        const auto before=runtime.take_skill_events();require(before.size()==1&&before[0].type==SkillEventType::missile_hit,"real pre-damage hook order");
        require(q.weapon_damage_pct==40&&q.soak_scale_pct==60&&q.use_dps,"real damage profile");return SkillWeaponDamageOutcome{true,true};}),"real impact refused");
    events=runtime.take_skill_events();require(events.size()==2&&events[1].type==SkillEventType::unit_die,"real death post");
    runtime.retire_missile(400);require(!runtime.has_pending_missiles(),"real retirement");
}
}
int main(){try{core();if(const char* dir=std::getenv("TORCHLIGHT_GAME_DIR"))real(dir);else std::cout<<"SKIP real resources: TORCHLIGHT_GAME_DIR unset\n";
    std::cout<<"PASS skill_event_runtime checks="<<checks<<'\n';return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
