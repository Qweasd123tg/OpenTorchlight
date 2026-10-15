#include <cstring>
#include "AutoTest.h"
#include "Detour.h"
#include "Achievement.h"
#include "Achievements.h"
#include "SteamStats.h"

TL_ORIGINAL(ESTATS, oldType, (CAchievement*), "_ZN12CAchievement11getStatTypeEv")
extern "C" ESTATS newType(CAchievement*) __asm__("_ZN12CAchievement11getStatTypeEv");
TL_ORIGINAL(void, oldCheck, (CAchievement*), "_ZN12CAchievement16checkForAchievedEv")
extern "C" void newCheck(CAchievement*) __asm__("_ZN12CAchievement16checkForAchievedEv");
TL_FUNCTION(statsSingleton, "_ZN11CSteamStats12getSingletonEv")
TL_FUNCTION(readInt, "_ZN11CSteamStats10getStatIntE6ESTATS")
TL_FUNCTION(readFloat, "_ZN11CSteamStats12getStatFloatE6ESTATS")
TL_FUNCTION(achievementSingleton, "_ZN13CAchievements12getSingletonEv")
TL_FUNCTION(complete, "_ZN13CAchievements22setAchievementCompleteEP12CAchievement")

namespace {
struct Case { int stat; unsigned type, scenario; bool typeOnly; };
autotest::Capture* output;
CAchievement* active;
unsigned scenario;
uint64_t statsStorage[8], managerStorage[8];
void number(unsigned value) { output->add(&value, sizeof(value)); }
void invalid() { output->issue = autotest::Capture::InvalidReport; }
CSteamStats* singleton()
{
    number(1);
    if (scenario == 5) {
        active->m_bAchieved = true;
        active->m_eStatType = static_cast<ESTATS>(29);
    }
    return reinterpret_cast<CSteamStats*>(statsStorage);
}
int integer(CSteamStats* self, ESTATS stat)
{
    number(2); number(stat);
    if (self != reinterpret_cast<CSteamStats*>(statsStorage)) invalid();
    if (scenario == 6) {
        active->m_bAchieved = true;
        active->m_eStatType = static_cast<ESTATS>(29);
        int maximum = 0x7fffffff;
        std::memcpy(&active->m_fRequiredValue, &maximum, sizeof(maximum));
    }
    const int values[] = {-1, 0, 1, static_cast<int>(0x80000000u), 0x7fffffff, -1, -1, 0};
    return values[scenario];
}
float floating(CSteamStats* self, ESTATS stat)
{
    number(3); number(stat);
    if (self != reinterpret_cast<CSteamStats*>(statsStorage)) invalid();
    if (scenario == 5 || scenario == 6) {
        unsigned nan = 0x7fc12345;
        std::memcpy(&active->m_fRequiredValue, &nan, sizeof(nan));
        active->m_eStatType = static_cast<ESTATS>(29);
        if (scenario == 6) active->m_bAchieved = true;
    }
    const unsigned values[] = {0xbf800000u, 0u, 0x7f800000u, 0x7fc98765u,
                                0x3f800000u, 0xbf800000u, 0xbf800000u, 0u};
    float value;
    std::memcpy(&value, &values[scenario], sizeof(value));
    return value;
}
CAchievements* manager()
{
    number(4);
    if (scenario == 6) active->m_bAchieved = false;
    return reinterpret_cast<CAchievements*>(managerStorage);
}
void completed(CAchievements* self, CAchievement* achievement)
{
    number(5);
    if (self != reinterpret_cast<CAchievements*>(managerStorage) || achievement != active) invalid();
    active->m_fCurrentValue = 123.5f;
}
void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    output = &out;
    scenario = c.scenario;
    uint64_t storage[(sizeof(CAchievement) + 7) / 8];
    std::memset(storage, 0xa5, sizeof(storage));
    active = reinterpret_cast<CAchievement*>(storage);
    active->m_eStatType = static_cast<ESTATS>(c.stat);
    active->m_bAchieved = c.scenario == 7;
    const unsigned intRequired[] = {0u, 0u, 0u, 0x7fffffffu, 0x80000000u, 1u, 0u, 0u};
    const unsigned floatRequired[] = {0u, 0x80000000u, 0u, 0xbf800000u, 0x7fc12345u, 0u, 0u, 0u};
    unsigned bits = c.type == 1 ? floatRequired[c.scenario] : intRequired[c.scenario];
    std::memcpy(&active->m_fRequiredValue, &bits, sizeof(bits));
    // Packet-provided STT_OBJECT local to Achievement.cpp, never file mutation.
    unsigned char* definitions = reinterpret_cast<unsigned char*>(0x1538e20);
    for (unsigned i = 0; i < 31; ++i)
        std::memcpy(definitions + i * 24 + 4, &c.type, sizeof(c.type));
    detour::Set patches;
    TL_REDIRECT(patches, statsSingleton, &singleton);
    TL_REDIRECT(patches, readInt, &integer);
    TL_REDIRECT(patches, readFloat, &floating);
    TL_REDIRECT(patches, achievementSingleton, &manager);
    TL_REDIRECT(patches, complete, &completed);
    if (patches.failed()) { invalid(); return; }
    if (c.typeOnly) {
        if (ours) autotest::invoke(out, newType, active);
        else autotest::invoke(out, oldType, active);
    } else {
        if (ours) autotest::invoke(out, newCheck, active);
        else autotest::invoke(out, oldCheck, active);
    }
    out.add(storage, sizeof(storage));
    out.add(definitions, 744);
}
void original(void* raw, autotest::Capture& out) { side(raw, out, false); }
void candidate(void* raw, autotest::Capture& out) { side(raw, out, true); }
int run(const tlhybrid_host* host, bool typeOnly, const char* name, uintptr_t address)
{
    autotest::Coverage coverage(name, address);
    const int keys[] = {0, 1, 15, 29, 30, 31, 0x7fffffff};
    for (unsigned k = 0; k < 7; ++k)
        for (unsigned type = 0; type < 3; ++type)
            for (unsigned scenario = 0; scenario < (typeOnly ? 1u : 8u); ++scenario) {
                Case c = {keys[k], type, scenario, typeOnly};
                autotest::Outcome a, b;
                autotest::runChild(original, &c, a);
                autotest::runChild(candidate, &c, b);
                if (coverage.observe(host, a, b)) {
                    host->log("    %s key %d type %u scenario %u exits %d/%d issues %u/%u\n",
                              name, c.stat, type, scenario, a.childStatus, b.childStatus,
                              a.capture.issue, b.capture.issue);
                    coverage.report(host);
                    return 1;
                }
            }
    coverage.report(host);
    return 0;
}
}

TL_TEST(achievement_stat_type)
{
    return run(host, true, "achievement_stat_type", reinterpret_cast<uintptr_t>(&oldType));
}
TL_TEST(achievement_check_achieved)
{
    return run(host, false, "achievement_check_achieved", reinterpret_cast<uintptr_t>(&oldCheck));
}
