#include <Ogre.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "WaypointActivator.h"
#include "Player.h"
#include "Level.h"
#include "GameClient.h"
#include "GameUI.h"
#include "StringTranslate.h"
#undef protected
#undef private
TL_ORIGINAL(void,oldWaypointActivation,(CWaypointActivator*),"_ZN18CWaypointActivator8activateEv")
extern "C" void newWaypointActivation(CWaypointActivator*) __asm__("_ZN18CWaypointActivator8activateEv");
TL_FUNCTION(activationAdd,"_ZN7CPlayer11addWaypointESbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(activationTranslateSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(activationTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(activationBig,"_ZN7CGameUI10setBigTextESbIwSt11char_traitsIwESaIwEEf")
TL_FUNCTION(activationSmall,"_ZN7CGameUI12setSmallTextESbIwSt11char_traitsIwESaIwEEf")
namespace {
struct Case{unsigned seed;bool negative;};
struct State{
 Case input;autotest::Capture*out;CWaypointActivator*activator;CResourceManager*resources[4];CPlayer*players[4];CGameClient*clients[4];CLevel*levels[4];CGameUI*ui[4];unsigned additions;
};
State*active;
void number(long long value){active->out->add(&value,sizeof(value));}
unsigned playerId(CPlayer*p){for(unsigned i=0;i<4;++i)if(p==active->players[i])return i;std::abort();return 0;}
unsigned uiId(CGameUI*p){for(unsigned i=0;i<4;++i)if(p==active->ui[i])return i;std::abort();return 0;}
bool add(CPlayer*p,std::wstring name,int depth){unsigned id=playerId(p);number(1);number(id);active->out->addText(name);number(depth);++active->additions;
 if(active->additions==1){
  unsigned mutation=active->input.seed/32%4;
  if(mutation==1)active->resources[0]->m_GameClients.clear();
  if(mutation==2)active->resources[id]->m_pLevel=active->levels[(id+1)%4];
  if(mutation==3)active->resources[0]->m_GameClients.add(active->clients[3]);
 }
 return bool((active->input.seed+id)&1);
}
CStringTranslate*singleton(){number(2);return reinterpret_cast<CStringTranslate*>(active);}
std::wstring translate(CStringTranslate*p,const wchar_t*key){number(3);number(p==reinterpret_cast<CStringTranslate*>(active));active->out->addText(std::wstring(key));return active->input.seed%7?L"Перевод activated":L"";}
void big(CGameUI*p,std::wstring value,float duration){number(4);unsigned id=uiId(p);number(id);active->out->addText(value);active->out->add(&duration,4);if(active->input.seed/128%2)active->levels[id]->m_pGameClient=active->clients[(id+1)%4];}
void small(CGameUI*p,std::wstring value,float duration){number(5);number(uiId(p));active->out->addText(value);active->out->add(&duration,4);}
template<class T>T*allocate(){return static_cast<T*>(autotest::allocate(sizeof(T)));}
void side(void*raw,autotest::Capture&out,bool ours){
 autotest::g_arenaUsed=0;State state;active=&state;state.input=*static_cast<Case*>(raw);state.out=&out;state.additions=0;
 state.activator=allocate<CWaypointActivator>();
 for(unsigned i=0;i<4;++i){
  state.resources[i]=allocate<CResourceManager>();new(&state.resources[i]->m_GameClients)TArrayList<CGameClient*>(10);
  state.players[i]=allocate<CPlayer>();state.clients[i]=allocate<CGameClient>();state.levels[i]=allocate<CLevel>();state.ui[i]=allocate<CGameUI>();
  state.players[i]->m_pResourceManager=state.resources[i];state.resources[i]->m_pLevel=state.levels[i];
  state.clients[i]->m_pPlayer=state.players[i];state.clients[i]->m_pGameUI=state.ui[i];state.levels[i]->m_pGameClient=state.clients[i];
  std::wstring name=i%2?L"DUNGEON_日本語":L"";new(&state.levels[i]->m_sDungeonName)std::wstring(name);
  state.levels[i]->m_iLevelDepth=int(0x80000000u+state.input.seed*13u+i*17u);
 }
 state.activator->m_pResourceManager=state.resources[0];
 unsigned count=state.input.seed%5;
 for(unsigned i=0;i<count;++i)state.resources[0]->m_GameClients.add(state.clients[i]);
 for(unsigned i=0;i<4;++i){unsigned kind=(state.input.seed/5+i)%5;if(kind==1)state.clients[i]->m_pPlayer=NULL;if(kind==2)state.players[i]->m_pResourceManager=NULL;if(kind==3)state.resources[i]->m_pLevel=NULL;}
 detour::Set hooks;TL_REDIRECT(hooks,activationAdd,&add);TL_REDIRECT(hooks,activationTranslateSingleton,&singleton);TL_REDIRECT(hooks,activationTranslate,&translate);TL_REDIRECT(hooks,activationBig,&big);TL_REDIRECT(hooks,activationSmall,&small);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Function)(CWaypointActivator*);Function function=ours?newWaypointActivation:oldWaypointActivation;
 if(!autotest::beginInvocation(out,function))return;function(state.activator);function(state.activator);out.callCompleted=1;
 if(ours&&state.input.negative)++state.additions;
 number(6);number(state.additions);number(state.resources[0]->m_GameClients.size());
 for(unsigned i=0;i<state.resources[0]->m_GameClients.size();++i){for(unsigned j=0;j<4;++j)if(state.resources[0]->m_GameClients[i]==state.clients[j])number(j);}
 for(unsigned i=0;i<4;++i){out.addText(state.levels[i]->m_sDungeonName);number(state.levels[i]->m_iLevelDepth);for(unsigned j=0;j<4;++j){number(state.resources[i]->m_pLevel==state.levels[j]);number(state.levels[i]->m_pGameClient==state.clients[j]);}}
}
void a(void*p,autotest::Capture&out){side(p,out,false);}void b(void*p,autotest::Capture&out){side(p,out,true);}
}
TL_TEST(waypoint_activation_recovery){
 autotest::Coverage coverage("waypoint_activation_recovery",0xeb2200);
 for(unsigned i=0;i<320;++i){Case c={i,false};autotest::Outcome before,after;autotest::runChild(a,&c,before);autotest::runChild(b,&c,after);
  if(coverage.observe(host,before,after)){host->log("    waypoint activation seed%u status%d/%d issue%u/%u bytes%lu/%lu\n",i,before.childStatus,after.childStatus,before.capture.issue,after.capture.issue,(unsigned long)before.capture.length,(unsigned long)after.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);Case c={19,true};autotest::Outcome before,after;autotest::runChild(a,&c,before);autotest::runChild(b,&c,after);
 bool detected=before.capture.length!=after.capture.length||std::memcmp(before.capture.data,after.capture.data,before.capture.length);
 host->log("    waypoint activation negative control detected%u\n",detected?1u:0u);
 return !detected||autotest::incomplete(before)||autotest::incomplete(after)||!before.reportValid||!after.reportValid||before.childStatus||after.childStatus;
}
