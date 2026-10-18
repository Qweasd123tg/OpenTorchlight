#include "SmallMassCompare.h"
#include "TArrayList.h"
TL_ORIGINAL(void,resourceOld0,(void*,void*,unsigned,unsigned),"_ZN16CResourceManager20createAffixesForUnitEP9CBaseUnitjj")
extern "C" void resourceNew0(void*,void*,unsigned,unsigned) __asm__("_ZN16CResourceManager20createAffixesForUnitEP9CBaseUnitjj");
TL_ORIGINAL(void*,resourceOld1,(void*),"_ZN16CResourceManager14getGraphDamageEv")
extern "C" void* resourceNew1(void*) __asm__("_ZN16CResourceManager14getGraphDamageEv");
TL_ORIGINAL(void*,resourceOld2,(void*,long long,int,bool),"_ZN16CResourceManager13createMonsterExib")
extern "C" void* resourceNew2(void*,long long,int,bool) __asm__("_ZN16CResourceManager13createMonsterExib");
TL_ORIGINAL(void*,resourceOld3,(void*,const wchar_t*,int,bool),"_ZN16CResourceManager13createMonsterEPKwib")
extern "C" void* resourceNew3(void*,const wchar_t*,int,bool) __asm__("_ZN16CResourceManager13createMonsterEPKwib");
TL_ORIGINAL(void*,resourceOld4,(void*,const wchar_t*,bool),"_ZN16CResourceManager12createPlayerEPKwb")
extern "C" void* resourceNew4(void*,const wchar_t*,bool) __asm__("_ZN16CResourceManager12createPlayerEPKwb");
TL_ORIGINAL(void*,resourceOld5,(void*,long long,bool,bool,bool),"_ZN16CResourceManager10createItemExbbb")
extern "C" void* resourceNew5(void*,long long,bool,bool,bool) __asm__("_ZN16CResourceManager10createItemExbbb");
TL_ORIGINAL(void*,resourceOld6,(void*,const wchar_t*,bool,bool),"_ZN16CResourceManager10createItemEPKwbb")
extern "C" void* resourceNew6(void*,const wchar_t*,bool,bool) __asm__("_ZN16CResourceManager10createItemEPKwbb");
TL_ORIGINAL(void*,resourceOld7,(void*,const wchar_t*,bool,bool),"_ZN16CResourceManager15createEquipmentEPKwbb")
extern "C" void* resourceNew7(void*,const wchar_t*,bool,bool) __asm__("_ZN16CResourceManager15createEquipmentEPKwbb");
TL_ORIGINAL(void,resourceOld8,(void*,void*),"_ZN16CResourceManagerC2EPN4Ogre12SceneManagerE")
extern "C" void resourceNew8(void*,void*) __asm__("_ZN16CResourceManagerC2EPN4Ogre12SceneManagerE");
TL_ORIGINAL(void*,resourceOld9,(void*,long long,int,bool,bool),"_ZN16CResourceManager10createUnitExibb")
extern "C" void* resourceNew9(void*,long long,int,bool,bool) __asm__("_ZN16CResourceManager10createUnitExibb");
TL_ORIGINAL(void,resourceOld10,(void*,const std::wstring&,TArrayList<void*>&,unsigned,void*,void*,int,int),"_ZN16CResourceManager23createUnitsBySpawnClassERKSbIwSt11char_traitsIwESaIwEER10TArrayListIP9CBaseUnitEjP10CCharacterSC_ii")
extern "C" void resourceNew10(void*,const std::wstring&,TArrayList<void*>&,unsigned,void*,void*,int,int) __asm__("_ZN16CResourceManager23createUnitsBySpawnClassERKSbIwSt11char_traitsIwESaIwEER10TArrayListIP9CBaseUnitEjP10CCharacterSC_ii");
TL_FUNCTION(resMasterTarget,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(resRollTarget,"_ZN19CEffectGroupManager26rollAndCreateRandomAffixesEjjjR10TArrayListIP6CAffixE")
TL_FUNCTION(resAffixTarget,"_ZN9CBaseUnit8addAffixEP6CAffixjPS_f")
TL_FUNCTION(resGraphManagerTarget,"_ZN13CGraphManager12getSingletonEv")
TL_FUNCTION(resGraphTarget,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(resListTarget,"_ZN17CUnitResourceList12getSingletonEv")
TL_FUNCTION(resGuidTarget,"_ZN17CUnitResourceList18getDataGroupByGuidEx")
TL_FUNCTION(resNameTarget,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(resMonsterCtorTarget,"_ZN8CMonsterC1EP16CResourceManageri")
TL_FUNCTION(resPlayerCtorTarget,"_ZN7CPlayerC1EP16CResourceManager")
TL_FUNCTION(resNewItemTarget,"_ZN16CResourceManager13createNewItemEP10CDataGroup")
TL_FUNCTION(resEnchantTarget,"_ZN10CEquipment7enchantEb")
TL_FUNCTION(resCreateItemTarget,"_ZN16CResourceManager10createItemEPKwbb")
TL_FUNCTION(resCreateItemGuidTarget,"_ZN16CResourceManager10createItemExbbb")
TL_FUNCTION(resCreateMonsterTarget,"_ZN16CResourceManager13createMonsterExib")
TL_FUNCTION(resParamTarget,"_ZN14CCmdLineParser14GetStringParamERKSbIwSt11char_traitsIwESaIwEES3_")
TL_FUNCTION(resValueTarget,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEj")
TL_FUNCTION(resSpawnTarget,"_ZN16CResourceManager19getSpawnClassByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(resSpawnUnitsTarget,"_ZN16CResourceManager23createUnitsBySpawnClassEP11CSpawnClassR10TArrayListIP9CBaseUnitEjP10CCharacterS8_ii")
extern "C" void* resEquipmentTable[] __asm__("_ZTV10CEquipment");
extern "C" void* resItemTable[] __asm__("_ZTV5CItem");
namespace {
using namespace smallmass;
void* manager;void* masterObject;void* dataObject;void* unitObject;void* token;void* levelObject;void* clientObject;void* parserObject;void** unitTable;unsigned calls;void* allocated;
void record(unsigned tag,void* p){event(tag,p);++calls;}
void* master(){record(1,masterObject);return input->op==8 && input->index%7==0?0:masterObject;}
void* singleton(){record(2,token);return token;}
void* graph(void* p,const std::wstring& name){record(3,p);text(name);return input->index&8?token:0;}
void roll(void* p,unsigned type,unsigned level,unsigned count,TArrayList<void*>& list){record(4,p);number(type);number(level);number(count);number(list.size());for(unsigned i=0;i<input->index%5;++i)list.add(i&1?token:unitObject);}
void affix(void* p,void* a,unsigned level,void* owner,float time){record(5,p);pointer(a);number(level);pointer(owner);floating(time);}
void* guid(void* p,long long value){record(6,p);output->add(&value,8);return input->index%7?dataObject:0;}
void* name(void* p,const std::wstring& category,const std::wstring& value){record(7,p);text(category);text(value);return input->index%7?dataObject:0;}
void initialize(void* p,void* data,bool flag){record(8,p);pointer(data);number(flag);if(input->op==5||input->op==6)number(field<bool>(p,0x20a));}
void monsterCtor(void* p,void* r,int level){record(9,p);pointer(r);number(level);field<void*>(p,0)=unitTable;allocated=p;}
void playerCtor(void* p,void* r){record(10,p);pointer(r);field<void*>(p,0)=unitTable;allocated=p;}
void* newItem(void* p,void* data){record(11,p);pointer(data);return input->index%5?unitObject:0;}
void enchant(void* p,bool flag){record(12,p);number(flag);}
void destroy(void* p){record(13,p);}
void* createItem(void* p,const wchar_t* n,bool a,bool b){record(14,p);text(std::wstring(n));number(a);number(b);return input->index%5?unitObject:0;}
void* createItemGuid(void* p,long long id,bool a,bool b,bool c){record(15,p);output->add(&id,8);number(a);number(b);number(c);return input->index%5?unitObject:0;}
void* createMonster(void* p,long long id,int level,bool flag){record(16,p);output->add(&id,8);number(level);number(flag);return input->index%5?unitObject:0;}
std::wstring param(void* p,const std::wstring& key,std::wstring defaultValue){record(17,p);text(key);text(defaultValue);return input->index&8?L"COMPRESSED":L"";}
unsigned value(void* p,const std::wstring& key,unsigned fallback){record(18,p);text(key);number(fallback);static unsigned groups[]={~0u,0,1,2,3,9};return groups[(input->index/2)%6];}
void setLevel(void* p,unsigned level){record(19,p);number(level);}
void* spawn(void* p,const std::wstring& n){record(20,p);text(n);return input->index%5?token:0;}
void spawnUnits(void* p,void* s,TArrayList<void*>& units,unsigned count,void* first,void* second,int level,int flags){record(21,p);pointer(s);number(units.size());number(count);pointer(first);pointer(second);number(level);number(flags);if(input->index&16)units.add(unitObject);}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;allocated=0;autotest::g_arenaUsed=0;manager=object(0x48);masterObject=object(0x190);dataObject=object(0x30);unitObject=object(0x1148);token=object(0x20);levelObject=object(0x1b0);clientObject=object(0x3900);parserObject=object(0x148);void* settings=object(0x148);field<void*>(settings,0x140)=parserObject;field<void*>(masterObject,0x90)=c.index&4?settings:0;field<void*>(masterObject,0xc8)=token;field<void*>(masterObject,0x80)=dataObject;field<void*>(masterObject,0x58)=token;field<void*>(manager,0x18)=c.index&2?levelObject:0;field<int>(levelObject,0x1a8)=int(c.index)-17;
 void** raw=static_cast<void**>(object(0x328));std::memcpy(raw,c.index&16?resEquipmentTable:resItemTable,0x328);unitTable=raw+2;unitTable[1]=reinterpret_cast<void*>(&destroy);unitTable[0x1f0/8]=reinterpret_cast<void*>(&initialize);unitTable[0x278/8]=reinterpret_cast<void*>(&setLevel);field<void*>(unitObject,0)=unitTable;field<unsigned>(unitObject,0x1ac)=c.index*17;
 void* clients[2]={c.index%3?clientObject:0,token};list(manager,0x28,clients,c.index&1?2:0,2);field<int>(clientObject,0x38ec)=int((c.index/2)%7)-1;
 detour::Set d;TL_REDIRECT(d,resMasterTarget,&master);TL_REDIRECT(d,resRollTarget,&roll);TL_REDIRECT(d,resAffixTarget,&affix);TL_REDIRECT(d,resGraphManagerTarget,&singleton);TL_REDIRECT(d,resGraphTarget,&graph);TL_REDIRECT(d,resListTarget,&singleton);TL_REDIRECT(d,resGuidTarget,&guid);TL_REDIRECT(d,resNameTarget,&name);TL_REDIRECT(d,resMonsterCtorTarget,&monsterCtor);TL_REDIRECT(d,resPlayerCtorTarget,&playerCtor);TL_REDIRECT(d,resNewItemTarget,&newItem);TL_REDIRECT(d,resEnchantTarget,&enchant);TL_REDIRECT(d,resParamTarget,&param);TL_REDIRECT(d,resValueTarget,&value);TL_REDIRECT(d,resSpawnTarget,&spawn);TL_REDIRECT(d,resSpawnUnitsTarget,&spawnUnits);
 if(c.op==7)TL_REDIRECT(d,resCreateItemTarget,&createItem);
 if(c.op==9){TL_REDIRECT(d,resCreateItemGuidTarget,&createItemGuid);TL_REDIRECT(d,resCreateMonsterTarget,&createMonster);}
 if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 long long id=c.index%11?0x123456780000LL+c.index:-1;int level=int(c.index%5)-2;bool a=c.index&1,b=c.index&2,e=c.index&4;const wchar_t* unitName=c.index&8?L"NAME/ЮНИТ":L"";void* result=0;
 if(c.op==0){typedef void(*F)(void*,void*,unsigned,unsigned);F fn=ours?resourceNew0:resourceOld0;if(!autotest::beginInvocation(out,fn))return;fn(manager,c.index&2?unitObject:0,c.index*3,c.index%7);out.callCompleted=1;}
 else if(c.op==1){typedef void*(*F)(void*);F fn=ours?resourceNew1:resourceOld1;if(!autotest::beginInvocation(out,fn))return;result=fn(manager);out.callCompleted=1;}
 else if(c.op==2){typedef void*(*F)(void*,long long,int,bool);F fn=ours?resourceNew2:resourceOld2;if(!autotest::beginInvocation(out,fn))return;result=fn(manager,id,level,a);out.callCompleted=1;}
 else if(c.op==3){typedef void*(*F)(void*,const wchar_t*,int,bool);F fn=ours?resourceNew3:resourceOld3;if(!autotest::beginInvocation(out,fn))return;result=fn(manager,unitName,level,a);out.callCompleted=1;}
 else if(c.op==4){typedef void*(*F)(void*,const wchar_t*,bool);F fn=ours?resourceNew4:resourceOld4;if(!autotest::beginInvocation(out,fn))return;result=fn(manager,unitName,a);out.callCompleted=1;}
 else if(c.op==5){typedef void*(*F)(void*,long long,bool,bool,bool);F fn=ours?resourceNew5:resourceOld5;if(!autotest::beginInvocation(out,fn))return;result=fn(manager,id,a,b,e);out.callCompleted=1;}
 else if(c.op==6||c.op==7){typedef void*(*F)(void*,const wchar_t*,bool,bool);F fn=c.op==6?(ours?resourceNew6:resourceOld6):(ours?resourceNew7:resourceOld7);if(!autotest::beginInvocation(out,fn))return;result=fn(manager,unitName,a,b);out.callCompleted=1;}
 else if(c.op==8){std::memset(manager,0xa5,0x48);typedef void(*F)(void*,void*);F fn=ours?resourceNew8:resourceOld8;if(!autotest::beginInvocation(out,fn))return;fn(manager,c.index&2?levelObject:0);out.callCompleted=1;pointer(field<void*>(manager,0x10));pointer(field<void*>(manager,0x18));pointer(field<void*>(manager,0x20));number(field<unsigned>(manager,0x30));number(field<unsigned>(manager,0x34));number(field<unsigned>(manager,0x38));out.add(static_cast<char*>(manager)+0x40,4);}
 else if(c.op==9){typedef void*(*F)(void*,long long,int,bool,bool);F fn=ours?resourceNew9:resourceOld9;if(!autotest::beginInvocation(out,fn))return;result=fn(manager,id,level,a,e);out.callCompleted=1;}
 else{TArrayList<void*> units(3);units.add(unitObject);units.add(token);std::wstring n=unitName;typedef void(*F)(void*,const std::wstring&,TArrayList<void*>&,unsigned,void*,void*,int,int);F fn=ours?resourceNew10:resourceOld10;if(!autotest::beginInvocation(out,fn))return;fn(manager,n,units,c.index%5,unitObject,token,level,int(c.index)-9);out.callCompleted=1;number(units.size());for(unsigned i=0;i<units.size();++i)pointer(units[i]);}
 number(result!=0);if(c.op==5||c.op==6)number(field<bool>(unitObject,0x20a));number(calls);
}
}
TL_TEST(advance_runtime_resource_affix){return smallmass::run(host,0,"advance_runtime_resource_affix",(uintptr_t)resourceOld0,execute,84);}
TL_TEST(advance_runtime_resource_graph){return smallmass::run(host,1,"advance_runtime_resource_graph",(uintptr_t)resourceOld1,execute,84);}
TL_TEST(advance_runtime_resource_monster_guid){return smallmass::run(host,2,"advance_runtime_resource_monster_guid",(uintptr_t)resourceOld2,execute,84);}
TL_TEST(advance_runtime_resource_monster_name){return smallmass::run(host,3,"advance_runtime_resource_monster_name",(uintptr_t)resourceOld3,execute,84);}
TL_TEST(advance_runtime_resource_player){return smallmass::run(host,4,"advance_runtime_resource_player",(uintptr_t)resourceOld4,execute,84);}
TL_TEST(advance_runtime_resource_item_guid){return smallmass::run(host,5,"advance_runtime_resource_item_guid",(uintptr_t)resourceOld5,execute,84);}
TL_TEST(advance_runtime_resource_item_name){return smallmass::run(host,6,"advance_runtime_resource_item_name",(uintptr_t)resourceOld6,execute,84);}
TL_TEST(advance_runtime_resource_equipment){return smallmass::run(host,7,"advance_runtime_resource_equipment",(uintptr_t)resourceOld7,execute,84);}
TL_TEST(advance_runtime_resource_ctor){return smallmass::run(host,8,"advance_runtime_resource_ctor",(uintptr_t)resourceOld8,execute,84);}
TL_TEST(advance_runtime_resource_unit_guid){return smallmass::run(host,9,"advance_runtime_resource_unit_guid",(uintptr_t)resourceOld9,execute,84);}
TL_TEST(advance_runtime_resource_spawn_name){return smallmass::run(host,10,"advance_runtime_resource_spawn_name",(uintptr_t)resourceOld10,execute,84);}
