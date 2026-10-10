#include <cstring>
#include <new>
#define private public
#define protected public
#include <CEGUI.h>
#include "StashMenu.h"
#include "Character.h"
#include "Inventory.h"
#include "Equipment.h"
#include "SharedStash.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,originalOut,(CStashMenu*,const CEGUI::EventArgs*),"_ZN10CStashMenu15handle_MouseOutERKN5CEGUI9EventArgsE")
TL_ORIGINAL(bool,originalPetOut,(CStashMenu*,const CEGUI::EventArgs*),"_ZN10CStashMenu18handle_PetMouseOutERKN5CEGUI9EventArgsE")
extern "C" bool candidateOut(CStashMenu*,const CEGUI::EventArgs*) __asm__("_ZN10CStashMenu15handle_MouseOutERKN5CEGUI9EventArgsE");
extern "C" bool candidatePetOut(CStashMenu*,const CEGUI::EventArgs*) __asm__("_ZN10CStashMenu18handle_PetMouseOutERKN5CEGUI9EventArgsE");
TL_FUNCTION(itemFn,"_ZN10CInventory18getEquipmentInSlotEj")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(sharedFn,"_ZN12CSharedStash12getSingletonEv")
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
namespace {
struct Case{unsigned mask,slot,profile,mutation,mode;};const Case* cs;autotest::Capture* cap;CStashMenu* menu;CCharacter* actors[3];CInventory* inventories[4];CEquipment* items[2];CGameUI* ui;CSharedStash* shared;CEGUI::Window* windows[3];int states[3];
void n(int x){cap->add(&x,4);}int aid(CBaseUnit* p){if(!p)return 0;for(unsigned i=0;i<3;++i)if(p==actors[i])return i+1;return 99;}int iid(CEquipment* p){return !p?0:p==items[0]?1:p==items[1]?2:99;}int wid(CEGUI::Window* p){for(unsigned i=0;i<3;++i)if(p==windows[i])return i+1;return p?99:0;}
CEquipment* getItem(CInventory* p,unsigned slot){n(1);unsigned id=99;for(unsigned i=0;i<4;++i)if(p==inventories[i])id=i+1;n(id);n(slot);if(cs->mutation)menu->m_pHoverObject=cs->mask&8?items[0]:0;if(cs->mutation==1)menu->m_pCharacter=actors[2];return cs->mask&4?items[0]:0;}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){n(2);n(int(type)==170?aid(p):iid(static_cast<CEquipment*>(p)));n(type);if(cs->mutation==2){menu->m_pUnknown38=windows[2];menu->m_pOwner=actors[1];}return cs->mask&(int(type)==170?64u:32u);}
CSharedStash* singleton(){n(4);return shared;}
void visible(CEGUI::Window* p,bool value){n(3);n(wid(p));n(value);states[wid(p)-1]=value;if(cs->mutation)menu->m_pUnknown38=windows[2];}
void ptr(unsigned char* p,unsigned off,uintptr_t v){std::memcpy(p+off,&v,8);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;unsigned long long mm[(sizeof(CStashMenu)+23)/8],am[3][(sizeof(CCharacter)+7)/8]={0},im[4][(sizeof(CInventory)+7)/8]={0},em[2][(sizeof(CEquipment)+7)/8]={0},um[32]={0},sm[(sizeof(CSharedStash)+7)/8]={0},wm[3][(sizeof(CEGUI::Window)+7)/8]={0};std::memset(mm,0xa5,sizeof(mm));menu=(CStashMenu*)mm;for(unsigned i=0;i<4;++i)inventories[i]=(CInventory*)im[i];for(unsigned i=0;i<3;++i){actors[i]=(CCharacter*)am[i];actors[i]->m_pInventory=inventories[i];new(&actors[i]->m_Followers)std::vector<CCharacter*>;}if(c.profile)actors[0]->m_Followers.push_back(c.profile==1?0:actors[1]);if(c.profile==3)actors[0]->m_Followers.push_back(actors[2]);items[0]=(CEquipment*)em[0];items[1]=(CEquipment*)em[1];ui=(CGameUI*)um;shared=(CSharedStash*)sm;shared->m_pInventory=inventories[3];menu->m_pOwner=c.mask&2?actors[0]:0;menu->m_pCharacter=actors[0];menu->m_pGameUI=ui;menu->m_pHoverObject=c.mask&8?items[0]:c.profile==2?items[1]:0;CEquipment* dragged=c.mask&16?items[1]:0;std::memcpy((char*)ui+0xb8,&dragged,8);for(unsigned i=0;i<3;++i){windows[i]=(CEGUI::Window*)wm[i];states[i]=-1;}menu->m_pUnknown30=windows[0];menu->m_pUnknown38=windows[1];const int values[]={0,19,(-2147483647-1),2147483647};int slot=values[c.slot];windows[2]->d_userData=&slot;CEGUI::WindowEventArgs event(c.mask&1?windows[2]:0);
 detour::Set d;TL_REDIRECT(d,itemFn,&getItem);TL_REDIRECT(d,isaFn,&isa);TL_REDIRECT(d,sharedFn,&singleton);d.redirect(visibleFn,visibleFn,&visible);if(d.failed())_exit(60);if(ours)autotest::invoke(out,c.mode?&candidatePetOut:&candidateOut,menu,static_cast<const CEGUI::EventArgs*>(&event));else autotest::invoke(out,c.mode?&originalPetOut:&originalOut,menu,static_cast<const CEGUI::EventArgs*>(&event));unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0x50,aid(menu->m_pOwner));ptr(snapshot,0x58,aid(menu->m_pCharacter));ptr(snapshot,0x70,menu->m_pGameUI==ui);ptr(snapshot,0x3408,iid(menu->m_pHoverObject));ptr(snapshot,0x30,wid(menu->m_pUnknown30));ptr(snapshot,0x38,wid(menu->m_pUnknown38));out.add(snapshot,sizeof(snapshot));out.add(states,sizeof(states));for(unsigned i=0;i<3;++i)actors[i]->m_Followers.~vector();}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
int run(const tlhybrid_host* host,unsigned mode){autotest::Coverage coverage(mode?"stashmenu_pet_mouse_out":"stashmenu_mouse_out",(uint64_t)(uintptr_t)(mode?&originalPetOut:&originalOut));for(unsigned mask=0;mask<(mode?64u:128u);++mask)for(unsigned slot=0;slot<4;++slot)for(unsigned profile=0;profile<4;++profile)for(unsigned mutation=0;mutation<3;++mutation){Case c={mask,slot,profile,mutation,mode};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    stash mouseout mismatch %u/%u/%u/%u/%u exits %d/%d\n",mode,mask,slot,profile,mutation,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(stashmenu_mouse_out){return run(host,0);}
TL_TEST(stashmenu_pet_mouse_out){return run(host,1);}
