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

#include "EditorScene.h"
#include "MasterResourceManager.h"
#include "ParticleUniverseAffector.h"
namespace ParticleUniverse {
class ParticleSystemManager {
public:
    ParticleAffector* createAffector(const std::string& name);
    void destroyAffector(ParticleAffector*);
};
}

namespace {
struct AffectorAccess : ParticleUniverse::ParticleAffector
{
    void clearRunicFlag() { mRunicFlag110 = false; }
};
}

CAffectorWrapper::CAffectorWrapper(CResourceManager* resources, std::string name)
    : CPositionableObject(resources, NULL), m_pParticleTechWrapper(NULL),
      m_pAffector(NULL), m_bPositioningEnabled(true), m_bEnabled(true)
{
    m_pAffector = CMasterResourceManager::getSingleton()->m_pParticleSystemManager->createAffector(name);
    m_bEnabled = true;
    reinterpret_cast<AffectorAccess*>(m_pAffector)->clearRunicFlag();
}

void CAffectorWrapper::setParentGuid(long long guid)
{
    if (m_pParticleTechWrapper)
        m_pParticleTechWrapper->removeAffector(this);
    setParentTechniqueWrapper(0);
    CEditorBaseObject::setParentGuid(guid);
    if (!getSceneOwner())
        return;
    while (guid != -1) {
        CEditorBaseObject* object = getSceneOwner()->GetObjectInScene(guid);
        if (!object)
            break;
        CParticleTechWrapper* parent = dynamic_cast<CParticleTechWrapper*>(object);
        if (parent) {
            setParentTechniqueWrapper(parent);
            break;
        }
        guid = object->getParentGuid();
    }
    if (m_pResourceManager->getEditorIsRunning() && getSceneOwner() && getSceneOwner()->getSceneOwner())
        sceneNodeDetachEntity();
}

void CAffectorWrapper::destroyAffector()
{
    if (m_pSceneNode) {
        sceneNodeDetachEntity();
        sceneNodeDestroy();
    }
    if (m_pAffector) {
        setParentTechniqueWrapper(0);
        CMasterResourceManager::getSingleton()->m_pParticleSystemManager->destroyAffector(m_pAffector);
    }
    m_pParticleTechWrapper = 0;
    m_pAffector = 0;
}
