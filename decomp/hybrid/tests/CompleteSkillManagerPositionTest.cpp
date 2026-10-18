#include <cstring>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "SkillManager.h"
#include "Skill.h"
#include "Character.h"
#undef protected
#undef private
TL_ORIGINAL(Ogre::Vector3*,mpOld,(CSkillManager*,CSkill*,CBaseUnit*),"_ZN13CSkillManager19getPositionForSkillEP6CSkillP9CBaseUnit")
extern "C" Ogre::Vector3*mpNew(CSkillManager*,CSkill*,CBaseUnit*) __asm__("_ZN13CSkillManager19getPositionForSkillEP6CSkillP9CBaseUnit");
TL_FUNCTION(mpTarget,"_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(mpRange,"_ZN6CSkill8getRangeEv")
TL_FUNCTION(mpMin,"_ZN6CSkill11getRangeMinEv")
TL_FUNCTION(mpRandom,"_ZN6CSkill14getRandomRangeEv")
TL_FUNCTION(mpRandomMin,"_ZN6CSkill17getRandomRangeMinEv")
TL_FUNCTION(mpRng,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(mpPosition,"_ZN19CPositionableObject11getPositionEb")
extern "C" void*mpBaseTable[] __asm__("_ZTV9CBaseUnit");
namespace {
using namespace smallmass;
unsigned seed,rng,positionCalls;CSkill*skill;CSkillManager*manager;CBaseUnit*units[2];Ogre::Vector3 forwards[2];
unsigned type(){unsigned t[]={0,1,2,5,6,11,~0u};return t[seed%7];}
void ev(unsigned n){number(n);vector(manager->m_skillPosition);}
int target(CSkill*p){ev(1);number(p==skill);return type();}
float scalar(unsigned op){ev(op);float v[]={0,1,-1,2.25f,-4.5f,0.000000001f,17.75f,bits(0x7fc00000)};return v[(seed/7+op)%8];}
float range(CSkill*p){return scalar(2);}float minimum(CSkill*p){return scalar(3);}float randomRange(CSkill*p){return scalar(4);}float randomMin(CSkill*p){return scalar(5);}
float randomBetween(float lo,float hi){ev(6);floating(lo);floating(hi);float v[]={0,1,-1,0.5f,-0.75f,0.000000001f,bits(0x7fc00000)};return v[(seed/13+rng++)%7];}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){ev(7);number(p==units[0]);number(absolute);++positionCalls;if(seed%17==0)return Ogre::Vector3(1,2,3);return Ogre::Vector3(p==units[0]?-2.5f:6.25f,float(int(seed%7)-3),p==units[0]?3.75f:-8.5f);}
const Ogre::Vector3&forward(CBaseUnit*p){ev(8);number(p==units[0]);return forwards[p==units[0]?0:1];}
void positionSide(Case&c,bool ours,autotest::Capture&out){output=&out;seed=c.index;rng=positionCalls=0;skill=static_cast<CSkill*>(object(sizeof(CSkill)));manager=static_cast<CSkillManager*>(object(sizeof(CSkillManager)));new(&manager->m_Owner)TSafePointer<CBaseUnit>();void*vt[150];std::memcpy(vt,mpBaseTable,sizeof(vt));vt[2+0x130/8]=reinterpret_cast<void*>(&forward);for(unsigned i=0;i<2;++i){units[i]=static_cast<CBaseUnit*>(object(sizeof(CBaseUnit)));*reinterpret_cast<void***>(units[i])=vt+2;units[i]->m_fBaseUnitValue194=seed%11==0?bits(0x7fc00000):i?1.25f:-2.5f;forwards[i]=Ogre::Vector3(0.25f,-0.5f,0.75f);}skill->m_targetPosition=Ogre::Vector3(float(seed%5),float(seed%3),seed%19==0?bits(0x7fc00000):float(int(seed%9)-4));manager->m_Owner.m_pObject=seed&64?units[0]:NULL;CBaseUnit*t=seed&128?units[1]:NULL;if(type()==6 && t && !manager->m_Owner.getObject())manager->m_Owner.m_pObject=units[0];typedef Ogre::Vector3*(*Fn)(CSkillManager*,CSkill*,CBaseUnit*);Fn fn=ours?mpNew:mpOld;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3*r=fn(manager,skill,t);out.callCompleted=1;number(r==&manager->m_skillPosition);number(r==NULL);vector(manager->m_skillPosition);number(rng);number(positionCalls);}
}
TL_TEST(complete_skill_manager_position){detour::Set h;TL_REDIRECT(h,mpTarget,&target);TL_REDIRECT(h,mpRange,&range);TL_REDIRECT(h,mpMin,&minimum);TL_REDIRECT(h,mpRandom,&randomRange);TL_REDIRECT(h,mpRandomMin,&randomMin);TL_REDIRECT(h,mpRng,&randomBetween);TL_REDIRECT(h,mpPosition,&position);if(h.failed())return 1;return smallmass::run(host,0,"complete_skill_manager_position",0xcd1570,&positionSide,4096);}
