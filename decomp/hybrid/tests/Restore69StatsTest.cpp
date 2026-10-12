#include "SmallMassCompare.h"
TL_ORIGINAL(bool, original0, (void*), "_ZN10CCharacter15performingSkillEv")
extern "C" bool candidate0(void*) __asm__("_ZN10CCharacter15performingSkillEv");
TL_ORIGINAL(unsigned, original1, (void*,bool), "_ZN10CCharacter31getArmorAndTrinketLevelCanEquipEb")
extern "C" unsigned candidate1(void*,bool) __asm__("_ZN10CCharacter31getArmorAndTrinketLevelCanEquipEb");
TL_ORIGINAL(unsigned, original2, (void*,bool), "_ZN10CCharacter22getWeaponLevelCanEquipEb")
extern "C" unsigned candidate2(void*,bool) __asm__("_ZN10CCharacter22getWeaponLevelCanEquipEb");
TL_ORIGINAL(int, original3, (void*), "_ZN10CCharacter9alignmentEv")
extern "C" int candidate3(void*) __asm__("_ZN10CCharacter9alignmentEv");
TL_ORIGINAL(bool, original4, (void*,void*), "_ZN10CCharacter7isEnemyEPS_")
extern "C" bool candidate4(void*,void*) __asm__("_ZN10CCharacter7isEnemyEPS_");
TL_ORIGINAL(bool, original5, (void*,void*), "_ZN10CCharacter8isFriendEPS_")
extern "C" bool candidate5(void*,void*) __asm__("_ZN10CCharacter8isFriendEPS_");
TL_ORIGINAL(float, original6, (void*), "_ZN10CCharacter9viewAngleEv")
extern "C" float candidate6(void*) __asm__("_ZN10CCharacter9viewAngleEv");
TL_ORIGINAL(bool, original7, (void*), "_ZN10CCharacter14isPetNearDeathEv")
extern "C" bool candidate7(void*) __asm__("_ZN10CCharacter14isPetNearDeathEv");
TL_ORIGINAL(float, original8, (void*), "_ZN10CCharacter12walkingSpeedEv")
extern "C" float candidate8(void*) __asm__("_ZN10CCharacter12walkingSpeedEv");
TL_ORIGINAL(float, original9, (void*), "_ZN10CCharacter12runningSpeedEv")
extern "C" float candidate9(void*) __asm__("_ZN10CCharacter12runningSpeedEv");
TL_ORIGINAL(void, original10, (void*,float), "_ZN10CCharacter10updateManaEf")
extern "C" void candidate10(void*,float) __asm__("_ZN10CCharacter10updateManaEf");
TL_ORIGINAL(bool, original11, (void*), "_ZN10CCharacter7blockedEv")
extern "C" bool candidate11(void*) __asm__("_ZN10CCharacter7blockedEv");
TL_ORIGINAL(float, original12, (void*), "_ZN10CCharacter26getDmgToReflectFromMissileEv")
extern "C" float candidate12(void*) __asm__("_ZN10CCharacter26getDmgToReflectFromMissileEv");
TL_ORIGINAL(float, original13, (void*), "_ZN10CCharacter11attackRangeEv")
extern "C" float candidate13(void*) __asm__("_ZN10CCharacter11attackRangeEv");
TL_FUNCTION(dep_effect, "_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(dep_hasEffect, "_ZN9CBaseUnit9hasEffectE12EEFFECT_TYPE")
TL_FUNCTION(dep_flag, "_ZN10CAIManager9hasAIFlagE13EAIFLAG_TYPES")
TL_FUNCTION(dep_isa, "_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dep_globals, "_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(dep_mana, "_ZN10CCharacter10modifyManaEf")
TL_FUNCTION(dep_blockChance, "_ZN10CCharacter14getBlockChanceEv")
TL_FUNCTION(dep_randomInt, "_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(dep_randomFloat, "_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(dep_equipped, "_ZN10CInventory22getEquipmentEquippedAtE16EEQUIP_LOCATIONS")
TL_FUNCTION(dep_getEffect, "_ZN14CEffectManager9getEffectE12EEFFECT_TYPE")
TL_FUNCTION(dep_selectAttack, "_ZN10CCharacter12selectAttackE18EATTACK_RANGE_TYPE")
namespace {
using namespace smallmass;
void* self;void* other;void* settings;void* inventory;void* equipments[12];void* effects[13];
unsigned effectCalls,randomCalls;
float value(unsigned n) {
 const float v[]={0,1,-1,0.5f,-0.5f,15,25,-25,99.999f,100,100.001f,-100,-200,250,360,0.125f};
 return v[n%16];
}
float effect(void* p,int type,int damage) {
 event(1,p);number(type);number(damage);++effectCalls;
 if(type==0x15) return input->index%23==0?bits(0x7fc01234):value(input->index);
 if(type==0x8c) return input->index%17==0?bits(0x7fc01234):value(input->index/3);
 if(type==0x3c) return value(input->index/2+(effectCalls-1)*3);
 return value(input->index/3+type);
}
bool hasEffect(void* p,int type) { event(2,p);number(type);return ((input->index/(p==self?3:7))&1)!=0; }
bool flag(void* p,int type) { event(3,p);number(type);return input->index&4; }
bool isa(void* p,int type) { event(4,p);number(type);if(p==self)field<unsigned>(self,0x100)+=3;return (input->index/(p==equipments[1]?2:5)+type)%3!=0; }
void* globals() { number(5);return settings; }
void mana(void* p,float amount) { event(6,p);floating(amount);field<float>(p,0x438)+=amount; }
int blockChance(void* p) { event(7,p);const int v[]={-10,0,1,50,99,100,101,250};return v[(input->index/8)%8]; }
int randomInt(int lo,int hi) { number(8);number(lo);number(hi);const int v[]={0,1,49,50,51,99,100,20};return v[input->index%8]; }
float randomFloat(float lo,float hi) { number(9);floating(lo);floating(hi);++randomCalls;return lo+(hi-lo)*(float((input->index+randomCalls)%5)/4.0f); }
void* equipped(void* p,int slot) { event(10,p);number(slot);return (input->index/3+slot)%5==0?NULL:equipments[slot]; }
void* getEffect(void* p,int type) { event(11,p);number(type);unsigned i=field<unsigned>(p,0x10);return (input->index/7+i)%4==0?NULL:effects[i]; }
void selectAttack(void* p,int type) { event(12,p);number(type); }
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;effectCalls=randomCalls=0;
 self=object(0x778);other=object(0x778);settings=object(0x100);inventory=object(0x200);void* skill=object(0x160);
 field<void*>(self,0x398)=c.index%7==0?NULL:skill;
 field<int>(skill,0xec)=c.index&1?-1:7;field<bool>(skill,0x64)=c.index&2;
 field<bool>(self,0x267)=c.index&4;field<float>(self,0x380)=c.index%11==0?bits(0x7fc01234):value(c.index/8);
 field<unsigned>(self,0x100)=c.index%17==0?0xffffffffu:c.index*5;
 field<int>(self,0x338)=(c.index/2)%5;field<int>(other,0x338)=(c.index/11)%5;
 field<void*>(self,0x718)=c.index%5==0?NULL:object(32);
 field<float>(self,0x368)=value(c.index/7);
 field<void*>(self,0x640)=c.index%3==0?NULL:other;field<bool>(self,0x52e)=c.index&1;
 const float hp[]={-1,0,1,1.5f,2,3,14,15,16,30,100};field<float>(self,0x414)=hp[(c.index/3)%11];
 const int states[]={0,5,6,10,41,42};field<int>(self,0x330)=states[(c.index/5)%6];
 field<int>(self,0x418)=100;field<int>(self,0x41c)=int(c.index%9)-4;
 field<float>(self,0x28c)=value(c.index/16);field<float>(self,0x290)=value(c.index/16);
 field<int>(self,0x43c)=int(c.index%17)-2;field<float>(self,0x440)=value(c.index/11);
 field<float>(settings,0x60)=value(c.index/13);field<float>(self,0x438)=value(c.index/7);
 for(unsigned i=0;i<13;++i) {
  void* manager=object(0x40);field<unsigned>(manager,0x10)=i;effects[i]=object(0x138);
  field<float>(effects[i],0xcc)=value(c.index/5+i);field<float>(effects[i],0xd0)=value(c.index/9+i);
  if(i==0)field<void*>(self,0x1b8)=c.index%7==0?NULL:manager;
  else {equipments[i-1]=object(0x480);field<void*>(equipments[i-1],0x1b8)=(c.index+i)%6?manager:NULL;}
 }
 field<void*>(self,0x490)=c.index%13==0?NULL:inventory;
 for(unsigned i=0;i<2;++i) {
  void* attack=object(0x80);field<float>(attack,0x68)=value(c.index/5+i);
  field<void*>(equipments[i],i==0?0x2a0:0x2a8)=attack;
 }
 void* attack=object(0x80);field<float>(attack,0x68)=value(c.index/7);
 field<void*>(self,0x390)=c.index%7==0?NULL:attack;
 field<void*>(self,0x498)=c.index%4==0?NULL:equipments[0];
 field<float>(self,0x4e0)=value(c.index/11);field<float>(self,0x90)=9;field<float>(self,0x94)=13;field<float>(self,0x98)=value(c.index/3);
 if(c.op==13)field<void*>(self,0x490)=inventory;
 detour::Set patches;
 TL_REDIRECT(patches,dep_effect,&effect);
 TL_REDIRECT(patches,dep_hasEffect,&hasEffect);
 TL_REDIRECT(patches,dep_flag,&flag);
 TL_REDIRECT(patches,dep_isa,&isa);
 TL_REDIRECT(patches,dep_globals,&globals);
 TL_REDIRECT(patches,dep_mana,&mana);
 TL_REDIRECT(patches,dep_blockChance,&blockChance);
 TL_REDIRECT(patches,dep_randomInt,&randomInt);
 TL_REDIRECT(patches,dep_randomFloat,&randomFloat);
 TL_REDIRECT(patches,dep_equipped,&equipped);
 TL_REDIRECT(patches,dep_getEffect,&getEffect);
 TL_REDIRECT(patches,dep_selectAttack,&selectAttack);
 if(patches.failed())_exit(41);
 switch(c.op) {
 case 0:autotest::invoke(out,ours?candidate0:original0,self);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,bool(c.index&1));break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,bool(c.index&1));break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self);break;
 case 4:autotest::invoke(out,ours?candidate4:original4,self,(c.index%13==0?NULL:other));break;
 case 5:autotest::invoke(out,ours?candidate5:original5,self,other);break;
 case 6:autotest::invoke(out,ours?candidate6:original6,self);break;
 case 7:autotest::invoke(out,ours?candidate7:original7,self);break;
 case 8:autotest::invoke(out,ours?candidate8:original8,self);break;
 case 9:autotest::invoke(out,ours?candidate9:original9,self);break;
 case 10:autotest::invoke(out,ours?candidate10:original10,self,value(c.index/4));break;
 case 11:autotest::invoke(out,ours?candidate11:original11,self);break;
 case 12:autotest::invoke(out,ours?candidate12:original12,self);break;
 case 13:autotest::invoke(out,ours?candidate13:original13,self);break;
 }
 number(effectCalls);number(randomCalls);out.add(autotest::g_arena,autotest::g_arenaUsed);
}
}
TL_TEST(restore69_80e930) { return smallmass::run(host,0,"restore69_80e930",(uint64_t)(uintptr_t)original0,execute,256); }
TL_TEST(restore69_80eef0) { return smallmass::run(host,1,"restore69_80eef0",(uint64_t)(uintptr_t)original1,execute,256); }
TL_TEST(restore69_80ef50) { return smallmass::run(host,2,"restore69_80ef50",(uint64_t)(uintptr_t)original2,execute,256); }
TL_TEST(restore69_810170) { return smallmass::run(host,3,"restore69_810170",(uint64_t)(uintptr_t)original3,execute,256); }
TL_TEST(restore69_810200) { return smallmass::run(host,4,"restore69_810200",(uint64_t)(uintptr_t)original4,execute,256); }
TL_TEST(restore69_8102d0) { return smallmass::run(host,5,"restore69_8102d0",(uint64_t)(uintptr_t)original5,execute,256); }
TL_TEST(restore69_8138a0) { return smallmass::run(host,6,"restore69_8138a0",(uint64_t)(uintptr_t)original6,execute,256); }
TL_TEST(restore69_814440) { return smallmass::run(host,7,"restore69_814440",(uint64_t)(uintptr_t)original7,execute,256); }
TL_TEST(restore69_815a20) { return smallmass::run(host,8,"restore69_815a20",(uint64_t)(uintptr_t)original8,execute,256); }
TL_TEST(restore69_815ad0) { return smallmass::run(host,9,"restore69_815ad0",(uint64_t)(uintptr_t)original9,execute,256); }
TL_TEST(restore69_815c90) { return smallmass::run(host,10,"restore69_815c90",(uint64_t)(uintptr_t)original10,execute,256); }
TL_TEST(restore69_816330) { return smallmass::run(host,11,"restore69_816330",(uint64_t)(uintptr_t)original11,execute,256); }
TL_TEST(restore69_8163a0) { return smallmass::run(host,12,"restore69_8163a0",(uint64_t)(uintptr_t)original12,execute,256); }
TL_TEST(restore69_812580) { return smallmass::run(host,13,"restore69_812580",(uint64_t)(uintptr_t)original13,execute,256); }
