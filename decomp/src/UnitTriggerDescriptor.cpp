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

void CUnitTriggerDescriptor::AddInputsAndOutputs(CDescriptor*)
{
    AddInputLogic(INPUT_EVENT_COLLIDABLE);
    AddInputLogic(INPUT_EVENT_NOT_COLLIDABLE);
    AddInputLogic(INPUT_EVENT_RESET);
    AddInputLogic(INPUT_EVENT_RESET);
    AddInputLogic(INPUT_EVENT_TRIGGER);
    AddInputLogic(INPUT_EVENT_SET_STATE_ONE);
    AddInputLogic(INPUT_EVENT_SET_STATE_TWO);
    AddOutputLogic(OUTPUT_EVENT_RESET);
    AddOutputLogic(OUTPUT_EVENT_TRIGGERED);
    AddOutputLogic(OUTPUT_EVENT_STATE_ONE);
    AddOutputLogic(OUTPUT_EVENT_STATE_TWO);
    AddOutputLogic(OUTPUT_EVENT_ACTIVATION_FAILED);
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
