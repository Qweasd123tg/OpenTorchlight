#ifndef SHAPE_H
#define SHAPE_H
#include "PositionableObject.h"
#include "ParticleDynamicAttribute.h"
#include <utility>
// Partial: full 0x168-byte primary base used by UnitSpawner's RTTI.
class CShape : public CPositionableObject
{
public:
    CShape(CResourceManager* resources);
    float getAngleOffsetAtPercent(float percent);
    Ogre::Vector3 calculatePositionFromPercent(float percent,float radius);
    Ogre::Vector3 calculatePositionOnSphere(float percent,float radius);
    Ogre::Vector3 calculatePositionOnBox(float percent,float radius);
    Ogre::Vector3 calculatePositionOnLineBetweenAngles(float percent,float radius);
    Ogre::Vector3 calculatePositionBetweenAnglesAndRadius(float percent,float radius);
    void calculateLineSequment(float percent,Ogre::Vector3& start,Ogre::Vector3& end);
    void calculateOrientation(const Ogre::Vector3& position,Ogre::Vector3& forward,Ogre::Vector3& up,Ogre::Vector3& right);
    void updatePositionAndOrientation(Ogre::Vector3& position,Ogre::Quaternion& orientation,float percent,float radius);
    std::pair<bool,float> lineIntersectsPosition(float percent,const Ogre::Vector3& position,float radius);

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
    unsigned int m_radiusMode; // +0x100
    int m_shapeKind; // +0x104
    int m_orientationMode; // +0x108
    unsigned char m_Padding10C[0x4];
    ParticleUniverse::DynamicAttribute* m_releaseAngle; // +0x110
    ParticleUniverse::DynamicAttribute* m_angleOffset; // +0x118
    ParticleUniverse::DynamicAttribute* m_maxRadius; // +0x120
    ParticleUniverse::DynamicAttribute* m_minRadius; // +0x128
    bool m_radiusOnEdge; // +0x130
    unsigned char m_Padding131[0x3];
    float m_radiusExtraScale; // +0x134
    Ogre::Vector3 m_boxSize; // +0x138
    unsigned char m_Padding144[0x4];
    ParticleUniverse::DynamicAttribute* m_directionX; // +0x148
    ParticleUniverse::DynamicAttribute* m_directionY; // +0x150
    ParticleUniverse::DynamicAttribute* m_orientationX; // +0x158
    ParticleUniverse::DynamicAttribute* m_orientationY; // +0x160
};
#endif
