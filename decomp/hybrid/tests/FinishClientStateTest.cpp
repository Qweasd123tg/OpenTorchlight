#include "SmallMassCompare.h"
#include <limits>
#include <string>
#include <vector>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#define private public
#define protected public
#include "GameClient.h"
#include "GameUI.h"
#include "Player.h"
#include "Settings.h"
#undef protected
#undef private
#include "SettingsVariables.h"
TL_ORIGINAL(void,clientSpeedOld,(CGameClient*,float),"_ZN11CGameClient12setSpeedMultEf")
extern "C" void clientSpeedNew(CGameClient*,float) __asm__("_ZN11CGameClient12setSpeedMultEf");
TL_ORIGINAL(bool,clientPauseOld,(CGameClient*),"_ZN11CGameClient11getIsPausedEv")
extern "C" bool clientPauseNew(CGameClient*) __asm__("_ZN11CGameClient11getIsPausedEv");
TL_ORIGINAL(void,clientWarpOld,(CGameClient*,std::wstring,int,int,bool,std::wstring,bool),"_ZN11CGameClient10warpLevelsESbIwSt11char_traitsIwESaIwEEiibS3_b")
extern "C" void clientWarpNew(CGameClient*,std::wstring,int,int,bool,std::wstring,bool) __asm__("_ZN11CGameClient10warpLevelsESbIwSt11char_traitsIwESaIwEEiibS3_b");
TL_FUNCTION(clientBoth,"_ZN7CGameUI18bothCoveredPartialEv")
TL_FUNCTION(clientConsole,"_ZN7CGameUI16getConsoleIsOpenEv")
TL_FUNCTION(clientModal,"_ZN7CGameUI22modalDialogOpenPartialEv")
TL_FUNCTION(clientSetting,"_ZN20CDynamicPropertyFile6GetIntEj")
namespace finish_client {
using namespace smallmass;
CGameClient* self;CGameUI* uis[2];CSettings* settings;unsigned calls;
// Only the typed state reached by these nonvirtual functions is constructed;
// no CGameClient/CGameUI/Player constructor or SDK-layout coverage is claimed.
unsigned mutation(){return input->index/32%5;}
void mutate(unsigned at){if(mutation()==at)self->m_pGameUI=0;else if(mutation()==4)self->m_pGameUI=uis[1];}
bool both(CGameUI* ui){number(1201);number(ui==uis[0]);++calls;mutate(1);return input->index&1;}
bool console(CGameUI* ui){number(1202);number(ui==uis[0]);++calls;mutate(2);return input->index&2;}
bool modal(CGameUI* ui){number(1203);number(ui==uis[0]);++calls;mutate(3);return input->index&4;}
int setting(CDynamicPropertyFile* p,unsigned key){number(1204);number(p==static_cast<CDynamicPropertyFile*>(settings));number(key==KSETTINGS_CONSOLE_NOPAUSE);++calls;return input->index&8?2:0;}
void side(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;calls=0;
 self=static_cast<CGameClient*>(autotest::allocate(sizeof(CGameClient)));new(static_cast<CRunicCore*>(self)) CRunicCore;
 new(&self->m_warpDungeon)std::wstring(L"old dungeon");new(&self->m_warpName)std::wstring(L"old waypoint");
 for(unsigned i=0;i<2;++i){uis[i]=static_cast<CGameUI*>(autotest::allocate(sizeof(CGameUI)));new(static_cast<CRunicCore*>(uis[i])) CRunicCore;uis[i]->m_paused=(c.index>>4)&1;}
 settings=static_cast<CSettings*>(autotest::allocate(sizeof(CSettings)));self->m_settings=settings;
 self->m_pGameUI=c.index%11?uis[0]:0;self->m_interactionState=c.index%13==0;
 CPlayer* player=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));new(static_cast<CRunicCore*>(player)) CRunicCore;new(&player->m_returnDungeon)std::wstring(c.index&16?L"saved_dungeon 名":L"");player->m_returnDepth=int(c.index)-17;self->m_pPlayer=player;
 detour::Set patch;TL_REDIRECT(patch,clientBoth,&both);TL_REDIRECT(patch,clientConsole,&console);TL_REDIRECT(patch,clientModal,&modal);TL_REDIRECT(patch,clientSetting,&setting);if(patch.failed())_exit(42);
 if(c.op==0){static const float values[]={0,-0.0f,1,-1,4.999f,5,5.001f,100,-100,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};float v=values[c.index%12];void(*fn)(CGameClient*,float)=ours?clientSpeedNew:clientSpeedOld;autotest::beginInvocation(out,fn);fn(self,v);out.callCompleted=1;floating(self->m_speedMult);if(v==v){float expected=v<=0?0:v>5?5:v;if(self->m_speedMult!=expected)_exit(53);}else if(self->m_speedMult==self->m_speedMult)_exit(54);}
 else if(c.op==1){bool(*fn)(CGameClient*)=ours?clientPauseNew:clientPauseOld;autotest::beginInvocation(out,fn);number(fn(self));out.callCompleted=1;number(calls);number(self->m_pGameUI==0);number(self->m_pGameUI==uis[1]);}
 else {static const wchar_t* names[]={L"",L"lastdungeon",L"LASTDUNGEON",L" lastdungeon",L"new_dungeon 名"};std::wstring dungeon=names[c.index%5],name=names[c.index/5%5];void(*fn)(CGameClient*,std::wstring,int,int,bool,std::wstring,bool)=ours?clientWarpNew:clientWarpOld;autotest::beginInvocation(out,fn);fn(self,dungeon,int(c.index)-70,int(c.index/7)-3,c.index&1,name,c.index&2);out.callCompleted=1;text(self->m_warpDungeon);text(self->m_warpName);number(self->m_warpDelta);number(self->m_warpDepth);number(self->m_warpPending);number(self->m_warpWaypoint);number(self->m_warpFlag);text(dungeon);text(name);text(player->m_returnDungeon);number(player->m_returnDepth);}
 player->m_returnDungeon.~basic_string();static_cast<CRunicCore*>(player)->~CRunicCore();for(unsigned i=0;i<2;++i)static_cast<CRunicCore*>(uis[i])->~CRunicCore();self->m_warpDungeon.~basic_string();self->m_warpName.~basic_string();static_cast<CRunicCore*>(self)->~CRunicCore();
}
}
TL_TEST(finish_client_speed){return smallmass::run(host,0,"finish_client_speed",0x56e170,&finish_client::side,144);}
TL_TEST(finish_client_pause){return smallmass::run(host,1,"finish_client_pause",0x56e570,&finish_client::side,352);}
TL_TEST(finish_client_warp){return smallmass::run(host,2,"finish_client_warp",0x5819b0,&finish_client::side,200);}
