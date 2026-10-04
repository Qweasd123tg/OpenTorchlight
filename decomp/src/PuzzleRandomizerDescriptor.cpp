#include "EmptyStrings.h"
#include "PuzzleRandomizerDescriptor.h"

CPuzzleRandomizerDescriptor::CPuzzleRandomizerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the puzzle input enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"NUMBER OF INPUTS", L"This is how many active inputs you want to use.", (void*)Set_setActiveInputs, (void*)Get_getActiveInputs, VARIABLE_TYPE_INTEGER, 0);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddInputLogic(INPUT_EVENT_RESET);
    AddInputLogic(INPUT_EVENT_INPUT_1);
    AddInputLogic(INPUT_EVENT_INPUT_2);
    AddInputLogic(INPUT_EVENT_INPUT_3);
    AddInputLogic(INPUT_EVENT_INPUT_4);
    AddInputLogic(INPUT_EVENT_INPUT_5);
    AddInputLogic(INPUT_EVENT_INPUT_6);
    AddOutputLogic(OUTPUT_EVENT_RESET);
    AddOutputLogic(OUTPUT_EVENT_SUCCESS);
    AddOutputLogic(OUTPUT_EVENT_FAILED);
}

CPuzzleRandomizerDescriptor::~CPuzzleRandomizerDescriptor()
{
}
