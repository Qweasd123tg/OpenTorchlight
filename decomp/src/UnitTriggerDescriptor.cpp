#include "TriggerUnit.h"
#include "GameVariables.h"
#include "UnitResourceList.h"
#include "UnitTriggerDescriptor.h"
#include "UnitTriggerDescriptorNames.h"
#include "EmptyStrings.h"
#include "StringUtilities.h"
#include "Quest.h"

void CUnitTriggerDescriptor::update(float value)
{
}

CUnitTriggerDescriptor::~CUnitTriggerDescriptor()
{
}

std::wstring CUnitTriggerDescriptor::GetLoopTypeStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 2)
        return gTRIGGER_LOOP_TYPE_NAMES[0];
    return gTRIGGER_LOOP_TYPE_NAMES[index];
}

unsigned int CUnitTriggerDescriptor::GetLoopTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 3; ++index)
    {
        if (value == gTRIGGER_LOOP_TYPE_NAMES[index])
            return index;
    }
    return 0;
}

void CUnitTriggerDescriptor::AddInputsAndOutputs(CDescriptor* descriptor)
{
    descriptor->AddInputLogic(INPUT_EVENT_COLLIDABLE);
    descriptor->AddInputLogic(INPUT_EVENT_NOT_COLLIDABLE);
    descriptor->AddInputLogic(INPUT_EVENT_RESET);
    descriptor->AddInputLogic(INPUT_EVENT_RESET);
    descriptor->AddInputLogic(INPUT_EVENT_TRIGGER);
    descriptor->AddInputLogic(INPUT_EVENT_SET_STATE_ONE);
    descriptor->AddInputLogic(INPUT_EVENT_SET_STATE_TWO);
    descriptor->AddOutputLogic(OUTPUT_EVENT_RESET);
    descriptor->AddOutputLogic(OUTPUT_EVENT_TRIGGERED);
    descriptor->AddOutputLogic(OUTPUT_EVENT_STATE_ONE);
    descriptor->AddOutputLogic(OUTPUT_EVENT_STATE_TWO);
    descriptor->AddOutputLogic(OUTPUT_EVENT_ACTIVATION_FAILED);
}

std::wstring CUnitTriggerDescriptor::getQuestStringByID(CEditorScene*, CEditorBaseObject*, unsigned int index, void*)
{
    std::map<std::wstring, CQuest*>& quests = CQuestManager::getSingleton()->m_Unknown40;
    std::map<std::wstring, CQuest*>::iterator it = quests.begin();
    for (; it != quests.end(); ++it) {
        if (index == 0)
            return it->second->m_sUnknown50;
        --index;
    }
    if (!quests.empty())
        return quests.begin()->second->m_sUnknown50;
    return EMPTY_WSTRING;
}

unsigned int CUnitTriggerDescriptor::getQuestIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring& value, void*)
{
    std::wstring name = STRINGS::StringUpper(value);
    std::map<std::wstring, CQuest*>& quests = CQuestManager::getSingleton()->m_Unknown40;
    unsigned int index = 0;
    for (std::map<std::wstring, CQuest*>::iterator it = quests.begin(); it != quests.end(); ++index, ++it)
        if (it->second->m_sUnknown50 == name)
            return index;
    return 0;
}

CUnitTriggerDescriptor::CUnitTriggerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, true, true, true, false)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the trigger enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"MODEL", L"The model you want to use for the trigger.", (void*)Set_setUnitModelName, (void*)Get_getUnitModelName, GetTriggerModelIDByString, GetTriggerModelStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"LOOP STYLE", L"The style of the trigger loop.", (void*)Set_setLoopType, (void*)Get_getLoopType, GetLoopTypeIDByString, GetLoopTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddPropertyWithInterpreterFunctions(L"REQUIREMENTS", L"REQUIRED QUEST", L"Quest required to interact with this trigger", (void*)Set_setRequiredQuest, (void*)Get_getRequiredQuest, getQuestIDByString, getQuestStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddPropertyWithInterpreterFunctions(L"REQUIREMENTS", L"REQUIRED ITEM", L"Item required to interact with this trigger", (void*)Set_setRequiredUnit, (void*)Get_getRequiredUnit, getItemIDByString, getItemStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddProperty(L"REQUIREMENTS", L"NUMBER REQUIRED", L"Number of items required to interact with the unit", (void*)Set_setRequiredUnitCount, (void*)Get_getRequiredUnitCount, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddProperty(L"REQUIREMENTS", L"TAKE ITEMS", L"Take the items upon interaction", (void*)Set_setTakeRequiredUnit, (void*)Get_getTakeRequiredUnit, VARIABLE_TYPE_BOOL, 0);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddInputsAndOutputs(this);
}

unsigned int CUnitTriggerDescriptor::getItemIDByString(CEditorScene*, CEditorBaseObject* object, const std::wstring& value, void*)
{
    CTriggerUnit* equipment = dynamic_cast<CTriggerUnit*>(object);
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
std::wstring CUnitTriggerDescriptor::getItemStringByID(CEditorScene*, CEditorBaseObject* object, unsigned int index, void*)
{
    CTriggerUnit* equipment = dynamic_cast<CTriggerUnit*>(object);
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

unsigned int CUnitTriggerDescriptor::GetTriggerModelIDByString(CEditorScene*, CEditorBaseObject* object, const std::wstring& value, void*)
{
    CTriggerUnit* trigger = dynamic_cast<CTriggerUnit*>(object);
    if (trigger == NULL || trigger->getResourceManager() == NULL)
        return static_cast<unsigned int>(-1);
    const std::map<long long, CDataGroup*>* group = trigger->getResourceManager()->getMasterResourceList()->getGroupByName(L"PROPS");
    unsigned int index = 1;
    for (std::map<long long, CDataGroup*>::const_iterator it = group->begin(); it != group->end(); ++it) {
        if (it->second->GetDataValue(L"CREATEAS", L"") != L"TRIGGER")
            continue;
        if (it->second->GetDataValue(L"NAME", L"") == value)
            return index;
        ++index;
    }
    return 0;
}
std::wstring CUnitTriggerDescriptor::GetTriggerModelStringByID(CEditorScene*, CEditorBaseObject* object, unsigned int index, void*)
{
    if (index == 0)
        return L"";
    CTriggerUnit* trigger = dynamic_cast<CTriggerUnit*>(object);
    if (trigger == NULL || trigger->getResourceManager() == NULL)
        return EMPTY_WSTRING;
    const std::map<long long, CDataGroup*>* group = trigger->getResourceManager()->getMasterResourceList()->getGroupByName(L"PROPS");
    --index;
    for (std::map<long long, CDataGroup*>::const_iterator it = group->begin(); it != group->end(); ++it) {
        if (it->second->GetDataValue(L"CREATEAS", L"") != L"TRIGGER")
            continue;
        if (index == 0)
            return it->second->GetDataValue(L"NAME", L"");
        --index;
    }
    return L"";
}
