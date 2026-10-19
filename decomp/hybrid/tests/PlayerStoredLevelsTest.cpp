#include <string>
#include <vector>
#include <map>
#include <new>
#include <limits>
#define private public
#define protected public
#include "Player.h"
#include "Level.h"
#include "LevelState.h"
#include "Quest.h"
#include "QuestManager.h"
#include "GameGlobals.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldPlayerStoredLevels,(CPlayer*,CLevel&),"_ZN7CPlayer18updateStoredLevelsER6CLevel")
extern "C" void newPlayerStoredLevels(CPlayer*,CLevel&) __asm__("_ZN7CPlayer18updateStoredLevelsER6CLevel");
TL_FUNCTION(psl_globals,"_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(psl_details,"_ZN6CQuest15getQuestDetailsEv")
namespace {
struct Case{unsigned index;};struct State{Case c;autotest::Capture*out;CGameGlobals*globals;CQuest*quests[4];CLevelState*states[10];unsigned destroyed[10];};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){active->out->add(&n,4);}void fp(float v){active->out->add(&v,4);}void wide(const std::wstring&s){num(s.size());active->out->add(s.data(),s.size()*4);}unsigned id(CLevelState*p){for(unsigned i=0;i<10;++i)if(active->states[i]==p)return i;return 99;}
CGameGlobals*globals(){num(1);return active->globals;}std::wstring details(CQuest*p){num(2);unsigned q=0;while(q<4&&active->quests[q]!=p)++q;num(q);return hash(10+q)%3?L"quest details":L"";}
class Saved:public CLevelState{public:Saved(int n):CLevelState(n){}virtual~Saved(){unsigned i=id(this);num(3);num(i);++active->destroyed[i];}};
void init(){const unsigned a[]={0x14949c8,0x148a308};for(unsigned i=0;i<2;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(a[i]),8);if(!p)new(reinterpret_cast<void*>(a[i]))std::wstring;}}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;init();CPlayer*p=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));CLevel*l=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));s.globals=static_cast<CGameGlobals*>(autotest::allocate(sizeof(CGameGlobals)));s.globals->m_maxLevelMemory=int(hash(1)%8)-1;s.globals->m_levelRespawnTime=int(hash(2)%5)*25-25;new(&p->m_savedLevels)std::vector<CLevelState*>;const wchar_t*names[]={L"A",L"B",L"C",L"D"};new(&p->m_portalDungeon)std::wstring(names[hash(3)%4]);new(&p->m_returnDungeon)std::wstring(names[hash(4)%4]);new(&l->m_sDungeonName)std::wstring(names[hash(5)%4]);p->m_portalDepth=hash(6)%3;p->m_returnDepth=hash(7)%3;p->m_hasPortal=hash(8)&1;l->m_iLevelDepth=hash(9)%3;const float times[]={-1,-2,0,24,25,49,50,75,100,1000000,1000001,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};p->m_playTime=times[hash(14)%13];unsigned count=hash(15)%10;for(unsigned i=0;i<count;++i){Saved*v=new Saved(hash(30+i)%3);s.states[i]=v;v->m_sLevelName=names[hash(50+i)%4];v->m_iStateVersion=times[hash(70+i)%13];v->m_bUnknownB0=(hash(90+i)&7)==0;v->m_bUnknownB1=(hash(110+i)&7)==0;p->m_savedLevels.push_back(v);}CQuestManager*q=static_cast<CQuestManager*>(autotest::allocate(sizeof(CQuestManager)));new(&q->m_Unknown18)TArrayList<CQuest*>(2);for(unsigned i=0;i<hash(16)%5;++i){CQuest*v=static_cast<CQuest*>(autotest::allocate(sizeof(CQuest)));s.quests[i]=v;const wchar_t*questNames[]={L"a",L"b",L"C",L"D"};new(&v->m_pUnknown30)std::wstring(questNames[hash(130+i)%4]);v->m_iUnknown20=hash(150+i)%3;q->m_Unknown18.add(v);}p->m_questManager=hash(17)%3?q:NULL;typedef void(*F)(CPlayer*,CLevel&);F f=ours?newPlayerStoredLevels:oldPlayerStoredLevels;if(!autotest::beginInvocation(out,f))return;f(p,*l);out.callCompleted=1;num(p->m_savedLevels.size());for(unsigned i=0;i<p->m_savedLevels.size();++i){CLevelState*v=p->m_savedLevels[i];num(id(v));num(v->m_iLevelId);wide(v->m_sLevelName);fp(v->m_iStateVersion);}for(unsigned i=0;i<count;++i)num(s.destroyed[i]);
// End remaining actual object lifetimes after the observed invocation.
s.out=NULL;for(unsigned i=0;i<p->m_savedLevels.size();++i){CLevelState*v=p->m_savedLevels[i];v->CLevelState::~CLevelState();Ogre::NedAllocImpl::deallocBytes(v);}p->m_savedLevels.~vector();p->m_portalDungeon.~basic_string();p->m_returnDungeon.~basic_string();l->m_sDungeonName.~basic_string();for(unsigned i=0;i<q->m_Unknown18.m_nCount;++i)q->m_Unknown18[i]->m_pUnknown30.~basic_string();q->m_Unknown18.~TArrayList();}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(all_player_stored_levels){detour::Set h;TL_REDIRECT(h,psl_globals,&globals);TL_REDIRECT(h,psl_details,&details);if(h.failed())return 1;autotest::Coverage coverage("all_player_stored_levels",0x8f3ba0);for(unsigned i=0;i<4096;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player stored seed%u status%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);for(unsigned z=k>8?k-8:0;z*4<a.capture.length&&z*4<b.capture.length&&z<k+24;++z){unsigned aa,bb;std::memcpy(&aa,a.capture.data+4*z,4);std::memcpy(&bb,b.capture.data+4*z,4);host->log("    word%u %08x/%08x\n",z,aa,bb);}break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=4096||coverage.different||coverage.missing;}
