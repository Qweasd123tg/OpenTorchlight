
#include "GameUIUpdate.h"
// Complete cinematic-return path with visible no-input floating window.
#include <cstring>
#include <CEGUIUDim.h>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void restoredUpdate(void*,float,void*,void*) __asm__("_ZN7CGameUI14updateIngameUIEfP11CGameClientPN4Ogre12RenderWindowE");
extern "C" void originalUpdate(void*,float,void*,void*) __asm__("__tlorig__ZN7CGameUI14updateIngameUIEfP11CGameClientPN4Ogre12RenderWindowE");
TL_FUNCTION(settingsGet,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(mousePressed,"_ZN13CMouseManager13buttonPressedE12EMouseButton")
TL_FUNCTION(mouseHeld,"_ZN13CMouseManager10buttonHeldE12EMouseButton")
TL_FUNCTION(windowWidth,"_ZN7CGameUI14getWindowWidthEv")
TL_FUNCTION(windowHeight,"_ZN7CGameUI15getWindowHeightEv")
namespace {
template<class T>T& at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
struct Case{float screen;long x,y;unsigned geometry,mode;};
struct World{unsigned long long ui[0x1a08/8],radio[0x800/8],cinema[2][0x100/8],holder[0x240/8],windows[2],vt[8],settings;World(){std::memset(this,0,sizeof(*this));}};
World*w;const Case*input;autotest::Capture*out;
void n(unsigned x){out->add(&x,sizeof(x));}void real(float x){out->add(&x,sizeof(x));}
unsigned windowID(void*p){return p==&w->windows[0]?0:p==&w->windows[1]?1:99;}
int zero(void*,unsigned){return 0;}bool no(void*,unsigned){return false;}
bool visible(void*p,bool inherited){n(10);n(windowID(p));n(inherited);if(input->mode==1)at<void*>(w->holder,0x238)=&w->windows[1];return true;}
float screenWidth(void*p){n(11);n(p==w->ui);return input->screen;}
float screenHeight(void*p){n(12);n(p==w->ui);return 999.0f;}
CEGUI::UDim width(void*p){n(13);n(windowID(p));const float scale[]={-0.5f,0.0f,0.5f,120.51f};const float offset[]={50,0,20,0};return CEGUI::UDim(scale[input->geometry],offset[input->geometry]);}
CEGUI::UDim height(void*p){n(14);n(windowID(p));const float scale[]={0.51f,-3.5f,0,12.49f};const float offset[]={30,17.25f,0,50};return CEGUI::UDim(scale[input->geometry],offset[input->geometry]);}
void position(void*p,const CEGUI::UVector2&v){n(15);n(windowID(p));out->add(&v,sizeof(v));if(input->mode==2)at<void*>(w->ui,0x540)=w->cinema[1];}
void cinematic(void*p,float elapsed){n(16);n(p==w->cinema[0]?0:1);real(elapsed);}
void model(){gameui_detail::Labels labels={"","","",""};gameui_detail::Frame frame(w->ui,NULL,NULL,0.125f,labels);if(!frame.entry())_exit(47); }
void side(void*context,autotest::Capture&capture,bool expected){Case&c=*static_cast<Case*>(context);World world;w=&world;input=&c;out=&capture;at<void*>(w->ui,0x78)=&w->settings;at<void*>(w->ui,0x200)=w->radio;at<void*>(w->ui,0x430)=w->holder;at<void*>(w->holder,0x238)=&w->windows[0];at<void*>(w->ui,0x540)=w->cinema[0];at<long>(w->ui,0x12d0)=c.x;at<long>(w->ui,0x12d8)=c.y;w->vt[3]=reinterpret_cast<unsigned long long>(&cinematic);for(unsigned i=0;i<2;++i){at<void*>(w->cinema[i],0)=w->vt;at<unsigned char>(w->cinema[i],0x30)=1;}
 const unsigned long guards[]={0x14b9bb8,0x14b9bc0,0x14b9bc8,0x14b9bd0};for(unsigned i=0;i<4;++i)*reinterpret_cast<unsigned char*>(guards[i])=1;
 detour::Set patches;TL_REDIRECT(patches,settingsGet,&zero);TL_REDIRECT(patches,mousePressed,&no);TL_REDIRECT(patches,mouseHeld,&no);TL_REDIRECT(patches,windowWidth,&screenWidth);TL_REDIRECT(patches,windowHeight,&screenHeight);patches.redirect(reinterpret_cast<char*>(0x5561d8),reinterpret_cast<char*>(&gameui_detail::service::native_isVisible),&visible);patches.redirect(reinterpret_cast<char*>(0x5560d8),reinterpret_cast<char*>(&gameui_detail::service::native_windowWidth),&width);patches.redirect(reinterpret_cast<char*>(0x552ab8),reinterpret_cast<char*>(&gameui_detail::service::native_windowHeight),&height);patches.redirect(reinterpret_cast<char*>(0x5548a8),reinterpret_cast<char*>(&gameui_detail::service::native_position),&position);if(patches.failed())_exit(42);if(expected)restoredUpdate(w->ui,0.125f,NULL,NULL);else originalUpdate(w->ui,0.125f,NULL,NULL);
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void expected(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(gameui_entry_recovered_tooltip_position_characterization){int failures=0;unsigned count=0;const float screen[]={50,200,800};const long x[]={-10,0,20,190,800,1000000000};const long y[]={-10,0,10,60,200,999,1000};for(unsigned a=0;a<3;++a)for(unsigned b=0;b<6;++b)for(unsigned c=0;c<7;++c)for(unsigned g=0;g<4;++g)for(unsigned mode=0;mode<3;++mode){Case item={screen[a],x[b],y[c],g,mode};autotest::Outcome u,v;autotest::runChild(original,&item,u);autotest::runChild(expected,&item,v);bool ok=WIFEXITED(u.status)&&WEXITSTATUS(u.status)==0&&WIFEXITED(v.status)&&WEXITSTATUS(v.status)==0&&u.capture.length==v.capture.length&&u.capture.length<autotest::Capture::kSize&&std::memcmp(u.capture.data,v.capture.data,u.capture.length)==0;TL_CHECK(failures,ok);if(!ok){host->log(" tooltip %u %u %u geometry %u mode %u statuses %d/%d sizes %lu/%lu\n",a,b,c,g,mode,u.status,v.status,(unsigned long)u.capture.length,(unsigned long)v.capture.length);return failures;}++count;}host->log("    gameui tooltip positioning: %u cases; cinematic early return\n",count);return failures;}
