#ifndef INVENTORY_H
#define INVENTORY_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include <map>
#include <vector>
#include "BaseUnit.h"
#include "EquipmentRef.h"
#include "Character.h"
#include "Constants.h"
#include "EffectDefines.h"
#include "EffectManager.h"
#include "GameEnums.h"
#include "PositionableObject.h"
#include "RunicCore.h"
#include "TArrayList.h"
#include "iInventoryListener.h"
class CEquipment;
class CSet;

class CInventory : public CRunicCore
{
public:
    unsigned int getEquipmentsOfUnitType(UNITTYPES::EUNITTYPES type, TArrayList<CEquipmentRef*>& output);

    virtual ~CInventory();
    void refreshEquipped();
    void removeListener(iInventoryListener*);
    void updateBonuses();
    int getPaneIndex(EINVENTORY_PANES);
    int getPaneSize(EINVENTORY_PANES);
    bool slotIsInPane(unsigned int, int);
    int itemsInPane(EINVENTORY_PANES);
    int getItemPane(unsigned int);
    bool isEquipmentInInventory(CEquipment*);
    bool EquipmentsInSlot(unsigned int);
    CEquipment* getEquipmentInSlot(unsigned int);
    CEquipmentRef* getEquipmentRefInSlot(unsigned int);
    int findEquipmentSlot(CEquipment*);
    CEquipment* getEquipmentEquippedAt(EEQUIP_LOCATIONS);
    int getEquipmentsEquippedLocation(CEquipment*);
    bool isEquipmentEquipped(CEquipment*);
    int getEquipmentCountOfGuid(long long);
    CEquipmentRef* getEquipmentOfGuid(long long);
    int getStackSizeOfEquipment(CEquipment*);
    int getMaxStackSizeOfEquipment(CEquipment*);
    void forceRecalculationOfEquipmentStats();
    bool canUseEquipment(CEquipment*, CCharacter*);
    void addListener(iInventoryListener*);
    int getRequiredPane(CEquipment*);
    int findFreeSlot(CEquipment*);
    bool canPickup(CEquipment*, bool);
    bool canEquipIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS, bool);
    bool canEquip(CEquipment*, bool);
    void getComparisonItems(CEquipment*, CEquipment**, CEquipment**);
    float getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES);
    void executeProcs(EEFFECT_TYPE, CBaseUnit*);
    void updateSkillManagers(float);
    float getEffectValue(EEFFECT_TYPE, float, const std::wstring&);
    float getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES);
    float getEffectValueMinusEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES);
    void transferEffects(CCharacter*, EEFFECT_ACTIVATION, EEFFECT_TYPE);
    float calculateEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES);
    void identifyAll();
    void freeInventory();
    void destroyIcons();
    unsigned int getEquipmentsOfQuestID(long long, TArrayList<CEquipmentRef*>&);
    unsigned int getEquipmentsOfUnitGuid(long long, TArrayList<CEquipmentRef*>&);
    // unresolved: CInventory::getEquipmentsOfUnitType(UNITTYPES::EUNITTYPES, TArrayList<CEquipmentRef*>&)
    int getSetCount(CSet*);
    void addSection(EINVENTORY_PANES, unsigned int);
    void calculateEffectValues();
    long long removeEquipment(CEquipment*);
    bool unequipEquipment(CEquipment*);
    void verifyEquipment();
    CEquipment* pickupEquipment(CEquipment*, int, bool);
    CEquipment* pickupEquipment(CEquipment*, bool);
    bool useEquipment(CEquipment*, CCharacter*);
    bool removeEquipmentByGuid(long long, unsigned int, bool);
    bool equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS);
    bool equipEquipmentIntoFirstFreeLocation(CEquipment*);
    void swapWeaponSet();
    CInventory(CCharacter*, unsigned int);

    // fields
    int m_iUnknown10;
    bool m_bUnknown14;
    bool m_bUnknown15;
    unsigned char m_gap16[0x2];
    CEffectManager* m_pEffectManager;
    CCharacter* m_pPositionableObject;
    unsigned int m_iUnknown28;
    unsigned char m_gap2C[0x4] __attribute__((aligned(4)));
    TArrayList<CEquipmentRef*> m_equipmentRefs;
    TArrayList<iInventoryListener*> m_listeners;
    // Original _M_insert_aux instantiations identify these vectors.
    std::vector<EINVENTORY_PANES> m_panes;
    std::vector<unsigned int> m_paneStarts;
    std::map<EEFFECT_TYPE, float> m_effectValues[8]; // +0x90

};

#endif
