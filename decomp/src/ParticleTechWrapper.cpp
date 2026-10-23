#include "EmptyStrings.h"
#include "Level.h"
#include "GenericModel.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include <OgreTextureManager.h>
#include "MasterResourceManager.h"
#include <ParticleUniverseSystemManager.h>
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
#include <ParticleUniverseSystem.h>
#include <ParticleUniverseEmitter.h>
#include <ParticleUniverseAffector.h>
#include <ParticleRenderers/ParticleUniverseRibbonTrailRenderer.h>
#include <ParticleRenderers/ParticleUniverseBillboardRenderer.h>
#include "ParticleEmitterWrapper.h"
#include "AffectorWrapper.h"

void CParticleTechWrapper::addEmitter(CParticleEmitterWrapper* emitter)
{
    if (!emitter)
        return;
    if (m_Unknown1D8.find(emitter) == -1)
        m_Unknown1D8.add(emitter);
    bool playing = false;
    if (m_pResourceManager->getEditorIsRunning()) {
        playing = isPlaying();
        if (m_pParticleSystem)
            m_pParticleSystem->stop();
    }
    if (m_technique)
        m_technique->addEmitter(emitter->m_pEmitter);
    emitter->sceneNodeRemoveFromParent();
    sceneNodeAddChild(emitter->getSceneNode());
    if (m_pResourceManager->getEditorIsRunning() && m_pParticleSystem && playing) {
        m_pParticleSystem->stop();
        m_pParticleSystem->start();
    }
}

void CParticleTechWrapper::removeEmitter(CParticleEmitterWrapper* emitter)
{
    if (!emitter)
        return;
    m_Unknown1D8.remove(emitter);
    emitter->sceneNodeRemoveFromParent();
    bool playing = false;
    if (m_pResourceManager->getEditorIsRunning()) {
        playing = isPlaying();
        if (m_pParticleSystem)
            m_pParticleSystem->stop();
    }
    if (m_technique && emitter->m_pEmitter && emitter->m_pEmitter->getParentTechnique()) {
        if (m_technique != emitter->m_pEmitter->getParentTechnique())
            return;
        m_technique->removeEmitter(emitter->m_pEmitter);
    }
    if (m_pResourceManager->getEditorIsRunning() && m_pParticleSystem && playing)
        m_pParticleSystem->start();
}

void CParticleTechWrapper::addAffector(CAffectorWrapper* affector)
{
    if (!affector || m_Unknown1F0.find(affector) != -1)
        return;
    bool playing = false;
    if (m_pResourceManager->getEditorIsRunning()) {
        playing = isPlaying();
        if (m_pParticleSystem)
            m_pParticleSystem->stop();
    }
    m_Unknown1F0.add(affector);
    sceneNodeAddChild(affector->getSceneNode());
    if (m_technique)
        m_technique->addAffector(affector->m_pAffector);
    if (m_pResourceManager->getEditorIsRunning() && m_pParticleSystem && playing)
        m_pParticleSystem->start();
}

void CParticleTechWrapper::removeAffector(CAffectorWrapper* affector)
{
    if (!affector)
        return;
    m_Unknown1F0.remove(affector);
    bool playing = false;
    if (m_pResourceManager->getEditorIsRunning()) {
        playing = isPlaying();
        if (m_pParticleSystem)
            m_pParticleSystem->stop();
    }
    affector->sceneNodeRemoveFromParent();
    if (m_technique && affector->m_pAffector && affector->m_pAffector->getParentTechnique()) {
        if (m_technique != affector->m_pAffector->getParentTechnique())
            return;
        m_technique->removeAffector(affector->m_pAffector);
    }
    if (m_pResourceManager->getEditorIsRunning() && m_pParticleSystem && playing)
        m_pParticleSystem->start();
}

void CParticleTechWrapper::setRibbonEndFade(bool fade)
{
    m_bRibbonEndFade = fade;
    if (m_ribbonRenderer) {
        if (fade) {
            m_ribbonRenderer->setStartColour(Ogre::ColourValue(0, 0, 0, 0));
            m_ribbonRenderer->setEndColour(Ogre::ColourValue(0, 0, 0, 0));
        } else {
            m_ribbonRenderer->setStartColour(Ogre::ColourValue(1, 1, 1, 1));
            m_ribbonRenderer->setEndColour(Ogre::ColourValue(1, 1, 1, 1));
        }
    }
}

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
    if (m_bUnknown208) {
        if (m_technique && m_technique->getParticlesUpdating())
            return true;
        m_bUnknown208 = false;
        CParticleWrapper::stop();
        setVisible(false);
        return false;
    }
    return true;
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


bool CParticleTechWrapper::isPlaying()
{
    if (!m_pParticleSystem)
        return false;
    bool nonExpiring = false;
    for (unsigned int i = 0; i < m_Unknown1D8.size(); ++i) {
        if (m_Unknown1D8[i]->m_pEmitter->isNonExpiring()) {
            nonExpiring = true;
            break;
        }
    }
    if (nonExpiring && m_pParticleSystem->getNumTechniques() &&
        m_pParticleSystem->getTechnique(0)->getNumberOfEmittedParticles())
        return true;
    if (m_bPlaying) {
        for (unsigned int i = 0; i < m_Unknown1D8.size(); ++i)
            if (m_Unknown1D8[i]->getIsDoneEmitting())
                stop();
        return m_bPlaying;
    }
    if (m_pParticleSystem->getState() == ParticleUniverse::ParticleSystem::PSS_STARTED)
        m_pParticleSystem->stop();
    return m_bPlaying;
}

void CParticleTechWrapper::start()
{
    if (!getEnabled()) {
        stop();
        return;
    }
    if (m_bPlaying)
        stop();
    m_technique->getNumberOfEmittedParticles();
    setVisible(true);
    for (unsigned int i = 0; i < m_Unknown1D8.size(); ++i) {
        m_Unknown1D8[i]->starting();
        m_Unknown1D8[i]->setEnabled(true);
    }
    CParticleWrapper::start();
    m_technique->getRenderer()->setVisible(true);
}

void CParticleTechWrapper::stop()
{
    bool nonExpiring = false;
    for (unsigned int i = 0; i < m_Unknown1D8.size(); ++i) {
        if (m_Unknown1D8[i]->m_pEmitter->isNonExpiring()) {
            nonExpiring = true;
            break;
        }
    }
    if (!m_pResourceManager->getLevel() || nonExpiring ||
        !m_technique->getNumberOfEmittedParticles()) {
        CParticleWrapper::stop();
        return;
    }
    if (!m_bUnknown208) {
        m_bUnknown208 = true;
        m_pResourceManager->getLevel()->addUpdateObject(this);
    }
    for (unsigned int i = 0; i < m_Unknown1D8.size(); ++i)
        m_Unknown1D8[i]->setEnabled(false);
}

CParticleTechWrapper::CParticleTechWrapper(CResourceManager* resources)
    : CParticleWrapper(resources), m_technique(NULL), m_renderType(13),
      m_renderQueue(90), m_billboardRotation(0), m_billboardOrigin(4),
      m_fRibbonLength(10.0f), m_fRibbonWidth(1.0f), m_iRibbonMaxChains(3),
      m_bRibbonEndFade(false), m_bRibbonLocalTrail(false),
      m_iFlipbookWidth(1), m_iFlipbookHeight(1), m_fUScroll(0.0f),
      m_fVScroll(0.0f), m_bSorts(false), m_pUnknown180(NULL),
      m_iUnknown188(0), m_iUnknown190(0), m_iUnknown198(0),
      m_ribbonRenderer(NULL), m_pUnknown1A8(NULL), m_pTexturePath(L""),
      m_pModelPath(L""), m_pUnknown1C0(""), m_iParticleRenderStyle(1),
      m_bDepthCheck(true), m_bIsLight(false), m_bUnknown1CE(false),
      m_iSortIndex(0), m_fDepthBias(0.0f), m_Unknown1D8(10),
      m_Unknown1F0(10), m_bUnknown208(false)
{
    m_technique = CMasterResourceManager::getSingleton()->m_pParticleSystemManager->createTechnique();
    m_technique->position = Ogre::Vector3(0.0f, 0.0f, 0.0f);
    m_technique->setDefaultDepth(1.0f);
    m_technique->setDefaultHeight(0.5f);
    m_technique->setDefaultWidth(0.5f);
    m_technique->setVisualParticleQuota(50);
    m_technique->setMaxVelocity(9999.0f);
    m_technique->setEnabled(true);
    setRenderType(0, false);
    setRenderQueue(90);
    if (m_pParticleSystem)
        m_pParticleSystem->addTechnique(m_technique);
    setRenderType(0, false);
}

void CParticleTechWrapper::setModelPath(const std::wstring& path)
{
    m_pModelPath = path;
    if (!m_pUnknown1A8 && path != L"") {
        m_pUnknown1A8 = new CGenericModel(m_pResourceManager, NULL, EMPTY_WSTRING, EMPTY_WSTRING, false);
        setRenderType(m_renderType, true);
    }
}

void CParticleTechWrapper::setTexturePath(const std::wstring& path)
{
    if (m_pResourceManager->getEditorIsRunning() && m_pTexturePath == path && path != L"") {
        std::wstring name = FILESYSTEM::GetFileName(path);
        Ogre::TexturePtr texture = Ogre::TextureManager::getSingletonPtr()->getByName(STRINGS::StringConvertToNarrow(name.c_str()));
        if (!texture.isNull() && texture->isLoaded() && texture->isReloadable())
            texture->reload();
    }
    m_pTexturePath = path;
    if (m_pResourceManager->getEditorIsRunning())
        createTextureMaterial();
}
