#include "EmptyStrings.h"
#include "OutputIncrementorDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "OutputIncrementor.h"

COutputIncrementorDescriptor::COutputIncrementorDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the timer enabled or disabled by default.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"INCREMENTOR", L"MAX OUTPUT", L"The max output before output incrementor loops.", (void*)Set_setMaxIncrement, (void*)Get_getMaxIncrement, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"INCREMENTOR", L"LOOP COUNT", L"The number of loops you the timer to do.", (void*)Set_setLoopCount, (void*)Get_getLoopCount, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"INCREMENTOR", L"LOOPS FOREVER", L"Loops forever.", (void*)Set_setLoopForever, (void*)Get_getLoopForever, VARIABLE_TYPE_BOOL, 0);
    AddInputLogic(INPUT_EVENT_INCREMENT);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddOutputLogic(OUTPUT_EVENT_INCREMENTED);
    AddOutputLogic(OUTPUT_EVENT_FIRST_INCREMENT);
    AddOutputLogic(OUTPUT_EVENT_SECOND_INCREMENT);
    AddOutputLogic(OUTPUT_EVENT_THIRD_INCREMENT);
    AddOutputLogic(OUTPUT_EVENT_FOURTH_INCREMENT);
    AddOutputLogic(OUTPUT_EVENT_FIFTH_INCREMENT);
    AddOutputLogic(OUTPUT_EVENT_INCREMENT_GREATER_THEN_FIVE);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
}

COutputIncrementorDescriptor::~COutputIncrementorDescriptor()
{
}

void COutputIncrementorDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int eventType, CEditorBaseObject*)
{
    COutputIncrementor* incrementor = dynamic_cast<COutputIncrementor*>(object);
    if (incrementor != NULL)
    {
        switch (eventType)
        {
        case 3:
            incrementor->setEnabled(false);
            break;
        case 14:
            incrementor->increment();
            break;
        case 2:
            incrementor->setEnabled(true);
            break;
        }
    }
}
