#ifndef TEXTUREANIMATEWRAPPER_H
#define TEXTUREANIMATEWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CTextureAnimateWrapper : public CAffectorWrapper
{
public:
    virtual ~CTextureAnimateWrapper();
    void setDynamicPropAnimationSpeed(const float*, unsigned int);
    void getDynamicPropAnimationSpeed(unsigned int&);
    CTextureAnimateWrapper(CResourceManager*);

    // fields
    unsigned char m_gap11A[0x6];
};

#endif
