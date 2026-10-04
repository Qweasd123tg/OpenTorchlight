#include "EmptyStrings.h"
#include "DungeonObject.h"
#include "ResourceManager.h"
#include "GameClient.h"
#include "Player.h"

CDungeonObject::CDungeonObject(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, NULL), m_sDungeon(EMPTY_WSTRING),
      m_pResourceManager(resourceManager)
{
}

CDungeonObject::~CDungeonObject()
{
}

void CDungeonObject::createEntity()
{
}

void CDungeonObject::clearHistory()
{
    CResourceManager* resourceManager = m_pResourceManager;
    for (unsigned int i = 0; i < resourceManager->getGameClientCount(); ++i)
    {
        CPlayer* player = resourceManager->getGameClient(i)->getPlayer();
        if (player != NULL)
        {
            player->clearDungeonHistory(m_sDungeon);
            if (player->getResourceManager() != NULL && player->getResourceManager()->getLevel() != NULL)
                player->updateStoredLevels(*player->getResourceManager()->getLevel());
        }
    }
}
