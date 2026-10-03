#include "EmptyStrings.h"
#include "LogicTimer.h"
#include "Utilities.h"

CLogicTimer::CLogicTimer(CResourceManager* resourceManager)
    : m_fMinTime(1.0f), m_fMaxTime(-1.0f), m_fTimeRemaining(1.0f), m_iRepeatCount(1), m_iRepeatsLeft(1),
      m_bEnabled(true), m_bRepeatForever(false), m_pResourceManager(resourceManager)
{
}

CLogicTimer::~CLogicTimer()
{
}

void CLogicTimer::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    if (m_pResourceManager->getEditorIsRunning())
        return;

    resetTimer();
    if (m_bEnabled)
    {
        BroadcastEvent(OUTPUT_EVENT_ENABLED);
        if (m_iRepeatsLeft <= 0)
            m_iRepeatsLeft = 1;
    }
    else
    {
        BroadcastEvent(OUTPUT_EVENT_DISABLED);
    }
}

void CLogicTimer::update(float elapsed)
{
    if (m_pResourceManager != NULL && !m_pResourceManager->getEditorIsRunning() &&
        (m_bRepeatForever || m_iRepeatsLeft > 0) && m_pResourceManager != NULL && m_bEnabled)
    {
        m_fTimeRemaining -= elapsed;
        if (m_fTimeRemaining <= 0.0f)
        {
            BroadcastEvent(OUTPUT_EVENT_ACTIVATED);
            if (!m_bRepeatForever)
            {
                m_iRepeatsLeft--;
                if (m_iRepeatsLeft <= 0)
                    return;
            }
            resetTimer();
        }
    }
}

void CLogicTimer::resetTimer()
{
    if (m_fMaxTime > m_fMinTime)
        m_fTimeRemaining = UTILITIES::randomBetweenVolatile(m_fMinTime, m_fMaxTime);
    else
        m_fTimeRemaining = m_fMinTime;
}
