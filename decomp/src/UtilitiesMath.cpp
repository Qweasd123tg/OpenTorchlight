#include "EmptyStrings.h"

#include <cmath>

#include <OgreCamera.h>
#include <OgreMatrix4.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>

#include "Constants.h"
#include "QuestDefines.h"
#include "UtilitiesMath.h"

float Percentage;
float LineLength;
float DistanceFromPlane;
float DeltaX;
float DeltaY;
float DeltaZ;
float ToPlaneX;
float ToPlaneY;
float ToPlaneZ;

static const float kPlaneEpsilon = 0.00001f;

namespace MATH
{

unsigned long vectorToRGB(const Ogre::Vector3& vector)
{
    unsigned long red = (unsigned long)(vector.x * 127.0f + 128.0f);
    unsigned long green = (unsigned long)(vector.y * 127.0f + 128.0f);
    unsigned long blue = (unsigned long)(vector.z * 127.0f + 128.0f);
    return 0xff000000 + (red << 16) + (green << 8) + blue;
}

bool boundsContains(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& innerMinimum,
                    const Ogre::Vector3& innerMaximum)
{
    return maximum.x >= innerMaximum.x && maximum.y >= innerMaximum.y && maximum.z >= innerMaximum.z &&
           innerMinimum.x >= minimum.x && innerMinimum.y >= minimum.y && innerMinimum.z >= minimum.z;
}

bool boundsIntersect(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& otherMinimum,
                     const Ogre::Vector3& otherMaximum)
{
    return boundsIntersectXY(minimum, maximum, otherMinimum, otherMaximum) && otherMaximum.y >= minimum.y &&
           maximum.y >= otherMinimum.y;
}

bool boundsContainsXY(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& innerMinimum,
                      const Ogre::Vector3& innerMaximum)
{
    return maximum.x >= innerMaximum.x && maximum.z >= innerMaximum.z && innerMinimum.x >= minimum.x &&
           innerMinimum.z >= minimum.z;
}

bool boundsIntersectXY(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& otherMinimum,
                       const Ogre::Vector3& otherMaximum)
{
    return otherMaximum.x >= minimum.x && otherMaximum.z >= minimum.z && maximum.x >= otherMinimum.x &&
           maximum.z >= otherMinimum.z;
}

bool boundsContains(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& center,
                    float radius)
{
    return center.x >= minimum.x + radius && center.y >= minimum.y + radius && center.z >= minimum.z + radius &&
           maximum.x - radius >= center.x && maximum.y - radius >= center.y && maximum.z - radius >= center.z;
}

bool boundsIntersect(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum, const Ogre::Vector3& center,
                     float radius)
{
    return center.x >= minimum.x - radius && center.y >= minimum.y - radius && center.z >= minimum.z - radius &&
           maximum.x + radius >= center.x && maximum.y + radius >= center.y && maximum.z + radius >= center.z;
}

void expandBounds(Ogre::Vector3& minimum, Ogre::Vector3& maximum, Ogre::Vector3 point)
{
    if (point.x < minimum.x)
        minimum.x = point.x;
    if (point.x > maximum.x)
        maximum.x = point.x;
    if (point.y < minimum.y)
        minimum.y = point.y;
    if (point.y > maximum.y)
        maximum.y = point.y;
    if (point.z < minimum.z)
        minimum.z = point.z;
    if (point.z > maximum.z)
        maximum.z = point.z;
}

void expandCubicBounds(Ogre::Vector3& minimum, Ogre::Vector3& maximum, Ogre::Vector3 extent)
{
    float size = 0.0f;
    if (fabs(extent.x) > size)
        size = fabs(extent.x);
    if (fabs(extent.y) > size)
        size = fabs(extent.y);
    if (fabs(extent.z) > size)
        size = fabs(extent.z);
    expandBounds(minimum, maximum, Ogre::Vector3(size, size, size));
    expandBounds(minimum, maximum, Ogre::Vector3(-size, -size, -size));
}

void expandHorizontalCubicBounds(Ogre::Vector3& minimum, Ogre::Vector3& maximum, Ogre::Vector3 extent)
{
    float size = 0.0f;
    if (fabs(extent.x) > size)
        size = fabs(extent.x);
    if (fabs(extent.z) > size)
        size = fabs(extent.z);
    expandBounds(minimum, maximum, Ogre::Vector3(size, 0.0f, size));
    expandBounds(minimum, maximum, Ogre::Vector3(-size, 0.0f, -size));
}

void worldToLocalPerspective(Ogre::Vector3& result, const Ogre::Vector3& point, const Ogre::Matrix4& matrix)
{
    Ogre::Vector3 local = point;
    result.x = local.x * matrix[0][0] + local.y * matrix[1][0] + local.z * matrix[2][0];
    result.y = local.x * matrix[0][1] + local.y * matrix[1][1] + local.z * matrix[2][1];
    result.z = local.x * matrix[0][2] + local.y * matrix[1][2] + local.z * matrix[2][2];
    float depth = result.z;
    if (depth < 0.0f)
        depth = -depth;
    result.x /= depth;
    result.y /= depth;
}

void worldToLocal(Ogre::Vector3& result, const Ogre::Vector3& point, const Ogre::Matrix4& matrix)
{
    float x=point.x,y=point.y,z=point.z;
    result.x=x*matrix[0][0]+y*matrix[1][0]+z*matrix[2][0];
    result.y=x*matrix[0][1]+y*matrix[1][1]+z*matrix[2][1];
    result.z=x*matrix[0][2]+y*matrix[1][2]+z*matrix[2][2];
}


void closestPointOnLine(const Ogre::Vector3& start, const Ogre::Vector3& end, const Ogre::Vector3& point,
                        Ogre::Vector3& result)
{
    Ogre::Vector3 direction = end - start;
    float t = (point - start).dotProduct(direction) / direction.squaredLength();
    if (t < 0.0f)
        result = start;
    else if (t > 1.0f)
        result = end;
    else
        result = start + direction * t;
}

void closestPointOnTriangle(const Ogre::Vector3& a, const Ogre::Vector3& b, const Ogre::Vector3& c,
                                            const Ogre::Vector3& point, Ogre::Vector3& result)
{
    Ogre::Vector3 closest;
    closestPointOnLine(a, b, point, closest);
    float best = (closest - point).squaredLength();
    result = closest;
    closestPointOnLine(b, c, point, closest);
    float distance = (closest - point).squaredLength();
    if (distance < best)
    {
        result = closest;
        best = distance;
    }
    closestPointOnLine(c, a, point, closest);
    distance = (closest - point).squaredLength();
    if (distance < best)
        result = closest;
}


EPLANE_SIDE classifyPoint(const Ogre::Vector3& point, const Ogre::Vector3& planePoint, const Ogre::Vector3& planeNormal)
{
    float distance = (planePoint - point).dotProduct(planeNormal);
    if (distance < -kPlaneEpsilon)
        return PLANE_SIDE_FRONT;
    if (distance > kPlaneEpsilon)
        return PLANE_SIDE_BACK;
    return PLANE_SIDE_ON;
}


EPLANE_SIDE classifyPointForSphere(const Ogre::Vector3& center, const Ogre::Vector3& planePoint,
                                                     const Ogre::Vector3& planeNormal, float radius)
{
    float distance = (planePoint.x - center.x) * planeNormal.x + (planePoint.y - center.y) * planeNormal.y + (planePoint.z - center.z) * planeNormal.z + radius;
    if (distance < -kPlaneEpsilon)
        return PLANE_SIDE_FRONT;
    if (distance > kPlaneEpsilon)
        return PLANE_SIDE_BACK;
    return PLANE_SIDE_ON;
}


bool getLinePlaneIntersection(const Ogre::Vector3& start, const Ogre::Vector3& end, const Ogre::Vector3& planePoint,
                              const Ogre::Vector3& planeNormal, Ogre::Vector3& result)
{
    DeltaX = end.x - start.x;
    DeltaY = end.y - start.y;
    DeltaZ = end.z - start.z;
    LineLength = DeltaX * planeNormal.x + DeltaY * planeNormal.y + DeltaZ * planeNormal.z;
    if (fabs(LineLength) < kPlaneEpsilon)
        return false;

    ToPlaneX = planePoint.x - start.x;
    ToPlaneY = planePoint.y - start.y;
    ToPlaneZ = planePoint.z - start.z;
    DistanceFromPlane = ToPlaneX * planeNormal.x + ToPlaneY * planeNormal.y + ToPlaneZ * planeNormal.z;
    Percentage = DistanceFromPlane / LineLength;
    if (Percentage < 0.0f || Percentage > 1.0f)
        return false;

    result.x = start.x + DeltaX * Percentage;
    result.y = start.y + DeltaY * Percentage;
    result.z = start.z + DeltaZ * Percentage;
    return true;
}

bool getSpherePlaneIntersection(const Ogre::Vector3& start, const Ogre::Vector3& end, const Ogre::Vector3& planePoint,
                                const Ogre::Vector3& planeNormal, Ogre::Vector3& result)
{
    DeltaX = end.x - start.x;
    DeltaY = end.y - start.y;
    DeltaZ = end.z - start.z;
    LineLength = DeltaX * planeNormal.x + DeltaY * planeNormal.y + DeltaZ * planeNormal.z;
    if (fabs(LineLength) < kPlaneEpsilon)
        return false;

    ToPlaneX = planePoint.x - start.x;
    ToPlaneY = planePoint.y - start.y;
    ToPlaneZ = planePoint.z - start.z;
    DistanceFromPlane = ToPlaneX * planeNormal.x + ToPlaneY * planeNormal.y + ToPlaneZ * planeNormal.z;
    Percentage = DistanceFromPlane / LineLength;

    result.x = start.x + DeltaX * Percentage;
    result.y = start.y + DeltaY * Percentage;
    result.z = start.z + DeltaZ * Percentage;
    return true;
}

float distanceToPlane(const Ogre::Vector3& origin, const Ogre::Vector3& direction, const Ogre::Vector3& planeNormal,
                      float planeDistance)
{
    float denominator = direction.dotProduct(planeNormal);
    if (denominator == 0.0f)
        return -1.0f;
    return (planeDistance - planeNormal.dotProduct(origin)) / denominator;
}

void matrixRotationZ(Ogre::Matrix4& matrix, float angle)
{
    float cosine = cosf(angle);
    float sine = sinf(angle);
    matrix = Ogre::Matrix4::IDENTITY;
    matrix[1][0] = sine;
    matrix[0][0] = cosine;
    matrix[1][1] = cosine;
    matrix[0][1] = -sine;
}

void matrixRotationX(Ogre::Matrix4& matrix, float angle)
{
    float sine = sinf(angle);
    float cosine = cosf(angle);
    matrix = Ogre::Matrix4::IDENTITY;
    matrix[1][1] = cosine;
    matrix[2][1] = sine;
    matrix[1][2] = -sine;
    matrix[2][2] = cosine;
}

void matrixRotationY(Ogre::Matrix4& matrix, float angle)
{
    float sine = sinf(angle);
    float cosine = cosf(angle);
    matrix = Ogre::Matrix4::IDENTITY;
    matrix[2][0] = -sine;
    matrix[0][0] = cosine;
    matrix[0][2] = sine;
    matrix[2][2] = cosine;
}


void rotateZ(Ogre::Vector3* vector, float angle)
{
    float cosine = cosf(angle);
    float sine = sinf(angle);
    float y = vector->y;
    float x = vector->x;
    vector->x = x * cosine + y * sine;
    vector->y = -x * sine + y * cosine;
}

void rotateX(Ogre::Vector3* vector, float angle)
{
    float cosine = cosf(angle);
    float sine = sinf(angle);
    float z = vector->z;
    float y = vector->y;
    vector->y = y * cosine + z * sine;
    vector->z = -y * sine + z * cosine;
}

void rotateY(Ogre::Vector3* vector, float angle)
{
    float cosine = cosf(angle);
    float sine = sinf(angle);
    float z = vector->z;
    float x = vector->x;
    vector->x = x * cosine + z * sine;
    vector->z = -x * sine + z * cosine;
}

float angleBetween(Ogre::Vector3 a, Ogre::Vector3 b)
{
    return acosf(a.dotProduct(b));
}

// Positions are scaled to a virtual 1024x768 screen first.
Ogre::Vector3 screenToWorldRay(Ogre::Camera* camera, float x, float y, float width, float height)
{
    float nearDistance = camera->getNearClipDistance();
    float farDistance = camera->getFarClipDistance();
    Ogre::Matrix4 projection = camera->getProjectionMatrix();

    float screenX = (2.0f * 1024.0f / width * x) / 1024.0f - 1.0f;
    float screenY = 1.0f - (2.0f * 768.0f / height * y) / 768.0f;
    screenX /= projection[0][0];
    screenY /= projection[1][1];

    Ogre::Vector3 nearPoint(screenX * nearDistance, screenY * nearDistance, -nearDistance);
    Ogre::Vector3 farPoint(screenX * farDistance, screenY * farDistance, -farDistance);

    Ogre::Matrix4 view = camera->getViewMatrix();
    view = view.inverse();
    view[0][3] = 0.0f;
    view[1][3] = 0.0f;
    view[2][3] = 0.0f;

    Ogre::Quaternion orientation = camera->getOrientation();
    nearPoint = orientation * nearPoint;
    Ogre::Vector3 direction = orientation * farPoint - nearPoint;
    direction.normalise();
    return direction;
}

}

