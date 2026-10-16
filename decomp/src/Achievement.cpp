#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Achievement.h"
#include "Achievements.h"
#include "SteamStats.h"

void CAchievement::setValue(float value)
{
    if ((int)m_eStatType < 30)
    {
        CSteamStats::getSingleton()->setStatInt(m_eStatType, value);
        checkForAchieved();
    }
}

void CAchievement::setValue(int value)
{
    if ((int)m_eStatType < 30) {
        CSteamStats::getSingleton()->setStatInt(
            m_eStatType, static_cast<unsigned int>(value));
        checkForAchieved();
    }
}

void CAchievement::cheat()
{
    if (m_eStatType != 30)
    {
        if (*(int *)(g_strStatDefines + m_eStatType * 24 + 4) == 0)
        {
            if (*reinterpret_cast<const int*>(&m_fRequiredValue) > 1 &&
                CSteamStats::getSingleton()->getStatInt(m_eStatType) <
                    *reinterpret_cast<const int*>(&m_fRequiredValue))
            {
                setValue(*reinterpret_cast<const int*>(&m_fRequiredValue) - 1);
            }
        }
        else if (*(int *)(g_strStatDefines + m_eStatType * 24 + 4) == 1 &&
                 m_fRequiredValue > 1.0f)
        {
            float statValue = CSteamStats::getSingleton()->getStatFloat(m_eStatType);
            if (statValue < m_fRequiredValue)
            {
                setValue(m_fRequiredValue - 1.0f);
            }
        }
    }
}

void CAchievement::forceComplete()
{
    if (!m_bAchieved) {
        if (m_eStatType != 30) {
            int statValueType =
                reinterpret_cast<int *>(g_strStatDefines)[m_eStatType * 6 + 1];

            if (statValueType == 0) {
                if (CSteamStats::getSingleton()->getStatInt(m_eStatType) <
                    *reinterpret_cast<const int*>(&m_fRequiredValue)) {
                    setValue(*reinterpret_cast<const int*>(&m_fRequiredValue));
                }
            } else if (statValueType == 1) {
                if (CSteamStats::getSingleton()->getStatFloat(m_eStatType) <
                    m_fRequiredValue) {
                    setValue(m_fRequiredValue);
                }
            }
        }

        CAchievements::getSingleton()->setAchievementComplete(this);
        m_bAchieved = true;
    }
}

void CAchievement::addValue(float fValue)
{
    if ((int)m_eStatType < 30) {
        float fCurrentValue =
            CSteamStats::getSingleton()->getStatFloat(m_eStatType);

        CSteamStats::getSingleton()->setStatInt(
            m_eStatType,
            static_cast<unsigned int>(fValue + fCurrentValue));

        checkForAchieved();
    }
}

void CAchievement::addValue(int value)
{
    if ((int)m_eStatType < 30) {
        int currentValue = CSteamStats::getSingleton()->getStatInt(m_eStatType);
        CSteamStats::getSingleton()->setStatInt(m_eStatType, currentValue + value);
        checkForAchieved();
    }
}

void CAchievement::increment()
{
    if ((int)m_eStatType >= 30)
        return;

    CSteamStats::getSingleton()->incrementStat(m_eStatType, 1);
    checkForAchieved();
}

CAchievement::~CAchievement()
{
}

ESTATS CAchievement::getStatType()
{
    if (static_cast<int>(m_eStatType) > 30)
        return static_cast<ESTATS>(0);
    return static_cast<ESTATS>(
        *reinterpret_cast<const int*>(g_strStatDefines + static_cast<long>(static_cast<int>(m_eStatType)) * 24 + 4));
}

void CAchievement::checkForAchieved()
{
    if (m_bAchieved)
        return;
    ESTATS stat = m_eStatType;
    if (static_cast<int>(stat) > 30)
        return;
    if (stat == 30)
        m_bAchieved = true;
    else {
        int type = *reinterpret_cast<const int*>(g_strStatDefines + static_cast<long>(static_cast<int>(stat)) * 24 + 4);
        if (type == 0) {
            if (CSteamStats::getSingleton()->getStatInt(stat) >=
                *reinterpret_cast<const int*>(&m_fRequiredValue))
                m_bAchieved = true;
        } else if (type == 1) {
            if (CSteamStats::getSingleton()->getStatFloat(stat) >= m_fRequiredValue)
                m_bAchieved = true;
        } else
            return;
    }
    if (m_bAchieved)
        CAchievements::getSingleton()->setAchievementComplete(this);
}

CAchievement::CAchievement(std::string name, ESTATS statType,
                           float currentValue, float requiredValue)
    : CRunicCore(), iStatListener(), m_strName(name.c_str()),
      m_bAchieved(false), m_eStatType(statType),
      m_fCurrentValue(requiredValue < currentValue ? requiredValue : currentValue),
      m_fRequiredValue(currentValue < requiredValue ? requiredValue : currentValue)
{
    CSteamStats::getSingleton()->addStatListener(statType, this);
}

CAchievement::CAchievement(std::string name, ESTATS statType,
                           int currentValue, int requiredValue)
    : CRunicCore(), iStatListener(), m_strName(name.c_str()),
      m_bAchieved(false), m_eStatType(statType)
{
    *reinterpret_cast<int*>(&m_fCurrentValue) =
        requiredValue < currentValue ? requiredValue : currentValue;
    *reinterpret_cast<int*>(&m_fRequiredValue) =
        currentValue < requiredValue ? requiredValue : currentValue;
    CSteamStats::getSingleton()->addStatListener(statType, this);
}

#include "StringUtilities.h"

std::wstring CAchievement::getStatCompleteString()
{
    if (m_eStatType == static_cast<ESTATS>(30))
        return m_bAchieved ? L"1/1" : L"0/1";
    std::wstring current = STRINGS::GetValueAsWString(CSteamStats::getSingleton()->getStatInt(m_eStatType));
    std::wstring required = STRINGS::GetValueAsWString(*reinterpret_cast<const int*>(&m_fRequiredValue));
    return current + L"/" + required;
}
