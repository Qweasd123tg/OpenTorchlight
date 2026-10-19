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

#include <ParticleUniverseTechnique.h>
#include <ParticleRenderers/ParticleUniverseRibbonTrailRenderer.h>
#include <ParticleRenderers/ParticleUniverseBillboardRenderer.h>

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

bool CParticleTechWrapper::updateLevelObject(float elapsed, Ogre::Camera* camera, const Ogre::Vector3& viewer)
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

void CParticleTechWrapper::setFlipbookHeight(int value)
{
    m_iFlipbookHeight = value;
    m_technique->setFlipbookWidthHeight(m_iFlipbookWidth, m_iFlipbookHeight);
}

void CParticleTechWrapper::setFlipbookWidth(int value)
{
    m_iFlipbookWidth = value;
    m_technique->setFlipbookWidthHeight(m_iFlipbookWidth, m_iFlipbookHeight);
}

void CParticleTechWrapper::setRibbonLocalTrail(bool value)
{
    m_bRibbonLocalTrail = value;
    if (m_ribbonRenderer)
        m_ribbonRenderer->setTrailLocal(value);
}

void CParticleTechWrapper::setRibbonMaxChains(unsigned int count)
{
    m_iRibbonMaxChains = count > 100 ? 100 : count;
    if (m_ribbonRenderer)
        m_ribbonRenderer->setMaxChainElements(m_iRibbonMaxChains);
}

void CParticleTechWrapper::setRibbonLength(float value)
{
    m_fRibbonLength = value;
    if (m_ribbonRenderer)
        m_ribbonRenderer->setTrailLength(value);
}

void CParticleTechWrapper::setRibbonWidth(float value)
{
    m_fRibbonWidth = value;
    if (m_ribbonRenderer)
        m_ribbonRenderer->setTrailWidth(value);
}

void CParticleTechWrapper::setSortIndex(unsigned int index)
{
    m_iSortIndex = index;
    if (m_bIsLight)
        setRenderQueue(index + 95);
    else
        setRenderQueue(index + 90);
}

void CParticleTechWrapper::setSorts(bool sorted)
{
    m_bSorts = sorted;
    if (m_technique->getRenderer())
        m_technique->getRenderer()->setSorted(m_bSorts);
}

void CParticleTechWrapper::setBillboardOrigin(unsigned int origin)
{
    m_billboardOrigin=origin;
    if(m_pUnknown180)m_pUnknown180->setBillboardOrigin(static_cast<Ogre::BillboardOrigin>(origin));
}

void CParticleTechWrapper::setBillboardRotationType(unsigned int rotation)
{
    m_billboardRotation=rotation;
    if(m_pUnknown180)m_pUnknown180->setBillboardRotationType(static_cast<Ogre::BillboardRotationType>(rotation));
}

void CParticleTechWrapper::setRenderQueue(unsigned int queue)
{
    m_renderQueue=queue>100?100:queue;
    if(m_technique->getRenderer())m_technique->getRenderer()->setRenderQueueGroup(m_renderQueue);
}
