#include "MenuGuiFixture.h"
#include "MenuModelGpuBoundary.h"
#include "GameVariables.h"
#include "Equipment.h"
#include <OgreEntity.h>
TL_ORIGINAL(void,uiDropCtor,(CDropdownMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*,unsigned),"_ZN13CDropdownMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManagerj")
TL_ORIGINAL(void,uiDropDtor,(CDropdownMenu*),"_ZN13CDropdownMenuD1Ev")
TL_ORIGINAL(void,uiDropCreate,(CDropdownMenu*),"_ZN13CDropdownMenu11createMenusEv")
TL_ORIGINAL(void,uiDropMap,(CDropdownMenu*,CEGUI::Window*),"_ZN13CDropdownMenu16mapEventHandlersEPN5CEGUI6WindowE")
TL_ORIGINAL(void,uiDropTitle,(CDropdownMenu*,const std::wstring&),"_ZN13CDropdownMenu8setTitleERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,uiDropOpen,(CDropdownMenu*,bool),"_ZN13CDropdownMenu7setOpenEb")
TL_ORIGINAL(void,uiDropUpdate,(CDropdownMenu*,float),"_ZN13CDropdownMenu6updateEf")
extern "C" void uiNewCreate(CDropdownMenu*) __asm__("_ZN13CDropdownMenu11createMenusEv");
extern "C" void uiNewMap(CDropdownMenu*,CEGUI::Window*) __asm__("_ZN13CDropdownMenu16mapEventHandlersEPN5CEGUI6WindowE");
extern "C" void uiNewTitle(CDropdownMenu*,const std::wstring&) __asm__("_ZN13CDropdownMenu8setTitleERKSbIwSt11char_traitsIwESaIwEE");
extern "C" void uiNewOpen(CDropdownMenu*,bool) __asm__("_ZN13CDropdownMenu7setOpenEb");
extern "C" void uiNewUpdate(CDropdownMenu*,float) __asm__("_ZN13CDropdownMenu6updateEf");
TL_FUNCTION(uiDropMouse,"_ZN13CDropdownMenu14handle_onClickERKN5CEGUI9EventArgsE")
TL_FUNCTION(uiDropDouble,"_ZN13CDropdownMenu20handle_onDoubleClickERKN5CEGUI9EventArgsE")
TL_FUNCTION(uiDropSound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
namespace {
CSettings* settings;Ogre::SceneManager* scene;autotest::Capture* output;unsigned clicks,doubles;
bool mouse(CDropdownMenu*,const CEGUI::EventArgs&){++clicks;return true;}
bool twice(CDropdownMenu*,const CEGUI::EventArgs&){++doubles;return true;}
int sound(CSoundBank*p,int id,Ogre::SceneNode*n,float a,float b,bool c){unsigned v[]={p!=NULL,unsigned(id),n!=NULL,c};output->add(v,sizeof(v));output->add(&a,4);output->add(&b,4);return 0;}
void snapshot(autotest::Capture&out,CEGUI::Window*w){std::string s=tlheadless::snapshot(*w);unsigned n=s.size();out.add(&n,4);out.add(s.data(),n);}
struct Drop {
 CDropdownMenu* p;
 explicit Drop(menugui::Fixture&f,unsigned flags){p=static_cast<CDropdownMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CDropdownMenu),0,0,0));detour::Set setup;TL_REDIRECT(setup,mgDropdownCreate,&menugui::skipDropdown);if(setup.failed())std::abort();uiDropCtor(p,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources,flags);}
 ~Drop(){uiDropDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}
};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;clicks=doubles=0;unsigned profile=c.index%3;int widths[]={800,1280,1920},heights[]={600,720,1080};settings->SetInt(KSETTINGS_RES_WIDTH,c.op==4?800+int(c.index)*13:widths[profile]);settings->SetInt(KSETTINGS_RES_HEIGHT,c.op==4?600+int(c.index)*7:heights[profile]);
 CStringTranslate translate(L"");menugui::ModelGpuBoundary gpu;menugui::Fixture f(*settings,scene);Drop drop(f,c.op>=2&&!(c.index&1)?0:1);CDropdownMenu*p=drop.p;CEGUI::WindowManager&wm=CEGUI::WindowManager::getSingleton();
 if(c.op==0){
  CEGUI::Window*a=wm.createWindow("GuiLook/StandardButton","a"),*b=wm.createWindow("GuiLook/StandardButton","b");f.root->addChildWindow(a);if(c.index&4)a->addChildWindow(b);else f.root->addChildWindow(b);
  if(c.index&8){CEGUI::Window*branch=wm.createWindow("DefaultWindow","branch");b->addChildWindow(branch);branch->addChildWindow(wm.createWindow("DefaultWindow","leaf"));}
  a->setProperty("onClick",c.index&1?"guiAccept":"");b->setProperty("onClick",c.index&2?"guiDecline":"");
  detour::Set observed;TL_REDIRECT(observed,uiDropMouse,&mouse);TL_REDIRECT(observed,uiDropDouble,&twice);if(observed.failed())std::abort();typedef void(*Fn)(CDropdownMenu*,CEGUI::Window*);Fn fn=ours?uiNewMap:uiDropMap;if(!autotest::beginInvocation(out,fn))return;fn(p,f.root);out.callCompleted=1;
  CEGUI::Window*all[]={a,b};for(unsigned i=0;i<2;++i){CEGUI::MouseEventArgs e(all[i]);e.button=c.index&16?CEGUI::RightButton:CEGUI::LeftButton;all[i]->fireEvent(CEGUI::Window::EventMouseButtonDown,e);all[i]->fireEvent(CEGUI::Window::EventMouseDoubleClick,e);}out.add(&clicks,4);out.add(&doubles,4);snapshot(out,f.root);
 }else if(c.op==1){
  const wchar_t* texts[]={L"",L"plain",L"Задание",L"漢字",L"emoji \U0001F525",L"line\nnext"};std::wstring title=texts[c.index%6];CEGUI::Window*w=wm.createWindow("GuiLook/StaticText","title");f.root->addChildWindow(w);w->setText(c.index&2?"before":"old");p->m_iUnknown50=(c.index/6)&1?w:NULL;typedef void(*Fn)(CDropdownMenu*,const std::wstring&);Fn fn=ours?uiNewTitle:uiDropTitle;if(!autotest::beginInvocation(out,fn))return;fn(p,title);out.callCompleted=1;snapshot(out,w);
 }else if(c.op==4){
  typedef void(*Fn)(CDropdownMenu*);Fn fn=ours?uiNewCreate:uiDropCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;
  snapshot(out,static_cast<CEGUI::Window*>(p->m_pUnknown18));unsigned state[]={p->m_pGenericModel!=NULL,p->m_bUnknown30,p->m_bUnknown31,p->m_bUnknown32};out.add(state,sizeof(state));
 }else{
  uiDropCreate(p);CEGUI::Window*root=static_cast<CEGUI::Window*>(p->m_pUnknown18);p->m_bUnknown30=(c.index/2)&1;p->m_bUnknown31=(c.index/4)&1;if(c.index&8)f.root->addChildWindow(root);
  detour::Set audio;TL_REDIRECT(audio,uiDropSound,&sound);if(audio.failed())std::abort();
  CEquipment* item=NULL;CPlayer* player=NULL;
  if(c.op==2&&(c.index&32)){item=new CEquipment(&f.resources);player=nativegame::createPlayer(&f.resources);f.nativeClient.client->m_selectedItem.setObject(item);f.nativeClient.client->m_targetItem.setObject(item);f.nativeClient.client->m_selectedCharacter.setObject(player);f.nativeClient.client->m_targetCharacter.setObject(player);}
  if(c.op==2){
   bool open=(c.index/16)&1;typedef void(*Fn)(CDropdownMenu*,bool);Fn fn=ours?uiNewOpen:uiDropOpen;if(!autotest::beginInvocation(out,fn))return;fn(p,open);
  }else{
   if(p->m_pGenericModel){p->m_pGenericModel->setPosition(float(c.index%3)*15,float(c.index%5)*-11,0);p->m_pGenericModel->playAnimation(c.index&16?"CLOSE":"OPEN",false,1,-1);}
   float times[]={0.0f,0.25f,9.0f};float elapsed=times[(c.index/8)%3];typedef void(*Fn)(CDropdownMenu*,float);Fn fn=ours?uiNewUpdate:uiDropUpdate;if(!autotest::beginInvocation(out,fn))return;fn(p,elapsed);
  }
  out.callCompleted=1;unsigned safe[]={f.nativeClient.client->m_selectedItem.getObject()!=NULL,f.nativeClient.client->m_targetItem.getObject()!=NULL,f.nativeClient.client->m_selectedCharacter.getObject()!=NULL,f.nativeClient.client->m_targetCharacter.getObject()!=NULL};out.add(safe,sizeof(safe));if(player)nativegame::destroyPlayer(player);delete item;
  unsigned state[]={p->m_bUnknown30,p->m_bUnknown31,p->m_bUnknown32,root->getParent()==f.root};out.add(state,sizeof(state));snapshot(out,root);
  if(p->m_pGenericModel){bool visible=p->m_pGenericModel->getVisible();out.add(&visible,sizeof(visible));bool a=p->m_pGenericModel->animationPlaying("CLOSE"),b=p->m_pGenericModel->animationPlaying("OPEN"),d=p->m_pGenericModel->animationQueued("IDLE");out.add(&a,1);out.add(&b,1);out.add(&d,1);}
 }
 if(p->m_pUnknown18){wm.destroyWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));p->m_pUnknown18=NULL;p->m_pUnknown20=NULL;}
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,op,name,address,&side,count);}
}
TL_TEST(complete_ui_dropdown_map){return run(host,0,"complete_ui_dropdown_map",0xb179e0,32);}
TL_TEST(complete_ui_dropdown_title){return run(host,1,"complete_ui_dropdown_title",0xb17e70,24);}
TL_TEST(complete_ui_dropdown_open){return run(host,2,"complete_ui_dropdown_open",0xb18e50,64);}
TL_TEST(complete_ui_dropdown_update){return run(host,3,"complete_ui_dropdown_update",0xb176b0,96);}
TL_TEST(complete_ui_dropdown_create){return run(host,4,"complete_ui_dropdown_create",0xb196f0,24);}
