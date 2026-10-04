#include "EmptyStrings.h"
#include "TextureRotateDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "TextureRotateWrapper.h"

CTextureRotateDescriptor::CTextureRotateDescriptor()
    : CAffectorDescriptor(L"Texture Rotate", L"This is a basic accelerator for your particles", L"gear")
{
    AddProperty(L"ROTATION", L"ROTATION SPEED", L"This is the speed at which the particles rotate", (void*)Set_setDynamicPropRotationSpeed, (void*)Get_getDynamicPropRotationSpeed, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"ROTATION", L"STARTING ROTATION", L"Starting rotation angle", (void*)Set_setDynamicPropRotation, (void*)Get_getDynamicPropRotation, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"ROTATION", L"USE OWN ROTATION", L"Making this true will mean the rotation speed will be based off the speed that the particle is currently rotating at do to other affectors.", (void*)Set_setUseOwnRotationSpeed, (void*)Get_getUseOwnRotationSpeed, VARIABLE_TYPE_BOOL, 0);
}

CTextureRotateDescriptor::~CTextureRotateDescriptor()
{
}

CEditorBaseObject* CTextureRotateDescriptor::CreateObject(CEditorScene* scene)
{
    return new CTextureRotateWrapper(scene->getResourceManager());
}
