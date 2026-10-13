#include "Effect.h"
#include "Utilities.h"
#include <OgreSceneNode.h>

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

void CInventory::addListener(iInventoryListener* listener)
{
    if (listener && m_listeners.find(listener) == -1) m_listeners.add(listener);
}

void CInventory::verifyEquipment()
{
    if (!m_pPositionableObject || m_bUnknown15) return;
    for (unsigned int pass = 0; pass < 20; ++pass) {
        bool valid = true;
        for (int slot = 0; slot < 12; ++slot) {
            CEquipmentRef* ref = getEquipmentRefInSlot(slot);
            if (!ref) continue;
            ref->m_effectsEnabled = false;
            calculateEffectValues();
            if (!canEquip(ref->m_pEquipment, false)) {
                ref->m_effectsEnabled = true;
                valid = false;
                unequipEquipment(ref->m_pEquipment);
            } else ref->m_effectsEnabled = true;
            calculateEffectValues();
        }
        if (valid) break;
    }
    updateBonuses();
}

bool CInventory::removeEquipmentByGuid(long long guid, unsigned int count, bool destroy)
{
    bool removed = false;
    for (int i = 0; i < static_cast<int>(m_equipmentRefs.size()); ++i) {
        if (m_equipmentRefs[i]->m_pEquipment->getUnitGuid() != guid) continue;
        CEquipment* equipment = m_equipmentRefs[i]->m_pEquipment;
        unsigned int stack = equipment->m_iUnknown238;
        if (stack > count) {
            equipment->incrementStackBy(-count);
            return true;
        }
        count -= stack;
        removeEquipment(equipment);
        if (destroy) delete equipment;
        if (!count) return true;
        --i;
        removed = true;
    }
    return removed;
}

long long CInventory::removeEquipment(CEquipment* equipment)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        CEquipmentRef* ref = m_equipmentRefs[i];
        CEquipment* item = ref->m_pEquipment;
        if (item != equipment) continue;
        int index = m_equipmentRefs.find(ref);
        if (index == -1) return false;
        m_equipmentRefs.removeAt(index);
        if (ref->m_iSlot <= 11) {
            equipment->unequipped(this, m_pPositionableObject, static_cast<EEQUIP_LOCATIONS>(ref->m_iSlot));
            for (unsigned int j = 0; j < m_listeners.size(); ++j)
                m_listeners[j]->equipmentUnequipped(equipment);
        }
        ref->m_pEquipment = NULL;
        delete ref;
        item->removedFromInventory(this, m_pPositionableObject);
        for (unsigned int j = 0; j < m_listeners.size(); ++j)
            m_listeners[j]->equipmentDropped(equipment);
        updateBonuses();
        calculateEffectValues();
        verifyEquipment();
        return true;
    }
    return false;
}

void CInventory::freeInventory()
{
    for (unsigned int i = 0; i < m_listeners.size(); ++i)
        m_listeners[i]->inventoryDestroyed();
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        if (m_equipmentRefs[i] && m_equipmentRefs[i]->m_pEquipment) {
            if (m_equipmentRefs[i]->m_pEquipment->getLevel())
                m_equipmentRefs[i]->m_pEquipment->getLevel()->notifyOfDeletion(m_equipmentRefs[i]->m_pEquipment);
            if (m_equipmentRefs[i]) {
                delete m_equipmentRefs[i];
                m_equipmentRefs[i] = NULL;
            }
        }
    }
    m_equipmentRefs.clear();
}

int CInventory::findFreeSlot(CEquipment* equipment)
{
    int end = m_iUnknown28;
    unsigned int pane = getPaneIndex(static_cast<EINVENTORY_PANES>(getRequiredPane(equipment)));
    int start = m_paneStarts[pane];
    if (pane < m_paneStarts.size() - 1) end = m_paneStarts[pane + 1];
    bool stacking = m_bUnknown14;
    if (stacking && equipment->m_iUnknown23C > 0) {
        CEquipment* chosen = NULL;
        int result = -1;
        for (int slot = start; slot < end; ++slot) {
            CEquipment* item = getEquipmentInSlot(slot);
            if (item && equipment->m_iUnknown23C != 1 && equipment->getUnitGuid() == item->getUnitGuid() &&
                equipment->m_iUnknown238 + item->m_iUnknown238 <= item->m_iUnknown23C &&
                (!chosen || item->m_iUnknown238 > chosen->m_iUnknown238)) {
                // The original keeps the incoming equipment in this comparison.
                chosen = equipment;
                result = slot;
            }
        }
        if (chosen) return result;
    }
    for (int slot = start; slot < end; ++slot) {
        CEquipment* item = getEquipmentInSlot(slot);
        if (!item || (stacking && equipment->m_iUnknown23C > 1 && equipment->getUnitGuid() == item->getUnitGuid() &&
            equipment->m_iUnknown238 + item->m_iUnknown238 <= item->m_iUnknown23C)) return slot;
    }
    return -1;
}

CInventory::CInventory(CCharacter* owner, unsigned int capacity)
    : m_iUnknown10(0), m_bUnknown14(true), m_bUnknown15(false), m_pEffectManager(NULL),
      m_pPositionableObject(owner), m_iUnknown28(capacity + 19), m_equipmentRefs(1), m_listeners(1)
{
    if (!m_pEffectManager) m_pEffectManager = new CEffectManager(NULL);
    m_panes.clear();
    m_panes.push_back(static_cast<EINVENTORY_PANES>(0));
    m_paneStarts.clear();
    m_paneStarts.push_back(19);
    freeInventory();
    calculateEffectValues();
}

void CInventory::executeProcs(EEFFECT_TYPE type, CBaseUnit* target)
{
    for (unsigned int slot = 0; slot < 12; ++slot) {
        CEquipment* equipment = getEquipmentInSlot(slot);
        if (!equipment || !equipment->hasEffect(type) || !equipment->getSkillManager()) continue;
        for (int activation = 0; activation < 3; ++activation) {
            TArrayList<CEffect*>& effects = reinterpret_cast<TArrayList<CEffect*>*>(
                equipment->m_pEffectManager->m_EffectData10 + 0x18)[activation];
            for (unsigned int i = 0; i < effects.size(); ++i) {
                if (effects[i]->m_eType != type) continue;
                int roll = UTILITIES::randomIntegerBetweenVolatile(0, 100);
                if (!(effects[i]->value(static_cast<EEFFECT_VALUES>(0)) >= static_cast<float>(roll))) continue;
                CSkill* skill = equipment->getSkillManager()->getSkill(effects[i]->m_sName, effects[i]->m_iLevel);
                if (!skill) continue;
                Ogre::Vector3 targetPosition = target ? target->getPosition(true) : m_pPositionableObject->getPosition(true);
                const Ogre::Quaternion& orientation = m_pPositionableObject->getSceneNode()->getOrientation();
                Ogre::Vector3 position = m_pPositionableObject->getPosition(true);
                equipment->getSkillManager()->executeSkill(skill, m_pPositionableObject,
                    static_cast<ESKILL_ACTIVATION_TYPE>(1), position, orientation, targetPosition, target);
            }
        }
    }
}

bool CInventory::equipEquipmentIntoSpecificLocation(CEquipment* equipment, EEQUIP_LOCATIONS location)
{
    if (!canEquipIntoSpecificLocation(equipment, location, false)) return false;
    if (equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(9)) &&
        (location == static_cast<EEQUIP_LOCATIONS>(0) || location == static_cast<EEQUIP_LOCATIONS>(1))) {
        CEquipment* opposite = getEquipmentInSlot(location == static_cast<EEQUIP_LOCATIONS>(0) ? 1 : 0);
        if (opposite && opposite->ISA(static_cast<UNITTYPES::EUNITTYPES>(10))) {
            removeEquipment(opposite);
            if (!pickupEquipment(opposite, true)) {
                Ogre::Vector3 position = m_pPositionableObject->getPosition(true);
                opposite->getLevel()->addItem(opposite, position, true);
                opposite->setPosition(m_pPositionableObject->getPosition(true));
                opposite->drop();
            }
        }
    }
    CEquipmentRef* reference = NULL;
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        if (m_equipmentRefs[i] && m_equipmentRefs[i]->m_pEquipment == equipment) {
            reference = m_equipmentRefs[i];
            break;
        }
    }
    if (reference) {
        reference->m_slot = location;
    } else {
        reference = new CEquipmentRef;
        reference->m_pEquipment = equipment;
        reference->m_slot = location;
        reference->m_originalSlot = location;
        reference->m_flag20 = false;
        reference->m_effectsEnabled = true;
        m_equipmentRefs.add(reference);
    }
    equipment->equipped(this, m_pPositionableObject, location);
    updateBonuses();
    calculateEffectValues();
    verifyEquipment();
    for (unsigned int i = 0; i < m_listeners.size(); ++i)
        m_listeners[i]->equipmentEquipped(equipment);
    return true;
}

void CInventory::swapWeaponSet()
{
    CEquipmentRef* right = getEquipmentRefInSlot(0);
    CEquipmentRef* left = getEquipmentRefInSlot(1);
    CEquipmentRef* secondaryRight = getEquipmentRefInSlot(12);
    CEquipmentRef* secondaryLeft = getEquipmentRefInSlot(13);
    if (right) {
        right->m_slot = 12;
        right->m_pEquipment->unequipped(this, m_pPositionableObject, static_cast<EEQUIP_LOCATIONS>(0));
        for (unsigned int i = 0; i < m_listeners.size(); ++i)
            m_listeners[i]->equipmentUnequipped(right->m_pEquipment);
    }
    if (left) {
        left->m_slot = 13;
        left->m_pEquipment->unequipped(this, m_pPositionableObject, static_cast<EEQUIP_LOCATIONS>(1));
        for (unsigned int i = 0; i < m_listeners.size(); ++i)
            m_listeners[i]->equipmentUnequipped(left->m_pEquipment);
    }
    if (secondaryRight) {
        secondaryRight->m_slot = 0;
        secondaryRight->m_pEquipment->equipped(this, m_pPositionableObject, static_cast<EEQUIP_LOCATIONS>(0));
        for (unsigned int i = 0; i < m_listeners.size(); ++i)
            m_listeners[i]->equipmentEquipped(secondaryRight->m_pEquipment);
    }
    if (secondaryLeft) {
        secondaryLeft->m_slot = 1;
        secondaryLeft->m_pEquipment->equipped(this, m_pPositionableObject, static_cast<EEQUIP_LOCATIONS>(1));
        for (unsigned int i = 0; i < m_listeners.size(); ++i)
            m_listeners[i]->equipmentEquipped(secondaryLeft->m_pEquipment);
    }
    updateBonuses();
    calculateEffectValues();
    verifyEquipment();
}
