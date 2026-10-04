#include "EmptyStrings.h"
#include "Teleport.h"
#include "GameClient.h"
#include "Player.h"

CTeleport::~CTeleport()
{
}

CTeleport::CTeleport(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, 0),
      m_bEnabled(true),
      m_pResourceManager(resourceManager)
{
}


void CTeleport::activate(Ogre::Vector3 position, Ogre::Vector3 direction)
{
    CResourceManager* resourceManager = m_pResourceManager;
    for (unsigned int i = 0; i < resourceManager->getGameClientCount(); ++i)
    {
        CPlayer* player = resourceManager->getGameClient(i)->getPlayer();
        if (player)
        {
            player->stopPathing();
            player->removeFromAvoidanceMap(*player->getLevel());
            player->setPosition(position);
            player->setDirection(direction);
            player->dropToGround(*player->getLevel(), 4.0f, false);

            for (unsigned int j = 0; j < player->getFollowerCount(); ++j)
                player->getFollower(j)->teleportToMaster(1.0f);
            BroadcastEvent(8);
        }
    }
}
