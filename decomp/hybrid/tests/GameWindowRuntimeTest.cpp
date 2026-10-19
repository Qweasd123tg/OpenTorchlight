#include <cstring>
#include <cstdlib>
#include <dlfcn.h>
#include <sys/mman.h>
#include <execinfo.h>
#include <ucontext.h>
#include <fcntl.h>
#include "tests/SystemsNativeGame.h"
#include "GameCpuRenderer.h"
#include "CharacterLibraryBoundary.h"
#include "Utilities.h"
extern "C" {
SDL_Window* SDL_CreateWindow(const char*,int,int,int,int,Uint32);
void SDL_DestroyWindow(SDL_Window*);
SDL_Surface* SDL_CreateRGBSurfaceFrom(void*,int,int,int,int,Uint32,Uint32,Uint32,Uint32);
void SDL_SetWindowIcon(SDL_Window*,SDL_Surface*);
}

#include <OgreDefaultHardwareBufferManager.h>
#include <OgreMaterialManager.h>
TL_ORIGINAL(Ogre::RenderWindow*,windowOld,(CGame*,bool),"_ZN5CGame12createWindowEb")
extern "C" Ogre::RenderWindow*windowNew(CGame*,bool) __asm__("_ZN5CGame12createWindowEb");
TL_FUNCTION(windowDefaults,"_ZN9CSettings13assignDefaultEiiSs")
TL_FUNCTION(windowCPU,"_ZN9UTILITIES17getProcessorSpeedEv")
TL_FUNCTION(windowRAM,"_ZN9UTILITIES15getAvailableRAMEv")
TL_FUNCTION(windowDesktop,"_ZN10LinuxUtils20GetDesktopResolutionERiS0_")
TL_FUNCTION(windowHandle,"_ZN10LinuxUtils18GetSDLWindowHandleEP10SDL_Window")
TL_FUNCTION(windowMessage,"_Z11MessageBoxAPvPKcS1_i")
TL_FUNCTION(windowCaps,"_ZN5CGame17checkCapabilitiesEPN4Ogre12RenderSystemE")
TL_FUNCTION(windowDecode,"_ZN7lodepng6decodeERSt6vectorIhSaIhEERjS4_RKSs16LodePNGColorTypej")
namespace {
struct Case {unsigned seed,control;};const Case*current;autotest::Capture*out;bool armed,oursSide;unsigned seed,mode,variant;CGame*game;Ogre::GameCpuRenderer*renderer;SDL_Window*sdl;unsigned calls;SDL_Surface*actualSurface;unsigned char actualPixels[256];bool returnedSurface;int desktopWidth,desktopHeight;
void num(unsigned n){if(armed)out->add(&n,4);}void text(const std::string&s){num(s.size());if(armed)out->add(s.data(),s.size());}void fp(float n){if(armed)out->add(&n,4);}
void fault(int sig,siginfo_t*info,void*ctx){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/game-window-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);if(fd>=0){char b[200];ucontext_t*u=static_cast<ucontext_t*>(ctx);int n=snprintf(b,sizeof(b),"signal%d side%d seed%u rip%llx address%p\n",sig,oursSide,seed,(unsigned long long)u->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,b,n);void*s[40];backtrace_symbols_fd(s,backtrace(s,40),fd);close(fd);}raise(sig);}
class Window:public Ogre::RenderWindow {
public:
 Window(){mWidth=19;mHeight=23;mActive=false;mAutoUpdate=false;}
 void create(const Ogre::String&,unsigned,unsigned,bool,const Ogre::NameValuePairList*){std::abort();}
 void destroy(){}void resize(unsigned w,unsigned h){mWidth=w;mHeight=h;}void reposition(int,int){std::abort();}bool isClosed()const{return false;}
 void setActive(bool b){num(17);num(b);Ogre::RenderTarget::setActive(b);}
 void setAutoUpdated(bool b){num(19);num(b);Ogre::RenderTarget::setAutoUpdated(b);}
 void getCustomAttribute(const std::string&name,void*p){num(23);text(name);*static_cast<unsigned long*>(p)=0x54321;}
 void copyContentsToMemory(const Ogre::PixelBox&,Ogre::RenderTarget::FrameBuffer){std::abort();}bool requiresTextureFlipping()const{return false;}
};Window*window;
Ogre::RenderWindow*initialise(Ogre::Root*p,bool autoWindow,const std::string&title,const std::string&caps){num(1);num(p==game->m_root);num(autoWindow);text(title);text(caps);num(p->getRenderSystem()==renderer);return NULL;}
Ogre::RenderWindow*create(Ogre::Root*p,const std::string&name,unsigned w,unsigned h,bool fullscreen,const Ogre::NameValuePairList*params){num(2);num(p==game->m_root);text(name);num(w);num(h);num(fullscreen);num(params!=NULL);if(params){num(params->size());for(Ogre::NameValuePairList::const_iterator i=params->begin();i!=params->end();++i){text(i->first);text(i->second);}}window->resize(w,h);return window;}
void defaults(CSettings*s,int ram,int cpu,std::string device){num(3);num(s==game->m_settings);num(ram);num(cpu);text(device);if(variant&8){s->SetInt(KSETTINGS_RES_WIDTH,1024);s->SetInt(KSETTINGS_RES_HEIGHT,768);}}
int cpu(){num(5);return 2000+variant*111;}int ram(){num(7);return variant%3?4096:512;}
void desktop(int&w,int&h){num(11);w=desktopWidth;h=desktopHeight;num(w);num(h);}
void*handle(SDL_Window*p){num(13);num(p==sdl);return reinterpret_cast<void*>(0x12345678);}
int message(void*p,const char*t,const char*title,int flags){num(29);num(p==NULL);text(t);text(title);num(flags);return 1;}
void caps(CGame*p,Ogre::RenderSystem*r){num(31);num(p==game);num(r==renderer);++calls;}
unsigned decode(std::vector<unsigned char>&pixels,unsigned&w,unsigned&h,const std::string&path,int type,unsigned depth){num(37);text(path);num(type);num(depth);if(variant%4==0)return 78;w=variant%3+1;h=variant%2+1;pixels.resize(w*h*4);for(unsigned i=0;i<pixels.size();++i)pixels[i]=i+variant;return 0;}
SDL_Surface*surface(void*p,int w,int h,int depth,int pitch,Uint32 r,Uint32 g,Uint32 b,Uint32 a){num(41);num(w);num(h);num(depth);num(pitch);num(r);num(g);num(b);num(a);if(armed)out->add(p,w*h*4);if(variant%4==1)return NULL;returnedSurface=true;return actualSurface;}
SDL_Window*createSDL(const char*name,int x,int y,int w,int h,Uint32 flags){num(43);text(name);num(x);num(y);num(w);num(h);num(flags);return sdl;}
void icon(SDL_Window*p,SDL_Surface*s){num(47);num(p==sdl);num(s==actualSurface?1:s==NULL?0:99);}
void grab(SDL_Window*p,SDL_bool b){num(53);num(p==sdl);num(b);}
void log(Ogre::LogManager*,const std::string&s,Ogre::LogMessageLevel level,bool mask){num(59);text(s);num(level);num(mask);}
const char*error(){num(61);return "comparison surface error";}
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);current=&c;out=&capture;seed=c.seed;mode=seed/32;variant=seed%32;oursSide=ours;armed=false;calls=0;returnedSurface=false;struct sigaction sa;std::memset(&sa,0,sizeof(sa));sa.sa_sigaction=&fault;sa.sa_flags=SA_SIGINFO|SA_RESETHAND;sigaction(SIGSEGV,&sa,NULL);sigaction(SIGABRT,&sa,NULL);
 SystemsNativeGame native;game=native.game;Ogre::GameCpuRenderer cpuRenderer;renderer=&cpuRenderer;game->m_width=71;game->m_height=73;Window actualWindow;window=&actualWindow;
 if(SDL_VideoInit("dummy"))std::abort();sdl=SDL_CreateWindow("comparison native SDL owner",0,0,32,24,0);if(!sdl)std::abort();for(unsigned i=0;i<256;++i)actualPixels[i]=i+variant;actualSurface=SDL_CreateRGBSurfaceFrom(actualPixels,variant%3+1,variant%2+1,32,(variant%3+1)*4,0xff,0xff00,0xff0000,0xff000000);if(!actualSurface)std::abort();
 if(mode!=2)native.root->addRenderSystem(renderer);game->m_root=mode==0?NULL:native.root;game->m_windowHandle=mode==1?reinterpret_cast<void*>(17):NULL;
 const int widths[]={640,1024,1600,1920,0,-1,2147483647,(-2147483647-1)};const int heights[]={360,768,900,1080};desktopWidth=variant&8?1280:1600;desktopHeight=variant&8?720:900;
 native.settings->SetInt(KSETTINGS_OPENGL,variant&1);native.settings->SetInt(KSETTINGS_RES_WIDTH,widths[variant%8]);native.settings->SetInt(KSETTINGS_RES_HEIGHT,heights[variant/8]);native.settings->SetInt(KSETTINGS_FULLSCREEN,mode==5||mode==6);native.settings->SetInt(KSETTINGS_VSYNCH,variant&2);native.settings->SetInt(KSETTINGS_FSAA,variant%3==0?0:variant%3==1?4:-1);native.settings->SetFloat(KSETTINGS_XRATIO,-3);native.settings->SetFloat(KSETTINGS_YRATIO,-5);
 *reinterpret_cast<bool*>(0x1426408)=(variant&4)!=0;*reinterpret_cast<bool*>(0x14210a4)=mode==6;cpuRenderer.options["Rendering Device"].currentValue="old-device";cpuRenderer.options["Rendering Device"].possibleValues[0]=variant&2?"CPU Adapter":"设备适配器";
 CharacterLibraryBoundary initBoundary(characterLibraryEntry("libOgreMain-1.6.5.so","_ZN4Ogre4Root10initialiseEbRKSsS2_"),&initialise),createBoundary(characterLibraryEntry("libOgreMain-1.6.5.so","_ZN4Ogre4Root18createRenderWindowERKSsjjbPKSt3mapISsSsSt4lessISsESaISt4pairIS1_SsEEE"),&create),logBoundary(characterLibraryEntry("libOgreMain-1.6.5.so","_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb"),&log),surfaceBoundary(characterLibraryEntry("libSDL2-2.0.so.0","SDL_CreateRGBSurfaceFrom"),&surface),sdlBoundary(characterLibraryEntry("libSDL2-2.0.so.0","SDL_CreateWindow"),&createSDL),iconBoundary(characterLibraryEntry("libSDL2-2.0.so.0","SDL_SetWindowIcon"),&icon),grabBoundary(characterLibraryEntry("libSDL2-2.0.so.0","SDL_SetWindowGrab"),&grab),errorBoundary(characterLibraryEntry("libSDL2-2.0.so.0","SDL_GetError"),&error);
 detour::Set patches;TL_REDIRECT(patches,windowDefaults,&defaults);TL_REDIRECT(patches,windowCPU,&cpu);TL_REDIRECT(patches,windowRAM,&ram);TL_REDIRECT(patches,windowDesktop,&desktop);TL_REDIRECT(patches,windowHandle,&handle);TL_REDIRECT(patches,windowMessage,&message);TL_REDIRECT(patches,windowCaps,&caps);TL_REDIRECT(patches,windowDecode,&decode);
 if(patches.failed()||initBoundary.failed()||createBoundary.failed()||logBoundary.failed()||surfaceBoundary.failed()||sdlBoundary.failed()||iconBoundary.failed()||grabBoundary.failed()||errorBoundary.failed())_exit(43);
 armed=true;typedef Ogre::RenderWindow*(*F)(CGame*,bool);F f=ours?windowNew:windowOld;if(!autotest::beginInvocation(capture,f))return;Ogre::RenderWindow*r=f(game,mode!=3);capture.callCompleted=1;if(ours&&c.control)++game->m_width;
 num(*reinterpret_cast<CGame**>(0x1426410)==game);num(r==NULL?0:r==window?1:99);num(calls);num(game->m_width);num(game->m_height);num(game->m_sdlWindow==sdl);num(native.settings->GetInt(KSETTINGS_RES_WIDTH));num(native.settings->GetInt(KSETTINGS_RES_HEIGHT));fp(native.settings->GetFloat(KSETTINGS_XRATIO));fp(native.settings->GetFloat(KSETTINGS_YRATIO));text(cpuRenderer.options["Rendering Device"].currentValue);num(actualWindow.isActive());num(actualWindow.isAutoUpdated());armed=false;patches.restore();game->m_root=native.root;native.root->setRenderSystem(NULL);game->m_sdlWindow=NULL;SDL_DestroyWindow(sdl);if(!returnedSurface)SDL_FreeSurface(actualSurface);
 if(mode==3&&Ogre::HardwareBufferManager::getSingletonPtr())delete Ogre::HardwareBufferManager::getSingletonPtr();
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(game_window_runtime){int failures=0;autotest::Coverage coverage("game_window_runtime",0x567ce0);for(unsigned i=0;i<256;++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    window seed%u status%d/%d bytes%lu/%lu\n",i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j+3<a.capture.length&&j+3<b.capture.length;j+=4){unsigned x,y;memcpy(&x,a.capture.data+j,4);memcpy(&y,b.capture.data+j,4);if(x!=y){host->log("    word%u %08x/%08x\n",j/4,x,y);if(j>2048)break;}}coverage.report(host);return failures;}}coverage.report(host);Case c={133,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    window negative detected%u\n",unsigned(caught));return failures;}
