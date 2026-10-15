// Direct original/replacement pairs. Only the two direct timeline collaborators
// are redirected; the entry under test and the map iterator are always real.
#include <climits>
#include <cstddef>
#include <cstring>
#include <map>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#include "Timeline.h"

TL_ORIGINAL(void, originalPlay, (void*, bool), "_ZN9CTimeline4PlayEb")
extern "C" void candidatePlay(void*, bool) __asm__("_ZN9CTimeline4PlayEb");
TL_ORIGINAL(void, originalBackwards, (void*), "_ZN9CTimeline14Play_BackwardsEv")
extern "C" void candidateBackwards(void*) __asm__("_ZN9CTimeline14Play_BackwardsEv");
TL_ORIGINAL(long long, originalObjectID, (void*, int), "_ZN9CTimeline28GetObjectIDInTimelineByIndexEi")
extern "C" long long candidateObjectID(void*, int) __asm__("_ZN9CTimeline28GetObjectIDInTimelineByIndexEi");
TL_FUNCTION(targetReset, "_ZN9CTimeline24resetPropertiesToPercentEf")
TL_FUNCTION(targetPercent, "_ZN9CTimeline22SetTimelinePercentDoneEf")

namespace {
typedef std::map<std::pair<int, bool>, CTimelineProperty*> Properties;
// ASM reads only the outer header and key; use original pointer-valued nodes.
typedef std::map<long long, Properties*> Objects;
typedef std::_Rb_tree_node<Objects::value_type> Node;
typedef char MapOffsetProof[(offsetof(CTimeline, m_timelineProperties) == 0x58) ? 1 : -1];
typedef char DirectionOffsetProof[(offsetof(CTimeline, m_bIsPlayingBackwards) == 0xa0) ? 1 : -1];
typedef char EnabledOffsetProof[(offsetof(CTimeline, m_bEnabled) == 0xa1) ? 1 : -1];
typedef char TimelineSizeProof[(sizeof(CTimeline) == 0xb0) ? 1 : -1];

struct Case {
    unsigned operation, seed, mutation;
    bool enabled, backwards, forwards;
    int index;
    long long expectedID;
    void* object;
    Objects* objects;
    Node* nodes[8];
    unsigned nodeCount;
};
const Case* input;
autotest::Capture* output;
unsigned stage;

void number(unsigned n) { output->add(&n, sizeof(n)); }
void invalid() { output->issue = autotest::Capture::InvalidReport; }
unsigned char& byte(void* p, unsigned offset) { return static_cast<unsigned char*>(p)[offset]; }
void recordState(void* p) {
    number(p == input->object);
    number(byte(p, 0xa0));
    number(byte(p, 0xa1));
}
void mutateAt(void* p, unsigned at) {
    if (input->mutation == at) {
        byte(p, 0xa0) ^= 1;
        byte(p, 0xa1) ^= 1;
    }
}
float startPercent() {
    return input->operation == 1 || !input->forwards ? 1.01f : -0.01f;
}
void checkPercent(float f) {
    float expected = startPercent();
    if (std::memcmp(&f, &expected, sizeof(f))) invalid();
    output->add(&f, sizeof(f));
}
void reset(void* p, float f) {
    if (stage != 0 || p != input->object || byte(p, 0xa1) != 1 ||
        byte(p, 0xa0) != (input->operation == 1 || !input->forwards)) invalid();
    number(1); recordState(p); checkPercent(f); ++stage;
    mutateAt(p, 1);
}
float percent(void* p, float f) {
    if (stage != 1 || p != input->object) invalid();
    number(2); recordState(p); checkPercent(f); ++stage;
    // A collaborator has observable effects; capture the complete receiver.
    float position = f + static_cast<float>(input->seed);
    std::memcpy(static_cast<char*>(p) + 0x98, &position, sizeof(position));
    mutateAt(p, 2);
    return position;
}
void broadcast(void* p, unsigned event) {
    unsigned direction = input->operation == 1 || !input->forwards ? 41 : 42;
    if (p != input->object || (stage != 2 && stage != 3) ||
        event != (stage == 2 ? 36u : direction)) invalid();
    number(3); recordState(p); number(event); ++stage;
    if (stage == 3) mutateAt(p, 3);
}

void side(Case& c, bool ours, autotest::Capture& out) {
    input = &c; output = &out; stage = 0;
    if (c.operation == 2) {
        unsigned char before[sizeof(CTimeline)];
        std::memcpy(before, c.object, sizeof(before));
        unsigned char beforeNodes[8][sizeof(Node)];
        for (unsigned i = 0; i < c.nodeCount; ++i) std::memcpy(beforeNodes[i], c.nodes[i], sizeof(Node));
        long long (*fn)(void*, int) = ours ? candidateObjectID : originalObjectID;
        if (!autotest::beginInvocation(out, fn)) return;
        long long id = fn(c.object, c.index);
        out.callCompleted = 1;
        out.add(&id, sizeof(id));
        if (id != c.expectedID || std::memcmp(before, c.object, sizeof(before))) invalid();
        out.add(c.object, sizeof(CTimeline));
        for (unsigned i = 0; i < c.nodeCount; ++i) {
            if (std::memcmp(beforeNodes[i], c.nodes[i], sizeof(Node))) invalid();
            out.add(c.nodes[i], sizeof(Node));
        }
        return;
    }
    detour::Set patches;
    TL_REDIRECT(patches, targetReset, &reset);
    TL_REDIRECT(patches, targetPercent, &percent);
    if (patches.failed()) { invalid(); return; }
    if (c.operation == 0) autotest::invoke(out, ours ? candidatePlay : originalPlay, c.object, c.forwards);
    else autotest::invoke(out, ours ? candidateBackwards : originalBackwards, c.object);
    bool requestedBackwards = c.operation == 1 || !c.forwards;
    bool action = !c.enabled || c.backwards != requestedBackwards;
    if (stage != (action ? 4u : 0u)) invalid();
    number(stage);
    out.add(c.object, sizeof(CTimeline));
    patches.restore();
}
void original(void* p, autotest::Capture& out) { side(*static_cast<Case*>(p), false, out); }
void recovered(void* p, autotest::Capture& out) { side(*static_cast<Case*>(p), true, out); }

int compare(const tlhybrid_host* host, Case& c, autotest::Coverage& coverage, unsigned ordinal) {
    autotest::Outcome a, b;
    autotest::runChild(original, &c, a);
    autotest::runChild(recovered, &c, b);
    int result = coverage.observe(host, a, b);
    if (result) host->log("    timeline controls op %u case %u pair %d status %d/%d issue %u/%u bytes %lu/%lu\n",
                         c.operation, ordinal, result, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue,
                         (unsigned long)a.capture.length, (unsigned long)b.capture.length);
    return result;
}
}

TL_TEST(timeline_controls_differential) {
    const uint64_t addresses[] = {
        (uint64_t)(uintptr_t)&originalPlay, (uint64_t)(uintptr_t)&originalBackwards,
        (uint64_t)(uintptr_t)&originalObjectID
    };
    for (unsigned operation = 0; operation < 3; ++operation) {
        autotest::Coverage coverage("timeline_controls_differential", addresses[operation]);
        unsigned cases = operation == 2 ? 40 : operation == 1 ? 32 : 64;
        unsigned active = 0, idle = 0, valid = 0, invalidIndex = 0;
        for (unsigned n = 0; n < cases; ++n) {
            unsigned long long storage[sizeof(CTimeline) / 8];
            std::memset(storage, 0x81u + n, sizeof(storage));
            void* table[7] = {0, 0, 0, 0, 0, 0, reinterpret_cast<void*>(&broadcast)};
            void* tablePointer = table;
            std::memcpy(storage, &tablePointer, sizeof(tablePointer));
            Case c = {};
            c.operation = operation; c.seed = n;
            c.enabled = (n & 1) != 0; c.backwards = (n & 2) != 0;
            c.forwards = (n & 4) != 0; c.mutation = (n / 8) % 4;
            c.object = storage;
            byte(c.object, 0xa0) = c.backwards;
            byte(c.object, 0xa1) = c.enabled;
            if (operation == 2) {
                c.objects = new(static_cast<char*>(c.object) + 0x58) Objects;
                const unsigned sizes[] = {0, 1, 3, 7};
                const long long keys[] = {-0x1234567890123LL, -17, 0, 1, 0x1234567887654321LL,
                                          0x3456789012345678LL, 0x7fffffffffffffffLL};
                unsigned count = sizes[n / 10];
                for (unsigned i = 0; i < count; ++i) (*c.objects)[keys[i]];
                unsigned at = 0;
                for (Objects::iterator i = c.objects->begin(); i != c.objects->end(); ++i) {
                    c.nodes[at++] = reinterpret_cast<Node*>(reinterpret_cast<char*>(&*i) - offsetof(Node, _M_value_field));
                }
                c.nodeCount = at;
                const int indices[] = {-1, 0, 1, 2, 3, 6, 7, 8, INT_MIN, INT_MAX};
                c.index = indices[n % 10];
                bool live = c.index >= 0 && static_cast<unsigned>(c.index) < count;
                c.expectedID = live ? keys[c.index] : -1LL;
                if (live) ++valid; else ++invalidIndex;
            } else {
                bool backwards = operation == 1 || !c.forwards;
                if (!c.enabled || c.backwards != backwards) ++active; else ++idle;
            }
            int result = compare(host, c, coverage, n);
            if (operation == 2) c.objects->~Objects();
            if (result) { coverage.report(host); return 1; }
        }
        coverage.report(host);
        if (coverage.completed != cases || coverage.completed < 20 || coverage.different || coverage.missing ||
            (operation == 2 ? (!valid || !invalidIndex) : (!active || !idle))) return 1;
        host->log("    timeline controls op %u live %u idle %u valid-index %u invalid-index %u\n",
                  operation, active, idle, valid, invalidIndex);
    }
    return 0;
}
