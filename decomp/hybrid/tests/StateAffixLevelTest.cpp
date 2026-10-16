#include <cstring>
#include <stdint.h>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "Affix.h"
TL_ORIGINAL(void,oLevel,(CAffix*,unsigned),"_ZN6CAffix8setLevelEj")
extern "C" void nLevel(CAffix*,unsigned) __asm__("_ZN6CAffix8setLevelEj");
TL_FUNCTION(affixPercent,"_ZN6CAffix10setPercentEc")
namespace {
autotest::Capture*cap;CAffix*self;
void percent(CAffix*p,char value){cap->add(&value,1);if(p!=self)cap->issue=autotest::Capture::InvalidReport;cap->add(&p->m_uiLevel,4);cap->add(&p->m_cLevelPercent,1);}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);cap=&out;uint64_t storage[(sizeof(CAffix)+7)/8];std::memset(storage,0x5a,sizeof(storage));self=reinterpret_cast<CAffix*>(storage);int lower[]={0,1,5,20,99,100,-10,50,0,16777216};int upper[]={1,10,5,10,100,100,10,99,1000000,16777316};unsigned levels[]={0,1,4,5,10,20,50,99,100,1000000,0x7fffffff,0xffffffff};self->m_iMinSpawnRange=lower[seed%10];self->m_iMaxSpawnRange=upper[seed%10];detour::Set patches;TL_REDIRECT(patches,affixPercent,&percent);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}void(*fn)(CAffix*,unsigned)=ours?nLevel:oLevel;if(!autotest::beginInvocation(out,fn))return;fn(self,levels[seed/10]);out.callCompleted=1;out.add(&self->m_uiLevel,4);out.add(&self->m_cLevelPercent,1);}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(state_affix_set_level){autotest::Coverage coverage("state_affix_set_level",(uintptr_t)&oLevel);for(unsigned seed=0;seed<120;++seed){autotest::Outcome x,y;autotest::runChild(a,&seed,x);autotest::runChild(b,&seed,y);if(coverage.observe(host,x,y)){host->log("    affix level seed %u issue %u/%u exits %d/%d\n",seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
