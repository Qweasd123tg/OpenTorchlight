#include "Equipment.h"
#include "Inventory.h"
#include "Inventory.h"


int CInventory::getPaneSize(EINVENTORY_PANES pane)
{
    unsigned int index = getPaneIndex(pane);
    if (m_paneStarts.size() - 1 == index)
        return m_iUnknown28 - m_paneStarts[index];
    return m_paneStarts[index + 1] - m_paneStarts[index];
}

bool CInventory::slotIsInPane(unsigned int pane, int slot)
{
    int start = m_paneStarts[pane];
    int end = m_iUnknown28;
    if (pane < m_paneStarts.size() - 1)
        end = m_paneStarts[pane + 1];
    return slot >= start && slot < end;
}

int CInventory::getItemPane(unsigned int slot)
{
    for (unsigned int i = 0; i < m_paneStarts.size(); ++i)
    {
        if (slot >= m_paneStarts[i] &&
            (i == m_paneStarts.size() - 1 || slot < m_paneStarts[i + 1]))
            return i;
    }
    return 0;
}

void CInventory::addSection(EINVENTORY_PANES pane, unsigned int size)
{
    m_panes.push_back(pane);
    m_paneStarts.push_back(m_iUnknown28);
    m_iUnknown28 += size;
}




// Imported source candidates; historical status is not fresh acceptance.
void CInventory::refreshEquipped()
{
    for (unsigned int i = 0; i < m_listeners.size(); ++i)
        m_listeners[i]->equipmentEquipped(NULL);
}

void CInventory::removeListener(iInventoryListener* listener)
{
    if (listener) m_listeners.remove(listener);
}

bool CInventory::isEquipmentInInventory(CEquipment* equipment)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        CEquipmentRef* ref = m_equipmentRefs[i];
        if (ref && ref->m_pEquipment == equipment) return true;
    }
    return false;
}

CEquipment* CInventory::getEquipmentInSlot(unsigned int slot)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        CEquipmentRef* ref = m_equipmentRefs[i];
        if (ref && ref->m_slot == slot) return ref->m_pEquipment;
    }
    return NULL;
}

CEquipmentRef* CInventory::getEquipmentRefInSlot(unsigned int slot)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        CEquipmentRef* ref = m_equipmentRefs[i];
        if (ref && ref->m_slot == slot) return ref;
    }
    return NULL;
}

int CInventory::getStackSizeOfEquipment(CEquipment* equipment)
{
    return equipment ? equipment->m_iUnknown238 : 0;
}

int CInventory::getMaxStackSizeOfEquipment(CEquipment* equipment)
{
    return equipment ? equipment->m_iUnknown23C : 0;
}

bool CInventory::canUseEquipment(CEquipment* equipment, CCharacter* target)
{
    if (!equipment) return false;
    if (!target) target = m_pPositionableObject;
    return equipment->canUseOnTarget(m_pPositionableObject, target);
}

int CInventory::itemsInPane(EINVENTORY_PANES pane)
{
    unsigned int index = getPaneIndex(pane);
    int count = 0;
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        unsigned int slot = m_equipmentRefs[i]->m_slot;
        if (slot >= m_paneStarts[index] && (m_paneStarts.size() - 1 == index || slot < m_paneStarts[index + 1])) ++count;
    }
    return count;
}
