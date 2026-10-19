#include "MenuGuiFixture.h"
#include "MenuModelGpuBoundary.h"
#include "DifficultyMenu.h"
#include "OptionsMenu.h"
#include "Equipment.h"
#include "GameVariables.h"
#include <clocale>
TL_ORIGINAL(void,doDifficultyCtor,(CDifficultyMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN15CDifficultyMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,doOptionsCtor,(COptionsMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN12COptionsMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,doDifficultyDtor,(CDifficultyMenu*),"_ZN15CDifficultyMenuD1Ev")
TL_ORIGINAL(void,doOptionsDtor,(COptionsMenu*),"_ZN12COptionsMenuD1Ev")
TL_ORIGINAL(void,doBaseCreate,(CDropdownMenu*),"_ZN13CDropdownMenu11createMenusEv")
TL_ORIGINAL(void,doDifficultyCreate,(CDifficultyMenu*),"_ZN15CDifficultyMenu11createMenusEv")
TL_ORIGINAL(void,doOptionsCreate,(COptionsMenu*),"_ZN12COptionsMenu11createMenusEv")
TL_ORIGINAL(void,doOptionsOpen,(COptionsMenu*,bool),"_ZN12COptionsMenu7setOpenEb")
extern "C" void doNewDifficultyCreate(CDifficultyMenu*) __asm__("_ZN15CDifficultyMenu11createMenusEv");
extern "C" void doNewOptionsCreate(COptionsMenu*) __asm__("_ZN12COptionsMenu11createMenusEv");
extern "C" void doNewOptionsOpen(COptionsMenu*,bool) __asm__("_ZN12COptionsMenu7setOpenEb");
TL_FUNCTION(doDifficultyCreateHook,"_ZN15CDifficultyMenu11createMenusEv")
TL_FUNCTION(doOptionsCreateHook,"_ZN12COptionsMenu11createMenusEv")
TL_FUNCTION(doSound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;unsigned zCalls;
bool zChanged(const CEGUI::EventArgs&){++zCalls;return false;}
void num(unsigned n){output->add(&n,4);}void scalar(float n){output->add(&n,4);}
void snapshot(CEGUI::Window*w){std::string s=tlheadless::snapshot(*w);num(s.size());output->add(s.data(),s.size());}
void skipDifficulty(CDifficultyMenu*){}void skipOptions(COptionsMenu*){}
int sound(CSoundBank*p,int id,Ogre::SceneNode*n,float a,float b,bool flag){num(p!=NULL);num(id);num(n!=NULL);scalar(a);scalar(b);num(flag);return 0;}
struct Strings {uintptr_t n,w;bool ownN,ownW;Strings(uintptr_t narrow,uintptr_t wide):n(narrow),w(wide),ownN(false),ownW(false){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(n),8);if(!p){new(reinterpret_cast<void*>(n))std::string;ownN=true;}std::memcpy(&p,reinterpret_cast<void*>(w),8);if(!p){new(reinterpret_cast<void*>(w))std::wstring;ownW=true;}}~Strings(){if(ownW){reinterpret_cast<std::wstring*>(w)->~basic_string();std::memset(reinterpret_cast<void*>(w),0,8);}if(ownN){reinterpret_cast<std::string*>(n)->~basic_string();std::memset(reinterpret_cast<void*>(n),0,8);}}};
struct Menu {
 Strings strings;CDropdownMenu*p;bool difficulty;
 Menu(menugui::Fixture&f,bool isDifficulty):strings(isDifficulty?0x14d9a00:0x14c9e00,isDifficulty?0x14d9a08:0x14c9e08),p(NULL),difficulty(isDifficulty){
  detour::Set setup;TL_REDIRECT(setup,mgDropdownCreate,&menugui::skipDropdown);TL_REDIRECT(setup,mgTitle,&menugui::skipTitle);TL_REDIRECT(setup,doDifficultyCreateHook,&skipDifficulty);TL_REDIRECT(setup,doOptionsCreateHook,&skipOptions);if(setup.failed())std::abort();
  if(difficulty){CDifficultyMenu*q=static_cast<CDifficultyMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CDifficultyMenu),0,0,0));doDifficultyCtor(q,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);p=q;}
  else{COptionsMenu*q=static_cast<COptionsMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(COptionsMenu),0,0,0));doOptionsCtor(q,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);p=q;}
 }
 ~Menu(){if(p->m_pUnknown18)CEGUI::WindowManager::getSingleton().destroyWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));if(difficulty)doDifficultyDtor(static_cast<CDifficultyMenu*>(p));else doOptionsDtor(static_cast<COptionsMenu*>(p));Ogre::NedAllocImpl::deallocBytes(p);}
};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;unsigned seed=c.index;settings->SetFloat(KSETTINGS_YRATIO,.5f+float(seed%3)*.25f);settings->SetInt(KSETTINGS_RES_WIDTH,800+int(seed%12)*80);settings->SetInt(KSETTINGS_RES_HEIGHT,600+int(seed%7)*30);CStringTranslate translate(L"");menugui::ModelGpuBoundary gpu;menugui::Fixture f(*settings,scene);Menu menu(f,c.op==0);CDropdownMenu*base=menu.p;doBaseCreate(base);CEGUI::Window*root=static_cast<CEGUI::Window*>(base->m_pUnknown18);
 if(c.op==0){CDifficultyMenu*p=static_cast<CDifficultyMenu*>(base);typedef void(*Fn)(CDifficultyMenu*);Fn fn=ours?doNewDifficultyCreate:doDifficultyCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;num(p->m_hardcoreCheckbox==root->recursiveChildSearch("Hardcore"));snapshot(root);
 }else if(c.op==1){COptionsMenu*p=static_cast<COptionsMenu*>(base);typedef void(*Fn)(COptionsMenu*);Fn fn=ours?doNewOptionsCreate:doOptionsCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;num(p->m_iUnknown50==root->recursiveChildSearch("Title"));snapshot(root);
 }else{
  COptionsMenu*p=static_cast<COptionsMenu*>(base);doOptionsCreate(p);p->m_bUnknown30=seed/2&1;p->m_bUnknown31=seed/4&1;CEGUI::Window*contents=static_cast<CEGUI::Window*>(p->m_pUnknown20);contents->setPosition(CEGUI::UVector2(CEGUI::UDim(.25f,21),CEGUI::UDim(.5f,43)));if(seed/8&1)f.root->addChildWindow(root);f.root->addChildWindow(CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","sibling"));
  CGenericModel*saved=p->m_pGenericModel;if(seed/16&1)p->m_pGenericModel=NULL;else{p->m_pGenericModel->setVisible(false);p->m_pGenericModel->playAnimation(seed/32&1?"CLOSE":"OPEN",false,1,-1);}
  CEquipment*item=NULL;CPlayer*player=NULL;unsigned weak=seed/64%4;if(weak&1){item=new CEquipment(&f.resources);f.nativeClient.client->getMouseClickUnit(2).setObject(item);f.nativeClient.client->getMouseClickUnit(3).setObject(item);}if(weak&2){player=nativegame::createPlayer(&f.resources);f.nativeClient.client->getMouseClickUnit(0).setObject(player);f.nativeClient.client->getMouseClickUnit(1).setObject(player);}
  root->setZOrderingEnabled(seed/256%3!=0);root->subscribeEvent(CEGUI::String("ZChanged"),CEGUI::Event::Subscriber(&zChanged));zCalls=0;detour::Set audio;TL_REDIRECT(audio,doSound,&sound);if(audio.failed())std::abort();typedef void(*Fn)(COptionsMenu*,bool);Fn fn=ours?doNewOptionsOpen:doOptionsOpen;if(!autotest::beginInvocation(out,fn))return;fn(p,seed&1);out.callCompleted=1;num(zCalls);num(p->m_bUnknown30);num(p->m_bUnknown31);num(root->getParent()==f.root);for(unsigned i=0;i<4;++i)num(f.nativeClient.client->getMouseClickUnit(i).getObject()!=NULL);snapshot(root);snapshot(f.root);
  if(p->m_pGenericModel){num(p->m_pGenericModel->getVisible());num(p->m_pGenericModel->animationPlaying("CLOSE"));num(p->m_pGenericModel->animationPlaying("OPEN"));num(p->m_pGenericModel->animationQueued("IDLE"));}p->m_pGenericModel=saved;if(player)nativegame::destroyPlayer(player);delete item;
 }
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){std::string previous=std::setlocale(LC_CTYPE,NULL);if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;int result;{tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;result=smallmass::run(host,op,name,address,&side,count);}std::setlocale(LC_CTYPE,previous.c_str());return result;}
}
TL_TEST(complete_ui_difficulty_create){return run(host,0,"complete_ui_difficulty_create",0xc4a810,24);}
TL_TEST(complete_ui_options_create){return run(host,1,"complete_ui_options_create",0xb87ff0,24);}
TL_TEST(complete_ui_options_open){return run(host,2,"complete_ui_options_open",0xb86f50,768);}
