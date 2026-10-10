#include <cstring>
#include <new>
#define private public
#define protected public
#include "MerchantMenu.h"
#include "Character.h"
#include "Inventory.h"
#include "SharedStash.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalOwner,(CMerchantMenu*,CCharacter*),"_ZN13CMerchantMenu8setOwnerEP10CCharacter")
TL_ORIGINAL(void,originalPlayer,(CMerchantMenu*,CCharacter*),"_ZN13CMerchantMenu9setPlayerEP10CCharacter")
extern "C" void candidateOwner(CMerchantMenu*,CCharacter*) __asm__("_ZN13CMerchantMenu8setOwnerEP10CCharacter");
extern "C" void candidatePlayer(CMerchantMenu*,CCharacter*) __asm__("_ZN13CMerchantMenu9setPlayerEP10CCharacter");
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(sharedFn,"_ZN12CSharedStash12getSingletonEv")
TL_FUNCTION(removeFn,"_ZN10CInventory14removeListenerEP18iInventoryListener")
TL_FUNCTION(addFn,"_ZN10CInventory11addListenerEP18iInventoryListener")
namespace {
struct Stop{};struct Case{unsigned mask,oldPet,newPet,mutation,mode,fault;};const Case* cs;autotest::Capture* cap;CMerchantMenu* menu;CCharacter* actors[5];CInventory* inventories[7];CSharedStash* shared[2];unsigned events,sharedCalls;
void n(int x){cap->add(&x,4);}int aid(CBaseUnit* p){if(!p)return 0;for(unsigned i=0;i<5;++i)if(p==actors[i])return i+1;return 99;}int iid(CInventory* p){if(!p)return 0;for(unsigned i=0;i<7;++i)if(p==inventories[i])return i+1;return 99;}void event(int x){n(x);n(aid(menu->m_pOwner));n(aid(menu->m_pCanEquipCharacter));if(++events==cs->fault)throw Stop();}
void destroyed(CMerchantMenu* p){event(1);n(p==menu);if(cs->mutation==1)menu->m_pOwner=actors[2];}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){event(2);n(aid(p));n(type);if(cs->mutation==3)menu->m_pOwner=actors[2];return cs->mask&(p==actors[1]?64u:32u);}
CSharedStash* singleton(){event(3);++sharedCalls;unsigned i=cs->mutation==3&&sharedCalls%2==0?1:0;n(i);return cs->mask&128?shared[i]:0;}
void remove(CInventory* p,iInventoryListener* listener){event(4);n(iid(p));n(listener==static_cast<iInventoryListener*>(menu));if(cs->mutation==2){if(cs->mode)menu->m_pCanEquipCharacter=actors[2];else if(p==inventories[3]&&menu->m_pCanEquipCharacter&&!menu->m_pCanEquipCharacter->m_Followers.empty())menu->m_pCanEquipCharacter->m_Followers[0]=actors[4];}}
void add(CInventory* p,iInventoryListener* listener){event(5);n(iid(p));n(listener==static_cast<iInventoryListener*>(menu));if(cs->mutation==3)menu->m_pOwner=actors[2];}
void ptr(unsigned char* p,unsigned off,uintptr_t value){std::memcpy(p+off,&value,8);}
void followers(CCharacter* p,unsigned profile){if(profile)p->m_Followers.push_back(profile==1?0:actors[3]);if(profile==3)p->m_Followers.push_back(actors[4]);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;events=sharedCalls=0;unsigned long long mm[(sizeof(CMerchantMenu)+23)/8],am[5][(sizeof(CCharacter)+7)/8]={0},im[7][(sizeof(CInventory)+7)/8]={0},sm[2][(sizeof(CSharedStash)+7)/8]={0};std::memset(mm,c.mask&4?0xa5:0x5a,sizeof(mm));menu=(CMerchantMenu*)mm;void* vt[20]={0};vt[18]=(void*)&destroyed;*(void***)menu=vt;for(unsigned i=0;i<7;++i)inventories[i]=(CInventory*)im[i];for(unsigned i=0;i<5;++i){actors[i]=(CCharacter*)am[i];new(&actors[i]->m_Followers)std::vector<CCharacter*>;actors[i]->m_pInventory=inventories[i];}actors[0]->m_pInventory=c.mask&8?inventories[0]:0;actors[1]->m_pInventory=c.mask&16?inventories[1]:0;for(unsigned i=0;i<2;++i){shared[i]=(CSharedStash*)sm[i];shared[i]->m_pInventory=c.mask&256?inventories[5+i]:0;}followers(actors[0],c.oldPet);followers(actors[1],c.newPet);followers(actors[2],c.oldPet);menu->m_pOwner=c.mask&1?actors[0]:0;menu->m_pCanEquipCharacter=c.mode?(c.mask&1?actors[0]:0):(c.oldPet?actors[0]:0);if(!c.mode){actors[0]->m_Followers.clear();if(c.oldPet>=2)actors[0]->m_Followers.push_back(c.oldPet==2?0:actors[3]);}CCharacter* next=c.mask&2?(c.mask&4?actors[0]:actors[1]):0;
 detour::Set d;TL_REDIRECT(d,isaFn,&isa);TL_REDIRECT(d,sharedFn,&singleton);TL_REDIRECT(d,removeFn,&remove);TL_REDIRECT(d,addFn,&add);if(d.failed())_exit(60);bool threw=false;try{if(c.mode){if(ours)autotest::invoke(out,&candidatePlayer,menu,next);else autotest::invoke(out,&originalPlayer,menu,next);}else {if(ours)autotest::invoke(out,&candidateOwner,menu,next);else autotest::invoke(out,&originalOwner,menu,next);}}catch(const Stop&){threw=true;}catch(...){_exit(61);}n(threw);n(events);n(sharedCalls);unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0,1);ptr(snapshot,0x50,aid(menu->m_pOwner));ptr(snapshot,0x58,aid(menu->m_pCanEquipCharacter));out.add(snapshot,sizeof(snapshot));for(unsigned i=0;i<5;++i){n(actors[i]->m_Followers.size());for(unsigned j=0;j<actors[i]->m_Followers.size();++j)n(aid(actors[i]->m_Followers[j]));actors[i]->m_Followers.~vector();}}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
int run(const tlhybrid_host* host,unsigned mode){autotest::Coverage coverage(mode?"merchantmenu_player":"merchantmenu_owner",(uint64_t)(uintptr_t)(mode?&originalPlayer:&originalOwner));for(unsigned mask=0;mask<(mode?8u:32u);++mask)for(unsigned oldPet=0;oldPet<4;++oldPet)for(unsigned newPet=0;newPet<(mode?4u:1u);++newPet)for(unsigned mutation=0;mutation<4;++mutation){Case c={mask,oldPet,newPet,mutation,mode,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    merchant owner mismatch mode %u mask %u pets %u/%u mutation %u exits %d/%d first %lu\n",mode,mask,oldPet,newPet,mutation,u.childStatus,v.childStatus,(unsigned long)f);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(merchantmenu_owner){return run(host,0);}
TL_TEST(merchantmenu_player){return run(host,1);}

TL_TEST(merchantmenu_listener_expected_exceptions){unsigned count=0;for(unsigned mode=0;mode<2;++mode)for(unsigned mutation=0;mutation<4;++mutation)for(unsigned fault=1;fault<=(mode?2u:5u);++fault){Case c={mode?3u:507u,mode?2u:3u,2,mutation,mode,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    merchant listener unwind mismatch %u/%u/%u exits %d/%d\n",mode,mutation,fault,u.childStatus,v.childStatus);return 1;}++count;}host->log("    EXPECTED LISTENER EXCEPTIONS: %u matching unwinds, not normal completion coverage\n",count);return 0;}
