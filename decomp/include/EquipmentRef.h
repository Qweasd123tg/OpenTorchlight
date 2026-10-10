#ifndef EQUIPMENTREF_H
#define EQUIPMENTREF_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "RunicCore.h"

class CEquipment;
class CEquipmentRef : public CRunicCore
{
public:
    virtual ~CEquipmentRef();

    // fields
    union { void* m_pUnknown10; CEquipment* m_pEquipment; };
    union { int m_iSlot; unsigned int m_slot; };
    unsigned char m_gap1C[0xc];
};

#endif
