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

#include "GameClient.h"
#include "GameUI.h"
#include "Monster.h"
#include "Player.h"
#include "Inventory.h"
#include "Level.h"
#include "SpawnClass.h"
#include "SoundBank.h"
#include "Graph.h"
#include "Utilities.h"

CQuestRewards::CQuestRewards(CQuest* quest)
    : m_pQuest(quest), m_fExperience(0), m_fGold(0), m_fFame(0),
      m_pSpawnClass(NULL), m_unitRewardReferences(1),
      m_fExperienceMinPercent(0), m_fExperienceMaxPercent(0),
      m_fGoldMinPercent(0), m_fGoldMaxPercent(0),
      m_fFameMinPercent(0), m_fFameMaxPercent(0), m_rewardItems(1)
{
}

CQuestRewards::~CQuestRewards()
{
    m_rewardItems.deleteAll();
    m_unitRewardReferences.deleteAll();
}

void CQuestRewards::reInitializeRewards()
{
    m_rewardItems.deleteAll();
    calculateRewards();
}

void CQuestRewards::calculateRewards()
{
    CResourceManager* resources = m_pQuest->m_pResourceManager;
    if (resources->getEditorIsRunning() || resources->getGameClients()->size() == 0 ||
        (*resources->getGameClients())[0] == NULL || m_pQuest->getPlayer() == NULL ||
        m_rewardItems.size() != 0)
        return;
    if (m_fGoldMinPercent <= 0 && m_fGoldMaxPercent <= 0 &&
        m_fFameMinPercent <= 0 && m_fFameMaxPercent <= 0 &&
        m_unitRewardReferences.size() == 0 && m_pSpawnClass == NULL)
        return;

    m_rewardItems.clear();
    resources = m_pQuest->m_pResourceManager;
    UTILITIES::setSeed(m_pQuest->m_iUnknown1C + 10027);
    float goldPercent = UTILITIES::randomBetween(m_fGoldMinPercent, m_fGoldMaxPercent);
    float famePercent = UTILITIES::randomBetween(m_fFameMinPercent, m_fFameMaxPercent);
    int level = m_pQuest->m_iUnknown20C;
    int difficulty = (*resources->getGameClients())[0]->m_startDifficulty;
    float graphLevel = static_cast<float>(level + 1);
    const wchar_t* goldGraph = NULL;
    const wchar_t* fameGraph = NULL;
    switch (difficulty) {
    case 0: goldGraph=L"GOLDDROP_EASY"; fameGraph=L"FAME_CHAMPIONMONSTER_EASY"; break;
    case 1: goldGraph=L"GOLDDROP"; fameGraph=L"FAME_CHAMPIONMONSTER"; break;
    case 2: goldGraph=L"GOLDDROP_HARD"; fameGraph=L"FAME_CHAMPIONMONSTER_HARD"; break;
    case 3: goldGraph=L"GOLDDROP_VERYHARD"; fameGraph=L"FAME_CHAMPIONMONSTER_VERYHARD"; break;
    }
    if (goldGraph != NULL) {
        m_fGold = ceilf(resources->getGraph(goldGraph)->getValue(graphLevel, 0) * (goldPercent / 100.0f));
        m_fFame = ceilf(resources->getGraph(fameGraph)->getValue(graphLevel, 0) * (famePercent / 100.0f));
    }
    float experiencePercent = UTILITIES::randomBetween(m_fExperienceMinPercent, m_fExperienceMaxPercent);
    m_fExperience = ceilf(resources->getGraph(L"EXPERIENCE_MONSTER")->getValue(graphLevel, 0) * (experiencePercent / 100.0f));
    for (unsigned i=0; i<m_unitRewardReferences.size(); ++i) {
        CBaseUnit* unit = m_pQuest->m_pResourceManager->createUnit(m_unitRewardReferences[i]->m_pDataGroup, 0, false, false);
        if (unit != NULL) {
            if (m_unitRewardReferences[i]->m_bIdentify) {
                CEquipment* equipment = dynamic_cast<CEquipment*>(unit);
                if (equipment != NULL) {
                    equipment->m_bUnknown348 = true;
                    equipment->destroyItemText();
                }
            }
            m_rewardItems.add(unit);
        }
    }
    if (m_pSpawnClass != NULL) {
        UTILITIES::setSeed(m_pQuest->m_iUnknown1C);
        TArrayList<CDataGroup*> groups(5);
        TArrayList<bool> enchanted(5);
        int seed = m_pQuest->m_iUnknown1C + 10027;
        int itemLevel = UTILITIES::randomIntegerBetween(-1, 2) + level;
        CPlayer* secondPlayer = m_pQuest->getPlayer();
        CPlayer* firstPlayer = m_pQuest->getPlayer();
        m_pSpawnClass->rollSpawnClass(groups, &enchanted, firstPlayer, secondPlayer, itemLevel, seed, 0, -1, 0, 0);
        for (unsigned i=0; i<groups.size(); ++i) {
            CBaseUnit* unit = m_pQuest->m_pResourceManager->createUnit(groups[i], 0, false, false);
            if (unit != NULL) {
                CEquipment* equipment = dynamic_cast<CEquipment*>(unit);
                if (enchanted[i]) equipment->enchant(true);
                if (equipment != NULL) {
                    equipment->m_bUnknown348 = true;
                    equipment->destroyItemText();
                }
                m_rewardItems.add(unit);
            }
        }
    }
    for (unsigned i=0; i<m_rewardItems.size(); ++i) {
        CLevel* level = m_pQuest->m_pResourceManager->getLevel();
        if (level != NULL) {
            level->removeUnit(m_rewardItems[i], true);
            m_rewardItems[i]->setVisible(false);
        }
    }
}

void CQuestRewards::rewardPlayer()
{
    if (m_pQuest == NULL || m_pQuest->getPlayer() == NULL ||
        m_pQuest->m_pResourceManager == NULL || m_pQuest->m_pResourceManager->getLevel() == NULL)
        return;
    if (m_fGold > 0) CGameUI::getSingleton()->m_soundBank->playSample(23, NULL, 0, 0, false);
    m_pQuest->getPlayer()->giveGold(static_cast<int>(ceilf(m_fGold)));
    if (m_fExperience > 0 && m_fGold == 0) CGameUI::getSingleton()->m_soundBank->playSample(36, NULL, 0, 0, false);
    int experience = static_cast<int>(ceilf(m_fExperience));
    CLevel* level = m_pQuest->m_pResourceManager->getLevel();
    m_pQuest->getPlayer()->awardExperience(*level, NULL, experience, false);
    int fame = static_cast<int>(ceilf(m_fFame));
    level = m_pQuest->m_pResourceManager->getLevel();
    m_pQuest->getPlayer()->awardFame(*level, NULL, fame, false);
    if (m_pQuest == NULL || m_pQuest->m_pResourceManager == NULL ||
        m_pQuest->m_pResourceManager->getLevel() == NULL)
        return;
    for (unsigned i=0; i<m_rewardItems.size(); ++i) {
        if (m_rewardItems[i] != NULL) {
            m_rewardItems[i]->setVisible(true);
            CEquipment* equipment = dynamic_cast<CEquipment*>(m_rewardItems[i]);
            CMonster* monster = dynamic_cast<CMonster*>(m_rewardItems[i]);
            if (monster == NULL && equipment != NULL &&
                m_pQuest->getPlayer()->getInventory()->canPickup(equipment, false)) {
                m_pQuest->getPlayer()->getInventory()->pickupEquipment(equipment, true);
                continue;
            }
            Ogre::Vector3 position = m_pQuest->getPlayer()->getPosition(false);
            m_pQuest->m_pResourceManager->getLevel()->addUnit(m_rewardItems[i], position);
            if (monster != NULL) m_pQuest->getPlayer()->addPet(monster);
        }
    }
    m_rewardItems.clear();
}
