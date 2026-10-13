#include "SmallMassCompare.h"
#include "DungeonTracker.h"
#include <cstdio>

TL_ORIGINAL(void, originalSave, (void*, FILE*), "_ZN15CDungeonTracker4saveEP8_IO_FILE")
extern "C" void candidateSave(void*, FILE*) __asm__("_ZN15CDungeonTracker4saveEP8_IO_FILE");

namespace {
using namespace smallmass;

void execute(Case& c, bool ours, autotest::Capture& out)
{
    input = &c;
    output = &out;
    autotest::g_arenaUsed = 0;
    CDungeonTracker tracker;
    switch (c.index % 8) {
    case 0: tracker.m_name = L""; break;
    case 1: tracker.m_name = L"MINE"; break;
    case 2: tracker.m_name = L"mine"; break;
    case 3: tracker.m_name = L"\x416\x430\x43b"; break;
    case 4: tracker.m_name.assign(L"A\0B", 3); break;
    case 5: tracker.m_name = L"\x1f642"; break;
    case 6: tracker.m_name.assign(257, L'X'); break;
    case 7: tracker.m_name = L"floor/23"; break;
    }
    tracker.m_rank = int(c.index * 101) - 7000;
    tracker.m_value8 = int(c.index) - 64;
    tracker.m_value10 = 7000 - int(c.index * 91);
    const unsigned counts[] = {0, 1, 2, 3, 7, 8, 15, 16, 31, 32, 63, 64, 65, 95, 127, 128};
    unsigned count = counts[(c.index / 8) % 16];
    for (unsigned i = 0; i < count; ++i)
        tracker.m_levels.push_back(int(i * 37 + c.index) - 2000);

    FILE* file = tmpfile();
    if (!file) _exit(43);
    const char prefix[] = "prefix!";
    fwrite(prefix, 1, c.index % 8, file);
    autotest::invoke(out, ours ? candidateSave : originalSave, static_cast<void*>(&tracker), file);
    number(ftell(file));
    number(ferror(file));
    rewind(file);
    unsigned char bytes[256];
    size_t size;
    while ((size = fread(bytes, 1, sizeof(bytes), file)) != 0)
        out.add(bytes, size);
    number(ferror(file));
    fclose(file);

    text(tracker.m_name);
    number(tracker.m_rank);
    number(tracker.m_value8);
    number(tracker.m_value10);
    number(tracker.m_levels.size());
    for (unsigned i = 0; i < tracker.m_levels.size(); ++i)
        number(tracker.m_levels[i]);
}
}

TL_TEST(restore69_guard_8e43a0)
{
    return smallmass::run(host, 0, "restore69_guard_8e43a0",
        (uint64_t)(uintptr_t)originalSave, execute, 128);
}
