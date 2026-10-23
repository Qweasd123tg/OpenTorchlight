#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "SharedStash.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Player.h"
#include "RunicCore.h"

CSharedStash* CSharedStash::getSingleton()
{
    return (CSharedStash*)g_pSharedStash;
}

CSharedStash::CSharedStash(const wchar_t* stashFileName,
                           const wchar_t* alternateStashFileName)
    : CRunicCore(),
      m_pInventory(NULL),
      m_stashFileName(stashFileName),
      m_alternateStashFileName(alternateStashFileName),
      m_bUseAlternateStash(false)
{
    if (g_pSharedStash == NULL)
    {
        m_pInventory = new CInventory(NULL, 42);
        g_pSharedStash = this;
    }
}

CSharedStash::~CSharedStash()
{
    g_pSharedStash = NULL;

    if (m_pInventory != NULL)
    {
        delete m_pInventory;
        m_pInventory = NULL;
    }
}

void CSharedStash::setPlayer(CPlayer* player)
{
    if (m_pInventory == NULL)
        return;
    m_pInventory->m_pPositionableObject = player;
    if (player == NULL)
        return;

    if (m_bUseAlternateStash != player->m_saveOnDeath)
    {
        m_bUseAlternateStash = player->m_saveOnDeath;
        if (m_pInventory != NULL)
        {
            delete m_pInventory;
            m_pInventory = NULL;
        }
        m_pInventory = NULL;
        loadSharedStash(player->getResourceManager(), player);
    }
    else
    {
        TArrayList<CEquipmentRef*>* equipment = &m_pInventory->m_equipmentRefs;
        if (equipment != NULL)
        {
            for (unsigned int i = 0; i < equipment->size(); ++i)
            {
                if ((*equipment)[i]->m_pEquipment != NULL)
                {
                    (*equipment)[i]->m_pEquipment->setResourceManager(player->getResourceManager());
                    (*equipment)[i]->m_pEquipment->setParentGuid(player->getGuid());
                }
            }
        }
    }
}
