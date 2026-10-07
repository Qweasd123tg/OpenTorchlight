// Compare the owner-chain walk, journal call and saturated gold arithmetic.
#include <climits>
#include <cstring>
#include "AutoTest.h"
#include "Detour.h"
#include "Character.h"

TL_ORIGINAL(void, originalCharacterGold, (CCharacter*, int), "_ZN10CCharacter8giveGoldEi")
extern "C" void recoveredCharacterGold(CCharacter*, int) __asm__("_ZN10CCharacter8giveGoldEi");
TL_FUNCTION(goldJournal, "_ZN10CCharacter25incrementJournalStatisticE17EJournalStatistici")

namespace
{
struct Case
{
    unsigned int depth;
    int gold;
    int amount;
    unsigned int journalMode;
};

autotest::Capture* capture;
unsigned int journalMode;

void journal(CCharacter* character, EJournalStatistic statistic, int amount)
{
    capture->addPointer(character);
    capture->add(&statistic, sizeof(statistic));
    capture->add(&amount, sizeof(amount));
    char* gold = reinterpret_cast<char*>(character) + 0x444;
    capture->add(gold, sizeof(int));
    // A collaborator can alter the balance. The caller must reload it.
    if (journalMode)
    {
        int changed = journalMode == 1 ? 0 : INT_MAX - 1;
        std::memcpy(gold, &changed, sizeof(changed));
    }
}

void side(Case& input, bool ours, autotest::Capture& out)
{
    autotest::g_arenaUsed = 0;
    CCharacter* characters[4];
    for (unsigned int i = 0; i < 4; ++i)
    {
        characters[i] = static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));
        if (!characters[i])
            _exit(40);
        std::memset(characters[i], 0xa5, sizeof(CCharacter));
    }
    for (unsigned int i = 0; i < 4; ++i)
    {
        char* bytes = reinterpret_cast<char*>(characters[i]);
        CCharacter* master = i < input.depth ? characters[i + 1] : 0;
        int gold = i == input.depth ? input.gold : 100 + static_cast<int>(i);
        std::memcpy(bytes + 0x640, &master, sizeof(master));
        std::memcpy(bytes + 0x444, &gold, sizeof(gold));
    }

    capture = &out;
    journalMode = input.journalMode;
    detour::Set patches;
    TL_REDIRECT(patches, goldJournal, &journal);
    if (patches.failed())
        _exit(41);
    autotest::invoke(out, ours ? recoveredCharacterGold : originalCharacterGold,
                     characters[0], input.amount);
    // Includes every balance and all untouched bytes, including chain links.
    out.add(autotest::g_arena, autotest::g_arenaUsed);
}

void original(void* input, autotest::Capture& out)
{
    side(*static_cast<Case*>(input), false, out);
}

void recovered(void* input, autotest::Capture& out)
{
    side(*static_cast<Case*>(input), true, out);
}
}

TL_TEST(character_gold_differential)
{
    const unsigned int depths[] = {0, 1, 3};
    const int balances[] = {0, 1, 17, INT_MAX - 1, INT_MAX, -1, -17, INT_MIN};
    const int amounts[] = {0, 1, 2, 17, -1, -17, INT_MAX, INT_MIN, INT_MIN + 1};
    autotest::Stats stats = {};
    autotest::Coverage coverage("character_gold_differential",
                               static_cast<uint64_t>(reinterpret_cast<uintptr_t>(&originalCharacterGold)));
    int failures = 0;
    int cases = 0;
    for (unsigned int d = 0; d < sizeof(depths) / sizeof(depths[0]); ++d)
        for (unsigned int g = 0; g < sizeof(balances) / sizeof(balances[0]); ++g)
            for (unsigned int a = 0; a < sizeof(amounts) / sizeof(amounts[0]); ++a)
                for (unsigned int mode = 0; mode < 3; ++mode)
                {
                    Case input = {depths[d], balances[g], amounts[a], mode};
                    bool same = autotest::compareCase(original, recovered, &input, stats, host,
                                                       "character_gold_differential", cases++, &coverage);
                    TL_CHECK(failures, same);
                }
    coverage.report(host);
    host->log("    character gold: %d cases, same %d, different %d, incomplete %d\n",
              cases, stats.same, stats.different, stats.incomplete);
    return failures + (coverage.completed != static_cast<unsigned int>(cases) ? 1 : 0);
}
