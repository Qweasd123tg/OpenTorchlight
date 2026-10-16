#include "AutoTest.h"
#include "Path.h"
#include <cmath>
#include <string>

TL_ORIGINAL(void, oldPathConstructor, (void*, std::string, bool, const Ogre::Vector3&), "_ZN5CPathC1ESsbRKN4Ogre7Vector3E")
TL_ORIGINAL(void, oldPathDestructor, (void*), "_ZN5CPathD1Ev")
TL_ORIGINAL(float, oldRightRadius, (CPath*, float), "_ZN5CPath21GetTweenedRadiusRightEf")
extern "C" float newRightRadius(CPath*, float) __asm__("_ZN5CPath21GetTweenedRadiusRightEf");
TL_ORIGINAL(float, oldLeftRadius, (CPath*, float), "_ZN5CPath20GetTweenedRadiusLeftEf")
extern "C" float newLeftRadius(CPath*, float) __asm__("_ZN5CPath20GetTweenedRadiusLeftEf");
TL_ORIGINAL(float, oldAngle, (CPath*, float, float), "_ZN5CPath20GetAngleOverDistanceEff")
extern "C" float newAngle(CPath*, float, float) __asm__("_ZN5CPath20GetAngleOverDistanceEff");
TL_ORIGINAL(Ogre::Vector3, oldSegment, (CPath*, unsigned), "_ZN5CPath14GetPathSegmentEj")
extern "C" Ogre::Vector3 newSegment(CPath*, unsigned) __asm__("_ZN5CPath14GetPathSegmentEj");
TL_ORIGINAL(Ogre::Vector3, oldPosition, (CPath*, float), "_ZN5CPath21GetPositionAtDistanceEf")
extern "C" Ogre::Vector3 newPosition(CPath*, float) __asm__("_ZN5CPath21GetPositionAtDistanceEf");
TL_ORIGINAL(Ogre::Vector3, oldPerpendicular, (CPath*, unsigned), "_ZN5CPath24GetSegmentPerpendicularYEj")
extern "C" Ogre::Vector3 newPerpendicular(CPath*, unsigned) __asm__("_ZN5CPath24GetSegmentPerpendicularYEj");

namespace {
struct Case { unsigned operation, index; };
template<class T> void record(autotest::Capture& out, const std::vector<T>& values)
{
    size_t size = values.size(); out.add(&size, sizeof(size));
    if (size) out.add(&values[0], size * sizeof(T));
}
void side(void* opaque, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(opaque);
    bool closed = (c.index / 28) & 1;
    unsigned shape = c.index / 56;
    Ogre::Vector3 origin(float(shape * 7), -float(shape), float(c.index % 3));
    CPath* path = static_cast<CPath*>(autotest::allocate(sizeof(CPath)));
    if (!path) { out.issue = autotest::Capture::InvalidReport; return; }
    oldPathConstructor(path, std::string("mass-path"), closed, origin);
    unsigned count = 4;
    if (c.operation == 3 || c.operation == 5) count = c.index % 5;
    for (unsigned i = 0; i < count; ++i) {
        path->m_lPoints.push_back(Ogre::Vector3(float(i * (shape + 1)), shape ? float(i % 2) : 0.0f, float((i * i) % 5)));
        path->m_lRadiusLeft.push_back(float(i * 5) - 11.0f);
        path->m_lRadiusRight.push_back(float(i * 7) + 3.0f);
        path->m_lSegmentAngle.push_back(float(i * 13) - 9.0f);
        float distance = i == 0 ? 0.0f : path->m_lPointDistance.back() +
            (path->m_lPoints[i] - path->m_lPoints[i - 1]).length();
        path->m_lPointDistance.push_back(distance);
    }
    path->m_fPathLength = count == 0 ? 1.0f : path->m_lPointDistance.back();
    if (closed && count > 1)
        path->m_fPathLength += (path->m_lPoints[0] - path->m_lPoints.back()).length();
    if (path->m_fPathLength == 0.0f) path->m_fPathLength = 1.0f;
    float length = path->m_fPathLength;
    const float fractions[] = {-2.25f, -1.0f, -0.5f, -0.0f, 0.0f, 0.001f, 0.1f, 0.25f, 0.5f, 0.75f, 0.999f, 1.0f, 1.25f, 2.0f};
    float distance = fractions[c.index % 14] * length;
    if (c.operation < 2) {
        float (*fn)(CPath*, float) = c.operation == 0 ?
            (ours ? newRightRadius : oldRightRadius) : (ours ? newLeftRadius : oldLeftRadius);
        if (!autotest::beginInvocation(out, fn)) return;
        float result = fn(path, distance); out.callCompleted = 1;
        out.add(&result, sizeof(result));
    } else if (c.operation == 2) {
        float to = fractions[(c.index + 5) % 14] * length;
        float (*fn)(CPath*, float, float) = ours ? newAngle : oldAngle;
        if (!autotest::beginInvocation(out, fn)) return;
        float result = fn(path, distance, to); out.callCompleted = 1;
        out.add(&result, sizeof(result));
    } else if (c.operation == 4) {
        Ogre::Vector3 (*fn)(CPath*, float) = ours ? newPosition : oldPosition;
        if (!autotest::beginInvocation(out, fn)) return;
        Ogre::Vector3 result = fn(path, distance); out.callCompleted = 1;
        out.add(&result, sizeof(result));
    } else {
        unsigned index = c.index % 7;
        // An open path has no last-to-first segment. The original does not
        // guard the one-past-end read for that invalid query.
        if (c.operation == 5 && !closed && count > 1 && index == count - 1) index = count;
        Ogre::Vector3 (*fn)(CPath*, unsigned) = c.operation == 3 ?
            (ours ? newSegment : oldSegment) : (ours ? newPerpendicular : oldPerpendicular);
        if (!autotest::beginInvocation(out, fn)) return;
        Ogre::Vector3 result = fn(path, index); out.callCompleted = 1;
        out.add(&result, sizeof(result));
    }
    out.add(path, sizeof(CPath));
    record(out, path->m_lPoints); record(out, path->m_lRadiusLeft); record(out, path->m_lRadiusRight);
    record(out, path->m_lSegmentAngle); record(out, path->m_lPointDistance);
    oldPathDestructor(path);
}
void original(void* c, autotest::Capture& out) { side(c, out, false); }
void candidate(void* c, autotest::Capture& out) { side(c, out, true); }
int run(const tlhybrid_host* host, unsigned operation, const char* name, uint64_t address)
{
    autotest::Coverage coverage(name, address);
    for (unsigned i = 0; i < 112; ++i) {
        Case c = {operation, i};
        autotest::Outcome& a = autotest::g_outcomes[0]; autotest::Outcome& b = autotest::g_outcomes[1];
        autotest::runChild(original, &c, a); autotest::runChild(candidate, &c, b);
        if (coverage.observe(host, a, b)) { coverage.report(host); return 1; }
    }
    coverage.report(host); return 0;
}
}
TL_TEST(mass_path_right_radius) { return run(host, 0, "mass_path_right_radius", (uint64_t)(uintptr_t)oldRightRadius); }
TL_TEST(mass_path_left_radius) { return run(host, 1, "mass_path_left_radius", (uint64_t)(uintptr_t)oldLeftRadius); }
TL_TEST(mass_path_angle) { return run(host, 2, "mass_path_angle", (uint64_t)(uintptr_t)oldAngle); }
TL_TEST(mass_path_segment) { return run(host, 3, "mass_path_segment", (uint64_t)(uintptr_t)oldSegment); }
TL_TEST(mass_path_position) { return run(host, 4, "mass_path_position", (uint64_t)(uintptr_t)oldPosition); }
TL_TEST(mass_path_perpendicular) { return run(host, 5, "mass_path_perpendicular", (uint64_t)(uintptr_t)oldPerpendicular); }
