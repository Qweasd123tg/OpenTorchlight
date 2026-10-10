#include <cstring>
#include <new>
#include <string>
#define private public
#define protected public
#include <CEGUI.h>
#include "PetMenu.h"
#include "Settings.h"
#include "GameVariables.h"
#include "GameUI.h"
#include "SoundBank.h"
#include "SoundData.h"
#include "SoundBankDataInformation.h"
#include "MasterResourceManager.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalCtor, (CPetMenu*,CGameUI&,CSettings&,Ogre::RenderWindow*,Ogre::SceneManager*,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*), "_ZN8CPetMenuC1ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerES8_PN5CEGUI6WindowEP16CResourceManager")
extern "C" void candidateCtor(CPetMenu*,CGameUI&,CSettings&,Ogre::RenderWindow*,Ogre::SceneManager*,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*) __asm__("_ZN8CPetMenuC1ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerES8_PN5CEGUI6WindowEP16CResourceManager");
TL_FUNCTION(settingsFn,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(coreCtorFn,"_ZN10CRunicCoreC1Ev")
TL_FUNCTION(masterFn,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(bankCtorFn,"_ZN10CSoundBankC1ER13CSoundManagerb")
TL_FUNCTION(soundFn,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(sampleFn,"_ZN10CSoundBank9addSampleEix")
TL_FUNCTION(createFn,"_ZN8CPetMenu11createMenusEv")
TL_FUNCTION(baseDtorFn,"_ZN8CSubMenuD2Ev")
extern "C" char allocFn[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char freeFn[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace {
template<class T> struct Ref { T* p; explicit Ref(T* value):p(value){} operator T&()const{return *p;} };
struct Stop {};
struct Case { unsigned found;bool alternate;unsigned fault;unsigned pattern; };
const Case* cs;autotest::Capture* cap;CPetMenu* menu;
CMasterResourceManager* masters[2];CSoundBankDataInformation* infos[2];CSoundManager* managers[2];CSoundData* sounds[4];CSoundBank* banks[2];
unsigned singletonCalls,lookupCalls,sampleCalls;unsigned coreCalls,baseCalls,freeCalls,settingsCalls;CSettings* settings[2];
void n(int v){cap->add(&v,sizeof(v));}
void core(CRunicCore* p){n(1);n(p==static_cast<CRunicCore*>(menu));++coreCalls;std::memset(p,0,16);}
CMasterResourceManager* master(){n(2);unsigned i=cs->alternate&&singletonCalls?1:0;++singletonCalls;n(i);return masters[i];}
void* allocate(size_t bytes,const char* file,int line,const char* func){n(3);n(bytes);n(file==0);n(line);n(func==0);if(cs->fault==1)throw Stop();return banks[0];}
void release(void* p){n(4);n(p==banks[0]);++freeCalls;}
void bank(CSoundBank* p,CSoundManager& manager,bool flag){n(5);n(p==banks[0]);n(&manager==managers[0]?0:&manager==managers[1]?1:99);n(flag);if(cs->fault==2)throw Stop();std::memset(p,0x37,sizeof(CSoundBank));}
CSoundData* lookup(CSoundBankDataInformation* info,const std::wstring& key){n(6);n(info==infos[0]?0:info==infos[1]?1:99);cap->addText(key);unsigned i=lookupCalls++;n(i);if(i>=3)_exit(60);if(cs->fault==3+i)throw Stop();return (cs->found&(1u<<i))?sounds[i]:0;}
void sample(CSoundBank* p,int index,long long guid){n(7);n(p==banks[0]?0:p==banks[1]?1:99);n(index);cap->add(&guid,sizeof(guid));++sampleCalls;if(cs->fault==5+sampleCalls)throw Stop();if(cs->alternate)menu->m_pSoundBank=banks[1];}
int setting(CDynamicPropertyFile* p,unsigned key){n(10);n(p==(CDynamicPropertyFile*)settings[0]?0:p==(CDynamicPropertyFile*)settings[1]?1:99);n(key);++settingsCalls;if(cs->fault==8+settingsCalls)throw Stop();if(cs->alternate)menu->m_pDynamicPropertyFile=settings[1];return settingsCalls==1?(cs->pattern?(-2147483647-1):1920):1080;}
void create(CPetMenu* p){n(8);n(p==menu);cap->add(&p->m_fScreenEdge,4);if(cs->fault==11)throw Stop();p->m_fScreenEdge=23.75f;}
void baseDtor(CSubMenu* p){n(9);n(p==static_cast<CSubMenu*>(menu));++baseCalls;}
void ptr(unsigned char* bytes,unsigned offset,unsigned value){uintptr_t v=value;std::memcpy(bytes+offset,&v,sizeof(v));}
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long mem[(sizeof(CPetMenu)+16+7)/8],masterMem[2][64]={{0}},bankMem[2][(sizeof(CSoundBank)+7)/8],soundMem[4][(sizeof(CSoundData)+7)/8]={{0}};
 unsigned long long uiMem[16]={0},settingsMem[2][16]={{0}},renderMem[8]={0},sceneMem[2][8]={{0}},parentMem[8]={0},resourcesMem[8]={0},managerMem[2][8]={{0}},infoMem[2][8]={{0}};
 std::memset(mem,c.pattern?0x5a:0xa5,sizeof(mem));std::memset(bankMem,c.pattern?0x73:0x29,sizeof(bankMem));menu=(CPetMenu*)mem;cs=&c;cap=&out;
 singletonCalls=lookupCalls=sampleCalls=coreCalls=baseCalls=freeCalls=settingsCalls=0;
 for(unsigned i=0;i<2;++i){settings[i]=(CSettings*)settingsMem[i];masters[i]=(CMasterResourceManager*)masterMem[i];banks[i]=(CSoundBank*)bankMem[i];infos[i]=(CSoundBankDataInformation*)infoMem[i];managers[i]=(CSoundManager*)managerMem[i];masters[i]->m_pSoundBankDataInformation=infos[i];masters[i]->m_pSoundManager=managers[i];}
 for(unsigned i=0;i<4;++i){sounds[i]=(CSoundData*)soundMem[i];sounds[i]->m_iGuid=c.pattern?(i==0?0:i==1?9223372036854775807LL:(-9223372036854775807LL-1)):(c.alternate?-1LL:1LL)*(0x1234567800000000LL+i*12345);}
 detour::Set redirects;TL_REDIRECT(redirects,settingsFn,&setting);TL_REDIRECT(redirects,coreCtorFn,&core);TL_REDIRECT(redirects,masterFn,&master);TL_REDIRECT(redirects,bankCtorFn,&bank);TL_REDIRECT(redirects,soundFn,&lookup);TL_REDIRECT(redirects,sampleFn,&sample);TL_REDIRECT(redirects,createFn,&create);TL_REDIRECT(redirects,baseDtorFn,&baseDtor);redirects.redirect(allocFn,allocFn,&allocate);redirects.redirect(freeFn,freeFn,&release);if(redirects.failed())_exit(61);
 bool threw=false;try{if(ours)autotest::invoke(out,&candidateCtor,menu,Ref<CGameUI>((CGameUI*)uiMem),Ref<CSettings>(settings[0]),(Ogre::RenderWindow*)renderMem,(Ogre::SceneManager*)sceneMem[0],(Ogre::SceneManager*)sceneMem[1],(CEGUI::Window*)parentMem,(CResourceManager*)resourcesMem);else autotest::invoke(out,&originalCtor,menu,Ref<CGameUI>((CGameUI*)uiMem),Ref<CSettings>(settings[0]),(Ogre::RenderWindow*)renderMem,(Ogre::SceneManager*)sceneMem[0],(Ogre::SceneManager*)sceneMem[1],(CEGUI::Window*)parentMem,(CResourceManager*)resourcesMem);}catch(const Stop&){threw=true;}catch(...){_exit(62);}
 n(threw);n(singletonCalls);n(lookupCalls);n(sampleCalls);n(coreCalls);n(baseCalls);n(freeCalls);n(settingsCalls);
 unsigned char snapshot[sizeof(mem)];std::memcpy(snapshot,menu,sizeof(snapshot));
 // Vtable identity resolves to the same original table in this hybrid.
 // Canonicalize only known argument identities; retain unexpected pointers.
 void* values[]={menu->m_pParent,menu->m_pDynamicPropertyFile,menu->m_pGameUI,menu->m_pPetSceneManager,menu->m_pResourceManager,menu->m_pSoundBank,menu->m_pWardrobeSceneManager,menu->m_pRenderWindow};
 void* expected[]={parentMem,settings[0],uiMem,sceneMem[0],resourcesMem,banks[0],sceneMem[1],renderMem};
 unsigned offsets[]={0x18,0x88,0x90,0x9160,0x91a8,0x91b8,0x9168,0x9178};
 for(unsigned i=0;i<8;++i){if(values[i]==expected[i])ptr(snapshot,offsets[i],1);else if(values[i]==0)ptr(snapshot,offsets[i],0);else if((i==1&&values[i]==settings[1])||(i==5&&values[i]==banks[1]))ptr(snapshot,offsets[i],2);}
 cap->add(snapshot,sizeof(snapshot));cap->add(bankMem,sizeof(bankMem));
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
}
TL_TEST(petmenu_constructor_differential){
 autotest::Coverage coverage("petmenu_constructor_differential",(uint64_t)(uintptr_t)&originalCtor);
 for(unsigned found=0;found<8;++found)for(unsigned change=0;change<2;++change)for(unsigned pattern=0;pattern<2;++pattern){Case c={found,bool(change),0,pattern};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callCompleted||!v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    ctor mismatch mask %u alternate %u exits %d/%d lengths %lu/%lu first %lu\n",found,change,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length,(unsigned long)f);coverage.report(host);return 1;}}
 coverage.report(host);return 0;
}
TL_TEST(petmenu_constructor_expected_exceptions){
 unsigned total=0;for(unsigned fault=1;fault<=11;++fault)for(unsigned change=0;change<2;++change)for(unsigned pattern=0;pattern<2;++pattern){Case c={7,bool(change),fault,pattern};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);++total;if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    ctor unwind mismatch %u/%u exits %d/%d lengths %lu/%lu\n",fault,change,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);return 1;}}
 host->log("    EXPECTED CONSTRUCTOR EXCEPTIONS: %u matching unwinds; not normal completion coverage\n",total);return 0;
}
