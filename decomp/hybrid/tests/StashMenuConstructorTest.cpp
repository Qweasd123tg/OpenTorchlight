#include <cstring>
#include <new>
#define private public
#define protected public
#include "StashMenu.h"
#include "Settings.h"
#include "MasterResourceManager.h"
#include "SoundBank.h"
#include "SoundData.h"
#include "SoundBankDataInformation.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalCtor,(CStashMenu*,CGameUI*,CSettings*,Ogre::RenderWindow*,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN10CStashMenuC1ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
extern "C" void candidateCtor(CStashMenu*,CGameUI*,CSettings*,Ogre::RenderWindow*,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*) __asm__("_ZN10CStashMenuC1ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerEPN5CEGUI6WindowEP16CResourceManager");
TL_FUNCTION(coreFn,"_ZN10CRunicCoreC1Ev")
TL_FUNCTION(masterFn,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(bankFn,"_ZN10CSoundBankC1ER13CSoundManagerb")
TL_FUNCTION(lookupFn,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(sampleFn,"_ZN10CSoundBank9addSampleEix")
TL_FUNCTION(createFn,"_ZN10CStashMenu11createMenusEv")
TL_FUNCTION(baseFn,"_ZN8CSubMenuD2Ev")
extern "C" char allocFn[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char freeFn[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace {
struct Stop{};struct Case{unsigned found,alternate,pattern,fault;};const Case* cs;autotest::Capture* cap;CStashMenu* menu;CMasterResourceManager* masters[2];CSoundBankDataInformation* infos[2];CSoundManager* managers[2];CSoundBank* banks[2];CSoundData* sounds[6];unsigned events,masterCalls,lookups,samples;
void n(int x){cap->add(&x,4);}void event(int x){n(x);if(++events==cs->fault)throw Stop();}
void core(CRunicCore* p){event(1);n(p==menu);std::memset(p,0,16);}
CMasterResourceManager* master(){event(2);unsigned i=cs->alternate&&masterCalls?1:0;++masterCalls;n(i);return masters[i];}
void* allocate(size_t bytes,const char* file,int line,const char* fn){event(3);n(bytes);n(file==0);n(line);n(fn==0);return banks[0];}
void release(void* p){n(4);n(p==banks[0]);}
void bank(CSoundBank* p,CSoundManager& m,bool flag){event(5);n(p==banks[0]);n(&m==managers[0]?1:&m==managers[1]?2:99);n(flag);std::memset(p,0x39,sizeof(CSoundBank));}
CSoundData* lookup(CSoundBankDataInformation* p,const std::wstring& name){event(6);n(p==infos[0]?1:p==infos[1]?2:99);cap->addText(name);unsigned i=lookups++;n(i);if(i>=6)_exit(60);return cs->found&(1u<<i)?sounds[i]:0;}
void sample(CSoundBank* p,int index,long long guid){event(7);n(p==banks[0]?1:p==banks[1]?2:99);n(index);cap->add(&guid,8);++samples;if(cs->alternate)menu->m_pSoundBank=banks[1];}
void create(CStashMenu* p){event(8);n(p==menu);cap->add(&p->m_fScreenEdge,4);p->m_fScreenEdge=17.25f;}
void base(CSubMenu* p){n(9);n(p==menu);}
void ptr(unsigned char* p,unsigned off,uintptr_t v){std::memcpy(p+off,&v,8);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;events=masterCalls=lookups=samples=0;unsigned long long mm[(sizeof(CStashMenu)+23)/8],bm[2][(sizeof(CSoundBank)+7)/8],sm[6][(sizeof(CSoundData)+7)/8]={0},masterMem[2][64]={0},infoMem[2][8]={0},managerMem[2][8]={0},uiMem[8]={0},settingsMem[8]={0},renderMem[8]={0},sceneMem[8]={0},windowMem[8]={0},resourcesMem[8]={0};const unsigned char patterns[]={0,0x5a,0xa5,0xff};std::memset(mm,patterns[c.pattern],sizeof(mm));std::memset(bm,0x73,sizeof(bm));menu=(CStashMenu*)mm;for(unsigned i=0;i<2;++i){masters[i]=(CMasterResourceManager*)masterMem[i];infos[i]=(CSoundBankDataInformation*)infoMem[i];managers[i]=(CSoundManager*)managerMem[i];banks[i]=(CSoundBank*)bm[i];masters[i]->m_pSoundBankDataInformation=infos[i];masters[i]->m_pSoundManager=managers[i];}for(unsigned i=0;i<6;++i){sounds[i]=(CSoundData*)sm[i];sounds[i]->m_iGuid=c.pattern==0?0:c.pattern==1?(i%2?(-9223372036854775807LL-1):9223372036854775807LL):c.pattern==2?0x1234567800000000LL+i*37:-1LL-int(i)*53;}
 detour::Set d;TL_REDIRECT(d,coreFn,&core);TL_REDIRECT(d,masterFn,&master);TL_REDIRECT(d,bankFn,&bank);TL_REDIRECT(d,lookupFn,&lookup);TL_REDIRECT(d,sampleFn,&sample);TL_REDIRECT(d,createFn,&create);TL_REDIRECT(d,baseFn,&base);d.redirect(allocFn,allocFn,&allocate);d.redirect(freeFn,freeFn,&release);if(d.failed())_exit(61);bool threw=false;try{if(ours)autotest::invoke(out,&candidateCtor,menu,(CGameUI*)uiMem,(CSettings*)settingsMem,(Ogre::RenderWindow*)renderMem,(Ogre::SceneManager*)sceneMem,(CEGUI::Window*)windowMem,(CResourceManager*)resourcesMem);else autotest::invoke(out,&originalCtor,menu,(CGameUI*)uiMem,(CSettings*)settingsMem,(Ogre::RenderWindow*)renderMem,(Ogre::SceneManager*)sceneMem,(CEGUI::Window*)windowMem,(CResourceManager*)resourcesMem);}catch(const Stop&){threw=true;}catch(...){_exit(62);}n(threw);n(events);n(masterCalls);n(lookups);n(samples);unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));void* values[]={menu->m_pUnknown18,menu->m_pDynamicPropertyFile,menu->m_pGameUI,menu->m_pUnknown78,menu->m_pUnknown80,menu->m_pResourceManager,menu->m_pSoundBank};void* expected[]={windowMem,settingsMem,uiMem,sceneMem,renderMem,resourcesMem,banks[0]};unsigned offsets[]={0x18,0x68,0x70,0x78,0x80,0x98,0xa8};for(unsigned i=0;i<7;++i)if(values[i]==expected[i])ptr(snapshot,offsets[i],1);else if(!values[i])ptr(snapshot,offsets[i],0);else if(i==6&&values[i]==banks[1])ptr(snapshot,offsets[i],2);cap->add(snapshot,sizeof(snapshot));cap->add(bm,sizeof(bm));}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(stashmenu_constructor){autotest::Coverage coverage("stashmenu_constructor",(uint64_t)(uintptr_t)&originalCtor);for(unsigned found=0;found<4;++found)for(unsigned alternate=0;alternate<2;++alternate)for(unsigned pattern=0;pattern<4;++pattern){Case c={found,alternate,pattern,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    stash ctor mismatch %u/%u/%u exits %d/%d\n",found,alternate,pattern,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
TL_TEST(stashmenu_constructor_expected_exceptions){unsigned count=0;for(unsigned fault=4;fault<=10;++fault)for(unsigned alternate=0;alternate<2;++alternate)for(unsigned pattern=0;pattern<4;++pattern){Case c={3,alternate,pattern,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||u.capture.callCompleted||v.capture.callCompleted||!u.capture.callStarted||!v.capture.callStarted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    stash ctor unwind mismatch %u/%u/%u exits %d/%d\n",fault,alternate,pattern,u.childStatus,v.childStatus);return 1;}++count;}host->log("    EXPECTED CONSTRUCTOR EXCEPTIONS: %u matching unwinds, not normal completion coverage\n",count);return 0;}
