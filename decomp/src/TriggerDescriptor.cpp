#include "EmptyStrings.h"
#include "TriggerDescriptor.h"

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
