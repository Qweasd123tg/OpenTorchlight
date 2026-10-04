#include "EmptyStrings.h"
#include "ColliderWrapper.h"
#include "AffectorWrapper.h"
#include "ResourceManager.h"

CColliderWrapper::~CColliderWrapper()
{
}

CColliderWrapper::~CColliderWrapper();

CColliderWrapper::CColliderWrapper(CResourceManager* resourceManager, std::string name)
    : CAffectorWrapper(resourceManager, name)
{
}
