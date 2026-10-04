#include "EmptyStrings.h"
#include "RandomChoiceDescriptor.h"

CRandomChoiceDescriptor::CRandomChoiceDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the random choice enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"TYPE", L"The type of random choice. Random will use the value between 0-100. Weight uses the value as a weight against all.", (void*)Set_setRandomType, (void*)Get_getRandomType, GetChoiceTypeIDByString, GetChoiceTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"WEIGHTED", L"COUNT", L"The number of objects to choose when using the weighted type.", (void*)Set_setCount, (void*)Get_getCount, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddProperty(L"CHOICES", L"ONE", L"Negative or Zero disable the choice.", (void*)Set_setRandomValue0, (void*)Get_getRandomValue0, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"CHOICES", L"TWO", L"Negative or Zero disable the choice.", (void*)Set_setRandomValue1, (void*)Get_getRandomValue1, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"CHOICES", L"THREE", L"Negative or Zero disable the choice.", (void*)Set_setRandomValue2, (void*)Get_getRandomValue2, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"CHOICES", L"FOUR", L"Negative or Zero disable the choice.", (void*)Set_setRandomValue3, (void*)Get_getRandomValue3, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"CHOICES", L"FIVE", L"Negative or Zero disable the choice.", (void*)Set_setRandomValue4, (void*)Get_getRandomValue4, VARIABLE_TYPE_INTEGER, 0);
    AddInputLogic(INPUT_EVENT_ROLL);
    AddOutputLogic(OUTPUT_EVENT_ONE);
    AddOutputLogic(OUTPUT_EVENT_TWO);
    AddOutputLogic(OUTPUT_EVENT_THREE);
    AddOutputLogic(OUTPUT_EVENT_FOUR);
    AddOutputLogic(OUTPUT_EVENT_FIVE);
}

CRandomChoiceDescriptor::~CRandomChoiceDescriptor()
{
}
