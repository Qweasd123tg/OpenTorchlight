#include "EmptyStrings.h"
#include "TextureAnimateWrapper.h"
#include "AffectorWrapper.h"
#include "ResourceManager.h"
#include "ParticleDynamicAttribute.h"
#include "ParticleUniverseConstants.h"
#include "ParticleWrapper.h"

namespace ParticleUniverse {
class DynamicAttribute;
class TextureAnimator {
public:
    void setAnimationSpeed(DynamicAttribute *dynamicPropertyAnimationSpeed);
};
}

extern ParticleUniverse::DynamicAttribute *getDynPropFromArray(
    const float *dynamicPropertyValues,
    unsigned int dynamicPropertyIndex);

void CTextureAnimateWrapper::setDynamicPropAnimationSpeed(
    const float* dynamicPropertyValues,
    unsigned int dynamicPropertyIndex)
{
    reinterpret_cast<ParticleUniverse::TextureAnimator *>(m_pAffector)
        ->setAnimationSpeed(getDynPropFromArray(
            dynamicPropertyValues, dynamicPropertyIndex));
}

CTextureAnimateWrapper::~CTextureAnimateWrapper()
{
}

// The non-virtual thunk is compiler-generated and has no C++98 source definition.

CTextureAnimateWrapper::CTextureAnimateWrapper(CResourceManager* resourceManager)
    : CAffectorWrapper(resourceManager, "TextureAnimator")
{
}
