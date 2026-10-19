#include "MenuGuiFixture.h"
#include "MenuModelGpuBoundary.h"
#include "ModalMenu.h"
#include "TipMenu.h"
#include "GameVariables.h"
#include <clocale>
TL_ORIGINAL(void,mtModalCtor,(CModalMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN10CModalMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,mtTipCtor,(CTipMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN8CTipMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,mtModalDtor,(CModalMenu*),"_ZN10CModalMenuD1Ev")
TL_ORIGINAL(void,mtTipDtor,(CTipMenu*),"_ZN8CTipMenuD1Ev")
TL_ORIGINAL(void,mtBaseCreate,(CDropdownMenu*),"_ZN13CDropdownMenu11createMenusEv")
TL_ORIGINAL(void,mtModalCreate,(CModalMenu*),"_ZN10CModalMenu11createMenusEv")
TL_ORIGINAL(void,mtTipCreate,(CTipMenu*),"_ZN8CTipMenu11createMenusEv")
TL_ORIGINAL(void,mtModalContents,(CModalMenu*,std::wstring&,bool,bool(*)(CBaseUnit*,CBaseUnit*),bool(*)(CBaseUnit*,CBaseUnit*)),"_ZN10CModalMenu11setContentsERSbIwSt11char_traitsIwESaIwEEbPFbP9CBaseUnitS6_ES8_")
TL_ORIGINAL(void,mtTipContents,(CTipMenu*,std::wstring&),"_ZN8CTipMenu11setContentsERSbIwSt11char_traitsIwESaIwEE")
extern "C" void mtNewModalCreate(CModalMenu*) __asm__("_ZN10CModalMenu11createMenusEv");
extern "C" void mtNewTipCreate(CTipMenu*) __asm__("_ZN8CTipMenu11createMenusEv");
extern "C" void mtNewModalContents(CModalMenu*,std::wstring&,bool,bool(*)(CBaseUnit*,CBaseUnit*),bool(*)(CBaseUnit*,CBaseUnit*)) __asm__("_ZN10CModalMenu11setContentsERSbIwSt11char_traitsIwESaIwEEbPFbP9CBaseUnitS6_ES8_");
extern "C" void mtNewTipContents(CTipMenu*,std::wstring&) __asm__("_ZN8CTipMenu11setContentsERSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(mtModalCreateHook,"_ZN10CModalMenu11createMenusEv")
TL_FUNCTION(mtTipCreateHook,"_ZN8CTipMenu11createMenusEv")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;
void num(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){num(s.size());output->add(s.data(),s.size()*4);}void snapshot(CEGUI::Window*w){std::string s=tlheadless::snapshot(*w);num(s.size());output->add(s.data(),s.size());}
void skipModal(CModalMenu*){}void skipTip(CTipMenu*){}bool accept(CBaseUnit*,CBaseUnit*){return true;}bool decline(CBaseUnit*,CBaseUnit*){return false;}
struct Strings {uintptr_t n,w;bool ownN,ownW;Strings(uintptr_t narrow,uintptr_t wide):n(narrow),w(wide),ownN(false),ownW(false){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(n),8);if(!p){new(reinterpret_cast<void*>(n))std::string;ownN=true;}std::memcpy(&p,reinterpret_cast<void*>(w),8);if(!p){new(reinterpret_cast<void*>(w))std::wstring;ownW=true;}}~Strings(){if(ownW){reinterpret_cast<std::wstring*>(w)->~basic_string();std::memset(reinterpret_cast<void*>(w),0,8);}if(ownN){reinterpret_cast<std::string*>(n)->~basic_string();std::memset(reinterpret_cast<void*>(n),0,8);}}};
struct Modal {Strings strings;CModalMenu*p;explicit Modal(menugui::Fixture&f):strings(0x14c88c0,0x14c88c8){p=static_cast<CModalMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CModalMenu),0,0,0));detour::Set setup;TL_REDIRECT(setup,mgDropdownCreate,&menugui::skipDropdown);TL_REDIRECT(setup,mgTitle,&menugui::skipTitle);TL_REDIRECT(setup,mtModalCreateHook,&skipModal);if(setup.failed())std::abort();mtModalCtor(p,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);}~Modal(){if(p->m_pUnknown18)CEGUI::WindowManager::getSingleton().destroyWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));mtModalDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}};
struct Tip {Strings strings;CTipMenu*p;explicit Tip(menugui::Fixture&f):strings(0x1527900,0x1527908){p=static_cast<CTipMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CTipMenu),0,0,0));detour::Set setup;TL_REDIRECT(setup,mgDropdownCreate,&menugui::skipDropdown);TL_REDIRECT(setup,mgTitle,&menugui::skipTitle);TL_REDIRECT(setup,mtTipCreateHook,&skipTip);if(setup.failed())std::abort();mtTipCtor(p,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);}~Tip(){if(p->m_pUnknown18)CEGUI::WindowManager::getSingleton().destroyWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));mtTipDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}};
std::wstring text(unsigned index){switch(index%6){case 0:return L"";case 1:return L"plain text";case 2:return L"Текст 漢字 \U0001F525";case 3:return L"line\nnext";case 4:return std::wstring(900,L'x');default:return std::wstring(L"prefix\0tail",11);}}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;unsigned seed=c.index;settings->SetFloat(KSETTINGS_YRATIO,.5f+float(seed%3)*.25f);settings->SetInt(KSETTINGS_RES_WIDTH,800+int(seed%12)*80);settings->SetInt(KSETTINGS_RES_HEIGHT,600+int(seed%7)*30);CStringTranslate translate(L"");menugui::ModelGpuBoundary gpu;menugui::Fixture f(*settings,scene);
 if(c.op<2){Modal menu(f);CModalMenu*p=menu.p;mtBaseCreate(p);
  if(c.op==0){typedef void(*Fn)(CModalMenu*);Fn fn=ours?mtNewModalCreate:mtModalCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;CEGUI::Window*root=static_cast<CEGUI::Window*>(p->m_pUnknown18);num(p->m_promptWindow==root->recursiveChildSearch("Ok"));num(p->m_acceptWindow==root->recursiveChildSearch("Accept"));num(p->m_declineWindow==root->recursiveChildSearch("Decline"));num(p->m_extraWindow==root->recursiveChildSearch("Dialog"));num(p->m_iUnknown50==root->recursiveChildSearch("Title"));snapshot(root);
  }else{mtModalCreate(p);CEGUI::Window*ok=p->m_promptWindow,*yes=p->m_acceptWindow,*no=p->m_declineWindow;ok->setVisible(seed&1);yes->setVisible(seed&2);no->setVisible(seed&4);p->m_extraWindow->setText(seed&1?"before":"old");unsigned mask=seed/6%8;if(mask&1)p->m_promptWindow=NULL;if(mask&2)p->m_acceptWindow=NULL;if(mask&4)p->m_declineWindow=NULL;std::wstring value=text(seed);unsigned callbacks=seed/96%4;bool(*a)(CBaseUnit*,CBaseUnit*)=callbacks&1?&accept:NULL;bool(*d)(CBaseUnit*,CBaseUnit*)=callbacks&2?&decline:NULL;typedef void(*Fn)(CModalMenu*,std::wstring&,bool,bool(*)(CBaseUnit*,CBaseUnit*),bool(*)(CBaseUnit*,CBaseUnit*));Fn fn=ours?mtNewModalContents:mtModalContents;if(!autotest::beginInvocation(out,fn))return;fn(p,value,seed/48&1,a,d);out.callCompleted=1;wide(value);num(p->m_acceptCallback==a);num(p->m_declineCallback==d);num(p->m_callbackData==NULL);snapshot(static_cast<CEGUI::Window*>(p->m_pUnknown18));p->m_promptWindow=ok;p->m_acceptWindow=yes;p->m_declineWindow=no;}
 }else{Tip menu(f);CTipMenu*p=menu.p;mtBaseCreate(p);
  if(c.op==2){typedef void(*Fn)(CTipMenu*);Fn fn=ours?mtNewTipCreate:mtTipCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;CEGUI::Window*root=static_cast<CEGUI::Window*>(p->m_pUnknown18);num(p->m_tipText==root->recursiveChildSearch("Ok"));num(p->m_tipImage==root->recursiveChildSearch("Dialog"));num(p->m_showTipsCheckbox==root->recursiveChildSearch("ShowTips"));num(p->m_iUnknown50==root->recursiveChildSearch("Title"));snapshot(root);
  }else{mtTipCreate(p);CEGUI::Window*ok=p->m_tipText;p->m_tipImage->setText(seed/12%2?"before":"old");if(seed/6&1)p->m_tipText=NULL;std::wstring value=text(seed);typedef void(*Fn)(CTipMenu*,std::wstring&);Fn fn=ours?mtNewTipContents:mtTipContents;if(!autotest::beginInvocation(out,fn))return;fn(p,value);out.callCompleted=1;wide(value);snapshot(static_cast<CEGUI::Window*>(p->m_pUnknown18));p->m_tipText=ok;}
 }
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){std::string old=std::setlocale(LC_CTYPE,NULL);if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;int result;{tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;result=smallmass::run(host,op,name,address,&side,count);}std::setlocale(LC_CTYPE,old.c_str());return result;}
}
TL_TEST(complete_ui_modal_create){return run(host,0,"complete_ui_modal_create",0xb7f580,24);}
TL_TEST(complete_ui_modal_contents){return run(host,1,"complete_ui_modal_contents",0xb7e520,384);}
TL_TEST(complete_ui_tip_create){return run(host,2,"complete_ui_tip_create",0xe4c800,24);}
TL_TEST(complete_ui_tip_contents){return run(host,3,"complete_ui_tip_contents",0xe4b810,48);}
