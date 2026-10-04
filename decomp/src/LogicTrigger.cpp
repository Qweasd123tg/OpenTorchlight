#include "EmptyStrings.h"
#include "LogicTrigger.h"
#include "OutputEvents.h"

CLogicTrigger::CLogicTrigger(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, NULL), m_bActive(false),
      m_bHasActivated(false), m_bHasDeactivated(false), m_bTriggerEnabled(true)
{
    setVisible(true);
}

CLogicTrigger::~CLogicTrigger()
{
}

void CLogicTrigger::TriggerReset()
{
    m_bActive = false;
    m_bHasActivated = false;
    m_bHasDeactivated = false;
    BroadcastEvent(OUTPUT_EVENT_RESET);
}

void CLogicTrigger::TriggerActivated(CEditorBaseObject*)
{
    if (!m_bActive)
    {
        m_bActive = true;
        if (m_bVisible)
        {
            if (!m_bHasActivated)
            {
                BroadcastEvent(OUTPUT_EVENT_TRIGGERED_FIRST_TIME);
                m_bHasActivated = true;
            }
            BroadcastEvent(OUTPUT_EVENT_TRIGGERED);
        }
    }
}

void CLogicTrigger::TriggerDeactivated(CEditorBaseObject*)
{
    if (m_bActive)
    {
        m_bActive = false;
        if (m_bVisible)
        {
            if (!m_bHasDeactivated)
            {
                BroadcastEvent(OUTPUT_EVENT_DEACTIVATED_FIRST_TIME);
                m_bHasDeactivated = true;
            }
            BroadcastEvent(OUTPUT_EVENT_DEACTIVATED);
        }
    }
}

bool CLogicTrigger::canUpdate()
{
    return m_bTriggerEnabled;
}
