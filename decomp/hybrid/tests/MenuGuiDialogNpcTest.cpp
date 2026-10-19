#include "MenuQuestWorld.h"
#include <clocale>
#include "SteamStats.h"
#include "GameVariables.h"
#include "TextEvent.h"
#include "GameUITextEventList.h"
#include "iMenuListener.h"
TL_ORIGINAL(void,mgNPCDialogCreate,(CQuestDialogMenu*),"_ZN16CQuestDialogMenu11createMenusEv")
TL_ORIGINAL(void,mgOldDialogNPC,(CQuestDialogMenu*,CBaseUnit*,bool,CQuest*),"_ZN16CQuestDialogMenu6setNPCEP9CBaseUnitbP6CQuest")
extern "C" void mgNewDialogNPC(CQuestDialogMenu*,CBaseUnit*,bool,CQuest*) __asm__("_ZN16CQuestDialogMenu6setNPCEP9CBaseUnitbP6CQuest");
TL_FUNCTION(mgNPCSelect,"_ZN6CQuest14getQuestDialogEP9CBaseUnit")
TL_FUNCTION(mgNPCDialogs,"_ZN13CQuestManager16getDialogsForNPCER10TArrayListIP12CQuestDialogEP9CBaseUnitb")
TL_FUNCTION(mgNPCDragged,"_ZN7CGameUI17returnDraggedItemEv")
TL_FUNCTION(mgNPCPlay,"_ZN12CQuestDialog15playDialogSoundEv")
TL_FUNCTION(mgNPCStop,"_ZN12CQuestDialog15stopDialogSoundEv")
TL_FUNCTION(mgNPCStats,"_ZN11CSteamStats13incrementStatE6ESTATSi")
TL_FUNCTION(mgNPCInteractive,"_ZN7CGameUI25setInteractiveMenuVisibleEb")
TL_FUNCTION(mgNPCBroadcast,"_ZN17CEditorBaseObject14BroadcastEventEj")
TL_FUNCTION(mgNPCEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;menugui::Fixture*fixture;menugui::QuestWorld*world;CPlayer*npc;CPlayer*previous;CQuest*target;CQuest*prior;CSteamStats*stats;unsigned selection;
void n(unsigned x){output->add(&x,4);}void fp(float x){output->add(&x,4);}void bytes(const std::string&s){n(s.size());output->add(s.data(),s.size());}
long long selected(CQuest*p,CBaseUnit*u){n(10);n(p==target);n(u==npc);return selection==0?reinterpret_cast<long long>(target->m_pQuestDialog):0;}
void dialogs(CQuestManager*p,TArrayList<CQuestDialog*>&list,CBaseUnit*u,bool retry){n(11);n(p==world->manager);n(u==npc);n(retry);n(list.size());if(selection!=3){list.add(target->m_pQuestDialog);if(selection==2)list.add(prior->m_pQuestDialog);}}
void dragged(CGameUI*p){n(12);n(p==fixture->ui);}
void play(CQuestDialog*p){n(13);n(p==target->m_pQuestDialog);}
void stop(CQuestDialog*p){n(14);n(p==prior->m_pQuestDialog);n(p==target->m_pQuestDialog);}
void stat(CSteamStats*p,ESTATS id,int amount){n(15);n(p==stats);n(id);n(amount);}
void interactive(CGameUI*p,bool yes){n(16);n(p==fixture->ui);n(yes);}
void broadcast(CEditorBaseObject*p,unsigned id){n(17);n(p==static_cast<CEditorBaseObject*>(npc));n(id);}
bool notEditor(CResourceManager*p){n(18);n(p==&fixture->resources);return false;}
struct Listener: iMenuListener {virtual void menuEventOccured(void*p,EMENU_TYPE type,EMENU_EVENT event){n(19);n(p==fixture->dialog);n(type);n(event);}};
struct Stats {long old;CSteamStats*value;Stats():old(m_gStatsObject),value(new CSteamStats){stats=value;}~Stats(){delete value;m_gStatsObject=old;}};
struct Windows {CEGUI::Window*base;Windows(menugui::Fixture&f){base=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","npc-dialog-base");CEGUI::Window*content=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","npc-dialog-content");base->addChildWindow(content);f.dialog->m_pUnknown10=f.root;f.dialog->m_pUnknown18=base;f.dialog->m_pUnknown20=content;f.dialog->m_bUnknown30=false;mgNPCDialogCreate(f.dialog);}~Windows(){CEGUI::WindowManager::getSingleton().destroyWindow(base);}};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
    output=&out;CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);fixture=&f;
    CDataGroup group(L"NPC",NULL,4,4,NULL),itemGroup(L"REWARD",NULL,4,4,NULL);itemGroup.AddDataValue(L"ICON",std::wstring(L"iconhelm"),false);
    menugui::QuestWorld graph(f);world=&graph;Stats statsScope;Windows windows(f);
    gameui_create_detail::TextEventList freeEvents,activeEvents;f.ui->m_freeEvents=&freeEvents;f.ui->m_activeEvents=&activeEvents;f.ui->m_rootWindow=f.root;std::memcpy(reinterpret_cast<char*>(f.ui)+0x488,&f.root,sizeof(f.root));
    f.ui->m_itemImagesets.add(CEGUI::ImagesetManager::getSingleton().getImageset("UIIcons"));
    unsigned type=c.index%6;selection=c.index/6%4;unsigned profile=c.index/24%20;unsigned portrait=profile%3;if(portrait)group.AddDataValue(L"PORTRAIT",portrait==1?std::wstring(L"iconhelm"):std::wstring(L"absent-menu-portrait"),false);
    npc=nativegame::createPlayer(&f.resources);previous=nativegame::createPlayer(&f.resources);npc->m_pDataGroup=&group;npc->m_sName=profile&1?L"Horse":L"NPC";npc->m_bBaseUnitFlag0=false;npc->m_targetLocked=false;npc->m_eAIState=static_cast<EAIState>(0);npc->setEnabled((profile&2)!=0);previous->setEnabled(false);
    const std::wstring texts[]={L"",L"Short dialog",L"Квест Ω / UTF8",std::wstring(400,L'a')};target=graph.add(L"Quest",texts[profile%4]);prior=graph.add(L"Previous",L"previous text");
    target->m_bUnknown28=(profile&4)!=0;target->m_pQuestDialog->m_iDialogType=type;target->m_pQuestDialog->m_bFloatyText=(profile&8)!=0;target->m_pQuestDialog->m_bLookAtPlayer=(profile&1)!=0;
    target->m_pQuestRewards->m_fGold=profile&1?91:0;target->m_pQuestRewards->m_fExperience=profile&2?137:0;target->m_pQuestRewards->m_fFame=profile&4?23:0;
    for(unsigned i=0;i<profile%5;++i){CEquipment*item=new CEquipment(&f.resources);item->m_pDataGroup=&itemGroup;item->m_bUnknown348=true;item->m_iUnknown238=i+1;target->m_pQuestRewards->m_rewardItems.add(item);}
    f.dialog->m_unit=previous;f.dialog->m_dialogActive=(profile&1)!=0;f.dialog->m_dialog=prior->m_pQuestDialog;f.dialog->m_bUnknown32=true;f.dialog->m_resultBroadcast=true;
    CRunicCore weak;f.dialog->m_safeOwner.setObject(&weak);Listener listener;f.dialog->addMenuListener(&listener);
    // Missing widget early return remains a valid native domain with unit NULL.
    CEGUI::Window*savedPrompt=f.dialog->m_promptWindow;CEGUI::Window*savedAccept=f.dialog->m_acceptWindow;CEGUI::Window*savedDialog=f.dialog->m_dialogWindow;
    if(profile==15)f.dialog->m_promptWindow=NULL;
    if(profile==16)f.dialog->m_acceptWindow=NULL;
    if(profile==17)f.dialog->m_dialogWindow=NULL;
    if(profile==18)target->m_pQuestDialog->m_pQuest=NULL;
    {detour::Set hooks;TL_REDIRECT(hooks,mgNPCSelect,&selected);TL_REDIRECT(hooks,mgNPCDialogs,&dialogs);TL_REDIRECT(hooks,mgNPCDragged,&dragged);TL_REDIRECT(hooks,mgNPCPlay,&play);TL_REDIRECT(hooks,mgNPCStop,&stop);TL_REDIRECT(hooks,mgNPCStats,&stat);TL_REDIRECT(hooks,mgNPCInteractive,&interactive);TL_REDIRECT(hooks,mgNPCBroadcast,&broadcast);TL_REDIRECT(hooks,mgNPCEditor,&notEditor);if(hooks.failed())std::abort();
    typedef void(*Fn)(CQuestDialogMenu*,CBaseUnit*,bool,CQuest*);Fn fn=ours?mgNewDialogNPC:mgOldDialogNPC;if(!autotest::beginInvocation(out,fn))return;fn(f.dialog,profile==15?NULL:npc,(profile&4)!=0,selection==1?NULL:target);out.callCompleted=1;}
    n(100);n(f.dialog->m_unit==npc);n(f.dialog->m_unit==NULL);n(f.dialog->m_dialog==target->m_pQuestDialog);n(f.dialog->m_dialog==NULL);n(f.dialog->m_bUnknown30);n(f.dialog->m_bUnknown31);n(f.dialog->m_bUnknown32);n(f.dialog->m_acceptOnExit);n(f.dialog->m_dialogActive);n(npc->getEnabled());n(previous->getEnabled());n(npc->m_targetCharacter.getObject()==graph.player);n(target->m_pQuestDialog->m_bDialogInitialized);n(target->m_pQuestDialog->m_bItemsGiven);n(f.dialog->m_displayedCharacters);fp(f.dialog->m_textIndex);fp(f.dialog->m_textLength);bytes(f.dialog->m_dialogName);n(f.dialog->m_safeOwner.getObject()==&weak);
    unsigned events=0;for(TLinkedListNode<CTextEvent*>*p=activeEvents.head;p;p=p->m_pNext){if(++events>4)std::abort();CTextEvent*t=p->m_Data;n(f.dialog->m_safeOwner.getObject()==t);bytes(t->m_Text);fp(t->m_Value10);fp(t->m_Value14);fp(t->m_Value18);fp(t->m_Value60);fp(t->m_Value64);fp(t->m_Value68);}n(events);
    std::string snapshot=tlheadless::snapshot(*f.root);bytes(snapshot);if(windows.base->getParent()!=f.root){std::string detached=tlheadless::snapshot(*windows.base);bytes(detached);}else bytes(std::string());
    f.dialog->m_promptWindow=savedPrompt;f.dialog->m_acceptWindow=savedAccept;f.dialog->m_dialogWindow=savedDialog;target->m_pQuestDialog->m_pQuest=target;f.dialog->m_safeOwner.setObject(NULL);f.dialog->removeMenuListener(&listener);f.dialog->m_unit=NULL;nativegame::destroyPlayer(npc);nativegame::destroyPlayer(previous);
}
}
TL_TEST(complete_menu_dialog_npc_real_graph){if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_menu_dialog_npc_real_graph",0xbb70b0,&side,480);}
