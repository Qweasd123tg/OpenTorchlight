#include "EmptyStrings.h"
#include "CounterDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Counter.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"

CCounterDescriptor::CCounterDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the counter enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"EQUALS VALUE", L"When the internal counter adds or subtracts an event will be broadcasted when it reaches this value.", (void*)Set_setCount, (void*)Get_getCount, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"PROPERTIES", L"STARTING VALUE", L"The starting value of the counter.", (void*)Set_setStartingValue, (void*)Get_getStartingValue, VARIABLE_TYPE_INTEGER, 0);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"LOGIC", L"This is the logic that will occure when the counter reaches the equal value.", (void*)Set_setLogicType, (void*)Get_getLogicType, GetCounterTypeIDByString, GetCounterTypeTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddInputLogic(INPUT_EVENT_ADD);
    AddInputLogic(INPUT_EVENT_SUBTRACT);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddInputLogic(INPUT_EVENT_RESET);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddOutputLogic(OUTPUT_EVENT_RESET);
    AddOutputLogic(OUTPUT_EVENT_ACTIVATED);
}

CCounterDescriptor::~CCounterDescriptor()
{
}

unsigned int CCounterDescriptor::GetCounterTypeIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring& value, void*)
{
    for (unsigned int index = 0; index < 6; ++index)
    {
        if (value == ::gCOUNTER_TYPE_NAMES[index])
            return index;
    }

    return 0;
}

CEditorBaseObject* CCounterDescriptor::CreateObject(CEditorScene*)
{
    return new CCounter();
}
