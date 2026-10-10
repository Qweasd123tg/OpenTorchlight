#include <cstring>
#include <CEGUI.h>
#include "SkillMenu.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool, originalClick, (CSkillMenu*,ELayoutFunction), "_ZN10CSkillMenu7onClickE15ELayoutFunction")
TL_ORIGINAL(bool, originalHandler, (CSkillMenu*,const CEGUI::EventArgs*), "_ZN10CSkillMenu14handle_onClickERKN5CEGUI9EventArgsE")
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char selectedFn[] __asm__("_ZN5CEGUI11RadioButton11setSelectedEb");
namespace {
struct Case {int action;unsigned open,profile,button,present;bool handler,result;};
const Case* cs;autotest::Capture* cap;CSkillMenu* menu;void* windows[7];int states[7],calls,layouts,dispatches;
void n(int value){cap->add(&value,sizeof(value));}
int id(void* p){if(!p)return 0;for(unsigned i=0;i<7;++i)if(p==windows[i])return i+1;return 99;}
void tick(int kind,void* window,bool value){n(kind);n(id(window));n(value);n(menu->m_iPane);n(menu->m_bOpenPartial);int i=id(window)-1;if(i<0||i>=7)_exit(60);states[i]=value;++calls;
 if(cs->profile==1&&calls==2){menu->m_Panes[2]=(CEGUI::Window*)windows[6];menu->m_Tabs[1]=(CEGUI::RadioButton*)windows[6];menu->m_iPane=57;}
 if(cs->profile==2&&calls==4){menu->m_bOpenPartial=!menu->m_bOpenPartial;menu->m_Tabs[2]=(CEGUI::RadioButton*)windows[0];}
}
void visible(CEGUI::Window* w,bool v){tick(1,w,v);}void selected(CEGUI::RadioButton* w,bool v){tick(2,w,v);}
void layout(CSkillMenu* p){n(3);n(p==menu);n(p->m_iPane);n(p->m_bOpenPartial);++layouts;if(cs->profile)p->m_iPane=73;}
bool dispatch(CSkillMenu* p,ELayoutFunction a){n(4);n(p==menu);n(int(a));++dispatches;p->m_iPane=int(a)^37;p->m_bSkillHovered=cs->result;return cs->result;}
extern "C" bool candidateClick(CSkillMenu*,ELayoutFunction) __asm__("_ZN10CSkillMenu7onClickE15ELayoutFunction");
extern "C" bool candidateHandler(CSkillMenu*,const CEGUI::EventArgs*) __asm__("_ZN10CSkillMenu14handle_onClickERKN5CEGUI9EventArgsE");
void ptr(unsigned char* b,unsigned offset,unsigned value){uintptr_t v=value;std::memcpy(b+offset,&v,sizeof(v));}
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long mem[(sizeof(CSkillMenu)+16+7)/8],fake[7][0x200/8];void* table[14]={0};table[9]=(void*)&layout;table[13]=(void*)&dispatch;std::memset(mem,c.profile==1?0x5a:0xa5,sizeof(mem));std::memset(fake,0x67,sizeof(fake));
 menu=(CSkillMenu*)mem;*(void***)menu=table;for(unsigned i=0;i<7;++i){windows[i]=fake[i];states[i]=-1;}cs=&c;cap=&out;calls=layouts=dispatches=0;
 menu->m_bOpenPartial=c.open;menu->m_bSkillHovered=false;menu->m_iPane=41;for(unsigned i=0;i<3;++i){menu->m_Panes[i]=(CEGUI::Window*)windows[i];menu->m_Tabs[i]=(CEGUI::RadioButton*)windows[i+3];}
 int action=c.action;void* data=&action;std::memcpy((char*)windows[0]+0x1d8,&data,sizeof(data));
 CEGUI::MouseEventArgs event(c.present?(CEGUI::Window*)windows[0]:0);event.button=static_cast<CEGUI::MouseButton>(c.button);event.position=CEGUI::Point(1,2);event.moveDelta=CEGUI::Point(3,4);event.sysKeys=5;event.wheelChange=6;event.clickCount=7;
 detour::Set redirects;redirects.redirect(visibleFn,visibleFn,&visible);redirects.redirect(selectedFn,selectedFn,&selected);if(redirects.failed())_exit(61);

 if(c.handler) {if(ours)autotest::invoke(out,&candidateHandler,menu,static_cast<const CEGUI::EventArgs*>(&event));else autotest::invoke(out,&originalHandler,menu,static_cast<const CEGUI::EventArgs*>(&event));}
 else {if(ours)autotest::invoke(out,&candidateClick,menu,static_cast<ELayoutFunction>(c.action));else autotest::invoke(out,&originalClick,menu,static_cast<ELayoutFunction>(c.action));}
 n(calls);n(layouts);n(dispatches);for(unsigned i=0;i<7;++i)n(states[i]);unsigned char snapshot[sizeof(mem)];std::memcpy(snapshot,mem,sizeof(snapshot));ptr(snapshot,0,1);for(unsigned i=0;i<3;++i){ptr(snapshot,0x90+8*i,id(menu->m_Panes[i]));ptr(snapshot,0xb0+8*i,id(menu->m_Tabs[i]));}cap->add(snapshot,sizeof(snapshot));
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
int run(const tlhybrid_host* host,bool handler,const char* name){
 autotest::Coverage coverage(name,(uint64_t)(uintptr_t)(handler?&originalHandler:reinterpret_cast<bool(*)(CSkillMenu*,const CEGUI::EventArgs*)>(&originalClick)));
 int actions[]={-1,0,63,64,65,66,67,2147483647};
 for(unsigned i=0;i<8;++i)for(unsigned open=0;open<2;++open)for(unsigned profile=0;profile<3;++profile)for(unsigned button=0;button<(handler?3u:1u);++button)for(unsigned present=0;present<(handler?2u:1u);++present)for(unsigned result=0;result<(handler?2u:1u);++result){
 Case c={actions[i],open,profile,button,present,handler,bool(result)};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);
 if(pair||!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callCompleted||!v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    controls mismatch %d/%u/%u/%u/%u/%u exits %d/%d first %lu lengths %lu/%lu\n",actions[i],open,profile,button,present,result,u.childStatus,v.childStatus,(unsigned long)f,(unsigned long)u.capture.length,(unsigned long)v.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);return 0;
}
}
TL_TEST(skillmenu_tab_click){return run(host,false,"skillmenu_tab_click");}
TL_TEST(skillmenu_click_dispatch){return run(host,true,"skillmenu_click_dispatch");}
