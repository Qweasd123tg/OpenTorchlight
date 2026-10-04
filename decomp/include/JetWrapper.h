#ifndef JETWRAPPER_H
#define JETWRAPPER_H

#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CJetWrapper : public CAffectorWrapper
{
public:
    virtual ~CJetWrapper();

    void setDynamicPropAcceleration(const float *accelerationArray, unsigned int arrayIndex);
    void getDynamicPropAcceleration(unsigned int &accelerationArrayIndex);

    CJetWrapper(CResourceManager *resourceManager);

    unsigned char m_reserved11A[0x6];
};

#endif
