#include "EmptyStrings.h"
#include "Counter.h"
#include "OutputEvents.h"

CCounter::CCounter()
    : m_iTarget(10), m_iStartValue(0), m_iValue(0), m_eType(COUNTER_ACTIVATE_ONCE), m_bEnabled(true)
{
}

CCounter::~CCounter()
{
}

void CCounter::reset()
{
    m_iValue = m_iStartValue;
    m_bEnabled = true;
}

void CCounter::updateCounter()
{
    if (!m_bEnabled)
        return;

    switch (m_eType)
    {
    case COUNTER_ACTIVATE_ONCE:
        if (m_iValue == m_iTarget)
        {
            BroadcastEvent(OUTPUT_EVENT_ACTIVATED);
            m_bEnabled = false;
        }
        break;
    case COUNTER_ACTIVATE_AND_RESET:
        if (m_iValue == m_iTarget)
        {
            BroadcastEvent(OUTPUT_EVENT_ACTIVATED);
            m_iValue = m_iStartValue;
        }
        break;
    case COUNTER_ACTIVATE_ON_EACH_ADD:
    case COUNTER_ACTIVATE_ON_EACH_SUBTRACT:
        if (m_iValue == m_iTarget)
            m_bEnabled = false;
        break;
    case COUNTER_ACTIVATE_ON_EACH_ADD_AND_RESET:
    case COUNTER_ACTIVATE_ON_EACH_SUBTRACT_AND_RESET:
        if (m_iValue == m_iTarget)
            m_iValue = m_iStartValue;
        break;
    default:
        break;
    }
}

void CCounter::subtract(int amount)
{
    if (!m_bEnabled)
        return;

    m_iValue -= amount;
    switch (m_eType)
    {
    case COUNTER_ACTIVATE_ON_EACH_SUBTRACT:
    case COUNTER_ACTIVATE_ON_EACH_SUBTRACT_AND_RESET:
        BroadcastEvent(OUTPUT_EVENT_ACTIVATED);
        break;
    default:
        break;
    }
    updateCounter();
}

void CCounter::add(int amount)
{
    if (!m_bEnabled)
        return;

    m_iValue += amount;
    switch (m_eType)
    {
    case COUNTER_ACTIVATE_ON_EACH_ADD:
    case COUNTER_ACTIVATE_ON_EACH_ADD_AND_RESET:
        BroadcastEvent(OUTPUT_EVENT_ACTIVATED);
        break;
    default:
        break;
    }
    updateCounter();
}
