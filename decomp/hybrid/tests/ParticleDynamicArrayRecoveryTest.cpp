#include "AutoTest.h"
#include "ParticlePropertyConversions.h"
#include "SystemsFixtureWorker.h"

TL_ORIGINAL(float*, originalDynamicArray, (ParticleUniverse::DynamicAttribute*, unsigned int&), "_Z19getArrayFromDynPropPN16ParticleUniverse16DynamicAttributeERj")
extern "C" float* recoveredDynamicArray(ParticleUniverse::DynamicAttribute*, unsigned int&) __asm__("_Z19getArrayFromDynPropPN16ParticleUniverse16DynamicAttributeERj");

namespace {
using namespace ParticleUniverse;
struct Case { unsigned index; bool negative; };
class OtherAttribute : public DynamicAttribute {
public:
    unsigned calls;
    OtherAttribute(int type) : calls(0) { mType = static_cast<DynamicAttributeType>(type); }
    virtual float getValue(Particle*, float) { ++calls; return -7.25f; }
    virtual void copyAttributesTo(DynamicAttribute*) {}
};

void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    DynamicAttribute* attribute = NULL;
    OtherAttribute* other = NULL;
    unsigned kind = c.index % 12;
    const unsigned sizes[] = {0, 1, 2, 3, 7, 18};
    unsigned size = sizes[(c.index / 12) % 6];
    if (kind == 0) {
        DynamicAttributeFixed* fixed = new DynamicAttributeFixed;
        fixed->setValue(float(int(c.index) - 31) * 0.125f);
        attribute = fixed;
    } else if (kind == 1) {
        DynamicAttributeRandom* random = new DynamicAttributeRandom;
        random->setMinMax(float(c.index) * -0.25f, float(c.index) * 0.125f);
        attribute = random;
    } else if (kind < 4) {
        DynamicAttributeCurved* curve = new DynamicAttributeCurved(static_cast<InterpolationType>(kind - 2));
        for (unsigned i = 0; i < size; ++i)
            curve->addControlPoint(float(int(size - i) % 4) * 0.5f, float(int(i * 13) - 21) * 0.125f);
        attribute = curve;
    } else if (kind < 6) {
        DynamicAttributeRandomCurved* curve = new DynamicAttributeRandomCurved(static_cast<InterpolationType>(kind - 4));
        for (unsigned i = 0; i < size; ++i)
            curve->addControlPoint(float(i % 4) * 0.5f, float(int(i * 7) - 11), float(int(i * 13) - 3));
        attribute = curve;
    } else {
        const int types[] = {2, 4, 3, -1, 7, 0};
        attribute = other = new OtherAttribute(types[kind - 6]);
    }
    m_DynamicArrayForProperties.clear();
    if (c.index & 1)
        for (unsigned i = 0; i < 37; ++i) m_DynamicArrayForProperties.add(float(i) * -0.25f);
    typedef float* (*Call)(DynamicAttribute*, unsigned int&);
    Call call = ours ? recoveredDynamicArray : originalDynamicArray;
    unsigned count = 0xdeadbeef;
    if (!autotest::beginInvocation(out, call)) return;
    float* result = call(attribute, count);
    out.callCompleted = 1;
    if (count > 64 || count != m_DynamicArrayForProperties.size() || result != &m_DynamicArrayForProperties[0]) {
        out.issue = autotest::Capture::InvalidReport; return;
    }
    unsigned reported = count + (ours && c.negative ? 1 : 0);
    out.add(&reported, sizeof(reported));
    bool empty = result == NULL;
    out.add(&empty, sizeof(empty));
    out.add(result, count * sizeof(float));
    unsigned calls = other ? other->calls : 0;
    out.add(&calls, sizeof(calls));
    delete attribute;
    out.addHeapInUse();
}

void before(void* p, autotest::Capture& out) { side(p, out, false); }
void after(void* p, autotest::Capture& out) { side(p, out, true); }
int worker(const tlhybrid_host* host)
{
    autotest::Coverage coverage("particle_dynamic_array_recovery", 0xa31c00);
    for (unsigned i = 0; i < 144; ++i) {
        Case c = {i, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    dynamic array seed%u status%d/%d issue%u/%u bytes%lu/%lu\n", i, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue, (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host);
    Case c = {7, true};
    autotest::Outcome a, b;
    autotest::runChild(before, &c, a, 2000, 10000);
    autotest::runChild(after, &c, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    return !detected || autotest::incomplete(a) || autotest::incomplete(b) || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus;
}
}
TL_TEST(particle_dynamic_array_recovery) { return systems_fixture::isolated(worker, host); }
