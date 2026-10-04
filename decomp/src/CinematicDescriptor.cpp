#include "EmptyStrings.h"
#include "CinematicDescriptor.h"

CCinematicDescriptor::CCinematicDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddPropertyWithInterpreterFunctions(L"CINEMATIC", L"CINEMATIC", L"Cinematic Name", (void*)Set_setCinematicName, (void*)Get_getCinematicName, getCinematicIDByString, getCinematicStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddOutputLogic(OUTPUT_EVENT_INTERACTED);
    AddInputLogic(INPUT_EVENT_PLAY);
}

CCinematicDescriptor::~CCinematicDescriptor()
{
}
