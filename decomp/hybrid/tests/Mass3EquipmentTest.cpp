#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,void*,const wchar_t*,int,bool), "_ZL23createEquipmentAndEquipP10CCharacterP10CDataGroupPKw16EEQUIP_LOCATIONSb")
extern "C" void candidate0(void*,void*,const wchar_t*,int,bool) __asm__("__tlhybrid_local_96__ZL23createEquipmentAndEquipP10CCharacterP10CDataGroupPKw16EEQUIP_LOCATIONSb");
TL_ORIGINAL(void, original1, (void*,void*,const wchar_t*,int), "_ZL12loadAndEquipP10CCharacterP10CDataGroupPKw16EEQUIP_LOCATIONS")
extern "C" void candidate1(void*,void*,const wchar_t*,int) __asm__("__tlhybrid_local_96__ZL12loadAndEquipP10CCharacterP10CDataGroupPKw16EEQUIP_LOCATIONS");
TL_ORIGINAL(void, original2, (void*,void*,const wchar_t*,int), "_ZL22loadAndEquipSpawnClassP10CCharacterP10CDataGroupPKw16EEQUIP_LOCATIONS")
extern "C" void candidate2(void*,void*,const wchar_t*,int) __asm__("__tlhybrid_local_96__ZL22loadAndEquipSpawnClassP10CCharacterP10CDataGroupPKw16EEQUIP_LOCATIONS");
TL_ORIGINAL(void, original3, (void*), "_ZN10CCharacter22createDefaultEquipmentEv")
extern "C" void candidate3(void*) __asm__("_ZN10CCharacter22createDefaultEquipmentEv");
TL_ORIGINAL(void, original4, (void*), "_ZN10CCharacter25generateMerchantInventoryEv")
extern "C" void candidate4(void*) __asm__("_ZN10CCharacter25generateMerchantInventoryEv");
#include "TArrayList.h"
TL_FUNCTION(dep_create, "_ZN16CResourceManager15createEquipmentEPKwbb")
TL_FUNCTION(dep_pickup, "_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(dep_specific, "_ZN10CInventory34equipEquipmentIntoSpecificLocationEP10CEquipment16EEQUIP_LOCATIONS")
TL_FUNCTION(dep_enchant, "_ZN10CEquipment7enchantEb")
TL_FUNCTION(dep_first, "_ZN10CInventory35equipEquipmentIntoFirstFreeLocationEP10CEquipment")
TL_FUNCTION(dep_stringValue, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(dep_group, "_ZN10CDataGroup18GetDataGroupByNameERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(dep_spawn, "_ZN16CResourceManager19getSpawnClassByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_roll, "_ZN11CSpawnClass14rollSpawnClassER10TArrayListIP10CDataGroupEPS0_IbEP10CCharacterS8_ijiiii")
TL_FUNCTION(dep_scale, "_ZN10CCharacter31playerLevelForMerchantInventoryEv")
TL_FUNCTION(dep_boolValue, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(dep_random, "_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(dep_createUnits, "_ZN16CResourceManager23createUnitsBySpawnClassEP11CSpawnClassR10TArrayListIP9CBaseUnitEjP10CCharacterS8_ii")
TL_FUNCTION(dep_isa, "_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dep_destroyText, "_ZN5CItem15destroyItemTextEv")
TL_FUNCTION(dep_price, "_ZN10CEquipment16recalculatePriceEv")
TL_FUNCTION(dep_player, "_ZN6CLevel9getPlayerEv")

extern "C" void* originalEquipmentTable[] __asm__("_ZTV10CEquipment");
namespace {
using namespace smallmass;
void *self,*resources,*inventory,*data,*equipment,*model,*spawnClass,*otherEquipment,*hero;void* groups[4];unsigned created,pickups;
void* create(void* p,const wchar_t* name,bool first,bool second){event(1,p);text(std::wstring(name));number(first);number(second);++created;return input->index%7==0?0:equipment;}
void* pickup(void* p,void* value,bool flag){event(2,p);pointer(value);number(flag);++pickups;return (input->index+pickups)%5==0?0:input->index&1?otherEquipment:value;}
bool specific(void* p,void* value,int slot){event(3,p);pointer(value);number(slot);return input->index&1;}
void enchant(void* p,bool flag){event(4,p);number(flag);field<bool>(p,0x349)=true;}
bool first(void* p,void* value){event(5,p);pointer(value);return input->index&2;}
const std::wstring& stringValue(void* p,const std::wstring& name,const std::wstring& fallback){event(6,p);text(name);text(fallback);if(input->index%11==0)return fallback;static const std::wstring generated(L"Generated Item");return name==L"NAME"?generated:name;}
void* group(void* p,const std::wstring& name,bool create){event(7,p);text(name);number(create);return input->index%5?data:0;}
void* spawn(void* p,const std::wstring& name){event(8,p);text(name);return input->index%7?spawnClass:0;}
void roll(void* p,TArrayList<void*>& output,TArrayList<bool>* flags,void* a,void* b,int level,unsigned min,int x,int y,int z,int mode){
 event(9,p);pointer(a);pointer(b);number(level);number(min);number(x);number(y);number(z);number(mode);
 for(unsigned i=0;i<input->index%4;++i){output.add(groups[i]);flags->add((input->index+i)&1);}
}
float scale(void* p){event(10,p);const float v[]={-1,0,.5f,1,1.25f,2};return v[input->index%6];}
bool boolValue(void* p,const std::wstring& name,bool fallback){event(11,p);text(name);number(fallback);return name==L"ALLOWS_MERCH_UNIQUES"?input->index&2:input->index&4;}
int random(int lo,int hi){number(12);number(lo);number(hi);return 1+input->index%5;}
void createUnits(void* p,void* spawn,TArrayList<void*>& units,unsigned count,void* a,void* b,int level,int flags){event(13,p);pointer(spawn);number(count);pointer(a);pointer(b);number(level);number(flags);for(unsigned i=0;i<input->index%5;++i)units.add(i&1?otherEquipment:equipment);}
bool isa(void* p,int type){event(14,p);number(type);return p==self?input->index&8:(input->index+(p==equipment?1:2))%3==0;}
void destroyText(void* p){event(15,p);}
void price(void* p){event(16,p);}
void* player(void* p){event(17,p);return input->index%5?hero:0;}
void* getModel(void* p){event(18,p);return model;}
void renderQueue(void* p,unsigned char queue){event(19,p);number(queue);}
bool magical(void* p){event(20,p);return (input->index+(p==equipment?0:1))%3==0;}
void destroy(void* p){event(21,p);field<bool>(p,0x34a)=true;}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;created=pickups=0;
 self=object(0x778);resources=object(0x48);inventory=object(0x200);data=object(0x80);equipment=object(0x480);otherEquipment=object(0x480);model=object(0x258);spawnClass=object(0x100);hero=object(0x778);
 void* level=object(0x2f0);void* entity=object(0x300);
 void** storage=static_cast<void**>(object(0x420));storage[1]=originalEquipmentTable[1];void** table=storage+2;table[0x1e0/8]=reinterpret_cast<void*>(&getModel);table[0x2b0/8]=reinterpret_cast<void*>(&magical);table[1]=reinterpret_cast<void*>(&destroy);field<void*>(equipment,0)=field<void*>(otherEquipment,0)=table;
 void** entityTable=static_cast<void**>(object(0x200));entityTable[0x140/8]=reinterpret_cast<void*>(&renderQueue);field<void*>(entity,0)=entityTable;field<void*>(model,0x60)=entity;
 field<void*>(self,0x68)=c.index%13?resources:0;field<void*>(self,0x490)=c.index%17?inventory:0;field<void*>(self,0x1b0)=c.op==3&&c.index%7==0?0:data;field<void*>(resources,0x18)=c.index%19?level:0;
 field<void*>(self,0x6c0)=c.index%11?spawnClass:0;field<int>(self,0x6c8)=2;field<int>(self,0x6cc)=5;field<bool>(inventory,0x14)=true;field<unsigned>(hero,0x100)=c.index%17==0?0xffffffffu:c.index%21;
 for(unsigned i=0;i<4;++i)groups[i]=object(0x80);
 detour::Set patches;
 TL_REDIRECT(patches,dep_create,&create);
 TL_REDIRECT(patches,dep_pickup,&pickup);
 TL_REDIRECT(patches,dep_specific,&specific);
 TL_REDIRECT(patches,dep_enchant,&enchant);
 TL_REDIRECT(patches,dep_first,&first);
 TL_REDIRECT(patches,dep_stringValue,&stringValue);
 TL_REDIRECT(patches,dep_group,&group);
 TL_REDIRECT(patches,dep_spawn,&spawn);
 TL_REDIRECT(patches,dep_roll,&roll);
 TL_REDIRECT(patches,dep_scale,&scale);
 TL_REDIRECT(patches,dep_boolValue,&boolValue);
 TL_REDIRECT(patches,dep_random,&random);
 TL_REDIRECT(patches,dep_createUnits,&createUnits);
 TL_REDIRECT(patches,dep_isa,&isa);
 TL_REDIRECT(patches,dep_destroyText,&destroyText);
 TL_REDIRECT(patches,dep_price,&price);
 TL_REDIRECT(patches,dep_player,&player);

 if(patches.failed())_exit(41);
 int location=c.index%4==0?12:int(c.index%12);
 void* characterArg=c.index%23?self:0;void* dataArg=c.index%29?data:0;
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,characterArg,dataArg,c.index%31?L"Sword":0,location,bool(c.index&1));break;
 case 1:autotest::invoke(out,ours?candidate1:original1,characterArg,dataArg,L"RIGHTHAND",location);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,characterArg,dataArg,L"SPAWNCLASS",location);break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self);break;
 case 4:autotest::invoke(out,ours?candidate4:original4,self);break;
 }
 number(created);number(pickups);number(field<bool>(inventory,0x14));number(field<bool>(equipment,0x348));number(field<bool>(equipment,0x349));number(field<bool>(equipment,0x34a));number(field<bool>(otherEquipment,0x348));number(field<bool>(otherEquipment,0x349));number(field<bool>(otherEquipment,0x34a));
}
}
TL_TEST(mass3_8132f0) { return smallmass::run(host,0,"mass3_8132f0",(uint64_t)(uintptr_t)original0,execute,192); }
TL_TEST(mass3_83e6f0) { return smallmass::run(host,1,"mass3_83e6f0",(uint64_t)(uintptr_t)original1,execute,128); }
TL_TEST(mass3_83bd10) { return smallmass::run(host,2,"mass3_83bd10",(uint64_t)(uintptr_t)original2,execute,192); }
TL_TEST(mass3_83e8a0) { return smallmass::run(host,3,"mass3_83e8a0",(uint64_t)(uintptr_t)original3,execute,64); }
TL_TEST(mass3_836cb0) { return smallmass::run(host,4,"mass3_836cb0",(uint64_t)(uintptr_t)original4,execute,256); }
