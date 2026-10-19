#include "FinishLevelFixture.h"
#include "NativeConsoleFixture.h"
#include "ConsoleData.h"
#include "MenuQuestWorld.h"
#include "StringUtilities.h"
#include "UnitResourceList.h"
#include "Monster.h"
#include "Skill.h"
#include "SettingsVariables.h"
#include <elements/CEGUIMultiLineEditbox.h>
#include <clocale>
TL_ORIGINAL(void,cqOriginal,(CConsole*,std::wstring),"_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE")
extern "C" void cqCandidate(CConsole*,std::wstring) __asm__("_ZN8CConsole18executeCommandLineESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(cqLog,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cqLookup,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cqType,"_ZN16CResourceManager17getUnitTypeByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cqMasterList,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(cqUiVisible,"_ZN7CGameUI18setIngameUIVisibleEb")
TL_FUNCTION(cqFps,"_ZN7CGameUI9toggleFPSEv")
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
TL_FUNCTION(cqNames,"_ZN13CQuestManager13getQuestNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(cqQuest,"_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cqGive,"_ZN13CQuestManager9giveQuestEP6CQuestP9CBaseUnitb")
TL_FUNCTION(cqComplete,"_ZN13CQuestManager13completeQuestEP6CQuest")
TL_FUNCTION(cqReset,"_ZN13CQuestManager10resetQuestEP6CQuest")
TL_FUNCTION(cqUpdate,"_ZN13CQuestManager6updateEf")
menugui::QuestWorld*quests;unsigned profile;
unsigned identity(CQuest*q){for(unsigned i=0;i<quests->quests.size();++i)if(quests->quests[i]==q)return i+1;return 0;}
void snapshot(CQuest*q){num(q->m_complete);num(q->m_questAccepted);num(q->m_pQuestDialog->m_bDialogInitialized);num(q->m_acceptDialogs.size());for(unsigned i=0;i<q->m_acceptDialogs.size();++i)num(q->m_acceptDialogs[i]->m_bDialogInitialized);}
void names(CQuestManager*p,TArrayList<std::wstring>&out){num(20);num(p==quests->manager);num(p==CQuestManager::getSingleton());for(unsigned i=0;i<quests->quests.size();++i)if(i<=profile%4)out.add(quests->quests[i]->m_sUnknown58);}
CQuest* lookupQuest(CQuestManager*p,const std::wstring&name){num(21);num(p==CQuestManager::getSingleton());wide(name);if(profile&4)return NULL;for(unsigned i=0;i<quests->quests.size();++i){std::wstring expected=STRINGS::StringUpper(quests->quests[i]->m_sUnknown58);if(name==expected)return quests->quests[i];}return NULL;}
long long give(CQuestManager*p,CQuest*q,CBaseUnit*unit,bool active){num(22);num(p==quests->manager);num(identity(q));num(unit==NULL);num(active);return 0;}
long long complete(CQuestManager*p,CQuest*q){num(23);num(p==quests->manager);num(identity(q));snapshot(q);return 0;}
void reset(CQuestManager*p,CQuest*q){num(24);num(p==quests->manager);num(identity(q));q->m_complete=false;q->m_questAccepted=false;}
void update(CQuestManager*p,float delta){num(25);num(p==quests->manager);output->add(&delta,4);for(unsigned i=0;i<quests->quests.size();++i){snapshot(quests->quests[i]);}}
const wchar_t*commands[]={L"QUESTS",L"QUESTCOMPLETE introquest",L"QUESTCOMPLETE CRYPTQUESTPT2",L"QUESTCOMPLETE 0",L"QUESTCOMPLETE 1",L"QUESTCOMPLETE 9",L"QUESTCOMPLETE 99",L"QUESTCOMPLETE missing",L"QUESTACTIVE ruinspt1",L"QUESTACTIVE 0",L"QUESTACTIVE 2",L"QUESTACTIVE 9",L"QUESTACTIVE missing",L"QUESTRESET INTROQUEST",L"QUESTRESET introquest",L"QUESTRESET 0",L"QUESTRESET 99",L"QUESTRESET missing",L"QUESTSTRATA1",L"QUESTSTRATA2",L"QUESTSTRATA3",L"QUESTSTRATA4",L"QUESTSTRATA5",L"QUESTSTRATA",L"QUESTSTRATA0",L"questcomplete IntroQuest",L"questactive Квест",L"QUESTCOMPLETE -1",L"QUESTCOMPLETE 01",L"QUESTCOMPLETE IntroQuest,extra",L"QUESTRESET Квест"};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;unsigned count=sizeof(commands)/sizeof(commands[0]);profile=c.index/count;CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);resources=&f.resources;menugui::Console owner(f);console=owner.p;ui=f.ui;menugui::QuestWorld world(f);quests=&world;player=world.player;const wchar_t*questNames[]={L"IntroQuest",L"CryptQuestPt2",L"ruinsPt1",L"Квест"};for(unsigned i=0;i<4;++i){CQuest*q=world.add(questNames[i],L"native owned dialog");q->m_complete=(profile+i)&1;q->m_questAccepted=(profile+i)&2;q->m_pQuestDialog->m_bDialogInitialized=(profile+i)&1;for(unsigned j=0;j<2;++j){CQuestDialog*d=new CQuestDialog(q);d->m_bDialogInitialized=(profile+i+j)&1;q->m_acceptDialogs.add(d);}}player->m_cheatMarker=profile%4==1?214:profile%4;player->m_characterDisplayName=profile&1?L"The Cheat":L"Тест 漢字";
 CUnitResourceList*previous=CUnitResourceList::getSingleton();CUnitResourceList list;unitlist=&list;m_pGlobalUnitResourceList=unitlist;
 detour::Set calls;TL_REDIRECT(calls,cqLog,&log);TL_REDIRECT(calls,cqLookup,&lookup);TL_REDIRECT(calls,cqType,&type);TL_REDIRECT(calls,cqMasterList,&masterList);TL_REDIRECT(calls,cqNames,&names);TL_REDIRECT(calls,cqQuest,&lookupQuest);TL_REDIRECT(calls,cqGive,&give);TL_REDIRECT(calls,cqComplete,&complete);TL_REDIRECT(calls,cqReset,&reset);TL_REDIRECT(calls,cqUpdate,&update);if(calls.failed())std::abort();typedef void(*Fn)(CConsole*,std::wstring);Fn fn=ours?cqCandidate:cqOriginal;if(!autotest::beginInvocation(out,fn))return;fn(console,commands[c.index%count]);out.callCompleted=1;
 num(player->m_cheatMarker);wide(player->m_characterDisplayName);for(unsigned i=0;i<4;++i){snapshot(world.quests[i]);}calls.restore();m_pGlobalUnitResourceList=previous;
}
}
TL_TEST(complete_ui_console_dispatch_quest){Locale locale;tlheadless::Environment env;env.loadGameSkin();CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/WindowsLook.scheme");nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_ui_console_dispatch_quest",0xaf2540,&side,(sizeof(commands)/sizeof(commands[0]))*8);}
