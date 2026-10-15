#include <cstring>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "Achievement.h"
#include "SteamStats.h"

TL_ORIGINAL(void, oldFloatCtor, (CAchievement*, std::string, ESTATS, float, float),
            "_ZN12CAchievementC1ESs6ESTATSff")
TL_ORIGINAL(void, oldIntCtor, (CAchievement*, std::string, ESTATS, int, int),
            "_ZN12CAchievementC1ESs6ESTATSii")
extern "C" void newFloatCtor(CAchievement*, std::string, ESTATS, float, float)
    __asm__("_ZN12CAchievementC1ESs6ESTATSff");
extern "C" void newIntCtor(CAchievement*, std::string, ESTATS, int, int)
    __asm__("_ZN12CAchievementC1ESs6ESTATSii");
extern "C" char achievementVtable[] __asm__("_ZTV12CAchievement");
TL_FUNCTION(statsSingletonCtor, "_ZN11CSteamStats12getSingletonEv")
TL_FUNCTION(registerListener, "_ZN11CSteamStats15addStatListenerE6ESTATSP13iStatListener")

namespace {
struct Case { unsigned name, pair; bool floating; };
autotest::Capture* output;
CAchievement* active;
uint64_t statsStorage[8];
unsigned registrations;
void number(unsigned value) { output->add(&value, sizeof(value)); }
void invalid() { output->issue = autotest::Capture::InvalidReport; }
CSteamStats* singleton()
{
    number(1);
    return reinterpret_cast<CSteamStats*>(statsStorage);
}
void added(CSteamStats* self, ESTATS stat, iStatListener* listener)
{
    number(2); number(stat);
    ++registrations;
    if (self != reinterpret_cast<CSteamStats*>(statsStorage) ||
        listener != static_cast<iStatListener*>(active)) invalid();
    unsigned offset = reinterpret_cast<char*>(listener) - reinterpret_cast<char*>(active);
    number(offset);
    // Registration happens after every data member is initialized.
    output->addText(active->m_strName);
    output->add(&active->m_bAchieved, sizeof(active->m_bAchieved));
    output->add(&active->m_eStatType, sizeof(active->m_eStatType));
    output->add(&active->m_fCurrentValue, sizeof(float));
    output->add(&active->m_fRequiredValue, sizeof(float));
}
void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    output = &out;
    registrations = 0;
    uint64_t storage[(sizeof(CAchievement) + 7) / 8];
    std::memset(storage, 0xa5, sizeof(storage));
    active = reinterpret_cast<CAchievement*>(storage);
    std::string name;
    if (c.name == 1) name = "Achievement";
    if (c.name == 2) name.assign("prefix\0suffix", 13);
    if (c.name == 3) { name.assign(96, 'x'); name[48] = '\xff'; }
    const int keys[] = {0, 30, 31, -1};
    ESTATS stat = static_cast<ESTATS>(keys[(c.name + c.pair) % 4]);
    const unsigned floatPairs[][2] = {
        {0u, 0x3f800000u}, {0x3f800000u, 0u},
        {0u, 0x80000000u}, {0x80000000u, 0u},
        {0x7fc12345u, 0x3f800000u}, {0x3f800000u, 0x7fc98765u},
        {0x7fc12345u, 0x7fc98765u}, {0x7f800000u, 0xff800000u},
        {0xff800000u, 0x7f800000u}, {0x7f7fffffu, 1u}
    };
    const int intPairs[][2] = {
        {0, 1}, {1, 0}, {-1, 0},
        {static_cast<int>(0x80000000u), 0x7fffffff},
        {0x7fffffff, static_cast<int>(0x80000000u)}, {5, 5},
        {static_cast<int>(0x80000000u), static_cast<int>(0x80000000u)},
        {0x3f800000, static_cast<int>(0xbf800000u)}
    };
    detour::Set patches;
    TL_REDIRECT(patches, statsSingletonCtor, &singleton);
    TL_REDIRECT(patches, registerListener, &added);
    if (patches.failed()) { invalid(); return; }
    g_iTotalCountOfObjects = 100;
    if (c.floating) {
        float current, required;
        std::memcpy(&current, &floatPairs[c.pair][0], sizeof(current));
        std::memcpy(&required, &floatPairs[c.pair][1], sizeof(required));
        typedef void (*Fn)(CAchievement*, std::string, ESTATS, float, float);
        Fn fn = ours ? newFloatCtor : oldFloatCtor;
        if (!autotest::beginInvocation(out, fn)) return;
        fn(active, name, stat, current, required);
    } else {
        typedef void (*Fn)(CAchievement*, std::string, ESTATS, int, int);
        Fn fn = ours ? newIntCtor : oldIntCtor;
        if (!autotest::beginInvocation(out, fn)) return;
        fn(active, name, stat, intPairs[c.pair][0], intPairs[c.pair][1]);
    }
    out.callCompleted = 1;
    number(registrations);
    number(g_iTotalCountOfObjects);
    // Compiler-owned vptrs are compared against the packet's two address points.
    void* primary;
    void* secondary;
    void* safePointers;
    std::memcpy(&primary, storage, sizeof(primary));
    std::memcpy(&safePointers, reinterpret_cast<char*>(storage) + 8, sizeof(safePointers));
    std::memcpy(&secondary, reinterpret_cast<char*>(storage) + 16, sizeof(secondary));
    unsigned primaryOk = primary == achievementVtable + 16;
    unsigned secondaryOk = secondary == achievementVtable + 56;
    unsigned safeOk = safePointers == NULL;
    number(primaryOk); number(secondaryOk); number(safeOk);
    if (!primaryOk || !secondaryOk || !safeOk) invalid();
    out.addText(active->m_strName);
    out.addText(name);
    // Include untouched padding around the achieved flag as a write canary.
    out.add(reinterpret_cast<char*>(storage) + 32, sizeof(CAchievement) - 32);
    active->~CAchievement();
}
void original(void* raw, autotest::Capture& out) { side(raw, out, false); }
void candidate(void* raw, autotest::Capture& out) { side(raw, out, true); }
int run(const tlhybrid_host* host, bool floating, const char* name, uintptr_t address)
{
    autotest::Coverage coverage(name, address);
    for (unsigned text = 0; text < 4; ++text)
        for (unsigned pair = 0; pair < (floating ? 10u : 8u); ++pair) {
            Case c = {text, pair, floating};
            autotest::Outcome a, b;
            autotest::runChild(original, &c, a);
            autotest::runChild(candidate, &c, b);
            if (coverage.observe(host, a, b)) {
                host->log("    %s name %u pair %u exits %d/%d issues %u/%u\n",
                          name, text, pair, a.childStatus, b.childStatus,
                          a.capture.issue, b.capture.issue);
                coverage.report(host);
                return 1;
            }
        }
    coverage.report(host);
    return 0;
}
}

TL_TEST(achievement_construct_float)
{
    return run(host, true, "achievement_construct_float", reinterpret_cast<uintptr_t>(&oldFloatCtor));
}
TL_TEST(achievement_construct_int)
{
    return run(host, false, "achievement_construct_int", reinterpret_cast<uintptr_t>(&oldIntCtor));
}
