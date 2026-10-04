#include "EmptyStrings.h"
#include "AffectorWrapper.h"
#include "ParticleTechWrapper.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ParticleWrapper.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

void CAffectorWrapper::enablePositioning(bool enabled)
{
    if (m_bPositioningEnabled != enabled) {
        m_bPositioningEnabled = enabled;
        if (m_pEntity != NULL) {
            if (enabled)
                sceneNodeAttachEntity(m_pEntity);
            else
                sceneNodeDetachEntity();
        }
    }
}

void CAffectorWrapper::positionUpdated(const Ogre::Vector3& position)
{
    static bool bUpdatingPosition = false;

    if (bUpdatingPosition)
        return;

    bUpdatingPosition = true;

    if (m_bPositioningEnabled && m_pAffector)
    {
        reinterpret_cast<CAffectorWrapper*>(m_pAffector)->m_vPosition = position;
        bUpdatingPosition = false;
        return;
    }

    if (m_pAffector)
        reinterpret_cast<CAffectorWrapper*>(m_pAffector)->m_vPosition = Ogre::Vector3::ZERO;

    if (position != Ogre::Vector3::ZERO)
        setPosition(Ogre::Vector3::ZERO);

    bUpdatingPosition = false;
}

void CAffectorWrapper::setParentTechniqueWrapper(CParticleTechWrapper* parent)
{
    if (m_pAffector != 0) {
        if (m_pParticleTechWrapper != 0) {
            m_pParticleTechWrapper->removeAffector(this);
        }

        m_pParticleTechWrapper = parent;

        if (parent != 0) {
            parent->addAffector(this);
        }
    }
}

CAffectorWrapper::~CAffectorWrapper()
{
}
