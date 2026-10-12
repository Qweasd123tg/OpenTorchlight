#include "SmallMassCompare.h"
TL_ORIGINAL(bool, original0, (void*), "_ZN8CMonster17hasOffensiveSkillEv")
extern "C" bool candidate0(void*) __asm__("_ZN8CMonster17hasOffensiveSkillEv");
TL_ORIGINAL(bool, original1, (void*), "_ZN8CMonster17hasDefensiveSkillEv")
extern "C" bool candidate1(void*) __asm__("_ZN8CMonster17hasDefensiveSkillEv");
TL_ORIGINAL(void, original2, (void*,bool), "_ZN8CMonster20selectOffensiveSkillEb")
extern "C" void candidate2(void*,bool) __asm__("_ZN8CMonster20selectOffensiveSkillEb");
TL_ORIGINAL(void, original3, (void*), "_ZN8CMonster20selectDefensiveSkillEv")
extern "C" void candidate3(void*) __asm__("_ZN8CMonster20selectDefensiveSkillEv");
TL_ORIGINAL(void, original4, (void*,float), "_ZN10CCharacter17updateActiveSkillEf")
extern "C" void candidate4(void*,float) __asm__("_ZN10CCharacter17updateActiveSkillEf");
TL_ORIGINAL(bool, original5, (void*), "_ZN10CCharacter24attemptStopOfActiveSkillEv")
extern "C" bool candidate5(void*) __asm__("_ZN10CCharacter24attemptStopOfActiveSkillEv");
TL_ORIGINAL(void, original6, (void*,float), "_ZN10CCharacter17performingSkillAIEf")
extern "C" void candidate6(void*,float) __asm__("_ZN10CCharacter17performingSkillAIEf");
TL_FUNCTION(dep_known, "_ZN13CSkillManager11knownSkillsE22ESKILL_ACTIVATION_TYPE")
TL_FUNCTION(dep_cost, "_ZN6CSkill11getManaCostEv")
TL_FUNCTION(dep_costOT, "_ZN6CSkill13getManaCostOTEv")
TL_FUNCTION(dep_cooling, "_ZN13CSkillManager17getSkillIsCoolingEP6CSkill")
TL_FUNCTION(dep_clear, "_ZN11CRandomizer5clearEv")
TL_FUNCTION(dep_choice, "_ZN11CRandomizer9addChoiceEii")
TL_FUNCTION(dep_random, "_ZN11CRandomizer9getRandomEv")
TL_FUNCTION(dep_active, "_ZN10CCharacter14setActiveSkillEP6CSkillb")
TL_FUNCTION(dep_castable, "_ZN10CCharacter19canCastCurrentSkillEP9CBaseUnitbb")
TL_FUNCTION(dep_stopAll, "_ZN13CSkillManager13stopAllSkillsEbbb")
TL_FUNCTION(dep_stopName, "_ZN13CSkillManager16stopSkillsByNameESbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(dep_canStop, "_ZN6CSkill10getCanStopEv")
TL_FUNCTION(dep_name, "_ZN6CSkill7getNameEv")
TL_FUNCTION(dep_loopEnd, "_ZN6CSkill24getAnimationIndexLoopEndEv")
TL_FUNCTION(dep_blend, "_ZN10CCharacter14blendAnimationEibfff")
TL_FUNCTION(dep_queue, "_ZN10CCharacter19queueBlendAnimationERKSsbff")
TL_FUNCTION(dep_modifyMana, "_ZN10CCharacter10modifyManaEf")
TL_FUNCTION(dep_trailActive, "_ZN12CWeaponTrail9setActiveEb")
TL_FUNCTION(dep_trailVisible, "_ZN12CWeaponTrail10setVisibleEb")
TL_FUNCTION(dep_targetType, "_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(dep_sight, "_ZN10CCharacter16validLineOfSightER6CLevelb")
TL_FUNCTION(dep_position, "_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(dep_range, "_ZN6CSkill12getIsInRangeERKN4Ogre7Vector3ES3_P9CBaseUnitS5_")

namespace {
using namespace smallmass;
void* self;void* manager;void* skills[3];void* target;unsigned manaCosts[3],overTime[3];
unsigned randomChoices[4],choiceCount;std::wstring skillName;
unsigned skillIndex(void* p) { for(unsigned i=0;i<3;++i)if(p==skills[i])return i;_exit(42); }
int known(void* p,int type) { event(1,p);number(type);return field<unsigned>(p,0x68); }
unsigned cost(void* p) { event(2,p);return manaCosts[skillIndex(p)]; }
unsigned costOT(void* p) { event(3,p);return overTime[skillIndex(p)]; }
bool cooling(void* p,void* skill) { event(4,p);pointer(skill);return ((input->index/4+skillIndex(skill))%5)==0; }
void clear(void* p) { event(5,p);choiceCount=0;field<unsigned>(p,0x30)=0; }
int choice(void* p,int value,int odds) { event(6,p);number(value);number(odds);randomChoices[choiceCount++]=value;field<unsigned>(p,0x30)=choiceCount;return choiceCount-1; }
int random(void* p) { event(7,p);return randomChoices[input->index%choiceCount]; }
void active(void* p,void* skill,bool flag) { event(8,p);pointer(skill);number(flag);field<void*>(p,0x398)=skill; }
bool castable(void* p,void* unit,bool a,bool b) { event(9,p);pointer(unit);number(a);number(b);return (input->index+skillIndex(field<void*>(p,0x398)))%3!=0; }
void stopAll(void* p,bool a,bool b,bool c) { event(10,p);number(a);number(b);number(c); }
void stopName(void* p,const std::wstring& name,bool flag) { event(11,p);text(name);number(flag); }
bool canStop(void* p) { event(12,p);return (input->index/8)%2; }
const std::wstring& name(void* p) { event(13,p);return skillName; }
int loopEnd(void* p) { event(14,p);return input->index%3==0?-1:17; }
void blend(void* p,int animation,bool loop,float fade,float speed,float end) { event(15,p);number(animation);number(loop);floating(fade);floating(speed);floating(end); }
void queue(void* p,const std::string& animation,bool loop,float fade,float speed) { event(16,p);text(animation);number(loop);floating(fade);floating(speed); }
void modifyMana(void* p,float amount) { event(17,p);floating(amount);field<float>(p,0x438)+=amount; }
void trailActive(void* p,bool v) { event(18,p);number(v); }
void trailVisible(void* p,bool v) { event(19,p);number(v); }
int targetType(void* p) { event(20,p);return input->index%5==0?1:2; }
bool sight(void* p,void* level,bool flag) { event(21,p);pointer(level);number(flag);return input->index%4!=0; }
Ogre::Vector3 position(void* p,bool absolute) { event(22,p);number(absolute);return p==self?Ogre::Vector3(1,2,3):Ogre::Vector3(-4,5,6); }
bool range(void* p,const Ogre::Vector3& from,const Ogre::Vector3& to,void* owner,void* other) { event(23,p);vector(from);vector(to);pointer(owner);pointer(other);return input->index%6!=0; }
void complete(void* p) { event(24,p); }
void state(void* p,int v) { event(25,p);number(v);field<int>(p,0x330)=v; }
void update(void* p,float elapsed,bool force) { event(26,p);floating(elapsed);number(force);if(input->index%7==0)field<void*>(p,0x398)=NULL; }
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;choiceCount=0;std::memset(randomChoices,0,sizeof(randomChoices));
 self=object(0x7f8);manager=object(0x98);target=object(0x778);void** table=static_cast<void**>(object(0x420));
 table[0x408/8]=reinterpret_cast<void*>(&complete);table[0x348/8]=reinterpret_cast<void*>(&state);table[0x358/8]=reinterpret_cast<void*>(&update);field<void*>(self,0)=table;
 void** allSkills=static_cast<void**>(object(3*8));
 const unsigned costs[]={0,1,5,20,0x80000000u,0xffffffffu};const int targets[]={0,2,3,9,10,4};
 for(unsigned i=0;i<3;++i) {
  skills[i]=object(0x160);allSkills[i]=skills[i];void* property=object(0x138);void** levels=static_cast<void**>(object(8));levels[0]=property;
  field<void*>(skills[i],0x90)=(c.index+i)%2?property:NULL;field<void*>(skills[i],0xa0)=levels;field<unsigned>(skills[i],0xa8)=1;
  field<int>(property,0x50)=(c.index/3+i)%4;field<int>(property,0x70)=targets[(c.index/5+i)%6];
  field<int>(skills[i],0x5c)=(c.index/7+i)%4;field<bool>(skills[i],0x6b)=(c.index/11+i)%5==0;field<bool>(skills[i],0x6d)=(c.index/13+i)%5!=0;
  field<int>(skills[i],0x120)=(c.index/17+i)%4;
  field<unsigned>(skills[i],0xec)=c.index&1?unsigned(-1):11;
  field<bool>(skills[i],0x64)=c.index&2;field<bool>(skills[i],0x6e)=c.index&4;
  manaCosts[i]=costs[(c.index/2+i)%6];overTime[i]=costs[(c.index/9+i)%6];
 }
 unsigned count=c.index%9==0?0:c.index%3==0?1:3;list(manager,0x60,allSkills,count,c.index%5==0?1:3);
 field<void*>(self,0x1c8)=c.index%19==0?NULL:manager;field<void*>(self,0x398)=c.index%17==0?NULL:skills[c.index%3];
 field<void*>(self,0x340)=c.index%3?target:NULL;field<void*>(self,0x350)=c.index%3==0&&c.index%2?target:NULL;
 field<void*>(self,0x68)=object(0x28);field<void*>(field<void*>(self,0x68),0x18)=object(8);
 field<int>(target,0x330)=c.index%3==0?5:c.index%3==1?6:2;
 const float mana[]={0,1,4.5f,20,-1,100};field<float>(self,0x438)=mana[(c.index/6)%6];field<float>(self,0x414)=c.index%5==0?0:12;
 field<bool>(self,0x267)=c.index&4;field<bool>(self,0x37d)=c.index&8;
 const float times[]={0,0.25f,1,-1,2};field<float>(self,0x380)=times[(c.index/4)%5];
 if(c.index%23==0)field<float>(self,0x380)=bits(0x7fc01234);
 field<void*>(self,0x698)=c.index&16?object(16):NULL;field<void*>(self,0x6a0)=c.index&32?object(16):NULL;
 skillName=L"MASS_SKILL";
 detour::Set patches;
 TL_REDIRECT(patches,dep_known,&known);
 TL_REDIRECT(patches,dep_cost,&cost);
 TL_REDIRECT(patches,dep_costOT,&costOT);
 TL_REDIRECT(patches,dep_cooling,&cooling);
 TL_REDIRECT(patches,dep_clear,&clear);
 TL_REDIRECT(patches,dep_choice,&choice);
 TL_REDIRECT(patches,dep_random,&random);
 TL_REDIRECT(patches,dep_active,&active);
 TL_REDIRECT(patches,dep_castable,&castable);
 TL_REDIRECT(patches,dep_stopAll,&stopAll);
 TL_REDIRECT(patches,dep_stopName,&stopName);
 TL_REDIRECT(patches,dep_canStop,&canStop);
 TL_REDIRECT(patches,dep_name,&name);
 TL_REDIRECT(patches,dep_loopEnd,&loopEnd);
 TL_REDIRECT(patches,dep_blend,&blend);
 TL_REDIRECT(patches,dep_queue,&queue);
 TL_REDIRECT(patches,dep_modifyMana,&modifyMana);
 TL_REDIRECT(patches,dep_trailActive,&trailActive);
 TL_REDIRECT(patches,dep_trailVisible,&trailVisible);
 TL_REDIRECT(patches,dep_targetType,&targetType);
 TL_REDIRECT(patches,dep_sight,&sight);
 TL_REDIRECT(patches,dep_position,&position);
 TL_REDIRECT(patches,dep_range,&range);

 if(patches.failed())_exit(41);
 const float elapsedValues[]={0,0.125f,0.5f,2,-0.25f};float elapsed=elapsedValues[(c.index/3)%5];
 switch(c.op) {
 case 0:autotest::invoke(out,ours?candidate0:original0,self);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,bool(c.index&1));break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self);break;
 case 4:autotest::invoke(out,ours?candidate4:original4,self,elapsed);break;
 case 5:autotest::invoke(out,ours?candidate5:original5,self);break;
 case 6:autotest::invoke(out,ours?candidate6:original6,self,elapsed);break;
 }
 out.add(autotest::g_arena,autotest::g_arenaUsed);number(choiceCount);out.add(randomChoices,sizeof(randomChoices));
}
}
TL_TEST(smallmass2_skill_offensive) { return smallmass::run(host,0,"smallmass2_skill_offensive",(uint64_t)(uintptr_t)original0,execute,256); }
TL_TEST(smallmass2_skill_defensive) { return smallmass::run(host,1,"smallmass2_skill_defensive",(uint64_t)(uintptr_t)original1,execute,256); }
TL_TEST(smallmass2_skill_select_offensive) { return smallmass::run(host,2,"smallmass2_skill_select_offensive",(uint64_t)(uintptr_t)original2,execute,256); }
TL_TEST(smallmass2_skill_select_defensive) { return smallmass::run(host,3,"smallmass2_skill_select_defensive",(uint64_t)(uintptr_t)original3,execute,256); }
TL_TEST(smallmass2_skill_update_active) { return smallmass::run(host,4,"smallmass2_skill_update_active",(uint64_t)(uintptr_t)original4,execute,256); }
TL_TEST(smallmass2_skill_stop_active) { return smallmass::run(host,5,"smallmass2_skill_stop_active",(uint64_t)(uintptr_t)original5,execute,256); }
TL_TEST(smallmass2_skill_perform_active) { return smallmass::run(host,6,"smallmass2_skill_perform_active",(uint64_t)(uintptr_t)original6,execute,256); }
