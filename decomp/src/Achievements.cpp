#include "Achievements.h"
#include "Achievement.h"

CAchievements* m_gAchievementsObject = NULL;

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
