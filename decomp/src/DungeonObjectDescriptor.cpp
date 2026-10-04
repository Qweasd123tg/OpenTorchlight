#include "EmptyStrings.h"
#include "DungeonObjectDescriptor.h"

CDungeonObjectDescriptor::CDungeonObjectDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, true, true, true, true)
{
    AddProperty(L"PROPERTIES", L"DUNGEON NAME", L"Dungeon to switch to", (void*)Set_setDungeon, (void*)Get_getDungeon, VARIABLE_TYPE_STRING, 0);
    AddInputLogic(INPUT_EVENT_CLEAR_HISTORY);
}

CDungeonObjectDescriptor::~CDungeonObjectDescriptor()
{
}
