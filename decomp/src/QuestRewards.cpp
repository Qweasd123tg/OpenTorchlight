#include "Quest.h"
#include "ResourceManager.h"
#include "SpawnClassParser.h"
#include "UnitResourceList.h"
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

long long CQuestRewards::parseRewardTag(CDataGroup *pDataGroup)
{
    if (pDataGroup == NULL)
        return 0;

    m_rewardItems.deleteAll();
    m_unitRewardReferences.deleteAll();
    m_fGoldMinPercent = pDataGroup->GetDataValue(L"GOLDMINPCT", 0);
    m_fGoldMaxPercent = pDataGroup->GetDataValue(L"GOLDMAXPCT", 0);
    m_fExperienceMinPercent = pDataGroup->GetDataValue(L"XPMINPCT", 500);
    m_fExperienceMaxPercent = pDataGroup->GetDataValue(L"XPMAXPCT", 800);
    m_fFameMinPercent = pDataGroup->GetDataValue(L"FAMEMINPCT", 0);
    m_fFameMaxPercent = pDataGroup->GetDataValue(L"FAMEMAXPCT", 0);

    std::wstring treasureClass = pDataGroup->GetDataValue(
        L"TREASURECLASS", EMPTY_WSTRING);
    m_pSpawnClass = CSpawnClassParser::getSingleton()->getSpawnClass(treasureClass);

    std::vector<CDataGroup*> rewards;
    pDataGroup->GetDataGroupsMatchingName(L"UNITREWARD", &rewards);
    const std::wstring *resourceGroups =
        reinterpret_cast<const std::wstring*>(gRESOURCE_GROUP_NAMES);
    for (unsigned int i = 0; i < rewards.size(); ++i)
    {
        std::wstring unitName = rewards[i]->GetDataValue(L"UNITNAME", EMPTY_WSTRING);
        for (unsigned int attempt = 0; attempt < 4; ++attempt)
        {
            CDataGroup *unit;
            {
                // The original retries the outer-index category, not attempt.
                std::wstring resourceGroup(resourceGroups[i].c_str());
                unit = m_pQuest->m_pResourceManager->getMasterResourceList()
                    ->getDataGroupByObjectName(resourceGroup, unitName);
            }
            if (unit != NULL)
            {
                CUnitCreateRef *reference = new CUnitCreateRef;
                reference->m_pDataGroup = unit;
                reference->m_bIdentify = rewards[i]->GetDataValue(L"IDENTIFY", true);
                m_unitRewardReferences.add(reference);
                break;
            }
        }
    }
    return 1;
}
