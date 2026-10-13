#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,void*), "_ZN10CCharacter6addPetEPS_")
extern "C" void candidate0(void*,void*) __asm__("_ZN10CCharacter6addPetEPS_");
TL_ORIGINAL(void, original1, (void*,void*,void*,int,bool), "_ZN10CCharacter15awardExperienceER6CLevelPS_ib")
extern "C" void candidate1(void*,void*,void*,int,bool) __asm__("_ZN10CCharacter15awardExperienceER6CLevelPS_ib");
TL_ORIGINAL(void*, original2, (void*,void*,float), "_ZN10CCharacter8updateHPER6CLevelf")
extern "C" void* candidate2(void*,void*,float) __asm__("_ZN10CCharacter8updateHPER6CLevelf");
#include <vector>
TL_FUNCTION(dep_maximum, "_ZN10CCharacter22getMaximumPetInstancesEv")
TL_FUNCTION(dep_setMaster, "_ZN10CCharacter9setMasterEPS_")
TL_FUNCTION(dep_effect, "_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(dep_hp, "_ZN10CCharacter2HPEv")
TL_FUNCTION(dep_isPlayer, "_ZN9CBaseUnit8isPlayerEv")
TL_FUNCTION(dep_journal, "_ZN10CCharacter25incrementJournalStatisticE17EJournalStatistici")
TL_FUNCTION(dep_steam, "_ZN11CSteamStats12getSingletonEv")
TL_FUNCTION(dep_stat, "_ZN11CSteamStats13incrementStatE6ESTATSi")
TL_FUNCTION(dep_master, "_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(dep_gate, "_ZN22CMasterResourceManager14experienceGateEi")
TL_FUNCTION(dep_maxLevel, "_ZN22CMasterResourceManager11getMaxLevelEv")
TL_FUNCTION(dep_isa, "_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dep_globals, "_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(dep_maxHP, "_ZN10CCharacter5maxHPEv")
TL_FUNCTION(dep_damage, "_ZN10CCharacter23getEffectValuesOfDamageEv")
TL_FUNCTION(dep_modify, "_ZN10CCharacter8modifyHPEf")
TL_FUNCTION(dep_value, "_ZN7CEffect5valueE14EEFFECT_VALUES")
TL_FUNCTION(dep_fame, "_ZN10CCharacter9awardFameER6CLevelPS_ib")
TL_FUNCTION(dep_owner, "_ZN7CEffect8setOwnerEP9CBaseUnitb")
TL_FUNCTION(dep_broadcast, "_ZN9CBaseUnit18broadcastUnitStateE12EUNIT_STATES")

TL_FUNCTION(dep_experience, "_ZN10CCharacter15awardExperienceER6CLevelPS_ib")
namespace {
using namespace smallmass;
void *self,*source,*settings,*services,*pet,*parent;void* followers[4];
int maximum(void* p){event(1,p);return int(input->index%7)-2;}
void setMaster(void* p,void* owner){event(2,p);pointer(owner);field<void*>(p,0x640)=owner;}
float effect(void* p,int type,int damage){event(3,p);number(type);number(damage);const float v[]={-125,-100,-25,0,12.5f,25,100};return v[input->index%7];}
int hp(void* p){event(4,p);return int(field<float>(p,0x414));}
bool isPlayer(void* p){event(5,p);return p==self&&(input->index&1);}
void journal(void* p,int type,int amount){event(6,p);number(type);number(amount);}
void* steam(){number(7);return services;}
void stat(void* p,int type,int amount){event(8,p);number(type);number(amount);}
void* master(){number(9);return services;}
int gate(void* p,int level){event(10,p);number(level);return 100+level*10;}
int maxLevel(void* p){event(11,p);return 5;}
bool isa(void* p,int type){event(12,p);number(type);return p==self;}
void* globals(){number(13);return settings;}
int maxHP(void* p){event(14,p);return 150;}
float damage(void* p){event(15,p);return float(int(input->index%9)-5)*3.5f;}
void modify(void* p,float change){event(16,p);floating(change);field<float>(p,0x414)+=change;}
float value(void* p,int index){event(17,p);number(index);return field<float>(p,0xc0);}
void experience(void* p,void* level,void* killed,int amount,bool flag){event(18,p);pointer(level);pointer(killed);number(amount);number(flag);}
void fame(void* p,void* level,void* killed,int amount,bool flag){event(19,p);pointer(level);pointer(killed);number(amount);number(flag);}
void owner(void* p,void* target,bool recalc){event(20,p);pointer(target);number(recalc);field<void*>(p,0x48)=target;}
void broadcast(void* p,int state){event(21,p);number(state);}
void die(void* p,void* killer,const Ogre::Vector3* force,float damage,bool flag){event(22,p);pointer(killer);pointer(force);floating(damage);number(flag);field<int>(p,0x330)=5;}
void levelUp(void* p){event(23,p);++field<unsigned>(p,0x100);}
void initCharacter(void* p,unsigned variant,void** table){
 field<void*>(p,0)=table;
 new(static_cast<char*>(p)+0x40)std::wstring(variant%3==0?L"Troll":variant%3==1?L"Troll Juggernaut":L"Goblin");
 new(static_cast<char*>(p)+0x648)std::vector<void*>;
 new(static_cast<char*>(p)+0x538)std::vector<bool>;
 field<unsigned>(p,0x100)=variant%7;
 const unsigned experience[]={0,1,99,100,101,150,0x7fffffffu,0x7ffffff0u};field<unsigned>(p,0x448)=experience[variant%8];
 field<float>(p,0x414)=float(int(variant%9)-4);
 const int states[]={0,2,5,6,7};field<int>(p,0x330)=states[variant%5];
 field<bool>(p,0x701)=variant%17==0;field<bool>(p,0x702)=variant&2;
}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;self=object(0x778);source=object(0x778);pet=object(0x778);parent=object(0x778);settings=object(0x110);services=object(0x100);
 void* level=object(0x2f0);void* effectManager=object(0x130);
 void** table=static_cast<void**>(object(0x430));table[0x330/8]=reinterpret_cast<void*>(&die);table[0x320/8]=reinterpret_cast<void*>(&levelUp);
 initCharacter(self,c.index,table);initCharacter(source,c.index/2,table);initCharacter(pet,c.index/3,table);initCharacter(parent,c.index/4,table);
 std::vector<void*>& pets=field<std::vector<void*> >(self,0x648);std::vector<bool>& flags=field<std::vector<bool> >(self,0x538);pets.reserve(8);flags.reserve(16);
 for(unsigned i=0;i<4;++i){followers[i]=object(0x778);initCharacter(followers[i],c.index+i,table);field<bool>(followers[i],0x52e)=(c.index+i)%4==0;if(i<c.index%5){pets.push_back(followers[i]);flags.push_back(i&1);}}
 field<bool>(pet,0x19b)=c.index&2;
 field<void*>(self,0x640)=c.index&8?parent:0;
 field<bool>(self,0x52e)=c.index&4;
 field<void*>(self,0x1b8)=c.index%11?effectManager:0;
 field<float>(settings,0x58)=float(int(c.index%5)-2);field<float>(settings,0x5c)=float(int(c.index%7)-3);
 field<int>(self,0x454)=123;field<int>(self,0x458)=45;field<float>(self,0x1ec)=7;
 const int types[]={1,7,0x34,0x7c,2,0x34};
 for(unsigned group=0;group<2;++group){
  void** effects=static_cast<void**>(object(6*8));
  for(unsigned i=0;i<6;++i){effects[i]=object(0x138);field<int>(effects[i],0x1c)=types[(c.index+i+group)%6];field<float>(effects[i],0xc0)=float(int((c.index+i)%5)-2);field<void*>(effects[i],0x58)=(c.index+i)%3==0?0:i&1?source:pet;field<void*>(effects[i],0x48)=self;}
  list(effectManager,0x28+group*0x18,effects,(c.index+group)%7,6);
 }
 detour::Set patches;
 TL_REDIRECT(patches,dep_maximum,&maximum);
 TL_REDIRECT(patches,dep_setMaster,&setMaster);
 TL_REDIRECT(patches,dep_effect,&effect);
 TL_REDIRECT(patches,dep_hp,&hp);
 TL_REDIRECT(patches,dep_isPlayer,&isPlayer);
 TL_REDIRECT(patches,dep_journal,&journal);
 TL_REDIRECT(patches,dep_steam,&steam);
 TL_REDIRECT(patches,dep_stat,&stat);
 TL_REDIRECT(patches,dep_master,&master);
 TL_REDIRECT(patches,dep_gate,&gate);
 TL_REDIRECT(patches,dep_maxLevel,&maxLevel);
 TL_REDIRECT(patches,dep_isa,&isa);
 TL_REDIRECT(patches,dep_globals,&globals);
 TL_REDIRECT(patches,dep_maxHP,&maxHP);
 TL_REDIRECT(patches,dep_damage,&damage);
 TL_REDIRECT(patches,dep_modify,&modify);
 TL_REDIRECT(patches,dep_value,&value);
 TL_REDIRECT(patches,dep_fame,&fame);
 TL_REDIRECT(patches,dep_owner,&owner);
 TL_REDIRECT(patches,dep_broadcast,&broadcast);

 if(c.op!=1){TL_REDIRECT(patches,dep_experience,&experience);}
 if(patches.failed())_exit(41);
 const int amounts[]={-1000,-1,0,1,9,100,1000000,0x7fffffff};
 const float elapsed[]={0,.125f,.5f,1,3};
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,self,c.index%9==0?0:c.index%9==1&&pets.size()?pets[0]:pet);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,level,c.index%7?source:0,amounts[(c.index/3)%8],bool(c.index&16));break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,level,elapsed[(c.index/4)%5]);break;
 }
 number(pets.size());for(unsigned i=0;i<pets.size();++i)pointer(pets[i]);number(flags.size());for(unsigned i=0;i<flags.size();++i)number(flags[i]);pointer(field<void*>(pet,0x640));
 void* all[]={self,source,pet,parent,followers[0],followers[1],followers[2],followers[3]};
 for(unsigned i=0;i<8;++i){number(field<unsigned>(all[i],0x100));number(field<unsigned>(all[i],0x448));number(field<int>(all[i],0x330));floating(field<float>(all[i],0x414));}
 number(field<int>(self,0x454));number(field<int>(self,0x458));floating(field<float>(self,0x1ec));
}
}
TL_TEST(mass3_831f90) { return smallmass::run(host,0,"mass3_831f90",(uint64_t)(uintptr_t)original0,execute,192); }
TL_TEST(mass3_822850) { return smallmass::run(host,1,"mass3_822850",(uint64_t)(uintptr_t)original1,execute,384); }
TL_TEST(mass3_83d930) { return smallmass::run(host,2,"mass3_83d930",(uint64_t)(uintptr_t)original2,execute,256); }
