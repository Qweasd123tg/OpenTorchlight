#include <cstring>
#include <new>
#include <string>
#include "StatsMenuFill.h"
#include "SoundData.h"
#include "SoundBankDataInformation.h"
#include "MasterResourceManager.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldCtor,(CStatsMenuFill*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN14CStatsMenuFillC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
extern "C" void newCtor(CStatsMenuFill*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*) __asm__("_ZN14CStatsMenuFillC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager");
TL_FUNCTION(baseCtorFn,"_ZN13CDropdownMenuC2ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManagerj")
TL_FUNCTION(baseDtorFn,"_ZN13CDropdownMenuD2Ev")
TL_FUNCTION(masterFn,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(bankCtorFn,"_ZN10CSoundBankC1ER13CSoundManagerb")
TL_FUNCTION(soundFn,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(sampleFn,"_ZN10CSoundBank9addSampleEix")
TL_FUNCTION(titleFn,"_ZN13CDropdownMenu8setTitleERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(createFn,"_ZN14CStatsMenuFill11createMenusEv")
TL_FUNCTION(graphFn,"_ZN16CResourceManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
extern "C" char allocFn[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char freeFn[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace {
typedef char menu_size[sizeof(CStatsMenuFill)==0x198?1:-1];
typedef char held_offset[__builtin_offsetof(CStatsMenuFill,m_HeldTime)==0x168?1:-1];
typedef char graph_offset[__builtin_offsetof(CStatsMenuFill,m_pPointGraph)==0x170?1:-1];
typedef char cooldown_offset[__builtin_offsetof(CStatsMenuFill,m_BarCooldown)==0x178?1:-1];
typedef char bank_offset[__builtin_offsetof(CStatsMenuFill,m_pFillSoundBank)==0x180?1:-1];
typedef char interval_offset[__builtin_offsetof(CStatsMenuFill,m_FillSoundInterval)==0x188?1:-1];
typedef char countdown_offset[__builtin_offsetof(CStatsMenuFill,m_FillSoundCountdown)==0x18c?1:-1];
typedef char filling_offset[__builtin_offsetof(CStatsMenuFill,m_Filling)==0x190?1:-1];
template<class T>struct Ref{T* p;explicit Ref(T* x):p(x){}operator T&()const{return *p;}};
struct Stop{};
struct Case{unsigned found,alternate,pattern,graph,fault;};
const Case* cs;autotest::Capture* cap;CStatsMenuFill* menu;
CGameUI* ui;CSettings* settings;Ogre::SceneManager* scene;CEGUI::Window* parent;CResourceManager* resources;CGraph* graph;
CMasterResourceManager* masters[2];CSoundBankDataInformation* infos[2];CSoundManager* managers[2];CSoundData* sounds[4];CSoundBank* banks[2];
unsigned singletonCalls,lookupCalls,sampleCalls,baseCalls,freeCalls;
void n(unsigned v){cap->add(&v,sizeof(v));}
void fault(unsigned v){if(cs->fault==v)throw Stop();}
void baseCtor(CDropdownMenu* p,CGameUI& a,CSettings& b,Ogre::SceneManager* c,CEGUI::Window* d,CResourceManager* e,unsigned f){
 n(1);n(p==menu);n(&a==ui);n(&b==settings);n(c==scene);n(d==parent);n(e==resources);n(f);fault(1);std::memset(p,0,sizeof(CDropdownMenu));
}
void baseDtor(CDropdownMenu* p){n(2);n(p==menu);++baseCalls;}
CMasterResourceManager* master(){n(3);unsigned i=cs->alternate&&singletonCalls?1:0;++singletonCalls;n(i);return masters[i];}
void* allocate(size_t bytes,const char* file,int line,const char* fn){n(4);n(bytes);n(file==0);n(line);n(fn==0);fault(2);return banks[0];}
void release(void* p){n(5);n(p==banks[0]);++freeCalls;}
void bank(CSoundBank* p,CSoundManager& manager,bool flag){n(6);n(p==banks[0]);n(&manager==managers[0]?0:&manager==managers[1]?1:99);n(flag);fault(3);std::memset(p,0x37,sizeof(CSoundBank));}
CSoundData* lookup(CSoundBankDataInformation* info,const std::wstring& key){n(7);n(info==infos[0]?0:info==infos[1]?1:99);cap->addText(key);unsigned i=lookupCalls++;n(i);if(i>=4)_exit(60);fault(4+i);return(cs->found&(1u<<i))?sounds[i]:0;}
void sample(CSoundBank* p,int index,long long guid){n(8);n(p==banks[0]?0:p==banks[1]?1:99);n(index);cap->add(&guid,sizeof(guid));cap->add(&menu->m_FillSoundInterval,4);fault(8+sampleCalls++);if(cs->alternate)menu->m_pFillSoundBank=banks[1];}
void title(CDropdownMenu* p,const std::wstring& key){n(9);n(p==menu);cap->addText(key);fault(12);}
void create(CStatsMenuFill* p){n(10);n(p==menu);cap->add(&p->m_BarCooldown,4);fault(13);p->m_BarCooldown=23.75f;}
CGraph* getGraph(CResourceManager* p,const std::wstring& key){n(11);n(p==resources);cap->addText(key);fault(14);return cs->graph?graph:0;}
void canonical(unsigned char* snapshot,unsigned offset,void* a,void* b=0){
 void* p;std::memcpy(&p,snapshot+offset,sizeof(p));
 if(p==a||p==b||p==0){uintptr_t v=p==a?1:p&&p==b?2:0;std::memcpy(snapshot+offset,&v,sizeof(v));}
 // Unknown pointers, including the initial canary, are retained verbatim.
}
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long mem[0x1a8/8],masterMem[2][64]={{0}},bankMem[2][(sizeof(CSoundBank)+7)/8],soundMem[4][(sizeof(CSoundData)+7)/8]={{0}};
 unsigned long long uiMem[16]={0},settingsMem[16]={0},sceneMem[8]={0},parentMem[8]={0},resourcesMem[8]={0},graphMem[8]={0},managerMem[2][8]={{0}},infoMem[2][8]={{0}};
 std::memset(mem,c.pattern?0x5a:0xa5,sizeof(mem));std::memset(bankMem,c.pattern?0x73:0x29,sizeof(bankMem));menu=(CStatsMenuFill*)mem;cs=&c;cap=&out;
 ui=(CGameUI*)uiMem;settings=(CSettings*)settingsMem;scene=(Ogre::SceneManager*)sceneMem;parent=(CEGUI::Window*)parentMem;resources=(CResourceManager*)resourcesMem;graph=(CGraph*)graphMem;
 singletonCalls=lookupCalls=sampleCalls=baseCalls=freeCalls=0;
 for(unsigned i=0;i<2;++i){masters[i]=(CMasterResourceManager*)masterMem[i];banks[i]=(CSoundBank*)bankMem[i];infos[i]=(CSoundBankDataInformation*)infoMem[i];managers[i]=(CSoundManager*)managerMem[i];masters[i]->m_pSoundBankDataInformation=infos[i];masters[i]->m_pSoundManager=managers[i];}
 for(unsigned i=0;i<4;++i){sounds[i]=(CSoundData*)soundMem[i];sounds[i]->m_iGuid=c.pattern?(i==0?0:i==1?9223372036854775807LL:i==2?(-9223372036854775807LL-1):-1):(c.alternate?-1LL:1LL)*(0x1234567800000000LL+i*12345);}
 detour::Set d;TL_REDIRECT(d,baseCtorFn,&baseCtor);TL_REDIRECT(d,baseDtorFn,&baseDtor);TL_REDIRECT(d,masterFn,&master);TL_REDIRECT(d,bankCtorFn,&bank);TL_REDIRECT(d,soundFn,&lookup);TL_REDIRECT(d,sampleFn,&sample);TL_REDIRECT(d,titleFn,&title);TL_REDIRECT(d,createFn,&create);TL_REDIRECT(d,graphFn,&getGraph);d.redirect(allocFn,allocFn,&allocate);d.redirect(freeFn,freeFn,&release);if(d.failed())_exit(61);
 bool threw=false;try{if(ours)autotest::invoke(out,&newCtor,menu,Ref<CGameUI>(ui),Ref<CSettings>(settings),scene,parent,resources);else autotest::invoke(out,&oldCtor,menu,Ref<CGameUI>(ui),Ref<CSettings>(settings),scene,parent,resources);}catch(const Stop&){threw=true;}catch(...){_exit(62);}
 n(threw);n(singletonCalls);n(lookupCalls);n(sampleCalls);n(baseCalls);n(freeCalls);
 unsigned char snapshot[sizeof(mem)];std::memcpy(snapshot,mem,sizeof(snapshot));canonical(snapshot,0x180,banks[0],banks[1]);canonical(snapshot,0x170,graph);
 cap->add(snapshot,sizeof(snapshot));cap->add(bankMem,sizeof(bankMem));
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
bool unequal(const autotest::Outcome& u,const autotest::Outcome& v){return !u.reportValid||!v.reportValid||u.childStatus||v.childStatus||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length);}
}
TL_TEST(stats_fill_constructor_differential){
 autotest::Coverage coverage("stats_fill_constructor_differential",(uint64_t)(uintptr_t)&oldCtor);
 for(unsigned mask=0;mask<16;++mask)for(unsigned alt=0;alt<2;++alt)for(unsigned pattern=0;pattern<2;++pattern)for(unsigned graph=0;graph<2;++graph){
  Case c={mask,alt,pattern,graph,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int diff=coverage.observe(host,u,v);
  if(diff||unequal(u,v)||!u.capture.callCompleted||!v.capture.callCompleted){coverage.report(host);host->log("    ctor %u/%u/%u/%u exits %d/%d lengths %lu/%lu\n",mask,alt,pattern,graph,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);return 1;}
 }coverage.report(host);return 0;
}
TL_TEST(stats_fill_constructor_expected_exceptions){
 unsigned total=0;for(unsigned fault=1;fault<=14;++fault)for(unsigned alt=0;alt<2;++alt)for(unsigned pattern=0;pattern<2;++pattern){
  Case c={15,alt,pattern,1,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);++total;
  if(unequal(u,v)||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted){host->log("    ctor unwind %u/%u/%u exits %d/%d lengths %lu/%lu\n",fault,alt,pattern,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);return 1;}
 }host->log("    EXPECTED CONSTRUCTOR EXCEPTIONS: %u matching unwinds; not normal completion coverage\n",total);return 0;
}
