#include "AutoTest.h"
#include <climits>
#include <cstring>
#include <locale>
#include <stdexcept>
#include <string>

TL_ORIGINAL(std::string, oldDoubleText, (double), "_ZN7STRINGS16GetValueAsStringEd")
extern "C" std::string newDoubleText(double) __asm__("_ZN7STRINGS16GetValueAsStringEd");
TL_ORIGINAL(std::string, oldLongText, (long long), "_ZN7STRINGS16GetValueAsStringEx")
extern "C" std::string newLongText(long long) __asm__("_ZN7STRINGS16GetValueAsStringEx");
TL_ORIGINAL(std::wstring, oldUnsignedWide, (unsigned), "_ZN7STRINGS17GetValueAsWStringEj")
extern "C" std::wstring newUnsignedWide(unsigned) __asm__("_ZN7STRINGS17GetValueAsWStringEj");
TL_ORIGINAL(std::wstring, oldIntWide, (int), "_ZN7STRINGS17GetValueAsWStringEi")
extern "C" std::wstring newIntWide(int) __asm__("_ZN7STRINGS17GetValueAsWStringEi");
TL_ORIGINAL(std::wstring, oldLongWide, (long long), "_ZN7STRINGS17GetValueAsWStringEx")
extern "C" std::wstring newLongWide(long long) __asm__("_ZN7STRINGS17GetValueAsWStringEx");
TL_ORIGINAL(std::wstring, oldDoubleWide, (double), "_ZN7STRINGS17GetValueAsWStringEd")
extern "C" std::wstring newDoubleWide(double) __asm__("_ZN7STRINGS17GetValueAsWStringEd");
TL_ORIGINAL(std::wstring, oldFloatWide, (float), "_ZN7STRINGS17GetValueAsWStringEf")
extern "C" std::wstring newFloatWide(float) __asm__("_ZN7STRINGS17GetValueAsWStringEf");

namespace {
struct Case { unsigned operation, index; };
// Use the library's named locales: constructing custom facets would require
// facet ID data that the original executable does not import.
void selectLocale(bool alternate)
{
    if (!alternate) {
        std::locale::global(std::locale("C"));
        return;
    }
    try {
        std::locale::global(std::locale("de_DE.utf8"));
    } catch (const std::runtime_error&) {
        std::locale::global(std::locale("POSIX"));
    }
}
template<class R, class T> void invoke(autotest::Capture& out, R (*fn)(T), T value)
{
    if (!autotest::beginInvocation(out, fn)) return;
    R result = fn(value);
    out.callCompleted = 1;
    out.addText(result);
    out.add(&value, sizeof(value));
}
void execute(void* opaque, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(opaque);
    unsigned i = c.index % 28;
    selectLocale(c.index >= 28);
    const long long integers[] = {0, 1, -1, 9, -9, 10, -10, 999, -999, 1000, -1000, INT_MIN, INT_MAX, 0x7fffffffffffffffLL, (-0x7fffffffffffffffLL - 1), 0x100000000LL, -0x100000000LL, 999999999999LL, -999999999999LL, 0x7fffffff00000000LL, -123456789, 123456789, 0xffff, 0x10000, -0xffff, -0x10000, 42, -42};
    const uint64_t doubles[] = {0, 0x8000000000000000ULL, 0x3ff0000000000000ULL, 0xbff0000000000000ULL, 0x3fd5555555555555ULL, 0x7ff0000000000000ULL, 0xfff0000000000000ULL, 0x7ff8000000000000ULL, 0xfff8123456789abcULL, 1, 0x8000000000000001ULL, 0x0010000000000000ULL, 0x7fefffffffffffffULL, 0xffefffffffffffffULL};
    const unsigned floats[] = {0, 0x80000000u, 0x3f800000, 0xbf800000, 0x3eaaaaab, 0x7f800000, 0xff800000, 0x7fc00000, 0xffc12345, 1, 0x80000001u, 0x00800000, 0x7f7fffff, 0xff7fffff};
    double d; float f;
    uint64_t dbits = doubles[i % 14]; unsigned fbits = floats[i % 14];
    std::memcpy(&d, &dbits, sizeof(d)); std::memcpy(&f, &fbits, sizeof(f));
    if (i >= 14) { d = static_cast<double>(integers[i]) / 13.0; f = static_cast<float>(integers[i]) / 13.0f; }
    switch (c.operation) {
    case 0: invoke(out, ours ? newDoubleText : oldDoubleText, d); break;
    case 1: invoke(out, ours ? newLongText : oldLongText, integers[i]); break;
    case 2: invoke(out, ours ? newUnsignedWide : oldUnsignedWide, static_cast<unsigned>(integers[i])); break;
    case 3: invoke(out, ours ? newIntWide : oldIntWide, static_cast<int>(integers[i])); break;
    case 4: invoke(out, ours ? newLongWide : oldLongWide, integers[i]); break;
    case 5: invoke(out, ours ? newDoubleWide : oldDoubleWide, d); break;
    case 6: invoke(out, ours ? newFloatWide : oldFloatWide, f); break;
    }
}
void original(void* c, autotest::Capture& out) { execute(c, out, false); }
void candidate(void* c, autotest::Capture& out) { execute(c, out, true); }
int run(const tlhybrid_host* host, unsigned operation, const char* name, uint64_t address)
{
    autotest::Coverage coverage(name, address);
    for (unsigned i = 0; i < 56; ++i) {
        Case c = {operation, i};
        autotest::Outcome& a = autotest::g_outcomes[0]; autotest::Outcome& b = autotest::g_outcomes[1];
        autotest::runChild(original, &c, a); autotest::runChild(candidate, &c, b);
        if (coverage.observe(host, a, b)) { coverage.report(host); return 1; }
    }
    coverage.report(host); return 0;
}
}
TL_TEST(mass_numeric_double_text) { return run(host, 0, "mass_numeric_double_text", (uint64_t)(uintptr_t)oldDoubleText); }
TL_TEST(mass_numeric_long_text) { return run(host, 1, "mass_numeric_long_text", (uint64_t)(uintptr_t)oldLongText); }
TL_TEST(mass_numeric_unsigned_wide) { return run(host, 2, "mass_numeric_unsigned_wide", (uint64_t)(uintptr_t)oldUnsignedWide); }
TL_TEST(mass_numeric_int_wide) { return run(host, 3, "mass_numeric_int_wide", (uint64_t)(uintptr_t)oldIntWide); }
TL_TEST(mass_numeric_long_wide) { return run(host, 4, "mass_numeric_long_wide", (uint64_t)(uintptr_t)oldLongWide); }
TL_TEST(mass_numeric_double_wide) { return run(host, 5, "mass_numeric_double_wide", (uint64_t)(uintptr_t)oldDoubleWide); }
TL_TEST(mass_numeric_float_wide) { return run(host, 6, "mass_numeric_float_wide", (uint64_t)(uintptr_t)oldFloatWide); }
