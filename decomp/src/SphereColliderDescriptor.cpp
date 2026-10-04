#include "EmptyStrings.h"
#include "SphereColliderDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "SphereColliderWrapper.h"

CSphereColliderDescriptor::CSphereColliderDescriptor()
    : CColliderDescriptor(L"Sphere Collision")
{
    AddProperty(L"SIZE", L"RADIUS", L"Radius of the sphere.", (void*)Set_setRadius, (void*)Get_getRadius, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"VISUAL SPHERE", L"SHOW SPHERE", L"Shows or hides the sphere.", (void*)Set_setShowSphere, (void*)Get_getShowSphere, VARIABLE_TYPE_BOOL, 0);
}

CSphereColliderDescriptor::~CSphereColliderDescriptor()
{
}

CEditorBaseObject* CSphereColliderDescriptor::CreateObject(CEditorScene* scene)
{
    return new CSphereColliderWrapper(scene->getResourceManager());
}
