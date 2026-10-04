#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Achievement.h"
#include "Achievements.h"
#include "SteamStats.h"

void CAchievement::setValue(float value)
{
    if (m_eStatType < 31 && m_eStatType != 30)
    {
        CSteamStats::getSingleton()->setStatInt(m_eStatType, value);
        checkForAchieved();
    }
}

void CAchievement::setValue(int value)
{
    if (m_eStatType <= 30 && m_eStatType != 30) {
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
            int currentValue = *(int *)((char *)this + 0x2c);
            if (currentValue > 1 &&
                CSteamStats::getSingleton()->getStatInt(m_eStatType) < currentValue)
            {
                setValue(currentValue - 1);
            }
        }
        else if (*(int *)(g_strStatDefines + m_eStatType * 24 + 4) == 1 &&
                 *(float *)((char *)this + 0x2c) > 1.0f)
        {
            typedef float (*GetStatFloat)(CSteamStats *, ESTATS);
            float statValue = reinterpret_cast<GetStatFloat>(&CSteamStats::getStatFloat)(
                CSteamStats::getSingleton(), m_eStatType);
            if (statValue < *(float *)((char *)this + 0x2c))
            {
                setValue(*(float *)((char *)this + 0x2c) - 1.0f);
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
                    (int)m_fRequiredValue) {
                    setValue((int)m_fRequiredValue);
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
    if (m_eStatType < 31 && m_eStatType != 30) {
        float fCurrentValue =
            CSteamStats::getSingleton()->getStatFloat(m_eStatType);

        CSteamStats::getSingleton()->setStatInt(
            m_eStatType,
            static_cast<unsigned int>(fCurrentValue + fValue));

        checkForAchieved();
    }
}

void CAchievement::addValue(int value)
{
    if ((int)m_eStatType < 30 && m_eStatType != 30) {
        CSteamStats::getSingleton()->setStatInt(
            m_eStatType,
            CSteamStats::getSingleton()->getStatInt(m_eStatType) + value
        );
        checkForAchieved();
    }
}

void CAchievement::increment()
{
    if (m_eStatType > 30 || m_eStatType == 30)
        return;

    CSteamStats::getSingleton()->incrementStat(m_eStatType, 1);
    checkForAchieved();
}

CAchievement::~CAchievement()
{
}
