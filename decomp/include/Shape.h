#ifndef SHAPE_H
#define SHAPE_H
#include "PositionableObject.h"
namespace ParticleUniverse { class DynamicAttribute; }
// Partial: full 0x168-byte primary base used by UnitSpawner's RTTI.
class CShape : public CPositionableObject
{
public:
    float getMaxRadiusAtPercent(float percent);
    float getMinRadiusAtPercent(float percent);
    float getAngleOfReleaseAtPercent(float percent);
    void setShape(unsigned int kind);
    void setAngleOffset(const float* values, unsigned int count);
    float* getAngleOffset(unsigned int& count);
    void setAngleOfRelease(const float* values, unsigned int count);
    float* getAngleOfRelease(unsigned int& count);
    void setMinRadius(const float* values, unsigned int count);
    float* getMinRadius(unsigned int& count);
    void setMaxRadius(const float* values, unsigned int count);
    float* getMaxRadius(unsigned int& count);
    float getRadiusAtPercent(float percent);
    virtual ~CShape();
    virtual void setBoxSize(const Ogre::Vector3& size);
private:
    unsigned int m_radiusMode;
    unsigned int m_shapeKind;
    unsigned char m_gap108[8];
    ParticleUniverse::DynamicAttribute* m_releaseAngle;
    ParticleUniverse::DynamicAttribute* m_angleOffset;
    ParticleUniverse::DynamicAttribute* m_maxRadius;
    ParticleUniverse::DynamicAttribute* m_minRadius;
    bool m_radiusOnEdge;
    unsigned char m_gap131[3];
    float m_radiusExtraScale;
    unsigned char m_gap138[0x168-0x138];
};
#endif
