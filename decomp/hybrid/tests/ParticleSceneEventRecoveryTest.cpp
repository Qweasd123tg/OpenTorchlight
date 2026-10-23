#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "tests/Detour.h"

extern "C" void* sceneTechniqueTable[] __asm__("_ZTV20CParticleTechWrapper");
extern "C" void* sceneOtherTable[] __asm__("_ZTV17CEditorBaseObject");
TL_ORIGINAL(void, sceneEventOriginal, (void*, unsigned, long long), "_ZN14CParticleScene9fireEventE14EEDITOR_EVENTSx")
extern "C" void sceneEventCandidate(void*, unsigned, long long) __asm__("_ZN14CParticleScene9fireEventE14EEDITOR_EVENTSx");
TL_FUNCTION(sceneEventDescriptor, "_ZN18CDescriptorManager13GetDescriptorEPKwb")
TL_FUNCTION(sceneEventFlag, "_ZN17CEditorBaseObject17HasBaseObjectFlagE18EEDITOROBJECT_FLAG")
TL_FUNCTION(sceneEventForceStop, "_ZN20CParticleTechWrapper9forceStopEv")
TL_FUNCTION(sceneEventActivated, "_ZN20CParticleTechWrapper12setActivatedEb")

namespace {
struct Case {
    uint64_t scene[56], manager[4], descriptor[40], objects[6][72];
    void* slots[6];
    unsigned event, count, capacity, mode, mutation, flags;
    long long guid;
    bool negative;
};
Case* input; autotest::Capture* output; unsigned lookups, stops, activations;
void number(unsigned value) { output->add(&value, sizeof(value)); }
unsigned identity(void* object) { for (unsigned i = 0; i < 6; ++i) if (object == input->objects[i]) return i; output->issue = autotest::Capture::InvalidReport; return 9; }
void* descriptor(void* manager, const wchar_t* name, bool create)
{
    if (manager != input->manager || std::wcscmp(name, L"Particle") || create || lookups++) output->issue = autotest::Capture::InvalidReport;
    number(1); output->add(name, 9 * sizeof(wchar_t)); number(create);
    return input->mode == 0 ? NULL : input->descriptor;
}
bool flag(void* object, unsigned value)
{
    unsigned id = identity(object);
    number(2); number(id); number(value);
    if (value != 2) output->issue = autotest::Capture::InvalidReport;
    return id < 6 && (input->flags & (1u << id));
}
void forceStop(void* object)
{
    unsigned id = identity(object); number(3); number(id); ++stops;
    if (id < 6) reinterpret_cast<unsigned char*>(object)[0x128] ^= 3;
    if (stops == 1 && input->mutation) {
        unsigned count = input->mutation == 1 ? 0 : 6;
        std::memcpy(reinterpret_cast<char*>(input->descriptor) + 0xe8, &count, 4);
    }
}
void activated(void* object, bool value)
{
    unsigned id = identity(object); number(4); number(id); number(value); ++activations;
    if (!value) output->issue = autotest::Capture::InvalidReport;
    if (id < 6) reinterpret_cast<unsigned char*>(object)[0x128] ^= 5;
}
void side(void* raw, autotest::Capture& out, bool ours)
{
    Case& c = *static_cast<Case*>(raw); input = &c; output = &out; lookups = stops = activations = 0;
    detour::Set redirects;
    TL_REDIRECT(redirects, sceneEventDescriptor, &descriptor);
    TL_REDIRECT(redirects, sceneEventFlag, &flag);
    TL_REDIRECT(redirects, sceneEventForceStop, &forceStop);
    TL_REDIRECT(redirects, sceneEventActivated, &activated);
    if (redirects.failed()) { out.issue = autotest::Capture::InvalidReport; return; }
    autotest::invoke(out, ours ? sceneEventCandidate : sceneEventOriginal, c.scene, c.event, c.guid);
    if (ours && c.negative) ++activations;
    number(lookups); number(stops); number(activations);
    out.add(c.scene, sizeof(c.scene)); out.add(c.descriptor, sizeof(c.descriptor)); out.add(c.objects, sizeof(c.objects));
}
void original(void* p, autotest::Capture& out) { side(p, out, false); }
void candidate(void* p, autotest::Capture& out) { side(p, out, true); }
void setup(Case& c, unsigned seed, unsigned guidMode)
{
    std::memset(&c, 0, sizeof(c));
    const unsigned events[] = {0, 1, 2, 5, 6, 0xffffffffu};
    const unsigned capacities[] = {0, 1, 4, 6};
    c.event = events[seed % 6]; c.count = seed / 6 % 7; c.capacity = capacities[seed / 42 % 4];
    c.mode = seed / 168 % 3; c.mutation = seed / 7 % 3; c.flags = seed / 5 % 64;
    c.guid = guidMode == 0 ? -1 : guidMode == 1 ? 101 : guidMode == 2 ? 999 : 103;
    void* manager = c.manager; std::memcpy(reinterpret_cast<char*>(c.scene) + 0x100, &manager, 8);
    void* slots = c.slots; std::memcpy(reinterpret_cast<char*>(c.descriptor) + 0xe0, &slots, 8);
    std::memcpy(reinterpret_cast<char*>(c.descriptor) + 0xe8, &c.count, 4); std::memcpy(reinterpret_cast<char*>(c.descriptor) + 0xec, &c.capacity, 4);
    for (unsigned i = 0; i < 6; ++i) {
        void* table = (i % 3 == 2 ? sceneOtherTable : sceneTechniqueTable) + 2;
        std::memcpy(c.objects[i], &table, 8);
        long long guid = 100 + i; std::memcpy(reinterpret_cast<char*>(c.objects[i]) + 0x10, &guid, 8);
        c.slots[i] = c.mode == 2 && i == 0 && c.guid == -1 ? NULL : c.objects[i];
    }
}
}

TL_TEST(particle_scene_event_recovery)
{
    autotest::Coverage coverage("particle_scene_event_recovery", 0x76f690);
    for (unsigned seed = 0; seed < 504; ++seed) for (unsigned guid = 0; guid < 4; ++guid) {
        Case c; setup(c, seed, guid); autotest::Outcome a, b;
        autotest::runChild(original, &c, a); autotest::runChild(candidate, &c, b);
        if (coverage.observe(host, a, b)) {
            host->log("    particle event seed %u guid %u status %d/%d issue %u/%u bytes %lu/%lu\n", seed, guid, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue, (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host);
    Case negative; setup(negative, 193, 0); negative.negative = true; autotest::Outcome a, b;
    autotest::runChild(original, &negative, a); autotest::runChild(candidate, &negative, b);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    particle scene event negative control detected %u\n", detected ? 1 : 0);
    return !detected || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus || autotest::incomplete(a) || autotest::incomplete(b);
}
