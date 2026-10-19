#ifndef TRIGGERUNIT_H
#define TRIGGERUNIT_H

#include "Item.h"

// Partial: the original RTTI proves the CItem base; used for descriptor casts.
class CTriggerUnit : public CItem
{
public:
    CTriggerUnit(CResourceManager*);
    virtual ~CTriggerUnit();
    virtual void setActiveInLevel(bool);
    virtual void* getUnitModel();
    virtual void* getUnitCollisionModel();
private:
    // Native createNewItem allocates 0x300; CItem tail padding ends at 0x22c.
    unsigned char m_unrecovered22C[0x300-0x22c] __attribute__((aligned(4)));
};

#endif
