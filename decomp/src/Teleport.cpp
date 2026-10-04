#include "EmptyStrings.h"
#include "Teleport.h"
#include "OutputEvents.h"
#include "ResourceManager.h"
#include "GameClient.h"
#include "Player.h"

CTeleport::CTeleport(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, NULL), m_bTeleportEnabled(true),
      m_pResourceManager(resourceManager)
{
}

CTeleport::~CTeleport()
{
}

void CTeleport::activate(Ogre::Vector3 position, Ogre::Vector3 direction)
{
    CResourceManager* resourceManager = m_pResourceManager;
    for (unsigned int i = 0; i < resourceManager->getGameClientCount(); i++)
    {
        CPlayer* player = resourceManager->getGameClient(i)->getPlayer();
        if (player == NULL)
            continue;
        player->stopPathing();
        player->removeFromAvoidanceMap(*player->getLevel());
        player->setPosition(position);
        player->setDirection(direction);
        player->dropToGround(*player->getLevel(), 4.0f, false);
        for (unsigned int pet = 0; pet < player->getPetCount(); pet++)
            player->getPet(pet)->teleportToMaster(1.0f);
        BroadcastEvent(OUTPUT_EVENT_ACTIVATED);
    }
}
