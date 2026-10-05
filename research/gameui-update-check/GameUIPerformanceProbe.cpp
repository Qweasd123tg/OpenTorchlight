#define OTL_RECOVERED_TEST_PLT
#include "implementation/RecoveredPhases.h"
#include <map>
#include <new>
// Complete no-character frame path; real pinned Ogre math, controlled services.
#include <cstring>
#include <Ogre.h>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void originalUpdate(void*,float,void*,void*) __asm__("__tlorig__ZN7CGameUI14updateIngameUIEfP11CGameClientPN4Ogre12RenderWindowE");
TL_FUNCTION(settingsGet,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(mousePressed,"_ZN13CMouseManager13buttonPressedE12EMouseButton")
TL_FUNCTION(textEvents,"_ZN7CGameUI16updateTextEventsEfRN4Ogre7Vector3ERNS0_7Matrix4Eb")
TL_FUNCTION(modalPartial,"_ZN7CGameUI22modalDialogOpenPartialEv")
TL_FUNCTION(consoleVisible,"_ZN8CConsole10getVisibleEv")
TL_FUNCTION(consoleUpdate,"_ZN8CConsole6updateEf")
TL_FUNCTION(menuUpdate,"_ZN12CMenuManager6updateEfP11CGameClientPN4Ogre12RenderWindowE")
namespace {
template<class T>T& at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
struct Case{unsigned rotation,flags,console,mode;float elapsed;unsigned perfFlags,meshCount;int fps;};
struct World{unsigned long long ui[0x1a08/8],radio[0x800/8],cinema[0x100/8],cameras[2],cameraVT[0x2e0/8],consoles[2],menus[2],windows[3],settings,client,renderWindow[0x60/8],manager[0x100/8],particles[0x520/8],missiles[0x90/8],resources[8],perfLevel[0x230/8],renderStats[0x40/8],resourceVT[16],renderVT[16],materials[0x100/8],meshes[0x400/8],textures[0x100/8];int updatePerf;std::wstring*version;Ogre::Quaternion orientation[2];Ogre::Vector3 position[2];Ogre::Matrix4 projection[2];World(){std::memset(ui,0,sizeof(ui));std::memset(radio,0,sizeof(radio));std::memset(cinema,0,sizeof(cinema));std::memset(cameraVT,0,sizeof(cameraVT));}};
World*w;const Case*input;autotest::Capture*out;unsigned orientations;
void n(unsigned x){out->add(&x,sizeof(x));}void real(float x){out->add(&x,sizeof(x));}
unsigned cameraID(void*p){return p==&w->cameras[0]?0:p==&w->cameras[1]?1:99;}void*camera(){return at<void*>(w->ui,0x10);}
int zero(void*p,unsigned key){
 if(key==gameui_recovered::service::key_DISPLAY_STATS){n(50);n(p==&w->settings);return (input->perfFlags>>1)&1;}
 if(key==gameui_recovered::service::key_UPDATE_PERF){n(51);n(p==&w->settings);return w->updatePerf;}
 if(key==gameui_recovered::service::key_NUM_TICKS_PER_SECOND){n(52);n(p==&w->settings);return 60;}
 if(key==gameui_recovered::service::key_CURRENT_FPS){n(53);n(p==&w->settings);return input->fps;}
 return 0;}
void setInt(void*p,unsigned key,int value){n(54);n(p==&w->settings);n(key==gameui_recovered::service::key_UPDATE_PERF);n(value);w->updatePerf=value;}
float getFloat(void*p,unsigned key){n(55);n(p==&w->settings);n(key==gameui_recovered::service::key_F_AVERAGE_FPS);return 59.25f;}
const std::wstring&getString(void*p,unsigned key){n(56);n(p==&w->settings);n(key==gameui_recovered::service::key_S_VERSION);return *w->version;}
void*master(){n(57);return w->manager;}
void*missile(void*p){n(58);n(p==w->resources);return w->missiles;}
int cache(void*p){n(59);n(p==w->particles);return 7;}
int channels(void*p){n(60);n(p==w->resources);return 9;}
void*materialManager(){n(61);return w->materials;}
void*meshManager(){n(62);return w->meshes;}
void*textureManager(){n(63);return w->textures;}
unsigned long memory(void*p){n(64);unsigned id=p==w->materials?0:p==w->meshes?1:2;n(id);return 1000+id*500;}
void*renderStatistics(void*p){n(65);n(p==&w->renderWindow);return w->renderStats;}
void text(void*p,const CEGUI::String&value){n(66);n(p==reinterpret_cast<void*>(0xeeee));std::string bytes(reinterpret_cast<const char*>(value.c_str()));n(bytes.size());out->add(bytes.data(),bytes.size());}
void front(void*p){n(67);n(p==reinterpret_cast<void*>(0xeeee));}
bool yes(void*,unsigned){return true;}
void hidden(void*p,bool value){n(10);n(p==&w->windows[0]?0:p==&w->windows[1]?1:p==&w->windows[2]?2:99);n(value);}
const Ogre::Quaternion& orientation(void*p){unsigned id=cameraID(p);n(11);n(id);++orientations;if(input->mode==1&&orientations==1)at<void*>(w->ui,0x10)=&w->cameras[1];return w->orientation[id%2];}
const Ogre::Vector3& position(void*p){unsigned id=cameraID(p);n(12);n(id);if(input->mode==2)at<void*>(w->ui,0x10)=&w->cameras[1];return w->position[id%2];}
const Ogre::Matrix4& projection(void*p){unsigned id=cameraID(p);n(13);n(id);return w->projection[id%2];}
void events(void*p,float elapsed,Ogre::Vector3&up,Ogre::Matrix4&matrix,bool value){n(14);n(p==w->ui);real(elapsed);out->add(&up,sizeof(up));out->add(&matrix,sizeof(matrix));n(value);}
bool modal(void*p){n(15);n(p==w->ui);return input->flags&1;}
bool visible(void*p){n(16);n(p==&w->consoles[0]?0:1);if(input->mode==3){at<void*>(w->ui,0x1690)=&w->consoles[1];at<void*>(w->ui,0x588)=&w->menus[1];}return input->console==2;}
void console(void*p,float elapsed){n(17);n(p==&w->consoles[0]?0:1);real(elapsed);if(input->mode==3)at<void*>(w->ui,0x588)=&w->menus[0];}
void menus(void*p,float elapsed,void*client,void*window){n(18);n(p==&w->menus[0]?0:1);real(elapsed);n(client==&w->client);n(window==&w->renderWindow);}
void model(){gameui_recovered::Labels labels={"","","",""};gameui_recovered::Frame frame(w->ui,&w->client,&w->renderWindow,input->elapsed,labels);frame.run();}
void side(void*context,autotest::Capture&capture,bool expected){Case&c=*static_cast<Case*>(context);std::wstring version=L"1.15 / версия / 版本";World world;w=&world;input=&c;out=&capture;orientations=0;at<void*>(w->ui,0x78)=&w->settings;at<void*>(w->ui,0x200)=w->radio;at<void*>(w->ui,0x540)=w->cinema;at<unsigned char>(w->cinema,0x31)=1;at<void*>(w->ui,0x10)=&w->cameras[0];at<void*>(w->ui,0x138)=c.flags&1?&w->windows[0]:NULL;at<void*>(w->ui,0x120)=c.flags&2?&w->windows[1]:NULL;at<void*>(w->ui,0x170)=&w->windows[2];at<void*>(w->ui,0x1690)=c.console?&w->consoles[0]:NULL;at<void*>(w->ui,0x588)=&w->menus[0];w->cameraVT[0x2d8/8]=reinterpret_cast<unsigned long long>(&projection);w->cameras[0]=w->cameras[1]=reinterpret_cast<unsigned long long>(w->cameraVT);
 const Ogre::Quaternion qs[]={Ogre::Quaternion(1,0,0,0),Ogre::Quaternion(0.70710677f,0,0.70710677f,0),Ogre::Quaternion(0.5f,0.5f,0.5f,0.5f),Ogre::Quaternion(0.7f,0.2f,0.1f,0.3f)};for(unsigned i=0;i<2;++i){w->orientation[i]=qs[(c.rotation+i)%4];w->position[i]=Ogre::Vector3(float(c.rotation)-2.0f+i,float(i)-0.5f,3.0f+i);w->projection[i]=Ogre::Matrix4::IDENTITY;w->projection[i][0][0]=1.25f+float(c.rotation)/16;w->projection[i][0][2]=0.2f*c.rotation;w->projection[i][1][1]=0.75f;w->projection[i][1][3]=2;w->projection[i][2][2]=-1.01f;w->projection[i][2][3]=-0.2f;w->projection[i][3][2]=-1;w->projection[i][3][3]=0;}

 gameui_recovered::settingsToggleNames=90;
 gameui_recovered::service::key_DISPLAY_STATS=91;gameui_recovered::service::key_UPDATE_PERF=92;gameui_recovered::service::key_NUM_TICKS_PER_SECOND=93;gameui_recovered::service::key_CURRENT_FPS=94;gameui_recovered::service::key_S_VERSION=95;gameui_recovered::service::key_F_AVERAGE_FPS=96;
 std::memset(w->manager,0,sizeof(w->manager));std::memset(w->particles,0,sizeof(w->particles));std::memset(w->missiles,0,sizeof(w->missiles));std::memset(w->perfLevel,0,sizeof(w->perfLevel));std::memset(w->renderStats,0,sizeof(w->renderStats));
 w->version=&version;w->updatePerf=(c.perfFlags>>2)&1;
 at<void*>(w->ui,0xe0)=c.perfFlags&1?reinterpret_cast<void*>(0xeeee):NULL;
 at<unsigned char>(w->ui,0x12f8)=(c.perfFlags>>3)&1;
 at<void*>(w->ui,0x1308)=w->resources;
 at<void*>(w->manager,0x90)=&w->settings;at<void*>(w->manager,0x98)=w->resources;at<void*>(w->manager,0xf0)=w->particles;at<void*>(w->manager,0xf8)=w->particles;
 at<int>(w->missiles,0x88)=4;
 for(unsigned j=0;j<4;++j)at<unsigned>(w->particles,0x4ec+j*4)=101+j*199;
 at<int>(w->particles,0x508)=6;at<int>(w->particles,0x4fc)=8;at<int>(w->particles,0x500)=9;at<int>(w->particles,0x504)=10;
 at<int>(w->particles,0x50c)=90;at<long>(w->particles,0x510)=0x1000;at<long>(w->particles,0x518)=0x1020;
 at<void*>(w->ui,0x40)=c.meshCount&1?w->perfLevel:NULL;at<int>(w->perfLevel,0x228)=12345;at<int>(w->perfLevel,0x1a4)=3;at<int>(w->perfLevel,0x22c)=12;
 w->resourceVT[0x48/8]=reinterpret_cast<unsigned long long>(&memory);at<void*>(w->materials,0)=w->resourceVT;at<void*>(w->meshes,0)=w->resourceVT;at<void*>(w->textures,0)=w->resourceVT;
 typedef std::map<Ogre::ResourceHandle,Ogre::ResourcePtr> ResourceMap;ResourceMap*map=new(reinterpret_cast<char*>(w->meshes)+8)ResourceMap();
 for(unsigned j=0;j<c.meshCount;++j)(*map)[j]=Ogre::ResourcePtr();
 w->renderVT[0x78/8]=reinterpret_cast<unsigned long long>(&renderStatistics);at<void*>(w->renderWindow,0)=w->renderVT;
 at<float>(w->renderStats,0)=58.75f;at<unsigned long>(w->renderStats,0x20)=123456;at<unsigned long>(w->renderStats,0x28)=654;
 const unsigned long guards[]={0x14b9bb8,0x14b9bc0,0x14b9bc8,0x14b9bd0};for(unsigned i=0;i<4;++i)*reinterpret_cast<unsigned char*>(guards[i])=1;
 detour::Set patches;TL_REDIRECT(patches,settingsGet,&zero);TL_REDIRECT(patches,mousePressed,&yes);TL_REDIRECT(patches,textEvents,&events);TL_REDIRECT(patches,modalPartial,&modal);TL_REDIRECT(patches,consoleVisible,&visible);TL_REDIRECT(patches,consoleUpdate,&console);TL_REDIRECT(patches,menuUpdate,&menus);patches.redirect(reinterpret_cast<char*>(0x554718),reinterpret_cast<char*>(0x554718),&hidden);patches.redirect(reinterpret_cast<char*>(0x554d48),reinterpret_cast<char*>(0x554d48),&orientation);patches.redirect(reinterpret_cast<char*>(0x5545c8),reinterpret_cast<char*>(0x5545c8),&position);patches.redirect(reinterpret_cast<char*>(0xc6e410),reinterpret_cast<char*>(0xc6e410),&getFloat);
patches.redirect(reinterpret_cast<char*>(0xc6e650),reinterpret_cast<char*>(0xc6e650),&setInt);
patches.redirect(reinterpret_cast<char*>(0xc6e460),reinterpret_cast<char*>(0xc6e460),&getString);
patches.redirect(reinterpret_cast<char*>(0xa54490),reinterpret_cast<char*>(0xa54490),&master);
patches.redirect(reinterpret_cast<char*>(0xd6f510),reinterpret_cast<char*>(0xd6f510),&missile);
patches.redirect(reinterpret_cast<char*>(0xa34e80),reinterpret_cast<char*>(0xa34e80),&cache);
patches.redirect(reinterpret_cast<char*>(0xa6af80),reinterpret_cast<char*>(0xa6af80),&channels);
patches.redirect(reinterpret_cast<char*>(0x553708),reinterpret_cast<char*>(0x553708),&materialManager);
patches.redirect(reinterpret_cast<char*>(0x553c78),reinterpret_cast<char*>(0x553c78),&meshManager);
patches.redirect(reinterpret_cast<char*>(0x554988),reinterpret_cast<char*>(0x554988),&textureManager);
patches.redirect(reinterpret_cast<char*>(0x555c08),reinterpret_cast<char*>(0x555c08),&text);
patches.redirect(reinterpret_cast<char*>(0x5547c8),reinterpret_cast<char*>(0x5547c8),&front);
 if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){if(expected)model();else originalUpdate(w->ui,c.elapsed,&w->client,&w->renderWindow);out->add(reinterpret_cast<char*>(w->particles)+0x4ec,16);n(w->updatePerf);}
 map->~ResourceMap();
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void expected(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(gameui_recovered_performance_overlay){
 int failures=0;unsigned count=0;const int fps[]={-1,1,2,60,144};
 for(unsigned flags=0;flags<16;++flags)for(unsigned meshes=0;meshes<3;++meshes)for(unsigned f=0;f<5;++f){
 Case c={0,0,0,0,0.125f,flags,meshes,fps[f]};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(expected,&c,b);
 bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
 TL_CHECK(failures,ok);if(!ok){for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first difference %u: %u/%u\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}host->log("    perf case %u flags %u meshes %u fps %d status %d/%d sizes %lu/%lu\n",count,flags,meshes,c.fps,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);return failures;}++count;
 }host->log("    recovered performance overlay: %u cases, two frames\n",count);return failures;
}
