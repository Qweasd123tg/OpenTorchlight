#include <cstring>
#define private public
#define protected public
#include <CEGUI.h>
#include "EnchantMenu.h"
#include "Character.h"
#include "Inventory.h"
#include "Equipment.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,originalOut,(CEnchantMenu*,const CEGUI::EventArgs*),"_ZN12CEnchantMenu15handle_MouseOutERKN5CEGUI9EventArgsE")
extern "C" bool candidateOut(CEnchantMenu*,const CEGUI::EventArgs*) __asm__("_ZN12CEnchantMenu15handle_MouseOutERKN5CEGUI9EventArgsE");
TL_FUNCTION(itemFn,"_ZN10CInventory18getEquipmentInSlotEj")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
namespace {
struct Case {unsigned mask,slot,profile,mutation;};const Case* cs;autotest::Capture* cap;CEnchantMenu* menu;CCharacter* actor;CInventory* inventory;CEquipment* items[2];CGameUI* ui;CEGUI::Window* windows[3];int states[3];
void n(int v){cap->add(&v,4);}int iid(CEquipment* p){return !p?0:p==items[0]?1:p==items[1]?2:99;}int wid(CEGUI::Window* p){for(unsigned i=0;i<3;++i)if(p==windows[i])return i+1;return 99;}
CEquipment* getItem(CInventory* p,unsigned slot){n(1);n(p==inventory);n(slot);if(cs->mutation)menu->m_pHoverObject=cs->mask&8?items[0]:0;return cs->mask&4?items[0]:0;}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){n(2);n(p==items[1]);n(int(type));if(cs->mutation==2)menu->m_pForeground=windows[2];return cs->mask&32;}
void visible(CEGUI::Window* p,bool value){n(3);n(wid(p));n(value);states[wid(p)-1]=value;if(cs->mutation)menu->m_pForeground=windows[2];}
void ptr(unsigned char* p,size_t off,uintptr_t value){std::memcpy(p+off,&value,8);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;unsigned long long mm[(sizeof(CEnchantMenu)+23)/8],am[(sizeof(CCharacter)+7)/8]={0},im[(sizeof(CInventory)+7)/8]={0},em[2][(sizeof(CEquipment)+7)/8]={0},um[32]={0},wm[3][(sizeof(CEGUI::Window)+7)/8]={0};std::memset(mm,0xa5,sizeof(mm));menu=(CEnchantMenu*)mm;actor=(CCharacter*)am;inventory=(CInventory*)im;items[0]=(CEquipment*)em[0];items[1]=(CEquipment*)em[1];ui=(CGameUI*)um;actor->m_pInventory=inventory;menu->m_pCharacter=c.mask&2?actor:0;menu->m_pGameUI=ui;menu->m_pHoverObject=c.mask&8?items[0]:c.profile==2?items[1]:0;CEquipment* dragged=c.mask&16?items[1]:0;std::memcpy((char*)ui+0xb8,&dragged,8);for(unsigned i=0;i<3;++i){windows[i]=(CEGUI::Window*)wm[i];states[i]=-1;}menu->m_pSocketedIconParent=windows[0];menu->m_pForeground=windows[1];const int mapped[]={0,19,(-2147483647-1),2147483647};for(unsigned i=0;i<1;++i)menu->m_aiSlotData[i]=mapped[(i+c.profile)%4];int slot=c.slot;windows[2]->d_userData=&slot;CEGUI::WindowEventArgs event(c.mask&1?windows[2]:0);
 detour::Set d;TL_REDIRECT(d,itemFn,&getItem);TL_REDIRECT(d,isaFn,&isa);d.redirect(visibleFn,visibleFn,&visible);if(d.failed())_exit(60);if(ours)autotest::invoke(out,&candidateOut,menu,static_cast<const CEGUI::EventArgs*>(&event));else autotest::invoke(out,&originalOut,menu,static_cast<const CEGUI::EventArgs*>(&event));unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0x60,menu->m_pCharacter==actor);ptr(snapshot,0x80,menu->m_pGameUI==ui);ptr(snapshot,0xf0,iid(menu->m_pHoverObject));ptr(snapshot,0x30,wid(menu->m_pSocketedIconParent));ptr(snapshot,0x38,wid(menu->m_pForeground));cap->add(snapshot,sizeof(snapshot));cap->add(states,sizeof(states));}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(enchantmenu_mouse_out){autotest::Coverage coverage("enchantmenu_mouse_out",(uint64_t)(uintptr_t)&originalOut);for(unsigned mask=0;mask<64;++mask)for(unsigned slot=0;slot<1;++slot)for(unsigned profile=0;profile<3;++profile)for(unsigned mutation=0;mutation<3;++mutation){Case c={mask,slot,profile,mutation};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    enchant mouseout mismatch %u/%u/%u/%u exits %d/%d\n",mask,slot,profile,mutation,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
