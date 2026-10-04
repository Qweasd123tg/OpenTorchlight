#include "EmptyStrings.h"
#include "MoneyTaker.h"
#include "ResourceManager.h"
#include "GameClient.h"
#include "Player.h"
#include "OutputEvents.h"

CMoneyTaker::CMoneyTaker(CResourceManager* resourceManager)
    : m_iAmount(0), m_pResourceManager(resourceManager)
{
}

CMoneyTaker::~CMoneyTaker()
{
}

void CMoneyTaker::takeMoney()
{
    CPlayer* player = m_pResourceManager->getGameClient()->getPlayer();
    if (player != NULL)
    {
        if (player->getGold() >= m_iAmount)
        {
            player->giveGold(-m_iAmount);
            BroadcastEvent(OUTPUT_EVENT_MONEY_TAKEN);
        }
        else
            BroadcastEvent(OUTPUT_EVENT_INSUFFICIENT_FUNDS);
    }
}
