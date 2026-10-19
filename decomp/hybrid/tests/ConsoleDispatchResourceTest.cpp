#include "FinishLevelFixture.h"
#include "NativeConsoleFixture.h"
#include "ConsoleData.h"
#include "SteamStats.h"
#include "Achievements.h"
#include "Achievement.h"
#include "ParticlePreloader.h"
#include "FileSystem.h"
#include "Dungeon.h"
#include <OgreLogManager.h>
#include <OgreMeshManager.h>
#include "UnitResourceList.h"
#include "Monster.h"
#include "Skill.h"
#include "SettingsVariables.h"
#include <elements/CEGUIMultiLineEditbox.h>
#include <clocale>
TL_ORIGINAL(void,crOriginal,(CConsole*,std::wstring),"_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE")
extern "C" void crCandidate(CConsole*,std::wstring) __asm__("_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(crLog,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(crLookup,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(crType,"_ZN16CResourceManager17getUnitTypeByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(crMasterList,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(crUiVisible,"_ZN7CGameUI18setIngameUIVisibleEb")
TL_FUNCTION(crFps,"_ZN7CGameUI9toggleFPSEv")
namespace {
struct Locale{std::string previous;Locale():previous(std::setlocale(LC_CTYPE,NULL)){if(!std::setlocale(LC_CTYPE,"C.UTF-8"))std::abort();}~Locale(){std::setlocale(LC_CTYPE,previous.c_str());}};
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;CConsole*console;CUnitResourceList*unitlist;CResourceManager*resources;CGameUI*ui;CPlayer*player;
unsigned int keys[]={KSETTINGS_DEBUG_LOGIC,KSETTINGS_SHOW_BLOOD,KSETTINGS_PLAYER_UNTARGETABLE,KSETTINGS_SHOW_MISSILE_TRAILS,KSETTINGS_SHOW_DAMAGE_SHAPES,KSETTINGS_DISPLAY_PATHING,KSETTINGS_SOUND_DEBUG,KSETTINGS_COMBAT_LOG,KSETTINGS_AI_FREEZE};
void num(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){num(s.size());output->add(s.data(),s.size()*4);}
void log(CConsole*p,std::wstring s){num(10);num(p==console);wide(s);num(player->m_cheatMarker);for(unsigned i=0;i<9;++i)num(settings->GetInt(keys[i]));}
CDataGroup* lookup(CUnitResourceList*p,const std::wstring&s){num(11);num(p==unitlist);wide(s);return NULL;}
unsigned type(CResourceManager*p,const std::wstring&s){num(12);num(p==resources);wide(s);return 22;}
CUnitResourceList* masterList(CResourceManager*p){num(13);num(p==resources);return unitlist;}
void visible(CGameUI*p,bool enabled){num(14);num(p==ui);num(enabled);}
void fps(CGameUI*p){num(15);num(p==ui);}
struct Help {bool made;Help():made(false){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14bd5a0),8);if(!p){new(reinterpret_cast<void*>(0x14bd5a0))std::wstring(gTEXT_HELP);made=true;}}~Help(){if(made){reinterpret_cast<std::wstring*>(0x14bd5a0)->~basic_string();std::memset(reinterpret_cast<void*>(0x14bd5a0),0,8);}}};
TL_FUNCTION(crAchievementStatus,"_ZN13CAchievements20getAchievementStatusEv")
TL_FUNCTION(crAchievement,"_ZN13CAchievements14getAchievementESs")
TL_FUNCTION(crCheat,"_ZN12CAchievement5cheatEv")
TL_FUNCTION(crMods,"_ZN11CFileSystem18getEnabledModNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(crParticleNames,"_ZN18CParticlePreloader12getFileNamesERSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(crFlush,"_ZN18CParticlePreloader25aggressiveUnloadParticlesEv")
TL_FUNCTION(crSoundDump,"_ZN13CSoundManager10dumpSoundsEv")
TL_FUNCTION(crRoom,"_ZN6CLevel23getRoomThatPositionIsInERKN4Ogre7Vector3E")
TL_FUNCTION(crMonster,"_ZN6CLevel16getRandomMonsterEv")
TL_FUNCTION(crIdentify,"_ZN10CInventory11identifyAllEv")
TL_FUNCTION(crReset,"_ZN7CPlayer10resetLevelEv")
TL_FUNCTION(crResetStats,"_ZN7CPlayer15resetStatPointsEv")
TL_FUNCTION(crResetSkills,"_ZN7CPlayer11resetSkillsEv")
TL_FUNCTION(crHistory,"_ZN7CPlayer17clearLevelHistoryEv")
TL_FUNCTION(crKill,"_ZN6CLevel7killAllEv")
TL_FUNCTION(crSave,"_ZN11CGameClient13saveCharacterEbb")
TL_FUNCTION(crPetLevel,"_ZN10CCharacter8setLevelEjb")
extern "C" void crLogLibrary(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool) __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
extern "C" void crReloadLibrary(Ogre::ResourceManager*,bool) __asm__("_ZN4Ogre15ResourceManager9reloadAllEb");
extern "C" void crFpsStatic(float) __asm__("_ZN16ParticleUniverse21ParticleSystemManager14setParticleFPSEf");
CMonster*pet;CLevel*level;CEditorScene*room;CAchievements*achievements;CParticlePreloader*preloader;CFileSystem*filesystem;unsigned profile,statusCalls;
void scalar(float v){output->add(&v,4);}void bytes(const std::string&s){num(s.size());output->add(s.data(),s.size());}void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}
unsigned character(CCharacter*p){return p==player?1:p==pet?2:0;}
std::wstring status(CAchievements*p){num(20);num(p==achievements);num(statusCalls++);std::wstring text=statusCalls==1?L"first Тест":L"second 漢字";if(profile&1)text.append(L"\0tail",5);return text;}
CAchievement* achievement(CAchievements*p,std::string name){num(21);num(p==achievements);bytes(name);return profile&1?NULL:achievements->m_achievements[profile%achievements->m_achievements.size()];}
void cheat(CAchievement*p){num(22);num(p==achievements->m_achievements[profile%achievements->m_achievements.size()]);p->m_bAchieved=true;}
void mods(CFileSystem*p,TArrayList<std::wstring>*names){num(23);num(p==filesystem);for(unsigned i=0;i<profile%4;++i)names->add(i&1?L"Mod 漢字":L"Another Mod");}
void names(CParticlePreloader*p,std::wstring&text){num(24);num(p==preloader);text=profile&1?std::wstring(L"a\0tail",6):L"Тест particles 漢字";}
void flush(CParticlePreloader*p){num(25);num(p==preloader);}
void sound(CSoundManager*p){num(26);num(p==CMasterResourceManager::getSingleton()->m_pSoundManager);}
CEditorScene* getRoom(CLevel*p,const Ogre::Vector3&position){num(27);num(p==level);vector(position);return profile&1?NULL:room;}
CCharacter* getMonster(CLevel*p){num(28);num(p==level);return profile&1?NULL:pet;}
void identify(CInventory*p){num(29);num(p==player->getInventory()?1:p==pet->getInventory()?2:0);}
void reset(CPlayer*p){num(30);num(p==player);p->m_iUnitLevel=1;}
void resetStats(CPlayer*p){num(31);num(p==player);}
void resetSkills(CPlayer*p){num(32);num(p==player);}
void history(CPlayer*p){num(33);num(p==player);}
void kill(CLevel*p){num(34);num(p==level);}
void save(CGameClient*p,bool a,bool b){num(35);num(p==console->m_gameClient);num(a);num(b);}
void petLevel(CCharacter*p,unsigned n,bool flag){num(36);num(character(p));num(n);num(flag);p->m_iUnitLevel=n;}
void libraryLog(Ogre::LogManager*p,const std::string&s,Ogre::LogMessageLevel level,bool debug){num(37);num(p==Ogre::LogManager::getSingletonPtr());bytes(s);num(level);num(debug);}
void reload(Ogre::ResourceManager*p,bool flag){num(38);num(p==&Ogre::MeshManager::getSingleton());num(flag);}
struct Files {
 CFileSystem*previous;CFileSystem*p;bool n,w;
 Files():previous(g_pFileSystem),p(NULL),n(false),w(false){void*q=NULL;std::memcpy(&q,reinterpret_cast<void*>(0x1528e40),8);if(!q){new(reinterpret_cast<void*>(0x1528e40))std::string;n=true;}std::memcpy(&q,reinterpret_cast<void*>(0x1528e48),8);if(!q){new(reinterpret_cast<void*>(0x1528e48))std::wstring;w=true;}void*storage=Ogre::NedAllocImpl::allocBytes(sizeof(CFileSystem),0,0,0);g_pFileSystem=static_cast<CFileSystem*>(storage);p=new(storage)CFileSystem(false);}
 ~Files(){p->~CFileSystem();Ogre::NedAllocImpl::deallocBytes(p);g_pFileSystem=previous;if(w){reinterpret_cast<std::wstring*>(0x1528e48)->~basic_string();std::memset(reinterpret_cast<void*>(0x1528e48),0,8);}if(n){reinterpret_cast<std::string*>(0x1528e40)->~basic_string();std::memset(reinterpret_cast<void*>(0x1528e40),0,8);}}
};
const wchar_t*commands[]={L"ACHIEVEMENTS",L"CHEATACHIEVEMENT test",L"CHEATACHIEVEMENT Тест",L"CHEATACHIEVEMENT 1",L"MODS",L"PARTICLES",L"PARTICLESOFF",L"PARTICLESON",L"PARTICLEFLUSH",L"SOUNDDUMP",L"RELOAD",L"SAVEME",L"ROOM",L"WATCHRANDOM",L"IDENTIFYALL",L"IDALL",L"RESETPLAYER",L"RESETSTATS",L"RESETSKILLS",L"RESETPLAYERLEVEL",L"RESETPETLEVEL",L"CLEARSTRINGS",L"KILLALL",L"CLEARHISTORY",L"ASCEND",L"ASCEND -2",L"ASCEND 0",L"ASCEND 2",L"ASCEND 99",L"DESCEND",L"DESCEND -2",L"DESCEND 0",L"DESCEND 2",L"DESCEND 1001",L"RESTARTLEVEL"};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;unsigned count=sizeof(commands)/sizeof(commands[0]);bool nullPlayer=c.index>=count*4;profile=nullPlayer?c.index-count*4:c.index/count;statusCalls=0;CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);finishlevel::Fixture world;resources=&world.resources;level=&world.level;resources->m_pSceneManager=f.nativeClient.scenes[0];resources->m_GameClients.add(f.nativeClient.client);menugui::Console owner(f);console=owner.p;ui=f.ui;console->m_resources=resources;console->m_gameClient=f.nativeClient.client;f.nativeClient.client->m_level=level;
 CUnitResourceList*previous=CUnitResourceList::getSingleton();CUnitResourceList list;unitlist=&list;m_pGlobalUnitResourceList=unitlist;player=nativegame::createPlayer(resources);f.nativeClient.client->m_pPlayer=player;pet=new CMonster(resources,1);if(profile&1)player->m_Followers.push_back(pet);player->m_iUnitLevel=profile+3;pet->m_iUnitLevel=profile+7;player->m_cheatMarker=profile%4==1?214:profile%4;player->m_characterDisplayName=profile&1?L"The Cheat":L"Тест 漢字";player->setPosition(Ogre::Vector3(.5f+profile,3.25f,-7.5f));
 CDungeon* dungeon=f.nativeClient.dungeons->m_lDungeons[0];dungeon->m_sName=profile&1?L"TOWN":L"Minedungeon";f.nativeClient.client->m_currentDungeon=dungeon;level->m_iLevelDepth=int(profile)-2;level->m_dungeonDepth=profile+19;f.nativeClient.client->m_warpDungeon=L"before";f.nativeClient.client->m_warpDepth=-17;f.nativeClient.client->m_warpDelta=13;f.nativeClient.client->m_warpPending=false;
 Files files;filesystem=files.p;CLayout actualRoom(resources,static_cast<ELAYOUT_TYPES>(0));room=&actualRoom;actualRoom.m_sFileLoaded=L"some/Тест.layout";void*oldStats=CSteamStats::getSingleton(),*oldAchievements=CAchievements::getSingleton();TSafePointer<CRunicCore> statsWeak,achievementsWeak;
 {CSteamStats stats;CAchievements actualAchievements;achievements=&actualAchievements;statsWeak.setObject(&stats);achievementsWeak.setObject(achievements);CParticlePreloader particles(NULL);preloader=&particles;CParticlePreloader*oldPreloader=CMasterResourceManager::getSingleton()->m_pParticlePreloader;CMasterResourceManager::getSingleton()->m_pParticlePreloader=preloader;float oldFps;std::memcpy(&oldFps,reinterpret_cast<void*>(0x14210d4),4);float sentinel=-13.25f;std::memcpy(reinterpret_cast<void*>(0x14210d4),&sentinel,4);settings->SetFloat(KSETTINGS_F_PARTICLEFPS,profile&1?37.5f:0.0f);
 detour::Set calls;TL_REDIRECT(calls,crLog,&log);TL_REDIRECT(calls,crLookup,&lookup);TL_REDIRECT(calls,crType,&type);TL_REDIRECT(calls,crMasterList,&masterList);TL_REDIRECT(calls,crAchievementStatus,&status);TL_REDIRECT(calls,crAchievement,&achievement);TL_REDIRECT(calls,crCheat,&cheat);TL_REDIRECT(calls,crMods,&mods);TL_REDIRECT(calls,crParticleNames,&names);TL_REDIRECT(calls,crFlush,&flush);TL_REDIRECT(calls,crSoundDump,&sound);TL_REDIRECT(calls,crRoom,&getRoom);TL_REDIRECT(calls,crMonster,&getMonster);TL_REDIRECT(calls,crIdentify,&identify);TL_REDIRECT(calls,crReset,&reset);TL_REDIRECT(calls,crResetStats,&resetStats);TL_REDIRECT(calls,crResetSkills,&resetSkills);TL_REDIRECT(calls,crHistory,&history);TL_REDIRECT(calls,crKill,&kill);TL_REDIRECT(calls,crSave,&save);TL_REDIRECT(calls,crPetLevel,&petLevel);calls.redirect(reinterpret_cast<char*>(&crLogLibrary),reinterpret_cast<char*>(&crLogLibrary),&libraryLog);calls.redirect(reinterpret_cast<char*>(&crReloadLibrary),reinterpret_cast<char*>(&crReloadLibrary),&reload);if(calls.failed())std::abort();
 if(nullPlayer)f.nativeClient.client->m_pPlayer=NULL;typedef void(*Fn)(CConsole*,std::wstring);Fn fn=ours?crCandidate:crOriginal;if(!autotest::beginInvocation(out,fn))return;fn(console,nullPlayer?(profile?L"IDALL":L"IDENTIFYALL"):commands[c.index%count]);out.callCompleted=1;
 num(statusCalls);float fps;std::memcpy(&fps,reinterpret_cast<void*>(0x14210d4),4);scalar(fps);num(player->m_iUnitLevel);num(pet->m_iUnitLevel);num(player->m_cheatMarker);wide(player->m_characterDisplayName);num(f.nativeClient.client->m_cameraWatchTarget==pet);num(f.nativeClient.client->m_cameraWatchTarget==NULL);wide(f.nativeClient.client->m_warpDungeon);num(f.nativeClient.client->m_warpDepth);num(f.nativeClient.client->m_warpDelta);num(f.nativeClient.client->m_warpPending);num(f.nativeClient.client->m_warpWaypoint);num(f.nativeClient.client->m_warpFlag);for(unsigned i=0;i<actualAchievements.m_achievements.size();++i)num(actualAchievements.m_achievements[i]->m_bAchieved);calls.restore();std::memcpy(reinterpret_cast<void*>(0x14210d4),&oldFps,4);CMasterResourceManager::getSingleton()->m_pParticlePreloader=oldPreloader;
 }
 num(statsWeak.getObject()==NULL);num(achievementsWeak.getObject()==NULL);std::memcpy(reinterpret_cast<void*>(0x153a840),&oldStats,8);std::memcpy(reinterpret_cast<void*>(0x1539240),&oldAchievements,8);
 player->m_Followers.clear();delete pet;f.nativeClient.client->m_pPlayer=NULL;f.nativeClient.client->m_level=NULL;f.nativeClient.client->m_currentDungeon=NULL;nativegame::destroyPlayer(player);resources->m_GameClients.clear();m_pGlobalUnitResourceList=previous;
}
}
TL_TEST(complete_ui_console_dispatch_resource){Locale locale;tlheadless::Environment env;env.loadGameSkin();CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/WindowsLook.scheme");nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_ui_console_dispatch_resource",0xaf2540,&side,(sizeof(commands)/sizeof(commands[0]))*4+2);}
