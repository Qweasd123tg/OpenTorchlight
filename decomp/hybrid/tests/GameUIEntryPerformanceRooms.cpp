
#include "GameUIUpdate.h"
#include <map>
#include <new>
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
TL_FUNCTION(perfPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(perfRoom,"_ZN6CLevel23getRoomThatPositionIsInERKN4Ogre7Vector3E")
TL_FUNCTION(entryDep_c6e410,"_ZN20CDynamicPropertyFile8GetFloatEj")
TL_FUNCTION(entryDep_c6e650,"_ZN20CDynamicPropertyFile6SetIntEji")
TL_FUNCTION(entryDep_c6e460,"_ZN20CDynamicPropertyFile9GetStringEj")
TL_FUNCTION(entryDep_a54490,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(entryDep_d6f510,"_ZN16CResourceManager19getMissilePreloaderEv")
TL_FUNCTION(entryDep_a34e80,"_ZN18CParticlePreloader21getParticleCacheCountEv")
TL_FUNCTION(entryDep_a6af80,"_ZN13CSoundManager26getNumberOfChannelsPlayingEv")
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
struct Case{unsigned rotation,flags,console,mode;float elapsed;unsigned perfFlags,meshCount;int fps;unsigned roomMode,resourceMode;};
struct World{unsigned long long ui[0x1a08/8],radio[0x800/8],cinema[0x100/8],cameras[2],cameraVT[0x2e0/8],consoles[2],menus[2],windows[3],settings,client,renderWindow[0x60/8],manager[0x100/8],particles[0x520/8],missiles[0x90/8],resources[8],perfLevel[0x230/8],renderStats[0x40/8],resourceVT[16],renderVT[16],materials[0x100/8],meshes[0x400/8],textures[0x100/8];unsigned long long actorToken,room[0x180/8];unsigned meshCalls;int updatePerf;std::wstring*version;Ogre::Quaternion orientation[2];Ogre::Vector3 position[2];Ogre::Matrix4 projection[2];World(){std::memset(ui,0,sizeof(ui));std::memset(radio,0,sizeof(radio));std::memset(cinema,0,sizeof(cinema));std::memset(cameraVT,0,sizeof(cameraVT));}};
World*w;const Case*input;autotest::Capture*out;unsigned orientations;
void n(unsigned x){out->add(&x,sizeof(x));}void real(float x){out->add(&x,sizeof(x));}
unsigned cameraID(void*p){return p==&w->cameras[0]?0:p==&w->cameras[1]?1:99;}void*camera(){return at<void*>(w->ui,0x10);}
int zero(void*p,unsigned key){
 if(key==gameui_detail::service::key_DISPLAY_STATS){n(50);n(p==&w->settings);return (input->perfFlags>>1)&1;}
 if(key==gameui_detail::service::key_UPDATE_PERF){n(51);n(p==&w->settings);return w->updatePerf;}
 if(key==gameui_detail::service::key_NUM_TICKS_PER_SECOND){n(52);n(p==&w->settings);return 60;}
 if(key==gameui_detail::service::key_CURRENT_FPS){n(53);n(p==&w->settings);return input->fps;}
 return 0;}
void setInt(void*p,unsigned key,int value){n(54);n(p==&w->settings);n(key==gameui_detail::service::key_UPDATE_PERF);n(value);w->updatePerf=value;}
float getFloat(void*p,unsigned key){n(55);n(p==&w->settings);n(key==gameui_detail::service::key_F_AVERAGE_FPS);return 59.25f;}
const std::wstring&getString(void*p,unsigned key){n(56);n(p==&w->settings);n(key==gameui_detail::service::key_S_VERSION);return *w->version;}
void*master(){n(57);return w->manager;}
void*missile(void*p){n(58);n(p==w->resources);return w->missiles;}
int cache(void*p){n(59);n(p==w->particles);return 7;}
int channels(void*p){n(60);n(p==w->resources);return 9;}
void*materialManager(){n(61);return w->materials;}
void*meshManager(){n(62);++w->meshCalls;if(w->meshCalls==2&&input->roomMode){at<void*>(w->ui,0x38)=&w->actorToken;at<void*>(w->ui,0x40)=w->perfLevel;}return w->meshes;}
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

class ProbeResource:public Ogre::Resource {
 unsigned id;
protected:
 void loadImpl(){} void unloadImpl(){} size_t calculateSize()const{return 1;}
public:
 ProbeResource(unsigned i):Ogre::Resource(NULL,"probe",i,"test"),id(i){}
 ~ProbeResource(){n(90);n(id);}
};
Ogre::Vector3 roomPosition(void* p,bool derived){n(80);n(p==&w->actorToken);n(derived);return Ogre::Vector3(1.25f,-3.5f,6);}
void* roomLookup(void* p,const Ogre::Vector3& pos){n(81);n(p==w->perfLevel);out->add(&pos,sizeof(pos));return input->roomMode==1?NULL:w->room;}
void model(){gameui_detail::Labels labels={"","","",""};gameui_detail::Frame frame(w->ui,&w->client,&w->renderWindow,input->elapsed,labels);frame.run();}
void side(void*context,autotest::Capture&capture,bool expected){Case&c=*static_cast<Case*>(context);std::wstring version=L"1.15 / версия / 版本";World world;w=&world;input=&c;out=&capture;orientations=0;at<void*>(w->ui,0x78)=&w->settings;at<void*>(w->ui,0x200)=w->radio;at<void*>(w->ui,0x540)=w->cinema;at<unsigned char>(w->cinema,0x31)=1;at<void*>(w->ui,0x10)=&w->cameras[0];at<void*>(w->ui,0x138)=c.flags&1?&w->windows[0]:NULL;at<void*>(w->ui,0x120)=c.flags&2?&w->windows[1]:NULL;at<void*>(w->ui,0x170)=&w->windows[2];at<void*>(w->ui,0x1690)=c.console?&w->consoles[0]:NULL;at<void*>(w->ui,0x588)=&w->menus[0];w->cameraVT[0x2d8/8]=reinterpret_cast<unsigned long long>(&projection);w->cameras[0]=w->cameras[1]=reinterpret_cast<unsigned long long>(w->cameraVT);
 const Ogre::Quaternion qs[]={Ogre::Quaternion(1,0,0,0),Ogre::Quaternion(0.70710677f,0,0.70710677f,0),Ogre::Quaternion(0.5f,0.5f,0.5f,0.5f),Ogre::Quaternion(0.7f,0.2f,0.1f,0.3f)};for(unsigned i=0;i<2;++i){w->orientation[i]=qs[(c.rotation+i)%4];w->position[i]=Ogre::Vector3(float(c.rotation)-2.0f+i,float(i)-0.5f,3.0f+i);w->projection[i]=Ogre::Matrix4::IDENTITY;w->projection[i][0][0]=1.25f+float(c.rotation)/16;w->projection[i][0][2]=0.2f*c.rotation;w->projection[i][1][1]=0.75f;w->projection[i][1][3]=2;w->projection[i][2][2]=-1.01f;w->projection[i][2][3]=-0.2f;w->projection[i][3][2]=-1;w->projection[i][3][3]=0;}

 gameui_detail::settingsToggleNames=90;
 gameui_detail::service::key_DISPLAY_STATS=91;gameui_detail::service::key_UPDATE_PERF=92;gameui_detail::service::key_NUM_TICKS_PER_SECOND=93;gameui_detail::service::key_CURRENT_FPS=94;gameui_detail::service::key_S_VERSION=95;gameui_detail::service::key_F_AVERAGE_FPS=96;
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
 for(unsigned j=0;j<c.meshCount;++j)(*map)[j]=c.resourceMode?Ogre::ResourcePtr(new ProbeResource(j)):Ogre::ResourcePtr();
 w->renderVT[0x78/8]=reinterpret_cast<unsigned long long>(&renderStatistics);at<void*>(w->renderWindow,0)=w->renderVT;
 at<float>(w->renderStats,0)=58.75f;at<unsigned long>(w->renderStats,0x20)=123456;at<unsigned long>(w->renderStats,0x28)=654;
 const unsigned long guards[]={0x14b9bb8,0x14b9bc0,0x14b9bc8,0x14b9bd0};for(unsigned i=0;i<4;++i)*reinterpret_cast<unsigned char*>(guards[i])=1;
new(reinterpret_cast<char*>(w->room)+0x168)std::wstring(c.roomMode==2?L"MEDIA/LEVELS/TEST/room.layout":c.roomMode==3?L"MEDIA/Комната.layout":L"");
 detour::Set patches;TL_REDIRECT(patches,settingsGet,&zero);TL_REDIRECT(patches,mousePressed,&yes);TL_REDIRECT(patches,textEvents,&events);TL_REDIRECT(patches,modalPartial,&modal);TL_REDIRECT(patches,consoleVisible,&visible);TL_REDIRECT(patches,consoleUpdate,&console);TL_REDIRECT(patches,menuUpdate,&menus);patches.redirect(reinterpret_cast<char*>(0x554718),reinterpret_cast<char*>(&gameui_detail::service::native_visible),&hidden);patches.redirect(reinterpret_cast<char*>(0x554d48),reinterpret_cast<char*>(&gameui_detail::service::native_cameraOrientation),&orientation);patches.redirect(reinterpret_cast<char*>(0x5545c8),reinterpret_cast<char*>(&gameui_detail::service::native_cameraPosition),&position);TL_REDIRECT(patches,entryDep_c6e410,&getFloat);
TL_REDIRECT(patches,entryDep_c6e650,&setInt);
TL_REDIRECT(patches,entryDep_c6e460,&getString);
TL_REDIRECT(patches,entryDep_a54490,&master);
TL_REDIRECT(patches,entryDep_d6f510,&missile);
TL_REDIRECT(patches,entryDep_a34e80,&cache);
TL_REDIRECT(patches,entryDep_a6af80,&channels);
patches.redirect(reinterpret_cast<char*>(0x553708),reinterpret_cast<char*>(&gameui_detail::service::native_materialManager),&materialManager);
patches.redirect(reinterpret_cast<char*>(0x553c78),reinterpret_cast<char*>(&gameui_detail::service::native_meshManager),&meshManager);
patches.redirect(reinterpret_cast<char*>(0x554988),reinterpret_cast<char*>(&gameui_detail::service::native_textureManager),&textureManager);
patches.redirect(reinterpret_cast<char*>(0x555c08),reinterpret_cast<char*>(&gameui_detail::service::native_text),&text);
patches.redirect(reinterpret_cast<char*>(0x5547c8),reinterpret_cast<char*>(&gameui_detail::service::native_front),&front);
 TL_REDIRECT(patches,perfPosition,&roomPosition);TL_REDIRECT(patches,perfRoom,&roomLookup);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){w->meshCalls=0;at<void*>(w->ui,0x38)=NULL;if(expected)if(repeat==0){autotest::invoke(capture,&restoredUpdate,w->ui,c.elapsed,&w->client,&w->renderWindow);}else{restoredUpdate(w->ui,c.elapsed,&w->client,&w->renderWindow);}else if(repeat==0){autotest::invoke(capture,&originalUpdate,w->ui,c.elapsed,&w->client,&w->renderWindow);}else{originalUpdate(w->ui,c.elapsed,&w->client,&w->renderWindow);}out->add(reinterpret_cast<char*>(w->particles)+0x4ec,16);n(w->updatePerf);}
 for(ResourceMap::iterator it=map->begin();it!=map->end();++it){n(it->second.isNull());if(!it->second.isNull())n(it->second.useCount());}
 map->~ResourceMap();typedef std::wstring WS;at<WS>(w->room,0x168).~WS();
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void expected(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(gameui_entry_recovered_performance_rooms){EntryReceipt receiptScope(host,"gameui_entry_recovered_performance_rooms");int failures=0;unsigned count=0;
for(unsigned room=0;room<5;++room)for(unsigned resources=0;resources<2;++resources)for(unsigned meshes=0;meshes<4;++meshes){
Case c={0,0,0,0,0.125f,7,meshes,60,room,resources};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(expected,&c,b);int receiptPair=actualCoverage->observe(host,a,b);
bool ok=receiptPair==0&&a.reportValid&&b.reportValid&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
if(!ok){for(unsigned i=0;i<a.capture.length&&i<b.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    first diff %u values %u/%u\n",i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);break;}host->log("    perf room %u resources %u meshes %u status %d/%d bytes %lu/%lu\n",room,resources,meshes,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);return 1;}++count;}
host->log("    performance rooms/resources: %u two-frame cases\n",count);return failures;}
