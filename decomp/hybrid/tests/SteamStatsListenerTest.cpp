#include <cstring>
#include <new>
#include "AutoTest.h"
#include "SteamStats.h"

TL_ORIGINAL(void, originalAddStatListener, (CSteamStats*, ESTATS, iStatListener*),
            "_ZN11CSteamStats15addStatListenerE6ESTATSP13iStatListener")
extern "C" void recoveredAddStatListener(CSteamStats*, ESTATS, iStatListener*)
    __asm__("_ZN11CSteamStats15addStatListenerE6ESTATSP13iStatListener");

namespace {
typedef TArrayList<iStatListener*> ListenerList;
typedef CSteamStats::TStatListenerMap ListenerMap;
struct Case { unsigned mask, count, growBy, listener; ESTATS stat; };
unsigned char listenerTokens[4];

iStatListener* listener(unsigned index)
{
    return index ? reinterpret_cast<iStatListener*>(&listenerTokens[index - 1]) : NULL;
}

int identity(iStatListener* value)
{
    for (unsigned i = 0; i <= 4; ++i)
        if (value == listener(i)) return i;
    return -1;
}

void record(autotest::Capture& out, unsigned value)
{
    out.add(&value, sizeof(value));
}

void side(const Case& c, bool ours, autotest::Capture& out)
{
    // Only the map is used by this method; avoid the game's singleton constructor.
    union Storage { long double alignment; char bytes[sizeof(CSteamStats)]; } storage;
    std::memset(storage.bytes, 0, sizeof(storage.bytes));
    CSteamStats* object = reinterpret_cast<CSteamStats*>(storage.bytes);
    ListenerMap& map = *new (&object->m_statListeners) ListenerMap;
    ListenerList lists[3];
    const ESTATS keys[] = { static_cast<ESTATS>(0), static_cast<ESTATS>(15), static_cast<ESTATS>(30) };
    for (unsigned i = 0; i < 3; ++i) {
        lists[i].setGrowBy(c.growBy);
        for (unsigned j = 0; j < c.count; ++j)
            lists[i].add(listener(1 + (i + j) % 3));
        if (c.mask & (1u << i)) map[keys[i]] = &lists[i];
    }

    if (ours) autotest::invoke(out, recoveredAddStatListener, object, c.stat, listener(c.listener));
    else autotest::invoke(out, originalAddStatListener, object, c.stat, listener(c.listener));

    record(out, map.size());
    for (ListenerMap::iterator i = map.begin(); i != map.end(); ++i) {
        record(out, i->first);
        unsigned index = 3;
        for (unsigned j = 0; j < 3; ++j)
            if (i->second == &lists[j]) index = j;
        record(out, index);
    }
    for (unsigned i = 0; i < 3; ++i) {
        // Original list layout: data pointer, count, capacity, growth increment.
        unsigned metadata[3];
        std::memcpy(metadata, reinterpret_cast<char*>(&lists[i]) + sizeof(void*), sizeof(metadata));
        out.add(metadata, sizeof(metadata));
        if (metadata[0] > 64 || metadata[1] > 64) _exit(51);
        for (unsigned j = 0; j < lists[i].size(); ++j)
            record(out, identity(lists[i][j]));
    }
    map.~ListenerMap();
}

void original(void* p, autotest::Capture& out) { side(*static_cast<Case*>(p), false, out); }
void recovered(void* p, autotest::Capture& out) { side(*static_cast<Case*>(p), true, out); }
}

TL_TEST(steamstats_listener_differential)
{
    int failures = 0;
    unsigned cases = 0;
    autotest::Stats stats = {0, 0, 0};
    autotest::Coverage coverage("steamstats_listener_differential", (uint64_t)(uintptr_t)&originalAddStatListener);
    const unsigned masks[] = {0, 5, 2, 7};
    const unsigned counts[] = {0, 1, 2, 5};
    const unsigned listeners[] = {0, 1, 4};
    const ESTATS keys[] = {static_cast<ESTATS>(0), static_cast<ESTATS>(15),
                          static_cast<ESTATS>(30), static_cast<ESTATS>(31)};
    for (unsigned m = 0; m < 4; ++m) for (unsigned k = 0; k < 4; ++k)
    for (unsigned n = 0; n < 4; ++n) for (unsigned grow = 1; grow <= 2; ++grow)
    for (unsigned l = 0; l < 3; ++l) {
        Case c = {masks[m], counts[n], grow, listeners[l], keys[k]};
        bool ok = autotest::compareCase(original, recovered, &c, stats, host,
                                       "steamstats_listener_differential", cases, &coverage);
        TL_CHECK(failures, ok);
        ++cases;
    }
    coverage.report(host);
    return failures + stats.incomplete + (coverage.completed != cases ? 1 : 0);
}
