#include "MenuGuiFixture.h"
#include "FishingMenu.h"
#include "GameVariables.h"
#include <CEGUIInputEvent.h>
TL_ORIGINAL(void,fiCtor,(CFishingMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN12CFishingMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,fiDtor,(CFishingMenu*),"_ZN12CFishingMenuD1Ev")
TL_ORIGINAL(void,fiMap,(CFishingMenu*,CEGUI::Window*),"_ZN12CFishingMenu16mapEventHandlersEPN5CEGUI6WindowE")
TL_ORIGINAL(void,fiCreate,(CFishingMenu*),"_ZN12CFishingMenu11createMenusEv")
TL_ORIGINAL(void,fiUpdate,(CFishingMenu*,float),"_ZN12CFishingMenu6updateEf")
extern "C" void fiNewMap(CFishingMenu*,CEGUI::Window*) __asm__("_ZN12CFishingMenu16mapEventHandlersEPN5CEGUI6WindowE");
extern "C" void fiNewCreate(CFishingMenu*) __asm__("_ZN12CFishingMenu11createMenusEv");
extern "C" void fiNewUpdate(CFishingMenu*,float) __asm__("_ZN12CFishingMenu6updateEf");
TL_FUNCTION(fiCreateHook,"_ZN12CFishingMenu11createMenusEv")
TL_FUNCTION(fiMouse,"_ZN12CFishingMenu14handle_onClickERKN5CEGUI9EventArgsE")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;unsigned clicks,eventKind;CEGUI::Window*first;
void num(unsigned n){output->add(&n,4);}void skip(CFishingMenu*){}bool mouse(CFishingMenu*,const CEGUI::EventArgs&e){const CEGUI::MouseEventArgs&m=static_cast<const CEGUI::MouseEventArgs&>(e);++clicks;num(eventKind);num(m.window==first);num(m.button);return true;}
void snapshot(CEGUI::Window*w){std::string s=tlheadless::snapshot(*w);num(s.size());output->add(s.data(),s.size());}
struct Strings{bool n,w;Strings():n(false),w(false){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14c31a0),8);if(!p){new(reinterpret_cast<void*>(0x14c31a0))std::string;n=true;}std::memcpy(&p,reinterpret_cast<void*>(0x14c31a8),8);if(!p){new(reinterpret_cast<void*>(0x14c31a8))std::wstring;w=true;}}~Strings(){if(w){reinterpret_cast<std::wstring*>(0x14c31a8)->~basic_string();std::memset(reinterpret_cast<void*>(0x14c31a8),0,8);}if(n){reinterpret_cast<std::string*>(0x14c31a0)->~basic_string();std::memset(reinterpret_cast<void*>(0x14c31a0),0,8);}}};
struct Menu{Strings strings;CFishingMenu*p;explicit Menu(menugui::Fixture&f){p=static_cast<CFishingMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CFishingMenu),0,0,0));detour::Set setup;TL_REDIRECT(setup,fiCreateHook,&skip);if(setup.failed())std::abort();fiCtor(p,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);p->m_ring=NULL;}~Menu(){if(p->m_window)CEGUI::WindowManager::getSingleton().destroyWindow(p->m_window);fiDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}};
// These three own-class scalar offsets are the native target's exact movss
// operands b3c8e0/b3c8ee/b3c8fe, on a genuine native-constructed Player.
void fishingValues(CPlayer*p,float time,float phase,float hold){std::memcpy(reinterpret_cast<char*>(p)+0x850,&time,4);std::memcpy(reinterpret_cast<char*>(p)+0x854,&phase,4);std::memcpy(reinterpret_cast<char*>(p)+0x860,&hold,4);}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;unsigned seed=c.index;settings->SetFloat(KSETTINGS_YRATIO,.5f+float(seed%3)*.25f);settings->SetInt(KSETTINGS_RES_WIDTH,800+int(seed%12)*80);settings->SetInt(KSETTINGS_RES_HEIGHT,600+int(seed%7)*30);CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);Menu menu(f);CFishingMenu*p=menu.p;CEGUI::WindowManager&wm=CEGUI::WindowManager::getSingleton();
 if(c.op==0){CEGUI::Window*a=wm.createWindow("GuiLook/StandardButton","first"),*b=wm.createWindow("GuiLook/StandardButton","second");first=a;f.root->addChildWindow(a);if(seed&4)a->addChildWindow(b);else f.root->addChildWindow(b);if(seed&8){CEGUI::Window*branch=wm.createWindow("DefaultWindow","branch");b->addChildWindow(branch);branch->addChildWindow(wm.createWindow("DefaultWindow","leaf"));}a->setProperty("onClick",seed&1?"guiAccept":"");b->setProperty("onClick",seed&2?"guiDecline":"");detour::Set observed;clicks=0;TL_REDIRECT(observed,fiMouse,&mouse);if(observed.failed())std::abort();typedef void(*Fn)(CFishingMenu*,CEGUI::Window*);Fn fn=ours?fiNewMap:fiMap;if(!autotest::beginInvocation(out,fn))return;fn(p,f.root);out.callCompleted=1;CEGUI::Window*all[]={a,b};for(unsigned i=0;i<2;++i){CEGUI::MouseEventArgs e(all[i]);e.button=seed&16?CEGUI::RightButton:CEGUI::LeftButton;eventKind=0;all[i]->fireEvent(CEGUI::Window::EventMouseButtonDown,e);eventKind=1;all[i]->fireEvent(CEGUI::Window::EventMouseDoubleClick,e);}num(clicks);snapshot(f.root);
 }else if(c.op==1){typedef void(*Fn)(CFishingMenu*);Fn fn=ours?fiNewCreate:fiCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;num(p->m_window->getParent()==f.root);num(p->m_ring==p->m_window->getChild("FishingRing"));num(p->m_visible);snapshot(p->m_window);
 }else{fiCreate(p);CPlayer*player=nativegame::createPlayer(&f.resources);const float times[]={0,.5f,1,2},phases[]={-3.1415927f,-1,0,1,1.5707964f,100},holds[]={-.2f,0,.2f};fishingValues(player,times[seed%4],phases[seed/4%6],holds[seed/24%3]);p->m_visible=(seed/72)&1;f.ui->m_pCharacter=seed/144&1?NULL:player;p->m_ring->setPosition(CEGUI::UVector2(CEGUI::UDim(float(seed%4)*.25f,100),CEGUI::UDim(float(seed/4%4)*.25f,-50)));p->m_ring->setSize(CEGUI::UVector2(CEGUI::UDim(.3f,20),CEGUI::UDim(.7f,40)));p->m_ring->setProperty("ImageColours","tl:FF102030 tr:FF102030 bl:FF102030 br:FF102030");typedef void(*Fn)(CFishingMenu*,float);Fn fn=ours?fiNewUpdate:fiUpdate;if(!autotest::beginInvocation(out,fn))return;fn(p,seed&1?.25f:4);out.callCompleted=1;snapshot(p->m_window);f.ui->m_pCharacter=NULL;nativegame::destroyPlayer(player);}
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,op,name,address,&side,count);}
}
TL_TEST(complete_ui_fishing_map){return run(host,0,"complete_ui_fishing_map",0xb3beb0,32);}
TL_TEST(complete_ui_fishing_create){return run(host,1,"complete_ui_fishing_create",0xb3c270,24);}
TL_TEST(complete_ui_fishing_update){return run(host,2,"complete_ui_fishing_update",0xb3c8b0,288);}
