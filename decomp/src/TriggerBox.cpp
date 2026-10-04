#include "EmptyStrings.h"
#include "TriggerBox.h"
#include "ResourceManager.h"
#include "GameClient.h"
#include "Player.h"

CTriggerBox::CTriggerBox(CResourceManager* resourceManager)
    : CLogicTrigger(resourceManager), m_vDimensions(0.0f, 0.0f, 0.0f)
{
    setDimensions(Ogre::Vector3(4.0f, 4.0f, 4.0f));
    setVisible(true);
}

CTriggerBox::~CTriggerBox()
{
}

void CTriggerBox::setDimensions(const Ogre::Vector3& dimensions)
{
    m_vDimensions = dimensions;
    m_vHalfDimensions.x = dimensions.x * 0.5f;
    m_vHalfDimensions.y = dimensions.y * 0.5f;
    m_vHalfDimensions.z = dimensions.z * 0.5f;
    setScale(dimensions.x, dimensions.y, dimensions.z);
}

void CTriggerBox::scaleUpdated(const Ogre::Vector3& scale)
{
    if (scale != m_vDimensions)
    {
        Ogre::Vector3 dimensions = scale;
        setDimensions(dimensions);
    }
}

void CTriggerBox::updateTrigger(float elapsed, CEditorScene* scene)
{
    if (getResourceManager() == NULL || !canUpdate())
        return;
    CResourceManager* resourceManager = getResourceManager();
    for (unsigned int i = 0; i < resourceManager->getGameClientCount(); ++i)
    {
        CPlayer* player = resourceManager->getGameClient(i)->getPlayer();
        if (player != NULL)
        {
            Ogre::Vector3 playerPosition = player->getPosition(true);
            Ogre::Vector3 position = getPosition(true);
            if (playerPosition.x > position.x - m_vHalfDimensions.x &&
                playerPosition.x < position.x + m_vHalfDimensions.x &&
                playerPosition.y > position.y - m_vHalfDimensions.y &&
                playerPosition.y < position.y + m_vHalfDimensions.y &&
                playerPosition.z > position.z - m_vHalfDimensions.z &&
                playerPosition.z < position.z + m_vHalfDimensions.z)
                TriggerActivated(player);
            else
                TriggerDeactivated(player);
        }
    }
}
