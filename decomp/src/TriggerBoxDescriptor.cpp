#include "EmptyStrings.h"
#include "TriggerBoxDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "TriggerBox.h"

CTriggerBoxDescriptor::CTriggerBoxDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CTriggerDescriptor(name, group, description)
{
    AddProperty(L"PROPERTIES", L"DIMENSIONS", L"Sets the dimensions of the box.", (void*)Set_setDimensions, (void*)Get_getDimensions, VARIABLE_TYPE_VECTOR3, 0);
}

CTriggerBoxDescriptor::~CTriggerBoxDescriptor()
{
}

CEditorBaseObject* CTriggerBoxDescriptor::CreateObject(CEditorScene* scene)
{
    return new CTriggerBox(scene->getResourceManager());
}
