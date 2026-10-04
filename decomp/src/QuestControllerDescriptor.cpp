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
        CQuestController* questController =
            m_Objects[i] != NULL
                ? dynamic_cast<CQuestController*>(m_Objects[i])
                : NULL;

        if (questController != NULL &&
            !scene->getResourceManager()->getEditorIsRunning()) {
            questController->initQuestController();
        }
    }
}

CEditorBaseObject* CQuestControllerDescriptor::CreateObject(CEditorScene* scene)
{
    return new CQuestController(scene->getResourceManager());
}
