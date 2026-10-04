#include "EmptyStrings.h"
#include "ResourceManager.h"

CResourceManager::~CResourceManager()
{
    m_pSceneManager = NULL;
    m_pLevel = NULL;
    m_pHierarchy = NULL;
}
