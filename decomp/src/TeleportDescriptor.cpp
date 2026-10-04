#include "EmptyStrings.h"
#include "TeleportDescriptor.h"

CTeleportDescriptor::CTeleportDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, true, true, true, false)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the teleport enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddInputLogic(INPUT_EVENT_ACTIVATE_TELEPORT);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddOutputLogic(OUTPUT_EVENT_ACTIVATED);
}

CTeleportDescriptor::~CTeleportDescriptor()
{
}
