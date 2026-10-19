#include "MenuGuiFixture.h"
#include <limits>
TL_ORIGINAL(void,mgOldMap,(CQuestMenu*,CEGUI::Window*),"_ZN10CQuestMenu16mapEventHandlersEPN5CEGUI6WindowE")
extern "C" void mgNewMap(CQuestMenu*,CEGUI::Window*) __asm__("_ZN10CQuestMenu16mapEventHandlersEPN5CEGUI6WindowE");
TL_ORIGINAL(void,mgOldText,(CQuestDialogMenu*,float),"_ZN16CQuestDialogMenu17updateTextDisplayEf")
extern "C" void mgNewText(CQuestDialogMenu*,float) __asm__("_ZN16CQuestDialogMenu17updateTextDisplayEf");
TL_FUNCTION(mgOnClick,"_ZN10CQuestMenu7onClickE15ELayoutFunction")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;unsigned clicked;
bool clickedHandler(CQuestMenu*,ELayoutFunction id){++clicked;output->add(&id,sizeof(id));return true;}
void snapshot(autotest::Capture&out,CEGUI::Window*w){std::string text=tlheadless::snapshot(*w);unsigned n=text.size();out.add(&n,4);out.add(text.data(),n);}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
    output=&out;clicked=0;CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);CRunicCore blocker;
    CEGUI::WindowManager&wm=CEGUI::WindowManager::getSingleton();
    if(c.op==0){
        CEGUI::Window*a=wm.createWindow("GuiLook/StandardButton","a"),*b=wm.createWindow("GuiLook/StandardButton","b");
        unsigned shape=c.index/4%6;
        if(shape==0){f.root->addChildWindow(a);f.root->addChildWindow(b);}
        else if(shape==1){f.root->addChildWindow(a);a->addChildWindow(b);}
        else if(shape==2){CEGUI::Window*branch=wm.createWindow("DefaultWindow","branch");f.root->addChildWindow(branch);branch->addChildWindow(a);a->addChildWindow(b);}
        else if(shape==3){f.root->addChildWindow(a);f.root->addChildWindow(b);for(unsigned i=0;i<3;++i){char name[20];std::sprintf(name,"empty-%u",i);a->addChildWindow(wm.createWindow("DefaultWindow",name));}}
        else if(shape==4){CEGUI::Window*branch=wm.createWindow("DefaultWindow","branch");f.root->addChildWindow(branch);branch->addChildWindow(a);branch->addChildWindow(b);branch->addChildWindow(wm.createWindow("DefaultWindow","leaf"));}
        else {f.root->addChildWindow(a);CEGUI::Window*branch=wm.createWindow("DefaultWindow","branch");a->addChildWindow(branch);branch->addChildWindow(b);f.root->addChildWindow(wm.createWindow("DefaultWindow","empty"));}
        a->setProperty("onClick",c.index&1?"guiAccept":"");b->setProperty("onClick",c.index&2?"guiDecline":"");
        ELayoutFunction ids[]={static_cast<ELayoutFunction>(8),static_cast<ELayoutFunction>(9)};a->setUserData(&ids[0]);b->setUserData(&ids[1]);
        detour::Set hooks;TL_REDIRECT(hooks,mgOnClick,&clickedHandler);if(hooks.failed())std::abort();
        typedef void(*Fn)(CQuestMenu*,CEGUI::Window*);Fn fn=ours?mgNewMap:mgOldMap;if(!autotest::beginInvocation(out,fn))return;fn(f.quest,f.root);out.callCompleted=1;
        CEGUI::Window*all[]={a,b};for(unsigned i=0;i<2;++i){CEGUI::MouseEventArgs args(all[i]);args.button=c.index/24%2?CEGUI::RightButton:CEGUI::LeftButton;all[i]->fireEvent(CEGUI::Window::EventMouseButtonDown,args);all[i]->fireEvent(CEGUI::Window::EventMouseDoubleClick,args);}
        out.add(&clicked,4);snapshot(out,f.root);
    }else{
        CEGUI::Window*parent=wm.createWindow("DefaultWindow","text-parent"),*text=wm.createWindow("GuiLook/StaticText","text");f.root->addChildWindow(parent);parent->addChildWindow(text);parent->setSize(CEGUI::UVector2(CEGUI::UDim(0,300),CEGUI::UDim(0,120)));
        f.dialog->m_declineWindow=text;const char*names[]={"","ASCII","\320\242\320\265\320\272\321\201\321\202","longer dialog text"};f.dialog->m_dialogName=names[c.index%4];text->setText(c.index&4?f.dialog->m_dialogName.c_str():"old");
        const float durations[]={0,1,5,-1,std::numeric_limits<float>::quiet_NaN()};f.dialog->m_textLength=durations[(c.index/8)%5];f.dialog->m_textIndex=float((c.index/40)%3)*2.0f;
        if(c.index>=120)f.dialog->m_safeOwner.setObject(&blocker);
        float delta=c.index&1?0.25f:7.0f;typedef void(*Fn)(CQuestDialogMenu*,float);Fn fn=ours?mgNewText:mgOldText;if(!autotest::beginInvocation(out,fn))return;fn(f.dialog,delta);out.callCompleted=1;out.add(&f.dialog->m_textIndex,4);snapshot(out,f.root);
    }
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=services.master?services.master->m_pSettings:CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,op,name,address,&side,count);}
}
TL_TEST(complete_menu_map_real_cegui){return run(host,0,"complete_menu_map_real_cegui",0xbc28c0,48);}
TL_TEST(complete_menu_text_real_cegui){return run(host,1,"complete_menu_text_real_cegui",0xbae6f0,240);}
