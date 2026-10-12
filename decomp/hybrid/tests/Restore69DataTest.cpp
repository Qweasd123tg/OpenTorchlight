#include "SmallMassCompare.h"
TL_ORIGINAL(int, original0, (void*), "_ZN10CCharacter22getMaximumPetInstancesEv")
extern "C" int candidate0(void*) __asm__("_ZN10CCharacter22getMaximumPetInstancesEv");
TL_ORIGINAL(std::wstring, original1, (void*), "_ZN10CCharacter14getDescriptionEv")
extern "C" std::wstring candidate1(void*) __asm__("_ZN10CCharacter14getDescriptionEv");
TL_ORIGINAL(bool, original2, (void*), "_ZN10CCharacter10diesOnWarpEv")
extern "C" bool candidate2(void*) __asm__("_ZN10CCharacter10diesOnWarpEv");
TL_ORIGINAL(bool, original3, (void*), "_ZN10CCharacter17getSpawnInvisibleEv")
extern "C" bool candidate3(void*) __asm__("_ZN10CCharacter17getSpawnInvisibleEv");
TL_ORIGINAL(bool, original4, (void*), "_ZN10CCharacter17getDestroyOnDeathEv")
extern "C" bool candidate4(void*) __asm__("_ZN10CCharacter17getDestroyOnDeathEv");
TL_ORIGINAL(bool, original5, (void*), "_ZN10CCharacter16attachesToMasterEv")
extern "C" bool candidate5(void*) __asm__("_ZN10CCharacter16attachesToMasterEv");
TL_ORIGINAL(std::wstring, original6, (void*), "_ZN10CCharacter12getMimicNameEv")
extern "C" std::wstring candidate6(void*) __asm__("_ZN10CCharacter12getMimicNameEv");
TL_ORIGINAL(int, original7, (void*), "_ZN10CCharacter21getDefaultMerchantTabEv")
extern "C" int candidate7(void*) __asm__("_ZN10CCharacter21getDefaultMerchantTabEv");
TL_ORIGINAL(std::wstring, original8, (void*), "_ZN10CCharacter17getIntroCinematicEv")
extern "C" std::wstring candidate8(void*) __asm__("_ZN10CCharacter17getIntroCinematicEv");
TL_ORIGINAL(float, original9, (void*), "_ZN10CCharacter31playerLevelForMerchantInventoryEv")
extern "C" float candidate9(void*) __asm__("_ZN10CCharacter31playerLevelForMerchantInventoryEv");
TL_ORIGINAL(std::wstring, original10, (void*,int), "_ZN10CCharacter15getSkillTabNameEi")
extern "C" std::wstring candidate10(void*,int) __asm__("_ZN10CCharacter15getSkillTabNameEi");
TL_ORIGINAL(int, original11, (void*), "_ZN10CCharacter14baseArmorBonusEv")
extern "C" int candidate11(void*) __asm__("_ZN10CCharacter14baseArmorBonusEv");
TL_ORIGINAL(std::wstring, original12, (void*), "_ZN7CPlayer18getPlayerClassNameEv")
extern "C" std::wstring candidate12(void*) __asm__("_ZN7CPlayer18getPlayerClassNameEv");
TL_ORIGINAL(void, original13, (void*), "_ZN7CPlayer21calculateNaturalArmorEv")
extern "C" void candidate13(void*) __asm__("_ZN7CPlayer21calculateNaturalArmorEv");
TL_ORIGINAL(void, original14, (void*,float,void*), "_ZN10CCharacter11interruptAIEfR6CLevel")
extern "C" void candidate14(void*,float,void*) __asm__("_ZN10CCharacter11interruptAIEfR6CLevel");
TL_FUNCTION(dep_getInt, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(dep_getBool, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(dep_getFloat, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEf")
TL_FUNCTION(dep_getWide, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(dep_getText, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEPKw")
TL_FUNCTION(dep_graphManager, "_ZN13CGraphManager12getSingletonEv")
TL_FUNCTION(dep_graph, "_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_graphValue, "_ZNK6CGraph8getValueEfj")
TL_FUNCTION(dep_playing, "_ZNK13CGenericModel25animationPlayingSubstringERKSs")
namespace {
using namespace smallmass;
void* self;void* graphObject;void* manager;std::wstring textValue;
int getInt(void* p,const std::wstring& key,int fallback) { event(1,p);text(key);number(fallback);return input->index%5==0?fallback:int(input->index%31)-9; }
bool getBool(void* p,const std::wstring& key,bool fallback) { event(2,p);text(key);number(fallback);return input->index%3==0?fallback:bool(input->index&1); }
float getFloat(void* p,const std::wstring& key,float fallback) { event(3,p);text(key);floating(fallback);return input->index%5==0?fallback:input->index%7==0?bits(0x7fc01234):float(int(input->index%41)-13)*0.25f; }
const std::wstring& getWide(void* p,const std::wstring& key,const std::wstring& fallback) { event(4,p);text(key);text(fallback);if(input->index%5==0)textValue=fallback;return textValue; }
const std::wstring& getText(void* p,const std::wstring& key,const wchar_t* fallback) { event(5,p);text(key);text(std::wstring(fallback));if(input->index%5==0)textValue=fallback;return textValue; }
void* graphManager() { number(6);return manager; }
void* graph(void* p,const std::wstring& name) { event(7,p);text(name);return input->index%3==0?NULL:graphObject; }
float graphValue(void* p,float level,unsigned curve) { event(8,p);floating(level);number(curve);field<int>(self,0x424)+=input->index%3;return float(int(input->index%67)-11)*0.5f; }
float namedEffect(void* p,int type,float initial,const std::wstring& name) { event(9,p);number(type);floating(initial);text(name);return float(int(input->index%19)-9)*0.25f; }
bool playing(void* p,const std::string& name) { event(10,p);text(name);return input->index&1; }
void state(void* p,int value) { event(11,p);number(value);field<int>(p,0x330)=value; }
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;
 self=object(0xa70);graphObject=object(32);manager=object(32);
 field<void*>(self,0x1b0)=c.op==12&&c.index%3==0?NULL:object(32);
 field<void*>(self,0x200)=object(0x258);field<void*>(self,0x490)=object(0x100);
 field<int>(field<void*>(self,0x490),0x10)=int(c.index%41)-20;
 field<int>(self,0x424)=int(c.index%13)-5;field<unsigned>(self,0x100)=c.index%5==0?0xffffffffu:c.index%97;
 field<int>(self,0x330)=29;
 void** table=static_cast<void**>(object(0x420));table[0x258/8]=reinterpret_cast<void*>(&namedEffect);table[0x348/8]=reinterpret_cast<void*>(&state);field<void*>(self,0)=table;
 const wchar_t* values[]={L"",L"Name",L"ICE",L"1b3541",L"space here",L"lower_123"};textValue=values[c.index%6];
 detour::Set patches;
 TL_REDIRECT(patches,dep_getInt,&getInt);
 TL_REDIRECT(patches,dep_getBool,&getBool);
 TL_REDIRECT(patches,dep_getFloat,&getFloat);
 TL_REDIRECT(patches,dep_getWide,&getWide);
 TL_REDIRECT(patches,dep_getText,&getText);
 TL_REDIRECT(patches,dep_graphManager,&graphManager);
 TL_REDIRECT(patches,dep_graph,&graph);
 TL_REDIRECT(patches,dep_graphValue,&graphValue);
 TL_REDIRECT(patches,dep_playing,&playing);
 if(patches.failed())_exit(41);
 switch(c.op) {
 case 0:autotest::invoke(out,ours?candidate0:original0,self);break;
 case 1:{std::wstring(*fn)(void*)=ours?candidate1:original1;if(!autotest::beginInvocation(out,fn))return;text(fn(self));out.callCompleted=1;break;}
 case 2:autotest::invoke(out,ours?candidate2:original2,self);break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self);break;
 case 4:autotest::invoke(out,ours?candidate4:original4,self);break;
 case 5:autotest::invoke(out,ours?candidate5:original5,self);break;
 case 6:{std::wstring(*fn)(void*)=ours?candidate6:original6;if(!autotest::beginInvocation(out,fn))return;text(fn(self));out.callCompleted=1;break;}
 case 7:autotest::invoke(out,ours?candidate7:original7,self);break;
 case 8:{std::wstring(*fn)(void*)=ours?candidate8:original8;if(!autotest::beginInvocation(out,fn))return;text(fn(self));out.callCompleted=1;break;}
 case 9:autotest::invoke(out,ours?candidate9:original9,self);break;
 case 10:{std::wstring(*fn)(void*,int)=ours?candidate10:original10;if(!autotest::beginInvocation(out,fn))return;text(fn(self,int(c.index%13)-3));out.callCompleted=1;break;}
 case 11:autotest::invoke(out,ours?candidate11:original11,self);break;
 case 12:{std::wstring(*fn)(void*)=ours?candidate12:original12;if(!autotest::beginInvocation(out,fn))return;text(fn(self));out.callCompleted=1;break;}
 case 13:autotest::invoke(out,ours?candidate13:original13,self);break;
 case 14:autotest::invoke(out,ours?candidate14:original14,self,0.125f,graphObject);break;
 }
 out.add(autotest::g_arena,autotest::g_arenaUsed);
}
}
TL_TEST(restore69_831ee0) { return smallmass::run(host,0,"restore69_831ee0",(uint64_t)(uintptr_t)original0,execute,64); }
TL_TEST(restore69_8325e0) { return smallmass::run(host,1,"restore69_8325e0",(uint64_t)(uintptr_t)original1,execute,64); }
TL_TEST(restore69_8326a0) { return smallmass::run(host,2,"restore69_8326a0",(uint64_t)(uintptr_t)original2,execute,64); }
TL_TEST(restore69_832750) { return smallmass::run(host,3,"restore69_832750",(uint64_t)(uintptr_t)original3,execute,64); }
TL_TEST(restore69_832800) { return smallmass::run(host,4,"restore69_832800",(uint64_t)(uintptr_t)original4,execute,64); }
TL_TEST(restore69_8328b0) { return smallmass::run(host,5,"restore69_8328b0",(uint64_t)(uintptr_t)original5,execute,64); }
TL_TEST(restore69_834700) { return smallmass::run(host,6,"restore69_834700",(uint64_t)(uintptr_t)original6,execute,64); }
TL_TEST(restore69_8347c0) { return smallmass::run(host,7,"restore69_8347c0",(uint64_t)(uintptr_t)original7,execute,64); }
TL_TEST(restore69_834ad0) { return smallmass::run(host,8,"restore69_834ad0",(uint64_t)(uintptr_t)original8,execute,64); }
TL_TEST(restore69_834b90) { return smallmass::run(host,9,"restore69_834b90",(uint64_t)(uintptr_t)original9,execute,64); }
TL_TEST(restore69_834870) { return smallmass::run(host,10,"restore69_834870",(uint64_t)(uintptr_t)original10,execute,64); }
TL_TEST(restore69_834990) { return smallmass::run(host,11,"restore69_834990",(uint64_t)(uintptr_t)original11,execute,64); }
TL_TEST(restore69_8f52a0) { return smallmass::run(host,12,"restore69_8f52a0",(uint64_t)(uintptr_t)original12,execute,64); }
TL_TEST(restore69_8f8510) { return smallmass::run(host,13,"restore69_8f8510",(uint64_t)(uintptr_t)original13,execute,64); }
TL_TEST(restore69_82a4e0) { return smallmass::run(host,14,"restore69_82a4e0",(uint64_t)(uintptr_t)original14,execute,64); }
