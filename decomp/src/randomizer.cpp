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
        if (m_Choices[i] == (int)choice)
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
    float sum = 0.0f;
    int picked = -1;
    for (unsigned int i = 0; i < m_ComputedOdds.size(); i++)
    {
        sum += m_ComputedOdds[i];
        if (sum > roll)
        {
            picked = i;
            break;
        }
    }

    if (m_eType == RANDOMIZER_DECAY)
    {
        m_Odds[picked] *= m_fDecay;
        m_bOddsDirty = true;
    }
    index = picked;
    if (picked == -1)
        return 0;
    return m_Choices[picked];
}

int CRandomizer::getRandom()
{
    if (m_bOddsDirty)
        computeOdds();

    float roll = UTILITIES::randomBetween(0.0f, 1.0f);
    float sum = 0.0f;
    int picked = -1;
    for (unsigned int i = 0; i < m_ComputedOdds.size(); i++)
    {
        sum += m_ComputedOdds[i];
        if (sum > roll)
        {
            picked = i;
            break;
        }
    }

    if (m_eType == RANDOMIZER_DECAY)
    {
        m_Odds[picked] *= m_fDecay;
        m_bOddsDirty = true;
    }
    if (picked == -1)
        return 0;
    return m_Choices[picked];
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
