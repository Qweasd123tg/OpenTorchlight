#include <cstring>
#define private public
#define protected public
#include <CEGUI.h>
#include "StatsMenuFill.h"
#undef private
#undef protected
#include "AutoTest.h"
TL_ORIGINAL(bool,oldAdd,(CStatsMenuFill*,const CEGUI::EventArgs*),"_ZN14CStatsMenuFill16handle_AddToStatERKN5CEGUI9EventArgsE")
TL_ORIGINAL(bool,oldRemove,(CStatsMenuFill*,const CEGUI::EventArgs*),"_ZN14CStatsMenuFill21handle_RemoveFromStatERKN5CEGUI9EventArgsE")
extern "C" bool newAdd(CStatsMenuFill*,const CEGUI::EventArgs*) __asm__("_ZN14CStatsMenuFill16handle_AddToStatERKN5CEGUI9EventArgsE");
extern "C" bool newRemove(CStatsMenuFill*,const CEGUI::EventArgs*) __asm__("_ZN14CStatsMenuFill21handle_RemoveFromStatERKN5CEGUI9EventArgsE");
namespace {
struct Case {unsigned operation,count,hit,duplicate,pattern;};
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long memory[64],windows[5][8];std::memset(memory,c.pattern?0x5a:0xa5,sizeof(memory));std::memset(windows,0,sizeof(windows));CStatsMenuFill* menu=reinterpret_cast<CStatsMenuFill*>(memory);
 CEGUI::Window* add[4];CEGUI::Window* remove[4];for(unsigned i=0;i<4;++i){add[i]=reinterpret_cast<CEGUI::Window*>(windows[i]);remove[i]=reinterpret_cast<CEGUI::Window*>(windows[3-i]);menu->m_AddHeld[i]=(i+c.pattern)%2;menu->m_RemoveHeld[i]=(i+c.pattern+1)%2;}
 if(c.duplicate){add[2]=add[0];remove[2]=remove[0];}if(c.hit==5){add[1]=0;remove[1]=0;}
 menu->m_AddButtons.m_pData=add;menu->m_AddButtons.m_nCount=c.count;menu->m_AddButtons.m_nCapacity=c.pattern?0:4;
 menu->m_RemoveButtons.m_pData=remove;menu->m_RemoveButtons.m_nCount=c.count;menu->m_RemoveButtons.m_nCapacity=c.pattern?0:4;
 CEGUI::WindowEventArgs event(c.hit==5?0:reinterpret_cast<CEGUI::Window*>(windows[c.hit]));const CEGUI::EventArgs* arg=&event;
 if(c.operation==0){if(ours)autotest::invoke(out,&newAdd,menu,arg);else autotest::invoke(out,&oldAdd,menu,arg);}
 else {if(ours)autotest::invoke(out,&newRemove,menu,arg);else autotest::invoke(out,&oldRemove,menu,arg);}
 out.add(memory,sizeof(memory));out.add(windows,sizeof(windows));out.add(add,sizeof(add));out.add(remove,sizeof(remove));
}
void a(void* p,autotest::Capture& o){side(*(Case*)p,false,o);}void b(void* p,autotest::Capture& o){side(*(Case*)p,true,o);}
}
TL_TEST(stats_fill_buttons_differential){autotest::Coverage add("stats_fill_buttons_differential",reinterpret_cast<uintptr_t>(&oldAdd));autotest::Coverage remove("stats_fill_buttons_differential",reinterpret_cast<uintptr_t>(&oldRemove));for(unsigned op=0;op<2;++op)for(unsigned count=0;count<=4;++count)for(unsigned hit=0;hit<6;++hit)for(unsigned duplicate=0;duplicate<2;++duplicate)for(unsigned pattern=0;pattern<2;++pattern){Case c={op,count,hit,duplicate,pattern};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);int d=(op?remove:add).observe(host,x,y);if(d||autotest::incomplete(x)||autotest::incomplete(y)||x.childStatus||y.childStatus){add.report(host);remove.report(host);host->log("    stats button case %u/%u/%u/%u/%u\n",op,count,hit,duplicate,pattern);return 1;}}add.report(host);remove.report(host);return 0;}
