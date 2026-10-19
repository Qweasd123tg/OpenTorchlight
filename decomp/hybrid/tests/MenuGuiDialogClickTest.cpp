#include "MenuQuestWorld.h"
#include "SteamStats.h"
#include "iMenuListener.h"
#include "GameVariables.h"
#include "tests/FinishLevelFixture.h"
TL_ORIGINAL(bool,mgOldDialogClick,(CQuestDialogMenu*,ELayoutFunction,std::wstring),"_ZN16CQuestDialogMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
extern "C" bool mgNewDialogClick(CQuestDialogMenu*,ELayoutFunction,std::wstring) __asm__("_ZN16CQuestDialogMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(mgClickModal,"_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b")
TL_FUNCTION(mgClickGive,"_ZN13CQuestManager9giveQuestEP6CQuestP9CBaseUnitb")
TL_FUNCTION(mgClickComplete,"_ZN13CQuestManager13completeQuestEP6CQuest")
TL_FUNCTION(mgClickBroadcast,"_ZN17CEditorBaseObject14BroadcastEventEj")
TL_FUNCTION(mgClickStop,"_ZN12CQuestDialog15stopDialogSoundEv")
TL_FUNCTION(mgClickStats,"_ZN11CSteamStats13incrementStatE6ESTATSi")
TL_FUNCTION(mgClickInteractive,"_ZN7CGameUI25setInteractiveMenuVisibleEb")
TL_FUNCTION(mgClickNPCIcons,"_ZN6CLevel14updateNPCIconsEv")
TL_FUNCTION(mgClickMapIcons,"_ZN6CLevel18updateAutomapIconsEv")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;menugui::Fixture*fixture;menugui::QuestWorld*world;CPlayer*npc;CSteamStats*stats;CQuest*target;CLevel*level;unsigned scenario;
void n(unsigned x){output->add(&x,4);}void wide(const std::wstring&s){n(s.size());output->add(s.data(),s.size()*4);}
void modal(CGameUI*p,std::wstring a,std::wstring b,bool close){n(10);n(p==fixture->ui);wide(a);wide(b);n(close);}
long long give(CQuestManager*p,CQuest*q,CBaseUnit*u,bool yes){n(11);n(p==world->manager);n(q==target);n(u==npc);n(yes);q->m_questAccepted=true;if(scenario==7)fixture->dialog->m_dialog=NULL;return 1;}
long long complete(CQuestManager*p,CQuest*q){n(12);n(p==world->manager);n(q==target);q->m_complete=true;if(scenario==7)fixture->dialog->m_dialog=NULL;return 1;}
void broadcast(CEditorBaseObject*p,unsigned id){n(13);n(p==static_cast<CEditorBaseObject*>(npc));n(id);}
void stop(CQuestDialog*p){n(20);n(p==target->m_pQuestDialog);}
void stat(CSteamStats*p,ESTATS id,int amount){n(14);n(p==stats);n(id);n(amount);}
void interactive(CGameUI*p,bool yes){n(15);n(p==fixture->ui);n(yes);}
void npcIcons(CLevel*p){n(16);n(p==level);}void mapIcons(CLevel*p){n(17);n(p==level);}
struct Listener: iMenuListener {
    virtual void menuEventOccured(void*p,EMENU_TYPE type,EMENU_EVENT event){n(18);n(p==fixture->dialog);n(type);n(event);}
};
struct Stats {long previous;CSteamStats*value;Stats():previous(m_gStatsObject),value(new CSteamStats){stats=value;}~Stats(){delete value;m_gStatsObject=previous;}};
struct Windows {CEGUI::Window*base;Windows(menugui::Fixture&f,bool open){base=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","click-dialog-base");CEGUI::Window*content=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","click-dialog-content");base->addChildWindow(content);f.dialog->m_pUnknown10=f.root;f.dialog->m_pUnknown18=base;f.dialog->m_pUnknown20=content;f.dialog->m_bUnknown30=open;if(open)f.root->addChildWindow(base);}~Windows(){CEGUI::WindowManager::getSingleton().destroyWindow(base);}};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
    output=&out;CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);fixture=&f;menugui::QuestWorld graph(f);world=&graph;Stats statsScope;Windows windows(f,c.index&1);finishlevel::Fixture levelFixture;level=&levelFixture.level;
    npc=nativegame::createPlayer(&f.resources);const wchar_t*names[]={L"Male1",L"Gar",L"Other",L""};unsigned unitMode=c.index/192%4;npc->m_sName=names[unitMode];
    scenario=c.index/6%8;const int types[]={0,1,2,3,4,1,1,3};unsigned count=c.index/48%4;const unsigned counts[]={0,5,6,7};
    for(unsigned i=0;i<counts[count];++i)graph.add(L"Active",(i==0&&scenario==5)?L"":L"Visible details");
    target=graph.add(L"Clicked",scenario==4?L"":L"Quest details");graph.manager->m_Unknown18.remove(target);
    target->m_bUnknown28=scenario==6;target->m_questAccepted=scenario==2;target->m_pQuestDialog->m_iDialogType=types[scenario];target->m_pQuestDialog->m_bDialogInitialized=true;
    f.dialog->m_dialog=scenario==0?NULL:target->m_pQuestDialog;f.dialog->m_unit=unitMode==3?NULL:npc;f.dialog->m_dialogActive=(c.index&2)!=0;f.dialog->m_resultBroadcast=(c.index&4)!=0;
    CRunicCore weakOwner;if(scenario&1)f.dialog->m_safeOwner.setObject(&weakOwner);
    graph.player->m_targetCharacter.setObject(npc);graph.player->m_targetLocked=false;graph.player->m_bBaseUnitFlag0=false;graph.player->m_eAIState=static_cast<EAIState>(0);
    f.resources.m_pLevel=scenario>=4?level:NULL;Listener listener;f.dialog->addMenuListener(&listener);
    bool result=false;
    {detour::Set hooks;TL_REDIRECT(hooks,mgClickModal,&modal);TL_REDIRECT(hooks,mgClickGive,&give);TL_REDIRECT(hooks,mgClickComplete,&complete);TL_REDIRECT(hooks,mgClickBroadcast,&broadcast);TL_REDIRECT(hooks,mgClickStats,&stat);TL_REDIRECT(hooks,mgClickStop,&stop);TL_REDIRECT(hooks,mgClickInteractive,&interactive);TL_REDIRECT(hooks,mgClickNPCIcons,&npcIcons);TL_REDIRECT(hooks,mgClickMapIcons,&mapIcons);if(hooks.failed())std::abort();
    const int functions[]={8,9,10,0,-1,2147483647};typedef bool(*Fn)(CQuestDialogMenu*,ELayoutFunction,std::wstring);Fn fn=ours?mgNewDialogClick:mgOldDialogClick;if(!autotest::beginInvocation(out,fn))return;result=fn(f.dialog,static_cast<ELayoutFunction>(functions[c.index%6]),L"payload");out.callCompleted=1;}
    n(100);n(result);n(f.dialog->m_unit==NULL);n(f.dialog->m_dialog==NULL);n(f.dialog->m_bUnknown30);n(f.dialog->m_bUnknown31);n(f.dialog->m_bUnknown32);n(f.dialog->m_resultBroadcast);n(target->m_questAccepted);n(target->m_complete);n(target->m_pQuestDialog->m_bItemsGiven);n(target->m_pQuestDialog->m_bDialogInitialized);n(npc->getEnabled());n(graph.player->m_eAIState);n(graph.player->m_targetCharacter.getObject()==NULL);n(windows.base->getParent()==f.root);
    f.dialog->removeMenuListener(&listener);f.dialog->m_safeOwner.setObject(NULL);f.resources.m_pLevel=NULL;nativegame::destroyPlayer(npc);
}
}
TL_TEST(complete_menu_dialog_click_real_graph){tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_menu_dialog_click_real_graph",0xbafab0,&side,768);}
