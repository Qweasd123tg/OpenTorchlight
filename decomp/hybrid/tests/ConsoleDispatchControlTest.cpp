#include "FinishLevelFixture.h"
#include "NativeConsoleFixture.h"
#include "ConsoleData.h"
#include "UnitResourceList.h"
#include "Monster.h"
#include "Skill.h"
#include "SettingsVariables.h"
#include <elements/CEGUIMultiLineEditbox.h>
#include <clocale>
TL_ORIGINAL(void,cdOriginal,(CConsole*,std::wstring),"_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE")
extern "C" void cdCandidate(CConsole*,std::wstring) __asm__("_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(cdLog,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cdLookup,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cdType,"_ZN16CResourceManager17getUnitTypeByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cdMasterList,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(cdUiVisible,"_ZN7CGameUI18setIngameUIVisibleEb")
TL_FUNCTION(cdFps,"_ZN7CGameUI9toggleFPSEv")
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
const wchar_t*commands[]={L"HELP",L"?",L"CLS",L"DEBUGLOGIC",L"HIDEUI",L"SHOWUI",L"DOICHEAT",L"WATCHPLAYER",L"WATCH",L"WATCH PLAYER",L"WATCHPET",L"DISABLEPET",L"SHOWBLOOD",L"ALWAYSCRIT",L"NOXP",L"HOWHARD",L"DIFFICULTY",L"PLAYERNOTARGET",L"MISSILETRAILS",L"MISSILE TRAILS",L"DAMAGE SHAPES",L"SKILLTEST",L"PATHING",L"SOUNDDEBUG",L"COMBATLOG",L"GOD",L"AIFREEZE",L"FPS",L"not_a_command",L"",L" ",L"@?!-HELP",L"help",L"h\ne\nl\np",L"debuglogic",L"NOXP\n",L"\t\rHOWHARD",L"ALWAYSCRIT\n",L"unknown  value",L"\n",L" PLAYERNOTARGET"};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;unsigned count=sizeof(commands)/sizeof(commands[0]);bool nullPlayer=c.index>=count*8;unsigned profile=nullPlayer?c.index-count*8:c.index/count;CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);finishlevel::Fixture world;resources=&world.resources;resources->m_pSceneManager=f.nativeClient.scenes[0];resources->m_GameClients.add(f.nativeClient.client);menugui::Console owner(f);console=owner.p;ui=f.ui;console->m_resources=resources;console->m_gameClient=f.nativeClient.client;f.nativeClient.client->m_level=&world.level;
 CUnitResourceList*previous=CUnitResourceList::getSingleton();CUnitResourceList list;unitlist=&list;m_pGlobalUnitResourceList=unitlist;
 player=nativegame::createPlayer(resources);f.nativeClient.client->m_pPlayer=player;CMonster*pet=new CMonster(resources,1),*nested=new CMonster(resources,1);player->m_Followers.push_back(pet);if(profile&1)pet->m_Followers.push_back(nested);pet->setEnabled(profile&1);nested->setEnabled(!(profile&1));player->m_flag700=profile&1;player->m_experienceDisabled=profile&2;player->m_godMode=profile&4;player->m_cheatMarker=profile%4==1?214:profile%4;player->m_characterDisplayName=profile&1?L"The Cheat":L"Тест 漢字";
 for(unsigned i=0;i<9;++i)settings->SetInt(keys[i],int(profile%4)-1);f.nativeClient.client->m_startDifficulty=int(profile)-2;f.nativeClient.client->m_cameraWatchTarget=pet;m_gAllowSkillTesting=profile&1;console->m_historyWindow->setText("before\ntext");static_cast<CEGUI::MultiLineEditbox*>(console->m_historyWindow)->setCaratIndex(profile);
 Help help;detour::Set calls;TL_REDIRECT(calls,cdLog,&log);TL_REDIRECT(calls,cdLookup,&lookup);TL_REDIRECT(calls,cdType,&type);TL_REDIRECT(calls,cdMasterList,&masterList);TL_REDIRECT(calls,cdUiVisible,&visible);TL_REDIRECT(calls,cdFps,&fps);if(calls.failed())std::abort();
 const wchar_t*nullCommands[]={L"DOICHEAT",L"doicheat",L" DOICHEAT",L"\nDOICHEAT",L"GOD",L"HIDEUI",L"AIFREEZE",L"unknown"};if(nullPlayer)f.nativeClient.client->m_pPlayer=NULL;typedef void(*Fn)(CConsole*,std::wstring);Fn fn=ours?cdCandidate:cdOriginal;if(!autotest::beginInvocation(out,fn))return;fn(console,nullPlayer?nullCommands[profile]:commands[c.index%count]);out.callCompleted=1;
 for(unsigned i=0;i<9;++i)num(settings->GetInt(keys[i]));num(player->m_flag700);num(player->m_experienceDisabled);num(pet->m_experienceDisabled);num(player->m_godMode);num(player->m_cheatMarker);wide(player->m_characterDisplayName);num(pet->getEnabled());num(nested->getEnabled());num(f.nativeClient.client->m_cameraWatchTarget==pet);num(f.nativeClient.client->m_cameraWatchTarget==NULL);num(m_gAllowSkillTesting);std::string history=console->m_historyWindow->getText().c_str();num(history.size());out.add(history.data(),history.size());num(static_cast<CEGUI::MultiLineEditbox*>(console->m_historyWindow)->getCaratIndex());
 calls.restore();player->m_Followers.clear();pet->m_Followers.clear();delete pet;delete nested;f.nativeClient.client->m_pPlayer=NULL;f.nativeClient.client->m_level=NULL;f.nativeClient.client->m_cameraWatchTarget=NULL;nativegame::destroyPlayer(player);resources->m_GameClients.clear();m_pGlobalUnitResourceList=previous;
}
}
TL_TEST(complete_ui_console_dispatch_control){Locale locale;tlheadless::Environment env;env.loadGameSkin();CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/WindowsLook.scheme");nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_ui_console_dispatch_control",0xaf2540,&side,(sizeof(commands)/sizeof(commands[0]))*8+8);}
