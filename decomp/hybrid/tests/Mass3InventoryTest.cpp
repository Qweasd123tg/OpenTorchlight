#include "TArrayList.h"
#include <map>
#include "SmallMassCompare.h"
TL_ORIGINAL(bool, original0, (void*,void*,bool), "_ZN10CInventory8canEquipEP10CEquipmentb")
extern "C" bool candidate0(void*,void*,bool) __asm__("_ZN10CInventory8canEquipEP10CEquipmentb");
TL_ORIGINAL(void, original1, (void*,void*,void**,void**), "_ZN10CInventory18getComparisonItemsEP10CEquipmentPS1_S2_")
extern "C" void candidate1(void*,void*,void**,void**) __asm__("_ZN10CInventory18getComparisonItemsEP10CEquipmentPS1_S2_");
TL_ORIGINAL(bool, original2, (void*,void*), "_ZN10CInventory35equipEquipmentIntoFirstFreeLocationEP10CEquipment")
extern "C" bool candidate2(void*,void*) __asm__("_ZN10CInventory35equipEquipmentIntoFirstFreeLocationEP10CEquipment");
TL_ORIGINAL(void*, original3, (void*,void*,int,bool), "_ZN10CInventory15pickupEquipmentEP10CEquipmentib")
extern "C" void* candidate3(void*,void*,int,bool) __asm__("_ZN10CInventory15pickupEquipmentEP10CEquipmentib");
TL_ORIGINAL(void*, original4, (void*,void*,bool), "_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
extern "C" void* candidate4(void*,void*,bool) __asm__("_ZN10CInventory15pickupEquipmentEP10CEquipmentb");
TL_ORIGINAL(void, original5, (void*), "_ZN10CInventory21calculateEffectValuesEv")
extern "C" void candidate5(void*) __asm__("_ZN10CInventory21calculateEffectValuesEv");
TL_FUNCTION(dep_isa, "_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dep_canPickup, "_ZN10CInventory9canPickupEP10CEquipmentb")
TL_FUNCTION(dep_canEquip, "_ZN10CInventory8canEquipEP10CEquipmentb")
TL_FUNCTION(dep_canSpecific, "_ZN10CInventory28canEquipIntoSpecificLocationEP10CEquipment16EEQUIP_LOCATIONSb")
TL_FUNCTION(dep_freeSlot, "_ZN10CInventory12findFreeSlotEP10CEquipment")
TL_FUNCTION(dep_pickupSlot, "_ZN10CInventory15pickupEquipmentEP10CEquipmentib")
TL_FUNCTION(dep_pickup, "_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(dep_reskin, "_ZN10CEquipment13reskinByClassESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_remove, "_ZN10CInventory15removeEquipmentEP10CEquipment")
TL_FUNCTION(dep_addItem, "_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(dep_position, "_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(dep_deleteItem, "_ZN6CLevel10deleteItemEP5CItem")
TL_FUNCTION(dep_bonuses, "_ZN10CInventory13updateBonusesEv")
TL_FUNCTION(dep_effects, "_ZN10CInventory21calculateEffectValuesEv")
TL_FUNCTION(dep_verify, "_ZN10CInventory15verifyEquipmentEv")
TL_FUNCTION(dep_core, "_ZN10CRunicCoreC1Ev")
TL_FUNCTION(dep_clearAffix, "_ZN14CEffectManager20clearOutAffixEffectsEv")
TL_FUNCTION(dep_clearEffects, "_ZN14CEffectManager12clearEffectsEb")
TL_FUNCTION(dep_getSet, "_ZN10CEquipment6getSetEv")
TL_FUNCTION(dep_sets, "_ZN5CSets12getSingletonEv")
TL_FUNCTION(dep_findSet, "_ZN5CSets6getSetEPKw")
TL_FUNCTION(dep_countSet, "_ZN10CInventory11getSetCountEP4CSet")
TL_FUNCTION(dep_affix, "_ZN14CEffectManager8addAffixERKSbIwSt11char_traitsIwESaIwEEjP9CBaseUnitP16CResourceManagerf")
TL_FUNCTION(dep_calculateManager, "_ZN14CEffectManager21calculateEffectValuesEv")
TL_FUNCTION(dep_calculateValue, "_ZN10CInventory20calculateEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")

extern "C" char allocator[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
namespace {
using namespace smallmass;
void *self,*owner,*resources,*services,*equipment[14],*setObjects[3];unsigned valueCalls;
bool isa(void* p,int type){event(1,p);number(type);if(p==owner)return type==28&&(input->index&2);unsigned kind=field<unsigned>(p,0x10);return int(kind)==type||(type==8&&(kind==9||kind==10||kind==36))||(type==9&&kind==36);}
bool canPickup(void* p,void* item,bool flag){event(2,p);pointer(item);number(flag);return input->index%7!=0;}
bool canEquip(void* p,void* item,bool flag){event(3,p);pointer(item);number(flag);return input->index%7!=0;}
bool canSpecific(void* p,void* item,int slot,bool flag){event(4,p);pointer(item);number(slot);number(flag);return (input->index+slot)%3!=0;}
int freeSlot(void* p,void* item){event(5,p);pointer(item);return input->index&4?-1:19+input->index%8;}
void* pickupSlot(void* p,void* item,int slot,bool flag){event(6,p);pointer(item);number(slot);number(flag);return input->index%11?item:0;}
void* pickup(void* p,void* item,bool flag){event(7,p);pointer(item);number(flag);return input->index%3?item:0;}
void reskin(void* p,std::wstring name){event(8,p);text(name);}
void remove(void* p,void* item){event(9,p);pointer(item);TArrayList<void*>& refs=field<TArrayList<void*> >(p,0x30);for(unsigned i=0;i<refs.size();++i)if(refs[i]&&field<void*>(refs[i],0x10)==item){refs.removeAt(i);break;}}
void addItem(void* p,void* item,const Ogre::Vector3& value,bool flag){event(10,p);pointer(item);vector(value);number(flag);}
void position(void* p,const Ogre::Vector3& value){event(11,p);vector(value);field<Ogre::Vector3>(p,0x84)=value;}
void deleteItem(void* p,void* item){event(12,p);pointer(item);}
void bonuses(void* p){event(13,p);}
void effects(void* p){event(14,p);}
void verify(void* p){event(15,p);}
void core(void* p){event(16,p);field<void*>(p,8)=0;}
void clearAffix(void* p){event(17,p);}
void clearEffects(void* p,bool flag){event(18,p);number(flag);}
std::wstring getSet(void* p){event(19,p);const wchar_t* names[]={L"",L"SET A",L"SET B",L"MISSING"};return names[(field<unsigned>(p,0x14)+input->index)%4];}
void* sets(){number(20);return services;}
void* findSet(void* p,const wchar_t* name){event(21,p);text(std::wstring(name));return std::wstring(name)==L"MISSING"?0:setObjects[std::wstring(name)==L"SET A"?0:1];}
int countSet(void* p,void* set){event(22,p);pointer(set);return int(input->index%5);}
void* affix(void* p,const std::wstring& name,unsigned level,void* source,void* resources,float scale){event(23,p);text(name);number(level);pointer(source);pointer(resources);floating(scale);return services;}
void calculateManager(void* p){event(24,p);}
float calculateValue(void* p,int effect,int damage){event(25,p);number(effect);number(damage);++valueCalls;if((effect+damage+input->index)%7)return 0;if(input->index%17==0&&effect==0)return bits(0x7fc01234);return float(effect-damage*20)*.125f;}
void* alloc(size_t size,const char* file,int line,const char* function){number(26);number(size);number(file!=0);number(line);number(function!=0);return object(size);}
bool equipmentCanEquip(void* p,void* owner,bool flag){event(27,p);pointer(owner);number(flag);return input->index%5!=0;}
void equipped(void* p,void* inventory,void* owner,int slot){event(28,p);pointer(inventory);pointer(owner);number(slot);}
void added(void* p,void* inventory,void* owner){event(29,p);pointer(inventory);pointer(owner);}
void increment(void* p,int delta){event(30,p);number(delta);field<int>(p,0x238)+=delta;}
void drop(void* p){event(31,p);}
void destroy(void* p){event(32,p);}
void picked(void* p,void* item){event(33,p);pointer(item);}
void notifyEquipped(void* p,void* item){event(34,p);pointer(item);}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;valueCalls=0;self=object(0x218);owner=object(0x778);resources=object(0x48);services=object(0x140);
 field<void*>(self,0x20)=owner;field<void*>(self,0x18)=services;field<bool>(self,0x14)=c.index&1;field<void*>(owner,0x68)=resources;field<void*>(resources,0x18)=c.index%5?object(0x2f0):0;
 new(static_cast<char*>(owner)+0x40)std::wstring(L"VANQUISHER");field<Ogre::Vector3>(owner,0x84)=Ogre::Vector3(1,2,3);
 void** table=static_cast<void**>(object(0x368));table[1]=reinterpret_cast<void*>(&destroy);table[0x2f8/8]=reinterpret_cast<void*>(&equipmentCanEquip);table[0x310/8]=reinterpret_cast<void*>(&added);table[0x320/8]=reinterpret_cast<void*>(&equipped);table[0x338/8]=reinterpret_cast<void*>(&increment);table[0x360/8]=reinterpret_cast<void*>(&drop);
 const unsigned kinds[]={8,9,10,21,36,23,12,15,20,16,18,17,24,22};
 for(unsigned i=0;i<14;++i){equipment[i]=object(0x350);field<void*>(equipment[i],0)=table;field<unsigned>(equipment[i],0x10)=kinds[(c.index+i)%14];field<unsigned>(equipment[i],0x14)=i;field<void*>(equipment[i],0x68)=c.index%7?resources:0;field<long long>(equipment[i],0x1a0)=((c.index+i)%3==0?7:8);field<int>(equipment[i],0x238)=int((c.index+i*3)%9)-1;field<int>(equipment[i],0x23c)=(c.index+i)%5==0?1:6;}
 new(static_cast<char*>(self)+0x30)TArrayList<void*>(4);TArrayList<void*>& refs=field<TArrayList<void*> >(self,0x30);
 for(unsigned i=0;i<c.index%13;++i){void* ref=object(0x28);field<void*>(ref,0x10)=(c.index+i)%9==0?0:equipment[(c.index/13+i)%14];field<int>(ref,0x18)=i;field<int>(ref,0x1c)=i+19;field<bool>(ref,0x21)=(c.index+i)%4!=0;if(c.op==5&&!field<void*>(ref,0x10))field<bool>(ref,0x21)=false;refs.add((c.index+i)%11==0?0:ref);}
 if(c.op==3&&c.index%3==0){void* ref=object(0x28);field<void*>(ref,0x10)=equipment[1];field<int>(ref,0x18)=19;refs.add(ref);}
 int* pane=static_cast<int*>(object(8));pane[0]=0;pane[1]=3;field<void*>(self,0x60)=pane;field<void*>(self,0x68)=pane+2;field<void*>(self,0x70)=pane+2;
 unsigned* starts=static_cast<unsigned*>(object(8));starts[0]=19;starts[1]=27;field<void*>(self,0x78)=starts;field<void*>(self,0x80)=starts+2;field<void*>(self,0x88)=starts+2;field<unsigned>(self,0x28)=35;
 void** listenerTable=static_cast<void**>(object(0x38));listenerTable[2]=reinterpret_cast<void*>(&picked);listenerTable[4]=reinterpret_cast<void*>(&notifyEquipped);void** listeners=static_cast<void**>(object(24));for(unsigned i=0;i<3;++i){listeners[i]=object(16);field<void*>(listeners[i],0)=listenerTable;}list(self,0x48,listeners,c.index%4,3);
 for(unsigned i=0;i<8;++i){std::map<int,float>* values=new(static_cast<char*>(self)+0x90+i*0x30)std::map<int,float>;(*values)[999]=42;}
 for(unsigned i=0;i<3;++i){setObjects[i]=object(0x30);new(static_cast<char*>(setObjects[i])+8)TArrayList<void*>(3);TArrayList<void*>& bonuses=field<TArrayList<void*> >(setObjects[i],8);for(unsigned j=0;j<3;++j){void* bonus=object(0x18);new(static_cast<char*>(bonus)+8)std::wstring(j?L"GREATER":L"LESSER");field<unsigned>(bonus,0x10)=i+j;field<int>(bonus,0x14)=j+1;bonuses.add(bonus);}}
 detour::Set patches;
 TL_REDIRECT(patches,dep_isa,&isa);
 TL_REDIRECT(patches,dep_canPickup,&canPickup);
 if(c.op!=0)TL_REDIRECT(patches,dep_canEquip,&canEquip);
 TL_REDIRECT(patches,dep_canSpecific,&canSpecific);
 TL_REDIRECT(patches,dep_freeSlot,&freeSlot);
 if(c.op!=3)TL_REDIRECT(patches,dep_pickupSlot,&pickupSlot);
 if(c.op!=4)TL_REDIRECT(patches,dep_pickup,&pickup);
 TL_REDIRECT(patches,dep_reskin,&reskin);
 TL_REDIRECT(patches,dep_remove,&remove);
 TL_REDIRECT(patches,dep_addItem,&addItem);
 TL_REDIRECT(patches,dep_position,&position);
 TL_REDIRECT(patches,dep_deleteItem,&deleteItem);
 TL_REDIRECT(patches,dep_bonuses,&bonuses);
 if(c.op!=5)TL_REDIRECT(patches,dep_effects,&effects);
 TL_REDIRECT(patches,dep_verify,&verify);
 TL_REDIRECT(patches,dep_core,&core);
 TL_REDIRECT(patches,dep_clearAffix,&clearAffix);
 TL_REDIRECT(patches,dep_clearEffects,&clearEffects);
 TL_REDIRECT(patches,dep_getSet,&getSet);
 TL_REDIRECT(patches,dep_sets,&sets);
 TL_REDIRECT(patches,dep_findSet,&findSet);
 TL_REDIRECT(patches,dep_countSet,&countSet);
 TL_REDIRECT(patches,dep_affix,&affix);
 TL_REDIRECT(patches,dep_calculateManager,&calculateManager);
 TL_REDIRECT(patches,dep_calculateValue,&calculateValue);

 patches.redirect(allocator,allocator,&alloc);if(patches.failed())_exit(41);
 void* first=c.index&16?equipment[12]:0;void* second=c.index&32?equipment[13]:0;const int slots[]={-1,999,0,1,2,11,12,19,20,26,27,34,35,40};
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,self,equipment[0],bool(c.index&2));break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,equipment[0],&first,&second);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,equipment[0]);break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self,equipment[0],slots[(c.index/3)%14],bool(c.index&2));break;
 case 4:autotest::invoke(out,ours?candidate4:original4,self,equipment[0],bool(c.index&2));break;
 case 5:autotest::invoke(out,ours?candidate5:original5,self);break;
 }
 pointer(first);pointer(second);number(valueCalls);number(refs.size());
 for(unsigned i=0;i<refs.size();++i){number(refs[i]!=0);if(refs[i]){pointer(field<void*>(refs[i],0x10));number(field<int>(refs[i],0x18));number(field<int>(refs[i],0x1c));number(field<bool>(refs[i],0x20));number(field<bool>(refs[i],0x21));}}
 for(unsigned i=0;i<14;++i){number(field<int>(equipment[i],0x238));vector(field<Ogre::Vector3>(equipment[i],0x84));}
 if(c.op==5)for(unsigned i=0;i<8;++i){const std::map<int,float>& values=field<std::map<int,float> >(self,0x90+i*0x30);number(values.size());for(std::map<int,float>::const_iterator it=values.begin();it!=values.end();++it){number(it->first);floating(it->second);}}
}
}
TL_TEST(mass3_91bdc0) { return smallmass::run(host,0,"mass3_91bdc0",(uint64_t)(uintptr_t)original0,execute,384); }
TL_TEST(mass3_91c2a0) { return smallmass::run(host,1,"mass3_91c2a0",(uint64_t)(uintptr_t)original1,execute,384); }
TL_TEST(mass3_925970) { return smallmass::run(host,2,"mass3_925970",(uint64_t)(uintptr_t)original2,execute,384); }
TL_TEST(mass3_924bd0) { return smallmass::run(host,3,"mass3_924bd0",(uint64_t)(uintptr_t)original3,execute,448); }
TL_TEST(mass3_9251b0) { return smallmass::run(host,4,"mass3_9251b0",(uint64_t)(uintptr_t)original4,execute,384); }
TL_TEST(mass3_924440) { return smallmass::run(host,5,"mass3_924440",(uint64_t)(uintptr_t)original5,execute,80); }
