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
    delete m_pCollisionModel;
}
