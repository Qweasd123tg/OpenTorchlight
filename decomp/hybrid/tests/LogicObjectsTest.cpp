// Shadow tests: decompiled logic objects against the original machine code,
// inside the game process before hooks. Events are observed by giving both
// objects a copy of the original vtable whose BroadcastEvent slot records.
#include <cstring>
#include <new>

#include "HybridTest.h"
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
};

EventLog g_logs[2];

void recordEvent(void* self, unsigned int event)
{
    for (int i = 0; i < 2; i++)
    {
        if (g_logs[i].object == self && g_logs[i].count < kMaxEvents)
            g_logs[i].events[g_logs[i].count++] = event;
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
    if (g_logs[0].count != g_logs[1].count)
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

TL_TEST(LogicTimer_shadow)
{
    int failures = 0;
    char* savedEditor = gEditor;
    gEditor = g_fakeEditor;
    CResourceManager* resources = reinterpret_cast<CResourceManager*>(g_fakeResourceManager);

    static char a[sizeof(CLogicTimer)];
    static char b[sizeof(CLogicTimer)];
    TL_CHECK(failures, sizeof(CLogicTimer) == 0x78);
    originalTimerConstruct(a, resources);
    new (b) CLogicTimer(resources);
    TL_CHECK(failures, std::memcmp(a + 0x58, b + 0x58, 0x20) == 0);
    installRecorder(a);
    *reinterpret_cast<void***>(b) = g_vtable;
    g_logs[0].object = a;
    g_logs[1].object = b;

    for (int step = 0; step < 20000 && failures == 0; step++)
    {
        // Same random state in both; max <= min keeps resetTimer off the volatile RNG.
        char fields[0x18];
        float minimum = randomFloat(0.0f, 2.0f);
        float maximum = minimum - randomFloat(0.0f, 1.0f);
        float remaining = randomFloat(-1.0f, 2.0f);
        int repeatCount = int(nextRandom() % 4);
        int repeatsLeft = int(nextRandom() % 6) - 2;
        std::memcpy(fields + 0x00, &minimum, 4);
        std::memcpy(fields + 0x04, &maximum, 4);
        std::memcpy(fields + 0x08, &remaining, 4);
        std::memcpy(fields + 0x0c, &repeatCount, 4);
        std::memcpy(fields + 0x10, &repeatsLeft, 4);
        fields[0x14] = char(nextRandom() % 2);
        fields[0x15] = char(nextRandom() % 2);
        fields[0x16] = fields[0x17] = 0;
        CResourceManager* manager = (nextRandom() % 8) ? resources : 0;
        setEditorRunning(nextRandom() % 6 == 0);
        std::memcpy(a + 0x58, fields, sizeof(fields));
        std::memcpy(b + 0x58, fields, sizeof(fields));

        g_logs[0].count = g_logs[1].count = 0;
        if (nextRandom() % 3 == 0)
        {
            bool enabled = nextRandom() % 2;
            *reinterpret_cast<CResourceManager**>(a + 0x70) = resources;
            *reinterpret_cast<CResourceManager**>(b + 0x70) = resources;
            originalTimerSetEnabled(a, enabled);
            reinterpret_cast<CLogicTimer*>(b)->setEnabled(enabled);
        }
        else
        {
            // A quarter of the steps land exactly on zero remaining time.
            float elapsed = (nextRandom() % 4 == 0) ? remaining : randomFloat(0.0f, 1.5f);
            *reinterpret_cast<CResourceManager**>(a + 0x70) = manager;
            *reinterpret_cast<CResourceManager**>(b + 0x70) = manager;
            originalTimerUpdate(a, elapsed);
            reinterpret_cast<CLogicTimer*>(b)->update(elapsed);
        }
        TL_CHECK(failures, sameLogs());
        TL_CHECK(failures, std::memcmp(a + 0x58, b + 0x58, 0x20) == 0);
        if (failures)
            host->log("    step %d\n", step);
    }

    gEditor = savedEditor;
    originalTimerDestroy(a);
    reinterpret_cast<CLogicTimer*>(b)->CLogicTimer::~CLogicTimer();
    return failures;
}

TL_TEST(OutputIncrementor_shadow)
{
    int failures = 0;
    char* savedEditor = gEditor;
    gEditor = g_fakeEditor;
    CResourceManager* resources = reinterpret_cast<CResourceManager*>(g_fakeResourceManager);

    static char a[sizeof(COutputIncrementor)];
    static char b[sizeof(COutputIncrementor)];
    TL_CHECK(failures, sizeof(COutputIncrementor) == 0x78);
    originalIncrementorConstruct(a, resources);
    new (b) COutputIncrementor(resources);
    TL_CHECK(failures, std::memcmp(a + 0x58, b + 0x58, 0x20) == 0);
    installRecorder(a);
    *reinterpret_cast<void***>(b) = g_vtable;
    g_logs[0].object = a;
    g_logs[1].object = b;

    for (int step = 0; step < 20000 && failures == 0; step++)
    {
        char fields[0x12];
        unsigned int target = nextRandom() % 9;
        unsigned int count = nextRandom() % 9;
        int repeatCount = int(nextRandom() % 4);
        int repeatsLeft = int(nextRandom() % 6) - 2;
        std::memcpy(fields + 0x00, &target, 4);
        std::memcpy(fields + 0x04, &count, 4);
        std::memcpy(fields + 0x08, &repeatCount, 4);
        std::memcpy(fields + 0x0c, &repeatsLeft, 4);
        fields[0x10] = char(nextRandom() % 2);
        fields[0x11] = char(nextRandom() % 2);
        CResourceManager* manager = (nextRandom() % 8) ? resources : 0;
        setEditorRunning(nextRandom() % 6 == 0);
        std::memcpy(a + 0x58, fields, sizeof(fields));
        std::memcpy(b + 0x58, fields, sizeof(fields));

        g_logs[0].count = g_logs[1].count = 0;
        if (nextRandom() % 4 == 0)
        {
            bool enabled = nextRandom() % 2;
            *reinterpret_cast<CResourceManager**>(a + 0x70) = resources;
            *reinterpret_cast<CResourceManager**>(b + 0x70) = resources;
            originalIncrementorSetEnabled(a, enabled);
            reinterpret_cast<COutputIncrementor*>(b)->setEnabled(enabled);
        }
        else
        {
            *reinterpret_cast<CResourceManager**>(a + 0x70) = manager;
            *reinterpret_cast<CResourceManager**>(b + 0x70) = manager;
            originalIncrement(a);
            reinterpret_cast<COutputIncrementor*>(b)->increment();
        }
        TL_CHECK(failures, sameLogs());
        TL_CHECK(failures, std::memcmp(a + 0x58, b + 0x58, 0x20) == 0);
        if (failures)
            host->log("    step %d\n", step);
    }

    gEditor = savedEditor;
    originalIncrementorDestroy(a);
    reinterpret_cast<COutputIncrementor*>(b)->COutputIncrementor::~COutputIncrementor();
    return failures;
}
