#ifndef ISTATLISTENER_H
#define ISTATLISTENER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "DescriptorProp.h"

class iStatListener
{
public:
    virtual ~iStatListener();
    virtual void statChanged(unsigned int, UNIONDATA32BIT, UNIONDATA32BIT) = 0;

    // fields
};

#endif
