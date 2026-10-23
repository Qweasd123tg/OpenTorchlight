#include "EmptyStrings.h"
#include "WaypointActivator.h"
#include "PositionableObject.h"
#include "ResourceManager.h"

void CWaypointActivator::createEntity()
{
}

CWaypointActivator::CWaypointActivator(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, NULL), m_emptyWString(EMPTY_WSTRING),
      m_pResourceManager(resourceManager)
{
}

CWaypointActivator::~CWaypointActivator()
{
}

#include "Level.h"
#include "GameClient.h"
#include "GameUI.h"
#include "Player.h"
#include "StringTranslate.h"

void CWaypointActivator::activate()
{
    CResourceManager* resources = m_pResourceManager;
    for (unsigned int i = 0; i < resources->getGameClientCount(); ++i) {
        CPlayer* player = resources->getGameClient(i)->getPlayer();
        if (!player || !player->getLevel())
            continue;
        bool added = player->addWaypoint(player->getLevel()->getDungeonName(),
                                         player->getLevel()->getLevelDepth());
        static std::wstring g_WaypointActivated;
        if (g_WaypointActivated.empty())
            g_WaypointActivated = CStringTranslate::getSinglton()->getTranslateString(L"Waypoint Activated");
        if (added) {
            player->getLevel()->m_pGameClient->getGameUI()->setBigText(g_WaypointActivated, 1.0f);
            player->getLevel()->m_pGameClient->getGameUI()->setSmallText(EMPTY_WSTRING, 1.0f);
        }
    }
}
