#include <cstring>
#include <map>
#include <string>
#include <new>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "SkillEvent.h"
#include "SkillProperty.h"
#include "SkillEffectAndAffixes.h"
#include "ParticleWrapper.h"
#include "DamageShape.h"
#include "Layout.h"
#include "UnitSpawner.h"
#include "Missile.h"
#undef protected
#undef private
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(bool,seOldCan,seNewCan,(CSkillEvent*,CBaseUnit*,CCharacter*),"_ZN11CSkillEvent35canAffixesAndEffectsBeAppliedToUnitEP9CBaseUnitP10CCharacter")
DECL(std::wstring,seOldStats,seNewStats,(CSkillEvent*,CSkillProperty*),"_ZN11CSkillEvent15getDisplayStatsEP14CSkillProperty")
DECL(bool,seOldPos,seNewPos,(CSkillEvent*,const Ogre::Vector3&,CPositionableObject*),"_ZN11CSkillEvent18canEffectPosObjectERKN4Ogre7Vector3EP19CPositionableObject")
DECL(bool,seOldEnemy,seNewEnemy,(CSkillEvent*,CBaseUnit*),"_ZN11CSkillEvent18effectsTargetEnemyEP9CBaseUnit")
DECL(bool,seOldShould,seNewShould,(CSkillEvent*),"_ZN11CSkillEvent10shouldStopEv")
DECL(bool,seOldStop,seNewStop,(CSkillEvent*),"_ZN11CSkillEvent7canStopEv")
DECL(void,seOldDisable,seNewDisable,(CSkillEvent*),"_ZN11CSkillEvent22disableAllDamageShapesEv")
DECL(void,seOldParticles,seNewParticles,(CSkillEvent*,bool),"_ZN11CSkillEvent16stopAllParticlesEb")
DECL(void,seOldStopEvent,seNewStopEvent,(CSkillEvent*),"_ZN11CSkillEvent9stopEventEv")
DECL(void,seOldResetEvent,seNewResetEvent,(CSkillEvent*),"_ZN11CSkillEvent10resetEventEv")
#undef DECL
TL_ORIGINAL(void,seCtor,(CSkillEvent*,CSkill*,CSkillProperty*,CResourceManager*,CDataGroup*),"_ZN11CSkillEventC1EP6CSkillP14CSkillPropertyP16CResourceManagerP10CDataGroup")
TL_FUNCTION(seCan,"_ZN22CSkillEffectAndAffixes35canAffixesAndEffectsBeAppliedToUnitEP9CBaseUnitP10CCharacter")
TL_FUNCTION(seStats,"_ZN22CSkillEffectAndAffixes15getDisplayStatsEv")
TL_FUNCTION(seEnemy,"_ZN22CSkillEffectAndAffixes18effectsTargetEnemyEP9CBaseUnit")
TL_FUNCTION(sePosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(seTimelines,"_ZN12CEditorScene28getNumberOfTimelinesUpdatingEb")
TL_FUNCTION(seObjects,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(seSpawnerVisible,"_ZN12CUnitSpawner24getParticlesStillVisibleEv")
TL_FUNCTION(seSpawnerStop,"_ZN12CUnitSpawner16stopAllParticlesEv")
TL_FUNCTION(seLayoutStop,"_ZN7CLayout4stopEb")
namespace {
using namespace smallmass;
unsigned seed;void*objects[12];Ogre::Vector3 pos;std::wstring stats;
int id(const void*p){if(!p)return -1;for(unsigned i=0;i<12;++i)if(p==objects[i])return i;return -2;}
void call(unsigned k,const void*p){number(k);number(id(p));}
bool can(CSkillEffectAndAffixes*p,CBaseUnit*u,CCharacter*c){call(1,p);number(id(u));number(id(c));return seed&2;}
std::wstring getStats(CSkillEffectAndAffixes*p){call(2,p);return stats;}
bool enemy(CSkillEffectAndAffixes*p,CBaseUnit*u){call(3,p);number(id(u));return seed&8;}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){call(4,p);number(absolute);return pos;}
unsigned timelines(CEditorScene*p,bool exclude){call(5,p);number(exclude);return seed&64?2:0;}
unsigned particles(CEditorScene*p){call(6,p);return seed&128?3:0;}
bool spawnerVisible(CUnitSpawner*p){call(7,p);return seed%7==0 && p==objects[10];}
void spawnerStop(CUnitSpawner*p){call(8,p);}
void layoutStop(CLayout*p,bool immediate){call(9,p);number(immediate);}
void shapeEnabled(CDamageShape*p,bool enabled){call(10,p);number(enabled);}
void particleStop(CParticleWrapper*p){call(11,p);}
void objectsOf(CEditorScene*p,const std::wstring&name,TArrayList<CEditorBaseObject*>*result){
 call(12,p);text(name);number(result->size());number(result->m_nGrowBy);
 unsigned count=seed%3;
 for(unsigned i=0;i<count;++i)result->add(static_cast<CEditorBaseObject*>(objects[(name==L"Damage Shape"?4:name==L"Particle"?6:8)+i]));
}
void eventSide(Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;stats=seed&1?L"damage Ж":L"";
 new(reinterpret_cast<void*>(0x14f0ca8))std::wstring();
 for(unsigned i=0;i<12;++i)objects[i]=object(0x400);
 CSkillEvent*self=static_cast<CSkillEvent*>(object(sizeof(CSkillEvent)));seCtor(self,NULL,NULL,NULL,NULL);
 CSkill*skill=static_cast<CSkill*>(object(sizeof(CSkill)));self->m_pSkill=skill;
 CSkillProperty*property=static_cast<CSkillProperty*>(object(sizeof(CSkillProperty)));self->m_pSkillProperty=seed&1?property:NULL;
 property->m_pSkillEffectAndAffixes=seed&4?static_cast<CSkillEffectAndAffixes*>(objects[2]):NULL;
 self->m_pSkillEffectAndAffixes=seed&2?static_cast<CSkillEffectAndAffixes*>(objects[1]):NULL;
 self->m_initialProperty=seed&8?property:NULL;self->m_statsHidden=seed&16;
 CEditorScene*scene=static_cast<CEditorScene*>(objects[3]);void*sceneVT[72];std::memset(sceneVT,0,sizeof(sceneVT));sceneVT[0x220/8]=reinterpret_cast<void*>(&particles);*reinterpret_cast<void***>(scene)=sceneVT;
 self->m_pEditorScene=seed&32?scene:NULL;
 void*shapeVT[70];void*particleVT[70];std::memset(shapeVT,0,sizeof(shapeVT));std::memset(particleVT,0,sizeof(particleVT));shapeVT[0x40/8]=reinterpret_cast<void*>(&shapeEnabled);particleVT[0x200/8]=reinterpret_cast<void*>(&particleStop);
 for(unsigned i=4;i<6;++i)*reinterpret_cast<void***>(objects[i])=shapeVT;
 for(unsigned i=6;i<8;++i)*reinterpret_cast<void***>(objects[i])=particleVT;
 for(unsigned i=0;i<seed%3;++i)self->m_spawners.add(static_cast<CUnitSpawner*>(objects[10+i%2]));
 const float times[]={-1,0,0.5f,bits(0x7fc00001),bits(0xff800000),bits(0x7f800000)};self->m_remainingTime=times[(seed/4)%6];
 skill->m_animationIndexLoopInto=seed&256?2:static_cast<unsigned>(-1);skill->m_eActivationType=seed&512?SKILL_ACTIVATION_PASSIVE:SKILL_ACTIVATION_NORMAL;
 TSafePointer<CMissile> weak; if(seed&1024)self->m_missiles.add(&weak);
 self->m_active=true;self->m_started=true;
 pos=Ogre::Vector3(91,2,-11);Ogre::Vector3 point(-99,float(int(seed%9)-4)+pos.y,77);if(seed&16)point.y=bits(0x7fc00001);if(seed&32)pos.y=bits(0x7f800000);
 bool result=false;
 switch(c.op){
 case 0:{typedef bool(*Fn)(CSkillEvent*,CBaseUnit*,CCharacter*);Fn fn=ours?seNewCan:seOldCan;if(!autotest::beginInvocation(out,fn))return;result=fn(self,static_cast<CBaseUnit*>(objects[0]),static_cast<CCharacter*>(objects[11]));break;}
 case 1:{typedef std::wstring(*Fn)(CSkillEvent*,CSkillProperty*);Fn fn=ours?seNewStats:seOldStats;if(!autotest::beginInvocation(out,fn))return;std::wstring value=fn(self,seed&32?property:NULL);text(value);break;}
 case 2:{typedef bool(*Fn)(CSkillEvent*,const Ogre::Vector3&,CPositionableObject*);Fn fn=ours?seNewPos:seOldPos;if(!autotest::beginInvocation(out,fn))return;result=fn(self,point,static_cast<CPositionableObject*>(objects[0]));break;}
 case 3:{typedef bool(*Fn)(CSkillEvent*,CBaseUnit*);Fn fn=ours?seNewEnemy:seOldEnemy;if(!autotest::beginInvocation(out,fn))return;result=fn(self,static_cast<CBaseUnit*>(objects[0]));break;}
 case 4:case 5:{typedef bool(*Fn)(CSkillEvent*);Fn fn=c.op==4?(ours?seNewShould:seOldShould):(ours?seNewStop:seOldStop);if(!autotest::beginInvocation(out,fn))return;result=fn(self);break;}
 case 7:{typedef void(*Fn)(CSkillEvent*,bool);Fn fn=ours?seNewParticles:seOldParticles;if(!autotest::beginInvocation(out,fn))return;fn(self,seed&4);break;}
 default:{typedef void(*Fn)(CSkillEvent*);Fn fn=c.op==6?(ours?seNewDisable:seOldDisable):c.op==8?(ours?seNewStopEvent:seOldStopEvent):(ours?seNewResetEvent:seOldResetEvent);if(!autotest::beginInvocation(out,fn))return;fn(self);break;}
 }
 out.callCompleted=1;number(result);number(self->m_active);number(self->m_started);
 self->m_spawners.~TArrayList<CUnitSpawner*>();self->m_missiles.~TArrayList<TSafePointer<CMissile>*>();
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned cases){
 detour::Set h;TL_REDIRECT(h,seCan,&can);TL_REDIRECT(h,seStats,&getStats);TL_REDIRECT(h,seEnemy,&enemy);TL_REDIRECT(h,sePosition,&position);TL_REDIRECT(h,seTimelines,&timelines);TL_REDIRECT(h,seObjects,&objectsOf);TL_REDIRECT(h,seSpawnerVisible,&spawnerVisible);TL_REDIRECT(h,seSpawnerStop,&spawnerStop);TL_REDIRECT(h,seLayoutStop,&layoutStop);if(h.failed())return 1;
 return smallmass::run(host,op,name,address,&eventSide,cases);
}
}
TL_TEST(complete_event_can_apply){return run(host,0,"complete_event_can_apply",0xcb6fa0,32);}
TL_TEST(complete_event_display_stats){return run(host,1,"complete_event_display_stats",0xcb71e0,64);}
TL_TEST(complete_event_vertical_range){return run(host,2,"complete_event_vertical_range",0xcb7240,64);}
TL_TEST(complete_event_targets_enemy){return run(host,3,"complete_event_targets_enemy",0xcb7820,32);}
TL_TEST(complete_event_should_stop){return run(host,4,"complete_event_should_stop",0xcb85d0,1536);}
TL_TEST(complete_event_can_stop){return run(host,5,"complete_event_can_stop",0xcb86c0,1536);}
TL_TEST(complete_event_disable_shapes){return run(host,6,"complete_event_disable_shapes",0xcc3980,96);}
TL_TEST(complete_event_stop_particles){return run(host,7,"complete_event_stop_particles",0xcc4010,96);}
TL_TEST(complete_event_stop){return run(host,8,"complete_event_stop",0xcc42a0,96);}
TL_TEST(complete_event_reset){return run(host,9,"complete_event_reset",0xcc42e0,96);}
