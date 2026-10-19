#include <string>
#include <vector>
#include <map>
#include <new>
#include <limits>
#define private public
#define protected public
#include "Player.h"
#include "GameClient.h"
#include "ResourceManager.h"
#include "Achievements.h"
#include "Achievement.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldPlayerAchievements,(CPlayer*,CCharacter*),"_ZN7CPlayer35applyAchievementsForKilledCharacterEP10CCharacter")
extern "C" void newPlayerAchievements(CPlayer*,CCharacter*) __asm__("_ZN7CPlayer35applyAchievementsForKilledCharacterEP10CCharacter");
TL_FUNCTION(pac_hp,"_ZN10CCharacter2HPEv")
TL_FUNCTION(pac_singleton,"_ZN13CAchievements12getSingletonEv")
TL_FUNCTION(pac_get,"_ZN13CAchievements14getAchievementE13EACHIEVEMENTS")
TL_FUNCTION(pac_complete,"_ZN12CAchievement13forceCompleteEv")
namespace {
struct Case{unsigned index;};struct State{Case c;autotest::Capture*out;CCharacter*target;CAchievement*achievements;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned v){active->out->add(&v,4);}
int hp(CCharacter*p){num(1);num(p==active->target);return active->c.index%5?0:1;}
CAchievements*singleton(){num(2);return reinterpret_cast<CAchievements*>(0x11223300);}
CAchievement*get(CAchievements*p,EACHIEVEMENTS e){num(3);num(p==reinterpret_cast<CAchievements*>(0x11223300));num(e);return int(e)<14&&(hash(4)&3)==0?NULL:&active->achievements[int(e)];}
void complete(CAchievement*p){num(4);num(p-active->achievements);p->m_bAchieved=true;}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;active=&s;s.c=c;s.out=&out;CPlayer*p=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));s.target=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.achievements=static_cast<CAchievement*>(autotest::allocate(sizeof(CAchievement)*40));CResourceManager*r=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));CGameClient*client=static_cast<CGameClient*>(autotest::allocate(sizeof(CGameClient)));new(&r->m_GameClients)TArrayList<CGameClient*>;if(hash(1)%3)r->m_GameClients.add(hash(2)%4?client:NULL);p->m_pResourceManager=hash(3)%5?r:NULL;client->m_startDifficulty=int(hash(5)%7)-2;p->m_saveOnDeath=hash(6)&1;p->m_journalStats[5]=int(hash(7)%3)-1;
const float times[]={-100,0,17999,18000,18001,28799,28800,28801,1e8f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};p->m_playTime=times[hash(8)%11];const wchar_t*names[]={L"EMBERCOLOSSUS",L"embercolossus",L"ALRIC_EVIL",L"alric_evil",L"FIRSTHENCHMEN",L"firsthenchmen",L"LICH",L"lich",L"MEDEA",L"medea",L"BOSS1",L"boss1",L"ROOTGOLEMBOSS",L"rootgolemboss",L"LAVATROLLBOSS",L"lavatrollboss",L"ORDRAK",L"ordrak",L"unknown",L""};new(&s.target->m_sName)std::wstring(names[c.index%20]);typedef void(*F)(CPlayer*,CCharacter*);F f=ours?newPlayerAchievements:oldPlayerAchievements;if(!autotest::beginInvocation(out,f))return;f(p,s.target);out.callCompleted=1;for(unsigned i=0;i<40;++i)num(s.achievements[i].m_bAchieved);num(p->m_journalStats[5]);s.target->m_sName.~basic_string();r->m_GameClients.~TArrayList();}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(all_player_achievements){detour::Set h;TL_REDIRECT(h,pac_hp,&hp);TL_REDIRECT(h,pac_singleton,&singleton);TL_REDIRECT(h,pac_get,&get);TL_REDIRECT(h,pac_complete,&complete);if(h.failed())return 1;autotest::Coverage coverage("all_player_achievements",0x8fb050);for(unsigned i=0;i<8192;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player achievement seed%u status%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=8192||coverage.different||coverage.missing;}
