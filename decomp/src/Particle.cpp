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
    return updateLevelObject(delta, camera, position);
}

CParticle::~CParticle()
{
}

#include "ParticleCache.h"
#include "ParticlePreloader.h"

namespace ParticleUniverse {
class ParticleTechnique;
class ParticleSystem {
public:
    void _update(float);
    void resume();
    void pause();
    unsigned long getNumTechniques() const;
    ParticleTechnique* getTechnique(unsigned long) const;
};
class ParticleTechnique {
public:
    unsigned long getNumEmitters() const;
    ParticleEmitter* getEmitter(unsigned long) const;
};
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
