#include <cstring>
#include <string>
#include <map>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "Skill.h"
#include "SkillEvent.h"
#include "SkillProperty.h"
#undef protected
#undef private
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(void,ssOldAttempt,ssNewAttempt,(CSkill*),"_ZN6CSkill18attemptToStopSkillEv")
DECL(void,ssOldStop,ssNewStop,(CSkill*),"_ZN6CSkill9stopSkillEv")
DECL(void,ssOldUpdate,ssNewUpdate,(CSkill*,float),"_ZN6CSkill11updateSkillEf")
DECL(bool,ssOldTrigger,ssNewTrigger,(CSkill*,ESKILL_EVENT_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,CBaseUnit*,const Ogre::Vector3*),"_ZN6CSkill12triggerEventE17ESKILL_EVENT_TYPERKN4Ogre7Vector3ERKNS1_10QuaternionEP9CBaseUnitPS3_")
#undef DECL
TL_FUNCTION(ssCan,"_ZN11CSkillEvent7canStopEv")
TL_FUNCTION(ssReset,"_ZN11CSkillEvent10resetEventEv")
TL_FUNCTION(ssEventStop,"_ZN11CSkillEvent9stopEventEv")
TL_FUNCTION(ssEventUpdate,"_ZN11CSkillEvent11updateEventEf")
TL_FUNCTION(ssTrigger,"_ZN6CSkill12triggerEventE17ESKILL_EVENT_TYPERKN4Ogre7Vector3ERKNS1_10QuaternionEP9CBaseUnitPS3_")
TL_FUNCTION(ssPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(ssRemoveSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(ssStart,"_ZN11CSkillEvent10startEventEP9CBaseUnitP14CSkillPropertyN4Ogre7Vector3ERKNS4_10QuaternionES1_PKS5_")
TL_FUNCTION(ssClone,"_ZN14CSkillProperty18cloneEventForSkillEP11CSkillEvent")
namespace {
using namespace smallmass;
CSkill*self;CBaseUnit*owner;CSkillEvent*events[5];CSkillEvent*cloned[5];unsigned seed;
int id(const void*p){if(!p)return -1;if(p==self)return 1;if(p==owner)return 2;for(unsigned i=0;i<5;++i)if(p==events[i])return 10+i;for(unsigned i=0;i<5;++i)if(p==cloned[i])return 20+i;return -2;}
void ev(unsigned e,const void*p){number(e);number(id(p));}
bool can(CSkillEvent*p){ev(1,p);return (seed/8+id(p))%4!=0;}
void reset(CSkillEvent*p){ev(2,p);}
void stop(CSkillEvent*p){ev(3,p);if(seed%17==0)self->m_animationSpeed+=0.25f;}
bool update(CSkillEvent*p,float dt){ev(4,p);floating(dt);if(seed%19==0)self->m_animationSpeed+=0.5f;return (seed/16+id(p))%3!=0;}
Ogre::Quaternion orientation(CBaseUnit*p){ev(5,p);return Ogre::Quaternion(0.25f,0.5f,-0.75f,1.0f);}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){ev(6,p);number(absolute);return Ogre::Vector3(float(seed),2,-3);}
bool trigger(CSkill*p,ESKILL_EVENT_TYPE type,const Ogre::Vector3&v,const Ogre::Quaternion&q,CBaseUnit*t,const Ogre::Vector3*to){ev(7,p);number(type);vector(v);output->add(&q,sizeof(q));number(id(t));number(to!=NULL);return seed&32;}
void removeSafe(CRunicCore*p,TSafePointer<void*>*ref,unsigned index){ev(8,p);number(reinterpret_cast<char*>(ref)-reinterpret_cast<char*>(self));number(index);}
bool startEvent(CSkillEvent*p,CBaseUnit*u,CSkillProperty*property,Ogre::Vector3 v,const Ogre::Quaternion&q,CBaseUnit*t,const Ogre::Vector3*to){ev(9,p);number(id(u));number(property==self->m_property);vector(v);output->add(&q,sizeof(q));number(id(t));number(to!=NULL);if(to)vector(*to);p->m_started=true;return seed&2;}
CSkillEvent*cloneEvent(CSkillProperty*p,CSkillEvent*event){number(10);number(p==self->m_property);number(id(event));unsigned i=id(event)-10;if(seed%7==0)return NULL;p->m_eventLists[seed/3%11]->add(cloned[i]);return cloned[i];}
void side(Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;self=static_cast<CSkill*>(object(sizeof(CSkill)));owner=static_cast<CBaseUnit*>(object(sizeof(CBaseUnit)));
 void* vt[64];std::memset(vt,0,sizeof(vt));vt[0xf0/8]=reinterpret_cast<void*>(&orientation);*reinterpret_cast<void***>(owner)=vt;
 self->m_pOwner=seed&1?owner:NULL;self->m_eActivationType=seed&2?SKILL_ACTIVATION_PASSIVE:SKILL_ACTIVATION_NORMAL;
 self->m_interruptible=seed&4;self->m_pendingStop=seed&8;self->m_animationIndexLoopInto=seed&16?2:static_cast<unsigned>(-1);
 const float times[]={-2,0,0.25f,1,4,bits(0x7fc00001),bits(0xff800000),bits(0x7f800000)};
 self->m_animationTimeRemaining=times[(seed/3)%8];self->m_elapsedSkillTime=times[(seed/7)%8];self->m_animationSpeed=times[(seed/11)%5];self->m_coolingTime=7;
 self->m_targetPosition=Ogre::Vector3(9,8,7);new(&self->m_Target)TSafePointer<CBaseUnit>();self->m_Target.m_pObject=seed&64?owner:NULL;self->m_Target.m_nIndex=77;
 new(&self->m_activeEvents)TArrayList<CSkillEvent*>(2);
 for(unsigned i=0;i<5;++i){events[i]=static_cast<CSkillEvent*>(object(sizeof(CSkillEvent)));cloned[i]=static_cast<CSkillEvent*>(object(sizeof(CSkillEvent)));events[i]->m_started=(seed+i)%3!=0;events[i]->m_canClone=(seed/2+i)%2;events[i]->m_cloneSource=(seed/7+i)%5==0?cloned[i]:NULL;}
 for(unsigned i=0;i<seed%6;++i)self->m_activeEvents.add(events[i]);
 CSkillProperty* property=static_cast<CSkillProperty*>(object(sizeof(CSkillProperty)));new(&property->m_eventLists)TArrayList<TArrayList<CSkillEvent*>*>(2);
 property->m_bContinuousLooping=seed&128;property->m_fDurationOverride=times[(seed/13)%8];property->m_fMinimumTime=1234;
 TArrayList<CSkillEvent*> groups[11];for(unsigned i=0;i<11;++i){if(c.op==3){for(unsigned j=0;j<seed%6;++j)groups[i].add(events[j]);}else if((i+seed)%3==0)groups[i].add(events[i%5]);property->m_eventLists.add(&groups[i]);}
 self->m_property=c.op==2||c.op==3?property:(seed&256?property:NULL);if(c.op==3&&seed%13==0)self->m_property=NULL;
 float dt=times[(seed/17)%8];
 if(c.op==3){typedef bool(*Fn)(CSkill*,ESKILL_EVENT_TYPE,const Ogre::Vector3&,const Ogre::Quaternion&,CBaseUnit*,const Ogre::Vector3*);Fn fn=ours?ssNewTrigger:ssOldTrigger;Ogre::Vector3 v(1,2,3),to(-4,-5,-6);Ogre::Quaternion q(0.25f,0.5f,-0.75f,1);if(!autotest::beginInvocation(out,fn))return;number(fn(self,static_cast<ESKILL_EVENT_TYPE>(seed/3%13),v,q,owner,seed&1?&to:NULL));}
 else if(c.op==2){typedef void(*Fn)(CSkill*,float);Fn fn=ours?ssNewUpdate:ssOldUpdate;if(!autotest::beginInvocation(out,fn))return;fn(self,dt);}
 else {typedef void(*Fn)(CSkill*);Fn fn=c.op==0?(ours?ssNewAttempt:ssOldAttempt):(ours?ssNewStop:ssOldStop);if(!autotest::beginInvocation(out,fn))return;fn(self);}
 out.callCompleted=1;number(self->m_interruptible);number(self->m_pendingStop);floating(self->m_animationTimeRemaining);floating(self->m_elapsedSkillTime);floating(self->m_animationSpeed);floating(self->m_coolingTime);vector(self->m_targetPosition);number(id(self->m_Target.m_pObject));number(self->m_Target.m_nIndex);
 number(self->m_activeEvents.size());number(self->m_activeEvents.m_nCapacity);for(unsigned i=0;i<self->m_activeEvents.size();++i)number(id(self->m_activeEvents[i]));
 self->m_Target.m_pObject=NULL;self->m_activeEvents.~TArrayList<CSkillEvent*>();property->m_eventLists.~TArrayList<TArrayList<CSkillEvent*>*>();
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned cases){detour::Set h;TL_REDIRECT(h,ssCan,&can);TL_REDIRECT(h,ssReset,&reset);TL_REDIRECT(h,ssEventStop,&stop);TL_REDIRECT(h,ssEventUpdate,&update);if(op!=3)TL_REDIRECT(h,ssTrigger,&trigger);TL_REDIRECT(h,ssStart,&startEvent);TL_REDIRECT(h,ssClone,&cloneEvent);TL_REDIRECT(h,ssPosition,&position);TL_REDIRECT(h,ssRemoveSafe,&removeSafe);if(h.failed())return 1;return smallmass::run(host,op,name,address,&side,cases);}
}
TL_TEST(complete_skill_attempt_stop){return run(host,0,"complete_skill_attempt_stop",0xc9d610,512);}
TL_TEST(complete_skill_stop){return run(host,1,"complete_skill_stop",0xca5f80,512);}
TL_TEST(complete_skill_update){return run(host,2,"complete_skill_update",0xca6160,2048);}

TL_TEST(complete_skill_trigger){return run(host,3,"complete_skill_trigger",0xca5950,2048);}
