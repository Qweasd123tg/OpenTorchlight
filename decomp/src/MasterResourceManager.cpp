#include "AnimationSet.h"
#include "BatchModelRef.h"
#include "CollisionModel.h"
#include "CollisionModelRef.h"
#include "GenericModel.h"
#include "Graph.h"
#include "MasterResourceManager.h"
#include "ParticlePreloader.h"
#include "SharedStash.h"
#include "SoundBankDataInformation.h"
#include "SoundManager.h"
#include "EmptyStrings.h"
#include "GameVariables.h"
#include "BatchModelRef.h"
#include "CollisionModelRef.h"
#include "MasterResourceManager.h"
#include "RunicCore.h"

CMasterResourceManager* CMasterResourceManager::getSingleton()
{
    return (CMasterResourceManager*)m_pMasterResourceManager;
}

BatchModelRef::BatchModelRef()
    : CRunicCore(), m_pBatchModel(NULL)
{
}

CollisionModelRef::CollisionModelRef()
    : CRunicCore(), m_pCollisionModel(NULL)
{
}

BatchModelRef::~BatchModelRef()
{
    if (m_pBatchModel)
    {
        delete m_pBatchModel;
        m_pBatchModel = 0;
    }
}

CollisionModelRef::~CollisionModelRef()
{
    if (m_pCollisionModel) { delete m_pCollisionModel; m_pCollisionModel = NULL; }
}


// Imported source candidates; historical status is not fresh acceptance.
void CMasterResourceManager::destroyStash()
{
    if (m_stash) { delete m_stash; m_stash = NULL; }
    m_stash = NULL;
}

CollisionModelRef* CMasterResourceManager::getCollisionModel(CCollisionModel* model)
{
    for (unsigned int i = 0; i < m_collisionModels.size(); ++i)
        if (m_collisionModels[i]->m_pCollisionModel == model) return m_collisionModels[i];
    return NULL;
}

void CMasterResourceManager::removeCollisionModel(CCollisionModel* model)
{
    CollisionModelRef* found = getCollisionModel(model);
    if (found) --found->m_referenceCount;
}

BatchModelRef* CMasterResourceManager::getBatchModel(CGenericModel* model)
{
    for (unsigned int i = 0; i < m_batchModels.size(); ++i)
        if (m_batchModels[i]->m_pBatchModel == model) return m_batchModels[i];
    return NULL;
}

void CMasterResourceManager::removeBatchModel(CGenericModel* model)
{
    BatchModelRef* found = getBatchModel(model);
    if (found) --found->m_referenceCount;
}

CAnimationSet* CMasterResourceManager::getAnimationSet(CAnimationSet* model)
{
    for (unsigned int i = 0; i < m_animationSets.size(); ++i)
        if (m_animationSets[i] == model) return m_animationSets[i];
    return NULL;
}

void CMasterResourceManager::removeAnimationSet(CAnimationSet* model)
{
    CAnimationSet* found = getAnimationSet(model);
    if (found) --found->m_nAnimationCount;
}

void CMasterResourceManager::reloadSoundBankData()
{
    if (m_pSoundManager && m_pSoundBankDataInformation) {
        m_pSoundManager->stopAllSounds();
        m_pSoundBankDataInformation->reload(m_resourceSettings);
    }
}

int CMasterResourceManager::getMaxFameLevel()
{
    return m_fameGraph->getControlPoints();
}

int CMasterResourceManager::fameGate(int level)
{
    if (!level) return 0;
    if (level > m_fameGraph->getControlPoints()) level = m_fameGraph->getControlPoints();
    return static_cast<int>(m_fameGraph->getValue(static_cast<float>(level), 0));
}

int CMasterResourceManager::getMaxLevel()
{
    return m_experienceGraph->getControlPoints();
}

int CMasterResourceManager::experienceGate(int level)
{
    if (!level) return 0;
    if (level > m_experienceGraph->getControlPoints()) level = m_experienceGraph->getControlPoints();
    return static_cast<int>(m_experienceGraph->getValue(static_cast<float>(level), 0));
}

CollisionModelRef* CMasterResourceManager::getCollisionModel(std::wstring name)
{
    for (unsigned int i = 0; i < m_collisionModels.size(); ++i)
        if (m_collisionModels[i]->m_sUnknown20 == name) return m_collisionModels[i];
    return NULL;
}

BatchModelRef* CMasterResourceManager::getBatchModel(std::wstring name)
{
    for (unsigned int i = 0; i < m_batchModels.size(); ++i)
        if (m_batchModels[i]->m_sBatchModelName == name) return m_batchModels[i];
    return NULL;
}

void CMasterResourceManager::createParticleReloader()
{
    if (!m_pParticlePreloader) m_pParticlePreloader = new CParticlePreloader(m_resourceSettings);
}

void CMasterResourceManager::addAnimationSet(CAnimationSet* animations)
{
    m_animationSets.push_back(animations);
}

CAnimationSet* CMasterResourceManager::getAnimationSet(std::wstring name)
{
    for (unsigned int i = 0; i < m_animationSets.size(); ++i)
        if (m_animationSets[i]->m_wsName == name) return m_animationSets[i];
    return NULL;
}
