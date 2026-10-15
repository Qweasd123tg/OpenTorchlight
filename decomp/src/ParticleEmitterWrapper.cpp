#include "EmptyStrings.h"
#include "ParticleEmitterWrapper.h"
#include "ParticleDynamicAttribute.h"
#include "ParticleUniverseConstants.h"
#include "ParticlePropertyConversions.h"
#include "ParticleWrapper.h"

namespace ParticleUniverse {
class ParticleRenderer { public: void setSorted(bool); };
class ParticleTechnique {
public:
    void setFlipbookWidthHeight(int, int);
    void setKeepLocal(bool);
    ParticleRenderer* getRenderer() const;
};
class RibbonTrailRenderer {
public:
    void setTrailLocal(bool);
    void setMaxChainElements(unsigned long);
    void setTrailLength(float);
    void setTrailWidth(float);
};
class ParticleEmitter { public: void setKeepLocal(bool); };
}

void CParticleEmitterWrapper::starting()
{
    setEnabled(m_bEnabled);
}

namespace ParticleUniverse
{
    class BoxEmitter
    {
    public:
        void setDepth(float);
        void setWidth(float);
    };
}

void CParticleEmitterWrapper::setBoxDepth(float depth)
{
    m_fBoxDepth = depth;
    if (m_iEmitterType == 1)
    {
        ParticleUniverse::BoxEmitter *emitter =
            *reinterpret_cast<ParticleUniverse::BoxEmitter **>(&m_ParticleDirection);
        if (emitter != NULL)
            emitter->setDepth(depth);
    }
}

extern "C" void particleUniverseBoxEmitterSetHeight(
    ParticleUniverse::BoxEmitter *, float)
    __asm__("_ZN16ParticleUniverse10BoxEmitter9setHeightEf");

void CParticleEmitterWrapper::setBoxHeight(float height)
{
    m_fBoxHeight = height;
    if (m_iEmitterType == 1 &&
        *reinterpret_cast<ParticleUniverse::BoxEmitter **>(m_ParticleDirection) != NULL) {
        particleUniverseBoxEmitterSetHeight(
            *reinterpret_cast<ParticleUniverse::BoxEmitter **>(m_ParticleDirection),
            height);
    }
}

namespace ParticleUniverse
{
    class LineEmitter
    {
    public:
        void setMinIncrement(float);
        void setMaxIncrement(float);
        void setMaxDeviation(float);
        void setEnd(const Ogre::Vector3&);
    };
}

void CParticleEmitterWrapper::setMinLineIncrement(float increment)
{
    *reinterpret_cast<float *>(m_ParticleDirection + 0x0c) = increment;

    ParticleUniverse::LineEmitter *lineEmitter =
        *reinterpret_cast<ParticleUniverse::LineEmitter **>(m_ParticleDirection);
    if (m_iEmitterType == 3 && lineEmitter != NULL)
        lineEmitter->setMinIncrement(increment);
}

namespace ParticleUniverse {
class SphereSurfaceEmitter
{
public:
    void setRadius(float);
};
}

void CParticleEmitterWrapper::setRadius(float radius)
{
    *reinterpret_cast<float *>(&m_ParticleDirection[8]) = radius;
    if (m_iEmitterType == 4)
        (*reinterpret_cast<ParticleUniverse::SphereSurfaceEmitter **>(&m_ParticleDirection[0]))->setRadius(radius);
}

CParticleEmitterWrapper::~CParticleEmitterWrapper()
{
}

namespace ParticleUniverse
{
    class CircleEmitter
    {
    public:
        void setFixedRadius(bool);
        void setStep(DynamicAttribute*);
        void setCircleAngle(DynamicAttribute*);
        void setMaxRadius(DynamicAttribute*);
        void setMinRadius(DynamicAttribute*);
    };
}

namespace
{
    // The Particle base of a ParticleEmitter stores its position at +0x10.
    struct EmitterPosition
    {
        unsigned char reserved[0x10];
        Ogre::Vector3 position;
    };
}

void CParticleEmitterWrapper::positionUpdated(const Ogre::Vector3& position)
{
    EmitterPosition* emitter = *reinterpret_cast<EmitterPosition**>(m_ParticleDirection);
    if (emitter != NULL)
        emitter->position = position;
}

void CParticleEmitterWrapper::setBoxWidth(float width)
{
    m_fBoxWidth = width;
    if (m_iEmitterType == 1)
    {
        ParticleUniverse::BoxEmitter* emitter =
            *reinterpret_cast<ParticleUniverse::BoxEmitter**>(m_ParticleDirection);
        if (emitter != NULL)
            emitter->setWidth(width);
    }
}

void CParticleEmitterWrapper::setMaxLineDeviation(float deviation)
{
    *reinterpret_cast<float*>(m_ParticleDirection + 0x14) = deviation;
    if (m_iEmitterType == 3)
    {
        ParticleUniverse::LineEmitter* emitter =
            *reinterpret_cast<ParticleUniverse::LineEmitter**>(m_ParticleDirection);
        if (emitter != NULL)
            emitter->setMaxDeviation(deviation);
    }
}

void CParticleEmitterWrapper::setMaxLineIncrement(float increment)
{
    *reinterpret_cast<float*>(m_ParticleDirection + 0x10) = increment;
    if (m_iEmitterType == 3)
    {
        ParticleUniverse::LineEmitter* emitter =
            *reinterpret_cast<ParticleUniverse::LineEmitter**>(m_ParticleDirection);
        if (emitter != NULL)
            emitter->setMaxIncrement(increment);
    }
}

void CParticleEmitterWrapper::setCircleFixedSize(bool fixed)
{
    m_bCircleFixedSize = fixed;
    if (m_iEmitterType == 2)
        (*reinterpret_cast<ParticleUniverse::CircleEmitter**>(m_ParticleDirection))->setFixedRadius(fixed);
}

void CParticleEmitterWrapper::setCircleStep(const float* values, unsigned int count)
{
    if (m_pUnknown160 != NULL)
    {
        delete static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown160);
        m_pUnknown160 = NULL;
    }
    m_pUnknown160 = getDynPropFromArray(values, count);
    if (m_iEmitterType == 2)
    {
        ParticleUniverse::CircleEmitter* emitter =
            *reinterpret_cast<ParticleUniverse::CircleEmitter**>(m_ParticleDirection);
        emitter->setStep(getDynPropFromArray(values, count));
    }
}

void CParticleEmitterWrapper::setCircleDegrees(const float* values, unsigned int count)
{
    if (m_pUnknown158 != NULL)
    {
        delete static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown158);
        m_pUnknown158 = NULL;
    }
    m_pUnknown158 = getDynPropFromArray(values, count);
    if (m_iEmitterType == 2)
    {
        ParticleUniverse::CircleEmitter* emitter =
            *reinterpret_cast<ParticleUniverse::CircleEmitter**>(m_ParticleDirection);
        emitter->setCircleAngle(getDynPropFromArray(values, count));
    }
}

void CParticleEmitterWrapper::setMaxRadius(const float* values, unsigned int count)
{
    if (m_pUnknown150 != NULL)
    {
        delete static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown150);
        m_pUnknown150 = NULL;
    }
    m_pUnknown150 = getDynPropFromArray(values, count);
    if (m_iEmitterType == 2)
    {
        ParticleUniverse::CircleEmitter* emitter =
            *reinterpret_cast<ParticleUniverse::CircleEmitter**>(m_ParticleDirection);
        emitter->setMaxRadius(getDynPropFromArray(values, count));
    }
}

void CParticleEmitterWrapper::setMinRadius(const float* values, unsigned int count)
{
    if (m_pUnknown148 != NULL)
    {
        delete static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown148);
        m_pUnknown148 = NULL;
    }
    m_pUnknown148 = getDynPropFromArray(values, count);
    if (m_iEmitterType == 2)
    {
        ParticleUniverse::CircleEmitter* emitter =
            *reinterpret_cast<ParticleUniverse::CircleEmitter**>(m_ParticleDirection);
        emitter->setMinRadius(getDynPropFromArray(values, count));
    }
}

void CParticleEmitterWrapper::setPositionEnd(const Ogre::Vector3& end)
{
    m_PositionEnd.x = end.x;
    m_PositionEnd.y = end.y;
    m_PositionEnd.z = end.z;
    if (m_iEmitterType == 3)
    {
        ParticleUniverse::LineEmitter* emitter =
            *reinterpret_cast<ParticleUniverse::LineEmitter**>(m_ParticleDirection);
        if (emitter != NULL)
            emitter->setEnd(m_PositionEnd);
    }
}

float* CParticleEmitterWrapper::getCircleStep(unsigned int& count)
{
    return getArrayFromDynProp(static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown160), count);
}

float* CParticleEmitterWrapper::getCircleDegrees(unsigned int& count)
{
    return getArrayFromDynProp(static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown158), count);
}

float* CParticleEmitterWrapper::getMaxRadius(unsigned int& count)
{
    return getArrayFromDynProp(static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown150), count);
}

float* CParticleEmitterWrapper::getMinRadius(unsigned int& count)
{
    return getArrayFromDynProp(static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown148), count);
}

void CParticleEmitterWrapper::setKeepLocal(bool local)
{
    (*reinterpret_cast<ParticleUniverse::ParticleEmitter**>(m_ParticleDirection))->setKeepLocal(local);
    if (m_pParticleTechWrapper)
        m_pParticleTechWrapper->m_technique->setKeepLocal(local);
}
