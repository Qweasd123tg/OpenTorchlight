#include <vector>
#include <OgreLogManager.h>
#include <OgreRenderWindow.h>
#include <CEGUISystem.h>
#include "SystemsNativeGame.h"
#include "CameraControl.h"
#include "CmdLineParser.h"
#include "Splash.h"
TL_ORIGINAL(bool,configOriginal,(CGame*,bool),"_ZN5CGame9configureEb")
extern "C" bool configCandidate(CGame*,bool) __asm__("_ZN5CGame9configureEb");
TL_ORIGINAL(void,aspectOriginal,(CGame*,float,float),"_ZN5CGame17updateAspectRatioEff")
extern "C" void aspectCandidate(CGame*,float,float) __asm__("_ZN5CGame17updateAspectRatioEff");
TL_ORIGINAL(void,viewportsOriginal,(CGame*),"_ZN5CGame15createViewportsEv")
extern "C" void viewportsCandidate(CGame*) __asm__("_ZN5CGame15createViewportsEv");
TL_ORIGINAL(long,beginOriginal,(CGame*,void*),"_ZN5CGame5beginEPv")
extern "C" long beginCandidate(CGame*,void*) __asm__("_ZN5CGame5beginEPv");
TL_FUNCTION(basicCreate,"_ZN5CGame12createWindowEb")
TL_FUNCTION(basicCameraAspect,"_ZN14CCameraControl14setAspectRatioE8ECAMERASff")
TL_FUNCTION(basicScreen,"_ZN11CGameClient16updateScreenInfoEPvii")
TL_FUNCTION(basicSetup,"_ZN5CGame5setupEb")
TL_FUNCTION(basicConvert,"_ZN5CGame21convertAssetsToBinaryEv")
TL_FUNCTION(basicCleanup,"_ZN5CGame18cleanUpGameObjectsEv")
TL_FUNCTION(basicUI,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(basicHide,"_ZN7CSplash4HideEv")
TL_FUNCTION(basicCenter,"_ZN7CSplash19findCenterForWindowEiiRiS0_")
TL_FUNCTION(basicEvent,"_ZN15SDLEventHandler12ProcessEventERK9SDL_Event")
extern "C" void basicLog(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool) __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
extern "C" void basicClearTimes(Ogre::Root*) __asm__("_ZN4Ogre4Root15clearEventTimesEv");
extern "C" bool basicRender(Ogre::Root*) __asm__("_ZN4Ogre4Root14renderOneFrameEv");
extern "C" CEGUI::System* basicSystem() __asm__("_ZN5CEGUI6System12getSingletonEv");
extern "C" bool basicMousePos(CEGUI::System*,float,float) __asm__("_ZN5CEGUI6System19injectMousePositionEff");
extern "C" bool basicMouseMove(CEGUI::System*,float,float) __asm__("_ZN5CEGUI6System15injectMouseMoveEff");
namespace {
struct Case{unsigned target,mode,size;};const Case*current;autotest::Capture*cap;unsigned createCalls,pollCalls,frameCalls;Ogre::RenderWindow*returned;
void word(unsigned x){cap->add(&x,sizeof(x));}void real(float x){cap->add(&x,sizeof(x));}
class Window:public Ogre::RenderWindow{public:Window(unsigned w,unsigned h){mWidth=w;mHeight=h;}void create(const Ogre::String&,unsigned,unsigned,bool,const Ogre::NameValuePairList*){}void destroy(){}void resize(unsigned w,unsigned h){word(10);word(w);word(h);mWidth=w;mHeight=h;}void reposition(int x,int y){word(11);word(x);word(y);}void windowMovedOrResized(){word(12);}void setVisible(bool b){word(13);word(b);}bool isClosed()const{return false;}void copyContentsToMemory(const Ogre::PixelBox&,Ogre::RenderTarget::FrameBuffer){}bool requiresTextureFlipping()const{return false;}};
Ogre::RenderWindow*create(CGame*g,bool editor){word(1);word(editor);word(g->m_settings->GetInt(KSETTINGS_RES_WIDTH));word(g->m_settings->GetInt(KSETTINGS_RES_HEIGHT));word(g->m_settings->GetInt(KSETTINGS_FULLSCREEN));word(g->m_settings->GetInt(KSETTINGS_FSAA));++createCalls;return current->mode==3||((current->mode==1||current->mode==2)&&createCalls==1)?NULL:returned;}
void aspect(CCameraControl*,ECAMERAS which,float w,float h){word(2);word(which);real(w);real(h);}
void screen(CGameClient*,void*w,int x,int y){word(3);word(w==reinterpret_cast<void*>(0x123));word(x);word(y);}
void log(Ogre::LogManager*,const std::string&s,Ogre::LogMessageLevel level,bool mask){word(4);cap->addText(s);word(level);word(mask);}
bool setup(CGame*,bool window){word(5);word(window);return current->mode!=0;}
void convert(CGame*){word(6);}void cleanup(CGame*){word(7);}
void*ui(){return current->mode==5?reinterpret_cast<void*>(0x456):NULL;}
void hide(CSplash*){word(8);}void center(CSplash*,int w,int h,int&x,int&y){word(9);word(w);word(h);x=23;y=47;}
void event(SDLEventHandler*,const SDL_Event&e){word(14);word(e.type);if(e.type==0x200)word(e.window.event);}
void clearTimes(Ogre::Root*){word(15);}bool render(Ogre::Root*){word(16);return ++frameCalls<2;}
int poll(SDL_Event*event){std::memset(event,0,sizeof(*event));unsigned i=pollCalls++;if(current->mode==6&&i==0){event->type=0x100;return 1;}if(i<3){event->type=0x200;event->window.event=i==0?4:i==1?14:1;event->window.data1=-17;event->window.data2=35;return 1;}if(i==3||i>=5)return 0;event->type=0x300;return 1;}
int push(SDL_Event*e){word(17);word(e->type);return 1;}
CEGUI::System*system(){return reinterpret_cast<CEGUI::System*>(0x789);}
bool mousePos(CEGUI::System*s,float x,float y){word(18);word(s==reinterpret_cast<CEGUI::System*>(0x789));real(x);real(y);return true;}
bool mouseMove(CEGUI::System*s,float x,float y){word(19);word(s==reinterpret_cast<CEGUI::System*>(0x789));real(x);real(y);return true;}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);current=&c;cap=&out;SystemsNativeGame native;CGame*g=native.game;const unsigned widths[]={800,1025,1920};const unsigned heights[]={600,769,1080};Window window(widths[c.size],heights[c.size]);returned=&window;g->m_root=native.root;g->m_renderWindow=&window;g->m_width=widths[c.size];g->m_height=heights[c.size];g->m_windowHandle=reinterpret_cast<void*>(0x123);
 CCameraControl*control=new CCameraControl(NULL,NULL,NULL,NULL,NULL);g->m_cameraControl=(c.mode&1)?NULL:control;g->m_gameClient=(c.mode&2)?reinterpret_cast<CGameClient*>(0x987):NULL;
 native.settings->SetInt(KSETTINGS_RES_WIDTH,1600);native.settings->SetInt(KSETTINGS_RES_HEIGHT,900);native.settings->SetInt(KSETTINGS_FULLSCREEN,1);native.settings->SetInt(KSETTINGS_FSAA,4);
 if(c.target==0&&(c.mode==2||c.mode==4))native.settings->m_pCmdLineParser->m_params[L"COMPRESS"].push_back(L"assets");if(c.target==3&&c.mode==1)native.settings->m_pCmdLineParser->m_params[L"COMPRESS"].push_back(L"assets");if(c.target==3&&c.mode==2)native.settings->m_pCmdLineParser->m_params[L"NOWINDOW"].push_back(L"1");
 *reinterpret_cast<bool*>(0x1426408)=true;*reinterpret_cast<bool*>(0x14210a4)=true;*reinterpret_cast<int*>(0x14263d8)=-1;*reinterpret_cast<int*>(0x14263dc)=-2;createCalls=pollCalls=frameCalls=0;
 detour::Set d;TL_REDIRECT(d,basicCreate,&create);TL_REDIRECT(d,basicCameraAspect,&aspect);TL_REDIRECT(d,basicScreen,&screen);TL_REDIRECT(d,basicSetup,&setup);TL_REDIRECT(d,basicConvert,&convert);TL_REDIRECT(d,basicCleanup,&cleanup);TL_REDIRECT(d,basicUI,&ui);TL_REDIRECT(d,basicHide,&hide);TL_REDIRECT(d,basicCenter,&center);TL_REDIRECT(d,basicEvent,&event);
 d.redirect(reinterpret_cast<char*>(&basicLog),reinterpret_cast<char*>(&basicLog),&log);d.redirect(reinterpret_cast<char*>(&basicClearTimes),reinterpret_cast<char*>(&basicClearTimes),&clearTimes);d.redirect(reinterpret_cast<char*>(&basicRender),reinterpret_cast<char*>(&basicRender),&render);d.redirect(reinterpret_cast<char*>(&SDL_PollEvent),reinterpret_cast<char*>(&SDL_PollEvent),&poll);d.redirect(reinterpret_cast<char*>(&SDL_PushEvent),reinterpret_cast<char*>(&SDL_PushEvent),&push);d.redirect(reinterpret_cast<char*>(&basicSystem),reinterpret_cast<char*>(&basicSystem),&system);d.redirect(reinterpret_cast<char*>(&basicMousePos),reinterpret_cast<char*>(&basicMousePos),&mousePos);d.redirect(reinterpret_cast<char*>(&basicMouseMove),reinterpret_cast<char*>(&basicMouseMove),&mouseMove);if(d.failed())_exit(64);
 if(c.target==0){bool(*fn)(CGame*,bool)=ours?configCandidate:configOriginal;if(autotest::beginInvocation(out,fn)){bool r=fn(g,c.size&1);out.callCompleted=1;word(r);}word(g->m_renderWindow==returned);word(native.settings->GetInt(KSETTINGS_RES_WIDTH));word(native.settings->GetInt(KSETTINGS_RES_HEIGHT));word(native.settings->GetInt(KSETTINGS_FULLSCREEN));word(native.settings->GetInt(KSETTINGS_FSAA));word(*reinterpret_cast<bool*>(0x1426408));out.add(reinterpret_cast<void*>(0x14263d8),8);}
 else if(c.target==1){void(*fn)(CGame*,float,float)=ours?aspectCandidate:aspectOriginal;if(autotest::beginInvocation(out,fn)){fn(g,widths[c.size],heights[c.size]);out.callCompleted=1;}}
 else if(c.target==2){if(c.mode&2)g->m_renderWindow=NULL;void(*fn)(CGame*)=ours?viewportsCandidate:viewportsOriginal;if(autotest::beginInvocation(out,fn)){fn(g);out.callCompleted=1;}word(window.getNumViewports());for(unsigned i=0;i<window.getNumViewports();++i){Ogre::Viewport*v=window.getViewport(i);word(v->getZOrder());word(v->getActualWidth());word(v->getActualHeight());word(v->getClearEveryFrame());word(v->getClearBuffers());out.add(&v->getBackgroundColour(),sizeof(Ogre::ColourValue));}}
 else{g->m_cameraControl=NULL;long(*fn)(CGame*,void*)=ours?beginCandidate:beginOriginal;if(autotest::beginInvocation(out,fn)){long r=fn(g,reinterpret_cast<void*>(0x852));out.callCompleted=1;out.add(&r,sizeof(r));}word(g->m_editorWindow==reinterpret_cast<void*>(0x852));}
 d.restore();g->m_cameraControl=NULL;delete control;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned target){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;const char*labels[]={"complete_game_configure","complete_game_aspect","complete_game_viewports","complete_game_begin"};uintptr_t addresses[]={reinterpret_cast<uintptr_t>(&configOriginal),reinterpret_cast<uintptr_t>(&aspectOriginal),reinterpret_cast<uintptr_t>(&viewportsOriginal),reinterpret_cast<uintptr_t>(&beginOriginal)};autotest::Coverage coverage(labels[target],addresses[target]);for(unsigned mode=0;mode<(target==3?7u:target==0?5u:4u);++mode)for(unsigned size=0;size<3;++size){Case c={target,mode,size};bool ok=autotest::compareCase(original,candidate,&c,stats,host,labels[target],cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
}
TL_TEST(complete_game_configure){return run(host,0);}TL_TEST(complete_game_aspect){return run(host,1);}TL_TEST(complete_game_viewports){return run(host,2);}TL_TEST(complete_game_begin){return run(host,3);}
