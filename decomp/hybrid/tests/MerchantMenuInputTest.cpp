#include <cstring>
#define private public
#define protected public
#include <CEGUI.h>
#include "MerchantMenu.h"
#include "Character.h"
#include "Equipment.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,originalInput,(CMerchantMenu*,void*,float,bool),"_ZN13CMerchantMenu12processInputEPvfb")
extern "C" bool candidateInput(CMerchantMenu*,void*,float,bool) __asm__("_ZN13CMerchantMenu12processInputEPvfb");
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char frontFn[] __asm__("_ZN5CEGUI6Window11moveToFrontEv");
extern "C" char childFn[] __asm__("_ZNK5CEGUI6Window7isChildEPKS0_");
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
namespace {
struct Case{unsigned mask,mutation;};const Case* cs;autotest::Capture* cap;CMerchantMenu* menu;CEquipment* items[2];CEGUI::Window* windows[8];int visibleStates[8];
void n(int x){cap->add(&x,4);}int wid(CEGUI::Window* p){if(!p)return 0;for(unsigned i=0;i<8;++i)if(p==windows[i])return i+1;return 99;}int iid(CEquipment* p){return !p?0:p==items[0]?1:p==items[1]?2:99;}
void open(CMerchantMenu* p,bool value){n(1);n(p==menu);n(value);n(p->m_bUnknown62);if(cs->mutation)p->m_bUnknown3450=!p->m_bUnknown3450;p->m_bOpenPartial=value;}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){n(2);n(p==menu->m_pOwner?3:iid(static_cast<CEquipment*>(p)));n(int(type));if(cs->mutation==1)menu->m_pHoveredEquipment=items[1];return cs->mask&(int(type)==127?1024u:16u);}
void visible(CEGUI::Window* p,bool value){n(3);n(wid(p));n(value);visibleStates[wid(p)-1]=value;if(cs->mutation==2){menu->m_pUnknown38=windows[4];menu->m_pSocketedIconParent=windows[5];}}
void front(CEGUI::Window* p){n(4);n(wid(p));if(cs->mutation==3)menu->m_bUnknown3450=!menu->m_bUnknown3450;}
bool child(const CEGUI::Window* p,const CEGUI::Window* q){n(5);n(wid(const_cast<CEGUI::Window*>(p)));n(wid(const_cast<CEGUI::Window*>(q)));if(cs->mutation==3)menu->m_pUnknown28=windows[7];return cs->mask&(p==windows[3]||p==windows[7]?256u:512u);}
void remove(CEGUI::Window* p,CEGUI::Window* q){n(6);n(wid(p));n(wid(q));q->d_parent=0;}
void ptr(unsigned char* p,unsigned off,uintptr_t v){std::memcpy(p+off,&v,8);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;unsigned long long mm[(sizeof(CMerchantMenu)+23)/8],am[(sizeof(CCharacter)+7)/8]={0},em[2][(sizeof(CEquipment)+7)/8]={0},um[32]={0},wm[8][(sizeof(CEGUI::Window)+7)/8]={0};std::memset(mm,0xa5,sizeof(mm));menu=(CMerchantMenu*)mm;void* vt[24]={0};vt[8]=(void*)&open;*(void***)menu=vt;for(unsigned i=0;i<2;++i){items[i]=(CEquipment*)em[i];items[i]->m_bRangeEnabled=c.mask&64;}for(unsigned i=0;i<8;++i){windows[i]=(CEGUI::Window*)wm[i];visibleStates[i]=-1;}
 menu->m_pOwner=c.mask&4?(CCharacter*)am:0;menu->m_pUnknown28=windows[3];menu->m_pUnknown40=windows[6];menu->m_pGameUI=(CGameUI*)um;CEquipment* dragged=c.mask&8?items[0]:0;std::memcpy((char*)um+0xb8,&dragged,8);menu->m_bUnknown62=c.mask&2;menu->m_bUnknown3450=c.mask&128;menu->m_pHoveredEquipment=c.mask&32?items[1]:0;menu->m_pUnknown38=windows[0];menu->m_pSocketedIconParent=windows[1];menu->m_pUnknown3448=windows[2];windows[2]->d_parent=c.mask&256?windows[3]:0;menu->m_iItemSlotIndexA=37;menu->m_iItemSlotIndexB=-93;menu->m_iPetSlotIndexA=53;menu->m_iPetSlotIndexB=-71;
 detour::Set d;TL_REDIRECT(d,isaFn,&isa);d.redirect(visibleFn,visibleFn,&visible);d.redirect(frontFn,frontFn,&front);d.redirect(childFn,childFn,&child);d.redirect(removeFn,removeFn,&remove);if(d.failed())_exit(60);if(ours)autotest::invoke(out,&candidateInput,menu,(void*)am,-1.25f,bool(c.mask&1));else autotest::invoke(out,&originalInput,menu,(void*)am,-1.25f,bool(c.mask&1));
 unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0,1);ptr(snapshot,0x50,menu->m_pOwner==(CCharacter*)am);ptr(snapshot,0x28,wid(menu->m_pUnknown28));ptr(snapshot,0x40,wid(menu->m_pUnknown40));ptr(snapshot,0x70,menu->m_pGameUI==(CGameUI*)um);ptr(snapshot,0x38,wid(menu->m_pUnknown38));ptr(snapshot,0x30,wid(menu->m_pSocketedIconParent));ptr(snapshot,0x3448,wid(menu->m_pUnknown3448));ptr(snapshot,0x3438,iid(menu->m_pHoveredEquipment));out.add(snapshot,sizeof(snapshot));out.add(visibleStates,sizeof(visibleStates));for(unsigned i=0;i<8;++i)n(wid(windows[i]->d_parent));
}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(merchantmenu_process_input){autotest::Coverage coverage("merchantmenu_process_input",(uint64_t)(uintptr_t)&originalInput);for(unsigned mask=0;mask<2048;++mask)for(unsigned mutation=0;mutation<4;++mutation){Case c={mask,mutation};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    input mismatch %u/%u exits %d/%d\n",mask,mutation,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
