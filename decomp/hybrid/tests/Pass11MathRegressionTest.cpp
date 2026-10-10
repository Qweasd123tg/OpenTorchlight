// Strict pass11 preservation evidence. C++98, original-versus-recovered only.
// No epsilon comparison, NaN canonicalisation, or counting crashed cases.
#include <cerrno>
#include <cmath>
#include <cstring>
#include <OgreCamera.h>
#include "UtilitiesMath.h"
#include "AutoTest.h"

TL_ORIGINAL(Ogre::Vector3, pass11OldRay, (Ogre::Camera*, float, float, float, float),
            "_ZN4MATH16screenToWorldRayEPN4Ogre6CameraEffff")
TL_ORIGINAL(void, pass11OldPerspective, (Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Matrix4&),
            "_ZN4MATH23worldToLocalPerspectiveERN4Ogre7Vector3ERKS1_RKNS0_7Matrix4E")
TL_ORIGINAL(void, pass11OldRotateX, (Ogre::Vector3*, float), "_ZN4MATH7rotateXEPN4Ogre7Vector3Ef")
TL_ORIGINAL(void, pass11OldRotateY, (Ogre::Vector3*, float), "_ZN4MATH7rotateYEPN4Ogre7Vector3Ef")

namespace
{
struct Case { unsigned mode, seed; };

float bits(uint32_t word)
{
    float value;
    std::memcpy(&value, &word, sizeof(value));
    return value;
}

// Includes both zero signs, both infinity signs, and distinct signed quiet NaNs.
// All are valid IEEE float data; no null/dangling objects or invalid references.
float edge(unsigned i)
{
    static const uint32_t words[] = {
        0x00000000u, 0x80000000u, 0x3f800000u, 0xbf800000u,
        0x3f000000u, 0xbe800000u, 0x00800000u, 0x80800000u,
        0x00000001u, 0x80000001u, 0x7f7fffffu, 0xff7fffffu,
        0x7f800000u, 0xff800000u, 0x7fc12345u, 0xffc54321u
    };
    return bits(words[i % 16]);
}

float finite(autotest::Rng& rng)
{
    return (float(int(rng.next() % 8193) - 4096)) / 32.0f;
}

struct GuardedVector
{
    uint32_t before[4];
    Ogre::Vector3 value;
    uint32_t after[4];
};

void init(GuardedVector& v)
{
    std::memset(&v, 0xa5, sizeof(v));
    v.value = Ogre::Vector3(31.0f, -73.0f, 123.0f);
}

void perspective(const Case& c, autotest::Capture& out, bool ours)
{
    autotest::Rng rng(c.seed + 19);
    GuardedVector point, result;
    init(point);
    init(result);
    // Draw separately: evaluation order of constructor arguments is unspecified.
    point.value.x = finite(rng);
    point.value.y = finite(rng);
    point.value.z = finite(rng);
    Ogre::Matrix4 matrix;
    for (unsigned row = 0; row < 4; ++row)
        for (unsigned col = 0; col < 4; ++col)
            matrix[row][col] = finite(rng) / 16.0f;

    if (c.seed < 256)
    {
        // Dense matrices plus identity/diagonal matrices; positive, negative,
        // and zero depth. Translation/homogeneous entries remain nonzero bait.
        if (c.seed % 4 != 0)
        {
            for (unsigned row = 0; row < 3; ++row)
                for (unsigned col = 0; col < 3; ++col)
                    matrix[row][col] = row == col ? 1.0f : 0.0f;
            if (c.seed % 4 == 1) point.value.z = 0.25f + c.seed;
            if (c.seed % 4 == 2) point.value.z = -0.25f - c.seed;
            if (c.seed % 4 == 3) point.value.z = 0.0f;
        }
    }
    else
    {
        const unsigned s = c.seed - 256;
        for (unsigned row = 0; row < 3; ++row)
            for (unsigned col = 0; col < 3; ++col)
                matrix[row][col] = row == col ? 1.0f : 0.0f;
        point.value.x = edge(s);
        point.value.y = edge(s / 16);
        point.value.z = edge((s + s / 16) % 16);
        // A quarter of edge cases put the exceptional value in a matrix operand.
        if (s % 4 == 3)
        {
            point.value = Ogre::Vector3(1.25f, -2.5f, 4.0f);
            matrix[(s / 4) % 3][(s / 16) % 3] = edge(s / 4);
        }
    }
    Ogre::Vector3& target = (c.seed & 1) ? point.value : result.value;
    typedef void (*Fn)(Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Matrix4&);
    autotest::invoke<Fn, Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Matrix4&>(
        out, ours ? &MATH::worldToLocalPerspective : &pass11OldPerspective,
        target, point.value, matrix);
    out.add(&point, sizeof(point));
    out.add(&result, sizeof(result));
    out.add(&matrix, sizeof(matrix));
}

void rotate(const Case& c, autotest::Capture& out, bool ours)
{
    autotest::Rng rng(c.seed + 53);
    GuardedVector vector;
    init(vector);
    vector.value.x = finite(rng);
    vector.value.y = finite(rng);
    vector.value.z = finite(rng);
    float angle = finite(rng);
    if (c.seed < 256)
    {
        static const float angles[] = {
            0.0f, -0.0f, 1.5707963267948966f, -1.5707963267948966f,
            3.1415926535897932f, -3.1415926535897932f,
            6.2831853071795864f, -6.2831853071795864f,
            0.000001f, -0.000001f, 100000.0f, -100000.0f
        };
        if (c.seed % 3) angle = angles[c.seed % 12];
        if (c.seed % 8 == 0) vector.value.z = 0.0f;
        if (c.seed % 8 == 1) vector.value.z = -0.0f;
    }
    else
    {
        unsigned s = c.seed - 256;
        angle = edge(s / 16);
        vector.value.x = edge(s);
        vector.value.y = edge((s + 5) % 16);
        vector.value.z = edge((s + 9) % 16);
    }
    typedef void (*Fn)(Ogre::Vector3*, float);
    Fn fn = c.mode == 2 ? (ours ? &MATH::rotateX : &pass11OldRotateX)
                          : (ours ? &MATH::rotateY : &pass11OldRotateY);
    errno = 0;
    autotest::invoke(out, fn, &vector.value, angle);
    int savedErrno = errno;
    out.add(&vector, sizeof(vector)); // Includes the untouched axis and guards.
    out.add(&angle, sizeof(angle));
    out.add(&savedErrno, sizeof(savedErrno));
}

// Verified from original c7a4b0: virtual calls at byte offsets 260,270,2d8,2e0.
// Shipped libOgreMain-1.6.5.so: Camera::getOrientation at 133210 is
// `lea 0x4b8(%rdi),%rax; ret`. No constructors, renderer, or scene required.
const unsigned kNearSlot = 0x260 / sizeof(void*);
const unsigned kFarSlot = 0x270 / sizeof(void*);
const unsigned kProjectionSlot = 0x2d8 / sizeof(void*);
const unsigned kViewSlot = 0x2e0 / sizeof(void*);
const unsigned kOrientationOffset = 0x4b8;
void* cameraVtable[kViewSlot + 1];
unsigned char cameraStorage[sizeof(Ogre::Camera) + 32] __attribute__((aligned(16)));
Ogre::Camera* cameraObject;
Ogre::Matrix4 projectionMatrix, viewMatrix;
float nearDistance, farDistance;
autotest::Capture* cameraCapture;
unsigned cameraCalls;

void unexpectedCameraCall() { _exit(71); }

void cameraEvent(const void* self, unsigned tag)
{
    if (self != cameraObject || tag != ++cameraCalls) _exit(72);
    cameraCapture->add(&tag, sizeof(tag));
}
float getNear(const void* self)
{
    cameraEvent(self, 1);
    cameraCapture->add(&nearDistance, sizeof(nearDistance));
    return nearDistance;
}
float getFar(const void* self)
{
    cameraEvent(self, 2);
    cameraCapture->add(&farDistance, sizeof(farDistance));
    return farDistance;
}
const Ogre::Matrix4& getProjection(const void* self)
{
    cameraEvent(self, 3);
    cameraCapture->add(&projectionMatrix, sizeof(projectionMatrix));
    return projectionMatrix;
}
const Ogre::Matrix4& getView(const void* self)
{
    cameraEvent(self, 4);
    cameraCapture->add(&viewMatrix, sizeof(viewMatrix));
    return viewMatrix;
}

void ray(const Case& c, autotest::Capture& out, bool ours)
{
    if (sizeof(void*) != 8 || sizeof(Ogre::Vector3) != 12 ||
        kOrientationOffset + sizeof(Ogre::Quaternion) > sizeof(Ogre::Camera)) _exit(73);
    std::memset(cameraStorage, 0xa5, sizeof(cameraStorage));
    cameraObject = reinterpret_cast<Ogre::Camera*>(cameraStorage + 16);
    for (unsigned i = 0; i <= kViewSlot; ++i)
        cameraVtable[i] = reinterpret_cast<void*>(&unexpectedCameraCall);
    cameraVtable[kNearSlot] = reinterpret_cast<void*>(&getNear);
    cameraVtable[kFarSlot] = reinterpret_cast<void*>(&getFar);
    cameraVtable[kProjectionSlot] = reinterpret_cast<void*>(&getProjection);
    cameraVtable[kViewSlot] = reinterpret_cast<void*>(&getView);
    void** vptr = cameraVtable;
    std::memcpy(cameraStorage + 16, &vptr, sizeof(vptr));

    Ogre::Quaternion orientation;
    switch (c.seed % 8)
    {
    case 0: orientation = Ogre::Quaternion(1, 0, 0, 0); break;
    case 1: orientation = Ogre::Quaternion(0, 1, 0, 0); break;
    case 2: orientation = Ogre::Quaternion(0, 0, 1, 0); break;
    case 3: orientation = Ogre::Quaternion(0, 0, 0, 1); break;
    case 4: orientation = Ogre::Quaternion(0.5f, 0.5f, 0.5f, 0.5f); break;
    case 5: orientation = Ogre::Quaternion(-0.5f, 0.5f, -0.5f, 0.5f); break;
    case 6: orientation = Ogre::Quaternion(0.7071067811865475f, 0.7071067811865475f, 0, 0); break;
    default: orientation = Ogre::Quaternion(0.7071067811865475f, 0, -0.7071067811865475f, 0); break;
    }
    std::memcpy(cameraStorage + 16 + kOrientationOffset, &orientation, sizeof(orientation));
    if (reinterpret_cast<const unsigned char*>(&cameraObject->getOrientation()) !=
        cameraStorage + 16 + kOrientationOffset) _exit(74);

    projectionMatrix = Ogre::Matrix4::IDENTITY;
    projectionMatrix[0][0] = 0.5f + float(c.seed % 11) / 4.0f;
    projectionMatrix[1][1] = 0.75f + float(c.seed % 13) / 8.0f;
    projectionMatrix[0][2] = 0.125f;
    projectionMatrix[1][2] = -0.25f;
    projectionMatrix[2][2] = -1.01f;
    projectionMatrix[2][3] = -0.2f;
    projectionMatrix[3][2] = -1.0f;
    projectionMatrix[3][3] = 0.0f;
    // Always invertible: exercise the real Matrix4::inverse dependency.
    viewMatrix = Ogre::Matrix4::IDENTITY;
    viewMatrix[0][0] = 1.0f + float(c.seed % 5) / 8.0f;
    viewMatrix[1][1] = 1.0f + float(c.seed % 7) / 8.0f;
    viewMatrix[2][2] = 1.0f + float(c.seed % 9) / 8.0f;
    viewMatrix[0][1] = float(c.seed % 3) / 8.0f;
    viewMatrix[0][3] = float(c.seed) - 129.0f;
    viewMatrix[1][3] = float(c.seed) / 4.0f;
    viewMatrix[2][3] = -17.0f;
    nearDistance = 0.125f + float(c.seed % 17) / 4.0f;
    farDistance = 20.0f + float(c.seed) * 1.75f;
    float width = 320.0f + float(c.seed % 19) * 93.0f;
    float height = 200.0f + float(c.seed % 23) * 57.0f;
    static const float positions[] = {0, 1, 0.5f, 0.25f, 0.75f, -0.25f, 1.25f};
    float x = width * positions[c.seed % 7];
    float y = height * positions[(c.seed / 7) % 7];
    // Zero ray and both sides of Ogre's 1e-8 normalise threshold.
    if (c.seed % 16 == 0) farDistance = nearDistance;
    if (c.seed % 16 == 1 || c.seed % 16 == 2)
    {
        nearDistance = 0.0f;
        farDistance = c.seed % 16 == 1 ? 1e-9f : 1e-7f;
        x = width * 0.5f;
        y = height * 0.5f;
    }
    // Additional IEEE propagation checks; dimensions and collaborators stay valid.
    if (c.seed >= 256)
    {
        x = edge(c.seed - 256);
        if (c.seed & 16) y = edge((c.seed - 256) / 2);
    }
    cameraCapture = &out;
    cameraCalls = 0;
    typedef Ogre::Vector3 (*Fn)(Ogre::Camera*, float, float, float, float);
    autotest::invoke<Fn, Ogre::Camera*, float, float, float, float>(
        out, ours ? &MATH::screenToWorldRay : &pass11OldRay,
        cameraObject, x, y, width, height);
    if (cameraCalls != 4) _exit(75);
    out.add(&cameraCalls, sizeof(cameraCalls));
    out.add(cameraStorage, sizeof(cameraStorage));
    out.add(cameraVtable, sizeof(cameraVtable));
    out.add(&projectionMatrix, sizeof(projectionMatrix));
    out.add(&viewMatrix, sizeof(viewMatrix));
    out.add(&nearDistance, sizeof(nearDistance));
    out.add(&farDistance, sizeof(farDistance));
}

void side(void* data, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<const Case*>(data);
    if (c.mode == 0) ray(c, out, ours);
    else if (c.mode == 1) perspective(c, out, ours);
    else rotate(c, out, ours);
}
void originalSide(void* data, autotest::Capture& out) { side(data, out, false); }
void recoveredSide(void* data, autotest::Capture& out) { side(data, out, true); }

int run(const tlhybrid_host* host, unsigned mode)
{
    const char* names[] = {
        "pass11_existing_screen_world_ray", "pass11_existing_world_local_perspective",
        "pass11_existing_rotate_x", "pass11_existing_rotate_y"
    };
    void* originals[] = {
        reinterpret_cast<void*>(&pass11OldRay), reinterpret_cast<void*>(&pass11OldPerspective),
        reinterpret_cast<void*>(&pass11OldRotateX), reinterpret_cast<void*>(&pass11OldRotateY)
    };
    const unsigned counts[] = {320, 512, 512, 512};
    autotest::Coverage coverage(names[mode], (uint64_t)(uintptr_t)originals[mode]);
    int failures = 0;
    for (unsigned i = 0; i < counts[mode]; ++i)
    {
        Case c = {mode, i};
        autotest::Outcome a, b;
        autotest::runChild(originalSide, &c, a);
        autotest::runChild(recoveredSide, &c, b);
        const int result = coverage.observe(host, a, b);
        if (result || autotest::incomplete(a) || autotest::incomplete(b) || a.childStatus || b.childStatus)
        {
            if (failures < 12)
                host->log("    pass11 math mode %u case %u result %d exits %d/%d\n",
                          mode, i, result, a.childStatus, b.childStatus);
            ++failures;
        }
    }
    coverage.report(host);
    // Every requested case must complete. Equal crashes never satisfy coverage.
    if (coverage.completed != counts[mode] || coverage.completed < 20 || coverage.missing)
        return 1;
    return failures ? 1 : 0;
}
} // namespace

TL_TEST(pass11_existing_screen_world_ray) { return run(host, 0); }
TL_TEST(pass11_existing_world_local_perspective) { return run(host, 1); }
TL_TEST(pass11_existing_rotate_x) { return run(host, 2); }
TL_TEST(pass11_existing_rotate_y) { return run(host, 3); }
