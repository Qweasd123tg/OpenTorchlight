#ifndef IRESOURCE_H
#define IRESOURCE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "DataGroup.h"
#include "ResourceManager.h"

class iResource
{
public:
    virtual ~iResource();
    virtual void resourceInit(CResourceManager*, CDataGroup*) = 0;
    virtual void resourceFreeing() = 0;
    virtual void free() = 0;

    // fields
};

#endif
