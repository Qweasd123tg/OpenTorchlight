#include "EmptyStrings.h"
#include "GravityWrapper.h"
#include "AffectorWrapper.h"
#include "ResourceManager.h"

CGravityWrapper::~CGravityWrapper()
{
}

CGravityWrapper::CGravityWrapper(CResourceManager* resourceManager)
    : CAffectorWrapper(resourceManager, "Gravity")
{
}
