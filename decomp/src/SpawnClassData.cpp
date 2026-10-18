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
