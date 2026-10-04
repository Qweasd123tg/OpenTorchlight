#ifndef LINEWRAPPER_H
#define LINEWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CLineWrapper : public CAffectorWrapper
{
public:
    virtual ~CLineWrapper();
    CLineWrapper(CResourceManager*);

    // fields
    unsigned char m_gap11A[0x6];
};

#endif
