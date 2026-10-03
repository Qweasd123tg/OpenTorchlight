// Shadow test: MATH functions of UtilitiesMath.cpp that do not match byte for
// byte, against the original machine code on random and boundary inputs.
// Results are compared bit for bit.
#include <cstring>

#include <OgreCamera.h>

#include "HybridTest.h"
#include "UtilitiesMath.h"

TL_ORIGINAL(void, originalWorldToLocal, (Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Matrix4&),
            "_ZN4MATH12worldToLocalERN4Ogre7Vector3ERKS1_RKNS0_7Matrix4E")
TL_ORIGINAL(void, originalWorldToLocalPerspective, (Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Matrix4&),
            "_ZN4MATH23worldToLocalPerspectiveERN4Ogre7Vector3ERKS1_RKNS0_7Matrix4E")
TL_ORIGINAL(unsigned char, originalClassifyPoint, (const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Vector3&),
            "_ZN4MATH13classifyPointERKN4Ogre7Vector3ES3_S3_")
TL_ORIGINAL(unsigned char, originalClassifyPointForSphere,
            (const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Vector3&, float),
            "_ZN4MATH22classifyPointForSphereERKN4Ogre7Vector3ES3_S3_f")
TL_ORIGINAL(void, originalClosestPointOnTriangle,
            (const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Vector3&, Ogre::Vector3&),
            "_ZN4MATH22closestPointOnTriangleERKN4Ogre7Vector3ES3_S3_S3_RS1_")
TL_ORIGINAL(void, originalMatrixRotationX, (Ogre::Matrix4&, float), "_ZN4MATH15matrixRotationXERN4Ogre7Matrix4Ef")
TL_ORIGINAL(void, originalMatrixRotationY, (Ogre::Matrix4&, float), "_ZN4MATH15matrixRotationYERN4Ogre7Matrix4Ef")
TL_ORIGINAL(void, originalRotateX, (Ogre::Vector3*, float), "_ZN4MATH7rotateXEPN4Ogre7Vector3Ef")
TL_ORIGINAL(void, originalRotateY, (Ogre::Vector3*, float), "_ZN4MATH7rotateYEPN4Ogre7Vector3Ef")
TL_ORIGINAL(void, originalRotateZ, (Ogre::Vector3*, float), "_ZN4MATH7rotateZEPN4Ogre7Vector3Ef")
TL_ORIGINAL(Ogre::Vector3, originalScreenToWorldRay, (Ogre::Camera*, float, float, float, float),
            "_ZN4MATH16screenToWorldRayEPN4Ogre6CameraEffff")

namespace
{

unsigned int g_seed = 9001;

unsigned int nextRandom()
{
    g_seed = g_seed * 1103515245u + 12345u;
    return g_seed >> 8;
}

float randomFloat(float low, float high)
{
    return low + (high - low) * float(nextRandom() % 100001) / 100000.0f;
}

Ogre::Vector3 randomVector(float range)
{
    return Ogre::Vector3(randomFloat(-range, range), randomFloat(-range, range), randomFloat(-range, range));
}

Ogre::Matrix4 randomMatrix()
{
    Ogre::Matrix4 m;
    for (int row = 0; row < 4; row++)
        for (int column = 0; column < 4; column++)
            m[row][column] = randomFloat(-2.0f, 2.0f);
    return m;
}

bool same(const void* a, const void* b, size_t size)
{
    return std::memcmp(a, b, size) == 0;
}

// Fake camera: a copy of nothing but the four virtual slots the function uses
// and the orientation read by the non-virtual Camera::getOrientation.
const int kNearSlot = 0x260 / 8;
const int kFarSlot = 0x270 / 8;
const int kProjectionSlot = 0x2d8 / 8;
const int kViewSlot = 0x2e0 / 8;

void* g_cameraVtable[kViewSlot + 1];
float g_near;
float g_far;
Ogre::Matrix4 g_projection;
Ogre::Matrix4 g_view;
char g_camera[sizeof(Ogre::Camera)] __attribute__((aligned(16)));

float fakeNear(const void*) { return g_near; }
float fakeFar(const void*) { return g_far; }
const Ogre::Matrix4& fakeProjection(const void*) { return g_projection; }
const Ogre::Matrix4& fakeView(const void*) { return g_view; }

Ogre::Camera* fakeCamera()
{
    g_cameraVtable[kNearSlot] = reinterpret_cast<void*>(&fakeNear);
    g_cameraVtable[kFarSlot] = reinterpret_cast<void*>(&fakeFar);
    g_cameraVtable[kProjectionSlot] = reinterpret_cast<void*>(&fakeProjection);
    g_cameraVtable[kViewSlot] = reinterpret_cast<void*>(&fakeView);
    void** vptr = g_cameraVtable;
    std::memcpy(g_camera, &vptr, sizeof(vptr));
    return reinterpret_cast<Ogre::Camera*>(g_camera);
}

} // namespace

TL_TEST(UtilitiesMath_shadow)
{
    int failures = 0;
    const float epsilon = 0.00001f;

    for (int round = 0; round < 2000 && failures == 0; round++)
    {
        Ogre::Matrix4 m = randomMatrix();
        Ogre::Vector3 p = randomVector(50.0f);
        Ogre::Vector3 a, b;
        originalWorldToLocal(a, p, m);
        MATH::worldToLocal(b, p, m);
        TL_CHECK(failures, same(&a, &b, sizeof(a)));
        // Depth sign decides whether it is flipped before the divide.
        originalWorldToLocalPerspective(a, p, m);
        MATH::worldToLocalPerspective(b, p, m);
        TL_CHECK(failures, same(&a, &b, sizeof(a)));

        Ogre::Vector3 point = randomVector(2.0f);
        Ogre::Vector3 planePoint = randomVector(2.0f);
        Ogre::Vector3 normal = randomVector(1.0f);
        if (round % 4 == 0)
        {
            // Distances exactly on and around +-epsilon.
            point = Ogre::Vector3::ZERO;
            normal = Ogre::Vector3::UNIT_X;
            float offsets[] = {epsilon, -epsilon, 0.0f, epsilon * 2.0f, -epsilon * 2.0f};
            planePoint = Ogre::Vector3(offsets[nextRandom() % 5], 0.0f, 0.0f);
        }
        TL_CHECK(failures, originalClassifyPoint(point, planePoint, normal) ==
                               MATH::classifyPoint(point, planePoint, normal));
        float radius = (round % 4 == 1) ? 0.0f : randomFloat(-1.0f, 1.0f);
        TL_CHECK(failures, originalClassifyPointForSphere(point, planePoint, normal, radius) ==
                               MATH::classifyPointForSphere(point, planePoint, normal, radius));

        Ogre::Vector3 t0 = randomVector(10.0f);
        Ogre::Vector3 t1 = randomVector(10.0f);
        Ogre::Vector3 t2 = randomVector(10.0f);
        Ogre::Vector3 target = randomVector(12.0f);
        if (round % 5 == 0)
            t2 = t0;
        originalClosestPointOnTriangle(t0, t1, t2, target, a);
        MATH::closestPointOnTriangle(t0, t1, t2, target, b);
        TL_CHECK(failures, same(&a, &b, sizeof(a)));

        float angle = randomFloat(-7.0f, 7.0f);
        Ogre::Matrix4 ma = randomMatrix();
        Ogre::Matrix4 mb = ma;
        originalMatrixRotationX(ma, angle);
        MATH::matrixRotationX(mb, angle);
        TL_CHECK(failures, same(&ma, &mb, sizeof(ma)));
        originalMatrixRotationY(ma, angle);
        MATH::matrixRotationY(mb, angle);
        TL_CHECK(failures, same(&ma, &mb, sizeof(ma)));

        a = p;
        b = p;
        originalRotateX(&a, angle);
        MATH::rotateX(&b, angle);
        TL_CHECK(failures, same(&a, &b, sizeof(a)));
        originalRotateY(&a, angle);
        MATH::rotateY(&b, angle);
        TL_CHECK(failures, same(&a, &b, sizeof(a)));
        originalRotateZ(&a, angle);
        MATH::rotateZ(&b, angle);
        TL_CHECK(failures, same(&a, &b, sizeof(a)));

        Ogre::Camera* camera = fakeCamera();
        g_near = randomFloat(0.1f, 5.0f);
        g_far = randomFloat(10.0f, 500.0f);
        g_projection = randomMatrix();
        g_view = randomMatrix();
        Ogre::Quaternion orientation(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f),
                                     randomFloat(-1.0f, 1.0f));
        const Ogre::Quaternion& slot = camera->getOrientation();
        std::memcpy(const_cast<Ogre::Quaternion*>(&slot), &orientation, sizeof(orientation));
        float width = randomFloat(320.0f, 2560.0f);
        float height = randomFloat(200.0f, 1600.0f);
        float x = randomFloat(0.0f, width);
        float y = randomFloat(0.0f, height);
        if (round % 7 == 0)
            g_far = g_near; // zero-length ray: normalise skips the scale
        a = originalScreenToWorldRay(camera, x, y, width, height);
        b = MATH::screenToWorldRay(camera, x, y, width, height);
        TL_CHECK(failures, same(&a, &b, sizeof(a)));
        if (failures)
            host->log("    round %d\n", round);
    }
    return failures;
}
