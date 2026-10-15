#include <cstddef>
#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "LogicGroup.h"

TL_ORIGINAL(bool, oldRemoveLink, (void*, unsigned, unsigned), "_ZN11CLogicGroup22RemoveLogicObjectsLinkEjj")
extern "C" bool newRemoveLink(void*, unsigned, unsigned) __asm__("_ZN11CLogicGroup22RemoveLogicObjectsLinkEjj");
TL_FUNCTION(removeLink, "_ZN12CLogicObject17RemoveLinkByIndexEj")

namespace {
typedef char CountOffset[(offsetof(CLogicGroup, m_logicObjects) == 0x60) ? 1 : -1];
struct Case { unsigned count, capacity, index, link, mutation; };
autotest::Capture* output;
void* expected;
unsigned expectedLink, calls;
bool result;
void* selected;
bool remove(void* object, unsigned link) {
    ++calls;
    unsigned valid = object == expected && link == expectedLink;
    output->add(&valid, sizeof(valid));
    output->add(&link, sizeof(link));
    if (!valid) output->issue = autotest::Capture::InvalidReport;
    static_cast<unsigned char*>(object)[0x58] ^= 0x5a;
    return result;
}
void side(void* raw, autotest::Capture& out, bool ours) {
    const Case& c = *static_cast<Case*>(raw);
    uint64_t group[(sizeof(CLogicGroup) + 7) / 8], objects[3][20];
    std::memset(group, 0xa5, sizeof(group));
    std::memset(objects, 0x3c, sizeof(objects));
    void* data[3] = {objects[0], c.mutation == 2 ? 0 : objects[1], objects[2]};
    unsigned grow = 3;
    void* address = data;
    std::memcpy(reinterpret_cast<char*>(group) + 0x60, &address, sizeof(address));
    std::memcpy(reinterpret_cast<char*>(group) + 0x68, &c.count, sizeof(c.count));
    std::memcpy(reinterpret_cast<char*>(group) + 0x6c, &c.capacity, sizeof(c.capacity));
    std::memcpy(reinterpret_cast<char*>(group) + 0x70, &grow, sizeof(grow));
    output = &out; calls = 0; expectedLink = c.link; result = c.mutation != 0;
    selected = data[c.index < c.capacity ? c.index : 0];
    expected = selected;
    const bool called = c.link != ~0u && c.index != ~0u && c.index < c.count && selected;
    detour::Set patches;
    TL_REDIRECT(patches, removeLink, &remove);
    if (patches.failed()) { out.issue = autotest::Capture::InvalidReport; return; }
    typedef bool (*Function)(void*, unsigned, unsigned);
    Function fn = ours ? newRemoveLink : oldRemoveLink;
    if (!autotest::beginInvocation(out, fn)) return;
    bool removed = fn(group, c.index, c.link);
    out.callCompleted = 1;
    if (calls != unsigned(called) || removed != (called && result)) out.issue = autotest::Capture::InvalidReport;
    out.add(&removed, sizeof(removed)); out.add(&calls, sizeof(calls));
    // Check child-local pointers before normalizing their addresses for capture.
    void* finalData;
    std::memcpy(&finalData, reinterpret_cast<char*>(group) + 0x60, sizeof(finalData));
    if (finalData != address || data[0] != objects[0] || data[2] != objects[2] ||
        data[1] != (c.mutation == 2 ? 0 : objects[1]))
        out.issue = autotest::Capture::InvalidReport;
    std::memset(reinterpret_cast<char*>(group) + 0x60, 0, sizeof(address));
    out.add(group, sizeof(group)); out.add(objects, sizeof(objects));
}
void original(void* c, autotest::Capture& out) { side(c, out, false); }
void candidate(void* c, autotest::Capture& out) { side(c, out, true); }
}
TL_TEST(logic_group_remove_link) {
    autotest::Coverage coverage("logic_group_remove_link", reinterpret_cast<uintptr_t>(&oldRemoveLink));
    const unsigned indices[] = {0, 1, 2, 3, 0x80000000u, ~0u};
    const unsigned links[] = {0, 7, 0x80000000u, ~0u};
    for (unsigned shape = 0; shape < 3; ++shape)
        for (unsigned i = 0; i < 6; ++i)
            for (unsigned j = 0; j < 4; ++j)
                for (unsigned mutation = 0; mutation < 3; ++mutation) {
                    Case c = {shape == 0 ? 0u : 3u, shape == 2 ? 1u : 3u, indices[i], links[j], mutation};
                    autotest::Outcome before, after;
                    autotest::runChild(original, &c, before);
                    autotest::runChild(candidate, &c, after);
                    if (coverage.observe(host, before, after)) {
                        host->log("    remove-link shape %u index %u link %u mutation %u exits %d/%d\n", shape, c.index, c.link, mutation, before.childStatus, after.childStatus);
                        coverage.report(host); return 1;
                    }
                }
    coverage.report(host); return 0;
}
