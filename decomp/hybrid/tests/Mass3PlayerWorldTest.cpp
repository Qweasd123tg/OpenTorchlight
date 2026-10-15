#include "TArrayList.h"
#include <vector>
#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,void*), "_ZN7CPlayer15setQuestManagerEP13CQuestManager")
extern "C" void candidate0(void*,void*) __asm__("_ZN7CPlayer15setQuestManagerEP13CQuestManager");
TL_ORIGINAL(void, original1, (void*,std::wstring,int), "_ZN7CPlayer21updateDungeonTrackingESbIwSt11char_traitsIwESaIwEEi")
extern "C" void candidate1(void*,std::wstring,int) __asm__("_ZN7CPlayer21updateDungeonTrackingESbIwSt11char_traitsIwESaIwEEi");
TL_ORIGINAL(void, original2, (void*,std::wstring,void*), "_ZN7CPlayer13openMapPortalESbIwSt11char_traitsIwESaIwEER6CLevel")
extern "C" void candidate2(void*,std::wstring,void*) __asm__("_ZN7CPlayer13openMapPortalESbIwSt11char_traitsIwESaIwEER6CLevel");
TL_ORIGINAL(void, original3, (void*,void*), "_ZN7CPlayer13createPortalsER6CLevel")
extern "C" void candidate3(void*,void*) __asm__("_ZN7CPlayer13createPortalsER6CLevel");
TL_FUNCTION(dep_setPlayer, "_ZN13CQuestManager9setPlayerEP7CPlayer")
TL_FUNCTION(dep_reset, "_ZN13CQuestManager17resetQuestManagerEb")
TL_FUNCTION(dep_group, "_ZN10CDataGroup18GetDataGroupByNameERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(dep_stringValue, "_ZN10CDataValue14GetValueStringEb")
TL_FUNCTION(dep_quest, "_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_give, "_ZN13CQuestManager9giveQuestEP6CQuestP9CBaseUnitb")
TL_FUNCTION(dep_accepted, "_ZN6CQuest16setQuestAcceptedEb")
TL_FUNCTION(dep_master, "_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(dep_getInt, "_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(dep_getString, "_ZN20CDynamicPropertyFile9GetStringEj")
TL_FUNCTION(dep_complete, "_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_completeQuest, "_ZN13CQuestManager13completeQuestEP6CQuest")
TL_FUNCTION(dep_dungeons, "_ZN15CDungeonManager12getSingletonEv")
TL_FUNCTION(dep_dungeon, "_ZN15CDungeonManager16getDungeonByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_openPosition, "_ZN6CLevel18randomOpenPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(dep_createUnit, "_ZN16CResourceManager10createUnitEPKwS1_ib")
TL_FUNCTION(dep_addItem, "_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(dep_effect, "_ZN7CEffectC1E12EEFFECT_TYPEb18EEFFECT_ACTIVATIONfffb")
TL_FUNCTION(dep_addEffect, "_ZN9CBaseUnit12addNewEffectEP7CEffect")
TL_FUNCTION(dep_icons, "_ZN6CLevel18updateAutomapIconsEv")

extern "C" void* itemTable[] __asm__("_ZTV5CItem");
extern "C" void* baseTable[] __asm__("_ZTV9CBaseUnit");
namespace {
using namespace smallmass;
void *self,*services,*settings,*quests,*questObjects[3],*dungeonObject,*unit,*effects;
std::wstring names[4];unsigned calls;
void setPlayer(void* p,void* player){event(1,p);pointer(player);}
void reset(void* p,bool clear){event(2,p);number(clear);}
void* group(void* p,const std::wstring& name,bool create){event(3,p);text(name);number(create);return input->index%7?quests:0;}
const std::wstring& stringValue(void* p,bool translate){event(4,p);number(translate);return names[field<unsigned>(p,0x20)%4];}
void* quest(void* p,const std::wstring& name){event(5,p);text(name);return name==L"MISSING"||input->index%11==0?0:questObjects[name==L"retire"?2:name==L"FIRST"?0:1];}
void give(void* p,void* quest,void* unit,bool reward){event(6,p);pointer(quest);pointer(unit);number(reward);}
void accepted(void* p,bool value){event(7,p);number(value);field<bool>(p,0x26)=value;}
void* master(){number(8);return services;}
int getInt(void* p,unsigned key){event(9,p);number(key);return int(input->index%4)-1;}
const std::wstring& getString(void* p,unsigned key){event(10,p);number(key);return names[3];}
char complete(void* p,const std::wstring& name){event(11,p);text(name);return input->index&4;}
void completeQuest(void* p,void* quest){event(12,p);pointer(quest);field<bool>(quest,0x24)=true;}
void* dungeons(){number(13);return services;}
void* dungeon(void* p,std::wstring name){event(14,p);text(name);return input->index%4?dungeonObject:0;}
Ogre::Vector3 openPosition(void* p,const Ogre::Vector3& origin,float radius,bool flag){event(15,p);vector(origin);floating(radius);number(flag);return origin+Ogre::Vector3(radius,1,-2);}
void* createUnit(void* p,const wchar_t* category,const wchar_t* name,int level,bool flag){event(16,p);text(std::wstring(category));text(std::wstring(name));number(level);number(flag);++calls;return (input->index+calls)%5==0?0:unit;}
void addItem(void* p,void* item,const Ogre::Vector3& position,bool drop){event(17,p);pointer(item);vector(position);number(drop);}
void effect(void* p,int type,bool flag,int activation,float duration,float a,float b,bool c){number(18);number(type);number(flag);number(activation);floating(duration);floating(a);floating(b);number(c);effects=p;new(static_cast<char*>(p)+0x80)std::wstring;field<bool>(p,0x33)=false;}
void addEffect(void* p,void* value){event(19,p);number(value==effects);number(field<bool>(value,0x33));text(field<std::wstring>(value,0x80));}
void icons(void* p){event(20,p);}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;calls=0;effects=0;
 self=object(0xa70);services=object(0x300);settings=object(0x100);quests=object(0x60);dungeonObject=object(0xe0);unit=object(0x228);
 field<void*>(unit,0)=(c.index&8?baseTable:itemTable)+2;
 void* data=object(0x60);void* manager=object(0xd0);void* resources=object(0x48);void* level=object(0x2f0);void* levelTemplate=object(0x100);
 for(unsigned i=0;i<3;++i)questObjects[i]=object(0x220);
 names[0]=L"first";names[1]=L"Second";names[2]=L"missing";names[3]=L"retire";
 field<void*>(self,0x68)=resources;field<void*>(self,0x1b0)=c.index%13?data:0;field<void*>(services,0x90)=settings;
 void** values=static_cast<void**>(object(5*8));const int types[]={5,8,2,5,8};
 for(unsigned i=0;i<5;++i){values[i]=object(0x38);field<int>(values[i],0x30)=types[i];field<unsigned>(values[i],0x20)=i%3;}
 list(quests,0x20,values,c.index%6,5);
 field<int>(self,0x100)=int(c.index%41)+1;field<int>(dungeonObject,0x58)=c.index%3;
 new(static_cast<char*>(self)+0xa40)TArrayList<void*>(2);TArrayList<void*>& trackers=field<TArrayList<void*> >(self,0xa40);
 unsigned trackerCount=c.index%4;
 for(unsigned i=0;i<trackerCount;++i){void* tracker=object(0x30);new(tracker)std::wstring(i==0?L"MINE":i==1?L"TOWN":L"MINE");field<int>(tracker,8)=int((c.index+i)%9)-3;field<int>(tracker,0xc)=17;field<int>(tracker,0x10)=i%2;new(static_cast<char*>(tracker)+0x18)std::vector<int>;if((c.index+i)%3==0)field<std::vector<int> >(tracker,0x18).push_back(3);trackers.add(tracker);}
 field<Ogre::Vector3>(self,0x84)=Ogre::Vector3(2,-1,8);field<Ogre::Vector3>(self,0x7c0)=Ogre::Vector3(7,2,9);field<Ogre::Vector3>(level,0x14c)=Ogre::Vector3(12,0,-5);
 const Ogre::Vector3 waypoints[]={Ogre::Vector3(-1,-1,-1),Ogre::Vector3(-1,0,-1),Ogre::Vector3(1,-1,-1),Ogre::Vector3(4,5,6)};field<Ogre::Vector3>(level,0x158)=waypoints[(c.index/3)%4];
 field<bool>(self,0x7b0)=c.index&1;field<int>(self,0x7b4)=c.index%3;field<int>(level,0x1a4)=(c.index/3)%3;
 new(static_cast<char*>(self)+0x7b8)std::wstring(c.index&2?L"MINE":L"TOWN");new(static_cast<char*>(level)+0x280)std::wstring(c.index&4?L"MINE":L"TOWN");field<void*>(level,0x1d8)=levelTemplate;field<bool>(levelTemplate,0x86)=c.index&16;
 detour::Set patches;
 TL_REDIRECT(patches,dep_setPlayer,&setPlayer);
 TL_REDIRECT(patches,dep_reset,&reset);
 TL_REDIRECT(patches,dep_group,&group);
 TL_REDIRECT(patches,dep_stringValue,&stringValue);
 TL_REDIRECT(patches,dep_quest,&quest);
 TL_REDIRECT(patches,dep_give,&give);
 TL_REDIRECT(patches,dep_accepted,&accepted);
 TL_REDIRECT(patches,dep_master,&master);
 TL_REDIRECT(patches,dep_getInt,&getInt);
 TL_REDIRECT(patches,dep_getString,&getString);
 TL_REDIRECT(patches,dep_complete,&complete);
 TL_REDIRECT(patches,dep_completeQuest,&completeQuest);
 TL_REDIRECT(patches,dep_dungeons,&dungeons);
 TL_REDIRECT(patches,dep_dungeon,&dungeon);
 TL_REDIRECT(patches,dep_openPosition,&openPosition);
 TL_REDIRECT(patches,dep_createUnit,&createUnit);
 TL_REDIRECT(patches,dep_addItem,&addItem);
 TL_REDIRECT(patches,dep_effect,&effect);
 TL_REDIRECT(patches,dep_addEffect,&addEffect);
 TL_REDIRECT(patches,dep_icons,&icons);

 if(patches.failed())_exit(41);
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,self,c.index%17?manager:0);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,std::wstring(c.index&4?L"Mine":c.index&8?L"new":L"Town"),int(c.index%13)-4);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,std::wstring(c.index&1?L"Map destination":L""),level);break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self,level);break;
 }
 pointer(field<void*>(self,0x868));number(calls);
 for(unsigned i=0;i<3;++i){number(field<bool>(questObjects[i],0x24));number(field<bool>(questObjects[i],0x26));}
 number(trackers.size());for(unsigned i=0;i<trackers.size();++i){void* tracker=trackers[i];text(field<std::wstring>(tracker,0));number(field<int>(tracker,8));number(field<int>(tracker,0xc));number(field<int>(tracker,0x10));const std::vector<int>& levels=field<std::vector<int> >(tracker,0x18);number(levels.size());for(unsigned j=0;j<levels.size();++j)number(levels[j]);}
}
}
TL_TEST(mass3_8f8260) { return smallmass::run(host,0,"mass3_8f8260",(uint64_t)(uintptr_t)original0,execute,192); }
TL_TEST(mass3_8f5c50) { return smallmass::run(host,1,"mass3_8f5c50",(uint64_t)(uintptr_t)original1,execute,256); }
TL_TEST(mass3_8f5670) { return smallmass::run(host,2,"mass3_8f5670",(uint64_t)(uintptr_t)original2,execute,256); }
TL_TEST(mass3_8e4490) { return smallmass::run(host,3,"mass3_8e4490",(uint64_t)(uintptr_t)original3,execute,384); }
