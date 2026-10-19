#include "FinishLevelFixture.h"
#include "NativeConsoleFixture.h"
#include "ConsoleData.h"
#include "SpawnClassParser.h"
#include "SpawnClass.h"
#include "Equipment.h"
#include "StringUtilities.h"
#include "UnitResourceList.h"
#include "Monster.h"
#include "Skill.h"
#include "SettingsVariables.h"
#include <elements/CEGUIMultiLineEditbox.h>
#include <clocale>
TL_ORIGINAL(void,cuOriginal,(CConsole*,std::wstring),"_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE")
extern "C" void cuCandidate(CConsole*,std::wstring) __asm__("_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(cuLog,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cuLookup,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cuType,"_ZN16CResourceManager17getUnitTypeByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cuMasterList,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(cuUiVisible,"_ZN7CGameUI18setIngameUIVisibleEb")
TL_FUNCTION(cuFps,"_ZN7CGameUI9toggleFPSEv")
namespace {
struct Locale{std::string previous;Locale():previous(std::setlocale(LC_CTYPE,NULL)){if(!std::setlocale(LC_CTYPE,"C.UTF-8"))std::abort();}~Locale(){std::setlocale(LC_CTYPE,previous.c_str());}};
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;CConsole*console;CUnitResourceList*unitlist;CResourceManager*resources;CGameUI*ui;CPlayer*player;
unsigned int keys[]={KSETTINGS_DEBUG_LOGIC,KSETTINGS_SHOW_BLOOD,KSETTINGS_PLAYER_UNTARGETABLE,KSETTINGS_SHOW_MISSILE_TRAILS,KSETTINGS_SHOW_DAMAGE_SHAPES,KSETTINGS_DISPLAY_PATHING,KSETTINGS_SOUND_DEBUG,KSETTINGS_COMBAT_LOG,KSETTINGS_AI_FREEZE};
void num(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){num(s.size());output->add(s.data(),s.size()*4);}
void log(CConsole*p,std::wstring s){num(10);num(p==console);wide(s);num(player->m_cheatMarker);for(unsigned i=0;i<9;++i)num(settings->GetInt(keys[i]));}
CDataGroup* lookup(CUnitResourceList*p,const std::wstring&s);
unsigned type(CResourceManager*p,const std::wstring&s);
CUnitResourceList* masterList(CResourceManager*p){num(13);num(p==resources);return unitlist;}
void visible(CGameUI*p,bool enabled){num(14);num(p==ui);num(enabled);}
void fps(CGameUI*p){num(15);num(p==ui);}
struct Help {bool made;Help():made(false){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14bd5a0),8);if(!p){new(reinterpret_cast<void*>(0x14bd5a0))std::wstring(gTEXT_HELP);made=true;}}~Help(){if(made){reinterpret_cast<std::wstring*>(0x14bd5a0)->~basic_string();std::memset(reinterpret_cast<void*>(0x14bd5a0),0,8);}}};
TL_FUNCTION(cuGroups,"_ZN17CUnitResourceList23getDataGroupsByUnitTypeEjR10TArrayListIP10CDataGroupE")
TL_FUNCTION(cuGroup,"_ZN17CUnitResourceList14getGroupByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cuCreate,"_ZN16CResourceManager10createUnitEP10CDataGroupibb")
TL_FUNCTION(cuOpen,"_ZN6CLevel18randomOpenPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(cuOpenItem,"_ZN6CLevel22randomOpenItemPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(cuAdd,"_ZN6CLevel7addUnitEP9CBaseUnitRKN4Ogre7Vector3E")
TL_FUNCTION(cuUnit,"_ZN8CConsole9spawnUnitESbIwSt11char_traitsIwESaIwEES3_")
TL_FUNCTION(cuMonster,"_ZN8CConsole12spawnMonsterESbIwSt11char_traitsIwESaIwEES3_bi")
TL_FUNCTION(cuItem,"_ZN8CConsole9spawnItemESbIwSt11char_traitsIwESaIwEExS3_")
CLevel*level;unsigned profile;std::vector<CDataGroup*>groups;std::vector<TSafePointer<CBaseUnit>*>units;std::map<long long,CDataGroup*>guidmap;
void scalar(float v){output->add(&v,4);}void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}unsigned groupIdentity(CDataGroup*p){for(unsigned i=0;i<groups.size();++i)if(groups[i]==p)return i+1;return 0;}unsigned identity(CBaseUnit*p){for(unsigned i=0;i<units.size();++i)if(units[i]->getObject()==p)return i+1;return 0;}
CDataGroup* lookup(CUnitResourceList*p,const std::wstring&s){num(11);num(p==unitlist);wide(s);return s==L"NAMED"?groups[profile%3]:NULL;}
unsigned type(CResourceManager*p,const std::wstring&s){num(12);num(p==resources);wide(s);std::wstring name=STRINGS::StringUpper(s);if(name==L"MONSTER")return 27;if(name==L"ITEM")return 7;if(name==L"OTHER TYPE")return 3;return 22;}
unsigned getGroups(CUnitResourceList*p,unsigned type,TArrayList<CDataGroup*>&out){num(20);num(p==unitlist);num(type);num(out.m_nGrowBy);for(unsigned i=0;i<profile%4;++i)out.add(groups[i]);return out.size();}
std::map<long long,CDataGroup*>*getGroup(CUnitResourceList*p,const std::wstring&name){num(21);num(p==unitlist);wide(name);return &guidmap;}
CBaseUnit* create(CResourceManager*p,CDataGroup*group,int depth,bool a,bool b){num(22);num(p==resources);num(groupIdentity(group));num(depth);num(a);num(b);CMonster*unit=new CMonster(resources,1);TSafePointer<CBaseUnit>*weak=new TSafePointer<CBaseUnit>;weak->setObject(unit);units.push_back(weak);return unit;}
Ogre::Vector3 open(CLevel*p,const Ogre::Vector3&pos,float radius,bool flag){num(23);num(p==level);vector(pos);scalar(radius);num(flag);return Ogre::Vector3(pos.x+radius,pos.y-.25f,pos.z-3.5f);}
Ogre::Vector3 openItem(CLevel*p,const Ogre::Vector3&pos,float radius,bool flag){num(24);num(p==level);vector(pos);scalar(radius);num(flag);return Ogre::Vector3(pos.x-.125f,pos.y+radius,pos.z-2.25f);}
CBaseUnit*add(CLevel*p,CBaseUnit*unit,const Ogre::Vector3&pos){num(25);num(p==level);num(identity(unit));vector(pos);return unit;}
void unit(CConsole*p,std::wstring name,std::wstring count){num(26);num(p==console);wide(name);wide(count);}
void monster(CConsole*p,std::wstring name,std::wstring count,bool champ,int depth){num(27);num(p==console);wide(name);wide(count);num(champ);num(depth);}
void item(CConsole*p,std::wstring name,long long guid,std::wstring count){num(28);num(p==console);wide(name);output->add(&guid,8);wide(count);}
struct GroupStrings {bool made[4];GroupStrings(){const wchar_t*names[]={L"ITEMS",L"MONSTERS",L"PLAYERS",L"PROPS"};for(unsigned i=0;i<4;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14bc560+i*8),8);made[i]=!p;if(made[i])new(reinterpret_cast<void*>(0x14bc560+i*8))std::wstring(names[i]);}}~GroupStrings(){for(unsigned i=0;i<4;++i)if(made[i]){reinterpret_cast<std::wstring*>(0x14bc560+i*8)->~basic_string();std::memset(reinterpret_cast<void*>(0x14bc560+i*8),0,8);}}};
const wchar_t*commands[]={L"NAMED",L"named",L"\tNAMED",L"ALLITEMS",L"ALLMONSTERS",L"SPAWNCLASS",L"MONSTER",L"CHAMPION",L"ITEM",L"OTHER_TYPE",L"monster",L"MONSTER 0",L"MONSTER 0,2",L"MONSTER 1,3,7",L"MONSTER 9",L"CHAMPION 0",L"CHAMPION 1,4",L"CHAMPION 9",L"ITEM 0",L"ITEM 1,2",L"ITEM 9",L"OTHER_TYPE 0",L"OTHER_TYPE 1,5",L"OTHER_TYPE 9",L"MONSTER -1",L"ITEM -1",L"CHAMPION -1",L"MONSTER 01",L"ITEM 01",L"MONSTER 2,3,4,5",L"CHAMPION 2,3,4",L"OTHER_TYPE 2,3,4"};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;unsigned count=sizeof(commands)/sizeof(commands[0]);profile=c.index/count;units.clear();groups.clear();guidmap.clear();CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);finishlevel::Fixture world;resources=&world.resources;level=&world.level;resources->m_pSceneManager=f.nativeClient.scenes[0];resources->m_GameClients.add(f.nativeClient.client);menugui::Console owner(f);console=owner.p;ui=f.ui;console->m_resources=resources;console->m_gameClient=f.nativeClient.client;f.nativeClient.client->m_level=level;level->m_iLevelDepth=int(profile)+2;level->m_dungeonDepth=int(profile)+41;
 CUnitResourceList*previous=CUnitResourceList::getSingleton();CUnitResourceList list;unitlist=&list;m_pGlobalUnitResourceList=unitlist;player=nativegame::createPlayer(resources);f.nativeClient.client->m_pPlayer=player;player->m_cheatMarker=profile%4==1?214:profile%4;player->m_characterDisplayName=profile&1?L"The Cheat":L"Тест 漢字";player->setPosition(Ogre::Vector3(.5f+profile,3.25f,-7.5f));Ogre::Vector3 forward(.25f,profile&1?.5f:0,-.75f),up(0,1,0);player->setOrientation(forward,up);
 const wchar_t*names[]={L"first",L"Name Two",L"漢字 Тест"};for(unsigned i=0;i<3;++i){CDataGroup*d=new CDataGroup(L"unit",NULL,3,3,NULL);d->AddDataValue(L"NAME",names[i],false);groups.push_back(d);}long long guids[]={-1,17,0x123456789abcdefLL};for(unsigned i=0;i<profile%4;++i)guidmap[guids[i]]=groups[i];GroupStrings groupStrings;
 CSpawnClassParser*previousParser=CSpawnClassParser::getSingleton();CSpawnClassParser parser;for(unsigned i=0;i<profile%4;++i)parser.m_spawnClasses[names[i]]=new CSpawnClass(names[i]);
 detour::Set calls;TL_REDIRECT(calls,cuLog,&log);TL_REDIRECT(calls,cuLookup,&lookup);TL_REDIRECT(calls,cuType,&type);TL_REDIRECT(calls,cuMasterList,&masterList);TL_REDIRECT(calls,cuGroups,&getGroups);TL_REDIRECT(calls,cuGroup,&getGroup);TL_REDIRECT(calls,cuCreate,&create);TL_REDIRECT(calls,cuOpen,&open);TL_REDIRECT(calls,cuOpenItem,&openItem);TL_REDIRECT(calls,cuAdd,&add);TL_REDIRECT(calls,cuUnit,&unit);TL_REDIRECT(calls,cuMonster,&monster);TL_REDIRECT(calls,cuItem,&item);if(calls.failed())std::abort();typedef void(*Fn)(CConsole*,std::wstring);Fn fn=ours?cuCandidate:cuOriginal;if(!autotest::beginInvocation(out,fn))return;fn(console,commands[c.index%count]);out.callCompleted=1;
 num(player->m_cheatMarker);wide(player->m_characterDisplayName);num(units.size());calls.restore();for(unsigned i=0;i<units.size();++i){num(units[i]->getObject()!=NULL);delete units[i]->getObject();num(units[i]->getObject()==NULL);delete units[i];}units.clear();for(unsigned i=0;i<groups.size();++i)delete groups[i];groups.clear();guidmap.clear();f.nativeClient.client->m_pPlayer=NULL;f.nativeClient.client->m_level=NULL;nativegame::destroyPlayer(player);resources->m_GameClients.clear();m_pGlobalUnitResourceList=previous;
 (void)previousParser;
}
}
TL_TEST(complete_ui_console_dispatch_unit){Locale locale;tlheadless::Environment env;env.loadGameSkin();CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/WindowsLook.scheme");nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_ui_console_dispatch_unit",0xaf2540,&side,(sizeof(commands)/sizeof(commands[0]))*8);}
