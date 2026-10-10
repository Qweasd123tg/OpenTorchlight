#include <cmath>
#include "Equipment.h"
#include "EquipmentRef.h"
#include "Level.h"
#include "Set.h"
#include "SkillManager.h"
static const UNITTYPES::EUNITTYPES gEQUIP_UNITTYPES_PANE[5] = {
    static_cast<UNITTYPES::EUNITTYPES>(31), static_cast<UNITTYPES::EUNITTYPES>(129),
    static_cast<UNITTYPES::EUNITTYPES>(124), static_cast<UNITTYPES::EUNITTYPES>(8),
    static_cast<UNITTYPES::EUNITTYPES>(13)
};

#include "Inventory.h"


int CInventory::getPaneSize(EINVENTORY_PANES pane)
{
    unsigned int index = getPaneIndex(pane);
    if (index == m_paneStarts.size() - 1)
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



void CInventory::refreshEquipped()
{
    for (unsigned int i = 0; i < m_listeners.size(); ++i)
        m_listeners[i]->equipmentEquipped(NULL);
}

void CInventory::removeListener(iInventoryListener* listener)
{
    if (listener) m_listeners.remove(listener);
}

void CInventory::updateBonuses()
{
    m_iUnknown10 = 0;
    for (int slot = 0; slot < 12; ++slot) {
        CEquipment* equipment = getEquipmentInSlot(slot);
        if (equipment) m_iUnknown10 += equipment->m_iUnknown338;
    }
}

int CInventory::itemsInPane(EINVENTORY_PANES pane)
{
    unsigned int index = getPaneIndex(pane);
    int count = 0;
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        unsigned int slot = m_equipmentRefs[i]->m_iSlot;
        if (slot >= m_paneStarts[index] && (index == m_paneStarts.size() - 1 || slot < m_paneStarts[index + 1])) ++count;
    }
    return count;
}

bool CInventory::isEquipmentInInventory(CEquipment* equipment)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        CEquipmentRef* ref = m_equipmentRefs[i];
        if (ref && ref->m_pUnknown10 == equipment) return true;
    }
    return false;
}

CEquipment* CInventory::getEquipmentInSlot(unsigned int slot)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        CEquipmentRef* ref = m_equipmentRefs[i];
        if (ref && ref->m_iSlot == slot) return ref->m_pUnknown10;
    }
    return NULL;
}

CEquipmentRef* CInventory::getEquipmentRefInSlot(unsigned int slot)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        CEquipmentRef* ref = m_equipmentRefs[i];
        if (ref && ref->m_iSlot == slot) return ref;
    }
    return NULL;
}

CEquipment* CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS location)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i)
    {
        CEquipmentRef* ref = m_equipmentRefs[i];
        if (ref && location == ref->m_iSlot) return ref->m_pUnknown10;
    }
    return NULL;
}
bool CInventory::isEquipmentEquipped(CEquipment* equipment)
{
    if (!equipment) return false;
    for (int i = 0; i < 12; ++i)
        if (getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(i)) == equipment) return true;
    return false;
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

int CInventory::getRequiredPane(CEquipment* equipment)
{
    for (int i = m_paneStarts.size() - 1; i >= 0; --i) {
        if (equipment->ISA(gEQUIP_UNITTYPES_PANE[m_panes[i]])) return m_panes[i];
    }
    return m_panes[0];
}

bool CInventory::canEquipIntoSpecificLocation(CEquipment* equipment, EEQUIP_LOCATIONS slot, bool ignoreCapacity)
{
    if (static_cast<unsigned int>(slot) > 18) return false;
    if (getEquipmentInSlot(slot)) return false;
    if (!canPickup(equipment, ignoreCapacity)) return false;
    return equipment->canEquip(m_pPositionableObject, true);
}

void CInventory::updateSkillManagers(float elapsed)
{
    for (int slot = 0; slot < 12; ++slot) {
        CEquipment* equipment = getEquipmentInSlot(slot);
        if (equipment && equipment->m_pSkillManager) equipment->m_pSkillManager->update(elapsed);
    }
}

void CInventory::transferEffects(CCharacter* character, EEFFECT_ACTIVATION activation, EEFFECT_TYPE type)
{
    for (int slot = 0; slot < 12; ++slot) {
        CEquipment* equipment = getEquipmentInSlot(slot);
        if (equipment && equipment->m_pEffectManager) equipment->m_pEffectManager->transferEffects(character, activation, type);
    }
}

CInventory::~CInventory()
{
    if (m_pEffectManager)
    {
        delete m_pEffectManager;
        m_pEffectManager = NULL;
    }
    freeInventory();
    m_pPositionableObject = NULL;
}

int CInventory::getSetCount(CSet* set)
{
    int count = 0;
    for (int slot = 0; slot < 12; ++slot) {
        CEquipment* equipment = getEquipmentInSlot(slot);
        if (equipment && equipment->getSet() == set->m_sName) ++count;
    }
    return count;
}

bool CInventory::unequipEquipment(CEquipment* equipment)
{
    removeEquipment(equipment);
    if (pickupEquipment(equipment, true))
        return true;
    equipment->getLevel()->addItem(equipment, m_pPositionableObject->getPosition(true), true);
    equipment->setPosition(m_pPositionableObject->getPosition(true));
    equipment->drop();
    return false;
}

int CInventory::getPaneIndex(EINVENTORY_PANES pane)
{
    for (int i = static_cast<int>(m_paneStarts.size()) - 1; i >= 0; --i)
        if (m_panes[i] == pane) return i;
    return 0;
}

bool CInventory::EquipmentsInSlot(unsigned int slot)
{
    if (slot < 12) return getEquipmentInSlot(slot) != NULL;
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        int location = m_equipmentRefs[i]->m_iSlot;
        if (location > 11 && static_cast<unsigned int>(location) == slot) return true;
    }
    return false;
}

int CInventory::findEquipmentSlot(CEquipment* equipment)
{
    for (int slot = 0; slot < static_cast<int>(m_iUnknown28); ++slot) {
        CEquipment* item = getEquipmentInSlot(slot);
        if (item && item == equipment) return slot;
    }
    return -1;
}

int CInventory::getEquipmentsEquippedLocation(CEquipment* equipment)
{
    for (int slot = 0; slot < 12; ++slot)
        if (getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(slot)) == equipment)
            return slot;
    return 12;
}

int CInventory::getEquipmentCountOfGuid(long long guid)
{
    int count = 0;
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        if (m_equipmentRefs[i]->m_pEquipment->getUnitGuid() == guid) {
            if (m_equipmentRefs[i]->m_pEquipment->m_iUnknown23C > 0)
                count += m_equipmentRefs[i]->m_pEquipment->m_iUnknown238;
            else ++count;
        }
    }
    return count;
}

CEquipmentRef* CInventory::getEquipmentOfGuid(long long guid)
{
    CEquipmentRef* result = NULL;
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        if (m_equipmentRefs[i]->m_pEquipment->getUnitGuid() == guid) {
            if (!result) result = m_equipmentRefs[i];
            if (m_equipmentRefs[i]->m_pEquipment->m_iUnknown23C <= 0) return result;
            if (result && m_equipmentRefs[i]->m_pEquipment->m_iUnknown238 < result->m_pEquipment->m_iUnknown238)
                result = m_equipmentRefs[i];
        }
    }
    return result;
}

void CInventory::forceRecalculationOfEquipmentStats()
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        if (m_equipmentRefs[i]->m_pEquipment && m_equipmentRefs[i]->m_pEquipment->m_pEffectManager)
            m_equipmentRefs[i]->m_pEquipment->m_pEffectManager->recalculateEffects();
    }
}

bool CInventory::canPickup(CEquipment* equipment, bool ignoreCapacity)
{
    if (!equipment) return false;
    if (equipment->getParentGuid() != -1)
        return equipment->getParentGuid() == m_pPositionableObject->getGuid();
    if (!equipment->canPickup(m_pPositionableObject)) return false;
    if (!equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(2))) return false;
    if (ignoreCapacity) return true;
    EINVENTORY_PANES pane = static_cast<EINVENTORY_PANES>(getRequiredPane(equipment));
    unsigned int items = itemsInPane(pane);
    return items < static_cast<unsigned int>(getPaneSize(pane));
}

float CInventory::getEffectValue(EEFFECT_TYPE effect, EDAMAGE_TYPES damage)
{
    if (m_effectValues[damage].find(effect) != m_effectValues[damage].end())
        return m_effectValues[damage][effect];
    return 0.0f;
}

float CInventory::getEffectValue(EEFFECT_TYPE effect, float value, const std::wstring& name)
{
    float result = 0.0f;
    for (int slot = 0; slot < 12; ++slot) {
        CEquipment* equipment = getEquipmentInSlot(slot);
        if (equipment) {
            result += ceilf(equipment->getEffectValue(effect, value, name));
            for (unsigned int i = 0; i < equipment->m_SocketedEquipment.size(); ++i)
                result += ceilf(equipment->m_SocketedEquipment[i]->getEffectValue(effect, value, name));
        }
    }
    return result + ceilf(m_pEffectManager->getEffectValue(effect, name));
}

float CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE effect, EEQUIP_LOCATIONS slot, EDAMAGE_TYPES damage)
{
    if (static_cast<int>(slot) == 12) return 0.0f;
    CEquipment* equipment = getEquipmentEquippedAt(slot);
    if (!equipment) return 0.0f;
    float result = ceilf(equipment->getEffectValue(EFFECT_ACTIVATION_PASSIVE, effect, 0.0f, damage));
    for (unsigned int i = 0; i < equipment->m_SocketedEquipment.size(); ++i)
        result += ceilf(equipment->m_SocketedEquipment[i]->getEffectValue(EFFECT_ACTIVATION_PASSIVE, effect, 0.0f, damage));
    return ceilf(result);
}

float CInventory::getEffectValueMinusEquipmentSlot(EEFFECT_TYPE effect, EEQUIP_LOCATIONS slot, EDAMAGE_TYPES damage)
{
    float result = ceilf(getEffectValue(effect, damage));
    if (result != 0.0f)
        return result - getEffectValueFromEquipmentSlot(effect, slot, damage);
    return 0.0f;
}

float CInventory::calculateEffectValue(EEFFECT_TYPE effect, EDAMAGE_TYPES damage)
{
    float result = 0.0f;
    for (int slot = 0; slot < 12; ++slot) {
        CEquipment* equipment = getEquipmentInSlot(slot);
        if (equipment) {
            result += ceilf(equipment->getEffectValue(EFFECT_ACTIVATION_PASSIVE, effect, 0.0f, damage));
            for (unsigned int i = 0; i < equipment->m_SocketedEquipment.size(); ++i)
                result += ceilf(equipment->m_SocketedEquipment[i]->getEffectValue(EFFECT_ACTIVATION_PASSIVE, effect, 0.0f, damage));
        }
    }
    return result + ceilf(m_pEffectManager->getEffectValue(EFFECT_ACTIVATION_PASSIVE, effect, damage));
}

void CInventory::identifyAll()
{
    for (int slot = 0; slot < static_cast<int>(m_iUnknown28); ++slot) {
        CEquipment* equipment = getEquipmentInSlot(slot);
        if (equipment) {
            equipment->m_bUnknown348 = true;
            equipment->destroyItemText();
        }
    }
}

void CInventory::destroyIcons()
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i)
        if (m_equipmentRefs[i] && m_equipmentRefs[i]->m_pEquipment)
            m_equipmentRefs[i]->m_pEquipment->destroyIcon();
}

unsigned int CInventory::getEquipmentsOfQuestID(long long guid, TArrayList<CEquipmentRef*>& output)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i)
        if (m_equipmentRefs[i]->m_pEquipment->getQuestGuid() == guid)
            output.add(m_equipmentRefs[i]);
    return output.size();
}

unsigned int CInventory::getEquipmentsOfUnitGuid(long long guid, TArrayList<CEquipmentRef*>& output)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i)
        if (m_equipmentRefs[i]->m_pEquipment->getUnitGuid() == guid)
            output.add(m_equipmentRefs[i]);
    return output.size();
}

unsigned int CInventory::getEquipmentsOfUnitType(UNITTYPES::EUNITTYPES type, TArrayList<CEquipmentRef*>& output)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i)
        if (m_equipmentRefs[i]->m_pEquipment->ISA(type))
            output.add(m_equipmentRefs[i]);
    return output.size();
}

bool CInventory::useEquipment(CEquipment* equipment, CCharacter* target)
{
    if (!equipment) return false;
    if (!target) target = m_pPositionableObject;
    if (!canUseEquipment(equipment, target)) return false;
    equipment->useEquipment(m_pPositionableObject, target);
    for (unsigned int i = 0; i < m_listeners.size(); ++i)
        m_listeners[i]->equipmentUsed(equipment);
    if (equipment->m_iUnknown238 <= 0) {
        removeEquipment(equipment);
        delete equipment;
    }
    return true;
}
