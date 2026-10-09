#include <cstring>
#include <string>
#include <vector>
#include <new>
#define private public
#define protected public
#include <CEGUI.h>
#include "CombineMenu.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Character.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, oldLayout, (CCombineMenu*), "_ZN12CCombineMenu12updateLayoutEv")
extern "C" void newLayout(CCombineMenu*) __asm__("_ZN12CCombineMenu12updateLayoutEv");
TL_FUNCTION(queryFn,"_ZN10CInventory21getEquipmentRefInSlotEj")
#define IMPORT(N,S) extern "C" char N[] __asm__(S)
IMPORT(getSizeFn,"_ZNK5CEGUI6Window7getSizeEv");
IMPORT(setSizeFn,"_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
IMPORT(removeFn,"_ZN5CEGUI6Window17removeChildWindowEPS0_");
IMPORT(frontFn,"_ZN5CEGUI6Window11moveToFrontEv");
IMPORT(backFn,"_ZN5CEGUI6Window10moveToBackEv");
IMPORT(propertyFn,"_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
IMPORT(textFn,"_ZN5CEGUI6Window7setTextERKNS_6StringE");
IMPORT(tooltipFn,"_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE");
IMPORT(showFn,"_ZN5CEGUI6Window10setVisibleEb");
#undef IMPORT
namespace {
struct Case {unsigned guard,children,holes,count,capacity,mutate;};
autotest::Capture* cap;CCombineMenu* menu;CInventory* inventory;CEGUI::Window* win[430];CEquipment* item[3];const Case* input;
void number(int n){cap->add(&n,sizeof(n));}
int id(const CEGUI::Window* p){for(int i=0;i<430;++i)if(p==win[i])return i;return -1;}
void text(const CEGUI::String& s){number(s.length());for(size_t i=0;i<s.length();++i)number(s[i]);}
void remove(CEGUI::Window* p,CEGUI::Window* q){number(1);number(id(p));number(id(q));for(size_t i=0;i<p->d_children.size();++i)if(p->d_children[i]==q){p->d_children.erase(p->d_children.begin()+i);break;}q->d_parent=0;}
CEGUI::UVector2 size(const CEGUI::Window* p){number(2);number(id(p));return CEGUI::UVector2(CEGUI::UDim(0.25f,32+id(p)),CEGUI::UDim(0.5f,48+id(p)));}
void setSize(CEGUI::Window* p,const CEGUI::UVector2& v){number(3);number(id(p));cap->add(&v,sizeof(v));}
void property(CEGUI::PropertySet* p,const CEGUI::String& k,const CEGUI::String& v){number(4);int n=-1;for(int i=0;i<430;++i)if(static_cast<CEGUI::PropertySet*>(win[i])==p)n=i;number(n);text(k);text(v);}
void setText(CEGUI::Window* p,const CEGUI::String& s){number(5);number(id(p));text(s);}
void tooltip(CEGUI::Window* p,const CEGUI::String& s){number(6);number(id(p));text(s);}
void front(CEGUI::Window* p){number(7);number(id(p));}
void back(CEGUI::Window* p){number(8);number(id(p));}
long query(CInventory* p,unsigned i){number(9);number(p==inventory);number(i);if(input->mutate&&i==(unsigned)menu->m_aiSlotData[3])menu->m_pSocketedSizeWindows[3]=0;return 0;}
void slot(CCombineMenu* p,CEquipment* e,int index,int data){number(10);number(p==menu);int n=-1;for(int i=0;i<3;++i)if(e==item[i])n=i;number(n);number(index);number(data);}
void show(CEGUI::Window* p,bool b){number(21);number(id(p));number(b);}
void side(const Case& c,bool ours,autotest::Capture& out){
 cap=&out;input=&c;
 unsigned long long mem[(sizeof(CCombineMenu)+7)/8]={0},cmem[(sizeof(CCharacter)+7)/8]={0},imem[(sizeof(CInventory)+7)/8]={0},rmem[3][(sizeof(CEquipmentRef)+7)/8]={0},emem[3][(sizeof(CEquipment)+7)/8]={0};
 unsigned long long wmem[430][(sizeof(CEGUI::Window)+7)/8]={0};
 menu=(CCombineMenu*)mem;inventory=(CInventory*)imem;CCharacter* character=(CCharacter*)cmem;
 for(int i=0;i<430;++i){win[i]=(CEGUI::Window*)wmem[i];new(&win[i]->d_children)std::vector<CEGUI::Window*>;}
 for(int i=0;i<4;++i){menu->m_pSocketedSizeWindows[i]=i<4&&c.holes&&(i%3==0)?0:win[i];menu->m_pMainGlowWindows[i]=win[82+i];menu->m_pMainSocketGlowWindows[i]=win[164+i];menu->m_pMainStackWindows[i]=win[246+i];menu->m_aiSlotData[i]=19+11*i;for(unsigned j=0;j<c.children;++j)win[i]->d_children.push_back(win[420+j]);}
 menu->m_pSocketedIconParent=win[410];menu->m_pBackground=win[411];menu->m_pPanel=win[412];menu->m_pForeground=win[413];
 for(unsigned j=0;j<c.children;++j)win[410]->d_children.push_back(win[420+j]);
 menu->m_bOpen=c.guard!=1;menu->m_pCharacter=c.guard==2?0:character;character->m_pInventory=c.guard==3?0:inventory;
 CEquipmentRef* refs[3];int slots[]={18,19,81};for(int i=0;i<3;++i){refs[i]=(CEquipmentRef*)rmem[i];item[i]=(CEquipment*)emem[i];refs[i]->m_pUnknown10=item[i];refs[i]->m_iSlot=slots[i];}
 TArrayList<CEquipmentRef*>& equipmentRefs=*reinterpret_cast<TArrayList<CEquipmentRef*>*>(inventory->m_Unknown30);equipmentRefs.m_pData=refs;equipmentRefs.m_nCount=c.count;equipmentRefs.m_nCapacity=c.capacity;
 detour::Set d;TL_REDIRECT(d,queryFn,&query);
 d.redirect(getSizeFn,getSizeFn,&size);d.redirect(setSizeFn,setSizeFn,&setSize);d.redirect(removeFn,removeFn,&remove);d.redirect(frontFn,frontFn,&front);d.redirect(backFn,backFn,&back);d.redirect(propertyFn,propertyFn,&property);d.redirect(textFn,textFn,&setText);d.redirect(tooltipFn,tooltipFn,&tooltip);
 d.redirect(showFn,showFn,&show);if(d.failed())_exit(42);
 if(ours)autotest::invoke(out,&newLayout,menu);else autotest::invoke(out,&oldLayout,menu);
 for(int i=0;i<4;++i){number(win[i]->d_children.size());number(menu->m_pSocketedSizeWindows[i]!=0);}number(win[410]->d_children.size());
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
}
TL_TEST(combine_layout_empty){
 autotest::Coverage coverage("combine_layout_empty",(uint64_t)(uintptr_t)&oldLayout);int failures=0,total=0;
 for(unsigned guard=0;guard<4;++guard)for(unsigned child=0;child<3;++child)for(unsigned holes=0;holes<2;++holes)for(unsigned count=0;count<1;++count)for(unsigned capacity=0;capacity<1;++capacity)for(unsigned mutate=0;mutate<2;++mutate){
 Case c={guard,child,holes,count,capacity,mutate};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);int pair=coverage.observe(host,x,y);++total;
 bool ok=pair==0&&!autotest::incomplete(x)&&!autotest::incomplete(y)&&x.reportValid&&y.reportValid&&x.childStatus==0&&y.childStatus==0&&x.capture.length==y.capture.length&&std::memcmp(x.capture.data,y.capture.data,x.capture.length)==0;
 if(!ok){++failures;size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    guard %u children %u holes %u count %u capacity %u mutation %u: exit %d/%d bytes %lu/%lu first %lu\n",guard,child,holes,count,capacity,mutate,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);return 1;}
 }coverage.report(host);host->log("    combine layout empty: %d cases, %d differences\n",total,failures);return failures;
}
