#include "MenuGuiFixture.h"
#include "QuestDialog.h"
#include "TextEvent.h"
#include "GameUITextEventList.h"
#include "GameVariables.h"
#include <limits>
TL_ORIGINAL(void,mgOldDialogUpdate,(CQuestDialogMenu*,float),"_ZN16CQuestDialogMenu6updateEf")
extern "C" void mgNewDialogUpdate(CQuestDialogMenu*,float) __asm__("_ZN16CQuestDialogMenu6updateEf");
TL_ORIGINAL(CTextEvent*,mgTextEvent,(CGameUI*,const Ogre::Vector3&,const std::string&,float,float,CEGUI::colour,CEGUI::colour,bool),"_ZN7CGameUI18getTextEventObjectERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_b")
TL_FUNCTION(mgTextEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(mgAudioLevels,"_ZN13CSoundManager17updateAudioLevelsEffbb")
TL_FUNCTION(mgBaseDialogUpdate,"_ZN13CDropdownMenu6updateEf")
TL_FUNCTION(mgDialogClick,"_ZN16CQuestDialogMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
namespace {
CSettings*settings;Ogre::SceneManager*scene;smallmass::Case*current;autotest::Capture*output;CQuestDialogMenu*menu;
bool editorNotRunning(CResourceManager*){return false;}
void n(unsigned x){output->add(&x,4);}void fp(float x){output->add(&x,4);}
void audio(CSoundManager*p,float sound,float music,bool smute,bool mmute){n(10);n(p==CMasterResourceManager::getSingleton()->m_pSoundManager);fp(sound);fp(music);n(smute);n(mmute);}
void baseUpdate(CDropdownMenu*p,float delta){n(20);n(p==static_cast<CDropdownMenu*>(menu));fp(delta);if(current->index&8)menu->m_bUnknown31=true;}
bool click(CQuestDialogMenu*p,ELayoutFunction id,std::wstring text){n(30);n(p==menu);n(static_cast<unsigned>(id));n(text.size());return true;}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
    current=&c;output=&out;CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);menu=f.dialog;
    CQuestDialog dialog(NULL);gameui_create_detail::TextEventList freeEvents,activeEvents;
    f.ui->m_freeEvents=&freeEvents;f.ui->m_activeEvents=&activeEvents;f.ui->m_rootWindow=f.root;
    // Native create phase SheetState ingame+488, already checked by GCC probes.
    std::memcpy(reinterpret_cast<char*>(f.ui)+0x488,&f.root,sizeof(f.root));
    CTextEvent*text;{detour::Set editor;TL_REDIRECT(editor,mgTextEditor,&editorNotRunning);if(editor.failed())std::abort();text=mgTextEvent(f.ui,Ogre::Vector3(0,0,0),std::string("bootstrap"),1,500,CEGUI::colour(1,1,1,1),CEGUI::colour(0,0,0,1),false);}
    CPlayer*unit=nativegame::createPlayer(&f.resources);unit->setEnabled(false);
    menu->m_declineWindow=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticText","dialog-updating-text");f.root->addChildWindow(menu->m_declineWindow);menu->m_dialogName="Dialog text";menu->m_textIndex=.75f;menu->m_textLength=5;
    menu->m_bUnknown30=(c.index&1)!=0;menu->m_bUnknown31=(c.index&2)!=0;menu->m_unit=c.index&4?unit:NULL;menu->m_dialogActive=(c.index&16)!=0;
    unsigned dialogKind=c.index/4%3;menu->m_dialog=dialogKind?&dialog:NULL;if(dialogKind==2)dialog.m_sSoundName=L"speech";
    float speeds[]={-1,.25f,.5f,1,2,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};menu->m_textSpeed=speeds[c.index/12%7];
    float deltas[]={-1,0,.1f,1,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};float delta=deltas[c.index/84%6];
    unsigned weak=c.index/3%5;if(weak){menu->m_safeOwner.setObject(text);text->m_Value68=weak==1?0:weak==2?250:weak==3?251:std::numeric_limits<float>::quiet_NaN();}
    menu->m_pGameUI->m_mouse.m_Held[0]=(c.index/7%3)==1;menu->m_pGameUI->m_mouse.m_Held[1]=(c.index/7%3)==2;menu->m_pGameUI->m_mouse.m_Pressed[0]=(c.index/11%3)==1;menu->m_pGameUI->m_mouse.m_Pressed[1]=(c.index/11%3)==2;
    settings->SetFloat(KSETTINGS_F_SOUNDVOLUME,.37f);settings->SetFloat(KSETTINGS_F_MUSICVOLUME,.83f);settings->SetInt(KSETTINGS_SOUNDMUTE,c.index&32?1:0);settings->SetInt(KSETTINGS_MUSICMUTE,c.index&64?1:0);
    {detour::Set hooks;TL_REDIRECT(hooks,mgAudioLevels,&audio);TL_REDIRECT(hooks,mgBaseDialogUpdate,&baseUpdate);TL_REDIRECT(hooks,mgDialogClick,&click);if(hooks.failed())std::abort();
     typedef void(*Fn)(CQuestDialogMenu*,float);Fn fn=ours?mgNewDialogUpdate:mgOldDialogUpdate;if(!autotest::beginInvocation(out,fn))return;fn(menu,delta);out.callCompleted=1;}
    n(100);fp(menu->m_textSpeed);fp(menu->m_textIndex);n(menu->m_bUnknown30);n(menu->m_bUnknown31);n(menu->m_unit==unit);n(menu->m_unit==NULL);n(menu->m_dialog==&dialog);n(menu->m_dialog==NULL);n(menu->m_safeOwner.getObject()==text);n(unit->getEnabled());
    std::string snapshot=tlheadless::snapshot(*f.root);n(snapshot.size());out.add(snapshot.data(),snapshot.size());
    menu->m_unit=NULL;menu->m_dialog=NULL;menu->m_safeOwner.setObject(NULL);nativegame::destroyPlayer(unit);
}
}
TL_TEST(complete_menu_dialog_update_real_owners){
    tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_menu_dialog_update_real_owners",0xbb0140,&side,504);
}
