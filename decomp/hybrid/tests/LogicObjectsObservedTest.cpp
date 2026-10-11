// Shadow tests: decompiled logic objects against the original machine code,
// inside the game process before hooks. Events are observed by giving both
// objects a copy of the original vtable whose BroadcastEvent slot records.
#include <cstring>
#include <new>

#include "AutoTest.h"
#include <limits>
#include "Utilities.h"
#include "LogicTimer.h"
#include "OutputIncrementor.h"

TL_ORIGINAL(void, originalTimerConstruct, (void*, CResourceManager*), "_ZN11CLogicTimerC1EP16CResourceManager")
TL_ORIGINAL(void, originalTimerDestroy, (void*), "_ZN11CLogicTimerD1Ev")
TL_ORIGINAL(void, originalTimerUpdate, (void*, float), "_ZN11CLogicTimer6updateEf")
TL_ORIGINAL(void, originalTimerSetEnabled, (void*, bool), "_ZN11CLogicTimer10setEnabledEb")
TL_ORIGINAL(void, originalIncrementorConstruct, (void*, CResourceManager*),
            "_ZN18COutputIncrementorC1EP16CResourceManager")
TL_ORIGINAL(void, originalIncrementorDestroy, (void*), "_ZN18COutputIncrementorD1Ev")
TL_ORIGINAL(void, originalIncrement, (void*), "_ZN18COutputIncrementor9incrementEv")
TL_ORIGINAL(void, originalIncrementorSetEnabled, (void*, bool), "_ZN18COutputIncrementor10setEnabledEb")

// The original global read by CResourceManager::getEditorIsRunning (bit 1 of +0x64).
extern char* gEditor;

extern "C" void candidateTimerConstruct (void*, CResourceManager*) __asm__("_ZN11CLogicTimerC1EP16CResourceManager");
extern "C" void candidateTimerDestroy (void*) __asm__("_ZN11CLogicTimerD1Ev");
extern "C" void candidateTimerUpdate (void*, float) __asm__("_ZN11CLogicTimer6updateEf");
extern "C" void candidateTimerSetEnabled (void*, bool) __asm__("_ZN11CLogicTimer10setEnabledEb");
extern "C" void candidateIncrementorConstruct (void*, CResourceManager*) __asm__("_ZN18COutputIncrementorC1EP16CResourceManager");
extern "C" void candidateIncrementorDestroy (void*) __asm__("_ZN18COutputIncrementorD1Ev");
extern "C" void candidateIncrement (void*) __asm__("_ZN18COutputIncrementor9incrementEv");
extern "C" void candidateIncrementorSetEnabled (void*, bool) __asm__("_ZN18COutputIncrementor10setEnabledEb");
namespace
{

const int kSlots = 8;
const int kBroadcastSlot = 6;
const int kMaxEvents = 64;

struct EventLog
{
    const void* object;
    unsigned int events[kMaxEvents];
    int count;
    bool overflow;

    void clear()
    {
        count = 0;
        overflow = false;
    }
};

EventLog g_logs[2];

void recordEvent(void* self, unsigned int event)
{
    for (int i = 0; i < 2; i++)
    {
        if (g_logs[i].object == self)
        {
            if (g_logs[i].count < kMaxEvents)
                g_logs[i].events[g_logs[i].count++] = event;
            else
                g_logs[i].overflow = true;
        }
    }
}

unsigned int g_seed = 777;

unsigned int nextRandom()
{
    g_seed = g_seed * 1103515245u + 12345u;
    return g_seed >> 8;
}

float randomFloat(float low, float high)
{
    return low + (high - low) * (nextRandom() % 10001) / 10000.0f;
}

// Copy of the object's original vtable with BroadcastEvent redirected.
void* g_vtable[kSlots];

void installRecorder(void* object)
{
    void** vptr = *reinterpret_cast<void***>(object);
    std::memcpy(g_vtable, vptr, sizeof(g_vtable));
    g_vtable[kBroadcastSlot] = reinterpret_cast<void*>(&recordEvent);
    *reinterpret_cast<void***>(object) = g_vtable;
}

bool sameLogs()
{
    if (g_logs[0].overflow || g_logs[1].overflow || g_logs[0].count != g_logs[1].count)
        return false;
    return std::memcmp(g_logs[0].events, g_logs[1].events, g_logs[0].count * sizeof(unsigned int)) == 0;
}

char g_fakeEditor[0x100];
char g_fakeResourceManager[0x100];

void setEditorRunning(bool running)
{
    int flags = running ? 2 : 0;
    std::memcpy(g_fakeEditor + 0x64, &flags, sizeof(flags));
}

} // namespace


namespace {
struct Case{unsigned seed,op;};
void body(Case&c,bool ours,autotest::Capture&out){
 gEditor=g_fakeEditor;setEditorRunning(c.seed%9==0);CResourceManager*resource=reinterpret_cast<CResourceManager*>(g_fakeResourceManager);
 unsigned long long bytes[0x78/8];std::memset(bytes,0x59,sizeof(bytes));void*p=bytes;char*fields=reinterpret_cast<char*>(bytes)+0x58;
 if(c.op==0)originalTimerConstruct(p,resource);else originalIncrementorConstruct(p,resource);installRecorder(p);g_logs[0].object=p;g_logs[1].object=NULL;g_logs[0].clear();g_logs[1].clear();
 const int counts[]={0,1,-1,2,3,-2,100,0x7fffffff};
 const float values[]={0.0f,-0.0f,0.125f,1.0f,-1.0f,100.0f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};
 if(c.op==0){float minimum=values[(c.seed/8)%8],maximum=minimum-0.5f,remaining=values[c.seed%8];std::memcpy(fields,&minimum,4);std::memcpy(fields+4,&maximum,4);std::memcpy(fields+8,&remaining,4);int repeats=counts[(c.seed/16)%8],left=counts[(c.seed/32)%8];std::memcpy(fields+12,&repeats,4);std::memcpy(fields+16,&left,4);fields[20]=(c.seed/64)&1;fields[21]=(c.seed/128)&1;
  void*manager=c.seed%11?resource:NULL;std::memcpy(fields+24,&manager,8);float elapsed=c.seed%3?values[(c.seed/3)%8]:remaining;UTILITIES::setSeed(c.seed+37);autotest::invoke(out,ours?candidateTimerUpdate:originalTimerUpdate,p,elapsed);
 }else{unsigned target=(c.seed/8)%9,count=c.seed%9;int repeats=counts[(c.seed/16)%8],left=counts[(c.seed/32)%8];std::memcpy(fields,&target,4);std::memcpy(fields+4,&count,4);std::memcpy(fields+8,&repeats,4);std::memcpy(fields+12,&left,4);fields[16]=(c.seed/64)&1;fields[17]=(c.seed/128)&1;void*manager=c.seed%11?resource:NULL;std::memcpy(fields+24,&manager,8);autotest::invoke(out,ours?candidateIncrement:originalIncrement,p);}
 if(g_logs[0].overflow){out.issue=autotest::Capture::Overflow;return;}out.add(&g_logs[0].count,4);out.add(g_logs[0].events,g_logs[0].count*4);out.add(bytes,sizeof(bytes));out.add(g_fakeEditor,sizeof(g_fakeEditor));out.add(g_fakeResourceManager,sizeof(g_fakeResourceManager));
 if(c.op==0)originalTimerDestroy(p);else originalIncrementorDestroy(p);
}
void original(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned op,const char*name){autotest::Coverage coverage(name,op?(uint64_t)(uintptr_t)originalIncrement:(uint64_t)(uintptr_t)originalTimerUpdate);
 for(unsigned seed=0;seed<768;++seed){Case c={seed,op};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    logic %u/%u status %d/%d\n",op,seed,a.status,b.status);coverage.report(host);return 1;}}
 coverage.report(host);return 0;}
}
TL_TEST(logic_timer_observed){return run(host,0,"logic_timer_observed");}
TL_TEST(logic_incrementor_observed){return run(host,1,"logic_incrementor_observed");}
