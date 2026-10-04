#include "EmptyStrings.h"
#include "TextureAnimateDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "TextureAnimateWrapper.h"

CTextureAnimateDescriptor::CTextureAnimateDescriptor()
    : CAffectorDescriptor(L"Texture Animation", L"This animates flipbook particle textures", L"gear")
{
    AddProperty(L"ANIMATION", L"ANIMATION SPEED", L"This is the speed at which the particles rotate", (void*)Set_setDynamicPropAnimationSpeed, (void*)Get_getDynamicPropAnimationSpeed, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"ANIMATION", L"USE OWN ANIMATION", L"Making this true will mean the rotation speed will be based off the speed that the particle is currently rotating at do to other affectors.", (void*)Set_setUseOwnAnimationSpeed, (void*)Get_getUseOwnAnimationSpeed, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"ANIMATION", L"USE RANDOM STARTING FRAME", L"Making this true will mean the rotation speed will be based off the speed that the particle is currently rotating at do to other affectors.", (void*)Set_setUseRandomStartingFrame, (void*)Get_getUseRandomStartingFrame, VARIABLE_TYPE_BOOL, 0);
}

CTextureAnimateDescriptor::~CTextureAnimateDescriptor()
{
}

CEditorBaseObject* CTextureAnimateDescriptor::CreateObject(CEditorScene* scene)
{
    return new CTextureAnimateWrapper(scene->getResourceManager());
}
