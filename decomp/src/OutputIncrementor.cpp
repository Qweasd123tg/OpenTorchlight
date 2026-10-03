#include "EmptyStrings.h"
#include "OutputIncrementor.h"

COutputIncrementor::COutputIncrementor(CResourceManager* resourceManager)
    : m_iTarget(5), m_iCount(0), m_iRepeatCount(1), m_iRepeatsLeft(1), m_bEnabled(true), m_bRepeatForever(false),
      m_pResourceManager(resourceManager)
{
}

COutputIncrementor::~COutputIncrementor()
{
}

void COutputIncrementor::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    if (m_pResourceManager->getEditorIsRunning())
        return;

    if (m_bEnabled)
        BroadcastEvent(OUTPUT_EVENT_ENABLED);
    else
        BroadcastEvent(OUTPUT_EVENT_DISABLED);
}

void COutputIncrementor::increment()
{
    if (m_pResourceManager == NULL || m_pResourceManager->getEditorIsRunning())
        return;
    if (!m_bRepeatForever && m_iRepeatsLeft <= 0)
        return;
    if (m_pResourceManager == NULL || !m_bEnabled)
        return;

    BroadcastEvent(OUTPUT_EVENT_INCREMENTED);
    m_iCount++;
    switch (m_iCount)
    {
    case 1:
        BroadcastEvent(OUTPUT_EVENT_FIRST_INCREMENT);
        break;
    case 2:
        BroadcastEvent(OUTPUT_EVENT_SECOND_INCREMENT);
        break;
    case 3:
        BroadcastEvent(OUTPUT_EVENT_THIRD_INCREMENT);
        break;
    case 4:
        BroadcastEvent(OUTPUT_EVENT_FOURTH_INCREMENT);
        break;
    case 5:
        BroadcastEvent(OUTPUT_EVENT_FIFTH_INCREMENT);
        break;
    default:
        BroadcastEvent(OUTPUT_EVENT_INCREMENT_GREATER_THEN_FIVE);
        break;
    }

    if (m_iCount == m_iTarget)
    {
        if (m_bRepeatForever || m_iRepeatsLeft > 0)
        {
            m_iCount = 0;
            m_iRepeatsLeft--;
        }
    }
}
