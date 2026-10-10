#include <cstring>
#include <vector>
#include <new>
#define private public
#define protected public
#include <CEGUI.h>
#include "StashMenu.h"
#include "Character.h"
#include "Inventory.h"
#include "EquipmentRef.h"
#include "SharedStash.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalLayout,(CStashMenu*),"_ZN10CStashMenu12updateLayoutEv")
extern "C" void candidateLayout(CStashMenu*) __asm__("_ZN10CStashMenu12updateLayoutEv");
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(sharedFn,"_ZN12CSharedStash12getSingletonEv")
TL_FUNCTION(mainFn,"_ZN10CStashMenu11setSlotIconEP10CEquipmentii")
TL_FUNCTION(petFn,"_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii")
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char propertyFn[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
extern "C" char textFn[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
extern "C" char backFn[] __asm__("_ZN5CEGUI6Window10moveToBackEv");
extern "C" char frontFn[] __asm__("_ZN5CEGUI6Window11moveToFrontEv");
namespace {
struct Stop{};struct Case{unsigned mask,profile,mutation,fault;};const Case* cs;autotest::Capture* cap;CStashMenu* menu;CCharacter* owners[2];CCharacter* player;CCharacter* follower;CInventory* invs[2];CSharedStash* shared;CEGUI::Window* windows[20];CEquipment* items[5];unsigned events,icons;
typedef std::vector<CEGUI::Window*> Children;typedef std::vector<CCharacter*> Followers;
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
void n(int x){cap->add(&x,4);}int wid(void* p){if(!p)return 0;for(unsigned i=0;i<20;++i)if(p==windows[i])return i+1;return 99;}int iid(void* p){if(!p)return 0;for(unsigned i=0;i<5;++i)if(p==items[i])return i+1;return 99;}
void event(int k){n(k);if(++events==cs->fault)throw Stop();}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){event(1);n(p==owners[0]?1:p==owners[1]?2:99);n(type);if(cs->mutation==1)menu->m_pOwner=owners[1];return cs->mask&8;}
CSharedStash* singleton(){event(2);return shared;}
void remove(CEGUI::Window* p,CEGUI::Window* q){event(3);n(wid(p));n(wid(q));Children& children=at<Children>(p,0x78);for(Children::iterator i=children.begin();i!=children.end();++i)if(*i==q){children.erase(i);break;}}
void property(CEGUI::PropertySet* p,const CEGUI::String& key,const CEGUI::String& value){event(4);n(wid(p));cap->addText(key.c_str());cap->addText(value.c_str());if(cs->mutation==2){menu->m_pMainGlowWindows[20]=windows[18];menu->m_pSocketGlowWindows[20]=windows[19];}}
void text(CEGUI::Window* p,const CEGUI::String& value){event(5);n(wid(p));cap->addText(value.c_str());}
void mainIcon(CStashMenu* p,CEquipment* item,int slot,int data){event(6);n(p==menu);n(iid(item));n(slot);n(data);++icons;if(cs->mutation==1&&icons==1)at<TArrayList<CEquipmentRef*> >(invs[0],0x30).m_nCount=1;}
void petIcon(CStashMenu* p,CEquipment* item,int slot,int data){event(7);n(p==menu);n(iid(item));n(slot);n(data);++icons;if(cs->mutation==2&&icons==1)at<TArrayList<CEquipmentRef*> >(invs[1],0x30).m_nCount=1;}
void back(CEGUI::Window* p){event(8);n(wid(p));if(cs->mutation==1)menu->m_pUnknown40=windows[19];}
void front(CEGUI::Window* p){event(9);n(wid(p));}
void ptr(unsigned char* p,unsigned off,uintptr_t v){std::memcpy(p+off,&v,8);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;events=icons=0;
unsigned long long mm[(sizeof(CStashMenu)+23)/8],am[4][(sizeof(CCharacter)+7)/8]={0},im[2][(sizeof(CInventory)+7)/8]={0},refsMem[5][8]={0},itemMem[5][8]={0},sm[8]={0},wm[20][(sizeof(CEGUI::Window)+7)/8]={0};std::memset(mm,0xa5,sizeof(mm));menu=(CStashMenu*)mm;owners[0]=(CCharacter*)am[0];owners[1]=(CCharacter*)am[1];player=(CCharacter*)am[2];follower=(CCharacter*)am[3];shared=(CSharedStash*)sm;
for(unsigned i=0;i<2;++i)invs[i]=(CInventory*)im[i];CEquipmentRef* refs[5];const int slots[]={-1,18,19,60,81};for(unsigned i=0;i<5;++i){refs[i]=(CEquipmentRef*)refsMem[i];items[i]=(CEquipment*)itemMem[i];refs[i]->m_pUnknown10=(i==3&&c.profile==2)?0:items[i];refs[i]->m_iSlot=slots[i];}
for(unsigned i=0;i<2;++i){TArrayList<CEquipmentRef*>& a=at<TArrayList<CEquipmentRef*> >(invs[i],0x30);a.m_pData=refs;a.m_nCount=c.profile==0?0:5;a.m_nCapacity=c.profile==2?3:5;}
for(unsigned i=0;i<20;++i){windows[i]=(CEGUI::Window*)wm[i];Children& children=*new(&at<Children>(windows[i],0x78)) Children;if(c.mask&64){children.push_back(windows[i]);children.push_back(windows[i]);}}
Followers& followers=*new(&at<Followers>(player,0x648)) Followers;followers.push_back(follower);owners[0]->m_pInventory=c.mask&4?invs[0]:0;owners[1]->m_pInventory=c.mask&4?invs[1]:0;follower->m_pInventory=c.mask&16?invs[1]:0;shared->m_pInventory=c.mask&4?invs[0]:0;
menu->m_bOpenPartial=c.mask&1;menu->m_pOwner=c.mask&2?owners[0]:0;menu->m_pCharacter=player;menu->m_pUnknown20=windows[0];menu->m_pUnknown28=windows[1];menu->m_pUnknown30=windows[2];menu->m_pUnknown38=windows[3];menu->m_pUnknown40=windows[4];for(unsigned i=0;i<145;++i){menu->m_pSocketedSizeWindows[i]=windows[5];menu->m_pMainUnidentifiedWindows[i]=windows[6];menu->m_pMainGlowWindows[i]=windows[7];menu->m_pMainSocketGlowWindows[i]=windows[8];menu->m_pMainStackWindows[i]=(c.mask&32)||i%2?windows[9]:0;}for(unsigned i=0;i<82;++i){menu->m_pSlotWindows[i]=windows[10];menu->m_pSlotGlowWindows[i]=windows[11];menu->m_pSocketGlowWindows[i]=windows[12];menu->m_pUnidentifiedWindows[i]=windows[13];menu->m_pStackWindows[i]=(c.mask&32)||i%2?windows[14]:0;}
detour::Set d;TL_REDIRECT(d,isaFn,&isa);TL_REDIRECT(d,sharedFn,&singleton);TL_REDIRECT(d,mainFn,&mainIcon);TL_REDIRECT(d,petFn,&petIcon);d.redirect(removeFn,removeFn,&remove);d.redirect(propertyFn,propertyFn,&property);d.redirect(textFn,textFn,&text);d.redirect(backFn,backFn,&back);d.redirect(frontFn,frontFn,&front);if(d.failed())_exit(61);bool threw=false;try{if(ours)autotest::invoke(out,&candidateLayout,menu);else autotest::invoke(out,&originalLayout,menu);}catch(const Stop&){threw=true;}catch(...){_exit(62);}n(threw);n(events);n(icons);for(unsigned i=0;i<20;++i){Children& a=at<Children>(windows[i],0x78);n(a.size());for(unsigned j=0;j<a.size();++j)n(wid(a[j]));a.~Children();}followers.~Followers();for(unsigned i=0;i<2;++i)n(at<TArrayList<CEquipmentRef*> >(invs[i],0x30).size());
unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0x50,menu->m_pOwner==owners[0]?1:menu->m_pOwner==owners[1]?2:menu->m_pOwner?99:0);ptr(snapshot,0x58,menu->m_pCharacter==player?1:99);const unsigned offsets[]={0x20,0x28,0x30,0x38,0x40};for(unsigned i=0;i<5;++i){void* p;std::memcpy(&p,snapshot+offsets[i],8);ptr(snapshot,offsets[i],wid(p));}for(unsigned off=0x1050;off<0x33c8;off+=8){void* p;std::memcpy(&p,snapshot+off,8);ptr(snapshot,off,wid(p));}out.add(snapshot,sizeof(snapshot));}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(stashmenu_layout){autotest::Coverage coverage("stashmenu_layout",(uint64_t)(uintptr_t)&originalLayout);for(unsigned mask=0;mask<128;++mask)for(unsigned profile=0;profile<3;++profile)for(unsigned mutation=0;mutation<3;++mutation){Case c={mask,profile,mutation,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    stash layout mismatch %u/%u/%u exits %d/%d first %lu\n",mask,profile,mutation,u.childStatus,v.childStatus,(unsigned long)f);coverage.report(host);return 1;}}coverage.report(host);return 0;}
TL_TEST(stashmenu_layout_expected_exceptions){const unsigned faults[]={1,2,3,6,20,100,200,400};unsigned count=0;for(unsigned i=0;i<8;++i)for(unsigned mutation=0;mutation<3;++mutation){Case c={127,1,mutation,faults[i]};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    stash layout unwind mismatch %u/%u exits %d/%d\n",faults[i],mutation,u.childStatus,v.childStatus);return 1;}++count;}host->log("    EXPECTED LAYOUT EXCEPTIONS: %u matching unwinds, not normal coverage\n",count);return 0;}
