#include "EmptyStrings.h"
#include "TriggerSphere.h"
#include "ResourceManager.h"
#include "GameClient.h"
#include "Player.h"

CTriggerSphere::CTriggerSphere(CResourceManager* resourceManager)
    : CLogicTrigger(resourceManager), m_fRadius(1.0f)
{
    void (CPositionableObject::*setUniformScale)(float) = &CPositionableObject::setScale;
    (this->*setUniformScale)(1.0f);
    setVisible(true);
}

CTriggerSphere::~CTriggerSphere()
{
}

void CTriggerSphere::scaleUpdated(const Ogre::Vector3& scale)
{
    if (scale.x != m_fRadius)
    {
        m_fRadius = scale.x;
        setScale(m_fRadius);
    }
}

void CTriggerSphere::updateTrigger(float elapsed, CEditorScene* scene)
{
    if (getResourceManager() == NULL || !canUpdate())
        return;
    CResourceManager* resourceManager = getResourceManager();
    if (resourceManager->getGameClientCount() == 0)
        return;
    for (unsigned int i = 0; i < resourceManager->getGameClientCount(); ++i)
    {
        CPlayer* player = resourceManager->getGameClient(i)->getPlayer();
        if (player != NULL)
        {
            Ogre::Vector3 playerPosition = player->getPosition(true);
            if (getPosition(true).distance(playerPosition) <= m_fRadius)
                TriggerActivated(player);
            else
                TriggerDeactivated(player);
        }
    }
}
