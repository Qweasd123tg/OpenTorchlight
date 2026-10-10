#include <cstring>
#include <map>
#include <new>
#define private public
#define protected public
#include "CombineMenu.h"
#include "Character.h"
#include "Inventory.h"
#include "Equipment.h"
#include "GenericModel.h"
#include "SoundBank.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalDtor,(CCombineMenu*),"_ZN12CCombineMenuD1Ev")
TL_ORIGINAL(void,originalDeleting,(CCombineMenu*),"_ZN12CCombineMenuD0Ev")
extern "C" void candidateDtor(CCombineMenu*) __asm__("_ZN12CCombineMenuD1Ev");
extern "C" void candidateDeleting(CCombineMenu*) __asm__("_ZN12CCombineMenuD0Ev");
TL_FUNCTION(removeFn,"_ZN10CInventory14removeListenerEP18iInventoryListener")
TL_FUNCTION(coreFn,"_ZN10CRunicCoreD2Ev")
extern "C" char freeFn[] __asm__("_ZdlPv");
namespace {
typedef std::map<CEquipment*,std::pair<CInventory*,EEQUIP_LOCATIONS> > Locations;
struct Stop{};struct Case{unsigned mask,mutation,mode,fault;};const Case* cs;autotest::Capture* cap;CCombineMenu* menu;CCharacter* actors[2];CInventory* inventories[2];CEquipment* items[6];void* model;void* bank;void* nodes[8];unsigned nodeCount,freeCount;
void n(int x){cap->add(&x,4);}void remember(CEquipment* p){Locations::iterator it=menu->m_OriginalItemLocations.find(p);nodes[nodeCount++]=it._M_node;}
void insert(unsigned i){menu->m_OriginalItemLocations[items[i]]=std::make_pair(inventories[i%2],(EEQUIP_LOCATIONS)(int(i)-1));remember(items[i]);}
void remove(CInventory* p,iInventoryListener* listener){n(1);n(p==inventories[0]?1:p==inventories[1]?2:99);n(listener==static_cast<iInventoryListener*>(menu));n(menu->m_OriginalItemLocations.size());if(cs->mutation)insert(4);if(cs->fault==1)throw Stop();if(cs->mutation==2)menu->m_pCharacter=actors[1];}
void destroyModel(CGenericModel* p){n(2);n(p==model);n(menu->m_OriginalItemLocations.size());n(menu->m_pCharacter==0);if(cs->mutation)insert(5);if(cs->fault==2)throw Stop();}
void destroyBank(CSoundBank* p){n(3);n(p==bank);n(menu->m_pMenuModel==0);n(menu->m_OriginalItemLocations.size());if(cs->fault==3)throw Stop();}
void core(CRunicCore* p){n(4);n(p==menu);n(freeCount);}
void release(void* p){n(5);int id=p==menu?100:99;for(unsigned i=0;i<nodeCount;++i)if(p==nodes[i])id=i+1;n(id);++freeCount;}
void ptr(unsigned char* p,unsigned off,uintptr_t x){std::memcpy(p+off,&x,8);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;nodeCount=freeCount=0;unsigned long long mm[(sizeof(CCombineMenu)+23)/8],am[2][(sizeof(CCharacter)+7)/8]={0},im[2][(sizeof(CInventory)+7)/8]={0},em[6][8]={0},modelMem[8]={0},bankMem[8]={0};std::memset(mm,0xa5,sizeof(mm));menu=(CCombineMenu*)mm;new(&menu->m_OriginalItemLocations) Locations;for(unsigned i=0;i<2;++i){actors[i]=(CCharacter*)am[i];inventories[i]=(CInventory*)im[i];actors[i]->m_pInventory=inventories[i];}for(unsigned i=0;i<6;++i)items[i]=(CEquipment*)em[i];for(unsigned i=0;i<4;++i)if(c.mask&(8u<<i))insert(i);menu->m_pCharacter=c.mask&1?actors[0]:0;model=modelMem;bank=bankMem;menu->m_pMenuModel=c.mask&2?(CGenericModel*)model:0;menu->m_pSoundBank=c.mask&4?(CSoundBank*)bank:0;void* mv[2]={0,(void*)&destroyModel};void* bv[2]={0,(void*)&destroyBank};*(void***)model=mv;*(void***)bank=bv;
 detour::Set d;TL_REDIRECT(d,removeFn,&remove);TL_REDIRECT(d,coreFn,&core);d.redirect(freeFn,freeFn,&release);if(d.failed())_exit(60);bool threw=false;try{if(c.mode){if(ours)autotest::invoke(out,&candidateDeleting,menu);else autotest::invoke(out,&originalDeleting,menu);}else{if(ours)autotest::invoke(out,&candidateDtor,menu);else autotest::invoke(out,&originalDtor,menu);}}catch(const Stop&){threw=true;}catch(...){_exit(61);}n(threw);n(nodeCount);n(freeCount);unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));std::memset(snapshot+0x18,0,sizeof(Locations));ptr(snapshot,0x90,!menu->m_pCharacter?0:menu->m_pCharacter==actors[0]?1:menu->m_pCharacter==actors[1]?2:99);ptr(snapshot,0xc8,!menu->m_pMenuModel?0:menu->m_pMenuModel==model?1:99);ptr(snapshot,0xe0,!menu->m_pSoundBank?0:menu->m_pSoundBank==bank?1:99);out.add(snapshot,sizeof(snapshot));}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
int run(const tlhybrid_host* host,unsigned mode){autotest::Coverage coverage(mode?"combinemenu_deleting_destructor":"combinemenu_destructor",(uint64_t)(uintptr_t)(mode?&originalDeleting:&originalDtor));for(unsigned mask=0;mask<128;++mask)for(unsigned mutation=0;mutation<3;++mutation){Case c={mask,mutation,mode,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    combine dtor mismatch %u/%u/%u exits %d/%d first %lu\n",mask,mutation,mode,u.childStatus,v.childStatus,(unsigned long)f);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(combinemenu_destructor){return run(host,0);}
TL_TEST(combinemenu_deleting_destructor){return run(host,1);}
TL_TEST(combinemenu_destructor_expected_exceptions){unsigned count=0;for(unsigned fault=1;fault<=3;++fault)for(unsigned mutation=0;mutation<3;++mutation)for(unsigned mode=0;mode<2;++mode){Case c={127,mutation,mode,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    dtor unwind mismatch %u/%u/%u exits %d/%d\n",fault,mutation,mode,u.childStatus,v.childStatus);return 1;}++count;}host->log("    EXPECTED DESTRUCTOR EXCEPTIONS: %u matching unwinds, not normal completion coverage\n",count);return 0;}
