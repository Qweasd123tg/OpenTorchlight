#include <Ogre.h>
#include "AutoTest.h"
#include "ColorWrapper.h"
#include "ParticleNativeOwners.h"
#include "SystemsFixtureWorker.h"

TL_ORIGINAL(void, colorOriginalCtor, (CColorWrapper*, CResourceManager*),
            "_ZN13CColorWrapperC1EP16CResourceManager")
TL_ORIGINAL(void, colorOriginalSet, (CColorWrapper*, float*, unsigned int),
            "_ZN13CColorWrapper9setColorsEPfj")
TL_ORIGINAL(float*, colorOriginalGet, (CColorWrapper*, unsigned int&),
            "_ZN13CColorWrapper9getColorsERj")
extern "C" float* colorRecoveredGet(CColorWrapper*, unsigned int&)
    __asm__("_ZN13CColorWrapper9getColorsERj");

namespace {
CResourceManager* resources;
struct Case { unsigned int index; bool negative; };

void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    union Storage { long double alignment; char bytes[sizeof(CColorWrapper)]; } storage;
    std::memset(storage.bytes, 0x5a, sizeof(storage.bytes));
    CColorWrapper* wrapper = reinterpret_cast<CColorWrapper*>(storage.bytes);
    colorOriginalCtor(wrapper, resources);

    // Exercise rebuilding both an empty cache and a previously allocated one.
    if (c.index % 4 == 1)
    {
        unsigned int previous;
        colorOriginalGet(wrapper, previous);
    }
    else if (c.index % 4 >= 2)
        for (unsigned int i = 0; i < 37; ++i)
            wrapper->m_colors.add(float(i) * -0.25f);

    float colors[90];
    const unsigned int counts[] = {0, 1, 2, 3, 7, 18};
    unsigned int count = counts[c.index % 6];
    for (unsigned int i = 0; i < count; ++i)
    {
        // Descending/duplicate/out-of-range times go through the native affector.
        colors[5 * i] = c.index & 8 ? float((count - i) % 3) : float(count - i) * 0.125f - 0.5f;
        for (unsigned int component = 1; component < 5; ++component)
            colors[5 * i + component] = float(int(i * 7 + component * 3) - 19) * 0.0625f;
    }
    if (c.index != 0)
        colorOriginalSet(wrapper, colors, count * 5);

    typedef float* (*Get)(CColorWrapper*, unsigned int&);
    Get get = ours ? colorRecoveredGet : colorOriginalGet;
    unsigned int number = 0xdeadbeef;
    if (!autotest::beginInvocation(out, get))
        return;
    float* result = get(wrapper, number);
    out.callCompleted = 1;
    if (number > 90 || number != wrapper->m_colors.size() || result != &wrapper->m_colors[0])
    {
        out.issue = autotest::Capture::InvalidReport;
        return;
    }
    if (ours && c.negative && number)
        result[0] += 1.0f;
    out.add(&number, sizeof(number));
    bool empty = result == NULL;
    out.add(&empty, sizeof(empty));
    out.add(result, number * sizeof(float));
    out.addHeapInUse();
}

void before(void* p, autotest::Capture& out) { side(p, out, false); }
void after(void* p, autotest::Capture& out) { side(p, out, true); }

int worker(const tlhybrid_host* host)
{
    resources = particleNativeOwners(0).resources;
    autotest::Coverage coverage("color_wrapper_get_colors", 0xa1e2e0);
    for (unsigned int i = 0; i < 24; ++i)
    {
        Case c = {i, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b))
        {
            host->log("    color case %u status %d/%d issue %u/%u bytes %lu/%lu\n",
                      i, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue,
                      (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            coverage.report(host);
            return 1;
        }
    }
    coverage.report(host);
    Case c = {7, true};
    autotest::Outcome a, b;
    autotest::runChild(before, &c, a, 2000, 10000);
    autotest::runChild(after, &c, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length ||
                    std::memcmp(a.capture.data, b.capture.data, a.capture.length) != 0;
    return coverage.completed != 24 || !detected || autotest::incomplete(a) ||
           autotest::incomplete(b) || !a.reportValid || !b.reportValid ||
           a.childStatus || b.childStatus;
}
}

TL_TEST(color_wrapper_get_colors)
{
    return systems_fixture::isolated(worker, host);
}
