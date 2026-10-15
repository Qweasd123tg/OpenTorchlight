#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "PuzzleRandomizer.h"
TL_ORIGINAL(long long, originalUpdate, (void*, float, Ogre::Camera*, const Ogre::Vector3&), "_ZN17CPuzzleRandomizer17updateLevelObjectEfPN4Ogre6CameraERKNS0_7Vector3E")
extern "C" long long candidateUpdate(void*, float, Ogre::Camera*, const Ogre::Vector3&) __asm__("_ZN17CPuzzleRandomizer17updateLevelObjectEfPN4Ogre6CameraERKNS0_7Vector3E");
TL_FUNCTION(resetTarget, "_ZN17CPuzzleRandomizer5resetEv")
namespace {
struct Case { void* object; int state; unsigned seed, mutation; };
Case* input; autotest::Capture* output; unsigned calls;
void invalid() { output->issue = autotest::Capture::InvalidReport; }
void number(unsigned n) { output->add(&n, sizeof(n)); }
void broadcast(void* object, unsigned event) {
    if (object != input->object || calls != 0 || event != (input->state == 1 ? 54u : input->state == 2 ? 55u : 9u)) invalid();
    number(event); ++calls;
    if (input->mutation) { int state = -77; std::memcpy(static_cast<char*>(object) + 0x8c, &state, 4); }
}
void reset(void* object) {
    if (object != input->object || calls != 1 || input->state != 1) invalid();
    number(100); ++calls;
    int state = 3; std::memcpy(static_cast<char*>(object) + 0x8c, &state, 4);
    static_cast<unsigned char*>(object)[0x68] ^= 1;
}
void body(Case& c, bool ours, autotest::Capture& out) {
    input = &c; output = &out; calls = 0;
    detour::Set patches; TL_REDIRECT(patches, resetTarget, &reset);
    if (patches.failed()) { invalid(); return; }
    Ogre::Vector3 position(c.seed * 0.125f, -2.0f, 16.0f);
    long long (*fn)(void*, float, Ogre::Camera*, const Ogre::Vector3&) = ours ? candidateUpdate : originalUpdate;
    if (!autotest::beginInvocation(out, fn)) return;
    long long result = fn(c.object, c.seed * 0.03125f, 0, position); out.callCompleted = 1;
    int state; std::memcpy(&state, static_cast<char*>(c.object) + 0x8c, 4);
    if (result != (c.state == 1 ? 1LL : 0LL) || state != (c.state == 1 ? 3 : 0) || calls != (c.state == 1 ? 2u : c.state == 2 || c.state == 3 ? 1u : 0u)) invalid();
    out.add(&result, sizeof(result)); number(calls); out.add(c.object, sizeof(CPuzzleRandomizer));
    patches.restore();
}
void original(void* p, autotest::Capture& out) { body(*static_cast<Case*>(p), false, out); }
void recovered(void* p, autotest::Capture& out) { body(*static_cast<Case*>(p), true, out); }
}
TL_TEST(puzzle_randomizer_update_differential) {
    autotest::Coverage coverage("puzzle_randomizer_update_differential", (uint64_t)(uintptr_t)&originalUpdate);
    const int states[] = {-2147483647 - 1, -1, 0, 1, 2, 3, 4, 2147483647};
    for (unsigned n = 0; n < 64; ++n) {
        unsigned long long object[(sizeof(CPuzzleRandomizer)+7)/8]; std::memset(object, 0x39 + n, sizeof(object));
        void* table[7] = {0, 0, 0, 0, 0, 0, reinterpret_cast<void*>(&broadcast)};
        void* tablePointer = table; std::memcpy(object, &tablePointer, 8);
        Case c = {}; c.object = object; c.state = states[n % 8]; c.seed = n; c.mutation = n / 8 % 2;
        std::memcpy(reinterpret_cast<char*>(object) + 0x8c, &c.state, 4);
        autotest::Outcome a, b; autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
        if (coverage.observe(host, a, b)) { host->log("    puzzle update case %u child %d/%d issue %u/%u\n", n, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue); coverage.report(host); return 1; }
    }
    coverage.report(host);
    return coverage.completed != 64 || coverage.different || coverage.missing;
}
