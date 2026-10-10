#include <cstring>
#define private public
#define protected public
#include <CEGUI.h>
#include "Equipment.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalDestroy,(CEquipment*),"_ZN10CEquipment11destroyIconEv")
extern "C" void candidateDestroy(CEquipment*) __asm__("_ZN10CEquipment11destroyIconEv");
TL_FUNCTION(textFn,"_ZN5CItem15destroyItemTextEv")
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char destroyFn[] __asm__("_ZN5CEGUI13WindowManager13destroyWindowEPNS_6WindowE");
namespace {
struct Stop{};struct Case{unsigned mask,profile,mutation,fault;};const Case* cs;autotest::Capture* cap;CEquipment* items[4];CEGUI::Window* windows[6];CEGUI::WindowManager* manager;unsigned events;
void n(int x){cap->add(&x,4);}int wid(void* p){if(!p)return 0;for(unsigned i=0;i<6;++i)if(p==windows[i])return i+1;return 99;}int iid(void* p){if(!p)return 0;for(unsigned i=0;i<4;++i)if(p==items[i])return i+1;return 99;}
void event(int x){n(x);for(unsigned i=0;i<4;++i)n(wid(items[i]->m_pIconWindow));if(++events==cs->fault)throw Stop();}
void remove(CEGUI::Window* p,CEGUI::Window* q){event(1);n(wid(p));n(wid(q));if(cs->mutation==1&&q==windows[0])items[0]->m_pIconWindow=windows[4];}
void destroy(CEGUI::WindowManager* p,CEGUI::Window* q){event(2);n(p==manager);n(wid(q));if(cs->mutation==2)items[0]->m_SocketedEquipment.m_nCount=0;}
void text(CItem* p){event(3);n(iid(p));if(cs->mutation==3&&p!=items[0])items[0]->m_SocketedEquipment.m_nCount=0;}
void ptr(unsigned char* p,unsigned off,uintptr_t x){std::memcpy(p+off,&x,8);}
void side(void* data,autotest::Capture& out,bool ours){
 Case c=*(Case*)data;cs=&c;cap=&out;events=0;unsigned long long mm[4][(sizeof(CEquipment)+23)/8],wm[6][(sizeof(CEGUI::Window)+7)/8]={0},service[8]={0};std::memset(mm,0xa5,sizeof(mm));CEquipment* refs[3];
 for(unsigned i=0;i<6;++i)windows[i]=(CEGUI::Window*)wm[i];
 for(unsigned i=0;i<4;++i){items[i]=(CEquipment*)mm[i];items[i]->m_pIconWindow=c.mask&(1u<<i)?windows[i]:0;items[i]->m_SocketedEquipment.m_pData=0;items[i]->m_SocketedEquipment.m_nCount=0;items[i]->m_SocketedEquipment.m_nCapacity=0;windows[i]->d_parent=c.mask&16?windows[5]:0;}
 windows[4]->d_parent=windows[5];for(unsigned i=0;i<3;++i)refs[i]=items[i+1];
 items[0]->m_SocketedEquipment.m_pData=refs;items[0]->m_SocketedEquipment.m_nCount=c.profile;items[0]->m_SocketedEquipment.m_nCapacity=c.mask&32?1:3;
 manager=(CEGUI::WindowManager*)service;CEGUI::WindowManager* old=CEGUI::WindowManager::ms_Singleton;CEGUI::WindowManager::ms_Singleton=manager;
 detour::Set d;TL_REDIRECT(d,textFn,&text);d.redirect(removeFn,removeFn,&remove);d.redirect(destroyFn,destroyFn,&destroy);if(d.failed())_exit(60);bool threw=false;
 try{if(ours)autotest::invoke(out,&candidateDestroy,items[0]);else autotest::invoke(out,&originalDestroy,items[0]);}catch(const Stop&){threw=true;}catch(...){_exit(61);}
 n(threw);n(events);for(unsigned i=0;i<4;++i){unsigned char snapshot[sizeof(mm[i])];std::memcpy(snapshot,items[i],sizeof(snapshot));ptr(snapshot,0x2c8,wid(items[i]->m_pIconWindow));if(items[i]->m_SocketedEquipment.m_pData==refs)ptr(snapshot,0x3e8,1);out.add(snapshot,sizeof(snapshot));}d.restore();CEGUI::WindowManager::ms_Singleton=old;
}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(equipment_destroy_icon){autotest::Coverage coverage("equipment_destroy_icon",(uint64_t)(uintptr_t)&originalDestroy);for(unsigned mask=0;mask<64;++mask)for(unsigned profile=0;profile<4;++profile)for(unsigned mutation=0;mutation<4;++mutation){Case c={mask,profile,mutation,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    destroy icon mismatch %u/%u/%u exits %d/%d\n",mask,profile,mutation,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
TL_TEST(equipment_destroy_icon_expected_exceptions){unsigned count=0;for(unsigned fault=1;fault<=12;++fault){Case c={31,3,0,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    destroy icon unwind mismatch %u exits %d/%d\n",fault,u.childStatus,v.childStatus);return 1;}++count;}host->log("    EXPECTED ICON EXCEPTIONS: %u matching unwinds\n",count);return 0;}
