#include "EmptyStrings.h"
#include "WaypointActivatorDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "WaypointActivator.h"

CWaypointActivatorDescriptor::CWaypointActivatorDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, true, true, true, true)
{
    AddInputLogic(INPUT_EVENT_ACTIVATE);
}

CWaypointActivatorDescriptor::~CWaypointActivatorDescriptor()
{
}

void CWaypointActivatorDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject*)
{
    if (object != NULL) {
        CWaypointActivator* waypoint = dynamic_cast<CWaypointActivator*>(object);
        if (waypoint != NULL && event == 0xf) {
            waypoint->activate();
        }
    }
}

CEditorBaseObject* CWaypointActivatorDescriptor::CreateObject(CEditorScene* scene)
{
    return new CWaypointActivator(scene->getResourceManager());
}
