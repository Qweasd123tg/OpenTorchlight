#include <math.h>
#include "StringUtilities.h"
#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "QuestRewards.h"
#include "BaseUnit.h"
#include "Equipment.h"
#include "TArrayList.h"

void CQuestRewards::destroyIcons()
{
    for (unsigned int i = 0; i < m_rewardItems.size(); ++i)
    {
        CEquipment *equipment =
            dynamic_cast<CEquipment *>(m_rewardItems[i]);
        if (equipment != NULL)
            equipment->destroyIcon();
    }
}

TArrayList<CBaseUnit*> *CQuestRewards::getRewardItems()
{
    calculateRewards();
    return &m_rewardItems;
}

std::wstring CQuestRewards::getRewardString()
{
    calculateRewards();
    if (m_fGold <= 0.0f && m_fExperience <= 0.0f)
        return L"Reward:\n    None";

    std::wstring result = L"Reward(s):\n";
    if (m_fGold > 0.0f)
        result += L"    GOLD: " + STRINGS::GetValueAsWString(
            static_cast<int>(ceilf(m_fGold))) + L"\n";
    if (m_fExperience > 0.0f)
        result += L"     XP: " + STRINGS::GetValueAsWString(
            static_cast<int>(ceilf(m_fExperience))) + L"\n";
    if (m_fFame > 0.0f)
        result += L"     FAME: " + STRINGS::GetValueAsWString(
            static_cast<int>(ceilf(m_fFame))) + L"\n";
    return result;
}
