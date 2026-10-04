#include "EmptyStrings.h"
#include "SineForceWrapper.h"
#include "ForceWrapper.h"
#include "ResourceManager.h"

CSineForceWrapper::~CSineForceWrapper()
{
}

CSineForceWrapper::CSineForceWrapper(CResourceManager* resourceManager)
    : CForceWrapper(resourceManager, "SineForce")
{
}
