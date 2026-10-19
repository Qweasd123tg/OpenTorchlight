#include "FinishLevelFixture.h"
#include "NativeConsoleFixture.h"
#include "ConsoleData.h"
#include "SkillParser.h"
#include "CameraControl.h"
#include "UnitResourceList.h"
#include "Monster.h"
#include "Skill.h"
#include "SettingsVariables.h"
#include <elements/CEGUIMultiLineEditbox.h>
#include <clocale>
TL_ORIGINAL(void,cpOriginal,(CConsole*,std::wstring),"_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE")
extern "C" void cpCandidate(CConsole*,std::wstring) __asm__("_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(cpLog,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cpLookup,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cpType,"_ZN16CResourceManager17getUnitTypeByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cpMasterList,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(cpUiVisible,"_ZN7CGameUI18setIngameUIVisibleEb")
TL_FUNCTION(cpFps,"_ZN7CGameUI9toggleFPSEv")
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
TL_FUNCTION(cpExperience,"_ZN22CMasterResourceManager14experienceGateEi")
TL_FUNCTION(cpAward,"_ZN10CCharacter15awardExperienceER6CLevelPS_ib")
TL_FUNCTION(cpStats,"_ZN10CCharacter20giveUnusedStatPointsEi")
TL_FUNCTION(cpSkills,"_ZN10CCharacter21giveUnusedSkillPointsEi")
TL_FUNCTION(cpMelee,"_ZN10CCharacter15spendMeleePointEv")
TL_FUNCTION(cpRanged,"_ZN10CCharacter16spendRangedPointEv")
TL_FUNCTION(cpMagic,"_ZN10CCharacter15spendMagicPointEv")
TL_FUNCTION(cpDefense,"_ZN10CCharacter17spendDefensePointEv")
TL_FUNCTION(cpFame,"_ZN10CCharacter7addFameEj")
TL_FUNCTION(cpGold,"_ZN10CCharacter8giveGoldEi")
TL_FUNCTION(cpMax,"_ZN10CCharacter5maxHPEv")
TL_FUNCTION(cpHp,"_ZN10CCharacter8modifyHPEf")
TL_FUNCTION(cpLevel,"_ZN10CCharacter8setLevelEjb")
TL_FUNCTION(cpNames,"_ZN12CSkillParser13getSkillNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(cpUnit,"_ZN8CConsole9spawnUnitESbIwSt11char_traitsIwESaIwEES3_")
TL_FUNCTION(cpMonster,"_ZN8CConsole12spawnMonsterESbIwSt11char_traitsIwESaIwEES3_bi")
TL_FUNCTION(cpItem,"_ZN8CConsole9spawnItemESbIwSt11char_traitsIwESaIwEExS3_")
TL_FUNCTION(cpObject,"_ZN8CConsole18createObjectByNameESbIwSt11char_traitsIwESaIwEES3_")
TL_FUNCTION(cpShake,"_ZN8CConsole11cameraShakeESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cpClass,"_ZN8CConsole16spawnClassCreateESbIwSt11char_traitsIwESaIwEES3_S3_")
TL_FUNCTION(cpEquip,"_ZN8CConsole18equipSkillToPlayerESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cpSpeed,"_ZN8CConsole16addSpeedToPlayerEv")
TL_FUNCTION(cpDistance,"_ZN14CCameraControl25getDefaultDistanceToDollyEv")
CMonster*pet;CLevel*level;CCameraControl*camera;unsigned profile;
void scalar(float f){output->add(&f,4);}unsigned character(CCharacter*p){return p==player?1:p==pet?2:0;}
int experience(CMasterResourceManager*p,int n){num(20);num(p==CMasterResourceManager::getSingleton());num(n);return 77+n*23;}
void award(CCharacter*p,CLevel&l,CCharacter*k,int amount,bool flag){num(21);num(character(p));num(&l==level);num(character(k));num(amount);num(flag);++p->m_iUnitLevel;p->m_experience+=amount;}
void stats(CCharacter*p,int n){num(22);num(character(p));num(n);p->m_iUnusedStatPoints+=n;}
void skills(CCharacter*p,int n){num(23);num(character(p));num(n);p->m_iUnusedSkillPoints+=n;}
void melee(CCharacter*p){num(24);num(character(p));--p->m_iUnusedStatPoints;}
void ranged(CCharacter*p){num(25);num(character(p));--p->m_iUnusedStatPoints;}
void magic(CCharacter*p){num(26);num(character(p));--p->m_iUnusedStatPoints;}
void defense(CCharacter*p){num(27);num(character(p));--p->m_iUnusedStatPoints;}
void fame(CCharacter*p,unsigned n){num(28);num(character(p));num(n);p->m_fame+=n;}
void gold(CCharacter*p,int n){num(29);num(character(p));num(n);}
int maxHP(CCharacter*p){num(30);num(character(p));return p==player?135:701;}
void modify(CCharacter*p,float n){num(31);num(character(p));scalar(n);}
void setLevel(CCharacter*p,unsigned n,bool flag){num(32);num(character(p));num(n);num(flag);p->m_iUnitLevel=n;}
void names(TArrayList<std::wstring>&n){num(33);for(unsigned i=0;i<profile%4;++i)n.add(i&1?L"Тест 漢字":L"Skill Name");}
void unit(CConsole*p,std::wstring name,std::wstring count){num(34);num(p==console);wide(name);wide(count);}
void monster(CConsole*p,std::wstring name,std::wstring count,bool champ,int depth){num(35);num(p==console);wide(name);wide(count);num(champ);num(depth);}
void item(CConsole*p,std::wstring name,long long guid,std::wstring count){num(36);num(p==console);wide(name);output->add(&guid,8);wide(count);}
void object(CConsole*p,std::wstring name,std::wstring count){num(37);num(p==console);wide(name);wide(count);}
void shake(CConsole*p,std::wstring name){num(38);num(p==console);wide(name);}
void spawnclass(CConsole*p,std::wstring name,std::wstring count,std::wstring depth){num(39);num(p==console);wide(name);wide(count);wide(depth);}
void equip(CConsole*p,std::wstring name){num(40);num(p==console);wide(name);}
void speed(CConsole*p){num(41);num(p==console);}
float distance(CCameraControl*p){num(42);num(p==camera);scalar(p->m_fUnknown8C);return p->m_fUnknown8C*7.25f+3.5f;}
const wchar_t*commands[]={L"LEVELUP",L"LEVELUP 0",L"LEVELUP 1",L"LEVELUP 2",L"LEVELUP 50",L"SETPETLEVEL -2",L"SETPETLEVEL 0",L"SETPETLEVEL 5",L"HURTME -2",L"HURTME 0",L"HURTME 47",L"HURTME 100",L"HURTME 999",L"SETDIFFICULTY 0",L"SETDIFFICULTY 1",L"SETDIFFICULTY 3",L"SETDIFFICULTY -1",L"SETDIFFICULTY 4",L"STATPOINTS -2",L"ALLSTATS 0",L"ALLSTATS 2",L"STRENGTH -2",L"STRENGTH 3",L"DEXTERITY 2",L"MAGIC 3",L"DEFENSE 2",L"FAME -2",L"FAME 7",L"ANIMATIONSPEED -4",L"ANIMATIONSPEED 53.75",L"SKILLPOINTS -2",L"SKILLPOINTS 3",L"MONEY -9",L"MONEY 19",L"CAMERADISTANCE .25",L"CAMERADISTANCE -1.5",L"CAMERASHAKE Some Shake",L"UNIT Test",L"UNIT Case Name,3",L"EDITOROBJECT Object Name",L"EDITOROBJECT Тест 漢字,2",L"SPAWNCLASS Name",L"SPAWNCLASS Name,2",L"SPAWNCLASS Name,3,-2",L"SKILL Name",L"SKILL 0",L"SKILL 2",L"SKILL -1",L"MONSTER Name",L"MONSTER Name,2",L"MONSTER Name,3,7",L"CHAMPION Name",L"CHAMPION Name,2,8",L"ITEM Name",L"ITEM Name,2",L"ITEMGUID -1",L"ITEMGUID 123456789123,3",L"SPEED",L"GODSPEED",L"SKILL",L"SKILLS",L"CAMERASHAKE ,",L"STRENGTH 0",L"UNIT a,b,c,d",L"unknown 0",L"unknown name,extra",L" statpoints 3",L"skill name\n"};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;unsigned count=sizeof(commands)/sizeof(commands[0]);profile=c.index/count;CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);finishlevel::Fixture world;resources=&world.resources;level=&world.level;resources->m_pSceneManager=f.nativeClient.scenes[0];resources->m_GameClients.add(f.nativeClient.client);menugui::Console owner(f);console=owner.p;ui=f.ui;camera=f.nativeClient.camera;console->m_resources=resources;console->m_gameClient=f.nativeClient.client;f.nativeClient.client->m_level=level;
 CUnitResourceList*previous=CUnitResourceList::getSingleton();CUnitResourceList list;unitlist=&list;m_pGlobalUnitResourceList=unitlist;
 player=nativegame::createPlayer(resources);f.nativeClient.client->m_pPlayer=player;pet=new CMonster(resources,1);if(profile&1)player->m_Followers.push_back(pet);player->m_iUnitLevel=profile+1;player->m_experience=profile*3+7;player->m_fame=profile*13;player->m_iUnusedStatPoints=profile;player->m_iUnusedSkillPoints=profile;player->m_godMode=profile&2;player->m_saveOnDeath=profile&1;player->m_cheatMarker=profile%4==1?214:profile%4;player->m_characterDisplayName=profile&1?L"The Cheat":L"Тест 漢字";camera->m_fUnknown8C=.5f;camera->m_fUnknown38=11.25f;
 for(unsigned i=0;i<9;++i)settings->SetInt(keys[i],int(profile%4)-1);f.nativeClient.client->m_startDifficulty=int(profile)-2;settings->SetFloat(KSETTINGS_F_ANIMATION_FPS,7.5f);std::wstring input=commands[c.index%count];if(profile==3&&input.find(L"LEVELUP")!=0&&input.find(L"ALLSTATS")!=0)f.nativeClient.client->m_pPlayer=NULL;
 detour::Set calls;TL_REDIRECT(calls,cpLog,&log);TL_REDIRECT(calls,cpLookup,&lookup);TL_REDIRECT(calls,cpType,&type);TL_REDIRECT(calls,cpMasterList,&masterList);TL_REDIRECT(calls,cpExperience,&experience);TL_REDIRECT(calls,cpAward,&award);TL_REDIRECT(calls,cpStats,&stats);TL_REDIRECT(calls,cpSkills,&skills);TL_REDIRECT(calls,cpMelee,&melee);TL_REDIRECT(calls,cpRanged,&ranged);TL_REDIRECT(calls,cpMagic,&magic);TL_REDIRECT(calls,cpDefense,&defense);TL_REDIRECT(calls,cpFame,&fame);TL_REDIRECT(calls,cpGold,&gold);TL_REDIRECT(calls,cpMax,&maxHP);TL_REDIRECT(calls,cpHp,&modify);TL_REDIRECT(calls,cpLevel,&setLevel);TL_REDIRECT(calls,cpNames,&names);TL_REDIRECT(calls,cpUnit,&unit);TL_REDIRECT(calls,cpMonster,&monster);TL_REDIRECT(calls,cpItem,&item);TL_REDIRECT(calls,cpObject,&object);TL_REDIRECT(calls,cpShake,&shake);TL_REDIRECT(calls,cpClass,&spawnclass);TL_REDIRECT(calls,cpEquip,&equip);TL_REDIRECT(calls,cpSpeed,&speed);TL_REDIRECT(calls,cpDistance,&distance);if(calls.failed())std::abort();
 typedef void(*Fn)(CConsole*,std::wstring);Fn fn=ours?cpCandidate:cpOriginal;if(!autotest::beginInvocation(out,fn))return;fn(console,input);out.callCompleted=1;
 num(player->m_iUnitLevel);num(player->m_experience);num(player->m_fame);num(player->m_iUnusedStatPoints);num(player->m_iUnusedSkillPoints);num(pet->m_iUnitLevel);num(player->m_godMode);num(player->m_cheatMarker);wide(player->m_characterDisplayName);num(f.nativeClient.client->m_startDifficulty);scalar(settings->GetFloat(KSETTINGS_F_ANIMATION_FPS));scalar(camera->m_fUnknown8C);scalar(camera->m_fUnknown38);
 calls.restore();player->m_Followers.clear();delete pet;f.nativeClient.client->m_pPlayer=NULL;f.nativeClient.client->m_level=NULL;nativegame::destroyPlayer(player);resources->m_GameClients.clear();m_pGlobalUnitResourceList=previous;
}
}
TL_TEST(complete_ui_console_dispatch_parameter){Locale locale;tlheadless::Environment env;env.loadGameSkin();CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/WindowsLook.scheme");nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_ui_console_dispatch_parameter",0xaf2540,&side,(sizeof(commands)/sizeof(commands[0]))*3);}
