#ifndef TEXTUREROTATEWRAPPER_H
#define TEXTUREROTATEWRAPPER_H

#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CTextureRotateWrapper : public CAffectorWrapper
{
public:
    virtual ~CTextureRotateWrapper();

    void setDynamicPropRotation(const float* dynamicPropertyValues,
                                unsigned int dynamicPropertyIndex);
    float* getDynamicPropRotation(unsigned int& dynamicPropertyValues);
    void setDynamicPropRotationSpeed(const float* dynamicPropertyValues,
                                     unsigned int dynamicPropertyIndex);
    float* getDynamicPropRotationSpeed(unsigned int& dynamicPropertyValues);

    CTextureRotateWrapper(CResourceManager* resourceManager);

    unsigned char m_textureRotatorState[0x6];
};

#endif
