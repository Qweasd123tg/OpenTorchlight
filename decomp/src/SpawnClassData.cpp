#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "SpawnClassData.h"
#include "DataGroup.h"
#include "GraphManager.h"
#include "RunicCore.h"
#include "SpawnClass.h"

void CSpawnClassData::addSpawnClass(CSpawnClass* spawnClass)
{
    if (m_lUnitDataObjects.size() == 0)
    {
        m_pSpawnClass = spawnClass;
        m_iMinimumLevel = -999;
        m_iLevelOffset = -999;
        m_iRarityOverride = -999;
        m_iFlags = -999;
    }
}

void CSpawnClassData::addUnitDataObject(CDataGroup* dataGroup)
{
    if (dataGroup != NULL && m_pSpawnClass == NULL)
    {
        m_iMinimumLevel = -999;
        m_iLevelOffset = -999;
        m_iRarityOverride = -999;
        m_iFlags = -999;
        m_lUnitDataObjects.add(dataGroup);
    }
}

CSpawnClassData::CSpawnClassData(const std::wstring& name)
    : CRunicCore(),
      m_sName(name),
      m_lUnitDataObjects(2),
      m_iMinimumLevel(-999),
      m_iLevelOffset(-999),
      m_iRarityOverride(-999),
      m_iFlags(-999),
      m_pRandomizer(NULL),
      m_pType1Randomizer(NULL),
      m_pType2Randomizer(NULL),
      m_pSpawnClass(NULL),
      m_bIsInitialized(false),
      m_lPrimaryRandomizerIDs(10),
      m_pMinimumLevelGraph(NULL),
      m_pMaximumLevelGraph(NULL)
{
    {
        std::wstring graphName(L"ITEM_SPAWN_RANGE_MINIMUM");
        m_pMinimumLevelGraph = CGraphManager::getSingleton()->getGraph(graphName);
    }
    {
        std::wstring graphName(L"ITEM_SPAWN_RANGE_MAXIMUM");
        m_pMaximumLevelGraph = CGraphManager::getSingleton()->getGraph(graphName);
    }
}

CSpawnClassData::~CSpawnClassData()
{
    if (m_pRandomizer != NULL) {
        delete m_pRandomizer;
        m_pRandomizer = NULL;
    }

    if (m_pType1Randomizer != NULL) {
        delete m_pType1Randomizer;
        m_pType1Randomizer = NULL;
    }

    if (m_pType2Randomizer != NULL) {
        delete m_pType2Randomizer;
        m_pType2Randomizer = NULL;
    }

    m_lUnitDataObjects.clear();
    m_pSpawnClass = NULL;
}

int CSpawnClassData::getUnitObjectCount()
{
    if (m_pRandomizer != NULL)
        return m_pRandomizer->getChoiceCount() +
               m_pType1Randomizer->getChoiceCount() +
               m_pType2Randomizer->getChoiceCount();
    return m_lUnitDataObjects.size();
}


void CSpawnClassData::addUnitDataObjects(TArrayList<CDataGroup*>& groups)
{
    if (m_pSpawnClass == NULL)
    {
        m_iMinimumLevel = -999;
        m_iLevelOffset = -999;
        m_iRarityOverride = -999;
        m_iFlags = -999;
        m_lUnitDataObjects.setGrowBy(groups.size() + 1);
        for (unsigned int i = 0; i < groups.size(); ++i)
            m_lUnitDataObjects.add(groups[i]);
    }
}

unsigned int CSpawnClassData::calculateChoices(CCharacter* character, int minimumLevel,
                                             int levelOffset, int rarityOverride, int flags)
{
    if (m_pSpawnClass)
        return m_pSpawnClass->calculateNumberOfChoices(character, minimumLevel, levelOffset, rarityOverride, flags);
    if (m_lUnitDataObjects.size() == 0)
        return 0;
    if (m_pRandomizer && m_iFlags == flags && m_iMinimumLevel == minimumLevel &&
        m_iLevelOffset == levelOffset && m_iRarityOverride == rarityOverride)
        return m_pRandomizer->getChoiceCount() + m_pType1Randomizer->getChoiceCount() +
               m_pType2Randomizer->getChoiceCount();
    if (m_pRandomizer)
    {
        m_pRandomizer->clear();
        m_pType1Randomizer->clear();
        m_pType2Randomizer->clear();
        m_lPrimaryRandomizerIDs.clear();
    }
    m_iMinimumLevel = minimumLevel;
    m_iLevelOffset = levelOffset;
    m_iRarityOverride = rarityOverride;
    m_iFlags = flags;
    fillRandomizer(character, minimumLevel, levelOffset, rarityOverride, flags);
    if (m_pRandomizer)
        return m_pRandomizer->getChoiceCount() + m_pType1Randomizer->getChoiceCount() +
               m_pType2Randomizer->getChoiceCount();
    return m_lUnitDataObjects.size();
}

#include <cmath>
#include "GameGlobals.h"
#include "Hierarchy.h"
#include "Level.h"
#include "MasterResourceManager.h"
#include "Player.h"
#include "ResourceManager.h"

void CSpawnClassData::fillRandomizer(CCharacter* character, int minimumLevel,
                                    int levelOffset, int rarityOverride, int flags)
{
    int level = minimumLevel > 0 ? minimumLevel : -1;
    int minimumAdjustment = 0;
    int maximumAdjustment = 0;
    bool hardcore = false;
    if (character != NULL && character->getLevel() != NULL)
    {
        CPlayer* player = static_cast<CPlayer*>(character->getLevel()->getPlayer());
        if (player != NULL)
            hardcore = player->m_saveOnDeath;
        if (character->getLevel() != NULL)
        {
            m_iMinimumLevel = -999;
            m_iLevelOffset = -999;
            level = minimumLevel;
            if (minimumLevel <= 0)
            {
                level = character->getLevel()->m_dungeonDepth;
                if (level <= 0)
                    level = 1;
            }
            if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x29)))
            {
                minimumAdjustment = -4;
                maximumAdjustment = 4;
            }
        }
    }
    if (level != -1)
    {
        level += levelOffset;
        if (level <= 0)
            level = 1;
    }
    if (m_pRandomizer == NULL)
    {
        m_pRandomizer = new CRandomizer(RANDOMIZER_NORMAL);
        m_pType1Randomizer = new CRandomizer(RANDOMIZER_NORMAL);
        m_pType2Randomizer = new CRandomizer(RANDOMIZER_NORMAL);
    }
    for (unsigned int i = 0; i < m_lUnitDataObjects.size(); ++i)
    {
        int rarity = m_lUnitDataObjects[i]->GetDataValue(std::wstring(L"RARITY"), 1);
        if (hardcore)
            rarity = m_lUnitDataObjects[i]->GetDataValue(std::wstring(L"RARITY_HARDCORE"), rarity);
        if (rarityOverride != -1)
            rarity = rarityOverride;
        if (level == -1)
        {
            if (rarity != 0)
                m_pRandomizer->addChoice(i, rarity);
            continue;
        }
        if (m_lUnitDataObjects[i]->GetDataValue(std::wstring(L"CREATEAS"), L"") == L"EQUIPMENT")
        {
            std::wstring name = m_lUnitDataObjects[i]->GetDataValue(std::wstring(L"NAME"), L"WHAT?");
            int itemLevel = m_lUnitDataObjects[i]->GetDataValue(std::wstring(L"LEVEL"), 1);
            int minimum = m_lUnitDataObjects[i]->GetDataValue(std::wstring(L"MINLEVEL"), 0);
            int maximum = m_lUnitDataObjects[i]->GetDataValue(std::wstring(L"MAXLEVEL"), 0);
            if (!(flags & 0x10))
            {
                if (maximum == 0)
                {
                    minimum = static_cast<int>(floorf(m_pMinimumLevelGraph->getValue(static_cast<float>(itemLevel), 0)));
                    maximum = static_cast<int>(ceilf(m_pMaximumLevelGraph->getValue(static_cast<float>(itemLevel), 0)));
                }
                if (level < minimum + minimumAdjustment || level > maximum + maximumAdjustment)
                    continue;
            }
            if (rarity <= 0)
                continue;
            unsigned int type = CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeIDByName(
                m_lUnitDataObjects[i]->GetDataValue(std::wstring(L"UNITTYPE"), L""));
            if (CMasterResourceManager::getSingleton()->m_pHierarchy->ISA(type, 0x36))
            {
                if (!(flags & 2))
                    m_pType2Randomizer->addChoice(i, rarity);
            }
            else if (CMasterResourceManager::getSingleton()->m_pHierarchy->ISA(type, 0x37))
            {
                if (!(flags & 4))
                    m_pType1Randomizer->addChoice(i, rarity);
            }
            else
            {
                if ((flags & 1)
                    && !CMasterResourceManager::getSingleton()->m_pHierarchy->ISA(type, 8)
                    && !CMasterResourceManager::getSingleton()->m_pHierarchy->ISA(type, 0xd)
                    && !CMasterResourceManager::getSingleton()->m_pHierarchy->ISA(type, 0x11)
                    && !CMasterResourceManager::getSingleton()->m_pHierarchy->ISA(type, 0xa0)
                    && !CMasterResourceManager::getSingleton()->m_pHierarchy->ISA(type, 0x18))
                    continue;
                int index = m_pRandomizer->addChoice(i, rarity);
                if (flags & 1)
                    m_lPrimaryRandomizerIDs.add(index);
            }
        }
        else
        {
            int a = m_lUnitDataObjects[i]->GetDataValue(std::wstring(L"MINLEVEL"), 0);
            int b = m_lUnitDataObjects[i]->GetDataValue(std::wstring(L"MAXLEVEL"), 99999);
            int minimum = a < b ? a : b;
            int maximum = a < b ? b : a;
            if (level < minimum || level > maximum)
            {
                if (rarityOverride == -1)
                    continue;
                rarity = rarityOverride;
            }
            if (rarity != 0)
                m_pRandomizer->addChoice(i, rarity);
        }
    }
}

void CSpawnClassData::rollSpawnClassData(TArrayList<CDataGroup*>& dataGroups,
                                        TArrayList<bool>* primaryChoices,
                                        CCharacter* character, CCharacter* rollingCharacter,
                                        int minimumLevel, int levelOffset, int rarityOverride,
                                        int bonusPercentage, int flags)
{
    if (m_pSpawnClass != NULL)
    {
        m_pSpawnClass->rollSpawnClass(dataGroups, primaryChoices, character, rollingCharacter,
                                     minimumLevel, static_cast<unsigned int>(-1), levelOffset,
                                     rarityOverride, bonusPercentage, flags);
        return;
    }
    calculateChoices(character, minimumLevel, levelOffset, rarityOverride, flags);
    if (m_pRandomizer == NULL)
        return;
    if (!m_pRandomizer->hasChoices() && !m_pType1Randomizer->hasChoices()
        && !m_pType2Randomizer->hasChoices())
        return;
    unsigned int magicFind = 0;
    if (rollingCharacter != NULL)
    {
        magicFind = static_cast<unsigned int>(rollingCharacter->getEffectValue(
            static_cast<EEFFECT_TYPE>(0x1b), static_cast<EDAMAGE_TYPES>(7)));
        if (rollingCharacter->m_pMaster != NULL)
        {
            unsigned int value = static_cast<unsigned int>(rollingCharacter->m_pMaster->getEffectValue(
                static_cast<EEFFECT_TYPE>(0x1b), static_cast<EDAMAGE_TYPES>(7)));
            if (value > magicFind)
                magicFind = value;
            if (rollingCharacter->m_pMaster != NULL && rollingCharacter->m_pMaster->m_pMaster != NULL)
            {
                value = static_cast<unsigned int>(rollingCharacter->m_pMaster->m_pMaster->getEffectValue(
                    static_cast<EEFFECT_TYPE>(0x1b), static_cast<EDAMAGE_TYPES>(7)));
                if (value >= magicFind)
                    magicFind = value;
            }
        }
    }
    CRandomizer categories(RANDOMIZER_NORMAL);
    if (m_pType2Randomizer->hasChoices())
    {
        int weight = CGameGlobals::getSingleton()->m_uniqueItemWeight;
        if (magicFind != 0 || bonusPercentage != 0)
        {
            float percent = static_cast<float>(magicFind + static_cast<unsigned int>(bonusPercentage)) / 100.0f;
            weight += static_cast<unsigned int>(ceilf(percent * CGameGlobals::getSingleton()->m_magicFindUniqueInfluence
                                                     * static_cast<float>(weight)));
        }
        categories.addChoice(2, weight);
    }
    if (m_pType1Randomizer->hasChoices())
    {
        int weight = CGameGlobals::getSingleton()->m_magicItemWeight;
        if (magicFind != 0 || bonusPercentage != 0)
        {
            float percent = static_cast<float>(magicFind + static_cast<unsigned int>(bonusPercentage)) / 100.0f;
            weight += static_cast<unsigned int>(ceilf(percent * CGameGlobals::getSingleton()->m_magicFindMagicInfluence
                                                     * static_cast<float>(weight)));
        }
        categories.addChoice(1, weight);
    }
    if (m_pRandomizer->hasChoices())
        categories.addChoice(0, CGameGlobals::getSingleton()->m_normalItemWeight);
    int choiceIndex = 0;
    int unitIndex = 0;
    bool primary = false;
    switch (categories.getRandom())
    {
    case 0:
        unitIndex = m_pRandomizer->getRandom(choiceIndex);
        primary = true;
        break;
    case 1:
        unitIndex = m_pType1Randomizer->getRandom();
        break;
    case 2:
        unitIndex = m_pType2Randomizer->getRandom();
        break;
    }
    if (static_cast<unsigned int>(unitIndex) < m_lUnitDataObjects.size())
    {
        dataGroups.add(m_lUnitDataObjects[unitIndex]);
        if (primaryChoices != NULL)
        {
            bool selectedPrimary = false;
            if (primary)
            {
                for (unsigned int i = 0; i < m_lPrimaryRandomizerIDs.size(); ++i)
                    if (m_lPrimaryRandomizerIDs[i] == choiceIndex)
                    {
                        selectedPrimary = true;
                        break;
                    }
            }
            primaryChoices->add(selectedPrimary);
        }
    }
}
