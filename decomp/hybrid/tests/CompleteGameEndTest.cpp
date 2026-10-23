#include <OgreRenderWindow.h>
#include <OgreLogManager.h>
#include "tests/SystemsNativeGame.h"
#include "tests/NativeMenuClient.h"
#include "tests/GameClientUiOwner.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/CharacterLibraryBoundary.h"
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
struct Case{unsigned mode,sound,negative;};const Case*current;autotest::Capture*cap;nativegame::Services*services;menugui::Client*owner;CGameUI*nativeUI;
void word(unsigned x){cap->add(&x,sizeof(x));}void real(float x){cap->add(&x,sizeof(x));}
class Window:public Ogre::RenderWindow{public:Window(){mWidth=800;mHeight=600;}void create(const Ogre::String&,unsigned,unsigned,bool,const Ogre::NameValuePairList*){}void destroy(){}void resize(unsigned w,unsigned h){word(10);word(w);word(h);mWidth=w;mHeight=h;}void reposition(int,int){}void windowMovedOrResized(){word(11);}bool isClosed()const{return false;}void copyContentsToMemory(const Ogre::PixelBox&,Ogre::RenderTarget::FrameBuffer){}bool requiresTextureFlipping()const{return false;}};
void aspect(CCameraControl*,ECAMERAS n,float w,float h){word(1);word(n);real(w);real(h);}void screen(CGameClient*,void*w,int x,int y){word(2);word(w==reinterpret_cast<void*>(0x123));word(x);word(y);}void rescale(CGameClient*){word(3);}void loading(CGameUI*,bool b){word(4);word(b);}void levels(CSoundManager*,float s,float m,bool sm,bool mm){word(5);real(s);real(m);word(sm);word(mm);}void updateSound(CSoundManager*,Ogre::SceneNode*n,const Ogre::Vector3&p,float elapsed){word(6);word(n!=NULL);real(p.x);real(p.y);real(p.z);real(elapsed);}
void log(Ogre::LogManager*,const std::string&s,Ogre::LogMessageLevel level,bool mask){word(7);cap->addText(s);word(level);word(mask);}
void size(SDL_Window*w,int*x,int*y){word(8);word(w==reinterpret_cast<SDL_Window*>(0x234));*x=current->mode==1?900:current->mode==2?511:800;*y=current->mode==1?650:current->mode==3?383:600;}
void grab(SDL_Window*w,SDL_bool b){word(9);word(w==reinterpret_cast<SDL_Window*>(0x234));word(b);}int fullscreen(SDL_Window*w,Uint32 flag){word(12);word(w==reinterpret_cast<SDL_Window*>(0x234));word(flag);return 0;}void position(SDL_Window*w,int x,int y){word(13);word(w==reinterpret_cast<SDL_Window*>(0x234));word(x);word(y);}void setSize(SDL_Window*w,int x,int y){word(14);word(w==reinterpret_cast<SDL_Window*>(0x234));word(x);word(y);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);current=&c;cap=&out;
 CGame*g=static_cast<CGame*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGame),0,0,0));CSettings*s=services->settings;
 {CharacterLibraryBoundary video(characterLibraryEntry(NULL,"SDL_VideoInit"),&systems_game::videoInit),displays(characterLibraryEntry(NULL,"SDL_GetNumVideoDisplays"),&systems_game::numDisplays),desktop(characterLibraryEntry(NULL,"SDL_GetDesktopDisplayMode"),&systems_game::desktopMode);if(video.failed()||displays.failed()||desktop.failed())std::abort();std::string empty;systemsGameCtor(g,empty,s,false);}
 TSafePointer<CGame> gameWitness;gameWitness.setObject(g);g->m_masterResourceManager=services->master;services->master->m_loadingResources=c.mode==8;
 Window window;g->m_renderWindow=&window;g->m_sdlWindow=reinterpret_cast<SDL_Window*>(0x234);g->m_windowHandle=reinterpret_cast<void*>(0x123);g->m_sceneManager=owner->scenes[0];
 CGameClient*client=owner->client;client->m_restartRequested=c.mode==9;client->m_audioListenerPosition=Ogre::Vector3(1.25f,-7.5f,3);client->m_pGameUI=c.mode==7?nativeUI:NULL;g->m_gameClient=client;
 g->m_cameraControl=c.sound?owner->camera:NULL;g->m_soundManager=c.sound?services->master->m_pSoundManager:NULL;
 s->SetInt(KSETTINGS_RES_WIDTH,c.mode==4?1600:800);s->SetInt(KSETTINGS_RES_HEIGHT,c.mode==4?900:600);s->SetInt(KSETTINGS_FULLSCREEN,c.mode==5?1:0);s->SetFloat(KSETTINGS_XRATIO,-1);s->SetFloat(KSETTINGS_YRATIO,-2);s->SetFloat(KSETTINGS_F_SOUNDVOLUME,.25f);s->SetFloat(KSETTINGS_F_MUSICVOLUME,.75f);s->SetInt(KSETTINGS_SOUNDMUTE,c.mode&1);s->SetInt(KSETTINGS_MUSICMUTE,c.mode&2);
 *reinterpret_cast<int*>(0x14263c0)=c.mode==10?0:800;*reinterpret_cast<int*>(0x14263c4)=600;*reinterpret_cast<int*>(0x14263c8)=c.mode==6?1:0;*reinterpret_cast<int*>(0x14263cc)=1024;*reinterpret_cast<int*>(0x14263d0)=768;*reinterpret_cast<bool*>(0x14263d4)=c.mode==7;*reinterpret_cast<int*>(0x14263d8)=c.mode==7?1280:0;*reinterpret_cast<int*>(0x14263dc)=c.mode==7?720:0;*reinterpret_cast<bool*>(0x14263e0)=false;
 detour::Set d;TL_REDIRECT(d,endAspect,&aspect);TL_REDIRECT(d,endScreen,&screen);TL_REDIRECT(d,endRescale,&rescale);TL_REDIRECT(d,endLoading,&loading);TL_REDIRECT(d,endLevels,&levels);TL_REDIRECT(d,endUpdateSound,&updateSound);if(d.failed())std::abort();
 CharacterLibraryBoundary logBoundary(characterLibraryEntry("libOgreMain-1.6.5.so","_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb"),&log),sizeBoundary(characterLibraryEntry(NULL,"SDL_GetWindowSize"),&size),grabBoundary(characterLibraryEntry(NULL,"SDL_SetWindowGrab"),&grab),fullscreenBoundary(characterLibraryEntry(NULL,"SDL_SetWindowFullscreen"),&fullscreen),positionBoundary(characterLibraryEntry(NULL,"SDL_SetWindowPosition"),&position),setSizeBoundary(characterLibraryEntry(NULL,"SDL_SetWindowSize"),&setSize);
 if(logBoundary.failed()||sizeBoundary.failed()||grabBoundary.failed()||fullscreenBoundary.failed()||positionBoundary.failed()||setSizeBoundary.failed())std::abort();

 Ogre::FrameEvent event={.01f,c.sound?.25f:0};bool(*fn)(CGame*,const Ogre::FrameEvent&)=ours?endCandidate:endOriginal;if(autotest::beginInvocation(out,fn)){bool r=fn(g,event);out.callCompleted=1;word(r);}if(ours&&c.negative)g->m_width^=1;word(g->m_width);word(g->m_height);out.add(reinterpret_cast<void*>(0x14263c0),33);word(s->GetInt(KSETTINGS_RES_WIDTH));word(s->GetInt(KSETTINGS_RES_HEIGHT));word(s->GetInt(KSETTINGS_FULLSCREEN));real(s->GetFloat(KSETTINGS_XRATIO));real(s->GetFloat(KSETTINGS_YRATIO));word(services->master->m_loadingResources);const CEGUI::Point& cursor=CEGUI::MouseCursor::getSingleton().getPosition();real(cursor.d_x);real(cursor.d_y);
 d.restore();g->m_settings=NULL;g->m_root=NULL;g->m_renderWindow=NULL;g->m_gameClient=NULL;g->m_masterResourceManager=NULL;g->m_cameraControl=NULL;g->m_soundManager=NULL;g->m_logManager=NULL;systemsGameDtor(g);Ogre::NedAllocImpl::deallocBytes(g);word(gameWitness.getObject()==NULL);if(gameWitness.getObject())std::abort();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
int endWorker(const tlhybrid_host*host){tlheadless::Environment*environment=new tlheadless::Environment;environment->loadGameSkin();services=new nativegame::Services;if(!services->ready())return 1;menugui::Audio*audio=new menugui::Audio(services->master);(void)audio;owner=new menugui::Client(*services->settings,services->master,*services->master->m_pSoundManager);gameclient_fixture::UiOwner*ui=new gameclient_fixture::UiOwner(*services->settings,*owner->client,owner->camera->m_cameras[0],owner->scenes[0],owner->scenes[1],owner->scenes[2],owner->resources);nativeUI=ui->ui;
 int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_game_frame_ended",reinterpret_cast<uintptr_t>(&endOriginal));for(unsigned mode=0;mode<11;++mode)for(unsigned sound=0;sound<2;++sound){Case c={mode,sound,0};autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,10000);autotest::runChild(candidate,&c,b,2000,10000);++cases;bool ok=coverage.observe(host,a,b)==0;if(!ok){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    game frame end mode%u sound%u status%d/%d valid%u/%u issue%u/%u bytes%lu/%lu first%lu\n",mode,sound,a.childStatus,b.childStatus,a.reportValid,b.reportValid,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);}TL_CHECK(failures,ok);}coverage.report(host);
 Case control={7,1,1};autotest::Outcome a,b;autotest::runChild(original,&control,a,2000,10000);autotest::runChild(candidate,&control,b,2000,10000);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);bool completed=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);host->log("    game frame end negative detected%u completed%u\n",unsigned(detected),unsigned(completed));return failures+(coverage.completed!=cases)+(!detected||!completed);}
TL_TEST(complete_game_frame_ended){return systems_fixture::isolated(endWorker,host,180);}
