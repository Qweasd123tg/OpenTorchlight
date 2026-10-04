#include "EmptyStrings.h"
#include "ItemDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"

CItemDescriptor::CItemDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, true, true, true, false)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the trigger enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"ITEM", L"The Item you want to spawn in the level.", (void*)Set_createNewEquipment, (void*)Get_getUnitDataName, getItemIDByString, getItemStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddOutputLogic(OUTPUT_EVENT_ITEM_PICKED_UP);
}

CItemDescriptor::~CItemDescriptor()
{
}

void CItemDescriptor::InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*)
{
}

void CItemDescriptor::deleteNotification()
{
}
