#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,int), "_ZN7CPlayer10setAIStateE8EAIState")
extern "C" void candidate0(void*,int) __asm__("_ZN7CPlayer10setAIStateE8EAIState");
TL_ORIGINAL(void, original1, (void*,int,int), "_ZN7CPlayer25incrementJournalStatisticE17EJournalStatistici")
extern "C" void candidate1(void*,int,int) __asm__("_ZN7CPlayer25incrementJournalStatisticE17EJournalStatistici");
TL_ORIGINAL(void, original2, (void*,void*,const Ogre::Vector3*,float,bool), "_ZN7CPlayer3dieEP10CCharacterPKN4Ogre7Vector3Efb")
extern "C" void candidate2(void*,void*,const Ogre::Vector3*,float,bool) __asm__("_ZN7CPlayer3dieEP10CCharacterPKN4Ogre7Vector3Efb");
TL_ORIGINAL(void*, original3, (void*,std::wstring,int), "_ZN7CPlayer18getLevelSavedStateESbIwSt11char_traitsIwESaIwEEi")
extern "C" void* candidate3(void*,std::wstring,int) __asm__("_ZN7CPlayer18getLevelSavedStateESbIwSt11char_traitsIwESaIwEEi");
TL_ORIGINAL(bool, original4, (void*,std::wstring,int), "_ZN7CPlayer18hasLevelSavedStateESbIwSt11char_traitsIwESaIwEEi")
extern "C" bool candidate4(void*,std::wstring,int) __asm__("_ZN7CPlayer18hasLevelSavedStateESbIwSt11char_traitsIwESaIwEEi");
#include <vector>
TL_FUNCTION(dep_steam, "_ZN11CSteamStats12getSingletonEv")
TL_FUNCTION(dep_increment, "_ZN11CSteamStats13incrementStatE6ESTATSi")
TL_FUNCTION(dep_achievements, "_ZN13CAchievements12getSingletonEv")
TL_FUNCTION(dep_achievement, "_ZN13CAchievements14getAchievementE13EACHIEVEMENTS")
TL_FUNCTION(dep_complete, "_ZN12CAchievement13forceCompleteEv")
TL_FUNCTION(dep_baseDie, "_ZN10CCharacter3dieEPS_PKN4Ogre7Vector3Efb")
TL_FUNCTION(dep_save, "_ZN11CGameClient13saveCharacterEbb")
namespace {
using namespace smallmass;
void* self;void* stats;void* allAchievements;void* reward;void* client2;void** clients;std::vector<std::wstring*> strings;
void* steam() { number(1);return stats; }
void increment(void* p,int stat,int amount) { event(2,p);number(stat);number(amount); }
void* achievements() { number(3);return allAchievements; }
void* achievement(void* p,int id) { event(4,p);number(id);return reward; }
void complete(void* p) { event(5,p); }
void baseDie(void* p,void* killer,const Ogre::Vector3* direction,float force,bool silent) { event(6,p);pointer(killer);number(direction!=NULL);if(direction)vector(*direction);floating(force);number(silent);field<int>(p,0x330)=5;if(input->index%5==0)clients[0]=client2;if(input->index%7==0)field<bool>(p,0xa15)=!field<bool>(p,0xa15); }
void save(void* p,bool a,bool b) { event(7,p);number(a);number(b); }
void visible(void* p,bool value,bool cascade) { event(8,p);number(value);number(cascade);number(field<int>(self,0x330)); }
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;strings.clear();
 self=object(0xa70);stats=object(32);allAchievements=object(32);reward=object(32);
 const int states[]={0,32,33,34,5,6,7,31,35};field<int>(self,0x330)=states[(c.index/9)%9];
 void* node=object(32);void** table=static_cast<void**>(object(0x380));table[0x378/8]=reinterpret_cast<void*>(&visible);field<void*>(node,0)=table;field<void*>(self,0x2f0)=c.index%7==0?NULL:node;
 for(unsigned i=0;i<43;++i)field<int>(self,0x7dc+i*4)=int(c.index*13+i)-300;
 const int gold[]={0,99998,99999,100000,200000};field<int>(self,0x444)=gold[(c.index/18)%5];field<bool>(self,0xa15)=(c.index/18)&1;
 void* resources=object(0x60);void* client=object(0x3900);client2=object(0x3900);clients=static_cast<void**>(object(16));clients[0]=client;clients[1]=client2;
 list(resources,0x28,clients,1,2);field<void*>(self,0x68)=resources;field<int>(client,0x38d0)=(c.index/3)%4;
 void** records=static_cast<void**>(object(5*8));const wchar_t* names[]={L"",L"DUNGEON",L"dungeon",L"mine",L"missing"};
 for(unsigned i=0;i<5;++i){records[i]=object(0xb8);field<int>(records[i],0x10)=int(i%3)-1;std::wstring* t=new(static_cast<char*>(records[i])+0x18)std::wstring(names[(c.index/5+i)%4]);strings.push_back(t);}
 field<void*>(self,0x798)=records;field<void*>(self,0x7a0)=records+c.index%6;field<void*>(self,0x7a8)=records+5;
 detour::Set patches;
 TL_REDIRECT(patches,dep_steam,&steam);
 TL_REDIRECT(patches,dep_increment,&increment);
 TL_REDIRECT(patches,dep_achievements,&achievements);
 TL_REDIRECT(patches,dep_achievement,&achievement);
 TL_REDIRECT(patches,dep_complete,&complete);
 TL_REDIRECT(patches,dep_baseDie,&baseDie);
 TL_REDIRECT(patches,dep_save,&save);
 if(patches.failed())_exit(41);
 const int amounts[]={-100,-1,0,1,100,100000,3};int amount=amounts[(c.index/18)%7];
 Ogre::Vector3 direction(-2,4,1);
 switch(c.op) {
 case 0:autotest::invoke(out,ours?candidate0:original0,self,states[c.index%9]);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,int(c.index%18),amount);break;
 case 2:{void(*fn)(void*,void*,const Ogre::Vector3*,float,bool)=ours?candidate2:original2;if(!autotest::beginInvocation(out,fn))return;fn(self,c.index&1?reward:NULL,c.index&2?&direction:NULL,float(int(c.index%7)-2)*0.5f,c.index&4);out.callCompleted=1;break;}
 case 3:{std::wstring name=c.index%3==0?std::wstring(names[c.index%5]):*strings[c.index%5];void*(*fn)(void*,std::wstring,int)=ours?candidate3:original3;if(!autotest::beginInvocation(out,fn))return;pointer(fn(self,name,int((c.index%5)%3)-1));out.callCompleted=1;break;}
 case 4:{std::wstring name=c.index%3==0?std::wstring(names[c.index%5]):*strings[c.index%5];bool(*fn)(void*,std::wstring,int)=ours?candidate4:original4;if(!autotest::beginInvocation(out,fn))return;number(fn(self,name,int((c.index%5)%3)-1));out.callCompleted=1;break;}
 }
 for(unsigned i=0;i<strings.size();++i){text(*strings[i]);strings[i]->~basic_string();std::memset(strings[i],0,sizeof(std::wstring));}
 out.add(autotest::g_arena,autotest::g_arenaUsed);
}
}
TL_TEST(restore69_8e3ff0) { return smallmass::run(host,0,"restore69_8e3ff0",(uint64_t)(uintptr_t)original0,execute,128); }
TL_TEST(restore69_8e41c0) { return smallmass::run(host,1,"restore69_8e41c0",(uint64_t)(uintptr_t)original1,execute,252); }
TL_TEST(restore69_8e47d0) { return smallmass::run(host,2,"restore69_8e47d0",(uint64_t)(uintptr_t)original2,execute,192); }
TL_TEST(restore69_8ef600) { return smallmass::run(host,3,"restore69_8ef600",(uint64_t)(uintptr_t)original3,execute,128); }
TL_TEST(restore69_8ef6c0) { return smallmass::run(host,4,"restore69_8ef6c0",(uint64_t)(uintptr_t)original4,execute,128); }
