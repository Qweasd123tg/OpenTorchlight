#ifndef SCALEWRAPPER_H
#define SCALEWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CScaleWrapper : public CAffectorWrapper
{
public:
    virtual ~CScaleWrapper();
    void setDynamicPropZScale(const float*, unsigned int);
    void getDynamicPropZScale(unsigned int&);
    void getDynamicPropYScale(unsigned int&);
    void getDynamicPropXScale(unsigned int&);
    void setDynamicPropYScale(const float*, unsigned int);
    void setDynamicPropXScale(const float*, unsigned int);
    CScaleWrapper(CResourceManager*);

    // fields
    unsigned char m_gap11A[0x6];
};

#endif
