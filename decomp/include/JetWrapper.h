#ifndef JETWRAPPER_H
#define JETWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CJetWrapper : public CAffectorWrapper
{
public:
    virtual ~CJetWrapper();
    void setDynamicPropAcceleration(const float*, unsigned int);
    void getDynamicPropAcceleration(unsigned int&);
    CJetWrapper(CResourceManager*);

    // fields
    unsigned char m_gap11A[0x6];
};

#endif
