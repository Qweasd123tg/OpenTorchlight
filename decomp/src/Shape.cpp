
#include <utility>
#include "OgreMath.h"
#include "ParticlePropertyConversions.h"
#include "Shape.h"
#include "UtilitiesMath.h"

float CShape::getMaxRadiusAtPercent(float percent)
{
    if (m_maxRadius) return m_maxRadius->getValue(NULL, percent) * (1.0f + m_radiusExtraScale);
    return 1.0f;
}

float CShape::getMinRadiusAtPercent(float percent)
{
    if (m_minRadius) {
        if (m_radiusOnEdge) return getMaxRadiusAtPercent(percent);
        return m_minRadius->getValue(NULL, percent);
    }
    return 1.0f;
}

float CShape::getAngleOfReleaseAtPercent(float percent)
{
    if (m_releaseAngle) return m_releaseAngle->getValue(NULL, percent);
    return 360.0f;
}

void CShape::setShape(unsigned int kind)
{
    m_shapeKind = kind;
}

void CShape::setAngleOffset(const float* values, unsigned int count)
{
    if (m_angleOffset) { delete m_angleOffset; m_angleOffset = NULL; }
    m_angleOffset = getDynPropFromArray(values, count);
}

float* CShape::getAngleOffset(unsigned int& count)
{
    return getArrayFromDynProp(m_angleOffset, count);
}

void CShape::setAngleOfRelease(const float* values, unsigned int count)
{
    if (m_releaseAngle) { delete m_releaseAngle; m_releaseAngle = NULL; }
    m_releaseAngle = getDynPropFromArray(values, count);
}

float* CShape::getAngleOfRelease(unsigned int& count)
{
    return getArrayFromDynProp(m_releaseAngle, count);
}

void CShape::setMinRadius(const float* values, unsigned int count)
{
    if (m_minRadius) { delete m_minRadius; m_minRadius = NULL; }
    m_minRadius = getDynPropFromArray(values, count);
}

float* CShape::getMinRadius(unsigned int& count)
{
    return getArrayFromDynProp(m_minRadius, count);
}

void CShape::setMaxRadius(const float* values, unsigned int count)
{
    if (m_maxRadius) { delete m_maxRadius; m_maxRadius = NULL; }
    m_maxRadius = getDynPropFromArray(values, count);
}

float* CShape::getMaxRadius(unsigned int& count)
{
    return getArrayFromDynProp(m_maxRadius, count);
}

float CShape::getRadiusAtPercent(float percent)
{
    float minimum = getMinRadiusAtPercent(percent);
    float maximum = getMaxRadiusAtPercent(percent);
    if (m_radiusMode == 2) return Ogre::Math::RangeRandom(minimum, maximum);
    return minimum + (maximum - minimum) * percent;
}

CShape::~CShape()
{
    if (m_directionX) {
        delete m_directionX;
        m_directionX = NULL;
    }
    if (m_directionY) {
        delete m_directionY;
        m_directionY = NULL;
    }
    if (m_maxRadius) {
        delete m_maxRadius;
        m_maxRadius = NULL;
    }
    if (m_minRadius) {
        delete m_minRadius;
        m_minRadius = NULL;
    }
    if (m_angleOffset) {
        delete m_angleOffset;
        m_angleOffset = NULL;
    }
    if (m_releaseAngle) {
        delete m_releaseAngle;
        m_releaseAngle = NULL;
    }
    if (m_orientationX) {
        delete m_orientationX;
        m_orientationX = NULL;
    }
    if (m_orientationY) {
        delete m_orientationY;
        m_orientationY = NULL;
    }
}

CShape::CShape(CResourceManager* resources)
    : CPositionableObject(resources, NULL), m_radiusMode(0), m_shapeKind(0), m_orientationMode(0),
      m_releaseAngle(NULL), m_angleOffset(NULL), m_maxRadius(NULL), m_minRadius(NULL),
      m_radiusOnEdge(false), m_radiusExtraScale(0.0f), m_boxSize(10.0f,1.0f,10.0f),
      m_directionX(NULL), m_directionY(NULL), m_orientationX(NULL), m_orientationY(NULL)
{
    float release[] = {0.0f,360.0f};
    float zero[] = {0.0f,0.0f};
    float radius[] = {0.0f,2.0f};
    setAngleOffset(zero,2);
    setAngleOfRelease(release,2);
    setMaxRadius(radius,2);
    setMinRadius(zero,2);
    setVisible(true);
}

Ogre::Vector3 CShape::calculatePositionFromPercent(float percent,float radius)
{
    switch (m_shapeKind) {
    case 0: return calculatePositionBetweenAnglesAndRadius(percent,radius);
    case 1: return calculatePositionOnLineBetweenAngles(percent,radius);
    case 2: return calculatePositionOnSphere(percent,radius);
    case 4: return calculatePositionOnBox(percent,radius);
    default: return getPosition(true);
    }
}

void CShape::updatePositionAndOrientation(Ogre::Vector3& position,Ogre::Quaternion& orientation,float percent,float radius)
{
    position = calculatePositionFromPercent(percent,radius);
    Ogre::Vector3 forward,up,right;
    calculateOrientation(position,forward,up,right);
    orientation = Ogre::Quaternion(right,up,forward);
}

#include <cmath>
float CShape::getAngleOffsetAtPercent(float percent)
{
    if (!m_angleOffset) return 0.0f;
    if (m_shapeKind == 0) {
        float offset = m_angleOffset->getValue(NULL, percent);
        return getAngleOfReleaseAtPercent(percent) * -0.5f + offset;
    }
    return m_angleOffset->getValue(NULL, percent);
}

Ogre::Vector3 CShape::calculatePositionOnSphere(float percent, float)
{
    float radius = getRadiusAtPercent(percent);
    float x = 0, y = 0, z = 0;
    if (static_cast<int>(m_radiusMode) >= 0 && m_radiusMode <= 1) {
        x = Ogre::Math::RangeRandom(-1,1) * radius;
        y = Ogre::Math::RangeRandom(-1,1) * radius;
        z = Ogre::Math::RangeRandom(-1,1) * radius;
    } else if (m_radiusMode == 2) {
        radius = Ogre::Math::RangeRandom(0, radius);
        x = radius * Ogre::Math::RangeRandom(-1,1);
        y = radius * Ogre::Math::RangeRandom(-1,1);
        z = radius * Ogre::Math::RangeRandom(-1,1);
    }
    Ogre::Vector3 position = getPosition(true);
    return Ogre::Vector3(x + position.x, y + position.y, position.z + z);
}

Ogre::Vector3 CShape::calculatePositionOnLineBetweenAngles(float percent, float radius)
{
    Ogre::Vector3 start(0,0,0), end(0,0,0);
    calculateLineSequment(percent, start, end);
    Ogre::Vector3 delta = end - start;
    if (m_radiusMode == 0) delta *= radius;
    else if (m_radiusMode == 1) delta *= 1.0f - radius;
    else if (m_radiusMode == 2) delta *= Ogre::Math::RangeRandom(0,1);
    return delta + start;
}

Ogre::Vector3 CShape::calculatePositionBetweenAnglesAndRadius(float percent, float amount)
{
    float radius = getRadiusAtPercent(percent);
    float release = getAngleOfReleaseAtPercent(percent);
    float part = amount * release;
    float offset = getAngleOffsetAtPercent(percent);
    float angle = release;
    if (m_radiusMode == 0) angle = part + offset;
    else if (m_radiusMode == 1) angle = (release - part) + offset;
    else if (m_radiusMode == 2) {
        float end = release + offset;
        float low = end < offset ? end : offset;
        float high = end > offset ? end : offset;
        angle = Ogre::Math::RangeRandom(low, high);
    }
    angle = Ogre::Math::AngleUnitsToRadians(90.0f + angle);
    Ogre::Vector3 local(::cosf(angle) * radius, 0.0f, ::sinf(angle) * radius);
    local = getSceneNode()->_getDerivedOrientation() * local;
    return getPosition(true) + local;
}

std::pair<bool,float> CShape::lineIntersectsPosition(float percent, const Ogre::Vector3& position, float radius)
{
    Ogre::Vector3 start(0,0,0), end(0,0,0), closest(0,0,0);
    calculateLineSequment(percent, start, end);
    MATH::closestPointOnLine(start, end, position, closest);
    float x = closest.x - position.x;
    float z = closest.z - position.z;
    float distance = ::sqrtf((x * x + 0.0f) + z * z);
    return std::pair<bool,float>(radius >= distance, distance);
}

std::pair<bool,float> CShape::positionWithRadiusIntersectsBox(float, const Ogre::Vector3& position, float radius)
{
    Ogre::Matrix4 inverse = getTransformation().inverse();
    float reciprocal = 1.0f / (((inverse[3][0] * position.x + inverse[3][1] * position.y) + inverse[3][2] * position.z) + inverse[3][3]);
    float x = (((inverse[0][0] * position.x + inverse[0][1] * position.y) + inverse[0][2] * position.z) + inverse[0][3]) * reciprocal;
    float z = (((inverse[2][0] * position.x + inverse[2][1] * position.y) + inverse[2][2] * position.z) + inverse[2][3]) * reciprocal;
    float halfX = 0.5f * m_boxSize.x;
    float halfZ = 0.5f * m_boxSize.z;
    float distance = (getPosition(true) - position).length();
    float minX = x - radius, minZ = z - radius;
    float maxX = radius + x, maxZ = radius + z;
    bool intersects = (!(minX > halfX) && !(minZ > halfZ) && !(-halfX > maxX) && !(-halfZ > maxZ));
    if (!intersects) intersects = minX >= -halfX && minZ >= -halfZ && halfX >= maxX && halfZ >= maxZ;
    return std::pair<bool,float>(intersects, distance);
}

std::pair<bool,float> CShape::getPositionIsInShapeAtPercent(float percent, const Ogre::Vector3& position, float radius)
{
    switch (m_shapeKind) {
    case 0: return positionIntersectsAngle(percent, position, radius);
    case 1: return lineIntersectsPosition(percent, position, radius);
    case 2: {
        float distance = (getPosition(true) - position).length();
        float maximum = getMaxRadiusAtPercent(percent);
        return std::pair<bool,float>(maximum + radius >= distance, distance);
    }
    case 3: {
        float distance = (getPosition(true) - position).length();
        return std::pair<bool,float>(radius >= distance, distance);
    }
    default: return positionWithRadiusIntersectsBox(percent, position, radius);
    }
}

#include "Utilities.h"

void CShape::calculateLineSequment(float percent, Ogre::Vector3& start, Ogre::Vector3& end)
{
    float minimum = getMinRadiusAtPercent(percent);
    float maximum = getMaxRadiusAtPercent(percent);
    if (minimum == maximum) minimum = 0.0f;
    float release = Ogre::Math::AngleUnitsToRadians(getAngleOfReleaseAtPercent(percent));
    float offset = Ogre::Math::AngleUnitsToRadians(getAngleOffsetAtPercent(percent));
    float angle = offset + release;
    start = Ogre::Vector3(cosf(angle), 0.0f, sinf(angle));
    end = start;
    start *= minimum;
    end *= maximum;
    start = m_pSceneNode->_getDerivedOrientation() * start;
    end = m_pSceneNode->_getDerivedOrientation() * end;
    start += getPosition(true);
    end += getPosition(true);
}

Ogre::Vector3 CShape::calculatePositionOnBox(float, float percent)
{
    Ogre::Vector3 point(0.0f, 0.0f, 0.0f);
    if (m_radiusMode == 0 || m_radiusMode == 1)
    {
        bool reverse = m_radiusMode == 1;
        float angle = static_cast<float>(static_cast<double>(percent) * 6.283185306);
        point.x = (cosf(angle) * m_boxSize.x) * (reverse ? -0.5f : 0.5f);
        point.z = (sinf(angle) * m_boxSize.z) * 0.5f;
    }
    else if (m_radiusMode == 2)
    {
        point.x = 0.5f * UTILITIES::randomBetweenVolatile(-m_boxSize.x, m_boxSize.x);
        point.y = 0.5f * UTILITIES::randomBetweenVolatile(-m_boxSize.y, m_boxSize.y);
        point.z = UTILITIES::randomBetweenVolatile(-m_boxSize.z, m_boxSize.z) * 0.5f;
    }
    return getTransformation() * point;
}

void CShape::calculateOrientation(const Ogre::Vector3& position, Ogre::Vector3& forward,
                                  Ogre::Vector3& up, Ogre::Vector3& right)
{
    switch (m_orientationMode) {
    case 0:
        forward = getForwardAbsolute();
        up = getUpAbsolute();
        right = getRightAbsolute();
        break;
    case 3:
        forward = position - getPosition(true);
        forward.y = 0.0f;
        forward.normalise();
        up = Ogre::Vector3(0.0f, 1.0f, 0.0f);
        right = up.crossProduct(forward);
        break;
    case 4:
        forward = getPosition(true) - position;
        forward.y = 0.0f;
        forward.normalise();
        up = Ogre::Vector3(0.0f, 1.0f, 0.0f);
        right = up.crossProduct(forward);
        break;
    case 1:
        forward = Ogre::Vector3(0.0f, -1.0f, 0.0f);
        up = Ogre::Vector3(0.0f, 0.0f, 1.0f);
        right = Ogre::Vector3(1.0f, 0.0f, 0.0f);
        break;
    case 2:
        forward = Ogre::Vector3(0.0f, 1.0f, 0.0f);
        up = Ogre::Vector3(0.0f, 0.0f, -1.0f);
        right = Ogre::Vector3(1.0f, 0.0f, 0.0f);
        break;
    default: break;
    }
}

std::pair<bool, float> CShape::positionIntersectsAngle(float percent, const Ogre::Vector3& position, float radius)
{
    Ogre::Vector3 direction(position.x, 0.0f, position.z);
    Ogre::Vector3 origin = getPosition(true);
    direction.x -= origin.x;
    direction.z -= origin.z;
    float distance = direction.normalise();
    float maximumRadius = getMaxRadiusAtPercent(percent);
    if (distance == 0.0f || distance > maximumRadius + radius)
        return std::pair<bool, float>(false, distance);
    if (getMinRadiusAtPercent(percent) - radius > distance)
        return std::pair<bool, float>(false, distance);
    float release = getAngleOfReleaseAtPercent(percent);
    if (release >= 360.0f)
        return std::pair<bool, float>(true, distance);

    const float toDegrees = 180.0f / 3.14159f;
    Ogre::Vector3 forward = getForwardAbsolute();
    float forwardAngle = static_cast<float>(::atan2(forward.x, forward.z)) * toDegrees;
    float angle = static_cast<float>(::atan2(direction.x, direction.z)) * toDegrees;
    if (forwardAngle < 0.0f) forwardAngle += 360.0f;
    if (angle < 0.0f) angle += 360.0f;
    angle -= forwardAngle;
    float offset = getAngleOffsetAtPercent(percent);
    float end = release + offset;
    const float& maximum = offset > end ? offset : end;
    const float& minimum = end > offset ? offset : end;
    if ((angle >= minimum && maximum >= angle) ||
        (angle >= minimum + 360.0f && maximum + 360.0f >= angle) ||
        (angle >= minimum - 360.0f && maximum - 360.0f >= angle))
        return std::pair<bool, float>(true, distance);

    Ogre::Vector3 side = direction.crossProduct(Ogre::Vector3::UNIT_Y) * radius;
    Ogre::Vector3 first((position.x + side.x) - origin.x, 0.0f,
                        (position.z + side.z) - origin.z);
    Ogre::Vector3 second((position.x - side.x) - origin.x, 0.0f,
                         (position.z - side.z) - origin.z);
    float firstDistance = first.normalise();
    float secondDistance = second.normalise();
    float firstAngle = static_cast<float>(::atan2(first.x, first.z)) * toDegrees;
    float secondAngle = static_cast<float>(::atan2(second.x, second.z)) * toDegrees;
    if (firstAngle < 0.0f) firstAngle += 360.0f;
    if (secondAngle < 0.0f) secondAngle += 360.0f;
    if ((firstAngle >= minimum && maximum >= firstAngle) ||
        (firstAngle >= minimum + 360.0f && maximum + 360.0f >= firstAngle) ||
        (firstAngle >= minimum - 360.0f && maximum - 360.0f >= firstAngle))
        return std::pair<bool, float>(true, firstDistance);
    if ((secondAngle >= minimum && maximum >= secondAngle) ||
        (secondAngle >= minimum + 360.0f && maximum + 360.0f >= secondAngle) ||
        (secondAngle >= minimum - 360.0f && maximum - 360.0f >= secondAngle))
        return std::pair<bool, float>(true, secondDistance);
    return std::pair<bool, float>(false, distance);
}
