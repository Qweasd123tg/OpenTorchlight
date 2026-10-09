#include <cstring>
#include "GameUI.h"
#include "AutoTest.h"
TL_ORIGINAL(bool,originalIngameEarly,(CGameUI*,void*,float,bool),"_ZN7CGameUI18processIngameInputEPvfb")
extern "C" bool candidateIngameEarly(CGameUI*,void*,float,bool) __asm__("_ZN7CGameUI18processIngameInputEPvfb");
namespace {
struct EarlyCase {unsigned player,enabled,consume,pattern;};
template<class T>T& field(void* p,unsigned offset){return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);}
void side(const EarlyCase& c,bool ours,autotest::Capture& out){
    unsigned long long memory[(0x1a08+7)/8],player[32]={0};
    std::memset(memory,c.pattern,sizeof(memory));
    CGameUI* ui=reinterpret_cast<CGameUI*>(memory);
    field<void*>(ui,0x38)=c.player?player:NULL;
    field<bool>(ui,0x1998)=c.consume;
    field<bool>(ui,0x12fb)=(c.pattern&1)!=0;
    const int slots[]={-1,0,1,999,-2147483647};
    field<int>(ui,0x1674)=slots[c.pattern%5];
    field<int>(ui,0x1678)=slots[(c.pattern+1)%5];
    field<int>(ui,0x167c)=slots[(c.pattern+2)%5];
    if(ours)autotest::invoke(out,&candidateIngameEarly,ui,static_cast<void*>(NULL),0.125f,bool(c.enabled));
    else autotest::invoke(out,&originalIngameEarly,ui,static_cast<void*>(NULL),0.125f,bool(c.enabled));
    // Compare the entire object: early exits must not mutate unrelated state.
    out.add(memory,sizeof(memory));
}
void a(void* p,autotest::Capture& out){side(*static_cast<EarlyCase*>(p),false,out);}
void b(void* p,autotest::Capture& out){side(*static_cast<EarlyCase*>(p),true,out);}
}
TL_TEST(ingame_input_early_exit_differential){
    autotest::Coverage coverage("ingame_input_early_exit_differential",reinterpret_cast<uintptr_t>(&originalIngameEarly));
    unsigned count=0;
    for(unsigned player=0;player<2;++player)for(unsigned enabled=0;enabled<2;++enabled){
        if(player&&enabled)continue;
        for(unsigned consume=0;consume<2;++consume)for(unsigned pattern=0;pattern<16;++pattern){
            EarlyCase c={player,enabled,consume,pattern*17};autotest::Outcome left,right;
            autotest::runChild(a,&c,left);autotest::runChild(b,&c,right);++count;
            int difference=coverage.observe(host,left,right);
            if(difference||left.childStatus||right.childStatus||!left.reportValid||!right.reportValid||!left.capture.callCompleted||!right.capture.callCompleted){
                coverage.report(host);host->log("    early case player=%u enabled=%u consume=%u pattern=%u exits=%d/%d lengths=%lu/%lu\n",player,enabled,consume,c.pattern,left.childStatus,right.childStatus,(unsigned long)left.capture.length,(unsigned long)right.capture.length);return 1;
            }
        }
    }
    coverage.report(host);host->log("    processIngameInput early exits: %u comparisons (partial coverage only)\n",count);return 0;
}
