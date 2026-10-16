#ifndef TRIGGERUNIT_H
#define TRIGGERUNIT_H

#include "Item.h"

// Partial: the original RTTI proves the CItem base; used for descriptor casts.
class CTriggerUnit : public CItem
{
public:
    virtual ~CTriggerUnit();
};

#endif
