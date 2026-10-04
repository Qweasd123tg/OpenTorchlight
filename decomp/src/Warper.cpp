#include "EmptyStrings.h"
#include "Warper.h"
#include "ResourceManager.h"
#include "GameClient.h"
#include "Player.h"
#include "Level.h"

void CWarper::createEntity()
{
}

CWarper::CWarper(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, NULL), m_iLevelDelta(1), m_iLevelDepth(0),
      m_bWarperEnabled(true), m_bWaypoint(false), m_sDungeon(EMPTY_WSTRING),
      m_sWarpName(EMPTY_WSTRING), m_pResourceManager(resourceManager)
{
}

void CWarper::activate()
{
    CResourceManager* resourceManager = m_pResourceManager;
    for (unsigned int i = 0; i < resourceManager->getGameClientCount(); i++)
    {
        CPlayer* player = resourceManager->getGameClient(i)->getPlayer();
        if (player == NULL)
            continue;
        if (m_bWaypoint)
            player->addWaypoint(player->getLevel()->getDungeonName(), player->getLevel()->getDepth());
        resourceManager->getGameClient(i)->warpLevels(m_sDungeon, m_iLevelDelta, m_iLevelDepth, m_bWaypoint,
                                                      m_sWarpName, false);
    }
}

CWarper::~CWarper()
{
}
