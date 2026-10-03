#ifndef IINVENTORYLISTENER_H
#define IINVENTORYLISTENER_H

class CEquipment;

// Receives inventory notifications (implemented by CCharacter).
class iInventoryListener
{
public:
    virtual ~iInventoryListener() {}

    virtual void equipmentPickedUp(CEquipment* equipment) = 0;
    virtual void equipmentDropped(CEquipment* equipment) = 0;
    virtual void equipmentEquipped(CEquipment* equipment) = 0;
    virtual void equipmentUnequipped(CEquipment* equipment) = 0;
    virtual void equipmentUsed(CEquipment* equipment) = 0;
    virtual void inventoryDestroyed() = 0;
};

#endif
