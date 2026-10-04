#ifndef SOUNDDATA_H
#define SOUNDDATA_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "RunicCore.h"

class CSoundData : public CRunicCore
{
public:
    virtual ~CSoundData();

    // fields
    void* m_pUnknown10;
    void* m_pUnknown18;
    long long m_iGuid;
    unsigned char m_gap28[0x18] __attribute__((aligned(8)));
    void* m_pUnknown40;
    unsigned char m_gap48[0x10] __attribute__((aligned(8)));
    long long m_iUnknown58;
};

#endif
