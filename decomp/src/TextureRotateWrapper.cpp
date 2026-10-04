#include "EmptyStrings.h"
#include "TextureRotateWrapper.h"
#include "AffectorWrapper.h"
#include "ResourceManager.h"

CTextureRotateWrapper::~CTextureRotateWrapper()
{
}

CTextureRotateWrapper::CTextureRotateWrapper(CResourceManager* resourceManager)
    : CAffectorWrapper(resourceManager, "TextureRotator")
{
}
