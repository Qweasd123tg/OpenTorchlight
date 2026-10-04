#include "EmptyStrings.h"
#include "GeometryRotateWrapper.h"
#include "AffectorWrapper.h"
#include "ResourceManager.h"

CGeometryRotateWrapper::~CGeometryRotateWrapper()
{
}

// The non-virtual thunk is emitted automatically by the compiler as an alternate
// entry point for the virtual destructor; it cannot be defined separately in C++.

CGeometryRotateWrapper::CGeometryRotateWrapper(CResourceManager* resourceManager)
    : CAffectorWrapper(resourceManager, "GeometryRotator")
{
}
