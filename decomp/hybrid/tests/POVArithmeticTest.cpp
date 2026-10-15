#include <cstddef>
#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "POV.h"

TL_ORIGINAL(void, oldUpDown, (void*, float), "_ZN4CPOV16AccelerateUpDownEf")
TL_ORIGINAL(void, oldForward, (void*, float), "_ZN4CPOV10AccelerateEf")
TL_ORIGINAL(void, oldLateral, (void*, float), "_ZN4CPOV11AccelerateXEf")
TL_ORIGINAL(void, oldDamp, (void*, float), "_ZN4CPOV19DampContactVelocityEf")
TL_ORIGINAL(void, oldExtract, (void*), "_ZN4CPOV25ExtractOrientationVectorsEv")
TL_ORIGINAL(long long, oldFlying, (void*, float), "_ZN4CPOV14UpdateFlyingToEf")
extern "C" void newUpDown(void*, float) __asm__("_ZN4CPOV16AccelerateUpDownEf");
extern "C" void newForward(void*, float) __asm__("_ZN4CPOV10AccelerateEf");
extern "C" void newLateral(void*, float) __asm__("_ZN4CPOV11AccelerateXEf");
extern "C" void newDamp(void*, float) __asm__("_ZN4CPOV19DampContactVelocityEf");
extern "C" void newExtract(void*) __asm__("_ZN4CPOV25ExtractOrientationVectorsEv");
extern "C" long long newFlying(void*, float) __asm__("_ZN4CPOV14UpdateFlyingToEf");

namespace {
typedef char SizeProof[(sizeof(CPOV) == 0x198) ? 1 : -1];
typedef char VelocityProof[(offsetof(CPOV, m_fUnknown138) == 0x138) ? 1 : -1];
typedef char ActiveProof[(offsetof(CPOV, m_bUnknown179) == 0x179) ? 1 : -1];
typedef void (*Arithmetic)(void*, float);
struct Case { unsigned operation, seed; };
float bits(uint32_t value) { float f; std::memcpy(&f, &value, sizeof(f)); return f; }
void put(void* object, unsigned offset, float value) { std::memcpy(static_cast<char*>(object) + offset, &value, sizeof(value)); }
void side(void* raw, autotest::Capture& out, bool ours) {
    const Case& c = *static_cast<Case*>(raw);
    uint64_t object[sizeof(CPOV) / 8];
    unsigned char before[sizeof(CPOV)];
    uint32_t random = 0x9e3779b9u ^ c.seed;
    for (unsigned i = 0; i < sizeof(object); ++i) {
        random = random * 1664525u + 1013904223u;
        reinterpret_cast<unsigned char*>(object)[i] = random >> 24;
    }
    for (unsigned offset = 0xd8; offset <= 0x144; offset += 4)
        put(object, offset, float(int((c.seed * 13 + offset) % 37) - 18) / 8.0f);
    float argument = float(int(c.seed % 11) - 5) / 4.0f;
    const uint32_t special[] = {0, 0x80000000u, 0x7f800000u, 0xff800000u, 0x7fc12345u, 1, 0x00800000u, 0x7f7fffffu};
    if (c.operation < 4 && c.seed >= 32) {
        unsigned index = (c.seed - 32) / 2;
        if (c.seed & 1) argument = bits(special[index]);
        else put(object, 0x138 + ((c.seed / 2) % 3) * 4, bits(special[index]));
    }
    if (c.operation == 4) {
        // Matrix extraction copies all bits, including signed zero and NaN payloads.
        for (unsigned i = 0; i < 16; ++i) {
            put(object, 0x18 + 4 * i, bits(special[(i + c.seed) % 8]));
            put(object, 0x58 + 4 * i, float(int(i * 7 + c.seed) - 31) / 3.0f);
        }
    }
    if (c.operation == 5) {
        reinterpret_cast<unsigned char*>(object)[0x179] = c.seed % 3 != 0;
        const unsigned variant = c.seed / 3;
        put(object, 0xd8, 0.0f); put(object, 0xdc, 0.0f); put(object, 0xe0, 0.0f);
        float x = float(int(variant % 7) - 3) / 16.0f;
        float y = float(int(variant % 5) - 2) / 32.0f;
        float z = float(int(variant % 3) - 1) / 64.0f;
        if (variant < 8) {
            const uint32_t thresholds[] = {0, 0x80000000u, 0x3c23d709u, 0x3c23d70au, 0x3c23d70bu, 1, 0x7f800000u, 0x7fc12345u};
            x = bits(thresholds[variant]); y = z = 0;
        } else if (variant < 16) {
            x = 0.0f; y = bits(special[variant - 8]); z = -0.0f;
        } else if (variant < 24) {
            x = 0.0f; y = -0.0f; z = bits(special[variant - 16]);
        }
        // A NaN on one axis must still interpolate the other, finite axes.
        if (variant == 7) { y = 2.0f; z = -3.0f; }
        if (variant == 15) { x = 2.0f; z = -3.0f; }
        if (variant == 23) { x = 2.0f; y = -3.0f; }
        put(object, 0x17c, x); put(object, 0x180, y); put(object, 0x184, z);
        if (variant >= 24) {
            put(object, 0xd8, -x * 2); put(object, 0xdc, y * 3); put(object, 0xe0, -z * 4);
        }
        argument = bits(special[c.seed % 8]);
    }
    std::memcpy(before, object, sizeof(before));
    if (c.operation == 4) {
        typedef void (*Extract)(void*);
        autotest::invoke<Extract, void*>(out, ours ? newExtract : oldExtract, object);
    } else if (c.operation == 5) {
        typedef long long (*Flying)(void*, float);
        autotest::invoke<Flying, void*, float>(out, ours ? newFlying : oldFlying, object, argument);
        if (!reinterpret_cast<unsigned char*>(object)[0x179] && std::memcmp(before, object, sizeof(object)))
            out.issue = autotest::Capture::InvalidReport;
    } else {
        Arithmetic oldFunctions[] = {oldUpDown, oldForward, oldLateral, oldDamp};
        Arithmetic newFunctions[] = {newUpDown, newForward, newLateral, newDamp};
        autotest::invoke<Arithmetic, void*, float>(out, ours ? newFunctions[c.operation] : oldFunctions[c.operation], object, argument);
    }
    out.add(object, sizeof(object));
}
void original(void* c, autotest::Capture& out) { side(c, out, false); }
void candidate(void* c, autotest::Capture& out) { side(c, out, true); }
int run(const tlhybrid_host* host, unsigned operation, const char* name, uintptr_t address) {
    autotest::Coverage coverage(name, address);
    const unsigned count = operation == 5 ? 96 : 48;
    for (unsigned seed = 0; seed < count; ++seed) {
        Case c = {operation, seed};
        autotest::Outcome before, after;
        autotest::runChild(original, &c, before);
        autotest::runChild(candidate, &c, after);
        if (coverage.observe(host, before, after)) {
            host->log("    POV operation %u seed %u exits %d/%d\n", operation, seed, before.childStatus, after.childStatus);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host); return 0;
}
}
TL_TEST(pov_accelerate_up_down) { return run(host, 0, "pov_accelerate_up_down", reinterpret_cast<uintptr_t>(&oldUpDown)); }
TL_TEST(pov_accelerate_forward) { return run(host, 1, "pov_accelerate_forward", reinterpret_cast<uintptr_t>(&oldForward)); }
TL_TEST(pov_accelerate_lateral) { return run(host, 2, "pov_accelerate_lateral", reinterpret_cast<uintptr_t>(&oldLateral)); }
TL_TEST(pov_damp_contact) { return run(host, 3, "pov_damp_contact", reinterpret_cast<uintptr_t>(&oldDamp)); }
TL_TEST(pov_extract_orientation) { return run(host, 4, "pov_extract_orientation", reinterpret_cast<uintptr_t>(&oldExtract)); }
TL_TEST(pov_update_flying_to) { return run(host, 5, "pov_update_flying_to", reinterpret_cast<uintptr_t>(&oldFlying)); }
