#include <cstring>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include "MerchantMenu.h"
#include "Character.h"
#include "Inventory.h"
#include "Equipment.h"
#include "SharedStash.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,originalHover,(CMerchantMenu*,const CEGUI::EventArgs*),"_ZN13CMerchantMenu16handle_MouseOverERKN5CEGUI9EventArgsE")
TL_ORIGINAL(bool,originalPetHover,(CMerchantMenu*,const CEGUI::EventArgs*),"_ZN13CMerchantMenu19handle_PetMouseOverERKN5CEGUI9EventArgsE")
extern "C" bool candidateHover(CMerchantMenu*,const CEGUI::EventArgs*) __asm__("_ZN13CMerchantMenu16handle_MouseOverERKN5CEGUI9EventArgsE");
extern "C" bool candidatePetHover(CMerchantMenu*,const CEGUI::EventArgs*) __asm__("_ZN13CMerchantMenu19handle_PetMouseOverERKN5CEGUI9EventArgsE");
TL_FUNCTION(itemFn,"_ZN10CInventory18getEquipmentInSlotEj")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(sharedFn,"_ZN12CSharedStash12getSingletonEv")
extern "C" char positionFn[] __asm__("_ZNK5CEGUI6Window11getPositionEv");
extern "C" char widthFn[] __asm__("_ZNK5CEGUI6Window8getWidthEv");
extern "C" char heightFn[] __asm__("_ZNK5CEGUI6Window9getHeightEv");
extern "C" char frontFn[] __asm__("_ZN5CEGUI6Window11moveToFrontEv");
extern "C" char backFn[] __asm__("_ZN5CEGUI6Window10moveToBackEv");
extern "C" char childFn[] __asm__("_ZNK5CEGUI6Window7isChildEPKS0_");
extern "C" char addFn[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");
extern "C" char positionSetFn[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char sizeSetFn[] __asm__("_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
namespace {
struct Case{unsigned mask,slot,profile,geometry,mutation,mode;};const Case* cs;autotest::Capture* cap;CMerchantMenu* menu;CCharacter* actors[3];CInventory* inventories[4];CEquipment* items[2];CGameUI* ui;CSharedStash* shared;CEGUI::Window* windows[12];int states[12];CEGUI::UVector2 positions[12],dimensions[12];int actualSlot;unsigned positionCalls;
void n(int x){cap->add(&x,4);}int aid(CBaseUnit* p){if(!p)return 0;for(unsigned i=0;i<3;++i)if(p==actors[i])return i+1;return 99;}int iid(CEquipment* p){return !p?0:p==items[0]?1:p==items[1]?2:99;}int wid(CEGUI::Window* p){for(unsigned i=0;i<12;++i)if(p==windows[i])return i+1;return p?99:0;}
CEquipment* getItem(CInventory* p,unsigned slot){n(1);unsigned id=99;for(unsigned i=0;i<4;++i)if(p==inventories[i])id=i+1;n(id);n(slot);if(cs->mutation)menu->m_pHoveredEquipment=cs->mask&8?items[0]:0;if(cs->mutation==1)menu->m_pCanEquipCharacter=actors[2];return cs->mask&4?items[0]:0;}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){n(2);n(int(type)==170?aid(p):iid(static_cast<CEquipment*>(p)));n(type);if(cs->mutation==2){menu->m_pUnknown38=windows[2];menu->m_pOwner=actors[1];}return cs->mask&(int(type)==170?128u:32u);}
CSharedStash* singleton(){n(4);return shared;}
void visible(CEGUI::Window* p,bool value){n(3);n(wid(p));n(value);states[wid(p)-1]=value;if(cs->mutation)menu->m_pUnknown38=windows[2];}
void replaceSlot(CEGUI::Window* p){if(cs->mode)menu->m_pSlotWindows[actualSlot]=p;else menu->m_pSocketedSizeWindows[actualSlot]=p;}
const CEGUI::UVector2& position(const CEGUI::Window* p){n(5);int id=wid(const_cast<CEGUI::Window*>(p));n(id);++positionCalls;if(cs->mutation==1&&positionCalls==1)replaceSlot(windows[10]);if(cs->mutation==4)menu->m_pUnknown28=windows[4];return positions[id-1];}
CEGUI::UDim width(const CEGUI::Window* p){n(6);int id=wid(const_cast<CEGUI::Window*>(p));n(id);if(cs->mutation==3)replaceSlot(windows[10]);return dimensions[id-1].d_x;}
CEGUI::UDim height(const CEGUI::Window* p){n(7);int id=wid(const_cast<CEGUI::Window*>(p));n(id);return dimensions[id-1].d_y;}
bool child(const CEGUI::Window* p,const CEGUI::Window* q){n(8);n(wid(const_cast<CEGUI::Window*>(p)));n(wid(const_cast<CEGUI::Window*>(q)));if(cs->mutation==5)menu->m_pUnknown3448=windows[5];return cs->mask&64;}
void add(CEGUI::Window* p,CEGUI::Window* q){n(9);n(wid(p));n(wid(q));q->d_parent=p;}
void setPosition(CEGUI::Window* p,const CEGUI::UVector2& value){n(10);int id=wid(p);n(id);cap->add(&value,sizeof(value));positions[id-1]=value;}
void setSize(CEGUI::Window* p,const CEGUI::UVector2& value){n(11);int id=wid(p);n(id);cap->add(&value,sizeof(value));dimensions[id-1]=value;}
void front(CEGUI::Window* p){n(12);n(wid(p));}
void back(CEGUI::Window* p){n(13);n(wid(p));}
void ptr(unsigned char* p,unsigned off,uintptr_t v){std::memcpy(p+off,&v,8);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;positionCalls=0;unsigned long long mm[(sizeof(CMerchantMenu)+23)/8],am[3][(sizeof(CCharacter)+7)/8]={0},im[4][(sizeof(CInventory)+7)/8]={0},em[2][(sizeof(CEquipment)+7)/8]={0},um[32]={0},sm[(sizeof(CSharedStash)+7)/8]={0},wm[12][(sizeof(CEGUI::Window)+7)/8]={0};std::memset(mm,0xa5,sizeof(mm));menu=(CMerchantMenu*)mm;for(unsigned i=0;i<4;++i)inventories[i]=(CInventory*)im[i];for(unsigned i=0;i<3;++i){actors[i]=(CCharacter*)am[i];actors[i]->m_pInventory=inventories[i];new(&actors[i]->m_Followers)std::vector<CCharacter*>;}if(c.profile)actors[0]->m_Followers.push_back(c.profile==1?0:actors[1]);if(c.profile==3)actors[0]->m_Followers.push_back(actors[2]);items[0]=(CEquipment*)em[0];items[1]=(CEquipment*)em[1];items[0]->m_bUnknown348=c.mask&8;items[0]->m_iSocketCount=c.mask&16?2:0;ui=(CGameUI*)um;shared=(CSharedStash*)sm;shared->m_pInventory=inventories[3];menu->m_pOwner=c.mask&2?actors[0]:0;menu->m_bOpenPartial=c.mask&128;menu->m_pCanEquipCharacter=actors[0];menu->m_pGameUI=ui;menu->m_pHoveredEquipment=c.mask&8?items[0]:c.profile==2?items[1]:0;CEquipment* dragged=c.mask&16?items[1]:0;std::memcpy((char*)ui+0xb8,&dragged,8);const float values[]={0.0f,17.25f,-9.5f,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};for(unsigned i=0;i<12;++i){windows[i]=(CEGUI::Window*)wm[i];states[i]=-1;positions[i]=CEGUI::UVector2(CEGUI::UDim(values[c.geometry],float(i)+0.25f),CEGUI::UDim(values[(c.geometry+1)%6],-float(i)-0.75f));dimensions[i]=CEGUI::UVector2(CEGUI::UDim(values[(c.geometry+2)%6],31.25f+i),CEGUI::UDim(values[(c.geometry+3)%6],41.75f-i));}menu->m_pSocketedIconParent=windows[0];menu->m_pUnknown38=windows[1];menu->m_pUnknown3448=windows[2];menu->m_pUnknown28=windows[3];menu->m_pUnknown40=windows[4];menu->m_bUnknown3450=false;const int slots[]={0,19,81,144};int slot=slots[c.slot];actualSlot=slot;for(unsigned i=0;i<145;++i)menu->m_pSocketedSizeWindows[i]=windows[6];for(unsigned i=0;i<82;++i)menu->m_pSlotWindows[i]=windows[7];menu->m_pSocketedSizeWindows[slot]=windows[8];if(slot<82)menu->m_pSlotWindows[slot]=windows[9];windows[11]->d_userData=&slot;CEGUI::WindowEventArgs event(c.mask&1?windows[11]:0);
 detour::Set d;TL_REDIRECT(d,itemFn,&getItem);TL_REDIRECT(d,isaFn,&isa);TL_REDIRECT(d,sharedFn,&singleton);d.redirect(visibleFn,visibleFn,&visible);d.redirect(positionFn,positionFn,&position);d.redirect(widthFn,widthFn,&width);d.redirect(heightFn,heightFn,&height);d.redirect(frontFn,frontFn,&front);d.redirect(backFn,backFn,&back);d.redirect(childFn,childFn,&child);d.redirect(addFn,addFn,&add);d.redirect(positionSetFn,positionSetFn,&setPosition);d.redirect(sizeSetFn,sizeSetFn,&setSize);if(d.failed())_exit(60);if(ours)autotest::invoke(out,c.mode?&candidatePetHover:&candidateHover,menu,static_cast<const CEGUI::EventArgs*>(&event));else autotest::invoke(out,c.mode?&originalPetHover:&originalHover,menu,static_cast<const CEGUI::EventArgs*>(&event));unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0x50,aid(menu->m_pOwner));ptr(snapshot,0x58,aid(menu->m_pCanEquipCharacter));ptr(snapshot,0x70,menu->m_pGameUI==ui);ptr(snapshot,0x3438,iid(menu->m_pHoveredEquipment));ptr(snapshot,0x30,wid(menu->m_pSocketedIconParent));ptr(snapshot,0x38,wid(menu->m_pUnknown38));ptr(snapshot,0x28,wid(menu->m_pUnknown28));ptr(snapshot,0x40,wid(menu->m_pUnknown40));ptr(snapshot,0x3448,wid(menu->m_pUnknown3448));for(unsigned i=0;i<145;++i)ptr(snapshot,0x1de8+8*i,wid(menu->m_pSocketedSizeWindows[i]));for(unsigned i=0;i<82;++i)ptr(snapshot,0x26f8+8*i,wid(menu->m_pSlotWindows[i]));out.add(snapshot,sizeof(snapshot));out.add(positions,sizeof(positions));out.add(dimensions,sizeof(dimensions));for(unsigned i=0;i<12;++i)n(wid(windows[i]->d_parent));out.add(states,sizeof(states));for(unsigned i=0;i<3;++i)actors[i]->m_Followers.~vector();}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
int pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case c){autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int result=coverage.observe(host,u,v);if(result||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    stash hover mismatch %u/%u/%u/%u/%u/%u exits %d/%d first %lu\n",c.mode,c.mask,c.slot,c.profile,c.geometry,c.mutation,u.childStatus,v.childStatus,(unsigned long)f);coverage.report(host);return 1;}return 0;}
int run(const tlhybrid_host* host,unsigned mode){autotest::Coverage coverage(mode?"merchantmenu_pet_mouse_over":"merchantmenu_mouse_over",(uint64_t)(uintptr_t)(mode?&originalPetHover:&originalHover));for(unsigned mask=0;mask<(mode?128u:256u);++mask)for(unsigned slot=0;slot<(mode?3u:4u);++slot)for(unsigned profile=0;profile<(mode?4u:2u);++profile){Case c={mask,slot,mode?profile:profile*2,0,0,mode};if(pair(host,coverage,c))return 1;}const unsigned masks[]={3,7,35,95,159,255};for(unsigned index=0;index<6;++index)for(unsigned slot=0;slot<(mode?3u:4u);++slot)for(unsigned geometry=0;geometry<6;++geometry)for(unsigned mutation=0;mutation<6;++mutation){Case c={masks[index]|(mode?0u:128u),slot,2,geometry,mutation,mode};if(pair(host,coverage,c))return 1;}coverage.report(host);return 0;}
}
TL_TEST(merchantmenu_mouse_over){return run(host,0);}
TL_TEST(merchantmenu_pet_mouse_over){return run(host,1);}
