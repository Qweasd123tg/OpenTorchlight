#include "EmptyStrings.h"
#include "BoxColliderDescriptor.h"
#include "GameVariables.h"
#include "BoxColliderWrapper.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"

CBoxColliderDescriptor::CBoxColliderDescriptor()
    : CColliderDescriptor(L"Box Collision")
{
    AddProperty(L"DIMINSIONS", L"WIDTH", L"Width of the box.", (void*)Set_setWidth, (void*)Get_getWidth, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"DIMINSIONS", L"HEIGHT", L"Height of the box.", (void*)Set_setHeight, (void*)Get_getHeight, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"DIMINSIONS", L"DEPTH", L"Depth of the box.", (void*)Set_setDepth, (void*)Get_getDepth, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"VISUAL BOX", L"SHOW BOX", L"Shows or hides the box.", (void*)Set_setShowBox, (void*)Get_getShowBox, VARIABLE_TYPE_BOOL, 0);
}

CBoxColliderDescriptor::~CBoxColliderDescriptor()
{
}

CEditorBaseObject* CBoxColliderDescriptor::CreateObject(CEditorScene* scene)
{
    return new CBoxColliderWrapper(scene->getResourceManager());
}
