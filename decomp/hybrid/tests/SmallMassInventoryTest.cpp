#include "SmallMassCompare.h"
#include <OgreQuaternion.h>
#include <vector>
TL_ORIGINAL(void, original0, (void*,std::wstring), "_ZN8CConsole18equipSkillToPlayerESbIwSt11char_traitsIwESaIwEE")
extern "C" void candidate0(void*,std::wstring) __asm__("_ZN8CConsole18equipSkillToPlayerESbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void, original1, (void*), "_ZN8CConsole16addSpeedToPlayerEv")
extern "C" void candidate1(void*) __asm__("_ZN8CConsole16addSpeedToPlayerEv");
TL_ORIGINAL(void, original2, (void*,std::wstring), "_ZN8CConsole11cameraShakeESbIwSt11char_traitsIwESaIwEE")
extern "C" void candidate2(void*,std::wstring) __asm__("_ZN8CConsole11cameraShakeESbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void, original3, (void*,std::wstring,std::wstring,std::wstring), "_ZN8CConsole16spawnClassCreateESbIwSt11char_traitsIwESaIwEES3_S3_")
extern "C" void candidate3(void*,std::wstring,std::wstring,std::wstring) __asm__("_ZN8CConsole16spawnClassCreateESbIwSt11char_traitsIwESaIwEES3_S3_");
TL_ORIGINAL(void, original4, (void*), "_ZN10CInventory13swapWeaponSetEv")
extern "C" void candidate4(void*) __asm__("_ZN10CInventory13swapWeaponSetEv");
TL_ORIGINAL(void, original5, (void*,int,void*), "_ZN10CInventory12executeProcsE12EEFFECT_TYPEP9CBaseUnit")
extern "C" void candidate5(void*,int,void*) __asm__("_ZN10CInventory12executeProcsE12EEFFECT_TYPEP9CBaseUnit");
TL_FUNCTION(dep_addSkill, "_ZN9CBaseUnit14addSkillByNameERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(dep_active, "_ZN10CCharacter20setActiveSkillByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_consoleText, "_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_removeAffix, "_ZN9CBaseUnit11removeAffixERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_addAffix, "_ZN9CBaseUnit8addAffixERKSbIwSt11char_traitsIwESaIwEEjPS_f")
TL_FUNCTION(dep_shake, "_ZN12CCameraShakeC1ERKSbIwSt11char_traitsIwESaIwEEN4Ogre7Vector3Ef")
TL_FUNCTION(dep_camera, "_ZN16CResourceManager16getCameraControlEv")
TL_FUNCTION(dep_addSafe, "_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(dep_position, "_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(dep_bonuses, "_ZN10CInventory13updateBonusesEv")
TL_FUNCTION(dep_effects, "_ZN10CInventory21calculateEffectValuesEv")
TL_FUNCTION(dep_verify, "_ZN10CInventory15verifyEquipmentEv")
TL_FUNCTION(dep_hasEffect, "_ZN9CBaseUnit9hasEffectE12EEFFECT_TYPE")
TL_FUNCTION(dep_roll, "_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(dep_value, "_ZN7CEffect5valueE14EEFFECT_VALUES")
TL_FUNCTION(dep_getSkill, "_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(dep_executeSkill, "_ZN13CSkillManager12executeSkillEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS5_10QuaternionES8_S3_")
TL_FUNCTION(dep_parser, "_ZN17CSpawnClassParser12getSingletonEv")
TL_FUNCTION(dep_spawn, "_ZN17CSpawnClassParser13getSpawnClassERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_create, "_ZN16CResourceManager40createUnitsBySpawnClassAtPositionInLevelEP11CSpawnClassjRKN4Ogre7Vector3EP6CLevelP10CCharacterS9_i")
extern "C" char dep_alloc[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");

TL_ORIGINAL(bool, original6, (void*,void*,int), "_ZN10CInventory34equipEquipmentIntoSpecificLocationEP10CEquipment16EEQUIP_LOCATIONS")
extern "C" bool candidate6(void*,void*,int) __asm__("_ZN10CInventory34equipEquipmentIntoSpecificLocationEP10CEquipment16EEQUIP_LOCATIONS");
TL_FUNCTION(dep_canEquip, "_ZN10CInventory28canEquipIntoSpecificLocationEP10CEquipment16EEQUIP_LOCATIONSb")
TL_FUNCTION(dep_isa, "_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dep_remove, "_ZN10CInventory15removeEquipmentEP10CEquipment")
TL_FUNCTION(dep_pickup, "_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(dep_addItem, "_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(dep_setPosition, "_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(dep_core, "_ZN10CRunicCoreC1Ev")
namespace {
using namespace smallmass;
void* self;void* owner;void* client;void* resources;void* cameraObject;void* parserObject;void* spawnObject;void* skillObject;void* target;
void* equipment[4];unsigned randomCalls;std::vector<std::wstring*> strings;Ogre::Quaternion orientationValue;
void* addSkill(void* p,const std::wstring& name,bool flag) { event(1,p);text(name);number(flag);return skillObject; }
void active(void* p,std::wstring name) { event(2,p);text(name); }
void consoleText(void* p,std::wstring value) { event(3,p);text(value); }
bool removeAffix(void* p,const std::wstring& name) { event(4,p);text(name);return input->index&1; }
void* addAffix(void* p,const std::wstring& name,unsigned level,void* source,float duration) { event(5,p);text(name);number(level);pointer(source);floating(duration);return NULL; }
void* alloc(size_t size,const char* file,int line,const char* function) { number(6);number(size);number(line);number(file!=NULL);number(function!=NULL);return object(size); }
void shake(void* p,const std::wstring& name,Ogre::Vector3 direction,float duration) { event(7,p);text(name);vector(direction);floating(duration); }
void* camera(void* p) { event(8,p);return cameraObject; }
unsigned addSafe(void* p,void* reference) { event(9,p);pointer(reference);return input->index+7; }
void* parser() { number(10);return parserObject; }
void* spawn(void* p,const std::wstring& name) { event(11,p);text(name);return input->index%5==0?NULL:spawnObject; }
Ogre::Vector3 position(void* p,bool absolute) { event(12,p);number(absolute);return p==owner?Ogre::Vector3(1,2,3):Ogre::Vector3(-4,5,-6); }
void create(void* p,void* spawn,unsigned count,const Ogre::Vector3& position,void* level,void* source,void* caster,int unitLevel) { event(13,p);pointer(spawn);number(count);vector(position);pointer(level);pointer(source);pointer(caster);number(unitLevel); }
void bonuses(void* p) { event(14,p); }
void effects(void* p) { event(15,p); }
void verify(void* p) { event(16,p); }
void equipped(void* p,void* inventory,void* unit,int location) { event(17,p);pointer(inventory);pointer(unit);number(location); }
void unequipped(void* p,void* inventory,void* unit,int location) { event(18,p);pointer(inventory);pointer(unit);number(location); }
void notifyEquipped(void* p,void* item) { event(19,p);pointer(item); }
void notifyUnequipped(void* p,void* item) { event(20,p);pointer(item); }
bool hasEffect(void* p,int type) { event(21,p);number(type);return (input->index+field<unsigned>(p,0x10))%3!=0; }
int roll(int low,int high) { number(22);number(low);number(high);++randomCalls;return (input->index+randomCalls*23)%101; }
float value(void* p,int type) { event(23,p);number(type);return field<float>(p,0xc0); }
void* getSkill(void* p,const std::wstring& name,int level) { event(24,p);text(name);number(level);return (input->index+level)%3?skillObject:NULL; }
void* executeSkill(void* p,void* skill,void* caster,int activation,const Ogre::Vector3& position,const Ogre::Quaternion& orientation,const Ogre::Vector3& targetPosition,void* target) { event(25,p);pointer(skill);pointer(caster);number(activation);vector(position);output->add(&orientation,sizeof(orientation));vector(targetPosition);pointer(target);return skill; }
const Ogre::Quaternion& orientation(void* p) { event(26,p);return orientationValue; }

bool canEquip(void* p,void* item,int location,bool force) { event(27,p);pointer(item);number(location);number(force);return input->index%4!=0; }
bool isa(void* p,int type) { event(28,p);number(type);return input->index&2; }
long long remove(void* p,void* item) { event(29,p);pointer(item);return 0; }
void* pickup(void* p,void* item,bool flag) { event(30,p);pointer(item);number(flag);return input->index&4?item:NULL; }
void addItem(void* p,void* item,const Ogre::Vector3& v,bool flag) { event(31,p);pointer(item);vector(v);number(flag); }
void setPosition(void* p,const Ogre::Vector3& v) { event(32,p);vector(v); }
void drop(void* p) { event(33,p); }
void core(void* p) { event(34,p);field<void*>(p,8)=NULL; }
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;randomCalls=0;strings.clear();
 self=object(0x600);owner=object(0xa40);client=object(0x100);resources=object(0x100);cameraObject=object(0x100);parserObject=object(16);spawnObject=object(16);skillObject=object(0x160);target=object(0x778);
 field<void*>(self,0x50)=resources;field<void*>(self,0x58)=client;field<void*>(client,0x58)=c.index%7==0?NULL:owner;field<void*>(resources,0x18)=c.index%11==0?NULL:object(16);
 void** references=static_cast<void**>(object(4*8));list(cameraObject,0x58,references,c.index%3,4);
 void** equipTable=static_cast<void**>(object(0x368));equipTable[0x320/8]=reinterpret_cast<void*>(&equipped);equipTable[0x328/8]=reinterpret_cast<void*>(&unequipped);equipTable[0x360/8]=reinterpret_cast<void*>(&drop);
 void** listenerTable=static_cast<void**>(object(0x38));listenerTable[4]=reinterpret_cast<void*>(&notifyEquipped);listenerTable[5]=reinterpret_cast<void*>(&notifyUnequipped);
 void** equipmentRefs=static_cast<void**>(object(6*8));const unsigned slots[]={0,1,12,13};
 for(unsigned i=0;i<4;++i) {
  equipment[i]=object(0x350);field<void*>(equipment[i],0)=equipTable;field<void*>(equipment[i],0x68)=resources;field<unsigned>(equipment[i],0x10)=i;
  void* reference=object(0x28);field<void*>(reference,0x10)=equipment[i];field<unsigned>(reference,0x18)=c.op==5?i:slots[i];equipmentRefs[i]=c.op!=5&&!(c.index&(1<<i))?NULL:reference;
  void* manager=object(0x100);field<void*>(equipment[i],0x1b8)=manager;field<void*>(equipment[i],0x1c8)=(c.index+i)%5==0?NULL:object(0x98);
  for(unsigned activation=0;activation<3;++activation) {
   void** entries=static_cast<void**>(object(16));list(manager,0x28+activation*24,entries,(c.index+activation)%3,2);
   for(unsigned j=0;j<2;++j){void* effect=object(0x138);entries[j]=effect;field<unsigned>(effect,0x10)=j+activation;field<unsigned>(effect,0x1c)=((c.index+activation+j)%3==0)?78:77;
    const float chances[]={0,25,50,100,-1};field<float>(effect,0xc0)=c.index%17==0?bits(0x7fc01234):chances[(c.index+j)%5];
    std::wstring* name=new(static_cast<char*>(effect)+0x80)std::wstring(j?L"skill_b":L"skill_a");strings.push_back(name);
   }
  }
 }
 if(c.op>=4) {field<void*>(self,0x20)=owner;list(self,0x30,equipmentRefs,4,c.op==6?6:c.index%19==0?1:4);void** listeners=static_cast<void**>(object(24));for(unsigned i=0;i<3;++i){listeners[i]=object(16);field<void*>(listeners[i],0)=listenerTable;}list(self,0x48,listeners,c.index%4,c.index%9==0?1:3);}
 void* node=object(16);field<void*>(owner,0x58)=node;void** nodeTable=static_cast<void**>(object(0xd0));nodeTable[0xc8/8]=reinterpret_cast<void*>(&orientation);field<void*>(node,0)=nodeTable;orientationValue=Ogre::Quaternion(1,0.25f,0.5f,0.75f);
 detour::Set patches;
 TL_REDIRECT(patches,dep_addSkill,&addSkill);
 TL_REDIRECT(patches,dep_active,&active);
 TL_REDIRECT(patches,dep_consoleText,&consoleText);
 TL_REDIRECT(patches,dep_removeAffix,&removeAffix);
 TL_REDIRECT(patches,dep_addAffix,&addAffix);
 TL_REDIRECT(patches,dep_shake,&shake);
 TL_REDIRECT(patches,dep_camera,&camera);
 TL_REDIRECT(patches,dep_addSafe,&addSafe);
 TL_REDIRECT(patches,dep_position,&position);
 TL_REDIRECT(patches,dep_bonuses,&bonuses);
 TL_REDIRECT(patches,dep_effects,&effects);
 TL_REDIRECT(patches,dep_verify,&verify);
 TL_REDIRECT(patches,dep_hasEffect,&hasEffect);
 TL_REDIRECT(patches,dep_roll,&roll);
 TL_REDIRECT(patches,dep_value,&value);
 TL_REDIRECT(patches,dep_getSkill,&getSkill);
 TL_REDIRECT(patches,dep_executeSkill,&executeSkill);
 TL_REDIRECT(patches,dep_parser,&parser);
 TL_REDIRECT(patches,dep_spawn,&spawn);
 TL_REDIRECT(patches,dep_create,&create);

 TL_REDIRECT(patches,dep_canEquip,&canEquip);
 TL_REDIRECT(patches,dep_isa,&isa);
 TL_REDIRECT(patches,dep_remove,&remove);
 TL_REDIRECT(patches,dep_pickup,&pickup);
 TL_REDIRECT(patches,dep_addItem,&addItem);
 TL_REDIRECT(patches,dep_setPosition,&setPosition);
 TL_REDIRECT(patches,dep_core,&core);
 if(c.op==2||c.op==6)patches.redirect(dep_alloc,dep_alloc,&alloc);if(patches.failed())_exit(41);
 const wchar_t* names[]={L"",L"skill",L"MiXeD",L"Longer effect name"};std::wstring name=names[c.index%4];
 switch(c.op) {
 case 0:{void(*fn)(void*,std::wstring)=ours?candidate0:original0;if(!autotest::beginInvocation(out,fn))return;fn(self,name);out.callCompleted=1;break;}
 case 1:autotest::invoke(out,ours?candidate1:original1,self);break;
 case 2:{void(*fn)(void*,std::wstring)=ours?candidate2:original2;if(!autotest::beginInvocation(out,fn))return;fn(self,name);out.callCompleted=1;break;}
 case 3:{const wchar_t* counts[]={L"0",L"1",L"25",L"01",L"-1",L"",L" 1",L"4294967295",L"junk"};const wchar_t* levels[]={L"0",L"3",L"-1",L"",L"04",L"4294967295"};std::wstring count=counts[c.index%9],level=levels[(c.index/3)%6];void(*fn)(void*,std::wstring,std::wstring,std::wstring)=ours?candidate3:original3;if(!autotest::beginInvocation(out,fn))return;fn(self,name,count,level);out.callCompleted=1;break;}
 case 4:autotest::invoke(out,ours?candidate4:original4,self);break;
 case 6:autotest::invoke(out,ours?candidate6:original6,self,equipment[c.index%4],int((c.index/4)%5));break;
 case 5:autotest::invoke(out,ours?candidate5:original5,self,77,c.index&1?target:NULL);break;
 }
 for(unsigned i=0;i<strings.size();++i){text(*strings[i]);std::memset(strings[i],0,sizeof(std::wstring));}
 number(randomCalls);out.add(autotest::g_arena,autotest::g_arenaUsed);
}
}
TL_TEST(smallmass2_inventory_console_skill) { return smallmass::run(host,0,"smallmass2_inventory_console_skill",(uint64_t)(uintptr_t)original0,execute,128); }
TL_TEST(smallmass2_inventory_console_speed) { return smallmass::run(host,1,"smallmass2_inventory_console_speed",(uint64_t)(uintptr_t)original1,execute,128); }
TL_TEST(smallmass2_inventory_console_shake) { return smallmass::run(host,2,"smallmass2_inventory_console_shake",(uint64_t)(uintptr_t)original2,execute,128); }
TL_TEST(smallmass2_inventory_console_spawn) { return smallmass::run(host,3,"smallmass2_inventory_console_spawn",(uint64_t)(uintptr_t)original3,execute,128); }
TL_TEST(smallmass2_inventory_swap) { return smallmass::run(host,4,"smallmass2_inventory_swap",(uint64_t)(uintptr_t)original4,execute,128); }
TL_TEST(smallmass2_inventory_procs) { return smallmass::run(host,5,"smallmass2_inventory_procs",(uint64_t)(uintptr_t)original5,execute,128); }
TL_TEST(smallmass2_inventory_equip_specific) { return smallmass::run(host,6,"smallmass2_inventory_equip_specific",(uint64_t)(uintptr_t)original6,execute,128); }
