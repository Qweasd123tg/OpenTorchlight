#ifndef FORCEWRAPPER_H
#define FORCEWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CForceWrapper : public CAffectorWrapper
{
public:
    virtual ~CForceWrapper();
    CForceWrapper(CResourceManager*, std::string);

    // fields
    unsigned char m_gap11A[0x6];
};

#endif
