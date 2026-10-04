#include "EmptyStrings.h"
#include "WarperDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "Warper.h"

CWarperDescriptor::CWarperDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, true, true, true, true)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the warper enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"LEVEL DELTA", L"Levels up or down to warp (-1 for up 1)", (void*)Set_setLevelDelta, (void*)Get_getLevelDelta, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"PROPERTIES", L"LEVEL ABSOLUTE", L"Absolute level depth", (void*)Set_setLevelDepth, (void*)Get_getLevelDepth, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"PROPERTIES", L"DUNGEON NAME", L"Dungeon to switch to", (void*)Set_setDungeon, (void*)Get_getDungeon, VARIABLE_TYPE_STRING, 0);
    AddProperty(L"PROPERTIES", L"WARP NAME", L"The warp name to look for on the level warping to", (void*)Set_setWarpName, (void*)Get_getWarpName, VARIABLE_TYPE_STRING, 0);
    AddProperty(L"PROPERTIES", L"WAYPOINT", L"This warp activates a waypoint", (void*)Set_setWaypoint, (void*)Get_getWaypoint, VARIABLE_TYPE_BOOL, 0);
    AddInputLogic(INPUT_EVENT_ACTIVATE_WARPER);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
}

CWarperDescriptor::~CWarperDescriptor()
{
}

void CWarperDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int eventType, CEditorBaseObject* source)
{
    if (object != 0) {
        CWarper* warper = dynamic_cast<CWarper*>(object);
        if (warper != 0) {
            if (eventType == 3) {
                warper->setEnabled(false);
                return;
            }
            if (eventType == 0x25) {
                warper->activate();
                return;
            }
            if (eventType == 2) {
                warper->setEnabled(true);
                return;
            }
        }
    }
}

CEditorBaseObject* CWarperDescriptor::CreateObject(CEditorScene* scene)
{
    return new CWarper(scene->getResourceManager());
}
