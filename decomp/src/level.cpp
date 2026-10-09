
#include "BaseUnit.h"
#include "Character.h"
#include "GameClient.h"
#include "Item.h"
#include "Level.h"
#include "Player.h"

CCharacter* CLevel::getPlayer()
{
    return m_pGameClient ? m_pGameClient->getPlayer() : NULL;
}

void CLevel::questEventFire(EQUEST_EVENTS event, CCharacter* character, CBaseUnit* target)
{
    if (m_pGameClient)
        m_pGameClient->questEventFire(event, character, target);
}

void CLevel::removeUnit(CBaseUnit* unit, bool flag)
{
    if (unit)
    {
        if (unit->m_eBaseUnitType == static_cast<EBASEUNIT_TYPE>(1))
            removeItem(static_cast<CItem*>(unit), flag);
        else if (unit->m_eBaseUnitType == static_cast<EBASEUNIT_TYPE>(0))
            removeCharacter(static_cast<CCharacter*>(unit), flag);
    }
}
