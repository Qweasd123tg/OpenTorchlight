#include <cstring>
#define private public
#define protected public
#include <CEGUI.h>
#include "StashMenu.h"
#include "Character.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,originalClick,(CStashMenu*,ELayoutFunction),"_ZN10CStashMenu7onClickE15ELayoutFunction")
TL_ORIGINAL(bool,originalClose,(CStashMenu*,const CEGUI::EventArgs*),"_ZN10CStashMenu18handle_CloseButtonERKN5CEGUI9EventArgsE")
TL_ORIGINAL(bool,originalHandler,(CStashMenu*,const CEGUI::EventArgs*),"_ZN10CStashMenu14handle_onClickERKN5CEGUI9EventArgsE")
extern "C" bool candidateClick(CStashMenu*,ELayoutFunction) __asm__("_ZN10CStashMenu7onClickE15ELayoutFunction");
extern "C" bool candidateClose(CStashMenu*,const CEGUI::EventArgs*) __asm__("_ZN10CStashMenu18handle_CloseButtonERKN5CEGUI9EventArgsE");
extern "C" bool candidateHandler(CStashMenu*,const CEGUI::EventArgs*) __asm__("_ZN10CStashMenu14handle_onClickERKN5CEGUI9EventArgsE");
TL_FUNCTION(targetFn,"_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(rightFn,"_ZN7CGameUI10closeRightEv")
extern "C" char radioFn[] __asm__("_ZN5CEGUI11RadioButton11setSelectedEb");
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
TL_FUNCTION(removeFn,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
namespace {
struct Case {unsigned mask,mutation,button,mode,present,result;int action;};const Case* cs;autotest::Capture* cap;CStashMenu* menu;CGameUI* ui[2];CCharacter* actor[2];unsigned char* clients[2];CRunicCore* objects[4];unsigned calls;CEGUI::Window* windows[12];
void n(int v){cap->add(&v,4);}template<class T>T& at(void* p,size_t off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}int uid(void* p){return p==ui[0]?1:p==ui[1]?2:99;}
void target(CCharacter* p,CCharacter* q){n(1);n(p==actor[0]?1:p==actor[1]?2:99);n(q==0);n(menu->m_bUnknown62);++calls;if(cs->mutation)menu->m_pGameUI=ui[1];if(cs->mutation==2)menu->m_bUnknown62=false;}
void right(CGameUI* p){n(2);n(uid(p));n(menu->m_bUnknown62);++calls;if(cs->mutation)menu->m_bOpenPartial=!menu->m_bOpenPartial;}
int wid(CEGUI::Window* p){for(unsigned i=0;i<12;++i)if(p==windows[i])return i+1;return p?99:0;}
void layout(CStashMenu* p){n(3);n(p==menu);++calls;if(cs->mutation)menu->m_iUnknown3400=87;}
void select(CEGUI::RadioButton* p,bool value){n(6);n(wid(p));n(value);++calls;if(cs->mutation==1){menu->m_pUnknown33e0=windows[6];menu->m_pUnknown33e8=windows[7];menu->m_pUnknown33f0=windows[8];menu->m_pUnknown33c8=windows[9];menu->m_pUnknown33d0=windows[10];menu->m_pUnknown33d8=windows[11];}if(cs->mutation==2)menu->m_bOpenPartial=false;}
void visible(CEGUI::Window* p,bool value){n(7);n(wid(p));n(value);++calls;if(cs->mutation==1)menu->m_pUnknown33d8=windows[5];}
void remove(CRunicCore* p,TSafePointer<void*>* ref,unsigned index){n(4);int id=0;for(unsigned i=0;i<4;++i)if(p==objects[i])id=i+1;n(id);unsigned char* base=0;for(unsigned i=0;i<2;++i)if((unsigned char*)ref>=clients[i]&&(unsigned char*)ref<clients[i]+0x240){base=clients[i];n(i+1);}if(!base)_exit(62);size_t offset=(unsigned char*)ref-base;n(offset);n(index);++calls;if(cs->mutation){menu->m_pGameUI=ui[0];unsigned next=offset==0x1f8?2:offset==0x1e8?0:offset==0x1c8?1:3;at<CRunicCore*>(base,0x1c8+16*next)=objects[(next+1)%4];}}
bool dispatch(CStashMenu* p,ELayoutFunction a){n(5);n(p==menu);n(int(a));++calls;p->m_iUnknown3400=int(a)^37;return cs->result;}
void ptr(unsigned char* p,size_t offset,uintptr_t value){std::memcpy(p+offset,&value,8);}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;cs=&c;cap=&out;calls=0;unsigned long long mm[(sizeof(CStashMenu)+23)/8],um[2][(sizeof(CGameUI)+7)/8]={0},am[2][(sizeof(CCharacter)+7)/8]={0},cm[2][0x240/8]={0},om[4][8]={0},wm[(sizeof(CEGUI::Window)+7)/8]={0},tabs[12][8]={0};std::memset(mm,0xa5,sizeof(mm));menu=(CStashMenu*)mm;void* vt[20]={0};vt[19]=(void*)&dispatch;vt[9]=(void*)&layout;*(void***)menu=vt;for(unsigned i=0;i<4;++i)objects[i]=(CRunicCore*)om[i];for(unsigned i=0;i<2;++i){ui[i]=(CGameUI*)um[i];actor[i]=(CCharacter*)am[i];clients[i]=(unsigned char*)cm[i];at<CCharacter*>(ui[i],0x38)=actor[i];at<void*>(ui[i],0x1920)=clients[i];for(unsigned j=0;j<4;++j){at<CRunicCore*>(clients[i],0x1c8+16*j)=c.mask&(1u<<j)?objects[j]:0;at<unsigned>(clients[i],0x1d0+16*j)=0xabcdef00u+j+i*23;}}
 for(unsigned i=0;i<12;++i)windows[i]=(CEGUI::Window*)tabs[i];menu->m_pUnknown33e0=windows[0];menu->m_pUnknown33e8=windows[1];menu->m_pUnknown33f0=windows[2];menu->m_pUnknown33c8=windows[3];menu->m_pUnknown33d0=windows[4];menu->m_pUnknown33d8=windows[5];
 menu->m_pGameUI=ui[0];menu->m_bUnknown62=c.mask&16;menu->m_bOpenPartial=c.mask&32;menu->m_iUnknown3400=17;CEGUI::Window* window=(CEGUI::Window*)wm;int action=c.action;window->d_userData=&action;CEGUI::MouseEventArgs event(c.present?window:0);event.button=(CEGUI::MouseButton)c.button;
 detour::Set d;TL_REDIRECT(d,targetFn,&target);TL_REDIRECT(d,rightFn,&right);d.redirect(radioFn,radioFn,&select);d.redirect(visibleFn,visibleFn,&visible);TL_REDIRECT(d,removeFn,&remove);if(d.failed())_exit(60);
 if(c.mode==0){if(ours)autotest::invoke(out,&candidateClick,menu,(ELayoutFunction)c.action);else autotest::invoke(out,&originalClick,menu,(ELayoutFunction)c.action);}else if(c.mode==1){if(ours)autotest::invoke(out,&candidateClose,menu,static_cast<const CEGUI::EventArgs*>(&event));else autotest::invoke(out,&originalClose,menu,static_cast<const CEGUI::EventArgs*>(&event));}else {if(ours)autotest::invoke(out,&candidateHandler,menu,static_cast<const CEGUI::EventArgs*>(&event));else autotest::invoke(out,&originalHandler,menu,static_cast<const CEGUI::EventArgs*>(&event));}
 unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(mm));ptr(snapshot,0,1);ptr(snapshot,0x70,uid(menu->m_pGameUI));ptr(snapshot,0x33e0,wid(menu->m_pUnknown33e0));ptr(snapshot,0x33e8,wid(menu->m_pUnknown33e8));ptr(snapshot,0x33f0,wid(menu->m_pUnknown33f0));ptr(snapshot,0x33c8,wid(menu->m_pUnknown33c8));ptr(snapshot,0x33d0,wid(menu->m_pUnknown33d0));ptr(snapshot,0x33d8,wid(menu->m_pUnknown33d8));cap->add(snapshot,sizeof(snapshot));n(calls);for(unsigned i=0;i<2;++i){for(unsigned j=0;j<4;++j){CRunicCore* q=at<CRunicCore*>(clients[i],0x1c8+16*j);int id=0;for(unsigned k=0;k<4;++k)if(q==objects[k])id=k+1;ptr(clients[i],0x1c8+16*j,id);}cap->add(clients[i],0x240);}
}
void a(void* p,autotest::Capture& o){side(p,o,false);}void b(void* p,autotest::Capture& o){side(p,o,true);}
int run(const tlhybrid_host* host,unsigned mode){uint64_t address=mode==0?(uint64_t)(uintptr_t)&originalClick:mode==1?(uint64_t)(uintptr_t)&originalClose:(uint64_t)(uintptr_t)&originalHandler;const char* name=mode==0?"stashmenu_click":mode==1?"stashmenu_close":"stashmenu_click_dispatch";autotest::Coverage coverage(name,address);const int actions[]={-1,0,8,13,14,15,16,17,2147483647,(-2147483647-1)};for(unsigned mask=0;mask<(mode==2?2u:64u);++mask)for(unsigned mutation=0;mutation<3;++mutation)for(unsigned button=0;button<(mode?4u:1u);++button)for(unsigned index=0;index<(mode==1?1u:10u);++index)for(unsigned present=0;present<(mode==2?2u:1u);++present)for(unsigned result=0;result<(mode==2?2u:1u);++result){Case c={mask,mutation,button,mode,present,result,actions[index]};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    stash action mismatch mode %u mask %u mutation %u button %u action %d presence %u result %u exits %d/%d\n",mode,mask,mutation,button,actions[index],present,result,u.childStatus,v.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(stashmenu_click){return run(host,0);}
TL_TEST(stashmenu_close){return run(host,1);}
TL_TEST(stashmenu_click_dispatch){return run(host,2);}
