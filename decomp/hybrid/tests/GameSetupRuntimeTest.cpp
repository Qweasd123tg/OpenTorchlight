#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <clocale>
#include <dlfcn.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <execinfo.h>
#include <OgreDefaultHardwareBufferManager.h>
#include <OgreLogManager.h>
#include "AutoTest.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/SystemsNativeGame.h"
#include "tests/GameSetupCleanBootstrap.h"
#include "tests/NativeMenuClient.h"
#include "CharacterLibraryBoundary.h"
#include "LinuxUtils.h"
#include "MasterResourceManager.h"
#include "MissilePreloader.h"
#include "SteamStats.h"
#include "Splash.h"
#include <ParticleUniverseSystemManager.h>
extern "C" SDL_Window*SDL_CreateWindow(const char*,int,int,int,int,Uint32);
extern "C" void SDL_DestroyWindow(SDL_Window*);
TL_ORIGINAL(bool,setupOld,(CGame*,bool),"_ZN5CGame5setupEb")
extern "C" bool setupNew(CGame*,bool) __asm__("_ZN5CGame5setupEb");
TL_FUNCTION(setupLocal,"_ZN10FILESYSTEM12GetLocalPathEv")
TL_FUNCTION(setupAppData,"_ZN10FILESYSTEM14GetAppDataPathEv")
TL_FUNCTION(setupResources,"_ZN5CGame14setupResourcesEv")
TL_FUNCTION(setupConfigure,"_ZN5CGame9configureEb")
TL_FUNCTION(setupChoose,"_ZN5CGame18chooseSceneManagerEv")
TL_FUNCTION(setupCamera,"_ZN5CGame12createCameraEv")
TL_FUNCTION(setupViewport,"_ZN5CGame15createViewportsEv")
TL_FUNCTION(setupListener,"_ZN5CGame22createResourceListenerEv")
TL_FUNCTION(setupLoad,"_ZN5CGame13loadResourcesEv")
TL_FUNCTION(setupMaterials,"_ZN5CGame15createMaterialsEv")
TL_FUNCTION(setupResize,"_ZN5CGame13windowResizedEPN4Ogre12RenderWindowE")
TL_FUNCTION(setupFrame,"_ZN5CGame19createFrameListenerEv")
TL_FUNCTION(setupClient,"_ZN5CGame16createGameClientEv")
TL_FUNCTION(setupInitialize,"_ZN13CSoundManager10initializeEP9CSettings")
TL_FUNCTION(setupLevels,"_ZN13CSoundManager17updateAudioLevelsEffbb")
TL_FUNCTION(setupParticles,"_ZN22CMasterResourceManager13loadParticlesEv")
TL_FUNCTION(setupMissiles,"_ZN17CMissilePreloader14reloadMissilesEv")
TL_FUNCTION(setupFps,"_ZN16ParticleUniverse21ParticleSystemManager14setParticleFPSEf")
TL_FUNCTION(setupPercent,"_ZN16ParticleUniverse21ParticleSystemManager27setEmitterLoopingReleasePCTEf")
TL_FUNCTION(setupSplashInit,"_ZN7CSplash4InitEPvi")
TL_FUNCTION(setupSplashShow,"_ZN7CSplash4ShowEv")
TL_FUNCTION(setupSplashHide,"_ZN7CSplash4HideEv")
TL_FUNCTION(setupMessage,"_Z11MessageBoxAPvPKcS1_i")
TL_FUNCTION(setupDesktop,"_ZN10LinuxUtils20GetDesktopResolutionERiS0_")
namespace {
struct Case{unsigned mode,profile,control;};const Case*current;autotest::Capture*cap;CGame*game;Ogre::RenderWindow*window;Ogre::RenderWindow*offscreen;Ogre::SceneManager*scenes[4];CCameraControl*camera;std::string base;std::wstring local;const tlhybrid_host*debugHost;
void num(unsigned n){cap->add(&n,4);}void real(float f){cap->add(&f,4);}
void fault(int sig){void*frames[32];int count=backtrace(frames,32);debugHost->log("    setup signal%u mode%u profile%u frames%u\n",sig,current?current->mode:99,current?current->profile:99,count);for(int i=0;i<count;++i)debugHost->log("    setup frame%d %p\n",i,frames[i]);_exit(128+sig);}
class Window:public Ogre::RenderWindow {
public:
 Window(unsigned w,unsigned h){mWidth=w;mHeight=h;}
 void create(const Ogre::String&,unsigned,unsigned,bool,const Ogre::NameValuePairList*){std::abort();}
 void destroy(){}void resize(unsigned w,unsigned h){mWidth=w;mHeight=h;}void reposition(int,int){std::abort();}
 bool isClosed()const{return false;}
 void copyContentsToMemory(const Ogre::PixelBox&,Ogre::RenderTarget::FrameBuffer){std::abort();}bool requiresTextureFlipping()const{return false;}
 void setActive(bool active){num(17);num(active);Ogre::RenderTarget::setActive(active);}
 void getCustomAttribute(const std::string&name,void*p){num(18);cap->addText(name);*static_cast<unsigned long*>(p)=0x10000+current->profile;}
 void addListener(Ogre::RenderTargetListener*p){num(19);num(p==static_cast<Ogre::RenderTargetListener*>(game));Ogre::RenderTarget::addListener(p);}
};
std::wstring getLocal(){num(1);return local;}
std::wstring getAppData(){num(2);return local+(current->profile&4?L"/данные/":L"/appdata/");}
void resources(CGame*p){num(3);num(p==game);num(p->m_root!=NULL);}
bool configure(CGame*p,bool create){num(4);num(p==game);num(create);num(p->m_settings->GetInt(KSETTINGS_OPENGL));bool hasWindow=current->mode>=3&&current->mode<=5;window=NULL;offscreen=NULL;if(p->m_root){offscreen=new Window(317,239);if(hasWindow)window=new Window(641+current->profile*2,481+current->profile*2);}p->m_renderWindow=window;return current->mode==0||current->mode==3||current->mode==5;}
void choose(CGame*p){num(5);num(p==game);new Ogre::DefaultHardwareBufferManager;for(unsigned i=0;i<4;++i){char name[32];std::sprintf(name,"setup-scene-%u",i);scenes[i]=p->m_root->createSceneManager(Ogre::ST_GENERIC,name);}p->m_sceneManager=scenes[0];p->m_renderBehindScene=scenes[1];p->m_renderBehindParticleScene=scenes[2];p->m_automapScene=scenes[3];}
void createCamera(CGame*p){num(6);num(p==game);menugui::ProjectionDuringConstruction projection;Ogre::Camera*c[5];for(unsigned i=0;i<5;++i){char name[32];std::sprintf(name,"setup-camera-%u",i);c[i]=scenes[0]->createCamera(name);}camera=static_cast<CCameraControl*>(Ogre::NedAllocImpl::allocBytes(sizeof(CCameraControl),0,0,0));mgCameraCtor(camera,c[0],c[1],c[2],c[3],c[4]);p->m_cameraControl=camera;p->m_viewport=offscreen->addViewport(c[0]);}
void createViewport(CGame*p){num(7);num(p==game);p->m_viewport=p->m_renderWindow->addViewport(camera->m_cameras[0]);}
bool render(Ogre::Root*p){num(8);num(p==game->m_root);num(game->m_viewport->getClearEveryFrame());num(game->m_viewport->getClearBuffers());return current->profile&1;}
void initialize(CSoundManager*p,CSettings*s){num(9);num(p==game->m_soundManager);num(s==game->m_settings);num(p->m_bUnknown6C8);}
void levels(CSoundManager*p,float s,float m,bool sm,bool mm){num(10);num(p==game->m_soundManager);num(p->m_bUnknown6A9);real(s);real(m);num(sm);num(mm);}
void particles(CMasterResourceManager*p){num(11);num(p==game->m_masterResourceManager);num(p->m_renderTarget==game->m_renderWindow);num(p->m_pSoundManager==game->m_soundManager);num(p->m_pDefaultSceneManager==scenes[0]);num(p->m_pSceneManager==scenes[1]);num(p->m_renderBehindParticleScene==scenes[2]);num(p->m_automapScene==scenes[3]);}
void missiles(CMissilePreloader*p){num(12);num(p==game->m_masterResourceManager->m_missilePreloader);}
void listener(CGame*p){num(13);num(p==game);}void load(CGame*p){num(14);num(p==game);}void materials(CGame*p){num(15);num(p==game);}void resize(CGame*p,Ogre::RenderWindow*w){num(16);num(p==game);num(w==window);}void frame(CGame*p){num(20);num(p==game);}
void client(CGame*p){num(21);num(p==game);num(p->m_soundManager->m_bUnknown6A9);num(CSteamStats::getSingleton()->m_game==p);}
void fps(float value){num(22);real(value);}void percent(float value){num(23);real(value);}
void splashInit(CSplash*p,void*parent,int unused){num(24);num(p==reinterpret_cast<CSplash*>(0x1424b60));num(parent==game->m_editorWindow);num(unused);}
void splashShow(CSplash*p){num(25);num(p==reinterpret_cast<CSplash*>(0x1424b60));}void splashHide(CSplash*p){num(26);num(p==reinterpret_cast<CSplash*>(0x1424b60));}
int message(void*parent,const char*text,const char*title,int flags){num(27);num(parent==NULL);cap->addText(std::string(text));cap->addText(std::string(title));num(flags);return 1;}
void desktop(int&w,int&h){num(28);w=current->profile&2?320:1921;h=current->profile&2?241:1081;}
void position(SDL_Window*p,int x,int y){num(29);num(p==game->m_sdlWindow);num(x);num(y);}
void show(SDL_Window*p){num(30);num(p==game->m_sdlWindow);}
void log(Ogre::LogManager*,const std::string&s,Ogre::LogMessageLevel level,bool mask){if(s.find("Path for ")==0){num(31);cap->addText(s);num(level);num(mask);}}
void side(void*raw,autotest::Capture&out,bool ours){
 Case c=*static_cast<Case*>(raw);current=&c;cap=&out;camera=NULL;signal(SIGSEGV,fault);signal(SIGABRT,fault);LinuxUtils::gameHomePath=local+L"/";
 if(!game_setup_fixture::finishInheritedOwners())std::abort();
 SystemsNativeGame native;game=native.game;Ogre::Root*old=native.root;native.root=NULL;native.ownsRoot=false;systemsGameRootDtor(old);Ogre::NedAllocImpl::deallocBytes(old);
 if(SDL_VideoInit("dummy"))std::abort();SDL_Window*sdl=SDL_CreateWindow("setup comparison",0,0,641+c.profile*2,481+c.profile*2,8);if(!sdl)std::abort();
 window=NULL;offscreen=NULL;game->m_sdlWindow=sdl;game->m_editorWindow=static_cast<void*>(sdl);game->m_width=71;game->m_height=73;game->m_windowHandle=static_cast<void*>(sdl);game->m_pluginsFile=base+(c.mode>=6?"bad/":"ok/");
 CSettings*s=game->m_settings;s->SetInt(KSETTINGS_FULLSCREEN,c.mode>=6?int(c.mode-6):(c.profile%3==0?0:c.profile%3==1?1:-1));s->SetInt(KSETTINGS_NO_SOUNDS,c.profile%3==0?0:c.profile%3==1?1:-1);s->SetInt(KSETTINGS_SOUNDMUTE,c.profile&1?2:0);s->SetInt(KSETTINGS_MUSICMUTE,c.profile&2?-1:0);s->SetFloat(KSETTINGS_F_SOUNDVOLUME,(float(c.profile)-2.f)*.25f);s->SetFloat(KSETTINGS_F_MUSICVOLUME,(float(c.profile)-1.f)*.5f);s->SetFloat(KSETTINGS_F_PARTICLE_FALLOFF,float(c.profile)*37.5f-25.f);s->SetFloat(KSETTINGS_F_PARTICLEFPS,float(c.profile)*15.f);
 unsigned bits[]={0xc1c80000,0x80000000,0,0x41c80000,0x42c80000,0x42fa0000,0x7fc12345,0x7f800000};float pct;std::memcpy(&pct,&bits[c.profile],4);s->SetFloat(KSETTINGS_F_PARTICLE_PCT,pct);*reinterpret_cast<bool*>(0x14210a4)=c.profile&1;
 detour::Set d;TL_REDIRECT(d,setupAppData,getAppData);TL_REDIRECT(d,setupResources,resources);TL_REDIRECT(d,setupConfigure,configure);TL_REDIRECT(d,setupChoose,choose);TL_REDIRECT(d,setupCamera,createCamera);TL_REDIRECT(d,setupViewport,createViewport);TL_REDIRECT(d,setupListener,listener);TL_REDIRECT(d,setupLoad,load);TL_REDIRECT(d,setupMaterials,materials);TL_REDIRECT(d,setupResize,resize);TL_REDIRECT(d,setupFrame,frame);TL_REDIRECT(d,setupClient,client);TL_REDIRECT(d,setupInitialize,initialize);TL_REDIRECT(d,setupLevels,levels);TL_REDIRECT(d,setupParticles,particles);TL_REDIRECT(d,setupMissiles,missiles);TL_REDIRECT(d,setupFps,fps);TL_REDIRECT(d,setupPercent,percent);TL_REDIRECT(d,setupSplashInit,splashInit);TL_REDIRECT(d,setupSplashShow,splashShow);TL_REDIRECT(d,setupSplashHide,splashHide);TL_REDIRECT(d,setupMessage,message);TL_REDIRECT(d,setupDesktop,desktop);
 CharacterLibraryBoundary renderBound(characterLibraryEntry("libOgreMain-1.6.5.so","_ZN4Ogre4Root14renderOneFrameEv"),render),logBound(characterLibraryEntry("libOgreMain-1.6.5.so","_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb"),log);
 d.redirect(reinterpret_cast<char*>(&SDL_SetWindowPosition),reinterpret_cast<char*>(&SDL_SetWindowPosition),position);d.redirect(reinterpret_cast<char*>(&SDL_ShowWindow),reinterpret_cast<char*>(&SDL_ShowWindow),show);if(d.failed()||renderBound.failed()||logBound.failed())std::abort();
 typedef bool(*F)(CGame*,bool);F f=ours?setupNew:setupOld;if(autotest::beginInvocation(out,f)){bool result=f(game,c.mode>=2&&c.mode!=5);out.callCompleted=1;if(ours&&c.control)result=!result;num(result);}
 num(game->m_root!=NULL);num(game->m_renderWindow==window);num(game->m_width);num(game->m_height);num(game->m_windowHandle==reinterpret_cast<void*>(static_cast<unsigned long>(SDL_GetWindowID(sdl))));num(game->m_masterResourceManager!=NULL);num(game->m_soundManager!=NULL);if(game->m_viewport){num(game->m_viewport->getClearEveryFrame());num(game->m_viewport->getClearBuffers());}if(game->m_masterResourceManager){ParticleUniverse::ParticleSystemManager*pu=game->m_masterResourceManager->m_pParticleSystemManager;real(pu->m_particleFalloff);num(pu->m_maxParticles);num(pu->m_availableParticles.size());}if(game->m_soundManager)num(game->m_soundManager->m_bUnknown6A9);
 d.restore();if(window){window->removeAllViewports();delete window;}if(offscreen){offscreen->removeAllViewports();delete offscreen;}game->m_sdlWindow=NULL;game->m_viewport=NULL;game->m_renderWindow=NULL;SDL_DestroyWindow(sdl);SDL_VideoQuit();
 // The constructor and target-owned graph remain alive until this isolated
 // child exits. Their lifecycle is independently covered by the bootstrap.
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){debugHost=host;if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;char path[]="/tmp/otl-setup-cases-XXXXXX";if(!mkdtemp(path))return 2;base=std::string(path)+"/";local=std::wstring(base.begin(),base.end());const char*dirs[]={".runicgames",".runicgames/Torchlight","appdata","данные","ok","ok/lib64","bad","bad/lib64"};for(unsigned i=0;i<8;++i)if(mkdir((base+dirs[i]).c_str(),0700))return 3;FILE*file=std::fopen((base+"ok/lib64/plugins_opengl.cfg").c_str(),"wb");if(!file)return 4;std::fputs("PluginFolder=.\n",file);std::fclose(file);file=std::fopen((base+"bad/lib64/plugins_opengl.cfg").c_str(),"wb");if(!file)return 5;std::fputs("PluginFolder=.\nPlugin=otl_comparison_missing_plugin\n",file);std::fclose(file);
 int failures=0;autotest::Coverage cov("game_setup_runtime",0x566c80);for(unsigned mode=0;mode<8;++mode)for(unsigned profile=0;profile<8;++profile){if(mode!=0&&mode!=3){bool wanted=(mode==1||mode==4)?(profile==0||profile==1||profile==6||profile==7):(profile==0||profile==1||profile==4||profile==5);if(!wanted)continue;}Case c={mode,profile,0};autotest::Outcome a,b;autotest::runChild(before,&c,a,1500,10000);autotest::runChild(after,&c,b,1500,10000);int pair=cov.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    setup mode%u profile%u status%d/%d issues%u/%u bytes%lu/%lu\n",mode,profile,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);if(a.capture.length==b.capture.length)for(unsigned i=0;i<a.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    setup first difference byte%u %u/%u\n",i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);break;}cov.report(host);return failures;}}cov.report(host);Case c={3,3,1};autotest::Outcome a,b;autotest::runChild(before,&c,a,1500,10000);autotest::runChild(after,&c,b,1500,10000);bool caught=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    setup negative detected%u\n",unsigned(caught));return failures;}
}
TL_TEST(game_setup_runtime){return systems_fixture::isolated(worker,host);}

#include "tests/NativeGameServices.h"
namespace { int dirtyParentWorker(const tlhybrid_host* h){
    new nativegame::Services; // real owners live until private worker exit
    return worker(h);
} }
TL_TEST(game_setup_runtime_dirty_parent){return systems_fixture::isolated(dirtyParentWorker,host);}
