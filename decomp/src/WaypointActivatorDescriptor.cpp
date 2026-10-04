#include "EmptyStrings.h"
#include "WaypointActivatorDescriptor.h"

CWaypointActivatorDescriptor::CWaypointActivatorDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, true, true, true, true)
{
    AddInputLogic(INPUT_EVENT_ACTIVATE);
}

CWaypointActivatorDescriptor::~CWaypointActivatorDescriptor()
{
}
