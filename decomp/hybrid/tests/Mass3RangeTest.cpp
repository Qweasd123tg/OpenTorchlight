#include "SmallMassCompare.h"
TL_ORIGINAL(bool, original0, (void*,int), "_ZN10CCharacter13inAttackRangeE18EATTACK_RANGE_TYPE")
extern "C" bool candidate0(void*,int) __asm__("_ZN10CCharacter13inAttackRangeE18EATTACK_RANGE_TYPE");
TL_ORIGINAL(int, original1, (void*,long long,bool), "_ZN10CCharacter12inSkillRangeExb")
extern "C" int candidate1(void*,long long,bool) __asm__("_ZN10CCharacter12inSkillRangeExb");
TL_ORIGINAL(bool, original2, (void*,void*,void*,void*), "_ZN10CCharacter13inStrikeRangeEPS_P5CItemP10CEquipment")
extern "C" bool candidate2(void*,void*,void*,void*) __asm__("_ZN10CCharacter13inStrikeRangeEPS_P5CItemP10CEquipment");
TL_ORIGINAL(bool, original3, (void*,void*,bool), "_ZN10CCharacter16validLineOfSightER6CLevelb")
extern "C" bool candidate3(void*,void*,bool) __asm__("_ZN10CCharacter16validLineOfSightER6CLevelb");
TL_FUNCTION(dep_left, "_ZN10CCharacter19getWeaponInLeftHandEv")
TL_FUNCTION(dep_right, "_ZN10CCharacter20getWeaponInRightHandEv")
TL_FUNCTION(dep_isa, "_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dep_effect, "_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(dep_range, "_ZN10CCharacter11attackRangeEv")
TL_FUNCTION(dep_select, "_ZN10CCharacter12selectAttackE18EATTACK_RANGE_TYPE")
TL_FUNCTION(dep_position, "_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(dep_known, "_ZN13CSkillManager11knownSkillsE22ESKILL_ACTIVATION_TYPE")
TL_FUNCTION(dep_skill, "_ZN13CSkillManager14getSkillByGuidEx")
TL_FUNCTION(dep_skillRange, "_ZN6CSkill8getRangeEv")
TL_FUNCTION(dep_minimum, "_ZN6CSkill11getRangeMinEv")
TL_FUNCTION(dep_targetType, "_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(dep_ai, "_ZN10CAIManager9hasAIFlagE13EAIFLAG_TYPES")
TL_FUNCTION(dep_sight, "_ZN6CLevel17sightUnobstructedERKN4Ogre7Vector3ES3_b")

namespace {
using namespace smallmass;
void *self,*target,*item,*weapon,*attack,*model,*manager,*active,*otherSkill;
void* left(void* p) {event(1,p);return input->index%5<2?weapon:0;}
void* right(void* p) {event(2,p);return input->index%7<3?weapon:0;}
bool isa(void* p,int type) {event(3,p);number(type);return input->index&8;}
float effect(void* p,int type,int damage) {event(4,p);number(type);number(damage);return float(int(input->index%9)-4);}
float range(void* p) {event(5,p);return float(input->index%11)*.75f;}
void select(void* p,int type) {event(6,p);number(type);if(input->index&4)field<void*>(p,0x390)=attack;}
Ogre::Vector3 position(void* p,bool absolute) {
 event(7,p);number(absolute);
 Ogre::Vector3 result=field<Ogre::Vector3>(p,0x84);
 if(input->op==3&&p==model&&input->index%13==0)field<void*>(self,0x340)=field<void*>(self,0x350)=0;
 return result;
}
unsigned known(void* p,int type) {event(8,p);number(type);return input->index%11?3:0;}
void* skill(void* p,long long guid) {event(9,p);output->add(&guid,8);return input->index%9?active:0;}
float skillRange(void* p) {event(10,p);return float(input->index%13)*.5f;}
float minimum(void* p) {event(11,p);return float(input->index%9)*.5f;}
int targetType(void* p) {event(12,p);const int values[]={0,1,2,3,4,9,10,11};return values[input->index%8];}
bool ai(void* p,int flag) {event(13,p);number(flag);return input->index%7==0;}
bool sight(void* p,const Ogre::Vector3& from,const Ogre::Vector3& to,bool flag) {event(14,p);vector(from);vector(to);number(flag);return input->index&2;}
void* getModel(void* p) {event(15,p);return model;}
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;
 self=object(0x778);target=object(0x778);item=object(0x380);weapon=object(0x480);attack=object(0x80);model=object(0x258);manager=object(0x100);active=object(0x160);otherSkill=object(0x160);
 void** table=static_cast<void**>(object(0x430));table[0x1e0/8]=reinterpret_cast<void*>(&getModel);field<void*>(self,0)=table;
 field<void*>(self,0x340)=(c.index%4==1||c.index%4==3)?target:0;
 field<void*>(self,0x350)=(c.index%4>=2)?item:0;
 field<void*>(self,0x390)=c.index%5?attack:0;
 field<void*>(self,0x498)=c.index&16?weapon:0;
 field<void*>(self,0x1c8)=c.index%7?manager:0;
 field<void*>(self,0x398)=c.index%3==0?0:c.index%3==1?otherSkill:active;
 field<long long>(active,0x150)=0x123456789012LL;
 field<void*>(self,0x718)=c.index%3?manager:0;
 field<float>(self,0x194)=float(int(c.index%5)-2)*.25f;
 field<float>(target,0x194)=float(int(c.index%7)-3)*.5f;
 field<float>(item,0x194)=float(int(c.index%9)-4)*.125f;
 field<float>(self,0x4e0)=float(c.index%7)*.3f;
 field<float>(self,0x98)=float(c.index%4)*.5f;
 field<float>(self,0x4dc)=float(c.index%5)*.5f;
 field<float>(attack,0x6c)=float(c.index%7)*.2f;
 const float heights[]={0,2.5f,2.50001f,-2.5f,-2.50001f,8,-8,1};
 field<Ogre::Vector3>(self,0x84)=Ogre::Vector3(float(int(c.index%7)-3),.5f,float(int(c.index%11)-5));
 field<Ogre::Vector3>(target,0x84)=field<Ogre::Vector3>(self,0x84)+Ogre::Vector3(float(c.index%9)*.5f,heights[(c.index/4)%8],float(c.index%5)*.75f);
 field<Ogre::Vector3>(item,0x84)=field<Ogre::Vector3>(target,0x84)+Ogre::Vector3(.25f,0,-.25f);
 field<Ogre::Vector3>(model,0x84)=Ogre::Vector3(.25f,.75f,-.5f);
 field<Ogre::Vector3>(self,0xbc)=Ogre::Vector3(.3f,.2f,.9f);
 if(c.index>=256&&c.index%5==0)field<float>(self,0x194)=bits(0x7fc00000);
 if(c.index>=256&&c.index%5==1)field<float>(target,0x194)=bits(0x7fc00000);
 if(c.index>=256&&c.index%5==2)field<float>(item,0x194)=bits(0x7fc00000);
 detour::Set patches;
 TL_REDIRECT(patches,dep_left,&left);
 TL_REDIRECT(patches,dep_right,&right);
 TL_REDIRECT(patches,dep_isa,&isa);
 TL_REDIRECT(patches,dep_effect,&effect);
 TL_REDIRECT(patches,dep_range,&range);
 TL_REDIRECT(patches,dep_select,&select);
 TL_REDIRECT(patches,dep_position,&position);
 TL_REDIRECT(patches,dep_known,&known);
 TL_REDIRECT(patches,dep_skill,&skill);
 TL_REDIRECT(patches,dep_skillRange,&skillRange);
 TL_REDIRECT(patches,dep_minimum,&minimum);
 TL_REDIRECT(patches,dep_targetType,&targetType);
 TL_REDIRECT(patches,dep_ai,&ai);
 TL_REDIRECT(patches,dep_sight,&sight);

 if(patches.failed())_exit(41);
 switch(c.op) {
 case 0:autotest::invoke(out,ours?candidate0:original0,self,int(c.index%5));break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,c.index&16?-1LL:0xabcdef12345LL,bool(c.index&32));break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,field<void*>(self,0x340),field<void*>(self,0x350),c.index&32?weapon:0);break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self,manager,bool(c.index&1));break;
 }
 pointer(field<void*>(self,0x398));pointer(field<void*>(self,0x390));
}
}
TL_TEST(mass3_826140) { return smallmass::run(host,0,"mass3_826140",(uint64_t)(uintptr_t)original0,execute,384); }
TL_TEST(mass3_826470) { return smallmass::run(host,1,"mass3_826470",(uint64_t)(uintptr_t)original1,execute,384); }
TL_TEST(mass3_824a50) { return smallmass::run(host,2,"mass3_824a50",(uint64_t)(uintptr_t)original2,execute,384); }
TL_TEST(mass3_824e60) { return smallmass::run(host,3,"mass3_824e60",(uint64_t)(uintptr_t)original3,execute,256); }
