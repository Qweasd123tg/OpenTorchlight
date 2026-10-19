#include "AutoTest.h"
#include "HeadlessGui.h"
#define private public
#include "SoundBank.h"
#undef private
#include "MenuGuiFixture.h"
#include "MenuModelGpuBoundary.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "GameVariables.h"
#include <clocale>
TL_ORIGINAL(void,dcOld,(CDropdownMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*,unsigned),"_ZN13CDropdownMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManagerj")
extern "C" void dcNew(CDropdownMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*,unsigned) __asm__("_ZN13CDropdownMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManagerj");
TL_ORIGINAL(void,dcDtor,(CDropdownMenu*),"_ZN13CDropdownMenuD1Ev")
TL_FUNCTION(dcLookup,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dcSample,"_ZN10CSoundBank9addSampleEix")
namespace {
autotest::Capture*output;unsigned seed,lookups;CSettings*settings;Ogre::SceneManager*scene;CDropdownMenu*menu;CSoundData*sounds[2];CSoundBankDataInformation*information;
void num(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){num(s.size());output->add(s.data(),s.size()*4);}void snapshot(CEGUI::Window*w){std::string s=tlheadless::snapshot(*w);num(s.size());output->add(s.data(),s.size());}
CSoundData*lookup(CSoundBankDataInformation*p,const std::wstring&name){num(10);num(p==information);wide(name);unsigned i=lookups++;return seed%4&(1u<<i)?sounds[i]:NULL;}
void sample(CSoundBank*p,int id,long long guid){num(11);num(p==menu->m_pSoundBank);num(id);output->add(&guid,8);}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;lookups=0;settings->SetInt(KSETTINGS_RES_WIDTH,800+int(seed/4)*64);settings->SetInt(KSETTINGS_RES_HEIGHT,600+int(seed/4)*48);settings->SetFloat(KSETTINGS_YRATIO,.5f+float(seed/4%3)*.25f);CStringTranslate translate(L"");menugui::ModelGpuBoundary gpu;menugui::Fixture f(*settings,scene);information=CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;if(!information)std::abort();CSoundData first,second;first.m_group=second.m_group=NULL;first.m_iGuid=static_cast<long long>(0x1234567800000000ULL+seed);second.m_iGuid=seed/4%2?-1:static_cast<long long>(0x7fffffffffffffffULL-seed);sounds[0]=&first;sounds[1]=&second;
 const unsigned flags[]={0,1,2,3,0xffffffff,0x80000000,1,0};unsigned mode=flags[seed/4%8];Ogre::SceneManager*inputScene=mode&1&&seed/4%2?NULL:f.nativeClient.scenes[0];CResourceManager*resources=mode&1&&seed/4%3==0?NULL:&f.resources;CEGUI::Window*parent=seed/4%3==1?NULL:f.root;
 menu=static_cast<CDropdownMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CDropdownMenu),0,0,0));std::memset(menu,0xa5,sizeof(CDropdownMenu));detour::Set calls;TL_REDIRECT(calls,dcLookup,&lookup);TL_REDIRECT(calls,dcSample,&sample);if(calls.failed())std::abort();typedef void(*Fn)(CDropdownMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*,unsigned);Fn fn=ours?dcNew:dcOld;if(!autotest::beginInvocation(out,fn))return;fn(menu,*f.ui,*settings,inputScene,parent,resources,mode);out.callCompleted=1;
 num(lookups);num(menu->m_pUnknown10==parent);num(menu->m_pDynamicPropertyFile==settings);num(menu->m_pGameUI==f.ui);num(menu->m_pUnknown48==inputScene);num(menu->m_pResourceManager==resources);num(menu->m_iUnknown50==NULL);num(menu->m_bUnknown30);num(menu->m_bUnknown31);num(menu->m_bUnknown32);num(menu->m_iUnknown88);num(menu->m_pGenericModel!=NULL);num(menu->m_menuListeners.size());num(menu->m_menuListeners.m_nGrowBy);num(menu->m_pendingMenuListeners.size());num(menu->m_pendingMenuListeners.m_nGrowBy);num(menu->m_pSoundBank!=NULL);num(menu->m_pSoundBank->m_soundManager==CMasterResourceManager::getSingleton()->m_pSoundManager);num(menu->m_pSoundBank->m_is3D);snapshot(static_cast<CEGUI::Window*>(menu->m_pUnknown18));TSafePointer<CDropdownMenu>weak;weak.setObject(menu);TSafePointer<CSoundBank>bank;bank.setObject(menu->m_pSoundBank);calls.restore();CEGUI::WindowManager::getSingleton().destroyWindow(static_cast<CEGUI::Window*>(menu->m_pUnknown18));dcDtor(menu);num(weak.getObject()==NULL);num(bank.getObject()==NULL);Ogre::NedAllocImpl::deallocBytes(menu);
}
int run(const tlhybrid_host*host){std::string old=std::setlocale(LC_CTYPE,NULL);if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;int result;{tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;result=smallmass::run(host,0,"complete_ui_dropdown_ctor",0xb1b6f0,&side,32);}std::setlocale(LC_CTYPE,old.c_str());return result;}
}
TL_TEST(complete_ui_dropdown_ctor){return run(host);}
