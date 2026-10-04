#include "EmptyStrings.h"
#include "Warper.h"
#include "GameClient.h"
#include "Player.h"
#include "Level.h"

CWarper::CWarper(CResourceManager* pResourceManager)
    : CPositionableObject(pResourceManager, 0),
      m_iLevelDelta(1),
      m_iLevelDepth(0),
      m_bEnabled(true),
      m_bWaypoint(false),
      m_sDungeon(EMPTY_WSTRING),
      m_sWarpName(EMPTY_WSTRING),
      m_pResourceManager(pResourceManager)
{
}

CWarper::~CWarper()
{
}
void CWarper::createEntity() {}

void CWarper::activate()
{
    CResourceManager* pResourceManager = m_pResourceManager;

    for (unsigned int iClient = 0;
         iClient < pResourceManager->getGameClientCount();
         iClient++)
    {
        CPlayer* pPlayer = pResourceManager->getGameClient(iClient)->getPlayer();
        if (pPlayer == NULL)
            continue;

        if (m_bWaypoint)
        {
            CLevel* pLevel = pPlayer->getLevel();
            pPlayer->addWaypoint(pLevel->getDungeonName(), pLevel->getLevelDepth());
        }

        pResourceManager->getGameClient(iClient)->warpLevels(m_sDungeon,
                                                          m_iLevelDelta,
                                                          m_iLevelDepth,
                                                          m_bWaypoint,
                                                          m_sWarpName,
                                                          false);
    }
}
