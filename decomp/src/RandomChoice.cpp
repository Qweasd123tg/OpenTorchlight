#include "EmptyStrings.h"
#include "RandomChoice.h"
#include "Randomizer.h"
#include "Utilities.h"

CRandomChoice::CRandomChoice()
    : m_eRandomType(RANDOMCHOICE_WEIGHT), m_bEnabled(true), m_iCount(1)
{
    for (int i = 0; i < OUTPUT_COUNT; i++)
        m_iRandomValues[i] = 0;
    m_iOutputs[0] = OUTPUT_EVENT_ONE;
    m_iOutputs[1] = OUTPUT_EVENT_TWO;
    m_iOutputs[2] = OUTPUT_EVENT_THREE;
    m_iOutputs[3] = OUTPUT_EVENT_FOUR;
    m_iOutputs[4] = OUTPUT_EVENT_FIVE;
}

CRandomChoice::~CRandomChoice()
{
}

void CRandomChoice::roll()
{
    if (!m_bEnabled)
        return;

    if (m_eRandomType == RANDOMCHOICE_RANDOM)
    {
        for (int i = 0; i < OUTPUT_COUNT; i++)
        {
            if (m_iRandomValues[i] > 0 && UTILITIES::randomIntegerBetweenVolatile(1, 100) <= m_iRandomValues[i])
                BroadcastEvent(m_iOutputs[i]);
        }
        return;
    }

    CRandomizer randomizer(RANDOMIZER_NORMAL);
    for (int i = 0; i < OUTPUT_COUNT; i++)
    {
        if (m_iRandomValues[i] > 0)
            randomizer.addChoice(i, m_iRandomValues[i]);
    }
    for (unsigned int i = 0; i < m_iCount; i++)
    {
        if (randomizer.hasChoices())
        {
            int choice = randomizer.getRandom();
            BroadcastEvent(m_iOutputs[choice]);
        }
    }
}
