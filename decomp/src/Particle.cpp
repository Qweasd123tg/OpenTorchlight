#include "EmptyStrings.h"
#include "Particle.h"
#include "BaseUnit.h"
#include "CollisionList.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

void CParticle::SetParticleDirection(const Ogre::Vector3&, const Ogre::Vector3&)
{
}

bool CParticle::updateLevelObject(float delta, Ogre::Camera* camera, const Ogre::Vector3& position)
{
    m_fUnknown120 -= delta;
    if (m_fUnknown120 <= 0.0f || !m_bVisible)
    {
        if (m_bUnknown128 && m_bVisible)
            if (getNumberOfParticlesUpdating(true) != 0)
                return true;
        m_bUnknown126 = false;
        Stop(true);
        return false;
    }
    return true;
}

CParticle::~CParticle()
{
}

#include "ParticleCache.h"
#include "ParticlePreloader.h"
#include "ParticleUniverseEmitter.h"
#include "ParticleUniverseSystem.h"
#include "ParticlePropertyConversions.h"
#include "Level.h"
#include <algorithm>

namespace {
struct EmitterAccess : ParticleUniverse::ParticleEmitter {
    int remainingLoops() const { return mRemainingLoops; }
    void stopping(bool value) { mRunicFlag25b = value; }
    ParticleUniverse::DynamicAttribute* duration() { return mDynDuration; }
    ParticleUniverse::DynamicAttribute* timeToLive() { return mDynTotalTimeToLive; }
};
}

bool CParticle::looping()
{
    bool result = false;
    if (m_pParticleCache) {
        for (unsigned int i = 0; i < m_pParticleCache->mActiveParticleSystems.size(); ++i) {
            unsigned int techniques = m_pParticleCache->mActiveParticleSystems[i]->getNumTechniques();
            for (unsigned int j = 0; j < techniques; ++j) {
                ParticleUniverse::ParticleTechnique* technique = m_pParticleCache->mActiveParticleSystems[i]->getTechnique(j);
                unsigned int emitters = technique->getNumEmitters();
                for (unsigned int k = 0; k < emitters; ++k) {
                    ParticleUniverse::ParticleEmitter* emitter = technique->getEmitter(k);
                    if (emitter->isNonExpiring())
                        result = true;
                    if (reinterpret_cast<EmitterAccess*>(emitter)->remainingLoops() == -1)
                        result = true;
                }
            }
        }
    }
    return result;
}

int CParticle::getNumberOfParticlesUpdating(bool includeLooping)
{
    int result = 0;
    if (m_pParticleCache) {
        for (unsigned int i = 0; i < m_pParticleCache->mActiveParticleSystems.size(); ++i) {
            ParticleUniverse::ParticleTechnique* technique = m_pParticleCache->mActiveParticleSystems[i]->getTechnique(0);
            if (technique && technique->getNumberOfEmittedParticles()) {
                bool updating = true;
                for (unsigned int j = 0; j < technique->getNumEmitters(); ++j) {
                    ParticleUniverse::ParticleEmitter* emitter = technique->getEmitter(j);
                    if (emitter && emitter->isNonExpiring()) {
                        updating = false;
                        break;
                    }
                    if (!includeLooping && emitter && reinterpret_cast<EmitterAccess*>(emitter)->remainingLoops() == -1) {
                        updating = false;
                        break;
                    }
                }
                if (updating)
                    ++result;
            }
        }
    }
    return result;
}

ParticleUniverse::DynamicAttribute* getDynPropFromArray(const float* values, unsigned int count)
{
    unsigned int type = static_cast<unsigned int>(values[0]);
    const float* data = values + 1;
    int valueCount = count - 1;
    switch (type) {
    case 0: {
        ParticleUniverse::DynamicAttributeFixed* attribute = new ParticleUniverse::DynamicAttributeFixed;
        attribute->setValue(values[1]);
        return attribute;
    }
    case 1:
        if (valueCount > 1) {
            ParticleUniverse::DynamicAttributeRandom* attribute = new ParticleUniverse::DynamicAttributeRandom;
            attribute->setMinMax(values[1], data[1]);
            return attribute;
        }
        break;
    case 2:
    case 3:
        if (valueCount > 1 && valueCount % 2 == 0) {
            ParticleUniverse::DynamicAttributeCurved* attribute = new ParticleUniverse::DynamicAttributeCurved(
                static_cast<ParticleUniverse::InterpolationType>(type == 2 ? 0 : 1));
            for (unsigned int i = 0; i < valueCount; i += 2)
                attribute->addControlPoint(data[i], data[i + 1]);
            attribute->processControlPoints();
            return attribute;
        }
        break;
    case 4:
    case 5:
        if (valueCount > 1 && valueCount % 3 == 0) {
            ParticleUniverse::DynamicAttributeRandomCurved* attribute = new ParticleUniverse::DynamicAttributeRandomCurved(
                static_cast<ParticleUniverse::InterpolationType>(type == 4 ? 0 : 1));
            for (unsigned int i = 0; i < valueCount; i += 3)
                attribute->addControlPoint(data[i], data[i + 1], data[i + 2]);
            attribute->processControlPoints();
            return attribute;
        }
        break;
    }
    ParticleUniverse::DynamicAttributeFixed* attribute = new ParticleUniverse::DynamicAttributeFixed;
    attribute->setValue(0.0f);
    return attribute;
}

void CParticle::Stop(bool immediately)
{
    if (!immediately && (!m_bVisible || m_bUnknown125))
        return;
    if (!m_pParticleCache)
        return;
    m_bUnknown125 = true;
    if (!immediately) {
        for (unsigned int i = 0; i < m_pParticleCache->mActiveParticleSystems.size(); ++i) {
            unsigned int techniques = m_pParticleCache->mActiveParticleSystems[i]->getNumTechniques();
            for (unsigned int j = 0; j < techniques; ++j) {
                ParticleUniverse::ParticleTechnique* technique = m_pParticleCache->mActiveParticleSystems[i]->getTechnique(j);
                unsigned int emitters = technique->getNumEmitters();
                for (unsigned int k = 0; k < emitters; ++k) {
                    ParticleUniverse::ParticleEmitter* emitter = technique->getEmitter(k);
                    if (emitter && !emitter->isNonExpiring())
                        reinterpret_cast<EmitterAccess*>(emitter)->stopping(true);
                    else
                        m_pParticleCache->mActiveParticleSystems[i]->stop();
                }
            }
        }
        if (m_pResourceManager->getLevel()) {
            m_bUnknown128 = true;
            m_pResourceManager->getLevel()->addUpdateObject(this);
            m_bUnknown126 = true;
            return;
        }
        m_bUnknown128 = false;
        m_bUnknown126 = false;
    }
    else if (m_bUnknown128) {
        for (unsigned int i = 0; i < m_pParticleCache->mActiveParticleSystems.size(); ++i) {
            unsigned int techniques = m_pParticleCache->mActiveParticleSystems[i]->getNumTechniques();
            for (unsigned int j = 0; j < techniques; ++j) {
                ParticleUniverse::ParticleTechnique* technique = m_pParticleCache->mActiveParticleSystems[i]->getTechnique(j);
                if (technique) {
                    unsigned int emitters = technique->getNumEmitters();
                    for (unsigned int k = 0; k < emitters; ++k) {
                        ParticleUniverse::ParticleEmitter* emitter = technique->getEmitter(k);
                        if (emitter && !emitter->isNonExpiring())
                            reinterpret_cast<EmitterAccess*>(emitter)->stopping(false);
                    }
                }
            }
        }
        m_bUnknown128 = false;
    }
    if (m_pResourceManager->getLevel())
        m_pResourceManager->getLevel()->removeUpdateObject(this);
    setVisible(false);
    m_pSceneNode->detachAllObjects();
    m_pSceneNode->removeAllChildren();
    if (m_pParticleCache) {
        for (unsigned int i = 0; i < m_pParticleCache->mActiveParticleSystems.size(); ++i)
            m_pParticleCache->mActiveParticleSystems[i]->stop();
        m_pParticlePreloader->returnParticleCache(m_pParticleCache);
        m_pParticleCache = NULL;
    }
}

void CParticle::Start()
{
    if (m_pUnknown110.empty() || !m_pResourceManager || !m_pResourceManager->getLevel() || !m_pParticlePreloader)
        return;
    if (!m_bUnknown126 && m_bVisible)
        return;
    Stop(false);
    m_pResourceManager->getLevel()->removeUpdateObject(this);
    if (!m_pParticleCache) {
        m_pParticleCache = m_pParticlePreloader->getParticleCache(m_pUnknown110);
        if (!m_pParticleCache)
            return;
    }
    m_bUnknown125 = false;
    m_bUnknown126 = false;
    m_pSceneNode->detachAllObjects();
    m_pSceneNode->removeAllChildren();
    setVisible(true);
    m_bUnknown128 = false;
    m_bUnknown127 = false;
    m_fUnknown120 = 0.0f;
    for (unsigned int i = 0; i < m_pParticleCache->mActiveParticleSystems.size(); ++i) {
        if (m_pParticleCache->mParticleSceneNodes[i])
            m_pSceneNode->addChild(m_pParticleCache->mParticleSceneNodes[i]);
        else
            m_pSceneNode->attachObject(m_pParticleCache->mActiveParticleSystems[i]);
        m_pParticleCache->mActiveParticleSystems[i]->notifyCurrentCamera(NULL);
        m_fUnknown120 = std::max(m_pParticleCache->mActiveParticleSystems[i]->getFixedTimeout(), m_fUnknown120);
    }
    m_pSceneNode->_update(true, true);
    m_pParticleCache->playSounds(m_pSceneNode);
    m_pParticleCache->playCameraShakes(getPosition(true));
    float duration = 0.0f;
    bool nonExpiring = false;
    for (unsigned int i = 0; i < m_pParticleCache->mActiveParticleSystems.size(); ++i) {
        unsigned int techniques = m_pParticleCache->mActiveParticleSystems[i]->getNumTechniques();
        for (unsigned int j = 0; j < techniques; ++j) {
            ParticleUniverse::ParticleTechnique* technique = m_pParticleCache->mActiveParticleSystems[i]->getTechnique(j);
            if (technique->mRunicFlag5b1)
                m_bUnknown127 = true;
            unsigned int emitters = technique->getNumEmitters();
            for (unsigned int k = 0; k < emitters; ++k) {
                EmitterAccess* emitter = reinterpret_cast<EmitterAccess*>(technique->getEmitter(k));
                if (emitter) {
                    emitter->stopping(false);
                    if (emitter->isNonExpiring())
                        nonExpiring = true;
                    int loops = emitter->remainingLoops();
                    if (loops >= 0) {
                        float emissionDuration = emitter->duration()->getValue(NULL, 0.0f);
                        float timeToLive = emitter->timeToLive()->getValue(NULL, 0.0f);
                        duration = std::max((loops + 1.0f) * emissionDuration + timeToLive, duration);
                    }
                }
            }
        }
        m_pParticleCache->mActiveParticleSystems[i]->start();
    }
    if (m_fUnknown120 == 0.0f)
        m_fUnknown120 = duration;
    if (nonExpiring)
        m_fUnknown120 = 0.0f;
    if (m_pResourceManager->getLevel() && m_fUnknown120 > 0.0f) {
        m_fUnknown120 += 0.1f;
        m_pResourceManager->getLevel()->addUpdateObject(this);
        m_bUnknown126 = true;
    }
}

void CParticle::forceParticleUpdate(float elapsed)
{
    if (!m_pParticleCache)
        return;
    for (unsigned int i = 0; i < m_pParticleCache->mActiveParticleSystems.size(); ++i)
        for (float remaining = elapsed; remaining > 0.0f; remaining -= 0.1f)
            m_pParticleCache->mActiveParticleSystems[i]->_update(0.1f);
}

void CParticle::Resume()
{
    if (!m_bVisible || !m_pParticleCache)
        return;
    for (unsigned int i = 0; i < m_pParticleCache->mActiveParticleSystems.size(); ++i)
        m_pParticleCache->mActiveParticleSystems[i]->resume();
}

void CParticle::Pause()
{
    if (!m_bVisible || !m_pParticleCache)
        return;
    for (unsigned int i = 0; i < m_pParticleCache->mActiveParticleSystems.size(); ++i)
        m_pParticleCache->mActiveParticleSystems[i]->pause();
}

void CParticle::getAllEmitters(TArrayList<ParticleUniverse::ParticleEmitter*>& emitters)
{
    if (!m_pParticleCache) {
        m_pParticleCache = m_pParticlePreloader->getParticleCache(m_pUnknown110);
        if (!m_pParticleCache)
            return;
    }
    for (unsigned int i = 0; i < m_pParticleCache->mActiveParticleSystems.size(); ++i) {
        for (unsigned int j = 0; j < m_pParticleCache->mActiveParticleSystems[i]->getNumTechniques(); ++j) {
            ParticleUniverse::ParticleTechnique* technique = m_pParticleCache->mActiveParticleSystems[i]->getTechnique(j);
            if (technique)
                for (unsigned int k = 0; k < technique->getNumEmitters(); ++k)
                    emitters.add(technique->getEmitter(k));
        }
    }
}


CParticle::CParticle(CParticlePreloader* preloader, const std::wstring& file,
                     CResourceManager* resources)
    : CPositionableObject(resources, NULL), m_pParticleCache(NULL),
      m_pUnknown110(file)
{
    m_pParticlePreloader = preloader;
    m_iUnknown118 = 0;
    m_iUnknown11C = 0;
    m_fUnknown120 = 0.0f;
    m_bUnknown124 = false;
    m_bUnknown125 = true;
    m_bUnknown126 = false;
    m_bUnknown127 = false;
    m_bUnknown128 = false;
}
