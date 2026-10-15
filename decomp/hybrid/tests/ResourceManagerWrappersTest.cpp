#include <cstring>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(bool, oldRunning, (void*), "_ZN16CResourceManager18getEditorIsRunningEv")
extern "C" bool newRunning(void*) __asm__("_ZN16CResourceManager18getEditorIsRunningEv");
TL_ORIGINAL(void*, oldCreate, (void*, void*, int, bool, bool), "_ZN16CResourceManager10createUnitEP10CDataGroupibb")
extern "C" void* newCreate(void*, void*, int, bool, bool) __asm__("_ZN16CResourceManager10createUnitEP10CDataGroupibb");
TL_FUNCTION(guidTarget, "_ZN16CResourceManager22getUnitGuidByDataGroupEP10CDataGroupRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(unitTarget, "_ZN16CResourceManager10createUnitExibb")
extern "C" void* editorGlobal __asm__("gEditor");

namespace {
struct Case { unsigned operation, seed; };
autotest::Capture* output;
void* manager; void* group;
uint64_t returnedUnit[4];
long long expectedGuid;
int expectedLevel;
bool firstFlag, secondFlag;
unsigned calls, mutation;
void number(unsigned n) { output->add(&n, sizeof(n)); }
void invalid() { output->issue = autotest::Capture::InvalidReport; }
long long guid(void* receiver, void* data, const std::wstring& name) {
    number(1); number(receiver == manager); number(data == group);
    if (calls++ != 0 || receiver != manager || data != group || name != L"UNIT_GUID") invalid();
    unsigned length = name.size(); number(length); output->add(name.data(), length * sizeof(wchar_t));
    static_cast<unsigned char*>(receiver)[0x40] ^= 0x55;
    if (mutation == 2) throw 19;
    return expectedGuid;
}
void* unit(void* receiver, long long id, int level, bool first, bool second) {
    number(2); number(receiver == manager);
    output->add(&id, sizeof(id)); output->add(&level, sizeof(level));
    number(first); number(second);
    if (calls++ != 1 || receiver != manager || id != expectedGuid || level != expectedLevel ||
        first != firstFlag || second != secondFlag || static_cast<unsigned char*>(receiver)[0x40] != 0xf0) invalid();
    return mutation == 1 ? 0 : returnedUnit;
}
void side(void* raw, autotest::Capture& out, bool ours) {
    const Case& c = *static_cast<Case*>(raw);
    uint64_t receiver[10], data[8], editor[16];
    std::memset(receiver, 0xa5, sizeof(receiver)); std::memset(data, 0x3c, sizeof(data));
    std::memset(editor, 0x69, sizeof(editor));
    output = &out; calls = 0;
    if (c.operation == 0) {
        uint32_t flags = c.seed < 8 ? c.seed : (c.seed * 2654435761u);
        std::memcpy(reinterpret_cast<char*>(editor) + 0x64, &flags, sizeof(flags));
        editorGlobal = editor;
        typedef bool (*Running)(void*);
        Running fn = ours ? newRunning : oldRunning;
        if (!autotest::beginInvocation(out, fn)) return;
        bool value = fn(receiver); out.callCompleted = 1;
        if (value != !(flags & 2) || editorGlobal != editor) invalid();
        out.add(&value, sizeof(value)); out.add(editor, sizeof(editor));
        editorGlobal = 0;
    } else {
        manager = receiver; group = c.seed & 1 ? data : 0;
        static const long long guids[] = {-1, 0, 1, 0x1122334455667788LL, -9223372036854775807LL};
        expectedGuid = guids[(c.seed / 2) % 5]; expectedLevel = int(c.seed * 17) - 300;
        firstFlag = c.seed & 2; secondFlag = c.seed & 4; mutation = (c.seed / 8) % 3;
        detour::Set patches; TL_REDIRECT(patches, guidTarget, &guid); TL_REDIRECT(patches, unitTarget, &unit);
        if (patches.failed()) { invalid(); return; }
        typedef void* (*Create)(void*, void*, int, bool, bool);
        Create fn = ours ? newCreate : oldCreate;
        if (!autotest::beginInvocation(out, fn)) return;
        void* result = 0; int exception = 0;
        try { result = fn(receiver, group, expectedLevel, firstFlag, secondFlag); }
        catch (int code) { exception = code; }
        out.callCompleted = 1;
        const unsigned expectedCalls = !group ? 0 : mutation == 2 ? 1 : 2;
        if (calls != expectedCalls || exception != (group && mutation == 2 ? 19 : 0) ||
            result != (group && mutation == 0 ? returnedUnit : 0)) invalid();
        number(calls); number(result == returnedUnit); out.add(&exception, sizeof(exception));
    }
    out.add(receiver, sizeof(receiver)); out.add(data, sizeof(data));
}
void original(void* c, autotest::Capture& out) { side(c, out, false); }
void candidate(void* c, autotest::Capture& out) { side(c, out, true); }
int run(const tlhybrid_host* host, unsigned op, const char* name, uintptr_t address) {
    autotest::Coverage coverage(name, address);
    for (unsigned seed = 0; seed < (op ? 80u : 64u); ++seed) {
        Case c = {op, seed}; autotest::Outcome before, after;
        autotest::runChild(original, &c, before); autotest::runChild(candidate, &c, after);
        if (coverage.observe(host, before, after)) {
            host->log("    resource wrapper %u seed %u exits %d/%d\n", op, seed, before.childStatus, after.childStatus);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host); return 0;
}
}
TL_TEST(resource_manager_editor_running) { return run(host, 0, "resource_manager_editor_running", reinterpret_cast<uintptr_t>(&oldRunning)); }
TL_TEST(resource_manager_create_from_group) { return run(host, 1, "resource_manager_create_from_group", reinterpret_cast<uintptr_t>(&oldCreate)); }
