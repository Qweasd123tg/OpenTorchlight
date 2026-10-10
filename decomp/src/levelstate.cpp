#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "LevelState.h"
#include "LogicNodeState.h"
#include "Automap.h"
#include "RunicCore.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "Level.h"

CLevelState::CLevelState(int iLevelId)
    : CRunicCore(),
      m_iLevelId(iLevelId),
      m_sLevelName(EMPTY_WSTRING),
      m_lCharacters(),
      m_lItems(),
      m_lLogicStates(),
      m_lLevelStrings(),
      m_lFormations(10),
      m_iStateVersion(0),
      m_iAutomapWidth(0),
      m_iAutomapHeight(0),
      m_pAutomapData(NULL),
      m_bUnknownB0(false),
      m_bUnknownB1(false)
{
}

void CLevelState::restoreAutomap(CAutomap *pAutomap)
{
    if (m_iAutomapWidth == pAutomap->m_iMapGridWidth &&
        m_iAutomapHeight == pAutomap->m_iMapGridHeight) {
        memcpy(pAutomap->m_pRevealedTiles, m_pAutomapData,
               (long)(m_iAutomapWidth * m_iAutomapHeight) << 2);
        pAutomap->m_bTilesChanged = true;
    }
}

void CLevelState::addLogicState(CLogicNodeState *pLogicState, CLevel &Level)
{
    m_lLogicStates.push_back(pLogicState);
}
