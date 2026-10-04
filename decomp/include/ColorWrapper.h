#ifndef COLORWRAPPER_H
#define COLORWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CColorWrapper : public CAffectorWrapper
{
public:
    virtual ~CColorWrapper();
    void setColors(float*, unsigned int);
    CColorWrapper(CResourceManager*);
    long long getColors(unsigned int&);

    // fields
    unsigned char m_gap11A[0x6];
    unsigned char m_Unknown120[0x18] __attribute__((aligned(8)));
};

#endif
