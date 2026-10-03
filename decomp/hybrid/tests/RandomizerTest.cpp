// Shadow test: decompiled CRandomizer against the original machine code on a
// random sequence of operations. Both sides get the same RNG seed before each
// roll, and the full object state is compared after every step.
#include <cstring>
#include <new>

#include "HybridTest.h"
#include "Randomizer.h"
#include "Utilities.h"

TL_ORIGINAL(void, originalConstruct, (void*, ERANDOMIZER_TYPE), "_ZN11CRandomizerC1E16ERANDOMIZER_TYPE")
TL_ORIGINAL(void, originalDestroy, (void*), "_ZN11CRandomizerD1Ev")
TL_ORIGINAL(int, originalGetOdds, (void*, int), "_ZN11CRandomizer7getOddsEi")
TL_ORIGINAL(void, originalSetChoiceOdds, (void*, int, int), "_ZN11CRandomizer13setChoiceOddsEii")
TL_ORIGINAL(void, originalRemoveChoice, (void*, unsigned int), "_ZN11CRandomizer12removeChoiceEj")
TL_ORIGINAL(void, originalClear, (void*), "_ZN11CRandomizer5clearEv")
TL_ORIGINAL(int, originalAddChoice, (void*, int, int), "_ZN11CRandomizer9addChoiceEii")
TL_ORIGINAL(void, originalComputeOdds, (void*), "_ZN11CRandomizer11computeOddsEv")
TL_ORIGINAL(void, originalSetToNormal, (void*, float), "_ZN11CRandomizer21setRandomizerToNormalEf")
TL_ORIGINAL(int, originalGetRandomIndex, (void*, int&), "_ZN11CRandomizer9getRandomERi")
TL_ORIGINAL(int, originalGetRandom, (void*), "_ZN11CRandomizer9getRandomEv")
TL_ORIGINAL(bool, originalHasValidChoices, (void*), "_ZN11CRandomizer15hasValidChoicesEv")

namespace
{

unsigned int g_seed = 4242;

unsigned int nextRandom()
{
    g_seed = g_seed * 1103515245u + 12345u;
    return g_seed >> 8;
}

// Raw view of one TArrayList member: data, count, capacity, growBy.
struct ListView
{
    const unsigned int* data;
    unsigned int count;
    unsigned int capacity;
    unsigned int growBy;
};

ListView listAt(const char* object, int offset)
{
    ListView view;
    std::memcpy(&view.data, object + offset, sizeof(view.data));
    std::memcpy(&view.count, object + offset + 8, 4);
    std::memcpy(&view.capacity, object + offset + 12, 4);
    std::memcpy(&view.growBy, object + offset + 16, 4);
    return view;
}

bool sameList(const char* a, const char* b, int offset)
{
    ListView x = listAt(a, offset);
    ListView y = listAt(b, offset);
    if (x.count != y.count || x.capacity != y.capacity || x.growBy != y.growBy)
        return false;
    if ((x.data == 0) != (y.data == 0))
        return false;
    return x.count == 0 || std::memcmp(x.data, y.data, x.count * 4) == 0;
}

// Makes the first computed odd equal the roll the next getRandom will draw,
// so the comparison against the running sum hits its boundary.
void forceBoundary(char* a, char* b, int seed)
{
    UTILITIES::setSeed(seed);
    float roll = UTILITIES::randomBetween(0.0f, 1.0f);
    originalComputeOdds(a);
    reinterpret_cast<CRandomizer*>(b)->computeOdds();
    ListView x = listAt(a, 0x40);
    ListView y = listAt(b, 0x40);
    if (x.count == 0 || y.count == 0)
        return;
    std::memcpy(const_cast<unsigned int*>(x.data), &roll, 4);
    std::memcpy(const_cast<unsigned int*>(y.data), &roll, 4);
}

bool sameState(const char* a, const char* b)
{
    return sameList(a, b, 0x10) && sameList(a, b, 0x28) && sameList(a, b, 0x40) &&
           std::memcmp(a + 0x58, b + 0x58, 9) == 0;
}

} // namespace

TL_TEST(Randomizer_shadow)
{
    int failures = 0;
    static char a[sizeof(CRandomizer)];
    static char b[sizeof(CRandomizer)];
    TL_CHECK(failures, sizeof(CRandomizer) == 0x68);

    for (int round = 0; round < 200 && failures == 0; round++)
    {
        ERANDOMIZER_TYPE type = ERANDOMIZER_TYPE(nextRandom() % 2);
        originalConstruct(a, type);
        CRandomizer* ours = new (b) CRandomizer(type);
        TL_CHECK(failures, sameState(a, b));
        if (type == RANDOMIZER_DECAY)
        {
            float decay = float(nextRandom() % 100) / 100.0f;
            std::memcpy(a + 0x5c, &decay, 4);
            std::memcpy(b + 0x5c, &decay, 4);
        }

        for (int step = 0; step < 300 && failures == 0; step++)
        {
            unsigned int op = nextRandom() % 16;
            // getOdds and a decaying miss in getRandom touch odds[0]; the
            // original crashes there too when the list has no storage.
            if ((op == 7 || (op >= 10 && op <= 14)) && listAt(a, 0x28).data == 0)
                op = 0;
            int choice = int(nextRandom() % 12) - 2;
            int odds = int(nextRandom() % 50) - 5;
            int seed = int(nextRandom() % 100000) + 1;
            switch (op)
            {
            case 0: case 1: case 2: case 3:
                TL_CHECK(failures, originalAddChoice(a, choice, odds) == ours->addChoice(choice, odds));
                break;
            case 4:
                originalSetChoiceOdds(a, choice, odds);
                ours->setChoiceOdds(choice, odds);
                break;
            case 5:
                originalRemoveChoice(a, unsigned(choice));
                ours->removeChoice(unsigned(choice));
                break;
            case 6:
                if (nextRandom() % 4 == 0)
                {
                    originalClear(a);
                    ours->clear();
                }
                break;
            case 7:
            {
                // Slots between count and capacity are uninitialized; read
                // live slots or out-of-capacity ones (which map to slot 0).
                if (choice >= 0 && unsigned(choice) >= listAt(a, 0x28).count)
                    choice = (nextRandom() % 2) ? 1000 : 0;
                int oddsA = originalGetOdds(a, choice);
                int oddsB = ours->getOdds(choice);
                TL_CHECK(failures, oddsA == oddsB);
                if (oddsA != oddsB)
                    host->log("    getOdds(%d): %d vs %d count %u cap %u\n", choice, oddsA, oddsB,
                              listAt(a, 0x28).count, listAt(a, 0x28).capacity);
            }
                break;
            case 8:
                originalComputeOdds(a);
                ours->computeOdds();
                break;
            case 9:
            {
                float value = float(odds) / 4.0f;
                originalSetToNormal(a, value);
                ours->setRandomizerToNormal(value);
                break;
            }
            case 10: case 11: case 12:
            {
                if (nextRandom() % 3 == 0)
                    forceBoundary(a, b, seed);
                int indexA = 12345;
                int indexB = 12345;
                UTILITIES::setSeed(seed);
                int resultA = originalGetRandomIndex(a, indexA);
                UTILITIES::setSeed(seed);
                int resultB = ours->getRandom(indexB);
                TL_CHECK(failures, resultA == resultB && indexA == indexB);
                break;
            }
            case 13: case 14:
            {
                if (nextRandom() % 3 == 0)
                    forceBoundary(a, b, seed);
                UTILITIES::setSeed(seed);
                int resultA = originalGetRandom(a);
                UTILITIES::setSeed(seed);
                TL_CHECK(failures, resultA == ours->getRandom());
                break;
            }
            default:
                TL_CHECK(failures, originalHasValidChoices(a) == ours->hasValidChoices());
                break;
            }
            TL_CHECK(failures, sameState(a, b));
            if (failures)
                host->log("    round %d step %d op %u\n", round, step, op);
        }
        originalDestroy(a);
        ours->~CRandomizer();
    }
    return failures;
}
