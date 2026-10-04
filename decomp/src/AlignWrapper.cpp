#include "EmptyStrings.h"
#include "AlignWrapper.h"
#include "AffectorWrapper.h"
#include "ResourceManager.h"

CAlignWrapper::~CAlignWrapper()
{
}

/* The non-virtual thunk is compiler-generated; no out-of-line C++ definition is required. */

CAlignWrapper::CAlignWrapper(CResourceManager* resourceManager)
    : CAffectorWrapper(resourceManager, "Align")
{
}
