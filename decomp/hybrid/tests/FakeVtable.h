// Fake polymorphic objects for shadow tests: every vtable slot records the call
// (object, slot, first two integer arguments) and returns a per-object value.
// Both implementations run against the same fakes, so their call logs compare.
#ifndef FAKEVTABLE_H
#define FAKEVTABLE_H

#include <cstring>

namespace fake
{

const int kSlots = 128;
const int kMaxCalls = 64;

struct Call
{
    const void* object;
    int slot;
    unsigned long a1;
    unsigned long a2;
};

struct Log
{
    Call calls[kMaxCalls];
    int count;

    void clear()
    {
        std::memset(this, 0, sizeof(*this));
    }

    bool operator==(const Log& other) const
    {
        return count == other.count && std::memcmp(calls, other.calls, count * sizeof(Call)) == 0;
    }
};

// Object whose vptr points at the recording table. The zeroed body stands in
// for fields that non-virtual library code may read.
struct Object
{
    void** vptr;
    char body[0x400];
    void* results[kSlots];
};

inline Log*& currentLog()
{
    static Log* log = 0;
    return log;
}

// Integer arguments recorded per slot; registers past them hold garbage.
inline int* argumentCounts()
{
    static int counts[kSlots];
    return counts;
}

inline void setArguments(int offset, int count)
{
    argumentCounts()[offset / 8] = count;
}

template <int N>
void* slotThunk(Object* self, unsigned long a1, unsigned long a2)
{
    Log* log = currentLog();
    if (log && log->count < kMaxCalls)
    {
        Call& call = log->calls[log->count++];
        call.object = self;
        call.slot = N;
        int arguments = argumentCounts()[N];
        call.a1 = arguments > 0 ? a1 : 0;
        call.a2 = arguments > 1 ? a2 : 0;
    }
    return self->results[N];
}

typedef void* (*Thunk)(Object*, unsigned long, unsigned long);

template <int N>
struct Filler
{
    static void fill(void** table)
    {
        Thunk thunk = &slotThunk<N>;
        table[N] = reinterpret_cast<void*>(thunk);
        Filler<N - 1>::fill(table);
    }
};

template <>
struct Filler<-1>
{
    static void fill(void**) {}
};

inline void** table()
{
    static void* slots[kSlots];
    if (!slots[0])
        Filler<kSlots - 1>::fill(slots);
    return slots;
}

inline void init(Object& object)
{
    std::memset(&object, 0, sizeof(object));
    object.vptr = table();
}

// Result of the virtual method at byte offset `offset` in the vtable.
inline void setResult(Object& object, int offset, const void* value)
{
    object.results[offset / 8] = const_cast<void*>(value);
}

} // namespace fake

#endif
