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
