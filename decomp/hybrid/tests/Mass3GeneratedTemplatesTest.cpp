#include <vector>
#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*, void*), "_ZN10TArrayListIP13CEquipmentRefE3addES1_")
extern "C" void candidate0(void*, void*) __asm__("_ZN10TArrayListIP13CEquipmentRefE3addES1_");
TL_ORIGINAL(void, original1, (void*, std::_Bit_iterator, bool), "_ZNSt6vectorIbSaIbEE13_M_insert_auxESt13_Bit_iteratorb")
extern "C" void candidate1(void*, std::_Bit_iterator, bool) __asm__("_ZNSt6vectorIbSaIbEE13_M_insert_auxESt13_Bit_iteratorb");

#include "TArrayList.h"
class CEquipmentRef;

namespace {
using namespace smallmass;

// These two weak template bodies are emitted by the new production callers.
// Invoke those linked bodies directly, without instantiating add/insert here.
void execute(Case& c, bool ours, autotest::Capture& out)
{
    input = &c;
    output = &out;
    autotest::g_arenaUsed = 0;
    if (c.op == 0)
    {
        const unsigned sizes[] = {0, 1, 2, 3, 7, 16, 31, 63};
        const unsigned growth[] = {1, 2, 3, 10};
        unsigned count = sizes[c.index % 8];
        unsigned grow = growth[(c.index / 8) % 4];
        unsigned spare = (c.index / 32) % 3;
        unsigned capacity = count + spare;
        TArrayList<CEquipmentRef*> list(grow);
        CEquipmentRef** data = capacity || c.index & 128
            ? new CEquipmentRef*[capacity] : NULL;
        for (unsigned i = 0; i < capacity; ++i)
            data[i] = (i + c.index) % 5
                ? static_cast<CEquipmentRef*>(object(8)) : NULL;
        field<CEquipmentRef**>(&list, 0) = data;
        field<unsigned>(&list, 8) = count;
        field<unsigned>(&list, 12) = capacity;
        void* value = c.index % 3 ? object(8) : NULL;
        autotest::invoke(out, ours ? candidate0 : original0,
                         static_cast<void*>(&list), value);
        number(field<unsigned>(&list, 8));
        number(field<unsigned>(&list, 12));
        number(field<unsigned>(&list, 16));
        CEquipmentRef** result = field<CEquipmentRef**>(&list, 0);
        number(result == data);
        if (field<unsigned>(&list, 8) != count + 1
            || field<unsigned>(&list, 12) > 128) _exit(42);
        // Initialized spare slots must also survive an append without growth.
        unsigned initialized = capacity > count + 1 ? capacity : count + 1;
        for (unsigned i = 0; i < initialized; ++i) pointer(result[i]);
    }
    else
    {
        const unsigned sizes[] = {0, 1, 2, 31, 63, 64, 65, 127, 128, 129};
        unsigned count = sizes[c.index % 10];
        std::vector<bool> bits(count, false);
        if ((c.index / 10) % 2) bits.reserve(count + 65);
        for (unsigned i = 0; i < count; ++i)
            bits[i] = ((i * 13 + c.index * 7) % 11) < 5;
        unsigned position = (c.index / 20) % 3 == 0 ? 0
            : (c.index / 20) % 3 == 1 ? count / 2 : count;
        std::_Bit_iterator where = bits.begin() + position;
        autotest::invoke(out, ours ? candidate1 : original1,
                         static_cast<void*>(&bits), where,
                         bool((c.index / 60) % 2));
        number(bits.size());
        number(bits.capacity());
        if (bits.size() != count + 1 || bits.capacity() > 512) _exit(43);
        for (unsigned i = 0; i < bits.size(); ++i) number(bits[i]);
    }
}
}
TL_TEST(mass3_926260) { return smallmass::run(host,0,"mass3_926260",(uint64_t)(uintptr_t)original0,execute,192); }
TL_TEST(mass3_85ad10) { return smallmass::run(host,1,"mass3_85ad10",(uint64_t)(uintptr_t)original1,execute,240); }
