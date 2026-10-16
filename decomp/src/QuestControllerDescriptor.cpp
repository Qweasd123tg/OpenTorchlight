#include "UnitResourceList.h"
#include "Quest.h"
#include "StringUtilities.h"
#include "EmptyStrings.h"
#include "QuestControllerDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "QuestController.h"
#include "ResourceManager.h"

CQuestControllerDescriptor::CQuestControllerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"PROPERTIES", L"DISABLE PLAYER", L"If true will disable the player.", (void*)Set_setPlayerGetsDisabled, (void*)Get_getPlayerGetsDisabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"BROADCAST ON LOAD", L"If true when the level loads it'll broadcast the message.", (void*)Set_setBroadcastEventsOnLoad, (void*)Get_getBroadcastEventsOnLoad, VARIABLE_TYPE_BOOL, 0);
    unsigned int groupProperty = AddPropertyWithInterpreterFunctions(L"INTERACT WITH", L"GROUP", L"The group to choose from.", (void*)Set_setCategory, (void*)Get_getCategory, GetGroupIDByString, GetGroupStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    unsigned int unitProperty = AddPropertyWithInterpreterFunctions(L"INTERACT WITH", L"UNIT", L"The unit to interact with.", (void*)Set_setUnitInteractWith, (void*)Get_getUnitInteractWith, GetResourceIDByString, GetResourceStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    LinkProperty(unitProperty, groupProperty);
    AddPropertyWithInterpreterFunctions(L"QUEST", L"QUEST", L"The quest the quest controller .... well controls.", (void*)Set_setQuest, (void*)Get_getQuest, getQuestIDByString, getQuestStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddInputLogic(INPUT_EVENT_INTERACT);
    AddInputLogic(INPUT_EVENT_FORCE_ACCEPT);
    AddInputLogic(INPUT_EVENT_FORCE_NOT_ACCEPTED);
    AddInputLogic(INPUT_EVENT_FORCE_COMPLETE);
    AddInputLogic(INPUT_EVENT_FORCE_NOT_COMPLETE);
    AddOutputLogic(OUTPUT_EVENT_INTERACTING);
    AddOutputLogic(OUTPUT_EVENT_INTERACTED);
    AddOutputLogic(OUTPUT_EVENT_INTERACTED_ACCEPTED);
    AddOutputLogic(OUTPUT_EVENT_INTERACTED_DECLINED);
    AddOutputLogic(OUTPUT_EVENT_QUEST_ACTIVE);
    AddOutputLogic(OUTPUT_EVENT_QUEST_NOT_ACTIVE);
    AddOutputLogic(OUTPUT_EVENT_QUEST_COMPLETE);
    AddOutputLogic(OUTPUT_EVENT_QUEST_NOT_COMPLETE);
    AddOutputLogic(OUTPUT_EVENT_QUEST_ABANDONED);
}

CQuestControllerDescriptor::~CQuestControllerDescriptor()
{
}

unsigned int CQuestControllerDescriptor::GetResourceIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring&, void*)
{
    return 0;
}

void CQuestControllerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* object2)
{
    CQuestController* controller = dynamic_cast<CQuestController*>(object);

    if (controller != NULL) {
        switch (event) {
        case 0x30:
            controller->interactWithUnit();
            return;
        case 0x35:
            controller->setQuestAccepted(true);
            return;
        case 0x36:
            controller->setQuestAccepted(false);
            return;
        case 0x37:
            controller->setQuestComplete(true);
            return;
        case 0x38:
            controller->setQuestComplete(false);
            return;
        }
    }
}

void CQuestControllerDescriptor::descriptorSceneActivated(CEditorScene* scene)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CQuestController* controller = dynamic_cast<CQuestController*>(m_Objects[i]);
        if (controller == NULL)
            continue;
        if (scene->getResourceManager()->getEditorIsRunning())
            continue;
        controller->initQuestController();
    }
}

CEditorBaseObject* CQuestControllerDescriptor::CreateObject(CEditorScene* scene)
{
    return new CQuestController(scene->getResourceManager());
}

std::wstring CQuestControllerDescriptor::GetGroupStringByID(CEditorScene*, CEditorBaseObject*, unsigned int index, void*)
{
    if (index == 0)
        return gRESOURCE_GROUP_NAMES[1];
    if (index == 1)
        return gRESOURCE_GROUP_NAMES[0];
    return gRESOURCE_GROUP_NAMES[3];
}

unsigned int CQuestControllerDescriptor::GetGroupIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring& value, void*)
{
    if (value == gRESOURCE_GROUP_NAMES[0])
        return 1;
    if (value == gRESOURCE_GROUP_NAMES[3])
        return 2;
    return 0;
}

std::wstring CQuestControllerDescriptor::getQuestStringByID(CEditorScene*, CEditorBaseObject*, unsigned int index, void*)
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

unsigned int CQuestControllerDescriptor::getQuestIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring& value, void*)
{
    std::wstring name = STRINGS::StringUpper(value);
    std::map<std::wstring, CQuest*>& quests = CQuestManager::getSingleton()->m_Unknown40;
    unsigned int index = 0;
    for (std::map<std::wstring, CQuest*>::iterator it = quests.begin(); it != quests.end(); ++index, ++it)
        if (it->second->m_sUnknown50 == name)
            return index;
    return 0;
}

std::wstring CQuestControllerDescriptor::GetResourceStringByID(CEditorScene*, CEditorBaseObject* object, unsigned int index, void*)
{
    if (index == 0)
        return EMPTY_WSTRING;
    CQuestController* controller = dynamic_cast<CQuestController*>(object);
    if (controller == NULL || controller->m_pResourceManager == NULL)
        return EMPTY_WSTRING;
    const std::map<long long, CDataGroup*>* group;
    if (std::wstring(controller->m_sCategory) == gRESOURCE_GROUP_NAMES[1])
        group = controller->m_pResourceManager->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[1]);
    else if (std::wstring(controller->m_sCategory) == gRESOURCE_GROUP_NAMES[0])
        group = controller->m_pResourceManager->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[0]);
    else if (std::wstring(controller->m_sCategory) == gRESOURCE_GROUP_NAMES[3])
        group = controller->m_pResourceManager->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[3]);
    else
        return EMPTY_WSTRING;
    for (std::map<long long, CDataGroup*>::const_iterator it = group->begin(); it != group->end(); ++it) {
        if (--index == 0)
            return it->second->GetDataValue(L"NAME", EMPTY_WSTRING);
    }
    return EMPTY_WSTRING;
}
