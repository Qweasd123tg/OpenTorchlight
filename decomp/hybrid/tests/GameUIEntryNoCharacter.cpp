
#include "GameUIUpdate.h"
// Complete no-character frame path; real pinned Ogre math, controlled services.
#include <cstring>
#include <Ogre.h>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void restoredUpdate(void*,float,void*,void*) __asm__("_ZN7CGameUI14updateIngameUIEfP11CGameClientPN4Ogre12RenderWindowE");
extern "C" void originalUpdate(void*,float,void*,void*) __asm__("__tlorig__ZN7CGameUI14updateIngameUIEfP11CGameClientPN4Ogre12RenderWindowE");
TL_FUNCTION(settingsGet,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(mousePressed,"_ZN13CMouseManager13buttonPressedE12EMouseButton")
TL_FUNCTION(textEvents,"_ZN7CGameUI16updateTextEventsEfRN4Ogre7Vector3ERNS0_7Matrix4Eb")
TL_FUNCTION(modalPartial,"_ZN7CGameUI22modalDialogOpenPartialEv")
TL_FUNCTION(consoleVisible,"_ZN8CConsole10getVisibleEv")
TL_FUNCTION(consoleUpdate,"_ZN8CConsole6updateEf")
TL_FUNCTION(menuUpdate,"_ZN12CMenuManager6updateEfP11CGameClientPN4Ogre12RenderWindowE")
namespace {
autotest::Coverage* actualCoverage;
struct EntryReceipt {
 autotest::Coverage coverage; const tlhybrid_host* host;
 EntryReceipt(const tlhybrid_host* h,const char* name):coverage(name,(uint64_t)(uintptr_t)&originalUpdate),host(h){actualCoverage=&coverage;}
 ~EntryReceipt(){coverage.report(host);actualCoverage=0;}
};
}
namespace {
template<class T>T& at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
struct Case{unsigned rotation,flags,console,mode;float elapsed;};
struct World{unsigned long long ui[0x1a08/8],radio[0x800/8],cinema[0x100/8],cameras[2],cameraVT[0x2e0/8],consoles[2],menus[2],windows[3],settings,client,renderWindow;Ogre::Quaternion orientation[2];Ogre::Vector3 position[2];Ogre::Matrix4 projection[2];World(){std::memset(ui,0,sizeof(ui));std::memset(radio,0,sizeof(radio));std::memset(cinema,0,sizeof(cinema));std::memset(cameraVT,0,sizeof(cameraVT));}};
World*w;const Case*input;autotest::Capture*out;unsigned orientations;
void n(unsigned x){out->add(&x,sizeof(x));}void real(float x){out->add(&x,sizeof(x));}
unsigned cameraID(void*p){return p==&w->cameras[0]?0:p==&w->cameras[1]?1:99;}void*camera(){return at<void*>(w->ui,0x10);}
int zero(void*,unsigned){return 0;}bool yes(void*,unsigned){return true;}
void hidden(void*p,bool value){n(10);n(p==&w->windows[0]?0:p==&w->windows[1]?1:p==&w->windows[2]?2:99);n(value);}
const Ogre::Quaternion& orientation(void*p){unsigned id=cameraID(p);n(11);n(id);++orientations;if(input->mode==1&&orientations==1)at<void*>(w->ui,0x10)=&w->cameras[1];return w->orientation[id%2];}
const Ogre::Vector3& position(void*p){unsigned id=cameraID(p);n(12);n(id);if(input->mode==2)at<void*>(w->ui,0x10)=&w->cameras[1];return w->position[id%2];}
const Ogre::Matrix4& projection(void*p){unsigned id=cameraID(p);n(13);n(id);return w->projection[id%2];}
void events(void*p,float elapsed,Ogre::Vector3&up,Ogre::Matrix4&matrix,bool value){n(14);n(p==w->ui);real(elapsed);out->add(&up,sizeof(up));out->add(&matrix,sizeof(matrix));n(value);}
bool modal(void*p){n(15);n(p==w->ui);return input->flags&1;}
bool visible(void*p){n(16);n(p==&w->consoles[0]?0:1);if(input->mode==3){at<void*>(w->ui,0x1690)=&w->consoles[1];at<void*>(w->ui,0x588)=&w->menus[1];}return input->console==2;}
void console(void*p,float elapsed){n(17);n(p==&w->consoles[0]?0:1);real(elapsed);if(input->mode==3)at<void*>(w->ui,0x588)=&w->menus[0];}
void menus(void*p,float elapsed,void*client,void*window){n(18);n(p==&w->menus[0]?0:1);real(elapsed);n(client==&w->client);n(window==&w->renderWindow);}
void model(){gameui_detail::Labels labels={"","","",""};gameui_detail::Frame frame(w->ui,&w->client,&w->renderWindow,input->elapsed,labels);frame.noCharacterFrame();}
void side(void*context,autotest::Capture&capture,bool expected){Case&c=*static_cast<Case*>(context);World world;w=&world;input=&c;out=&capture;orientations=0;at<void*>(w->ui,0x78)=&w->settings;at<void*>(w->ui,0x200)=w->radio;at<void*>(w->ui,0x540)=w->cinema;at<unsigned char>(w->cinema,0x31)=1;at<void*>(w->ui,0x10)=&w->cameras[0];at<void*>(w->ui,0x138)=c.flags&1?&w->windows[0]:NULL;at<void*>(w->ui,0x120)=c.flags&2?&w->windows[1]:NULL;at<void*>(w->ui,0x170)=&w->windows[2];at<void*>(w->ui,0x1690)=c.console?&w->consoles[0]:NULL;at<void*>(w->ui,0x588)=&w->menus[0];w->cameraVT[0x2d8/8]=reinterpret_cast<unsigned long long>(&projection);w->cameras[0]=w->cameras[1]=reinterpret_cast<unsigned long long>(w->cameraVT);
 const Ogre::Quaternion qs[]={Ogre::Quaternion(1,0,0,0),Ogre::Quaternion(0.70710677f,0,0.70710677f,0),Ogre::Quaternion(0.5f,0.5f,0.5f,0.5f),Ogre::Quaternion(0.7f,0.2f,0.1f,0.3f)};for(unsigned i=0;i<2;++i){w->orientation[i]=qs[(c.rotation+i)%4];w->position[i]=Ogre::Vector3(float(c.rotation)-2.0f+i,float(i)-0.5f,3.0f+i);w->projection[i]=Ogre::Matrix4::IDENTITY;w->projection[i][0][0]=1.25f+float(c.rotation)/16;w->projection[i][0][2]=0.2f*c.rotation;w->projection[i][1][1]=0.75f;w->projection[i][1][3]=2;w->projection[i][2][2]=-1.01f;w->projection[i][2][3]=-0.2f;w->projection[i][3][2]=-1;w->projection[i][3][3]=0;}
 const unsigned long guards[]={0x14b9bb8,0x14b9bc0,0x14b9bc8,0x14b9bd0};for(unsigned i=0;i<4;++i)*reinterpret_cast<unsigned char*>(guards[i])=1;
 detour::Set patches;TL_REDIRECT(patches,settingsGet,&zero);TL_REDIRECT(patches,mousePressed,&yes);TL_REDIRECT(patches,textEvents,&events);TL_REDIRECT(patches,modalPartial,&modal);TL_REDIRECT(patches,consoleVisible,&visible);TL_REDIRECT(patches,consoleUpdate,&console);TL_REDIRECT(patches,menuUpdate,&menus);patches.redirect(reinterpret_cast<char*>(0x554718),reinterpret_cast<char*>(&gameui_detail::service::native_visible),&hidden);patches.redirect(reinterpret_cast<char*>(0x554d48),reinterpret_cast<char*>(&gameui_detail::service::native_cameraOrientation),&orientation);patches.redirect(reinterpret_cast<char*>(0x5545c8),reinterpret_cast<char*>(&gameui_detail::service::native_cameraPosition),&position);if(patches.failed())_exit(42);if(expected)autotest::invoke(capture,&restoredUpdate,w->ui,c.elapsed,&w->client,&w->renderWindow);else autotest::invoke(capture,&originalUpdate,w->ui,c.elapsed,&w->client,&w->renderWindow);
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void expected(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(gameui_entry_recovered_no_character_frame_characterization){EntryReceipt receiptScope(host,"gameui_entry_recovered_no_character_frame_characterization");int failures=0;unsigned count=0;const float elapsed[]={0,0.016f,-0.25f};for(unsigned rotation=0;rotation<4;++rotation)for(unsigned flags=0;flags<4;++flags)for(unsigned console=0;console<3;++console)for(unsigned mode=0;mode<4;++mode)for(unsigned t=0;t<3;++t){Case c={rotation,flags,console,mode,elapsed[t]};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(expected,&c,b);int receiptPair=actualCoverage->observe(host,a,b);bool ok=receiptPair==0&&a.reportValid&&b.reportValid&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;TL_CHECK(failures,ok);if(!ok){host->log(" no character rotation %u flags %u console %u mode %u time %u status %d/%d sizes %lu/%lu\n",rotation,flags,console,mode,t,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);return failures;}++count;}host->log("    gameui no-character frame: %u cases; complete controlled path\n",count);return failures;}
