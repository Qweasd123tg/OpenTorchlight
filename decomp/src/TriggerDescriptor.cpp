#include "LogicTrigger.h"
#include "EmptyStrings.h"
#include "TriggerDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"

CTriggerDescriptor::CTriggerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, false, false, false, false)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the trigger enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddInputLogic(INPUT_EVENT_RESET);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddOutputLogic(OUTPUT_EVENT_RESET);
    AddOutputLogic(OUTPUT_EVENT_TRIGGERED);
    AddOutputLogic(OUTPUT_EVENT_TRIGGERED_FIRST_TIME);
    AddOutputLogic(OUTPUT_EVENT_DEACTIVATED);
    AddOutputLogic(OUTPUT_EVENT_DEACTIVATED_FIRST_TIME);
}

CTriggerDescriptor::~CTriggerDescriptor()
{
}

CEditorBaseObject* CTriggerDescriptor::CreateObject(CEditorScene*)
{
    return 0;
}

void CTriggerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject*)
{
    CLogicTrigger* trigger = dynamic_cast<CLogicTrigger*>(object);
    if (trigger == NULL)
        return;
    switch (event) {
    case INPUT_EVENT_ENABLE: trigger->setEnabled(true); break;
    case INPUT_EVENT_DISABLE: trigger->setEnabled(false); break;
    case INPUT_EVENT_RESET: trigger->TriggerReset(); break;
    }
}

void CTriggerDescriptor::update(float elapsed)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CLogicTrigger* trigger = dynamic_cast<CLogicTrigger*>(m_Objects[i]);
        if (trigger != NULL)
            trigger->updateTrigger(elapsed, getSceneOwner());
    }
}
