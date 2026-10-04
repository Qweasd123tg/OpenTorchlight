#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Dungeon.h"
#include "LevelTemplateData.h"
#include "RunicCore.h"

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
    if (depth >= static_cast<unsigned int>(m_iDungeonIndex))
        depth = 0;
    return getStrataTemplate(depth);
}
