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
            dynamic_cast<CEquipment *>(&m_rewardItems[i]);
        if (equipment != NULL)
            equipment->destroyIcon();
    }
}

TArrayList<CBaseUnit> *CQuestRewards::getRewardItems()
{
    calculateRewards();
    return &m_rewardItems;
}
