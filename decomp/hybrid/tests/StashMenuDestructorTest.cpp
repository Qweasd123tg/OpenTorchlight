#include <cstring>
#include <new>
#define private public
#define protected public
#include "StashMenu.h"
#include "Character.h"
#include "Inventory.h"
#include "GenericModel.h"
#include "SoundBank.h"
#include "SharedStash.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalDtor,(CStashMenu*),"_ZN10CStashMenuD1Ev")
TL_ORIGINAL(void,originalDeleting,(CStashMenu*),"_ZN10CStashMenuD0Ev")
extern "C" void candidateDtor(CStashMenu*) __asm__("_ZN10CStashMenuD1Ev");
extern "C" void candidateDeleting(CStashMenu*) __asm__("_ZN10CStashMenuD0Ev");
TL_FUNCTION(removeFn,"_ZN10CInventory14removeListenerEP18iInventoryListener")
TL_FUNCTION(coreFn,"_ZN10CRunicCoreD2Ev")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(sharedFn,"_ZN12CSharedStash12getSingletonEv")
extern "C" char freeFn[] __asm__("_ZdlPv");
namespace {
struct Stop{};struct Case{unsigned mask,profile,mutation,mode,fault;};const Case* cs;autotest::Capture* cap;CStashMenu* menu;CCharacter* actors[4];CInventory* inventories[5];CSharedStash* shared;CGenericModel* models[2];CSoundBank* banks[2];unsigned events,freeCount;
void n(int x){cap->add(&x,4);}int aid(CBaseUnit* p){if(!p)return 0;for(unsigned i=0;i<4;++i)if(p==actors[i])return i+1;return 99;}int mid(CGenericModel* p){return !p?0:p==models[0]?1:p==models[1]?2:99;}int bid(CSoundBank* p){return !p?0:p==banks[0]?1:p==banks[1]?2:99;}void event(int x){n(x);n(aid(menu->m_pOwner));n(aid(menu->m_pCharacter));n(mid(menu->m_pUnknown90));n(bid(menu->m_pSoundBank));n(menu->m_bUnknown3421);if(++events==cs->fault)throw Stop();}
void remove(CInventory* p,iInventoryListener* listener){event(1);unsigned id=99;for(unsigned i=0;i<5;++i)if(p==inventories[i])id=i+1;n(id);n(listener==static_cast<iInventoryListener*>(menu));if(cs->mutation==1){if(p==inventories[1])menu->m_pOwner=actors[3];else menu->m_pUnknown90=models[1];}if(cs->mutation==2)menu->m_bUnknown3421=!menu->m_bUnknown3421;}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){event(2);n(aid(p));n(type);return cs->mask&16;}
CSharedStash* singleton(){event(3);return cs->mask&32?shared:0;}
void destroyModel(CGenericModel* p){event(4);n(mid(p));if(cs->mutation==1)menu->m_pSoundBank=banks[1];if(cs->mutation==2)menu->m_pSoundBank=0;if(cs->mutation==3){menu->m_pOwner=actors[3];menu->m_pCharacter=actors[0];}}
void destroyBank(CSoundBank* p){event(5);n(bid(p));}
void core(CRunicCore* p){n(6);n(p==menu);n(freeCount);n(aid(menu->m_pOwner));n(aid(menu->m_pCharacter));n(mid(menu->m_pUnknown90));n(bid(menu->m_pSoundBank));}
void release(void* p){n(7);n(p==menu);++freeCount;}
void ptr(unsigned char* p,unsigned off,uintptr_t x){std::memcpy(p+off,&x,8);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;events=freeCount=0;unsigned long long mm[(sizeof(CStashMenu)+23)/8],am[4][(sizeof(CCharacter)+7)/8]={0},im[5][(sizeof(CInventory)+7)/8]={0},sm[(sizeof(CSharedStash)+7)/8]={0},modelMem[2][8]={0},bankMem[2][8]={0};std::memset(mm,0xa5,sizeof(mm));menu=(CStashMenu*)mm;for(unsigned i=0;i<5;++i)inventories[i]=(CInventory*)im[i];for(unsigned i=0;i<4;++i){actors[i]=(CCharacter*)am[i];actors[i]->m_pInventory=inventories[i];new(&actors[i]->m_Followers)std::vector<CCharacter*>;}actors[2]->m_pInventory=c.mask&128?inventories[2]:0;if(c.profile)actors[0]->m_Followers.push_back(c.profile==1?0:actors[1]);shared=(CSharedStash*)sm;shared->m_pInventory=c.mask&64?inventories[4]:0;void* mv[2]={0,(void*)&destroyModel};void* bv[2]={0,(void*)&destroyBank};for(unsigned i=0;i<2;++i){models[i]=(CGenericModel*)modelMem[i];banks[i]=(CSoundBank*)bankMem[i];*(void***)models[i]=mv;*(void***)banks[i]=bv;}menu->m_pCharacter=c.mask&1?actors[0]:0;menu->m_pOwner=c.mask&2?actors[2]:0;menu->m_pUnknown90=c.mask&4?models[0]:0;menu->m_pSoundBank=c.mask&8?banks[0]:0;menu->m_bUnknown3421=c.profile&1;
 detour::Set d;TL_REDIRECT(d,removeFn,&remove);TL_REDIRECT(d,coreFn,&core);TL_REDIRECT(d,isaFn,&isa);TL_REDIRECT(d,sharedFn,&singleton);d.redirect(freeFn,freeFn,&release);if(d.failed())_exit(60);bool threw=false;try{if(ours)autotest::invoke(out,c.mode?&candidateDeleting:&candidateDtor,menu);else autotest::invoke(out,c.mode?&originalDeleting:&originalDtor,menu);}catch(const Stop&){threw=true;}catch(...){_exit(61);}n(threw);n(events);n(freeCount);unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0x50,aid(menu->m_pOwner));ptr(snapshot,0x58,aid(menu->m_pCharacter));ptr(snapshot,0x90,mid(menu->m_pUnknown90));ptr(snapshot,0xa8,bid(menu->m_pSoundBank));out.add(snapshot,sizeof(snapshot));for(unsigned i=0;i<4;++i)actors[i]->m_Followers.~vector();}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
int run(const tlhybrid_host* host,unsigned mode){autotest::Coverage coverage(mode?"stashmenu_deleting_destructor":"stashmenu_destructor",(uint64_t)(uintptr_t)(mode?&originalDeleting:&originalDtor));for(unsigned mask=0;mask<256;++mask)for(unsigned profile=0;profile<3;++profile)for(unsigned mutation=0;mutation<4;++mutation){Case c={mask,profile,mutation,mode,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    stash dtor mismatch %u/%u/%u/%u exits %d/%d\n",mode,mask,profile,mutation,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(stashmenu_destructor){return run(host,0);}
TL_TEST(stashmenu_deleting_destructor){return run(host,1);}
TL_TEST(stashmenu_destructor_expected_exceptions){unsigned count=0;for(unsigned mode=0;mode<2;++mode)for(unsigned fault=1;fault<=7;++fault){Case c={255,2,0,mode,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    stash dtor unwind mismatch %u/%u exits %d/%d\n",mode,fault,u.childStatus,v.childStatus);return 1;}++count;}host->log("    EXPECTED DESTRUCTOR EXCEPTIONS: %u matching unwinds, not normal coverage\n",count);return 0;}
