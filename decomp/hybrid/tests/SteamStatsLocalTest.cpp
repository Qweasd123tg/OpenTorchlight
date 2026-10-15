#include <cstring>
#include <new>
#include "AutoTest.h"
#define private public
#include "SteamStats.h"
#undef private
#include "iStatListener.h"

TL_ORIGINAL(void, oldLocal, (CSteamStats*, float), "_ZN11CSteamStats20checkForLocalUpdatesEf")
extern "C" void newLocal(CSteamStats*, float) __asm__("_ZN11CSteamStats20checkForLocalUpdatesEf");

namespace {
struct Case { unsigned gate, clock, values; };
autotest::Capture* output;
unsigned calls;
class Listener : public iStatListener
{
public:
    virtual ~Listener() {}
    virtual void statChanged(unsigned stat, UNIONDATA32BIT old, UNIONDATA32BIT current)
    {
        ++calls;
        output->add(&stat, sizeof(stat));
        output->add(&old.m_uValue, sizeof(old.m_uValue));
        output->add(&current.m_uValue, sizeof(current.m_uValue));
    }
};
void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    uint64_t storage[(sizeof(CSteamStats) + 7) / 8];
    std::memset(storage, 0xa5, sizeof(storage));
    CSteamStats* self = reinterpret_cast<CSteamStats*>(storage);
    typedef CSteamStats::TStatListenerMap Map;
    Map& map = *new (&self->m_statListeners) Map;
    Listener listener;
    TArrayList<iStatListener*> listeners;
    listeners.add(&listener);
    for (unsigned i = 0; i < 31; ++i)
        if (c.values == 3 || (c.values && (i == 28 || i == 29)))
            map[static_cast<ESTATS>(i)] = &listeners;
    TArrayList<int>* values = new (&self->m_statValues) TArrayList<int>(4);
    int data[31];
    for (unsigned i = 0; i < 31; ++i)
        data[i] = c.values == 0 ? -1 : c.values == 1 ? 0xbf800000 :
                  c.values == 2 ? 0x7fc12345 : static_cast<int>(i * 101);
    values->m_pData = data;
    values->m_nCount = 31;
    values->m_nCapacity = c.values == 3 ? 1 : 31;
    typedef CSteamStats::SStatChange Change;
    TArrayList<Change>* pending = new (&self->m_pendingStatChanges) TArrayList<Change>(4);
    if (c.gate == 4) {
        Change change;
        change.stat = static_cast<ESTATS>(28);
        change.value.m_iValue = 123;
        pending->add(change);
    }
    // The target's fresh ASM directly reads 32-bit player fields at these
    // offsets. This is synthetic storage, never a call to CPlayer's constructor.
    uint64_t playerStorage[0x900 / 8];
    std::memset(playerStorage, 0x5a, sizeof(playerStorage));
    int gold = c.values == 0 ? -1 : 29;
    int level = c.values == 1 ? -1 : 28;
    std::memcpy(reinterpret_cast<char*>(playerStorage) + 0x444, &gold, sizeof(gold));
    std::memcpy(reinterpret_cast<char*>(playerStorage) + 0x7f0, &level, sizeof(level));
    self->m_pPlayer = c.gate == 3 ? NULL : reinterpret_cast<CPlayer*>(playerStorage);
    self->m_bLocalUpdatesEnabled = c.gate != 1;
    self->m_bStatsEnabled = c.gate == 2;
    const unsigned timers[] = {0u, 0x3f800000u, 0x3f000000u, 0xbf800000u,
                               0x7fc12345u, 0x7f800000u, 0xff800000u};
    const unsigned steps[] = {0u, 0x3e800000u, 0x3f000000u, 0xbf800000u,
                              0u, 0x7f800000u, 0u};
    float elapsed;
    std::memcpy(&self->m_fLocalUpdateTimer, &timers[c.clock], sizeof(float));
    std::memcpy(&elapsed, &steps[c.clock], sizeof(float));
    unsigned char playerBefore[sizeof(playerStorage)];
    std::memcpy(playerBefore, playerStorage, sizeof(playerStorage));
    output = &out;
    calls = 0;
    if (ours) autotest::invoke(out, newLocal, self, elapsed);
    else autotest::invoke(out, oldLocal, self, elapsed);
    out.add(&calls, sizeof(calls));
    out.add(&self->m_fLocalUpdateTimer, sizeof(float));
    out.add(data, sizeof(data));
    out.add(&pending->m_nCount, sizeof(pending->m_nCount));
    out.add(&pending->m_nCapacity, sizeof(pending->m_nCapacity));
    out.add(&pending->m_nGrowBy, sizeof(pending->m_nGrowBy));
    unsigned retained = pending->m_pData != NULL;
    out.add(&retained, sizeof(retained));
    if (pending->m_nCount <= 4) out.add(pending->m_pData, pending->m_nCount * sizeof(Change));
    else out.issue = autotest::Capture::InvalidReport;
    unsigned unchanged = std::memcmp(playerBefore, playerStorage, sizeof(playerStorage)) == 0;
    out.add(&unchanged, sizeof(unchanged));
    unsigned size = map.size();
    out.add(&size, sizeof(size));
    pending->~TArrayList<Change>();
    values->m_pData = NULL;
    values->~TArrayList<int>();
    map.~Map();
}
void original(void* raw, autotest::Capture& out) { side(raw, out, false); }
void candidate(void* raw, autotest::Capture& out) { side(raw, out, true); }
}

TL_TEST(steam_stats_local_updates)
{
    autotest::Coverage coverage("steam_stats_local_updates", reinterpret_cast<uintptr_t>(&oldLocal));
    for (unsigned gate = 0; gate < 5; ++gate)
        for (unsigned clock = 0; clock < 7; ++clock)
            for (unsigned values = 0; values < 4; ++values) {
                Case c = {gate, clock, values};
                autotest::Outcome a, b;
                autotest::runChild(original, &c, a);
                autotest::runChild(candidate, &c, b);
                if (coverage.observe(host, a, b)) {
                    host->log("    local gate %u clock %u values %u statuses %d/%d issues %u/%u\n",
                              gate, clock, values, a.childStatus, b.childStatus,
                              a.capture.issue, b.capture.issue);
                    coverage.report(host);
                    return 1;
                }
            }
    coverage.report(host);
    return 0;
}
