#include <cstring>
#include <string>
#include <vector>
#include <new>
#define private public
#define protected public
#include <CEGUI.h>
#include <CEGUIMemberFunctionSlot.h>
#include "InventoryMenu.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalMap,(CInventoryMenu*,CEGUI::Window*),"_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE")
extern "C" void candidateMap(CInventoryMenu*,CEGUI::Window*) __asm__("_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE");
extern "C" char presentFn[] __asm__("_ZNK5CEGUI11PropertySet17isPropertyPresentERKNS_6StringE");
extern "C" char propertyFn[] __asm__("_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE");
namespace {
struct Stop{};
struct Case {unsigned shape,mask,profile,fault;};
const Case* cs;autotest::Capture* cap;CInventoryMenu* menu;CEGUI::Window* windows[6];unsigned refCounts[6],connectionCount;unsigned char connectionObjects[6][128];
void n(int x){cap->add(&x,4);}int id(CEGUI::Window* p){for(unsigned i=0;i<6;++i)if(p==windows[i])return i;return 99;}
void str(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
bool present(CEGUI::PropertySet* p,const CEGUI::String& key){unsigned i=id(static_cast<CEGUI::Window*>(p));n(1);n(i);str(key);if(cs->fault==1&&i==2)throw Stop();return cs->mask&(1u<<i);}
CEGUI::String property(CEGUI::PropertySet* p,const CEGUI::String& key){unsigned i=id(static_cast<CEGUI::Window*>(p));n(2);n(i);str(key);if(cs->fault==2&&i==2)throw Stop();return cs->profile==0?CEGUI::String(""):cs->profile==1?CEGUI::String("click"):CEGUI::String("arbitrary property text");}
CEGUI::Event::Connection subscribe(CEGUI::EventSet* p,const CEGUI::String& event,CEGUI::Event::Subscriber sub){unsigned i=id(static_cast<CEGUI::Window*>(p));n(3);n(i);str(event);CEGUI::MemberFunctionSlot<CInventoryMenu>* f=static_cast<CEGUI::MemberFunctionSlot<CInventoryMenu>*>(sub.d_functor_impl);cap->add(&f->d_function,sizeof(f->d_function));n(f->d_object==menu);if(cs->fault==3&&i==2)throw Stop();if(connectionCount>=6)_exit(61);unsigned k=connectionCount++;refCounts[k]=2;CEGUI::Event::Connection c;c.d_object=(CEGUI::BoundSlot*)connectionObjects[k];c.d_count=&refCounts[k];return c;}
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long mm[(sizeof(CInventoryMenu)+16+7)/8],wm[6][(sizeof(CEGUI::Window)+7)/8];std::memset(mm,0xa5,sizeof(mm));std::memset(wm,0,sizeof(wm));menu=(CInventoryMenu*)mm;cs=&c;cap=&out;connectionCount=0;std::memset(refCounts,0,sizeof(refCounts));std::memset(connectionObjects,0,sizeof(connectionObjects));void* vt[3]={0,0,(void*)&subscribe};
 for(unsigned i=0;i<6;++i){windows[i]=(CEGUI::Window*)wm[i];*(void***)static_cast<CEGUI::EventSet*>(windows[i])=vt;new(&windows[i]->d_children)std::vector<CEGUI::Window*>;}
 if(c.shape==0){for(unsigned i=1;i<6;++i)windows[0]->d_children.push_back(windows[i]);}
 else if(c.shape==1){for(unsigned i=1;i<6;++i)windows[i-1]->d_children.push_back(windows[i]);}
 else {windows[0]->d_children.push_back(windows[1]);windows[0]->d_children.push_back(windows[2]);windows[1]->d_children.push_back(windows[3]);windows[1]->d_children.push_back(windows[4]);windows[2]->d_children.push_back(windows[5]);}
 detour::Set d;d.redirect(presentFn,presentFn,&present);d.redirect(propertyFn,propertyFn,&property);if(d.failed())_exit(62);
 if(ours)autotest::invoke(out,&candidateMap,menu,windows[0]);else autotest::invoke(out,&originalMap,menu,windows[0]);
 n(connectionCount);for(unsigned i=0;i<6;++i)n(refCounts[i]);cap->add(mm,sizeof(mm));for(unsigned i=0;i<6;++i){n(windows[i]->d_children.size());for(unsigned j=0;j<windows[i]->d_children.size();++j)n(id(windows[i]->d_children[j]));}
}
void a(void* p,autotest::Capture& o){side(*(Case*)p,false,o);}void b(void* p,autotest::Capture& o){side(*(Case*)p,true,o);}
}
TL_TEST(inventorymenu_event_mapping){
 autotest::Coverage coverage("inventorymenu_event_mapping",(uint64_t)(uintptr_t)&originalMap);
 for(unsigned shape=0;shape<3;++shape)for(unsigned mask=0;mask<64;++mask)for(unsigned profile=0;profile<3;++profile)for(unsigned fault=0;fault<4;++fault){Case c={shape,mask,profile,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    map mismatch %u/%u/%u/%u exits %d/%d first %lu lengths %lu/%lu\n",shape,mask,profile,fault,u.childStatus,v.childStatus,(unsigned long)f,(unsigned long)u.capture.length,(unsigned long)v.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);return 0;
}
