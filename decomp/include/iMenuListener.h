#ifndef IMENULISTENER_H
#define IMENULISTENER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "GameEnums.h"

class iMenuListener
{
public:
    virtual ~iMenuListener();
    virtual void menuEventOccured(void*, EMENU_TYPE, EMENU_EVENT) = 0;

    // fields
};

#endif
