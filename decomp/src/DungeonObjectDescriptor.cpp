#include "EmptyStrings.h"
#include "DungeonObjectDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "DungeonObject.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"

CDungeonObjectDescriptor::CDungeonObjectDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, true, true, true, true)
{
    AddProperty(L"PROPERTIES", L"DUNGEON NAME", L"Dungeon to switch to", (void*)Set_setDungeon, (void*)Get_getDungeon, VARIABLE_TYPE_STRING, 0);
    AddInputLogic(INPUT_EVENT_CLEAR_HISTORY);
}

CDungeonObjectDescriptor::~CDungeonObjectDescriptor()
{
}

void CDungeonObjectDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject*)
{
    if (object != NULL) {
        CDungeonObject* dungeonObject = dynamic_cast<CDungeonObject*>(object);
        if (dungeonObject != NULL && event == 0x51) {
            dungeonObject->clearHistory();
            return;
        }
    }
}

CEditorBaseObject* CDungeonObjectDescriptor::CreateObject(CEditorScene* scene)
{
    return new CDungeonObject(scene->getResourceManager());
}
