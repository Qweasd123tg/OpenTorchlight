#ifndef ISNAP_H
#define ISNAP_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "GameEnums.h"

class iSnap
{
public:
    virtual ~iSnap();
    virtual long getSnapValues(ESNAP_TYPES) = 0;

    // fields
};

#endif
