#include "AutoTest.h"
#include "Detour.h"
#include "CollisionList.h"
#include <climits>
#include <vector>

TL_ORIGINAL(unsigned, originalMemory, (void*), "_ZN14CCollisionList14getMemoryUsageEv")
extern "C" unsigned candidateMemory(void*) __asm__("_ZN14CCollisionList14getMemoryUsageEv");
TL_ORIGINAL(void, originalCollisionConstructor, (void*), "_ZN14CCollisionListC1Ev")
TL_ORIGINAL(void, originalCollisionDestructor, (void*), "_ZN14CCollisionListD1Ev")
TL_ORIGINAL(std::string, originalUnsignedText, (unsigned), "_ZN7STRINGS16GetValueAsStringEj")
extern "C" std::string candidateUnsignedText(unsigned) __asm__("_ZN7STRINGS16GetValueAsStringEj");
TL_ORIGINAL(std::wstring, originalSavePath, (), "_ZN10FILESYSTEM15GetSaveDataPathEv")
extern "C" std::wstring candidateSavePath() __asm__("_ZN10FILESYSTEM15GetSaveDataPathEv");
TL_FUNCTION(appDataPath, "_ZN10FILESYSTEM14GetAppDataPathEv")

namespace {
struct Case { unsigned operation, index; };
autotest::Capture* capture;
unsigned pathCalls;
const Case* activeCase;

std::wstring appData()
{
    ++pathCalls;
    capture->add(&pathCalls, sizeof(pathCalls));
    static const wchar_t* paths[] = { L"", L"/", L"/tmp/test/", L"relative", L"/home/\x0418\x0433\x0440\x043e\x043a/", L"a//b/", L"space name/" };
    std::wstring value(paths[activeCase->index % 7]);
    value.append(activeCase->index / 7, L'x');
    capture->addText(value);
    return value;
}

template<class T> void recordVector(autotest::Capture& out, std::vector<T>& values)
{
    size_t count = values.size(), capacity = values.capacity();
    out.add(&count, sizeof(count));
    out.add(&capacity, sizeof(capacity));
    if (count) out.add(&values[0], count * sizeof(T));
}

void execute(void* opaque, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(opaque);
    if (c.operation == 0) {
        // The receiver and every vector are constructed by the original C++
        // constructor. Offsets below are the actual private fields in its TU.
        void* object = autotest::allocate(sizeof(CCollisionList));
        if (!object) { out.issue = autotest::Capture::InvalidReport; return; }
        originalCollisionConstructor(object);
        const unsigned vectorOffsets[] = {0x28, 0x40, 0x58, 0x70, 0x88};
        const unsigned indexOffsets[] = {0xa0, 0xb8, 0xd0, 0xe8};
        for (unsigned i = 0; i < 5; ++i) {
            std::vector<Ogre::Vector3>& values = *reinterpret_cast<std::vector<Ogre::Vector3>*>(static_cast<char*>(object) + vectorOffsets[i]);
            unsigned count = c.index == 0 ? 0 : (c.index * (i + 1)) % 37;
            if (c.index & 1) values.reserve(count + 19);
            values.resize(count, Ogre::Vector3(float(i), float(c.index), -float(i)));
        }
        for (unsigned i = 0; i < 4; ++i) {
            std::vector<unsigned>& values = *reinterpret_cast<std::vector<unsigned>*>(static_cast<char*>(object) + indexOffsets[i]);
            unsigned count = c.index == 0 ? 0 : (c.index * (i + 2)) % 31;
            if (c.index & 2) values.reserve(count + 41);
            values.resize(count, c.index * 101 + i);
        }
        unsigned (*fn)(void*) = ours ? candidateMemory : originalMemory;
        if (!autotest::beginInvocation(out, fn)) return;
        unsigned result = fn(object);
        out.callCompleted = 1;
        out.add(&result, sizeof(result));
        out.add(object, sizeof(CCollisionList));
        for (unsigned i = 0; i < 5; ++i)
            recordVector(out, *reinterpret_cast<std::vector<Ogre::Vector3>*>(static_cast<char*>(object) + vectorOffsets[i]));
        for (unsigned i = 0; i < 4; ++i)
            recordVector(out, *reinterpret_cast<std::vector<unsigned>*>(static_cast<char*>(object) + indexOffsets[i]));
        originalCollisionDestructor(object);
    } else if (c.operation == 1) {
        const unsigned values[] = {0, 1, 9, 10, 99, 100, 999, 1000, 65535, 65536, 0x7fffffffu, 0x80000000u, 0xfffffffeu, UINT_MAX};
        unsigned input = c.index < 14 ? values[c.index] : (c.index - 13) * 2654435761u;
        std::string (*fn)(unsigned) = ours ? candidateUnsignedText : originalUnsignedText;
        if (!autotest::beginInvocation(out, fn)) return;
        std::string result = fn(input);
        out.callCompleted = 1;
        out.addText(result);
        out.add(&input, sizeof(input));
    } else {
        activeCase = &c;
        capture = &out;
        pathCalls = 0;
        detour::Set redirects;
        TL_REDIRECT(redirects, appDataPath, appData);
        if (redirects.failed()) { out.issue = autotest::Capture::InvalidReport; return; }
        std::wstring (*fn)() = ours ? candidateSavePath : originalSavePath;
        if (!autotest::beginInvocation(out, fn)) return;
        std::wstring result = fn();
        out.callCompleted = 1;
        out.addText(result);
        out.add(&pathCalls, sizeof(pathCalls));
    }
}
void original(void* p, autotest::Capture& out) { execute(p, out, false); }
void candidate(void* p, autotest::Capture& out) { execute(p, out, true); }
int run(const tlhybrid_host* host, unsigned operation, const char* name, uint64_t address)
{
    autotest::Coverage coverage(name, address);
    for (unsigned index = 0; index < 35; ++index) {
        Case c = {operation, index};
        autotest::Outcome& a = autotest::g_outcomes[0];
        autotest::Outcome& b = autotest::g_outcomes[1];
        autotest::runChild(original, &c, a);
        autotest::runChild(candidate, &c, b);
        if (coverage.observe(host, a, b)) { coverage.report(host); return 1; }
    }
    coverage.report(host);
    return 0;
}
}
TL_TEST(mass_accessors_memory_size) { return run(host, 0, "mass_accessors_memory_size", (uint64_t)(uintptr_t)originalMemory); }
TL_TEST(mass_accessors_unsigned_text) { return run(host, 1, "mass_accessors_unsigned_text", (uint64_t)(uintptr_t)originalUnsignedText); }
TL_TEST(mass_accessors_save_path) { return run(host, 2, "mass_accessors_save_path", (uint64_t)(uintptr_t)originalSavePath); }
