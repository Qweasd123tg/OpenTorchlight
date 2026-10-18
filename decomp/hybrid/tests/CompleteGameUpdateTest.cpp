#include <map>
#include <list>
#include <cstring>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#include "Game.h"
#include "GameClient.h"
#include "GameUI.h"
#undef private
#include "SteamStats.h"
#include "Achievements.h"
#include "SDL.h"
TL_ORIGINAL(bool, gameUpdateOriginal, (CGame*,float,float,bool), "_ZN5CGame6updateEffb")
extern "C" bool gameUpdateCandidate(CGame*,float,float,bool) __asm__("_ZN5CGame6updateEffb");
TL_ORIGINAL(void, updateSettingsCtor, (CSettings*,std::wstring,std::wstring,std::wstring,std::wstring), "_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_")
TL_ORIGINAL(void, updateSettingsDtor, (CSettings*), "_ZN9CSettingsD1Ev")
TL_ORIGINAL(void, updateStatsCtor, (CSteamStats*), "_ZN11CSteamStatsC1Ev")
TL_ORIGINAL(void, updateStatsDtor, (CSteamStats*), "_ZN11CSteamStatsD1Ev")
TL_ORIGINAL(void, updateAchievementsCtor, (CAchievements*), "_ZN13CAchievementsC1Ev")
TL_ORIGINAL(void, updateAchievementsDtor, (CAchievements*), "_ZN13CAchievementsD1Ev")
TL_FUNCTION(updateProcess,"_ZN11CGameClient12processInputEPvfb")
TL_FUNCTION(updateClient,"_ZN11CGameClient6updateEfPN4Ogre12RenderWindowEfb")
TL_FUNCTION(updateCovered,"_ZN7CGameUI11bothCoveredEv")
TL_FUNCTION(updateModal,"_ZN7CGameUI22modalDialogOpenPartialEv")
TL_FUNCTION(updateCinematic,"_ZN7CGameUI18getUIIsInCinematicEv")
TL_FUNCTION(updateSave,"_ZN11CSteamStats16forceStatsToSaveEv")
TL_FUNCTION(updateStats,"_ZN11CSteamStats6updateEf")
TL_FUNCTION(updateAchievements,"_ZN13CAchievements6updateEf")
namespace {
struct Case{unsigned scenario,timing;};const Case* current;autotest::Capture* capture;
void word(unsigned x){capture->add(&x,sizeof(x));}void real(float x){capture->add(&x,sizeof(x));}
bool process(CGameClient*,void*w,float e,bool focused){word(1);word(w==reinterpret_cast<void*>(0x1234));real(e);word(focused);return current->scenario!=1;}
void clientUpdate(CGameClient*,float e,Ogre::RenderWindow*w,float t,bool b){word(2);real(e);word(w==reinterpret_cast<Ogre::RenderWindow*>(0x5678));real(t);word(b);}
bool covered(CGameUI*){word(3);return current->scenario==7||current->scenario==14;}
bool modal(CGameUI*){word(4);return current->scenario==8||current->scenario==14;}
bool cinematic(CGameUI*){word(5);return current->scenario==10||current->scenario==14;}
void save(CSteamStats*){word(6);}void stats(CSteamStats*,float e){word(7);real(e);}void achievements(CAchievements*,float e){word(8);real(e);}
Uint32 windowFlags(SDL_Window*w){word(9);word(w==reinterpret_cast<SDL_Window*>(0x9876));return current->scenario==5?0:current->scenario==6?0x240:0x200;}
void side(void* raw,autotest::Capture&out,bool ours){
 Case c=*static_cast<Case*>(raw);current=&c;capture=&out;
 union G{long double a;unsigned char data[sizeof(CGame)];} gs;
 union C{long double a;unsigned char data[sizeof(CGameClient)];} cs;
 union U{long double a;unsigned char data[sizeof(CGameUI)];} us;
 union S{long double a;unsigned char data[sizeof(CSettings)];} ss;
 union T{long double a;unsigned char data[sizeof(CSteamStats)];} ts;
 union A{long double a;unsigned char data[sizeof(CAchievements)];} as;
 std::memset(&gs,0,sizeof(gs));std::memset(&cs,0,sizeof(cs));std::memset(&us,0,sizeof(us));
 CGame*g=reinterpret_cast<CGame*>(gs.data);CGameClient*client=reinterpret_cast<CGameClient*>(cs.data);CGameUI*ui=reinterpret_cast<CGameUI*>(us.data);
 CSettings*settings=reinterpret_cast<CSettings*>(ss.data);updateSettingsCtor(settings,L"",L"",L"",L"");
 CSteamStats*service=reinterpret_cast<CSteamStats*>(ts.data);updateStatsCtor(service);
 CAchievements*awards=reinterpret_cast<CAchievements*>(as.data);updateAchievementsCtor(awards);
 if(c.scenario==11)*reinterpret_cast<void**>(0x153a840)=NULL;
 if(c.scenario==12)*reinterpret_cast<void**>(0x1539240)=NULL;
 typedef std::list<float> Times;::new(&g->m_frameTimes)Times();
 g->m_settings=settings;g->m_gameClient=c.scenario==0?NULL:client;
 g->m_windowHandle=reinterpret_cast<void*>(0x1234);g->m_renderWindow=reinterpret_cast<Ogre::RenderWindow*>(0x5678);g->m_sdlWindow=reinterpret_cast<SDL_Window*>(0x9876);
 g->m_focused=c.timing&1;g->m_frameTimeCount=c.timing==2?2:4;g->m_frameTimeSum=0;
 for(unsigned i=0;i<c.timing;++i){float e=.02f*(i+1);g->m_frameTimes.push_back(e);g->m_frameTimeSum+=e;}
 client->m_restartRequested=c.scenario==2||c.scenario==4;client->m_quitRequested=c.scenario==3||c.scenario==4;
 client->m_pGameUI=c.scenario==13?NULL:ui;ui->m_paused=c.scenario==9||c.scenario==14;
 settings->SetInt(KSETTINGS_RENDERBEHIND,c.scenario%3-1);settings->SetInt(KSETTINGS_RES_WIDTH,800+c.timing);settings->SetInt(KSETTINGS_RES_HEIGHT,600+c.timing);settings->SetInt(KSETTINGS_FULLSCREEN,c.timing%2);
 *reinterpret_cast<bool*>(0x14263e0)=c.scenario==15;*reinterpret_cast<int*>(0x14263e4)=static_cast<int>(c.timing)-1;
 *reinterpret_cast<int*>(0x14263c0)=-2;*reinterpret_cast<int*>(0x14263c4)=-3;*reinterpret_cast<int*>(0x14263c8)=-4;
 detour::Set d;TL_REDIRECT(d,updateProcess,&process);TL_REDIRECT(d,updateClient,&clientUpdate);TL_REDIRECT(d,updateCovered,&covered);TL_REDIRECT(d,updateModal,&modal);TL_REDIRECT(d,updateCinematic,&cinematic);TL_REDIRECT(d,updateSave,&save);TL_REDIRECT(d,updateStats,&stats);TL_REDIRECT(d,updateAchievements,&achievements);
 d.redirect(reinterpret_cast<char*>(&SDL_GetWindowFlags),reinterpret_cast<char*>(&SDL_GetWindowFlags),&windowFlags);if(d.failed())_exit(64);
 const float elapsed[]={0.0f,-.1f,.025f,.5f};bool(*fn)(CGame*,float,float,bool)=ours?gameUpdateCandidate:gameUpdateOriginal;
 if(autotest::beginInvocation(out,fn)){bool r=fn(g,elapsed[c.timing],.031f,c.timing&1);out.callCompleted=1;word(r);}
 word(g->m_requestRestart);word(g->m_renderBehind);word(g->m_disableRenderBehind);word(g->m_disableRendering);
 real(g->m_frameTimeSum);word(g->m_frameTimes.size());for(Times::iterator it=g->m_frameTimes.begin();it!=g->m_frameTimes.end();++it)real(*it);
 real(settings->GetFloat(KSETTINGS_F_AVERAGE_FPS));out.add(reinterpret_cast<void*>(0x14263c0),12);out.add(reinterpret_cast<void*>(0x14263e4),8);
 d.restore();g->m_frameTimes.~Times();
 updateAchievementsDtor(awards);updateStatsDtor(service);updateSettingsDtor(settings);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_game_update){
 autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_game_update",reinterpret_cast<uintptr_t>(&gameUpdateOriginal));
 for(unsigned scenario=0;scenario<16;++scenario)for(unsigned timing=0;timing<4;++timing){Case c={scenario,timing};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_game_update",cases++,&coverage);TL_CHECK(failures,ok);}
 coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);
}
