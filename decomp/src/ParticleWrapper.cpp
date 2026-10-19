#include "EmptyStrings.h"
#include "ParticleWrapper.h"
#include "DataGroup.h"
#include "ResourceManager.h"
#include "ParticleUniverseConstants.h"

void CParticleWrapper::free()
{
}

#include <ParticleUniverseSystem.h>
#include <ParticleUniverseSystemManager.h>
#include "MasterResourceManager.h"
#include "Layout.h"
#include "OgreUtilities.h"
#include "StringUtilities.h"

void CParticleWrapper::stop()
{
    if (m_pParticleSystem) {
        m_bPlaying = false;
        m_pParticleSystem->stop();
        m_pParticleSystem->_resetBounds();
        BroadcastEvent(32);
    }
}

void CParticleWrapper::hideVisualSphereMesh()
{
    if (m_pVisualSphereNode == NULL)
        return;
    if (m_pSceneNode == NULL)
        return;
    if (m_pVisualSphereNode->getParentSceneNode() != NULL)
        m_pSceneNode->removeChild(m_pVisualSphereNode);
}

void CParticleWrapper::resourceFreeing()
{
}

void CParticleWrapper::resourceInit(CResourceManager* resourceManager, CDataGroup* dataGroup)
{
}

CParticleWrapper::~CParticleWrapper()
{
}

CParticleWrapper::CParticleWrapper(CResourceManager* resources)
    : CPositionableObject(resources,NULL),m_pParticleSystem(NULL),
      m_pVisualSphereNode(NULL),m_pVisualSphereEntity(NULL),
      m_bPlaying(false),m_iRandomWeight(1)
{
    createParticleSystem();
}

bool CParticleWrapper::isPlaying()
{
    if (!m_pParticleSystem) return false;
    if (m_pParticleSystem->getNumTechniques() &&
        m_pParticleSystem->getTechnique(0)->getNumberOfEmittedParticles()) return true;
    if (!m_bPlaying && m_pParticleSystem->getState()==ParticleUniverse::ParticleSystem::PSS_STARTED)
        m_pParticleSystem->stop();
    return m_bPlaying;
}

void CParticleWrapper::updateParticleSystem(float elapsed)
{
    if (m_pParticleSystem && isPlaying() &&
        !CMasterResourceManager::getSingleton()->m_pParticleSystemManager->m_paused)
        m_pParticleSystem->_update(elapsed);
}

void CParticleWrapper::start()
{
    if (m_pParticleSystem) {
        m_bPlaying=true;
        m_pParticleSystem->notifyCurrentCamera(m_pResourceManager->getSceneManager()->getCamera("PlayerCam"));
        m_pParticleSystem->_resetBounds();
        m_pParticleSystem->start();
        BroadcastEvent(31);
    }
}

void CParticleWrapper::createParticleSystem()
{
    Ogre::SceneManager* scene=m_pResourceManager->getSceneManager();
    m_pParticleSystem=CMasterResourceManager::getSingleton()->m_pParticleSystemManager->createParticleSystem(STRINGS::uniqueName("part"),scene);
    m_pParticleSystem->setCastShadows(false);
    m_pParticleSystem->setQueryFlags(1);
    if (m_pParticleSystem->getFixedTimeout()<=0.0f)
        m_pParticleSystem->setBoundsAutoUpdated(false,0.25f);
    m_pParticleSystem->setKeepLocal(true);
    m_pSceneNode->attachObject(m_pParticleSystem);
    m_pParticleSystem->prepare();
    m_pParticleSystem->ParticleUniverse::Particle::setEnabled(true);
    if (m_pResourceManager->getEditorIsRunning()) {
        m_bPlaying=true;
        m_pParticleSystem->start();
        showVisualSphereMesh();
    }
    setVisible(true);
    scene=m_pResourceManager->getSceneManager();
    if (scene->getCurrentViewport())
        m_pParticleSystem->notifyCurrentCamera(scene->getCamera("PlayerCam"));
}

void CParticleWrapper::showVisualSphereMesh()
{
    if (m_pVisualSphereNode) {
        OGRE_UTILITIES::addChildSceneNode(m_pSceneNode,m_pVisualSphereNode);
        return;
    }
    if (!getSceneOwner() || dynamic_cast<CLayout*>(getSceneOwner())) return;
    try {
        m_pVisualSphereNode=m_pResourceManager->getSceneManager()->createSceneNode();
        m_pVisualSphereEntity=OGRE_UTILITIES::createEntity(m_pResourceManager->getSceneManager(),static_cast<OGRE_UTILITIES::EPRIMITIVES>(0),static_cast<OGRE_UTILITIES::EQUERYMASK>(-2),"gm");
        m_pVisualSphereNode->attachObject(m_pVisualSphereEntity);
        m_pVisualSphereNode->setScale(0.1f,0.1f,0.1f);
        m_pVisualSphereEntity->setMaterialName("WireframeBlue");
        m_pVisualSphereEntity->setQueryFlags(1);
        m_pVisualSphereEntity->setCastShadows(false);
        sceneNodeAddChild(m_pVisualSphereNode);
    } catch (Ogre::Exception&) {
        Ogre::LogManager::getSingleton().logMessage("[PARTICLEWRAPPER] Error creating entity",Ogre::LML_NORMAL,false);
    }
}
