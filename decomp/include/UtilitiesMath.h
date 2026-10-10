#ifndef UTILITIESMATH_H
#define UTILITIESMATH_H

#include <string>
#include <vector>

#include <OgreMatrix4.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>

namespace Ogre
{
    class Camera;
    class Mesh;
    class SubMesh;
    struct VertexBoneAssignment_s;
}

// Results of classifyPoint and classifyPointForSphere (returned in EAX).
// Enumerator names are ours: the distance along the plane normal from the
// point to the plane is below -epsilon, above +epsilon, or within it.
enum EPLANE_SIDE
{
    PLANE_SIDE_FRONT,
    PLANE_SIDE_BACK,
    PLANE_SIDE_ON
};

// Scratch values of the last line/sphere-plane intersection.
extern float Percentage;
extern float LineLength;
extern float DistanceFromPlane;
extern float DeltaX;
extern float DeltaY;
extern float DeltaZ;
extern float ToPlaneX;
extern float ToPlaneY;
extern float ToPlaneZ;

namespace MATH
{
    unsigned long vectorToRGB(const Ogre::Vector3& vector);

    bool boundsContains(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& innerMinimum,
                        const Ogre::Vector3& innerMaximum);
    bool boundsIntersect(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& otherMinimum,
                         const Ogre::Vector3& otherMaximum);
    bool boundsContainsXY(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum,
                          const Ogre::Vector3& innerMinimum, const Ogre::Vector3& innerMaximum);
    bool boundsIntersectXY(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum,
                           const Ogre::Vector3& otherMinimum, const Ogre::Vector3& otherMaximum);
    bool boundsContains(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& center,
                        float radius);
    bool boundsIntersect(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& center,
                         float radius);
    void expandBounds(Ogre::Vector3& minimum, Ogre::Vector3& maximum, Ogre::Vector3 point);
    void expandCubicBounds(Ogre::Vector3& minimum, Ogre::Vector3& maximum, Ogre::Vector3 extent);
    void expandHorizontalCubicBounds(Ogre::Vector3& minimum, Ogre::Vector3& maximum, Ogre::Vector3 extent);

    void worldToLocalPerspective(Ogre::Vector3& result, const Ogre::Vector3& point, const Ogre::Matrix4& matrix);
    void worldToLocal(Ogre::Vector3& result, const Ogre::Vector3& point, const Ogre::Matrix4& matrix);

    void closestPointOnLine(const Ogre::Vector3& start, const Ogre::Vector3& end, const Ogre::Vector3& point,
                            Ogre::Vector3& result);
    void closestPointOnTriangle(const Ogre::Vector3& a, const Ogre::Vector3& b, const Ogre::Vector3& c,
                                const Ogre::Vector3& point, Ogre::Vector3& result);
    EPLANE_SIDE classifyPoint(const Ogre::Vector3& point, const Ogre::Vector3& planePoint,
                                const Ogre::Vector3& planeNormal);
    EPLANE_SIDE classifyPointForSphere(const Ogre::Vector3& center, const Ogre::Vector3& planePoint,
                                         const Ogre::Vector3& planeNormal, float radius);
    bool getLinePlaneIntersection(const Ogre::Vector3& start, const Ogre::Vector3& end,
                                  const Ogre::Vector3& planePoint, const Ogre::Vector3& planeNormal,
                                  Ogre::Vector3& result);
    bool getSpherePlaneIntersection(const Ogre::Vector3& start, const Ogre::Vector3& end,
                                    const Ogre::Vector3& planePoint, const Ogre::Vector3& planeNormal,
                                    Ogre::Vector3& result);
    float distanceToPlane(const Ogre::Vector3& origin, const Ogre::Vector3& direction,
                          const Ogre::Vector3& planeNormal, float planeDistance);

    void matrixRotationZ(Ogre::Matrix4& matrix, float angle);
    void matrixRotationX(Ogre::Matrix4& matrix, float angle);
    void matrixRotationY(Ogre::Matrix4& matrix, float angle);
    void rotateZ(Ogre::Vector3* vector, float angle);
    void rotateX(Ogre::Vector3* vector, float angle);
    void rotateY(Ogre::Vector3* vector, float angle);
    float angleBetween(Ogre::Vector3 a, Ogre::Vector3 b);

    Ogre::Vector3 screenToWorldRay(Ogre::Camera* camera, float x, float y, float width, float height);
}

#endif
