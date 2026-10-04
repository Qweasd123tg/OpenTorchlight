#include "EmptyStrings.h"
#include "InteractiveDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "Interact.h"
#include "StringUtilities.h"

CInteractiveDescriptor::CInteractiveDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"CAMERA CONTROL", L"PAN TIME", L"The amount of time the camera takes to pan to target.", (void*)Set_setCameraPanTime, (void*)Get_getCameraPanTime, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"CAMERA CONTROL", L"EASE IN DISTANCE PCT", L"The percent of distance before the the ease in kicks on. Use a number between 0-1", (void*)Set_setCameraPanTime, (void*)Get_getCameraPanTime, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"CAMERA CONTROL", L"EASE IN PCT", L"When the ease in distance is reached it will use a given pct of the final distance. Use a number between 0-1", (void*)Set_setCameraPanTime, (void*)Get_getCameraPanTime, VARIABLE_TYPE_FLOAT, 0);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"TYPE", L"The type of interactable. Quest - will give the accept dialog. Manual - will use the text field supplied. Interactable - will use the choice menu.", (void*)Set_setInteractableType, (void*)Get_getInteractableType, getTypeIDByString, getTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    unsigned int groupProperty = AddPropertyWithInterpreterFunctions(L"INTERACT WITH", L"GROUP", L"The group to choose from.", (void*)Set_setCategory, (void*)Get_getCategory, GetGroupIDByString, GetGroupStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    unsigned int unitProperty = AddPropertyWithInterpreterFunctions(L"INTERACT WITH", L"UNIT", L"The unit to interact with.", (void*)Set_setUnitInteractWithByIndexKINTERACTABLE_UNIT_ONE, (void*)Get_getUnitInteractWithByIndexKINTERACTABLE_UNIT_ONE, GetResourceIDByString, GetResourceStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    LinkProperty(unitProperty, groupProperty);
    AddOutputLogic(OUTPUT_EVENT_INTERACTED_WITH_UNIT);
    AddOutputLogic(OUTPUT_EVENT_ACCEPTED);
    AddOutputLogic(OUTPUT_EVENT_DECLINED);
}

CInteractiveDescriptor::~CInteractiveDescriptor()
{
}

void CInteractiveDescriptor::InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*)
{
}

unsigned int CInteractiveDescriptor::GetResourceIDByString(
    CEditorScene* scene,
    CEditorBaseObject* object,
    const std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >& value,
    void* userData)
{
    return 0;
}

std::wstring CInteractiveDescriptor::GetGroupStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData)
{
    if (index == 0)
        return std::wstring(L"MONSTERS");

    return std::wstring(L"ITEMS");
}

unsigned int CInteractiveDescriptor::getTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    return STRINGS::getStringIndex(value, reinterpret_cast<const std::wstring*>(gINTERACTABLE_TYPE_NAMES), 4, 0, false);
}

void CInteractiveDescriptor::update(float deltaTime)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CEditorBaseObject *object = m_Objects[i];
        if (object != NULL) {
            CInteract *interact = dynamic_cast<CInteract *>(object);
            if (interact != NULL) {
                interact->update(deltaTime);
            }
        }
    }
}

CEditorBaseObject* CInteractiveDescriptor::CreateObject(CEditorScene* scene)
{
    return new CInteract(scene->getResourceManager());
}
