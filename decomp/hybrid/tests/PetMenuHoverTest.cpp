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
TL_ORIGINAL(bool,originalHover,(CPetMenu*,const CEGUI::EventArgs*),"_ZN8CPetMenu16handle_MouseOverERKN5CEGUI9EventArgsE")
extern "C" bool candidateHover(CPetMenu*,const CEGUI::EventArgs*) __asm__("_ZN8CPetMenu16handle_MouseOverERKN5CEGUI9EventArgsE");
TL_FUNCTION(itemFn,"_ZN10CInventory18getEquipmentInSlotEj")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
#define IMPORT(N,S) extern "C" char N[] __asm__(S)
IMPORT(visibleFn,"_ZN5CEGUI6Window10setVisibleEb");
IMPORT(frontFn,"_ZN5CEGUI6Window11moveToFrontEv");
IMPORT(backFn,"_ZN5CEGUI6Window10moveToBackEv");
IMPORT(positionFn,"_ZNK5CEGUI6Window11getPositionEv");
IMPORT(widthFn,"_ZNK5CEGUI6Window8getWidthEv");
IMPORT(heightFn,"_ZNK5CEGUI6Window9getHeightEv");
IMPORT(childFn,"_ZNK5CEGUI6Window7isChildEPKS0_");
IMPORT(addFn,"_ZN5CEGUI6Window14addChildWindowEPS0_");
IMPORT(setPositionFn,"_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
IMPORT(setSizeFn,"_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
#undef IMPORT
namespace {
struct Case {unsigned mask,slot,geometry,mutation;};const Case* cs;autotest::Capture* cap;CPetMenu* menu;CCharacter* actor;CInventory* inventory;CEquipment* equipment;CEGUI::Window* w[8];CEGUI::UVector2 pos[8],sizes[8];int state[8];bool child;unsigned getPositionCalls;
void n(int x){cap->add(&x,4);}int wid(const CEGUI::Window* p){if(!p)return 0;for(unsigned i=0;i<8;++i)if(p==w[i])return i+1;return 99;}int slotIndex(){const int values[]={0,18,19,81};return values[cs->slot];}
CEquipment* item(CInventory* p,unsigned slot){n(1);n(p==inventory);n(slot);if(cs->mutation)menu->m_pPanel=w[6];return cs->mask&4?equipment:0;}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){n(2);n(p==equipment);n(int(type));return cs->mask&32;}
void visible(CEGUI::Window* p,bool value){n(3);n(wid(p));n(value);state[wid(p)-1]=value;if(cs->mutation==2)menu->m_pSocketOverlay=w[7];}
void front(CEGUI::Window* p){n(4);n(wid(p));}
void back(CEGUI::Window* p){n(5);n(wid(p));}
const CEGUI::UVector2& position(const CEGUI::Window* p){n(6);n(wid(p));++getPositionCalls;if(cs->mutation){menu->m_pSocketedSizeWindows[slotIndex()]=w[5];menu->m_pPanel=w[3];}return pos[wid(p)-1];}
CEGUI::UDim width(const CEGUI::Window* p){n(7);n(wid(p));if(cs->mutation==2)menu->m_pSocketedSizeWindows[slotIndex()]=w[4];return sizes[wid(p)-1].d_x;}
CEGUI::UDim height(const CEGUI::Window* p){n(8);n(wid(p));return sizes[wid(p)-1].d_y;}
bool isChild(const CEGUI::Window* p,const CEGUI::Window* q){n(9);n(wid(p));n(wid(q));return child;}
void add(CEGUI::Window* p,CEGUI::Window* q){n(10);n(wid(p));n(wid(q));child=true;if(cs->mutation==2)menu->m_pSlotGlow=w[7];}
void setPosition(CEGUI::Window* p,const CEGUI::UVector2& value){n(11);n(wid(p));cap->add(&value,sizeof(value));pos[wid(p)-1]=value;}
void setSize(CEGUI::Window* p,const CEGUI::UVector2& value){n(12);n(wid(p));cap->add(&value,sizeof(value));sizes[wid(p)-1]=value;}
void ptr(unsigned char* bytes,size_t offset,unsigned value){uintptr_t v=value;std::memcpy(bytes+offset,&v,sizeof(v));}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;unsigned long long mm[(sizeof(CPetMenu)+16+7)/8],am[(sizeof(CCharacter)+7)/8]={0},im[(sizeof(CInventory)+7)/8]={0},em[(sizeof(CEquipment)+7)/8]={0},wm[8][(sizeof(CEGUI::Window)+7)/8];std::memset(mm,0xa5,sizeof(mm));std::memset(wm,0,sizeof(wm));cs=&c;cap=&out;menu=(CPetMenu*)mm;actor=(CCharacter*)am;inventory=(CInventory*)im;equipment=(CEquipment*)em;actor->m_pInventory=inventory;equipment->m_bUnknown348=c.mask&8;equipment->m_iSocketCount=(c.mask&16)?2:0;child=c.mask&64;getPositionCalls=0;
 const float scales[]={0.0f,0.5f,-0.5f,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};for(unsigned i=0;i<8;++i){w[i]=(CEGUI::Window*)wm[i];state[i]=-1;pos[i]=CEGUI::UVector2(CEGUI::UDim(scales[c.geometry],float(i)*3.25f-10),CEGUI::UDim(scales[c.geometry],float(i)*-2.5f+7));sizes[i]=CEGUI::UVector2(CEGUI::UDim(scales[c.geometry],float(i)*2.0f+1.25f),CEGUI::UDim(scales[c.geometry],float(i)*4.0f+3.5f));}
 int slot=slotIndex();w[0]->d_userData=&slot;menu->m_pCharacter=c.mask&2?actor:0;menu->m_pHoverObject=0;menu->m_pSocketedIconParent=w[1];menu->m_pSocketOverlay=w[2];menu->m_pPanel=w[3];menu->m_pSlotGlow=w[0];menu->m_Data9188=0;for(unsigned i=0;i<82;++i)menu->m_pSocketedSizeWindows[i]=w[4];CEGUI::WindowEventArgs event(c.mask&1?w[0]:0);
 detour::Set d;TL_REDIRECT(d,itemFn,&item);TL_REDIRECT(d,isaFn,&isa);
#define R(N,F) d.redirect(N##Fn,N##Fn,&F)
 R(visible,visible);R(front,front);R(back,back);R(position,position);R(width,width);R(height,height);R(child,isChild);R(add,add);R(setPosition,setPosition);R(setSize,setSize);
#undef R
 if(d.failed())_exit(60);if(ours)autotest::invoke(out,&candidateHover,menu,static_cast<const CEGUI::EventArgs*>(&event));else autotest::invoke(out,&originalHover,menu,static_cast<const CEGUI::EventArgs*>(&event));
 unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0x58,menu->m_pCharacter==actor);ptr(snapshot,0x1370,menu->m_pHoverObject==equipment);ptr(snapshot,0x30,wid(menu->m_pSocketedIconParent));ptr(snapshot,0x40,wid(menu->m_pSocketOverlay));ptr(snapshot,0x28,wid(menu->m_pPanel));ptr(snapshot,0x9110,wid(menu->m_pSlotGlow));for(unsigned i=0;i<82;++i)ptr(snapshot,0x1378+8*i,wid(menu->m_pSocketedSizeWindows[i]));cap->add(snapshot,sizeof(snapshot));n(child);n(getPositionCalls);for(unsigned i=0;i<8;++i){n(state[i]);cap->add(&pos[i],sizeof(pos[i]));cap->add(&sizes[i],sizeof(sizes[i]));}
}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(petmenu_mouse_over){autotest::Coverage coverage("petmenu_mouse_over",(uint64_t)(uintptr_t)&originalHover);for(unsigned mask=0;mask<128;++mask)for(unsigned slot=0;slot<4;++slot)for(unsigned geometry=0;geometry<6;++geometry)for(unsigned mutation=0;mutation<3;++mutation){Case c={mask,slot,geometry,mutation};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    hover mismatch %u/%u/%u/%u exits %d/%d first %lu\n",mask,slot,geometry,mutation,u.childStatus,v.childStatus,(unsigned long)f);coverage.report(host);return 1;}}coverage.report(host);return 0;}
