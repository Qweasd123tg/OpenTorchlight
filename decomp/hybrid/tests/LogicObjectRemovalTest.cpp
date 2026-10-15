#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "LogicObject.h"
#include "LogicLink.h"

TL_ORIGINAL(bool, originalRemoveObject, (void*, void*), "_ZN12CLogicObject24RemoveLinksToLogicObjectEPS_")
TL_ORIGINAL(bool, originalRemoveID, (void*, long long), "_ZN12CLogicObject30RemoveLogicLinksRefingObjectIDEx")
extern "C" bool candidateRemoveObject(void*, void*) __asm__("_ZN12CLogicObject24RemoveLinksToLogicObjectEPS_");
extern "C" bool candidateRemoveID(void*, long long) __asm__("_ZN12CLogicObject30RemoveLogicLinksRefingObjectIDEx");
TL_FUNCTION(removeIndex, "_ZN12CLogicObject17RemoveLinkByIndexEj")
namespace {
struct Case { void* object; void* target; long long id; void** slots; unsigned count, capacity, seed, operation, mutation; };
Case* input;
autotest::Capture* output;
unsigned calls;
void invalid() { output->issue = autotest::Capture::InvalidReport; }
void number(unsigned n) { output->add(&n, sizeof(n)); }
bool remove(void* object, unsigned index) {
    if (object != input->object || index >= input->count) invalid();
    number(index); ++calls;
    input->slots[index < input->capacity ? index : 0] = 0;
    if (input->mutation == 1) {
        unsigned count = index + 1;
        std::memcpy(static_cast<char*>(object) + 0x88, &count, 4);
    }
    return (input->seed & 1) != 0;
}
void body(Case& c, bool ours, autotest::Capture& out) {
    input = &c; output = &out; calls = 0;
    detour::Set patches; TL_REDIRECT(patches, removeIndex, &remove);
    if (patches.failed()) { invalid(); return; }
    bool value;
    if (c.operation == 0) {
        bool (*fn)(void*, void*) = ours ? candidateRemoveObject : originalRemoveObject;
        if (!autotest::beginInvocation(out, fn)) return;
        value = fn(c.object, c.target);
    } else {
        bool (*fn)(void*, long long) = ours ? candidateRemoveID : originalRemoveID;
        if (!autotest::beginInvocation(out, fn)) return;
        value = fn(c.object, c.id);
    }
    out.callCompleted = 1;
    bool valid = c.operation == 0 ? c.target != 0 : c.id != -1;
    if (value != valid || (!valid && calls)) invalid();
    out.add(&value, sizeof(value)); number(calls);
    out.add(c.object, sizeof(CLogicObject)); out.add(c.slots, 8 * sizeof(void*));
    patches.restore();
}
void original(void* p, autotest::Capture& out) { body(*static_cast<Case*>(p), false, out); }
void recovered(void* p, autotest::Capture& out) { body(*static_cast<Case*>(p), true, out); }
}
TL_TEST(logic_object_removal_differential) {
    const uint64_t addresses[] = {(uint64_t)(uintptr_t)&originalRemoveObject, (uint64_t)(uintptr_t)&originalRemoveID};
    unsigned sizes[] = {0, 1, 3, 7};
    for (unsigned operation = 0; operation < 2; ++operation) {
        autotest::Coverage coverage("logic_object_removal_differential", addresses[operation]);
        for (unsigned n = 0; n < 128; ++n) {
            unsigned long long object[(sizeof(CLogicObject)+7)/8];
            unsigned long long linked[2][(sizeof(CLogicObject)+7)/8];
            unsigned long long links[8][(sizeof(CLogicLink)+7)/8];
            void* slots[8];
            std::memset(object, 0x61 + n, sizeof(object));
            std::memset(linked, 0x42, sizeof(linked));
            std::memset(links, 0x23, sizeof(links));
            const long long ids[] = {0x123456789abcdefLL, -17};
            std::memcpy(reinterpret_cast<char*>(linked[0]) + 0x60, &ids[0], 8);
            std::memcpy(reinterpret_cast<char*>(linked[1]) + 0x60, &ids[1], 8);
            for (unsigned i = 0; i < 8; ++i) {
                void* to = (i + n) % 3 == 0 ? 0 : linked[(i + n) % 2];
                std::memcpy(reinterpret_cast<char*>(links[i]) + 0x28, &to, 8);
                slots[i] = (i + n) % 4 == 0 ? 0 : links[i];
            }
            Case c = {}; c.object = object; c.slots = slots; c.seed = n; c.operation = operation;
            c.count = sizes[n % 4]; c.capacity = n & 4 ? 1 : 8; c.mutation = (n / 8) % 2;
            c.target = n & 16 ? linked[0] : 0; c.id = n & 16 ? ids[n / 32 % 2] : -1;
            void* data = slots;
            std::memcpy(reinterpret_cast<char*>(object) + 0x80, &data, 8);
            std::memcpy(reinterpret_cast<char*>(object) + 0x88, &c.count, 4);
            std::memcpy(reinterpret_cast<char*>(object) + 0x8c, &c.capacity, 4);
            autotest::Outcome a, b; autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
            if (coverage.observe(host, a, b)) {
                host->log("    logic removal op %u case %u child %d/%d issue %u/%u\n", operation, n, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue);
                coverage.report(host); return 1;
            }
        }
        coverage.report(host);
        if (coverage.completed != 128 || coverage.different || coverage.missing) return 1;
    }
    return 0;
}
