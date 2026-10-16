#include <cstring>
#include <stdint.h>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "Achievement.h"
TL_ORIGINAL(std::wstring,oProgress,(CAchievement*),"_ZN12CAchievement21getStatCompleteStringEv")
extern "C" std::wstring nProgress(CAchievement*) __asm__("_ZN12CAchievement21getStatCompleteStringEv");
TL_FUNCTION(statsSingleton,"_ZN11CSteamStats12getSingletonEv")
TL_FUNCTION(statInt,"_ZN11CSteamStats10getStatIntE6ESTATS")
namespace {
autotest::Capture*cap;void*stats;unsigned seed;
void*singleton(){unsigned mark=1;cap->add(&mark,4);return stats;}
int stat(void*p,int type){unsigned mark=2;cap->add(&mark,4);cap->add(&type,4);if(p!=stats)cap->issue=autotest::Capture::InvalidReport;int values[]={0,1,-1,100,2147483647,int(0x80000000)};return values[(seed/3)%6];}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);cap=&out;uint64_t as[(sizeof(CAchievement)+7)/8],ss[16];stats=ss;CAchievement*self=reinterpret_cast<CAchievement*>(as);self->m_eStatType=static_cast<ESTATS>(seed%3==0?30:seed%32);self->m_bAchieved=seed&1;int required[]={0,1,-1,42,int(0x80000000),2147483647};std::memcpy(&self->m_fRequiredValue,&required[(seed/2)%6],4);detour::Set patches;TL_REDIRECT(patches,statsSingleton,&singleton);TL_REDIRECT(patches,statInt,&stat);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}std::wstring(*fn)(CAchievement*)=ours?nProgress:oProgress;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(self);out.callCompleted=1;out.addText(result);if(self->m_eStatType==30&&result!=(self->m_bAchieved?L"1/1":L"0/1"))out.issue=autotest::Capture::InvalidReport;}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(state_achievement_progress){autotest::Coverage coverage("state_achievement_progress",(uintptr_t)&oProgress);for(unsigned seed=0;seed<120;++seed){autotest::Outcome x,y;autotest::runChild(a,&seed,x);autotest::runChild(b,&seed,y);if(coverage.observe(host,x,y)){host->log("    achievement progress seed %u issue %u/%u exits %d/%d\n",seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
