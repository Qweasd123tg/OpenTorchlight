#include "SmallMassCompare.h"
#include <map>
#include <new>
#include "TArrayList.h"
TL_ORIGINAL(bool, oldCooling, (void*,int), "_ZN13CSkillManager35getAnySkillsCoolingByActivationTypeE22ESKILL_ACTIVATION_TYPE")
extern "C" bool nextCooling(void*,int) __asm__("_ZN13CSkillManager35getAnySkillsCoolingByActivationTypeE22ESKILL_ACTIVATION_TYPE");
TL_ORIGINAL(void*, oldFindLevel, (void*,const std::wstring&,int), "_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEEi")
extern "C" void* nextFindLevel(void*,const std::wstring&,int) __asm__("_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEEi");
TL_ORIGINAL(void*, oldFindName, (void*,const std::wstring&), "_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void* nextFindName(void*,const std::wstring&) __asm__("_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void, oldReset, (void*), "_ZN13CSkillManager16resetSkillLevelsEv")
extern "C" void nextReset(void*) __asm__("_ZN13CSkillManager16resetSkillLevelsEv");
TL_ORIGINAL(float, oldCooldownProperty, (void*), "_ZN14CSkillProperty11getCoolDownEv")
extern "C" float nextCooldownProperty(void*) __asm__("_ZN14CSkillProperty11getCoolDownEv");
TL_ORIGINAL(void, oldStart, (void*), "_ZN16CSkillController10startSkillEv")
extern "C" void nextStart(void*) __asm__("_ZN16CSkillController10startSkillEv");
TL_ORIGINAL(void, oldStop, (void*), "_ZN16CSkillController9stopSkillEv")
extern "C" void nextStop(void*) __asm__("_ZN16CSkillController9stopSkillEv");
TL_ORIGINAL(bool, oldRemove, (void*,unsigned), "_ZN11CLogicGroup24RemoveLogicObjectByIndexEj")
extern "C" bool nextRemove(void*,unsigned) __asm__("_ZN11CLogicGroup24RemoveLogicObjectByIndexEj");
TL_FUNCTION(skillName,"_ZN6CSkill7getNameEv")
TL_FUNCTION(setLevel,"_ZN13CSkillManager13setSkillLevelEP6CSkillj")
TL_FUNCTION(unitISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(configure,"_ZN16CSkillController13configureUnitEv")
TL_FUNCTION(removeLinks,"_ZN12CLogicObject24RemoveLinksToLogicObjectEPS_")
namespace {
using namespace smallmass;
void* manager;void* skills[6];void* owner;void* controller;void* logic[4];void* group;
std::wstring names[6];unsigned calls;unsigned mutation;bool answer;
void invalid(){output->issue=autotest::Capture::InvalidReport;}
unsigned indexOf(void* p,void** values,unsigned count){for(unsigned i=0;i<count;++i)if(p==values[i])return i;invalid();return ~0u;}
const std::wstring& nameSpy(void* p){unsigned i=indexOf(p,skills,6);event(1,p);++calls;if(mutation==1)field<unsigned>(manager,0x68)=1;return names[i<6?i:0];}
void levelSpy(void* p,void* skill,unsigned level){event(2,p);pointer(skill);number(level);++calls;if(p!=manager||indexOf(skill,skills,6)==~0u||level!=0)invalid();field<unsigned>(skill,0xdc)=0;if(mutation==1)field<unsigned>(manager,0x68)=1;}
bool isaSpy(void* p,int type){event(3,p);number(type);++calls;if(p!=owner||type!=27)invalid();field<unsigned>(p,0x194)^=0x55;return answer;}
bool configureSpy(void* p){event(4,p);++calls;if(p!=controller)invalid();field<unsigned>(p,0x150)^=0x10;return answer;}
bool linksSpy(void* p,void* target){event(5,p);pointer(target);++calls;if(indexOf(p,logic,4)==~0u||indexOf(target,logic,4)==~0u)invalid();field<unsigned>(p,0x70)^=0x1234;if(mutation==1)field<unsigned>(group,0x68)=1;return answer;}
void deleteSpy(void* p){event(6,p);number(indexOf(p,logic,4));++calls;field<unsigned>(p,0x74)=0xdead;if(mutation==2)field<unsigned>(group,0x68)=0;}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;calls=0;mutation=(c.index/8)%3;answer=c.index&1;
 if(c.op<=3){
  manager=object(0x98);void** ordinary=static_cast<void**>(object(6*8));void** updating=static_cast<void**>(object(6*8));
  const unsigned values[]={0,0x80000000u,0x3f800000,0xbf800000,0x7f800000,0x7fc00000};
  for(unsigned i=0;i<6;++i){skills[i]=object(0x160);ordinary[i]=skills[i];names[i]=i%3==0?L"Fire":i%3==1?L"ICE":L"fire";field<int>(skills[i],0x60)=(i+c.index)%4;field<unsigned>(skills[i],0xfc)=values[(i+c.index/4)%6];field<unsigned>(skills[i],0xdc)=(i+c.index)%3;field<bool>(skills[i],0x6b)=(i+c.index)%3==0;field<bool>(skills[i],0x6d)=(i+c.index)%4!=0;field<int>(skills[i],0x5c)=(i+c.index)%3;}
  // Finish the reversed list only after all object identities exist.
  for(unsigned i=0;i<6;++i)updating[i]=skills[5-i];
  unsigned count=c.index%7,other=(c.index/7)%7,capacity=c.index&16?2:6;
  list(manager,0x60,ordinary,count,capacity);list(manager,0x48,updating,other,capacity);
  detour::Set patches;TL_REDIRECT(patches,skillName,&nameSpy);TL_REDIRECT(patches,setLevel,&levelSpy);if(patches.failed()){invalid();return;}
  if(c.op==0){typedef bool(*Fn)(void*,int);Fn fn=ours?nextCooling:oldCooling;autotest::invoke(out,fn,manager,int(c.index%5));}
  if(c.op==1){const wchar_t* labels[]={L"fire",L"IcE",L"missing",L"",L"FIRE"};std::wstring name=labels[(c.index/3)%5];typedef void*(*Fn)(void*,const std::wstring&,int);Fn fn=ours?nextFindLevel:oldFindLevel;if(!autotest::beginInvocation(out,fn))return;void* result=fn(manager,name,c.index%4);out.callCompleted=1;if(result&&indexOf(result,skills,6)==~0u)invalid();pointer(result);text(name);}
  if(c.op==2){typedef std::map<std::wstring,TArrayList<void*>*> Map;Map* map=new(static_cast<char*>(manager)+0x18)Map;TArrayList<void*>* listA=new(object(sizeof(TArrayList<void*>)))TArrayList<void*>(4);TArrayList<void*>* listB=new(object(sizeof(TArrayList<void*>)))TArrayList<void*>(4);if(c.index&1)listA->add(skills[0]);if(c.index&2)listB->add(skills[1]);(*map)[L"FIRE"]=listA;(*map)[L"ICE"]=listB;const wchar_t* labels[]={L"Fire",L"iCe",L"unknown",L"",L"FIRE"};std::wstring name=labels[c.index%5];typedef void*(*Fn)(void*,const std::wstring&);Fn fn=ours?nextFindName:oldFindName;if(!autotest::beginInvocation(out,fn))return;void* result=fn(manager,name);out.callCompleted=1;if(result&&indexOf(result,skills,6)==~0u)invalid();pointer(result);text(name);number(map->size());for(Map::iterator i=map->begin();i!=map->end();++i){text(i->first);number(i->second->size());if(i->second!=(i->first==L"FIRE"?listA:listB))invalid();}map->~Map();}
  if(c.op==3){typedef void(*Fn)(void*);Fn fn=ours?nextReset:oldReset;autotest::invoke(out,fn,manager);}
  number(calls);
  if(field<void*>(manager,0x60)!=ordinary||field<void*>(manager,0x48)!=updating)invalid();
  // The map was destroyed above; its allocator/header pointers are no longer live observations.
  if(c.op==2)std::memset(static_cast<char*>(manager)+0x18,0,0x30);
  out.add(manager,0x98);for(unsigned i=0;i<6;++i){if(ordinary[i]!=skills[i]||updating[i]!=skills[5-i])invalid();out.add(skills[i],0x160);}
 }else if(c.op==4){
  void* property=object(0x130);void* skill=object(0x160);owner=object(0x1d8);answer=(c.index/4)&1;
  field<void*>(property,0x38)=c.index%4==0?0:skill;field<void*>(skill,0x30)=c.index%4==1?0:owner;field<int>(owner,0x188)=c.index%4==2?1:0;
  const unsigned values[]={0,0x80000000u,0x3f800000,0xbf800000,1,0x7f800000,0x7fc00001};field<unsigned>(property,0x98)=values[(c.index/4)%7];field<unsigned>(property,0x9c)=values[(c.index/7)%7];
  detour::Set patches;TL_REDIRECT(patches,unitISA,&isaSpy);if(patches.failed()){invalid();return;}
  typedef float(*Fn)(void*);Fn fn=ours?nextCooldownProperty:oldCooldownProperty;autotest::invoke(out,fn,property);number(calls);out.add(property,0x130);out.add(skill,0x160);out.add(owner,0x1d8);
 }else if(c.op<=6){
  controller=object(0x158);new(static_cast<char*>(controller)+0x130)std::wstring(c.index&2?L"synthetic skill":L"");field<bool>(controller,0x14a)=c.index&4;field<bool>(controller,0x14b)=c.index&8;field<unsigned>(controller,0x150)=0x12345678;
  detour::Set patches;TL_REDIRECT(patches,configure,&configureSpy);if(patches.failed()){invalid();return;}
  typedef void(*Fn)(void*);Fn fn=c.op==5?(ours?nextStart:oldStart):(ours?nextStop:oldStop);autotest::invoke(out,fn,controller);number(calls);if(calls!=1)invalid();text(*reinterpret_cast<std::wstring*>(static_cast<char*>(controller)+0x130));reinterpret_cast<std::wstring*>(static_cast<char*>(controller)+0x130)->~basic_string();std::memset(static_cast<char*>(controller)+0x130,0,8);out.add(controller,0x158);
 }else{
  group=object(0x80);void** data=static_cast<void**>(object(4*8));void** table=static_cast<void**>(object(16));table[1]=reinterpret_cast<void*>(&deleteSpy);
  for(unsigned i=0;i<4;++i){logic[i]=object(0x88);field<void*>(logic[i],0)=table;data[i]=(c.index&4)&&i==1?0:logic[i];}
  unsigned count=(c.index/8)%5,capacity=c.index&2?2:4;list(group,0x60,data,count,capacity);
  const unsigned indices[]={0,1,2,3,4,~0u};unsigned index=indices[(c.index/40)%6];
  detour::Set patches;TL_REDIRECT(patches,removeLinks,&linksSpy);if(patches.failed()){invalid();return;}
  typedef bool(*Fn)(void*,unsigned);Fn fn=ours?nextRemove:oldRemove;autotest::invoke(out,fn,group,index);number(calls);if(field<void*>(group,0x60)!=data)invalid();out.add(group,0x80);out.add(data,4*8);for(unsigned i=0;i<4;++i){if(field<void*>(logic[i],0)!=table)invalid();out.add(logic[i],0x88);}
 }
}
}
TL_TEST(followup_skill_any_cooling){return smallmass::run(host,0,"followup_skill_any_cooling",(uint64_t)(uintptr_t)oldCooling,execute,294);}
TL_TEST(followup_skill_find_level){return smallmass::run(host,1,"followup_skill_find_level",(uint64_t)(uintptr_t)oldFindLevel,execute,120);}
TL_TEST(followup_skill_find_name){return smallmass::run(host,2,"followup_skill_find_name",(uint64_t)(uintptr_t)oldFindName,execute,40);}
TL_TEST(followup_skill_reset_levels){return smallmass::run(host,3,"followup_skill_reset_levels",(uint64_t)(uintptr_t)oldReset,execute,144);}
TL_TEST(followup_skill_property_cooldown){return smallmass::run(host,4,"followup_skill_property_cooldown",(uint64_t)(uintptr_t)oldCooldownProperty,execute,196);}
TL_TEST(followup_skill_controller_start){return smallmass::run(host,5,"followup_skill_controller_start",(uint64_t)(uintptr_t)oldStart,execute,32);}
TL_TEST(followup_skill_controller_stop){return smallmass::run(host,6,"followup_skill_controller_stop",(uint64_t)(uintptr_t)oldStop,execute,32);}
TL_TEST(followup_logic_group_remove){return smallmass::run(host,7,"followup_logic_group_remove",(uint64_t)(uintptr_t)oldRemove,execute,240);}
