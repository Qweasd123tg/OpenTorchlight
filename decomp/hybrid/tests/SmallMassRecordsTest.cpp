#include "SmallMassCompare.h"
#include "DungeonTracker.h"
#include <vector>
#include <cstdio>
TL_ORIGINAL(void, original0, (void*,std::wstring,int), "_ZN10CCharacter10learnSpellESbIwSt11char_traitsIwESaIwEEi")
extern "C" void candidate0(void*,std::wstring,int) __asm__("_ZN10CCharacter10learnSpellESbIwSt11char_traitsIwESaIwEEi");
TL_ORIGINAL(void, original1, (void*,const std::string&,bool,float,float), "_ZN10CCharacter18setAIPlayAnimationERKSsbff")
extern "C" void candidate1(void*,const std::string&,bool,float,float) __asm__("_ZN10CCharacter18setAIPlayAnimationERKSsbff");
TL_ORIGINAL(void, original2, (void*,std::wstring), "_ZN10CCharacter9removePetESbIwSt11char_traitsIwESaIwEE")
extern "C" void candidate2(void*,std::wstring) __asm__("_ZN10CCharacter9removePetESbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void, original3, (void*,float,void*), "_ZN10CCharacter10spawningAIEfR6CLevel")
extern "C" void candidate3(void*,float,void*) __asm__("_ZN10CCharacter10spawningAIEfR6CLevel");
TL_ORIGINAL(void, original4, (void*,const std::wstring&), "_ZN10CCharacter21setPathToFollowByNameERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void candidate4(void*,const std::wstring&) __asm__("_ZN10CCharacter21setPathToFollowByNameERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void, original5, (void*), "_ZN7CPlayer14firstTimeSetupEv")
extern "C" void candidate5(void*) __asm__("_ZN7CPlayer14firstTimeSetupEv");
TL_ORIGINAL(void, original6, (void*), "_ZN7CPlayer15resetStatPointsEv")
extern "C" void candidate6(void*) __asm__("_ZN7CPlayer15resetStatPointsEv");
TL_ORIGINAL(void, original7, (void*), "_ZN7CPlayer11resetSkillsEv")
extern "C" void candidate7(void*) __asm__("_ZN7CPlayer11resetSkillsEv");
TL_ORIGINAL(void, original8, (void*,FILE*,unsigned), "_ZN15CDungeonTracker4loadEP8_IO_FILEj")
extern "C" void candidate8(void*,FILE*,unsigned) __asm__("_ZN15CDungeonTracker4loadEP8_IO_FILEj");
TL_FUNCTION(dep_addSkill, "_ZN9CBaseUnit14addSkillByNameERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(dep_setLevel, "_ZN13CSkillManager13setSkillLevelEP6CSkillj")
TL_FUNCTION(dep_animationIndex, "_ZNK13CGenericModel17getAnimationIndexERKSs")
TL_FUNCTION(dep_length, "_ZNK13CGenericModel25getAnimationLengthSecondsEi")
TL_FUNCTION(dep_blend, "_ZN13CGenericModel14blendAnimationEjbfff")
TL_FUNCTION(dep_play, "_ZN13CGenericModel13playAnimationEjbff")
TL_FUNCTION(dep_queue, "_ZN13CGenericModel19queueBlendAnimationERKSsbff")
TL_FUNCTION(dep_removePet, "_ZN10CCharacter9removePetEPS_")
TL_FUNCTION(dep_getText, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEPKw")
TL_FUNCTION(dep_getBool, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(dep_getSigned, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(dep_getUnsigned, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEj")
TL_FUNCTION(dep_playing, "_ZNK13CGenericModel25animationPlayingSubstringERKSs")
TL_FUNCTION(dep_behind, "_ZN10CCharacter15setRenderBehindEb")
TL_FUNCTION(dep_paths, "_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_addSafe, "_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(dep_removeSafe, "_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(dep_createEquipment, "_ZN16CResourceManager15createEquipmentEPKwbb")
TL_FUNCTION(dep_pickup, "_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(dep_ui, "_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(dep_tip, "_ZN7CGameUI8queueTipE11EContextTip")
TL_FUNCTION(dep_points, "_ZN13CSkillManager14getSkillPointsEv")
TL_FUNCTION(dep_stopAll, "_ZN13CSkillManager13stopAllSkillsEbbb")
TL_FUNCTION(dep_resetLevels, "_ZN13CSkillManager16resetSkillLevelsEv")
TL_FUNCTION(dep_groups, "_ZN10CDataGroup25GetDataGroupsMatchingNameERKSbIwSt11char_traitsIwESaIwEEPSt6vectorIPS_SaIS7_EE")
TL_FUNCTION(dep_levelName, "_ZN13CSkillManager13setSkillLevelERKSbIwSt11char_traitsIwESaIwEEj")
extern "C" char dep_logSingleton[] __asm__("_ZN4Ogre10LogManager12getSingletonEv");
extern "C" char dep_log[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");

namespace {
using namespace smallmass;
void* self;void* skill;void* uiObject;void* logger;void* pathsList;void* groupObjects[3];void* pets[4];void* pathObjects[3];unsigned created,propertyCalls;std::wstring returnedText;
std::vector<std::wstring*> strings;
std::wstring& makeText(void* p,unsigned off,const wchar_t* value) { std::wstring* s=new(static_cast<char*>(p)+off)std::wstring(value);strings.push_back(s);return *s; }
void* addSkill(void* p,const std::wstring& name,bool flag) { event(1,p);text(name);number(flag);return input->index%3?skill:NULL; }
void setLevel(void* p,void* s,unsigned level) { event(2,p);pointer(s);number(level); }
int animationIndex(void* p,const std::string& name) { event(3,p);text(name);return input->index%5==0?-1:input->index%3+7; }
float length(void* p,int animation) { event(4,p);number(animation);return input->index%7==0?bits(0x7fc01234):input->index%3==0?0:1.25f; }
void blend(void* p,int animation,bool loop,float fade,float speed,float end) { event(5,p);number(animation);number(loop);floating(fade);floating(speed);floating(end); }
void play(void* p,int animation,bool loop,float speed,float end) { event(6,p);number(animation);number(loop);floating(speed);floating(end); }
void queue(void* p,const std::string& name,bool loop,float fade,float speed) { event(7,p);text(name);number(loop);floating(fade);floating(speed); }
void removePet(void* p,void* pet) { event(8,p);pointer(pet);std::vector<void*>& all=field<std::vector<void*> >(p,0x648);for(unsigned i=0;i<all.size();++i)if(all[i]==pet){all.erase(all.begin()+i);break;} }
void die(void* p,void* source,void* target,float amount,bool flag) { event(9,p);pointer(source);pointer(target);floating(amount);number(flag); }
const std::wstring& getText(void* p,const std::wstring& name,const wchar_t* fallback) { event(10,p);text(name);text(std::wstring(fallback));const wchar_t* values[]={L"",L"spawn",L"IceSkill",L"same"};returnedText=values[(input->index+field<unsigned>(p,8))%4];return returnedText; }
bool getBool(void* p,const std::wstring& name,bool fallback) { event(11,p);text(name);number(fallback);return input->index&2; }
int getSigned(void* p,const std::wstring& name,int fallback) { event(12,p);text(name);number(fallback);return int(input->index%31)-5+int(++propertyCalls); }
unsigned getUnsigned(void* p,const std::wstring& name,unsigned fallback) { event(13,p);text(name);number(fallback);return (input->index+field<unsigned>(p,8))%7; }
bool playing(void* p,const std::string& name) { event(14,p);text(name);return input->index&1; }
void behind(void* p,bool flag) { event(15,p);number(flag); }
void* paths(void* p,const std::wstring& name) { event(16,p);text(name);return input->index%5==0?NULL:pathsList; }
unsigned addSafe(void* p,void* reference) { event(17,p);pointer(reference);return 81+input->index; }
void removeSafe(void* p,void* reference,unsigned index) { event(18,p);pointer(reference);number(index); }
void* createEquipment(void* p,const wchar_t* name,bool a,bool b) { event(19,p);text(std::wstring(name));number(a);number(b);++created;return (input->index+created)%3==0?NULL:skill; }
void* pickup(void* p,void* equipment,bool flag) { event(20,p);pointer(equipment);number(flag);return equipment; }
void* ui(void* p) { event(21,p);return uiObject; }
void tip(void* p,int tip) { event(22,p);number(tip); }
int points(void* p) { event(23,p);return int(input->index%19)-3; }
void stopAll(void* p,bool a,bool b,bool c) { event(24,p);number(a);number(b);number(c); }
void resetLevels(void* p) { event(25,p); }
unsigned groups(void* p,const std::wstring& name,std::vector<void*>* result) { event(26,p);text(name);unsigned n=input->index%4;for(unsigned i=0;i<n;++i)result->push_back(groupObjects[i]);return n; }
void levelName(void* p,const std::wstring& name,unsigned level) { event(27,p);text(name);number(level); }
void state(void* p,int state) { event(28,p);number(state);field<int>(p,0x330)=state; }
void* logSingleton() { number(29);return logger; }
void log(void* p,const std::string& message,int level,bool mask) { event(30,p);text(message);number(level);number(mask); }
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;created=propertyCalls=0;strings.clear();
 self=object(0xa40);skill=object(0x360);uiObject=object(16);logger=object(16);
 field<void*>(self,0x200)=c.index%7==0&&c.op==1?NULL:object(0x258);field<void*>(self,0x1c8)=c.index%5==0&&c.op==7?NULL:object(0x98);
 field<void*>(self,0x1b0)=object(24);field<void*>(self,0x68)=object(0x28);field<void*>(self,0x490)=c.index%5==0?NULL:object(0x90);
 field<void*>(self,0x340)=c.index&2?skill:NULL;field<int>(self,0x45c)=78;field<int>(self,0x460)=31;
 void** table=static_cast<void**>(object(0x410));table[0x348/8]=reinterpret_cast<void*>(&state);table[0x330/8]=reinterpret_cast<void*>(&die);field<void*>(self,0)=table;
 for(unsigned i=0;i<4;++i) {makeText(self,0x3c8+i*8,i<c.index%5?L"existing":L"");field<int>(self,0x3e8+i*4)=11+i;}
 makeText(self,0x760,L"old path");field<void*>(self,0x48)=c.index%7==0?NULL:object(16);
 std::vector<void*>& followers=*new(static_cast<char*>(self)+0x648)std::vector<void*>;
 for(unsigned i=0;i<4;++i){pets[i]=object(0x778);field<void*>(pets[i],0)=table;makeText(pets[i],0x40,i%2?L"PeT":L"wolf");if(i<c.index%5)followers.push_back(pets[i]);}
 pathsList=object(24);void** pathData=static_cast<void**>(object(24));
 for(unsigned i=0;i<3;++i){pathObjects[i]=object(0x198);makeText(pathObjects[i],0x188,i==0?L"path":i==1?L"Path":L"duplicate");pathData[i]=pathObjects[i];groupObjects[i]=object(24);field<unsigned>(groupObjects[i],8)=i;}
 list(pathsList,0,pathData,c.index%4,c.index%7==0?1:3);field<void*>(self,0x750)=c.index%3?pathObjects[0]:NULL;field<unsigned>(self,0x758)=21;
 detour::Set patches;
 TL_REDIRECT(patches,dep_addSkill,&addSkill);
 TL_REDIRECT(patches,dep_setLevel,&setLevel);
 TL_REDIRECT(patches,dep_animationIndex,&animationIndex);
 TL_REDIRECT(patches,dep_length,&length);
 TL_REDIRECT(patches,dep_blend,&blend);
 TL_REDIRECT(patches,dep_play,&play);
 TL_REDIRECT(patches,dep_queue,&queue);
 TL_REDIRECT(patches,dep_removePet,&removePet);
 TL_REDIRECT(patches,dep_getText,&getText);
 TL_REDIRECT(patches,dep_getBool,&getBool);
 TL_REDIRECT(patches,dep_getSigned,&getSigned);
 TL_REDIRECT(patches,dep_getUnsigned,&getUnsigned);
 TL_REDIRECT(patches,dep_playing,&playing);
 TL_REDIRECT(patches,dep_behind,&behind);
 TL_REDIRECT(patches,dep_paths,&paths);
 TL_REDIRECT(patches,dep_addSafe,&addSafe);
 TL_REDIRECT(patches,dep_removeSafe,&removeSafe);
 TL_REDIRECT(patches,dep_createEquipment,&createEquipment);
 TL_REDIRECT(patches,dep_pickup,&pickup);
 TL_REDIRECT(patches,dep_ui,&ui);
 TL_REDIRECT(patches,dep_tip,&tip);
 TL_REDIRECT(patches,dep_points,&points);
 TL_REDIRECT(patches,dep_stopAll,&stopAll);
 TL_REDIRECT(patches,dep_resetLevels,&resetLevels);
 TL_REDIRECT(patches,dep_groups,&groups);
 TL_REDIRECT(patches,dep_levelName,&levelName);

 patches.redirect(dep_logSingleton,dep_logSingleton,&logSingleton);patches.redirect(dep_log,dep_log,&log);if(patches.failed())_exit(41);
 const wchar_t* names[]={L"",L"PeT",L"wolf",L"path",L"Path",L"missing"};std::wstring name=names[c.index%6];
 switch(c.op) {
 case 0:{void(*fn)(void*,std::wstring,int)=ours?candidate0:original0;if(!autotest::beginInvocation(out,fn))return;fn(self,name,int(c.index%9)-2);out.callCompleted=1;break;}
 case 1:{const char* names[]={"","idle","IDLE","attack","walk"};std::string animation=names[c.index%5];float fade=c.index%4==0?0:c.index%4==1?0.2f:c.index%4==2?-1:bits(0x7fc01234);void(*fn)(void*,const std::string&,bool,float,float)=ours?candidate1:original1;if(!autotest::beginInvocation(out,fn))return;fn(self,animation,c.index&1,fade,0.5f);out.callCompleted=1;break;}
 case 2:{void(*fn)(void*,std::wstring)=ours?candidate2:original2;if(!autotest::beginInvocation(out,fn))return;fn(self,name);out.callCompleted=1;break;}
 case 3:autotest::invoke(out,ours?candidate3:original3,self,0.125f,uiObject);break;
 case 4:{void(*fn)(void*,const std::wstring&)=ours?candidate4:original4;if(!autotest::beginInvocation(out,fn))return;fn(self,name);out.callCompleted=1;break;}
 case 5:autotest::invoke(out,ours?candidate5:original5,self);break;
 case 6:autotest::invoke(out,ours?candidate6:original6,self);break;
 case 7:autotest::invoke(out,ours?candidate7:original7,self);break;
 case 8:{
  CDungeonTracker tracker;tracker.m_name=L"before";tracker.m_rank=-31;tracker.m_value8=-41;tracker.m_value10=-51;for(unsigned i=0;i<c.index%3;++i)tracker.m_levels.push_back(91+i);
  FILE* file=tmpfile();if(!file)_exit(43);unsigned short length=c.index%4;fwrite(&length,2,1,file);const unsigned short chars[]={0x0041,0x0416,0x0030};fwrite(chars,2,length,file);
  unsigned version=c.index%9;int values[]={11,-21,33};fwrite(values,4,2,file);if(version>2){fwrite(values+2,4,1,file);if(version>5){unsigned count=c.index%5;fwrite(&count,4,1,file);for(unsigned i=0;i<count;++i){int value=int(i*17)-32;fwrite(&value,4,1,file);}}}rewind(file);
  void(*fn)(void*,FILE*,unsigned)=ours?candidate8:original8;if(!autotest::beginInvocation(out,fn))return;fn(&tracker,file,version);out.callCompleted=1;text(tracker.m_name);number(tracker.m_rank);number(tracker.m_value8);number(tracker.m_value10);number(tracker.m_levels.size());for(unsigned i=0;i<tracker.m_levels.size();++i)number(tracker.m_levels[i]);number(ftell(file));fclose(file);break;
 }
 }
 number(followers.size());for(unsigned i=0;i<followers.size();++i)pointer(followers[i]);
 for(unsigned i=0;i<strings.size();++i){text(*strings[i]);std::memset(strings[i],0,sizeof(std::wstring));}
 std::memset(&followers,0,sizeof(followers));number(created);number(propertyCalls);out.add(autotest::g_arena,autotest::g_arenaUsed);
}
}
TL_TEST(smallmass2_record_learn) { return smallmass::run(host,0,"smallmass2_record_learn",(uint64_t)(uintptr_t)original0,execute,96); }
TL_TEST(smallmass2_record_animation) { return smallmass::run(host,1,"smallmass2_record_animation",(uint64_t)(uintptr_t)original1,execute,96); }
TL_TEST(smallmass2_record_remove_pet) { return smallmass::run(host,2,"smallmass2_record_remove_pet",(uint64_t)(uintptr_t)original2,execute,96); }
TL_TEST(smallmass2_record_spawning) { return smallmass::run(host,3,"smallmass2_record_spawning",(uint64_t)(uintptr_t)original3,execute,96); }
TL_TEST(smallmass2_record_path) { return smallmass::run(host,4,"smallmass2_record_path",(uint64_t)(uintptr_t)original4,execute,96); }
TL_TEST(smallmass2_record_first_setup) { return smallmass::run(host,5,"smallmass2_record_first_setup",(uint64_t)(uintptr_t)original5,execute,96); }
TL_TEST(smallmass2_record_reset_stats) { return smallmass::run(host,6,"smallmass2_record_reset_stats",(uint64_t)(uintptr_t)original6,execute,96); }
TL_TEST(smallmass2_record_reset_skills) { return smallmass::run(host,7,"smallmass2_record_reset_skills",(uint64_t)(uintptr_t)original7,execute,96); }
TL_TEST(smallmass2_record_dungeon_load) { return smallmass::run(host,8,"smallmass2_record_dungeon_load",(uint64_t)(uintptr_t)original8,execute,96); }
