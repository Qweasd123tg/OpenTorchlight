#include "EmptyStrings.h"
#include "LinearForceWrapper.h"
#include "ForceWrapper.h"
#include "ResourceManager.h"

CLinearForceWrapper::~CLinearForceWrapper()
{
}

CLinearForceWrapper::CLinearForceWrapper(CResourceManager* resourceManager)
    : CForceWrapper(resourceManager, "LinearForce")
{
}
