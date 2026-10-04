#include "EmptyStrings.h"
#include "ParticleEmitterWrapper.h"
#include "ParticleDynamicAttribute.h"
#include "ParticleUniverseConstants.h"
#include "ParticleWrapper.h"

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
