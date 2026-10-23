#include "Achievements.h"
#include "Achievement.h"

CAchievements* m_gAchievementsObject = NULL;

CAchievements::~CAchievements()
{
    m_achievements.deleteAll();
    m_gAchievementsObject = NULL;
}

CAchievements* CAchievements::getSingleton()
{
    return m_gAchievementsObject;
}

CAchievement* CAchievements::getAchievement(EACHIEVEMENTS achievement)
{
    std::map<EACHIEVEMENTS, CAchievement*>::iterator found = m_achievementsById.find(achievement);
    if (found == m_achievementsById.end())
        return NULL;
    return found->second;
}

void CAchievements::synchAchievementsComplete()
{
    m_bUnknown10 = true;
}

void CAchievements::update(float)
{
    m_completedAchievements.clear();
}

template TArrayList<CAchievement*>::~TArrayList();

CAchievement* CAchievements::getAchievement(std::string name)
{
    for (unsigned int i = 0; i < m_achievements.size(); ++i)
        if (std::string(m_achievements[i]->m_strName) == name)
            return m_achievements[i];
    return NULL;
}

#include "Achievement.h"
#include "StringUtilities.h"

void CAchievements::cheat()
{
    for (unsigned int i = 0; i < m_achievements.size(); ++i)
        m_achievements[i]->cheat();
}

void CAchievements::setAchievementComplete(CAchievement* achievement)
{
    m_completedAchievements.add(achievement);
}

std::wstring CAchievements::getAchievementStatus()
{
    std::wstring result;
    for (unsigned int i = 0; i < m_achievements.size(); ++i)
    {
        const wchar_t* status = m_achievements[i]->m_bAchieved ? L"(COMPLETE)" : L"(NOT COMPLETE)";
        std::wstring progress = m_achievements[i]->getStatCompleteString();
        result = result + STRINGS::StringConvertToWide(std::string(m_achievements[i]->m_strName)) + L": " + progress + L"\t\t" + status + L"\n";
    }
    return result;
}
