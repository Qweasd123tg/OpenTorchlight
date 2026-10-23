#include "EditorScene.h"
#include "EmptyStrings.h"
#include "ParticleEmitterWrapper.h"
#include "ParticleDynamicAttribute.h"
#include "ParticleUniverseConstants.h"
#include "ParticlePropertyConversions.h"
#include "ParticleWrapper.h"

#include "ParticleUniverseEmitter.h"
#include "ParticleUniverseSystemManager.h"
#include "ParticleUniverseTechnique.h"
#include "MasterResourceManager.h"

bool CParticleEmitterWrapper::getIsDoneEmitting()
{
    return m_pEmitter->getRemainingLoops() >= 0 && !m_pEmitter->isEnabled();
}

void CParticleEmitterWrapper::setParentTechniqueWrapper(CParticleTechWrapper* parent)
{
    if (m_pParticleTechWrapper)
        m_pParticleTechWrapper->removeEmitter(this);
    if (m_pEmitter->getParentTechnique())
        m_pEmitter->getParentTechnique()->removeEmitter(m_pEmitter);
    m_pParticleTechWrapper = parent;
    if (parent)
    {
        parent->addEmitter(this);
        ParticleUniverse::ParticleEmitter* emitter = m_pEmitter;
        ParticleUniverse::ParticleTechnique* technique = m_pParticleTechWrapper->m_technique;
        if (emitter->getParentTechnique() != technique)
            technique->addEmitter(emitter);
    }
}

void CParticleEmitterWrapper::destroyEmitter()
{
    if (m_pSceneNode)
        sceneNodeDetachEntity();
    if (m_pEmitter)
    {
        setParentTechniqueWrapper(NULL);
        ParticleUniverse::ParticleEmitter* emitter = m_pEmitter;
        CMasterResourceManager::getSingleton()->m_pParticleSystemManager->destroyEmitter(emitter);
    }
    m_pParticleTechWrapper = NULL;
    m_pEmitter = NULL;
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

void CParticleEmitterWrapper::setParentGuid(long long guid)
{
    if (m_pParticleTechWrapper)
        m_pParticleTechWrapper->removeEmitter(this);
    setParentTechniqueWrapper(NULL);
    CEditorBaseObject::setParentGuid(guid);
    if (getSceneOwner())
    {
        while (guid != -1)
        {
            CEditorBaseObject* parent = getSceneOwner()->GetObjectInScene(guid);
            if (!parent)
                break;
            CParticleTechWrapper* technique = dynamic_cast<CParticleTechWrapper*>(parent);
            if (technique)
            {
                setParentTechniqueWrapper(technique);
                break;
            }
            guid = parent->getParentGuid();
        }
    }
}

#include "MasterResourceManager.h"
#include "ParticleEmitterWrapperDescriptorNames.h"
#include "StringUtilities.h"

namespace
{
    // Native Runic emitter flag at +0x25b; the SDK keeps it protected.
    struct EmitterFlagAccess : ParticleUniverse::ParticleEmitter
    {
        void clearRunicFlag() { mRunicFlag25b = false; }
    };
}

CParticleEmitterWrapper::CParticleEmitterWrapper(CResourceManager* resources)
    : CPositionableObject(resources, NULL), m_pParticleTechWrapper(NULL), m_pEmitter(NULL),
      m_fRadius(1.0f), m_fMinLineIncrement(0.0f), m_fMaxLineIncrement(0.0f), m_fMaxLineDeviation(0.0f),
      m_iEmitterType(0), m_fBoxWidth(1.0f), m_fBoxHeight(1.0f), m_fBoxDepth(1.0f),
      m_bEnabled(true), m_bCircleFixedSize(true), m_PositionEnd(0.0f, 0.0f, 0.0f),
      m_pUnknown148(NULL), m_pUnknown150(NULL), m_pUnknown158(NULL), m_pUnknown160(NULL)
{
    m_pEmitter = CMasterResourceManager::getSingleton()->m_pParticleSystemManager->createEmitter("Point");
    float emissionRate[2] = { 0.0f, 15.0f };
    float angle[2] = { 0.0f, 45.0f };
    float velocity[2] = { 0.0f, 15.0f };
    float timeToLive[3] = { 1.0f, 5.0f, 10.0f };
    float dimensions[3] = { 0.0f, 1.0f, 1.0f };
    float duration[2] = { 0.0f, 1.0f };
    m_pEmitter->setNumberOfLoops(-1);
    Ogre::Vector3 direction(0.0f, 1.0f, 0.0f);
    m_pEmitter->setParticleDirection(direction);
    m_pEmitter->setDynEmissionRate(getDynPropFromArray(emissionRate, 2));
    m_pEmitter->setDynParticleWidth(getDynPropFromArray(dimensions, 3));
    m_pEmitter->setDynParticleHeight(getDynPropFromArray(dimensions, 3));
    m_pEmitter->setDynParticleDepth(getDynPropFromArray(dimensions, 3));
    m_pEmitter->setDynAngle(getDynPropFromArray(angle, 2));
    m_pEmitter->setDynVelocity(getDynPropFromArray(velocity, 2));
    m_pEmitter->setDynTotalTimeToLive(getDynPropFromArray(timeToLive, 3));
    m_pEmitter->setDynDuration(getDynPropFromArray(duration, 2));
    float radius[2] = { 0.0f, 3.0f };
    float degrees[2] = { 0.0f, 0.0f };
    float step[2] = { 0.0f, 0.1f };
    setMinRadius(radius, 2);
    setMaxRadius(radius, 2);
    setCircleDegrees(degrees, 2);
    setCircleStep(step, 2);
    m_bEnabled = true;
    static_cast<EmitterFlagAccess*>(m_pEmitter)->clearRunicFlag();
    CSceneNodeObject::setVisible(true);
    m_pEmitter->setEmitsType(ParticleUniverse::Particle::PT_VISUAL);
}

void CParticleEmitterWrapper::setEmitterType(int type)
{
    if (m_iEmitterType == type)
        return;
    m_iEmitterType = type;
    ParticleUniverse::ParticleEmitter* emitter = CMasterResourceManager::getSingleton()->m_pParticleSystemManager->createEmitter(
        STRINGS::StringConvertToNarrow(gEMITTER_TYPES[type].c_str()));
    CParticleTechWrapper* technique = m_pParticleTechWrapper;
    setParentTechniqueWrapper(NULL);
    if (m_pEmitter) {
        std::string emitterType = emitter->getEmitterType();
        m_pEmitter->copyAttributesTo(emitter);
        emitter->setEmitterType(emitterType);
        destroyEmitter();
    }
    m_pEmitter = emitter;
    setParentTechniqueWrapper(technique);
    setRadius(m_fRadius);
    positionUpdated(getPosition(false));
    setMinLineIncrement(m_fMinLineIncrement);
    setMaxLineIncrement(m_fMaxLineIncrement);
    setMaxLineDeviation(m_fMaxLineDeviation);
    setPositionEnd(m_PositionEnd);
    setBoxDepth(m_fBoxDepth);
    setBoxHeight(m_fBoxHeight);
    setBoxWidth(m_fBoxWidth);
    unsigned int count = 0;
    setCircleFixedSize(m_bCircleFixedSize);
    setMinRadius(getArrayFromDynProp(static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown148), count), count);
    setMaxRadius(getArrayFromDynProp(static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown150), count), count);
    setCircleDegrees(getArrayFromDynProp(static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown158), count), count);
    setCircleStep(getArrayFromDynProp(static_cast<ParticleUniverse::DynamicAttribute*>(m_pUnknown160), count), count);
}
