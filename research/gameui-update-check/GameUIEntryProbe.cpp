// Original-only characterization of cinematic early returns, not full recovery.
#include <cstring>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void originalUpdate(void*,float,void*,void*) __asm__("__tlorig__ZN7CGameUI14updateIngameUIEfP11CGameClientPN4Ogre12RenderWindowE");
TL_FUNCTION(settingsGet,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(mousePressed,"_ZN13CMouseManager13buttonPressedE12EMouseButton")
TL_FUNCTION(mouseHeld,"_ZN13CMouseManager10buttonHeldE12EMouseButton")
namespace {
struct Case {unsigned selected,first,second,buttons,flags,mode;};
struct World {unsigned long long ui[0x1a08/8],radio[2][0x800/8],cinema[2][0x100/8],vt[8],holder[0x240/8],window,settings;unsigned reads;World():window(0),settings(0),reads(0){std::memset(ui,0,sizeof(ui));std::memset(radio,0,sizeof(radio));std::memset(cinema,0,sizeof(cinema));std::memset(vt,0,sizeof(vt));std::memset(holder,0,sizeof(holder));}};
World*w;const Case*input;autotest::Capture*out;
template<class T>T& at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
void n(unsigned x){out->add(&x,sizeof(x));}
void real(float x){out->add(&x,sizeof(x));}
int setting(void*p,unsigned key){n(10);n(p==&w->settings);n(key==*reinterpret_cast<unsigned*>(0x150b570));++w->reads;if(input->mode==1)at<void*>(w->ui,0x200)=w->radio[1];static const int values[]={0,1,-1};return values[w->reads==1?input->first:input->second];}
void selected(void*p,bool b){n(11);n(p==w->radio[0]?0:1);n(b);at<unsigned char>(p,0x732)=b;}
bool button(void*p,unsigned b,bool held){n(held?13:12);n(p==static_cast<void*>(reinterpret_cast<char*>(w->ui)+0x12a8));n(b);if(input->mode==2)at<void*>(w->ui,0x540)=w->cinema[1];unsigned bit=held?(b==1?2:3):(b==1?0:1);return (input->buttons&(1u<<bit))!=0;}
bool pressed(void*p,unsigned b){return button(p,b,false);}bool held(void*p,unsigned b){return button(p,b,true);}
bool visible(void*p,bool inherited){n(15);n(p==&w->window);n(inherited);return false;}
void update(void*p,float elapsed){n(14);n(p==w->cinema[0]?0:1);real(elapsed);}
void model(){unsigned saved=at<unsigned char>(at<void*>(w->ui,0x200),0x732);if(saved!=unsigned(setting(&w->settings,*reinterpret_cast<unsigned*>(0x150b570))==1)){bool next=setting(&w->settings,*reinterpret_cast<unsigned*>(0x150b570))==1;selected(at<void*>(w->ui,0x200),next);}void*m=reinterpret_cast<char*>(w->ui)+0x12a8;bool any=pressed(m,1)||pressed(m,0)||held(m,1)||held(m,0);if(!any){void*holder=at<void*>(w->ui,0x430);if(visible(at<void*>(holder,0x238),false))_exit(43);}void*c=at<void*>(w->ui,0x540);if(at<unsigned char>(c,0x30)||!at<unsigned char>(c,0x31))update(c,0.125f);else _exit(44);}
void side(void*context,autotest::Capture&capture,bool reference){Case&c=*static_cast<Case*>(context);World world;w=&world;input=&c;out=&capture;at<void*>(w->ui,0x78)=&w->settings;at<void*>(w->ui,0x200)=w->radio[0];at<unsigned char>(w->radio[0],0x732)=c.selected;at<unsigned char>(w->radio[1],0x732)=!c.selected;at<void*>(w->ui,0x540)=w->cinema[0];at<void*>(w->ui,0x430)=w->holder;at<void*>(w->holder,0x238)=&w->window;w->vt[3]=reinterpret_cast<unsigned long long>(&update);for(unsigned j=0;j<2;++j){at<void*>(w->cinema[j],0)=w->vt;at<unsigned char>(w->cinema[j],0x30)=c.flags&1;at<unsigned char>(w->cinema[j],0x31)=(c.flags>>1)&1;}
 // Locals are pre-initialized for this entry-path probe. Their string payloads
 // are never used on these cinematic exits; first-time localization is excluded.
 const unsigned long guards[]={0x14b9bb8,0x14b9bc0,0x14b9bc8,0x14b9bd0};for(unsigned j=0;j<4;++j)*reinterpret_cast<unsigned char*>(guards[j])=1;
 detour::Set patches;TL_REDIRECT(patches,settingsGet,&setting);TL_REDIRECT(patches,mousePressed,&pressed);TL_REDIRECT(patches,mouseHeld,&held);patches.redirect(reinterpret_cast<char*>(0x554dc8),reinterpret_cast<char*>(0x554dc8),&selected);patches.redirect(reinterpret_cast<char*>(0x5561d8),reinterpret_cast<char*>(0x5561d8),&visible);if(patches.failed())_exit(42);
 if(reference)model();else originalUpdate(w->ui,0.125f,NULL,NULL);n(w->reads);n(at<unsigned char>(w->radio[0],0x732));n(at<unsigned char>(w->radio[1],0x732));}
void original(void*p,autotest::Capture&c){side(p,c,false);}void expected(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(gameui_cinematic_entry_characterization){int failures=0;unsigned count=0;for(unsigned s=0;s<2;++s)for(unsigned a=0;a<3;++a)for(unsigned b=0;b<3;++b)for(unsigned buttons=0;buttons<16;++buttons)for(unsigned flags=0;flags<4;++flags)for(unsigned mode=0;mode<3;++mode){if(flags==2)continue;Case c={s,a,b,buttons,flags,mode};autotest::Outcome x,y;autotest::runChild(original,&c,x);autotest::runChild(expected,&c,y);bool ok=WIFEXITED(x.status)&&WEXITSTATUS(x.status)==0&&WIFEXITED(y.status)&&WEXITSTATUS(y.status)==0&&x.capture.length==y.capture.length&&x.capture.length<autotest::Capture::kSize&&std::memcmp(x.capture.data,y.capture.data,x.capture.length)==0;TL_CHECK(failures,ok);if(!ok){host->log(" entry %u %u %u %u %u %u status %d/%d sizes %lu/%lu\n",s,a,b,buttons,flags,mode,x.status,y.status,(unsigned long)x.capture.length,(unsigned long)y.capture.length);return failures;}++count;}host->log("    gameui cinematic entry: %u cases; characterization only\n",count);return failures;}
