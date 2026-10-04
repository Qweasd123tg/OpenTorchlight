#include "EmptyStrings.h"
#include "ParticleTechWrapper.h"
#include "ParticleWrapper.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "PlaneColliderWrapper.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "SphereColliderWrapper.h"
#include "UtilitiesMath.h"

void CParticleTechWrapper::setParentGuid(long long guid)
{
    CParticleWrapper::setParentGuid(guid);
}

void CParticleTechWrapper::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
}

void CParticleTechWrapper::setAsLight(bool bIsLight)
{
    m_bIsLight = bIsLight;
    if (bIsLight) {
        setRenderQueue(m_iSortIndex + 0x5f);
    } else {
        setRenderQueue(m_iSortIndex + 0x5a);
    }
}

void CParticleTechWrapper::forceStop()
{
    CParticleWrapper::stop();
}

long long CParticleTechWrapper::updateLevelObject(float elapsed, Ogre::Camera* camera, const Ogre::Vector3& viewer)
{
    return this->updateLevelObject(elapsed, camera, viewer);
}

CParticleTechWrapper::~CParticleTechWrapper()
{
}

void CParticleTechWrapper::setActivated(bool activated)
{
    if (m_pResourceManager->getEditorIsRunning())
        createTextureMaterial();

    if (activated)
    {
        setVisible(true);
        setEnabled(true);
        start();
    }
    else
    {
        setEnabled(false);
        stop();
    }
}

void CParticleTechWrapper::setDepthCheck(bool depthCheck)
{
    m_bDepthCheck = depthCheck;
    if (m_pResourceManager->getEditorIsRunning())
        createTextureMaterial();
}

void CParticleTechWrapper::setParticleRenderStyle(unsigned int style)
{
    if (style <= 3) {
        m_iParticleRenderStyle = style;
        if (m_pResourceManager->getEditorIsRunning())
            createTextureMaterial();
    }
}

void CParticleTechWrapper::setVScroll(float vScroll)
{
    m_fVScroll = vScroll;
    if (!m_pResourceManager->getEditorIsRunning())
        return;

    createTextureMaterial();
    stop();
    start();
}

void CParticleTechWrapper::setUScroll(float uScroll)
{
    m_fUScroll = uScroll;

    if (m_pResourceManager->getEditorIsRunning())
    {
        createTextureMaterial();
        stop();
        start();
    }
}

void CParticleTechWrapper::setDepthBias(float depthBias)
{
    m_fDepthBias = depthBias;
    if (m_pResourceManager->getEditorIsRunning())
        createTextureMaterial();
}
