#include "EmptyStrings.h"
#include "LogicTimerDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "LogicTimer.h"

CLogicTimerDescriptor::CLogicTimerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the timer enabled or disabled by default.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"TIMER", L"TIME", L"When the timer reaches zero an activate message will be broadcasted.", (void*)Set_setTimer, (void*)Get_getTimer, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"TIMER", L"MAXTIME", L"If Max Time is > than Time, Timer duration will be rolled between Time and Max Time", (void*)Set_setMaxTimer, (void*)Get_getMaxTimer, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"TIMER", L"LOOP COUNT", L"The number of loops you the timer to do.", (void*)Set_setLoopCount, (void*)Get_getLoopCount, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"TIMER", L"LOOPS FOREVER", L"Loops forever.", (void*)Set_setLoopForever, (void*)Get_getLoopForever, VARIABLE_TYPE_BOOL, 0);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddInputLogic(INPUT_EVENT_RESET);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddOutputLogic(OUTPUT_EVENT_ACTIVATED);
}

CLogicTimerDescriptor::~CLogicTimerDescriptor()
{
}

void CLogicTimerDescriptor::update(float delta)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i)
    {
        CEditorBaseObject* object = m_Objects[i];
        if (object != NULL)
        {
            CLogicTimer* timer = dynamic_cast<CLogicTimer*>(object);
            if (timer != NULL)
            {
                timer->update(delta);
            }
        }
    }
}

void CLogicTimerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject*)
{
    CLogicTimer* timer = dynamic_cast<CLogicTimer*>(object);
    if (timer != NULL)
    {
        switch (event)
        {
        case 3:
            timer->setEnabled(false);
            break;
        case 6:
            timer->resetTimer();
            timer->setEnabled(true);
            break;
        case 2:
            timer->setEnabled(true);
            break;
        }
    }
}

CEditorBaseObject* CLogicTimerDescriptor::CreateObject(CEditorScene* scene)
{
    return new CLogicTimer(scene->getResourceManager());
}
