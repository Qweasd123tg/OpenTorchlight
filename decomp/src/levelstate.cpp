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
      m_lCharacters(0),
      m_lItems(0),
      m_lLogicStates(0),
      m_lLevelStrings(0),
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
    if (m_iAutomapWidth == pAutomap->m_iUnknown90 &&
        m_iAutomapHeight == pAutomap->m_iUnknown94) {
        memcpy(pAutomap->m_pUnknown98, m_pAutomapData,
               (long)(m_iAutomapWidth * m_iAutomapHeight) << 2);
        pAutomap->m_bUnknownA0 = true;
    }
}

void CLevelState::addLogicState(CLogicNodeState *pLogicState, CLevel &Level)
{
    struct CLevelStateLayout
    {
        char m_gap[0x50];
        std::vector<CLogicNodeState *> m_lLogicStates;
    };

    reinterpret_cast<CLevelStateLayout *>(this)->m_lLogicStates.push_back(pLogicState);
}
