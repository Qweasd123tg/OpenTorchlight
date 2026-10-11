#include <cstring>
#include <limits>
#include <vector>
#include <fenv.h>
#include "AutoTest.h"
#include "GameStateController.h"
TL_ORIGINAL(void, originalPlayerHPEvents, (CGameStateController*,float,float,float), "_ZN20CGameStateController33broadcastPlayerHPThreshholdEventsEfff")
extern "C" void* gameStateTable[] __asm__("_ZTV20CGameStateController");
extern "C" void candidatePlayerHPEvents (CGameStateController*,float,float,float) __asm__("_ZN20CGameStateController33broadcastPlayerHPThreshholdEventsEfff");
namespace {
struct Case {float maximum,oldHP,change;};
std::vector<unsigned int> events;
void event(void*,unsigned int id) {events.push_back(id);}
void side(Case& c,bool ours,autotest::Capture& out) {
    long long storage[0x78/8];std::memset(storage,0,sizeof(storage));
    void* table[10];std::memcpy(table,gameStateTable,sizeof(table));table[8]=reinterpret_cast<void*>(&event);void* address=table+2;std::memcpy(storage,&address,sizeof(address));
    CGameStateController* object=reinterpret_cast<CGameStateController*>(storage);events.clear();feclearexcept(FE_ALL_EXCEPT);
    autotest::invoke(out,ours?candidatePlayerHPEvents:originalPlayerHPEvents,object,c.maximum,c.oldHP,c.change);
    out.add(storage,sizeof(storage));int exceptions=fetestexcept(FE_ALL_EXCEPT);out.add(&exceptions,sizeof(exceptions));size_t count=events.size();out.add(&count,sizeof(count));for(size_t i=0;i<count;++i)out.add(&events[i],sizeof(events[i]));
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(game_state_hp_observed) {
    int failures=0;autotest::Coverage coverage("game_state_hp_observed",(uint64_t)(uintptr_t)originalPlayerHPEvents);std::vector<Case> cases;
    const float maxima[]={1,100,1000};
    for(unsigned int m=0;m<3;++m)for(unsigned int n=1;n<=9;++n) {
        float at=maxima[m]*static_cast<float>(n)/10.0f,step=maxima[m]/1000.0f;
        const Case boundaries[]={
            {maxima[m],at+step,-2*step},{maxima[m],at-step,2*step},
            {maxima[m],at+step,-step},{maxima[m],at-step,step},
            {maxima[m],at,step},{maxima[m],at,-step},{maxima[m],at,0},
            {maxima[m],0,at+step}};
        cases.insert(cases.end(),boundaries,boundaries+8);
    }
    float nan=std::numeric_limits<float>::quiet_NaN(),inf=std::numeric_limits<float>::infinity();
    const Case special[]={
        {100,100,-100},{100,1,100},{100,100,-200},{100,-50,200},
        {0,100,-100},{-1,100,-100},{-0.0f,100,-100},{nan,inf,-inf},
        {nan,100,-100},{inf,100,-100},{100,nan,0},{100,100,nan},
        {100,inf,-inf},{100,-inf,inf},{inf,inf,-inf},{100,0,inf},
        {100,100,inf},{100,100,-inf},{100,-0.0f,100},{1,0.1f,0.8f}};
    cases.insert(cases.end(),special,special+sizeof(special)/sizeof(special[0]));
    for(size_t i=0;i<cases.size();++i) {autotest::Outcome a,b;autotest::runChild(original,&cases[i],a);autotest::runChild(recovered,&cases[i],b);

        if(coverage.observe(host,a,b)){host->log("    HP observed case %lu status %d/%d\n",(unsigned long)i,a.status,b.status);coverage.report(host);return 1;}
    }coverage.report(host);return failures;
}
