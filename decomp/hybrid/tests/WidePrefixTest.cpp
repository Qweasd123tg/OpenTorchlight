#include <string>
#include <stdint.h>
#include "AutoTest.h"
TL_ORIGINAL(long long, old_wide_prefix, (const std::wstring&, const std::wstring&, unsigned int), "_ZN7STRINGS21firstXCharactersMatchERKSbIwSt11char_traitsIwESaIwEES5_j")
extern "C" long long new_wide_prefix(const std::wstring&, const std::wstring&, unsigned int) __asm__("_ZN7STRINGS21firstXCharactersMatchERKSbIwSt11char_traitsIwESaIwEES5_j");
namespace {
struct Case {unsigned pattern, count;};
void side(void* p, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(p);
    std::wstring a, b;
    switch (c.pattern % 12) {
    case 0: break;
    case 1: a = L"a"; b = a; break;
    case 2: a = L"a"; b = L"b"; break;
    case 3: a = L"prefix"; b = L"prefix suffix"; break;
    case 4: a = L"prefix suffix"; b = L"prefix"; break;
    case 5: a = L"abXde"; b = L"abYde"; break;
    case 6: a = L"abcdX"; b = L"abcdY"; break;
    case 7: a.assign(L"ab\0cd", 5); b = a; break;
    case 8: a.assign(L"ab\0cd", 5); b.assign(L"ab\0cX", 5); break;
    case 9: a = L"\x416\x4e2d\x1f642"; b = a; break;
    case 10: a.assign(1025, L'\x416'); b = a; b[1024] = L'Z'; break;
    case 11: a = L""; b = L"nonempty"; break;
    }
    if (c.pattern >= 12) a.swap(b);
    unsigned counts[] = {0, 1, 2, 3, static_cast<unsigned>(a.size()),
                         static_cast<unsigned>(b.size()),
                         static_cast<unsigned>(a.size() + 1), ~0u};
    typedef long long (*Fn)(const std::wstring&, const std::wstring&, unsigned);
    Fn fn = ours ? new_wide_prefix : old_wide_prefix;
    if (!autotest::beginInvocation(out, fn)) return;
    long long value = fn(a, b, counts[c.count]);
    out.callCompleted = 1;
    out.add(&value, sizeof(value));
    out.addText(a); out.addText(b);
}
void original(void* p, autotest::Capture& out) {side(p, out, false);}
void recovered(void* p, autotest::Capture& out) {side(p, out, true);}
}
TL_TEST(strings_wide_prefix)
{
    autotest::Coverage coverage("strings_wide_prefix", reinterpret_cast<uintptr_t>(&old_wide_prefix));
    for (unsigned pattern = 0; pattern < 24; ++pattern)
        for (unsigned count = 0; count < 8; ++count) {
            Case c = {pattern, count}; autotest::Outcome a, b;
            autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
            if (coverage.observe(host, a, b)) {
                host->log("    wide prefix pattern %u count %u statuses %d/%d\n", pattern, count, a.status, b.status);
                coverage.report(host); return 1;
            }
        }
    coverage.report(host); return 0;
}
