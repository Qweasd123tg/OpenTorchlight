#include <limits>
#include "SystemsNativeGame.h"
#include "SystemsNativeMaster.h"
#define private public
#include "GameClient.h"
#undef private
TL_ORIGINAL(bool,startOriginal,(CGame*,const Ogre::FrameEvent&),"_ZN5CGame12frameStartedERKN4Ogre10FrameEventE")
extern "C" bool startCandidate(CGame*,const Ogre::FrameEvent&) __asm__("_ZN5CGame12frameStartedERKN4Ogre10FrameEventE");
TL_FUNCTION(startUpdate,"_ZN5CGame6updateEffb")
TL_FUNCTION(startClear,"_ZN11CGameClient25clearSceneManagerPassMapsEv")
extern "C" unsigned long startMilliseconds(Ogre::Timer*) __asm__("_ZN4Ogre5Timer15getMillisecondsEv");
namespace {
struct Case{unsigned mode,time,elapsed;};const Case*current;autotest::Capture*cap;unsigned timerCalls;
void word(unsigned x){cap->add(&x,sizeof(x));}void real(float x){cap->add(&x,sizeof(x));}
bool update(CGame*,float elapsed,float t,bool flag){word(1);real(elapsed);real(t);word(flag);return current->mode!=1;}
void clear(CGameClient*){word(2);}
unsigned long milliseconds(Ogre::Timer*){word(3);return timerCalls++?2500:current->time;}
void invoke(CGame*g,autotest::Capture&out,bool ours){
 union C{long double a;unsigned char data[sizeof(CGameClient)];} cs;std::memset(&cs,0,sizeof(cs));CGameClient*client=reinterpret_cast<CGameClient*>(cs.data);client->m_pendingPassClear=current->mode&1;g->m_gameClient=current->mode==2?NULL:client;
 *reinterpret_cast<unsigned long*>(0x14263f0)=current->mode==3?0:1;*reinterpret_cast<unsigned long*>(0x1426400)=100;*reinterpret_cast<unsigned*>(0x14263f8)=27;
 g->m_settings->SetInt(KSETTINGS_NUM_TICKS_PER_SECOND,21);g->m_settings->SetInt(KSETTINGS_CURRENT_FPS,3);g->m_settings->SetInt(KSETTINGS_UPDATE_PERF,0);
 detour::Set d;TL_REDIRECT(d,startUpdate,&update);TL_REDIRECT(d,startClear,&clear);d.redirect(reinterpret_cast<char*>(&startMilliseconds),reinterpret_cast<char*>(&startMilliseconds),&milliseconds);if(d.failed())_exit(64);timerCalls=0;
 const float elapsed[]={-.25f,0,.05f,.1f,.2f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};Ogre::FrameEvent event={0,elapsed[current->elapsed]};bool(*fn)(CGame*,const Ogre::FrameEvent&)=ours?startCandidate:startOriginal;
 if(autotest::beginInvocation(out,fn)){bool r=fn(g,event);out.callCompleted=1;word(r);}out.add(reinterpret_cast<void*>(0x14263f8),4);out.add(reinterpret_cast<void*>(0x1426400),8);word(g->m_settings->GetInt(KSETTINGS_NUM_TICKS_PER_SECOND));word(g->m_settings->GetInt(KSETTINGS_CURRENT_FPS));word(g->m_settings->GetInt(KSETTINGS_UPDATE_PERF));
}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);current=&c;cap=&out;if(c.mode==4){SystemsNativeMaster native;SystemsNativeGame game(native.root,native.settings);game.game->m_masterResourceManager=native.master;native.master->m_loadingResources=true;invoke(game.game,out,ours);}else{SystemsNativeGame game;invoke(game.game,out,ours);}}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_game_frame_started){int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_game_frame_started",reinterpret_cast<uintptr_t>(&startOriginal));const unsigned times[]={100,1100,1101,2400};for(unsigned mode=0;mode<5;++mode)for(unsigned t=0;t<4;++t)for(unsigned e=0;e<(mode==4?1u:7u);++e){Case c={mode,times[t],e};autotest::Outcome a,b;autotest::runChild(original,&c,a,1500,10000);autotest::runChild(candidate,&c,b,1500,10000);++cases;bool ok=coverage.observe(host,a,b)==0;TL_CHECK(failures,ok);}coverage.report(host);return failures+(coverage.completed!=cases);}
