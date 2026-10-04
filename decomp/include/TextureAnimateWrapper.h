#ifndef TEXTUREANIMATEWRAPPER_H
#define TEXTUREANIMATEWRAPPER_H

#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CTextureAnimateWrapper : public CAffectorWrapper
{
public:
    virtual ~CTextureAnimateWrapper();

    void setDynamicPropAnimationSpeed(const float* dynamicPropertyValues,
                                      unsigned int dynamicPropertyIndex);
    void getDynamicPropAnimationSpeed(unsigned int& dynamicPropertyIndex);

    CTextureAnimateWrapper(CResourceManager* resourceManager);

    // Fields
    unsigned char m_textureAnimatorData[6];
};

#endif
