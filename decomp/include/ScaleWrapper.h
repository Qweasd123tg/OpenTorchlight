#ifndef SCALEWRAPPER_H
#define SCALEWRAPPER_H

#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CScaleWrapper : public CAffectorWrapper
{
public:
    virtual ~CScaleWrapper();

    void setDynamicPropZScale(float const* scale, unsigned int count);
    void getDynamicPropZScale(unsigned int& prop);
    void getDynamicPropYScale(unsigned int& prop);
    void getDynamicPropXScale(unsigned int& prop);
    void setDynamicPropYScale(float const* scale, unsigned int count);
    void setDynamicPropXScale(float const* scale, unsigned int count);

    CScaleWrapper(CResourceManager* resourceManager);

    unsigned char m_padding11A[6];
};

#endif
