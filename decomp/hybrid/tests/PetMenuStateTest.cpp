#include <cstring>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include "PetMenu.h"
#include "Character.h"
#include "Inventory.h"
#include "Equipment.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalOwner,(CPetMenu*,CCharacter*),"_ZN8CPetMenu8setOwnerEP10CCharacter")
TL_ORIGINAL(void,originalCheck,(CPetMenu*,CEquipment*),"_ZN8CPetMenu14checkForUpdateEP10CEquipment")
TL_ORIGINAL(bool,originalOut,(CPetMenu*,const CEGUI::EventArgs*),"_ZN8CPetMenu15handle_MouseOutERKN5CEGUI9EventArgsE")
TL_ORIGINAL(bool,originalInput,(CPetMenu*,void*,float,bool),"_ZN8CPetMenu12processInputEPvfb")
extern "C" void candidateOwner(CPetMenu*,CCharacter*) __asm__("_ZN8CPetMenu8setOwnerEP10CCharacter");
extern "C" void candidateCheck(CPetMenu*,CEquipment*) __asm__("_ZN8CPetMenu14checkForUpdateEP10CEquipment");
extern "C" bool candidateOut(CPetMenu*,const CEGUI::EventArgs*) __asm__("_ZN8CPetMenu15handle_MouseOutERKN5CEGUI9EventArgsE");
extern "C" bool candidateInput(CPetMenu*,void*,float,bool) __asm__("_ZN8CPetMenu12processInputEPvfb");
TL_FUNCTION(removeListenerFn,"_ZN10CInventory14removeListenerEP18iInventoryListener")
TL_FUNCTION(addListenerFn,"_ZN10CInventory11addListenerEP18iInventoryListener")
TL_FUNCTION(paneFn,"_ZN10CInventory15getRequiredPaneEP10CEquipment")
TL_FUNCTION(slotFn,"_ZN10CInventory17findEquipmentSlotEP10CEquipment")
TL_FUNCTION(itemFn,"_ZN10CInventory18getEquipmentInSlotEj")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
#define IMPORT(N,S) extern "C" char N[] __asm__(S)
IMPORT(visibleFn,"_ZN5CEGUI6Window10setVisibleEb");
IMPORT(frontFn,"_ZN5CEGUI6Window11moveToFrontEv");
IMPORT(isVisibleFn,"_ZNK5CEGUI6Window9isVisibleEb");
IMPORT(isChildFn,"_ZNK5CEGUI6Window7isChildEPKS0_");
IMPORT(removeFn,"_ZN5CEGUI6Window17removeChildWindowEPS0_");
#undef IMPORT
namespace {
struct Case {unsigned kind,mask,profile,slot,pane,mutation;};
const Case* cs;autotest::Capture* cap;CPetMenu* menu;CCharacter* actors[3];CInventory* inv[3];CEquipment* items[2];CGameUI* ui[2];CEGUI::Window* windows[8];int visibleState[8],notifications,updates,destroyed;unsigned childMask;
void n(int v){cap->add(&v,4);}template<class T>T& at(void* p,size_t o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
int aid(CCharacter* p){if(!p)return 0;for(int i=0;i<3;++i)if(p==actors[i])return i+1;return 99;}int iid(CInventory* p){if(!p)return 0;for(int i=0;i<3;++i)if(p==inv[i])return i+1;return 99;}int wid(CEGUI::Window* p){if(!p)return 0;for(int i=0;i<8;++i)if(p==windows[i])return i+1;return 99;}int eid(void* p){return !p?0:p==items[0]?1:p==items[1]?2:99;}
void update(CPetMenu* p){n(1);n(p==menu);n(aid(p->m_pCharacter));++updates;if(cs->mutation)for(unsigned i=0;i<3;++i)p->m_TabNotifications[i]=true;}
void destroy(CPetMenu* p){n(2);n(p==menu);++destroyed;if(cs->mutation)p->m_pCharacter=actors[2];}
void close(CPetMenu* p,bool value){n(3);n(p==menu);n(value);if(cs->mutation)p->m_pGameUI=ui[1];if(cs->mutation==2)p->m_Data9188=0;}
void removeListener(CInventory* p,iInventoryListener* listener){n(4);n(iid(p));n(listener==static_cast<iInventoryListener*>(menu));n(aid(menu->m_pCharacter));if(cs->mutation)menu->m_pCharacter=actors[0];}
void addListener(CInventory* p,iInventoryListener* listener){n(5);n(iid(p));n(listener==static_cast<iInventoryListener*>(menu));n(aid(menu->m_pCharacter));if(cs->mutation==2)menu->m_pCharacter=actors[2];}
int pane(CInventory* p,CEquipment* item){n(6);n(iid(p));n(eid(item));if(cs->mutation)menu->m_pCharacter=actors[1];int a[]={-1,0,1,2,3};return a[cs->pane];}
int slot(CInventory* p,CEquipment* item){n(7);n(iid(p));n(eid(item));if(cs->mutation==2)menu->m_pFishSlots=windows[7];int a[]={-1,0,18,19,81};return a[cs->slot];}
CEquipment* item(CInventory* p,unsigned index){n(8);n(iid(p));n(index);if(cs->mutation)menu->m_pGameUI=ui[1];if(cs->mutation==2)menu->m_pHoverObject=items[1];return cs->profile==0?0:items[cs->profile-1];}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){n(9);n(eid(p));n(int(type));if(cs->mutation==2)menu->m_pHoverObject=0;return cs->kind==3?bool(cs->mask&8):bool(cs->mask&16);}
void visible(CEGUI::Window* p,bool value){n(10);n(wid(p));n(value);int i=wid(p)-1;if(i<0||i>=8)_exit(60);visibleState[i]=value;if(cs->mutation==2&&p==windows[0])menu->m_pSocketOverlay=windows[7];}
void front(CEGUI::Window* p){n(11);n(wid(p));}
bool isVisible(const CEGUI::Window* p,bool parent){n(12);n(wid(const_cast<CEGUI::Window*>(p)));n(parent);return cs->mask&4;}
bool isChild(const CEGUI::Window* p,const CEGUI::Window* q){n(13);n(wid(const_cast<CEGUI::Window*>(p)));n(wid(const_cast<CEGUI::Window*>(q)));return p==windows[2]?bool(childMask&1):p==windows[3]?bool(childMask&2):false;}
void remove(CEGUI::Window* p,CEGUI::Window* q){n(14);n(wid(p));n(wid(q));if(p==windows[2])childMask&=~1u;if(p==windows[3])childMask&=~2u;}
void ptr(unsigned char* bytes,unsigned offset,unsigned value){uintptr_t v=value;std::memcpy(bytes+offset,&v,sizeof(v));}
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long mm[(sizeof(CPetMenu)+16+7)/8],am[3][0x800/8],im[3][0x200/8],em[2][0x800/8],um[2][0x200/8],wm[8][(sizeof(CEGUI::Window)+7)/8];std::memset(mm,c.profile==1?0x5a:0xa5,sizeof(mm));std::memset(am,0,sizeof(am));std::memset(im,0,sizeof(im));std::memset(em,0,sizeof(em));std::memset(um,0,sizeof(um));std::memset(wm,0,sizeof(wm));cs=&c;cap=&out;menu=(CPetMenu*)mm;updates=destroyed=notifications=0;childMask=((c.mask&128)?1:0)|((c.mask&256)?2:0);
 void* table[20]={0};table[8]=(void*)&close;table[9]=(void*)&update;table[18]=(void*)&destroy;*(void***)menu=table;for(unsigned i=0;i<3;++i){actors[i]=(CCharacter*)am[i];inv[i]=(CInventory*)im[i];actors[i]->m_pInventory=c.kind==0?((c.mask&(1u<<i))?inv[i]:0):inv[i];}
 for(unsigned i=0;i<2;++i){items[i]=(CEquipment*)em[i];ui[i]=(CGameUI*)um[i];at<CBaseUnit*>(ui[i],0xb8)=c.kind==3?((c.mask&4)?items[i]:0):((c.mask&8)?items[i]:0);at<bool>(items[i],0x198)=c.mask&32;}
 for(unsigned i=0;i<8;++i){windows[i]=(CEGUI::Window*)wm[i];visibleState[i]=-1;}
 menu->m_pCharacter=actors[0];menu->m_pGameUI=ui[0];menu->m_pSocketedIconParent=windows[0];menu->m_pSocketOverlay=windows[1];menu->m_pPanel=windows[2];menu->m_pForeground48=windows[3];menu->m_pSlotGlow=windows[4];menu->m_pBackpackSlots=windows[5];menu->m_pSpellsSlots=windows[6];menu->m_pFishSlots=windows[7];menu->m_pHoverObject=c.kind==3?((c.mask&16)?items[0]:0):((c.mask&32)?items[0]:0);menu->m_Data9188=bool(c.mask&64);menu->m_Data6a[0]=bool(c.mask&2);menu->m_bOpenPartial=false;menu->m_bFullyClosed=true;
 for(unsigned i=0;i<3;++i)menu->m_TabNotifications[i]=bool((c.kind==1?c.profile:c.mask)&(1u<<i));menu->m_ClickedSlot=123;menu->m_RightClickedSlot=-45;
 CCharacter* owner=0;if(c.kind==0){menu->m_pCharacter=c.profile==0?0:actors[0];owner=c.slot==0?0:c.slot==1?actors[0]:actors[1];}
 if(c.kind==1)actors[0]->m_pInventory=(c.mask&2)?inv[0]:0;
 if(c.kind==2)menu->m_pCharacter=(c.mask&2)?actors[0]:0;
 int index=c.slot==0?-1:c.slot==1?0:81;windows[0]->d_userData=&index;CEGUI::WindowEventArgs e((c.mask&1)?windows[0]:0);
 detour::Set d;TL_REDIRECT(d,removeListenerFn,&removeListener);TL_REDIRECT(d,addListenerFn,&addListener);TL_REDIRECT(d,paneFn,&pane);TL_REDIRECT(d,slotFn,&slot);TL_REDIRECT(d,itemFn,&item);TL_REDIRECT(d,isaFn,&isa);
 d.redirect(visibleFn,visibleFn,&visible);d.redirect(frontFn,frontFn,&front);d.redirect(isVisibleFn,isVisibleFn,&isVisible);d.redirect(isChildFn,isChildFn,&isChild);d.redirect(removeFn,removeFn,&remove);if(d.failed())_exit(61);
 if(c.kind==0){if(ours)autotest::invoke(out,&candidateOwner,menu,owner);else autotest::invoke(out,&originalOwner,menu,owner);}
 if(c.kind==1){CEquipment* x=(c.mask&1)?items[0]:0;if(ours)autotest::invoke(out,&candidateCheck,menu,x);else autotest::invoke(out,&originalCheck,menu,x);}
 if(c.kind==2){if(ours)autotest::invoke(out,&candidateOut,menu,static_cast<const CEGUI::EventArgs*>(&e));else autotest::invoke(out,&originalOut,menu,static_cast<const CEGUI::EventArgs*>(&e));}
 if(c.kind==3){float dt=c.profile?std::numeric_limits<float>::quiet_NaN():0.25f;if(ours)autotest::invoke(out,&candidateInput,menu,(void*)0x1234,dt,bool(c.mask&1));else autotest::invoke(out,&originalInput,menu,(void*)0x1234,dt,bool(c.mask&1));}
 n(updates);n(destroyed);n(childMask);for(unsigned i=0;i<8;++i)n(visibleState[i]);unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(snapshot));ptr(snapshot,0,1);ptr(snapshot,0x58,aid(menu->m_pCharacter));ptr(snapshot,0x90,menu->m_pGameUI==ui[0]?1:menu->m_pGameUI==ui[1]?2:99);ptr(snapshot,0x30,wid(menu->m_pSocketedIconParent));ptr(snapshot,0x40,wid(menu->m_pSocketOverlay));ptr(snapshot,0x28,wid(menu->m_pPanel));ptr(snapshot,0x48,wid(menu->m_pForeground48));ptr(snapshot,0x9110,wid(menu->m_pSlotGlow));ptr(snapshot,0x91c0,wid(menu->m_pBackpackSlots));ptr(snapshot,0x91c8,wid(menu->m_pSpellsSlots));ptr(snapshot,0x91d0,wid(menu->m_pFishSlots));ptr(snapshot,0x1370,eid(menu->m_pHoverObject));cap->add(snapshot,sizeof(snapshot));
}
void a(void* p,autotest::Capture& o){side(*(Case*)p,false,o);}void b(void* p,autotest::Capture& o){side(*(Case*)p,true,o);}
int run(const tlhybrid_host* host,unsigned kind,const char* name,uint64_t address){autotest::Coverage coverage(name,address);unsigned masks=kind==0?8:kind==1?8:kind==2?64:512;unsigned profiles=kind==0?2:kind==1?8:kind==2?3:kind==3?2:1;unsigned slots=kind==0?3:kind==1?5:kind==2?3:1;unsigned panes=kind==1?5:1;
 for(unsigned mask=0;mask<masks;++mask)for(unsigned profile=0;profile<profiles;++profile)for(unsigned slot=0;slot<slots;++slot)for(unsigned pane=0;pane<panes;++pane)for(unsigned mutation=0;mutation<3;++mutation){Case c={kind,mask,profile,slot,pane,mutation};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    pet state mismatch %u/%u/%u/%u/%u/%u exits %d/%d first %lu lengths %lu/%lu\n",kind,mask,profile,slot,pane,mutation,u.childStatus,v.childStatus,(unsigned long)f,(unsigned long)u.capture.length,(unsigned long)v.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);return 0;}
}
TL_TEST(petmenu_owner){return run(host,0,"petmenu_owner",(uint64_t)(uintptr_t)&originalOwner);}
TL_TEST(petmenu_notifications){return run(host,1,"petmenu_notifications",(uint64_t)(uintptr_t)&originalCheck);}
TL_TEST(petmenu_mouse_out){return run(host,2,"petmenu_mouse_out",(uint64_t)(uintptr_t)&originalOut);}
TL_TEST(petmenu_input){return run(host,3,"petmenu_input",(uint64_t)(uintptr_t)&originalInput);}
