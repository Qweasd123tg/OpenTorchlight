#include "ParticleDynamicAttribute.h"
ParticleUniverse::DynamicAttribute* getDynPropFromArray(const float*, unsigned int);
float* getArrayFromDynProp(ParticleUniverse::DynamicAttribute*, unsigned int&);
#include <OgreMath.h>
#include "Shape.h"


// Imported source candidates; historical status is not fresh acceptance.
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
