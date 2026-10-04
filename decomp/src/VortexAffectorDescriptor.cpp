#include "EmptyStrings.h"
#include "VortexAffectorDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "VortexWrapper.h"

CVortexAffectorDescriptor::CVortexAffectorDescriptor()
    : CAffectorDescriptor(L"Vortext", L"This will effect your particles as if they were in a vortex", L"gear")
{
    AddProperty(L"ROTATION", L"DIRECTION", L"This is the axis which the vortex will rotate", (void*)Set_setRotationVector, (void*)Get_getRotationVector, VARIABLE_TYPE_VECTOR3, 0);
    AddProperty(L"ROTATION", L"RATE", L"This is the rate of the rotation", (void*)Set_setDynamicPropRotationSpeed, (void*)Get_getDynamicPropRotationSpeed, VARIABLE_TYPE_FLOAT, 16);
}

CVortexAffectorDescriptor::~CVortexAffectorDescriptor()
{
}

CEditorBaseObject* CVortexAffectorDescriptor::CreateObject(CEditorScene* scene)
{
    return new CVortexWrapper(scene->getResourceManager());
}
