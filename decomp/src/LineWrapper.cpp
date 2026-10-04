#include "EmptyStrings.h"
#include "LineWrapper.h"
#include "AffectorWrapper.h"
#include "ResourceManager.h"

CLineWrapper::~CLineWrapper()
{
}

/* The non-virtual thunk is compiler-generated and has no separate C++98 definition. */

CLineWrapper::CLineWrapper(CResourceManager* resourceManager)
    : CAffectorWrapper(resourceManager, "Line")
{
    enablePositioning(false);
}
