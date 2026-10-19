#include "MenuGuiFixture.h"
#include "MainMenu.h"
#include "FileSystem.h"
#include "GameVariables.h"
#include <clocale>
TL_ORIGINAL(void,maCtor,(CMainMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN9CMainMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,maDtor,(CMainMenu*),"_ZN9CMainMenuD1Ev")
TL_ORIGINAL(void,maBaseCreate,(CDropdownMenu*),"_ZN13CDropdownMenu11createMenusEv")
TL_ORIGINAL(void,maCreate,(CMainMenu*),"_ZN9CMainMenu11createMenusEv")
TL_ORIGINAL(void,maUpdate,(CMainMenu*,float),"_ZN9CMainMenu6updateEf")
extern "C" void maNewCreate(CMainMenu*) __asm__("_ZN9CMainMenu11createMenusEv");
extern "C" void maNewUpdate(CMainMenu*,float) __asm__("_ZN9CMainMenu6updateEf");
TL_FUNCTION(maCreateHook,"_ZN9CMainMenu11createMenusEv")
TL_FUNCTION(maCanContinue,"_ZN7CGameUI11canContinueEv")
TL_FUNCTION(maMods,"_ZN11CFileSystem18getEnabledModNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;unsigned seed;bool duringTarget;std::vector<std::wstring>enabled;
void num(unsigned n){output->add(&n,4);}
void mods(CFileSystem*p,TArrayList<std::wstring>*values){if(duringTarget){num(17);num(p==CFileSystem::getSingleton());num(values->size());num(values->m_nGrowBy);}for(unsigned i=0;i<enabled.size();++i)values->add(enabled[i]);}
bool canContinue(CGameUI*p){num(19);num(p!=NULL);return seed&1;}
void skip(CMainMenu*){}
void snapshot(CEGUI::Window*w){std::string s=tlheadless::snapshot(*w);num(s.size());output->add(s.data(),s.size());}
struct Strings{
 bool n,w,c;
 Strings():n(false),w(false),c(false){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14daf40),8);if(!p){new(reinterpret_cast<void*>(0x14daf40))std::string;n=true;}std::memcpy(&p,reinterpret_cast<void*>(0x14daf48),8);if(!p){new(reinterpret_cast<void*>(0x14daf48))std::wstring;w=true;}std::memcpy(&p,reinterpret_cast<void*>(0x14dc468),8);if(!p){new(reinterpret_cast<void*>(0x14dc468))std::wstring(L"(v1.15) Torchlight (C) 2009 Runic Games Inc.");c=true;}}
 ~Strings(){if(c){reinterpret_cast<std::wstring*>(0x14dc468)->~basic_string();std::memset(reinterpret_cast<void*>(0x14dc468),0,8);}if(w){reinterpret_cast<std::wstring*>(0x14daf48)->~basic_string();std::memset(reinterpret_cast<void*>(0x14daf48),0,8);}if(n){reinterpret_cast<std::string*>(0x14daf40)->~basic_string();std::memset(reinterpret_cast<void*>(0x14daf40),0,8);}}
};
struct Menu{
 Strings strings;CMainMenu*p;
 explicit Menu(menugui::Fixture&f){p=static_cast<CMainMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CMainMenu),0,0,0));detour::Set setup;TL_REDIRECT(setup,mgDropdownCreate,&menugui::skipDropdown);TL_REDIRECT(setup,maCreateHook,&skip);if(setup.failed())std::abort();maCtor(p,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);}
 ~Menu(){if(p->m_pUnknown18)CEGUI::WindowManager::getSingleton().destroyWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));maDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}
};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;duringTarget=false;settings->SetInt(KSETTINGS_RES_WIDTH,800+int(seed%12)*80);settings->SetInt(KSETTINGS_RES_HEIGHT,600+int(seed%7)*30);CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);Menu menu(f);CMainMenu*p=menu.p;maBaseCreate(p);
 if(c.op==0){typedef void(*Fn)(CMainMenu*);Fn fn=ours?maNewCreate:maCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;snapshot(static_cast<CEGUI::Window*>(p->m_pUnknown18));CEGUI::Window*root=static_cast<CEGUI::Window*>(p->m_pUnknown18);unsigned fields[]={p->m_iUnknownC8==root->recursiveChildSearch("ContinueLast"),p->m_iUnknownD0==root->recursiveChildSearch("DemoVersion"),p->m_iUnknownD8==root->recursiveChildSearch("CharacterModsWarning"),p->m_iUnknownE0==root->recursiveChildSearch("Credits"),p->m_creditsWindow==root->recursiveChildSearch("CreditFrame"),p->m_extraWindow==root->recursiveChildSearch("CreditFrameB")};out.add(fields,sizeof(fields));return;}
 maCreate(p);p->m_bUnknown30=(seed/32)&1;p->m_bUnknown31=(seed/64)&1;p->m_iUnknownC8->setVisible((seed/2)&1);p->m_iUnknownD8->setVisible((seed/4)&1);CEGUI::Window*warning=p->m_iUnknownD8;if(seed&8)p->m_iUnknownD8=NULL;
 enabled.clear();unsigned profile=seed/16%6;if(profile){enabled.push_back(L"Alpha");enabled.push_back(L"Beta");if(profile==5)enabled.push_back(L"漢字");}
 detour::Set collaborators;TL_REDIRECT(collaborators,maMods,&mods);TL_REDIRECT(collaborators,maCanContinue,&canContinue);if(collaborators.failed())std::abort();CPlayer*player=nativegame::createPlayer(&f.resources);CPlayer*previous=f.nativeClient.client->m_pPlayer;f.nativeClient.client->m_pPlayer=seed%13?player:NULL;
 if(profile==2)enabled[0]=L"aLpHa";if(profile==3)enabled[1]=L"different";if(profile==4)enabled.pop_back();if(profile==5)enabled[2]=L"漢字";
 duringTarget=true;typedef void(*Fn)(CMainMenu*,float);Fn fn=ours?maNewUpdate:maUpdate;if(!autotest::beginInvocation(out,fn))return;fn(p,seed&1?.125f:4);out.callCompleted=1;duringTarget=false;snapshot(static_cast<CEGUI::Window*>(p->m_pUnknown18));num(p->m_bUnknown30);num(p->m_bUnknown31);num(p->m_iUnknownD8!=NULL);p->m_iUnknownD8=warning;f.nativeClient.client->m_pPlayer=previous;collaborators.restore();nativegame::destroyPlayer(player);
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){std::string old=std::setlocale(LC_CTYPE,NULL);if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;int result;{tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;result=smallmass::run(host,op,name,address,&side,count);}std::setlocale(LC_CTYPE,old.c_str());return result;}
}
TL_TEST(complete_ui_main_create){return run(host,0,"complete_ui_main_create",0xc52a10,24);}
TL_TEST(complete_ui_main_update){return run(host,1,"complete_ui_main_update",0xc53b70,192);}
