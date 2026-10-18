#include <OgreRenderWindow.h>
#include <OgreLogManager.h>
#include "SystemsNativeMaster.h"
#include "SystemsNativeGame.h"
#define private public
#include "GameClient.h"
#undef private
#include "CameraControl.h"
#include "SoundManager.h"
TL_ORIGINAL(bool,endOriginal,(CGame*,const Ogre::FrameEvent&),"_ZN5CGame10frameEndedERKN4Ogre10FrameEventE")
extern "C" bool endCandidate(CGame*,const Ogre::FrameEvent&) __asm__("_ZN5CGame10frameEndedERKN4Ogre10FrameEventE");
TL_FUNCTION(endAspect,"_ZN14CCameraControl14setAspectRatioE8ECAMERASff")
TL_FUNCTION(endScreen,"_ZN11CGameClient16updateScreenInfoEPvii")
TL_FUNCTION(endRescale,"_ZN11CGameClient9rescaleUIEv")
TL_FUNCTION(endLoading,"_ZN7CGameUI17setLoadingVisibleEb")
TL_FUNCTION(endLevels,"_ZN13CSoundManager17updateAudioLevelsEffbb")
TL_FUNCTION(endUpdateSound,"_ZN13CSoundManager6updateEPN4Ogre9SceneNodeERKNS0_7Vector3Ef")
extern "C" void endLog(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool) __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
struct Case{unsigned mode,sound;};const Case*current;autotest::Capture*cap;
void word(unsigned x){cap->add(&x,sizeof(x));}void real(float x){cap->add(&x,sizeof(x));}
class Window:public Ogre::RenderWindow{public:Window(){mWidth=800;mHeight=600;}void create(const Ogre::String&,unsigned,unsigned,bool,const Ogre::NameValuePairList*){}void destroy(){}void resize(unsigned w,unsigned h){word(10);word(w);word(h);mWidth=w;mHeight=h;}void reposition(int,int){}void windowMovedOrResized(){word(11);}bool isClosed()const{return false;}void copyContentsToMemory(const Ogre::PixelBox&,Ogre::RenderTarget::FrameBuffer){}bool requiresTextureFlipping()const{return false;}};
void aspect(CCameraControl*,ECAMERAS n,float w,float h){word(1);word(n);real(w);real(h);}void screen(CGameClient*,void*w,int x,int y){word(2);word(w==reinterpret_cast<void*>(0x123));word(x);word(y);}void rescale(CGameClient*){word(3);}void loading(CGameUI*,bool b){word(4);word(b);}void levels(CSoundManager*,float s,float m,bool sm,bool mm){word(5);real(s);real(m);word(sm);word(mm);}void updateSound(CSoundManager*,Ogre::SceneNode*n,const Ogre::Vector3&p,float elapsed){word(6);word(n!=NULL);real(p.x);real(p.y);real(p.z);real(elapsed);}
void log(Ogre::LogManager*,const std::string&s,Ogre::LogMessageLevel level,bool mask){word(7);cap->addText(s);word(level);word(mask);}
void size(SDL_Window*w,int*x,int*y){word(8);word(w==reinterpret_cast<SDL_Window*>(0x234));*x=current->mode==1?900:current->mode==2?511:800;*y=current->mode==1?650:current->mode==3?383:600;}
void grab(SDL_Window*w,SDL_bool b){word(9);word(w==reinterpret_cast<SDL_Window*>(0x234));word(b);}int fullscreen(SDL_Window*w,Uint32 flag){word(12);word(w==reinterpret_cast<SDL_Window*>(0x234));word(flag);return 0;}void position(SDL_Window*w,int x,int y){word(13);word(w==reinterpret_cast<SDL_Window*>(0x234));word(x);word(y);}void setSize(SDL_Window*w,int x,int y){word(14);word(w==reinterpret_cast<SDL_Window*>(0x234));word(x);word(y);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);current=&c;cap=&out;SystemsNativeMaster master;SystemsNativeGame native(master.root,master.settings);CGame*g=native.game;CSettings*s=native.settings;g->m_masterResourceManager=master.master;master.master->m_loadingResources=c.mode==8;
 Window window;g->m_renderWindow=&window;g->m_sdlWindow=reinterpret_cast<SDL_Window*>(0x234);g->m_windowHandle=reinterpret_cast<void*>(0x123);g->m_sceneManager=master.root->createSceneManager(Ogre::ST_GENERIC,"end-native");
 union C{long double a;unsigned char data[sizeof(CGameClient)];}cs;std::memset(&cs,0,sizeof(cs));CGameClient*client=reinterpret_cast<CGameClient*>(cs.data);client->m_restartRequested=c.mode==9;client->m_audioListenerPosition=Ogre::Vector3(1.25f,-7.5f,3);client->m_pGameUI=c.mode==7?reinterpret_cast<CGameUI*>(0x345):NULL;g->m_gameClient=client;
 CCameraControl*control=new CCameraControl(NULL,NULL,NULL,NULL,NULL);g->m_cameraControl=c.sound?control:NULL;CSoundManager*sound=new CSoundManager(false);g->m_soundManager=c.sound?sound:NULL;
 s->SetInt(KSETTINGS_RES_WIDTH,c.mode==4?1600:800);s->SetInt(KSETTINGS_RES_HEIGHT,c.mode==4?900:600);s->SetInt(KSETTINGS_FULLSCREEN,c.mode==5?1:0);s->SetFloat(KSETTINGS_XRATIO,-1);s->SetFloat(KSETTINGS_YRATIO,-2);s->SetFloat(KSETTINGS_F_SOUNDVOLUME,.25f);s->SetFloat(KSETTINGS_F_MUSICVOLUME,.75f);s->SetInt(KSETTINGS_SOUNDMUTE,c.mode&1);s->SetInt(KSETTINGS_MUSICMUTE,c.mode&2);
 *reinterpret_cast<int*>(0x14263c0)=c.mode==10?0:800;*reinterpret_cast<int*>(0x14263c4)=600;*reinterpret_cast<int*>(0x14263c8)=c.mode==6?1:0;*reinterpret_cast<int*>(0x14263cc)=1024;*reinterpret_cast<int*>(0x14263d0)=768;*reinterpret_cast<bool*>(0x14263d4)=c.mode==7;*reinterpret_cast<int*>(0x14263d8)=c.mode==7?1280:0;*reinterpret_cast<int*>(0x14263dc)=c.mode==7?720:0;*reinterpret_cast<bool*>(0x14263e0)=false;
 detour::Set d;TL_REDIRECT(d,endAspect,&aspect);TL_REDIRECT(d,endScreen,&screen);TL_REDIRECT(d,endRescale,&rescale);TL_REDIRECT(d,endLoading,&loading);TL_REDIRECT(d,endLevels,&levels);TL_REDIRECT(d,endUpdateSound,&updateSound);d.redirect(reinterpret_cast<char*>(&endLog),reinterpret_cast<char*>(&endLog),&log);d.redirect(reinterpret_cast<char*>(&SDL_GetWindowSize),reinterpret_cast<char*>(&SDL_GetWindowSize),&size);d.redirect(reinterpret_cast<char*>(&SDL_SetWindowGrab),reinterpret_cast<char*>(&SDL_SetWindowGrab),&grab);d.redirect(reinterpret_cast<char*>(&SDL_SetWindowFullscreen),reinterpret_cast<char*>(&SDL_SetWindowFullscreen),&fullscreen);d.redirect(reinterpret_cast<char*>(&SDL_SetWindowPosition),reinterpret_cast<char*>(&SDL_SetWindowPosition),&position);d.redirect(reinterpret_cast<char*>(&SDL_SetWindowSize),reinterpret_cast<char*>(&SDL_SetWindowSize),&setSize);if(d.failed())_exit(64);
 Ogre::FrameEvent event={.01f,c.sound?.25f:0};bool(*fn)(CGame*,const Ogre::FrameEvent&)=ours?endCandidate:endOriginal;if(autotest::beginInvocation(out,fn)){bool r=fn(g,event);out.callCompleted=1;word(r);}word(g->m_width);word(g->m_height);out.add(reinterpret_cast<void*>(0x14263c0),33);word(s->GetInt(KSETTINGS_RES_WIDTH));word(s->GetInt(KSETTINGS_RES_HEIGHT));word(s->GetInt(KSETTINGS_FULLSCREEN));real(s->GetFloat(KSETTINGS_XRATIO));real(s->GetFloat(KSETTINGS_YRATIO));word(master.master->m_loadingResources);
 d.restore();g->m_soundManager=NULL;delete sound;g->m_cameraControl=NULL;delete control;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_game_frame_ended){int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_game_frame_ended",reinterpret_cast<uintptr_t>(&endOriginal));for(unsigned mode=0;mode<11;++mode)for(unsigned sound=0;sound<2;++sound){Case c={mode,sound};autotest::Outcome a,b;autotest::runChild(original,&c,a,1500,10000);autotest::runChild(candidate,&c,b,1500,10000);++cases;bool ok=coverage.observe(host,a,b)==0;TL_CHECK(failures,ok);}coverage.report(host);return failures+(coverage.completed!=cases);}
