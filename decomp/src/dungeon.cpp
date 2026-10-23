#include "DungeonManager.h"
#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Dungeon.h"
#include "LevelTemplateData.h"
#include "DataGroup.h"
#include "RunicCore.h"
#include "StringUtilities.h"

CDungeon::~CDungeon()
{
    m_strataData.clear();
    if (m_pDungeonData) {
        delete m_pDungeonData;
        m_pDungeonData = NULL;
    }
    m_mustBeCompleted.deleteAll();
    m_mustBeCompletedOrActive.deleteAll();
    m_levelTemplateData.deleteAll();
}

CDungeon::CDungeon()
    : CRunicCore(),
      m_levelTemplateData(1),
      m_mustBeCompleted(1),
      m_mustBeCompletedOrActive(1),
      m_iDungeonIndex(-1),
      m_sParentDungeon(EMPTY_WSTRING),
      m_fMonsterLevelMultiplier(1.0f),
      m_iPlayerLevelMatchMin(1),
      m_iPlayerLevelMatchMax(1),
      m_iPlayerLevelMatchOffset(0),
      m_bVolatile(true),
      m_bBottomless(false),
      m_randomizer(static_cast<ERANDOMIZER_TYPE>(0)),
      m_pDungeonData(NULL),
      m_strataData(5)
{
}

CLevelTemplateData* CDungeon::getRandomLevelTemplateData()
{
    unsigned int depth = m_randomizer.getRandom();
    if (depth >= m_levelTemplateData.size())
        depth = 0;
    return getStrataTemplate(depth);
}


CLevelTemplateData* CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int depth)
{
    CLevelTemplateData* level = getStrataTemplate(depth < m_levelTemplateData.size() ?
                                                depth : m_levelTemplateData.size() - 1);
    if (level && level->m_string60 != EMPTY_WSTRING) {
        CDungeon* fallback = CDungeonManager::getSingleton()->getDungeonByName(level->m_string60);
        if (fallback)
            level = fallback->getRandomLevelTemplateData();
    }
    return level;
}

CLevelTemplateData* CDungeon::getStrataTemplate(unsigned int depth)
{
    if (depth >= m_levelTemplateData.size())
        return NULL;
    if (!m_levelTemplateData[depth])
    {
        CDataGroup* data = m_strataData[depth];
        std::wstring ruleset = data->GetDataValue(L"RULESET", L"media/layouts/crypt/rules.dat");
        bool portals = data->GetDataValue(L"ALLOW_PORTALS", true);
        bool pets = data->GetDataValue(L"ALLOW_PET_RETURN", true);
        bool town = data->GetDataValue(L"IS_TOWN", false);
        std::wstring dungeon = data->GetDataValue(L"DUNGEON", EMPTY_WSTRING);
        int minimum = data->GetDataValue(L"MONSTER_LVL_MIN", -1);
        int maximum = data->GetDataValue(L"MONSTER_LVL_MAX", -1);
        bool noQuests = data->GetDataValue(L"NO_RANDOM_QUESTS", false);
        std::wstring cinematic = data->GetDataValue(L"CINEMATIC", EMPTY_WSTRING);
        bool dontStore = data->GetDataValue(L"DONTSTORE", false);
        std::wstring name = data->GetDataValue(L"NAME_OVERRIDE", EMPTY_WSTRING);

        CLevelTemplateData* level = new CLevelTemplateData(ruleset.c_str());
        m_levelTemplateData[depth] = level;
        level->m_cinematic = cinematic;
        if (name != EMPTY_WSTRING)
            level->m_levelName = name;
        if (maximum > 0 && minimum > 0)
        {
            level->m_monsterLevelMin = minimum;
            level->m_monsterLevelMax = maximum;
        }
        if (noQuests)
            level->m_questSelectionExcluded = true;
        for (int i = 0; i < 11; ++i)
        {
            std::wstring previous = level->m_unitSpawnerNames[i];
            level->m_unitSpawnerNames[i] = data->GetDataValue(g_LEVELLAYOUT_CREATION_NAMES[i], previous);
            level->m_useSpawnClass[i] = data->GetDataValue(g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES[i], level->m_useSpawnClass[i]);
            float low = level->m_densityRanges[i].minimum;
            float high = data->GetDataValue(g_LEVELLAYOUT_CREATION_PATHNODES[2*i+1], level->m_densityRanges[i].maximum);
            low = data->GetDataValue(g_LEVELLAYOUT_CREATION_PATHNODES[2*i], low);
            level->m_densityRanges[i].minimum = low;
            level->m_densityRanges[i].maximum = high;
            low = level->m_countRanges[i].minimum;
            high = data->GetDataValue(g_LEVELLAYOUT_CREATION_COUNTS[2*i+1], level->m_countRanges[i].maximum);
            low = data->GetDataValue(g_LEVELLAYOUT_CREATION_COUNTS[2*i], low);
            level->m_countRanges[i].minimum = low;
            level->m_countRanges[i].maximum = high;
        }
        if (dontStore)
            level->m_dontStore = true;
        level->m_permitsPortal = portals;
        level->m_permitsPetDeparture = pets;
        level->m_isTown = town;
        std::wstring fallback = dungeon;
        level->m_string60 = fallback;
    }
    return m_levelTemplateData[depth];
}

bool CDungeon::loadDungeon(const wchar_t* filename)
{
    if (m_pDungeonData)
    {
        delete m_pDungeonData;
        m_pDungeonData = NULL;
    }
    m_pDungeonData = new CDataGroup(EMPTY_WSTRING, NULL, 20, 10, NULL);
    m_pDungeonData->LoadFile(filename, NULL);
    if (m_pDungeonData->GetGroupName().empty())
        return false;
    m_sName = m_pDungeonData->GetDataValue(L"NAME", EMPTY_WSTRING);
    m_sName = STRINGS::StringUpper(m_sName);
    m_sDisplayName = m_pDungeonData->GetDataValue(L"DISPLAYNAME", EMPTY_WSTRING);
    m_sParentDungeon = m_pDungeonData->GetDataValue(L"PARENT_DUNGEON", m_sParentDungeon);
    m_bVolatile = m_pDungeonData->GetDataValue(L"VOLATILE", true);
    m_fMonsterLevelMultiplier = m_pDungeonData->GetDataValue(L"MONSTER_LVL_MULT", m_fMonsterLevelMultiplier);
    m_iPlayerLevelMatchMin = m_pDungeonData->GetDataValue(L"PLAYER_LVL_MATCH_MIN", m_iPlayerLevelMatchMin);
    m_iPlayerLevelMatchMax = m_pDungeonData->GetDataValue(L"PLAYER_LVL_MATCH_MAX", m_iPlayerLevelMatchMax);
    m_iPlayerLevelMatchOffset = m_pDungeonData->GetDataValue(L"PLAYER_LVL_MATCH_OFFSET", m_iPlayerLevelMatchOffset);
    m_bBottomless = m_pDungeonData->GetDataValue(L"BOTTOMLESS", false);

    CDataGroup* strata = m_pDungeonData->GetDataGroupByName(L"STRATA" + STRINGS::GetValueAsWString(0u), false);
    unsigned int index = 1;
    while (strata)
    {
        int floors = strata->GetDataValue(L"FLOORS", 1);
        if (floors <= 0)
            floors = 1;
        int weight = strata->GetDataValue(L"WEIGHT", 1);
        m_levelTemplateData.setGrowBy(floors + 10);
        for (int floor = 0; floor < floors; ++floor)
        {
            m_strataData.add(strata);
            m_randomizer.addChoice(m_levelTemplateData.size(), weight);
            m_levelTemplateData.add(NULL);
            CDataGroup* completed = strata->GetDataGroupByName(L"MUST_BE_COMPLETED", false);
            CDataGroup* active = strata->GetDataGroupByName(L"MUST_BE_COMPLETED_OR_ACTIVE", false);
            if (completed)
            {
                TArrayList<std::wstring>* values = new TArrayList<std::wstring>(1);
                for (unsigned int i = 0; i < completed->GetNumberOfDataValues(); ++i)
                {
                    CDataValue* value = completed->GetDataValue(i);
                    if (value->GetValueType() == CDataValue::DATAVALUE_TRANSLATE || value->GetValueType() == CDataValue::DATAVALUE_STRING)
                        values->add(value->GetValueString(true));
                }
                m_mustBeCompleted.add(values);
            }
            else
                m_mustBeCompleted.add(NULL);
            if (active)
            {
                TArrayList<std::wstring>* values = new TArrayList<std::wstring>(1);
                for (unsigned int i = 0; i < active->GetNumberOfDataValues(); ++i)
                {
                    CDataValue* value = active->GetDataValue(i);
                    if (value->GetValueType() == CDataValue::DATAVALUE_TRANSLATE || value->GetValueType() == CDataValue::DATAVALUE_STRING)
                        values->add(value->GetValueString(true));
                }
                m_mustBeCompletedOrActive.add(values);
            }
            else
                m_mustBeCompletedOrActive.add(NULL);
        }
        strata = m_pDungeonData->GetDataGroupByName(L"STRATA" + STRINGS::GetValueAsWString(index), false);
        ++index;
    }
    return m_levelTemplateData.size() != 0;
}
