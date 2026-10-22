#include "EmptyStrings.h"
#include "Randomizer.h"
#include "Utilities.h"

CRandomizer::CRandomizer(ERANDOMIZER_TYPE type)
    : m_Choices(100), m_Odds(100), m_ComputedOdds(100), m_eType(type), m_fDecay(1.0f), m_bOddsDirty(true)
{
}

int CRandomizer::getOdds(int index)
{
    return (int)m_Odds[index];
}

void CRandomizer::setChoiceOdds(int choice, int odds)
{
    for (unsigned int i = 0; i < m_Choices.size(); i++)
    {
        if (m_Choices[i] == choice)
        {
            m_Odds[i] = (float)odds;
            m_bOddsDirty = true;
            return;
        }
    }
}

void CRandomizer::removeChoice(unsigned int choice)
{
    for (unsigned int i = 0; i < m_Choices.size(); i++)
    {
        if (choice == (unsigned int)m_Choices[i])
        {
            m_Odds.removeAt(i);
            m_Choices.removeAt(i);
            m_ComputedOdds.removeAt(i);
            m_bOddsDirty = true;
            return;
        }
    }
}

void CRandomizer::setRandomSeed(unsigned int seed)
{
    UTILITIES::setSeed(seed);
}

void CRandomizer::clear()
{
    m_Odds.clear();
    m_ComputedOdds.clear();
    m_Choices.clear();
    m_bOddsDirty = true;
}

int CRandomizer::addChoice(int choice, int odds)
{
    int index = m_Odds.size();
    m_Odds.add((float)odds);
    m_Choices.add(choice);
    m_bOddsDirty = true;
    return index;
}

void CRandomizer::computeOdds()
{
    float total = 0.0f;
    for (unsigned int i = 0; i < m_Odds.size(); i++)
        total += m_Odds[i];

    m_ComputedOdds.clear();
    for (unsigned int i = 0; i < m_Odds.size(); i++)
        m_ComputedOdds.add(m_Odds[i] / total);
    m_bOddsDirty = false;
}

void CRandomizer::setRandomizerToNormal(float odds)
{
    if (odds > 0.0f)
    {
        for (unsigned int i = 0; i < m_Odds.size(); i++)
            m_Odds[i] = odds;
    }
    m_eType = RANDOMIZER_NORMAL;
    m_bOddsDirty = true;
    computeOdds();
}

int CRandomizer::getRandom(int& index)
{
    if (m_bOddsDirty)
        computeOdds();

    float roll = UTILITIES::randomBetween(0.0f, 1.0f);
    unsigned int i = 0;
    float sum = 0.0f;
    for (; i < m_ComputedOdds.size(); i++)
    {
        sum += m_ComputedOdds[i];
        if (roll < sum)
        {
            switch (m_eType)
            {
            case RANDOMIZER_DECAY:
                m_Odds[i] *= m_fDecay;
                m_bOddsDirty = true;
                break;
            default:
                break;
            }
            index = i;
            return m_Choices[i];
        }
    }

    // The original still decays slot zero when no choice is selected.
    switch (m_eType)
    {
    case RANDOMIZER_DECAY:
        m_Odds[-1] *= m_fDecay;
        m_bOddsDirty = true;
        break;
    default:
        break;
    }
    index = -1;
    return 0;
}

int CRandomizer::getRandom()
{
    if (m_bOddsDirty)
        computeOdds();

    float roll = UTILITIES::randomBetween(0.0f, 1.0f);
    float sum = 0.0f;
    unsigned int i = 0;
    for (; i < m_ComputedOdds.size(); i++)
    {
        sum += m_ComputedOdds[i];
        if (roll < sum)
        {
            switch (m_eType)
            {
            case RANDOMIZER_DECAY:
                m_Odds[i] *= m_fDecay;
                m_bOddsDirty = true;
                break;
            default:
                break;
            }
            return m_Choices[i];
        }
    }

    // The original still decays slot zero when no choice is selected.
    switch (m_eType)
    {
    case RANDOMIZER_DECAY:
        m_Odds[0] *= m_fDecay;
        m_bOddsDirty = true;
        break;
    default:
        break;
    }
    return 0;
}

bool CRandomizer::hasValidChoices()
{
    if (m_bOddsDirty)
        computeOdds();

    for (unsigned int i = 0; i < m_ComputedOdds.size(); i++)
    {
        if (m_ComputedOdds[i] > 0.0f)
            return true;
    }
    return false;
}
