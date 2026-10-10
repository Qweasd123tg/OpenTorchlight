#include "Affix.h"
#include "BaseUnit.h"
#include "Effect.h"
#include "EffectManager.h"
#include "EmptyStrings.h"
#include "Particle.h"
#include "ResourceManager.h"
#include "Skill.h"


// Imported source candidates; historical status is not fresh acceptance.
void CEffect::getMaxCaculatedValue()
{
    calculateBaseValue(static_cast<ECALCULATETYPES>(1));
}

void CEffect::getMinCaculatedValue()
{
    calculateBaseValue(static_cast<ECALCULATETYPES>(2));
}

void CEffect::playFX(CResourceManager* manager, const Ogre::Vector3& position)
{
    if (!m_particle) {
        m_particle=manager->createParticle(m_particleName.c_str());
        if (m_particle) {
            m_particle->setPosition(position);
            m_particle->Start();
        }
    }
}

bool CEffect::fxShouldPlay()
{
    if (m_particle && m_particle->m_pParticleCache) return false;
    return m_particleName != EMPTY_WSTRING;
}
