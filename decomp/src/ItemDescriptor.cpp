#include "Equipment.h"
#include "UnitResourceList.h"
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

#include "Level.h"

bool CItemDescriptor::DescriptorObjectBeingDeleted(CEditorBaseObject* object)
{
    CLevel* level = getSceneOwner()->getResourceManager()->getLevel();
    if (level)
        level->removeItem(static_cast<CItem*>(object), true);
    return true;
}

unsigned int CItemDescriptor::getItemIDByString(CEditorScene*, CEditorBaseObject* object, const std::wstring& value, void*)
{
    CEquipment* equipment = dynamic_cast<CEquipment*>(object);
    if (equipment == NULL || equipment->getResourceManager() == NULL)
        return static_cast<unsigned int>(-1);
    const std::map<long long, CDataGroup*>* group = equipment->getResourceManager()->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[0]);
    unsigned int index = 0;
    for (std::map<long long, CDataGroup*>::const_iterator it = group->begin(); it != group->end(); ++it, ++index) {
        if (it->second->GetDataValue(L"NAME", EMPTY_WSTRING) == value)
            return index;
    }
    return 0;
}
std::wstring CItemDescriptor::getItemStringByID(CEditorScene*, CEditorBaseObject* object, unsigned int index, void*)
{
    CEquipment* equipment = dynamic_cast<CEquipment*>(object);
    if (equipment == NULL || equipment->getResourceManager() == NULL)
        return EMPTY_WSTRING;
    const std::map<long long, CDataGroup*>* group = equipment->getResourceManager()->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[0]);
    std::wstring fallback = EMPTY_WSTRING;
    std::map<long long, CDataGroup*>::const_iterator it = group->begin();
    if (it != group->end())
        fallback = it->second->GetDataValue(L"NAME", L"");
    for (; it != group->end(); ++it) {
        if (index == 0)
            return it->second->GetDataValue(L"NAME", L"");
        --index;
    }
    return fallback;
}
