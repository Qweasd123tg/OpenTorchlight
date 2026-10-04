#ifndef COLLIDERWRAPPER_H
#define COLLIDERWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CColliderWrapper : public CAffectorWrapper
{
public:
    virtual ~CColliderWrapper();
    CColliderWrapper(CResourceManager*, std::string);

    // fields
    unsigned char m_gap11A[0x6];
};

#endif
