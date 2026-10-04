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
    m_pMinimumLevelGraph = CGraphManager::getSingleton()->getGraph(L"ITEM_SPAWN_RANGE_MINIMUM");
    m_pMaximumLevelGraph = CGraphManager::getSingleton()->getGraph(L"ITEM_SPAWN_RANGE_MAXIMUM");
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
