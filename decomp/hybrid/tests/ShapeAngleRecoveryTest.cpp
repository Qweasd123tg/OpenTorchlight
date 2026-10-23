#include <cmath>
#include <cstring>
#include <fenv.h>
#include <utility>
#include <OgreVector3.h>
#include "AutoTest.h"
#include "tests/Detour.h"

typedef std::pair<bool, float> ShapeAngleResult;
TL_ORIGINAL(ShapeAngleResult, shapeAngleOriginal, (void*, float, const Ogre::Vector3&, float), "_ZN6CShape23positionIntersectsAngleEfRKN4Ogre7Vector3Ef")
extern "C" ShapeAngleResult shapeAngleCandidate(void*, float, const Ogre::Vector3&, float) __asm__("_ZN6CShape23positionIntersectsAngleEfRKN4Ogre7Vector3Ef");
TL_FUNCTION(anglePosition, "_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(angleMinimum, "_ZN6CShape21getMinRadiusAtPercentEf")
TL_FUNCTION(angleMaximum, "_ZN6CShape21getMaxRadiusAtPercentEf")
TL_FUNCTION(angleRelease, "_ZN6CShape26getAngleOfReleaseAtPercentEf")
TL_FUNCTION(angleOffset, "_ZN6CShape23getAngleOffsetAtPercentEf")

namespace {
struct Case {
    unsigned seed, mutation;
    float percent, radius, minimum, maximum, release, offset;
    Ogre::Vector3 point, origin, forward;
    bool negative;
};
Case* input; autotest::Capture* output; void* object; Ogre::Vector3* point; unsigned calls;
void number(unsigned n) { output->add(&n, 4); }
void floating(float n) { output->add(&n, 4); }
void observe(unsigned event, void* self)
{
    if (self != object) output->issue = autotest::Capture::InvalidReport;
    number(event); ++calls; output->add(point, 12);
    if (input->mutation == event) {
        point->x += 0.75f; point->z -= 0.125f;
        reinterpret_cast<unsigned char*>(object)[0x134] ^= static_cast<unsigned char>(event);
    }
}
Ogre::Vector3 position(void* self, bool absolute)
{
    observe(1, self); number(absolute);
    if (!absolute) output->issue = autotest::Capture::InvalidReport;
    return input->origin;
}
float minimum(void* self, float percent) { observe(2, self); floating(percent); return input->minimum; }
float maximum(void* self, float percent) { observe(3, self); floating(percent); return input->maximum; }
float release(void* self, float percent) { observe(4, self); floating(percent); return input->release; }
float offset(void* self, float percent) { observe(5, self); floating(percent); return input->offset; }
Ogre::Vector3 forward(void* self) { observe(6, self); return input->forward; }
void side(void* raw, autotest::Capture& out, bool ours)
{
    Case c = *static_cast<Case*>(raw); input = &c; output = &out; calls = 0;
    uint64_t storage[0x168 / 8]; std::memset(storage, 0xa5, sizeof(storage)); object = storage;
    void* table[0x140 / 8] = {0}; table[0x138 / 8] = reinterpret_cast<void*>(&forward);
    void* vtable = table; std::memcpy(storage, &vtable, 8);
    Ogre::Vector3 value = c.point; point = &value;
    detour::Set redirects;
    TL_REDIRECT(redirects, anglePosition, &position); TL_REDIRECT(redirects, angleMinimum, &minimum);
    TL_REDIRECT(redirects, angleMaximum, &maximum); TL_REDIRECT(redirects, angleRelease, &release); TL_REDIRECT(redirects, angleOffset, &offset);
    if (redirects.failed()) { out.issue = autotest::Capture::InvalidReport; return; }
    feclearexcept(FE_ALL_EXCEPT);
    typedef ShapeAngleResult (*Function)(void*, float, const Ogre::Vector3&, float);
    Function fn = ours ? shapeAngleCandidate : shapeAngleOriginal;
    if (!autotest::beginInvocation(out, fn)) return;
    ShapeAngleResult result = fn(storage, c.percent, value, c.radius);
    out.callCompleted = 1;
    if (ours && c.negative) result.first = !result.first;
    int exceptions = fetestexcept(FE_ALL_EXCEPT);
    number(result.first); floating(result.second); number(exceptions); number(calls);
    out.add(&value, 12); out.add(storage, sizeof(storage));
}
void original(void* p, autotest::Capture& out) { side(p, out, false); }
void candidate(void* p, autotest::Capture& out) { side(p, out, true); }
float fromBits(unsigned bits) { float value; std::memcpy(&value, &bits, 4); return value; }
void setup(Case& c, unsigned seed)
{
    const float radii[] = {0, 0.125f, 1, 3, -0.25f, 8};
    const float releases[] = {0, 15, 45, 90, 180, 270, 359.9f, 360, 720, -45, -180, -360};
    const float offsets[] = {0, -15, -45, -90, -180, -270, -360, 45, 360, 720};
    const Ogre::Vector3 directions[] = {
        Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 1), Ogre::Vector3(1, 0, 0), Ogre::Vector3(0, 0, -1), Ogre::Vector3(-1, 0, 0),
        Ogre::Vector3(1, 0, 1), Ogre::Vector3(-1, 0, 1), Ogre::Vector3(1, 0, -1), Ogre::Vector3(-1, 0, -1), Ogre::Vector3(1e-9f, 0, 0), Ogre::Vector3(3, 0, 4)
    };
    c.seed = seed; c.mutation = seed / 13 % 7; c.percent = static_cast<float>(int(seed % 9) - 3) * 0.25f;
    c.radius = radii[seed / 7 % 6]; c.release = releases[seed / 11 % 12]; c.offset = offsets[seed / 17 % 10];
    c.minimum = seed % 5 == 0 ? 4 : seed % 5 == 1 ? -1 : 0;
    c.maximum = seed % 7 == 0 ? 0 : seed % 7 == 1 ? 1 : 20;
    c.origin = Ogre::Vector3(float(int(seed % 5) - 2), float(seed % 3) * 7, float(int(seed % 7) - 3));
    c.point = c.origin + directions[seed % 11] * (seed % 4 + 1.0f);
    c.point.y = -13.0f;
    c.forward = directions[1 + seed / 19 % 8]; c.negative = false;
    if (seed >= 1400) {
        const unsigned exceptional[] = {0x80000000u, 0x7fc01234u, 0x7f800000u, 0xff800000u, 0x00000001u, 0x3f800000u};
        float value = fromBits(exceptional[(seed - 1400) % 6]);
        switch ((seed - 1400) / 6 % 10) {
        case 0: c.point.x = value; break;
        case 1: c.point.z = value; break;
        case 2: c.maximum = value; break;
        case 3: c.minimum = value; break;
        case 4: c.radius = value; break;
        case 5: c.release = value; break;
        case 6: c.offset = value; break;
        case 7: c.forward.x = value; break;
        case 8: c.forward.z = value; break;
        case 9: c.point.y = value; break;
        }
    }
}
}

TL_TEST(shape_angle_recovery)
{
    autotest::Coverage coverage("shape_angle_recovery", 0xa056b0);
    for (unsigned seed = 0; seed < 1580; ++seed) {
        Case c; setup(c, seed); autotest::Outcome a, b;
        autotest::runChild(original, &c, a); autotest::runChild(candidate, &c, b);
        if (coverage.observe(host, a, b)) {
            size_t at = 0; while (at < a.capture.length && at < b.capture.length && a.capture.data[at] == b.capture.data[at]) ++at;
            host->log("    shape angle seed %u status %d/%d issue %u/%u bytes %lu/%lu first %lu\n", seed, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue, (unsigned long)a.capture.length, (unsigned long)b.capture.length, (unsigned long)at);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host);
    Case c; setup(c, 97); c.negative = true; autotest::Outcome a, b;
    autotest::runChild(original, &c, a); autotest::runChild(candidate, &c, b);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    shape angle negative control detected %u\n", detected ? 1 : 0);
    return !detected || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus || autotest::incomplete(a) || autotest::incomplete(b);
}
