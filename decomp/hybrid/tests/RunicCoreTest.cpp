// Shadow test: the decompiled CRunicCore against the original machine code,
// inside the real game process (real NedAlloc heap and libstdc++), before hooks.
#include <new>

#include "HybridTest.h"
#include "RunicCore.h"

TL_ORIGINAL(void, originalConstruct, (CRunicCore*), "_ZN10CRunicCoreC1Ev")
TL_ORIGINAL(void, originalDestroy, (CRunicCore*), "_ZN10CRunicCoreD1Ev")
TL_ORIGINAL(unsigned int, originalAdd, (CRunicCore*, TSafePointer<void*>*),
            "_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_ORIGINAL(void, originalRemove, (CRunicCore*, TSafePointer<void*>*, unsigned int),
            "_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")

namespace
{

// Raw layouts used only to observe both implementations identically.
struct ArrayView
{
    void** data;
    unsigned int count;
    unsigned int capacity;
    unsigned int growBy;
};

struct CoreView
{
    void* vptr;
    ArrayView* pointers;
};

struct PointerView
{
    void* object;
    unsigned int index;
};

const int kSlots = 48;

struct Side
{
    CRunicCore* core;
    PointerView slots[kSlots];
    bool active[kSlots];
};

unsigned int g_seed = 12345;

unsigned int nextRandom()
{
    g_seed = g_seed * 1103515245u + 12345u;
    return g_seed >> 8;
}

int compare(const tlhybrid_host* host, const Side& a, const Side& b, int step)
{
    int failures = 0;
    const CoreView* ca = reinterpret_cast<const CoreView*>(a.core);
    const CoreView* cb = reinterpret_cast<const CoreView*>(b.core);
    TL_CHECK(failures, ca->vptr == cb->vptr);
    TL_CHECK(failures, (ca->pointers == 0) == (cb->pointers == 0));
    if (ca->pointers && cb->pointers)
    {
        TL_CHECK(failures, ca->pointers->count == cb->pointers->count);
        TL_CHECK(failures, ca->pointers->capacity == cb->pointers->capacity);
        TL_CHECK(failures, ca->pointers->growBy == cb->pointers->growBy);
        for (unsigned int i = 0; i < ca->pointers->count && i < cb->pointers->count; i++)
        {
            long ka = reinterpret_cast<PointerView*>(ca->pointers->data[i]) - a.slots;
            long kb = reinterpret_cast<PointerView*>(cb->pointers->data[i]) - b.slots;
            TL_CHECK(failures, ka == kb);
        }
    }
    for (int k = 0; k < kSlots; k++)
    {
        TL_CHECK(failures, a.active[k] == b.active[k]);
        TL_CHECK(failures, a.slots[k].index == b.slots[k].index);
        TL_CHECK(failures, (a.slots[k].object == a.core) == (b.slots[k].object == b.core));
    }
    if (failures)
        host->log("    diverged at step %d\n", step);
    return failures;
}

void addOriginal(Side& s, int k)
{
    s.slots[k].index = originalAdd(s.core, reinterpret_cast<TSafePointer<void*>*>(&s.slots[k]));
    s.slots[k].object = s.core;
    s.active[k] = true;
}

void addDecomp(Side& s, int k)
{
    s.slots[k].index = s.core->addSafePointer(reinterpret_cast<TSafePointer<void*>*>(&s.slots[k]));
    s.slots[k].object = s.core;
    s.active[k] = true;
}

void removeOriginal(Side& s, int k, unsigned int index)
{
    originalRemove(s.core, reinterpret_cast<TSafePointer<void*>*>(&s.slots[k]), index);
    if (s.active[k] && index == s.slots[k].index)
    {
        s.slots[k].object = 0;
        s.slots[k].index = 0xFFFFFFFF;
        s.active[k] = false;
    }
}

void removeDecomp(Side& s, int k, unsigned int index)
{
    s.core->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&s.slots[k]), index);
    if (s.active[k] && index == s.slots[k].index)
    {
        s.slots[k].object = 0;
        s.slots[k].index = 0xFFFFFFFF;
        s.active[k] = false;
    }
}

void reset(Side& s)
{
    for (int k = 0; k < kSlots; k++)
    {
        s.slots[k].object = 0;
        s.slots[k].index = 0xFFFFFFFF;
        s.active[k] = false;
    }
}

} // namespace

TL_TEST(RunicCore_shadow)
{
    int failures = 0;
    for (int round = 0; round < 64; round++)
    {
        Side a, b;
        reset(a);
        reset(b);
        int counterBefore = g_iTotalCountOfObjects;
        a.core = static_cast<CRunicCore*>(::operator new(sizeof(CRunicCore)));
        originalConstruct(a.core);
        b.core = new (::operator new(sizeof(CRunicCore))) CRunicCore();
        TL_CHECK(failures, g_iTotalCountOfObjects == counterBefore + 2);

        // Removal before any registration and with an invalid index.
        removeOriginal(a, 0, 0xFFFFFFFF);
        removeDecomp(b, 0, 0xFFFFFFFF);
        removeOriginal(a, 0, 0);
        removeDecomp(b, 0, 0);
        failures += compare(host, a, b, -1);

        for (int step = 0; step < 400 && failures == 0; step++)
        {
            int k = nextRandom() % kSlots;
            unsigned int op = nextRandom() % 8;
            if (op < 4 && !a.active[k])
            {
                addOriginal(a, k);
                addDecomp(b, k);
            }
            else if (op < 7 && a.active[k])
            {
                unsigned int index = a.slots[k].index;
                removeOriginal(a, k, index);
                removeDecomp(b, k, index);
            }
            else
            {
                // Stale or out-of-range index: both must ignore it.
                unsigned int index = 1000 + nextRandom() % 16;
                removeOriginal(a, k, index);
                removeDecomp(b, k, index);
            }
            failures += compare(host, a, b, step);
        }

        originalDestroy(a.core);
        b.core->CRunicCore::~CRunicCore();
        for (int k = 0; k < kSlots; k++)
        {
            // Destruction invalidates every registered safe pointer.
            TL_CHECK(failures, a.slots[k].index == b.slots[k].index);
            TL_CHECK(failures, a.slots[k].object == 0 || !a.active[k]);
            TL_CHECK(failures, b.slots[k].object == 0 || !b.active[k]);
        }
        TL_CHECK(failures, reinterpret_cast<CoreView*>(a.core)->pointers == 0);
        TL_CHECK(failures, reinterpret_cast<CoreView*>(b.core)->pointers == 0);
        ::operator delete(a.core);
        ::operator delete(b.core);
        if (failures)
            break;
    }
    return failures;
}
