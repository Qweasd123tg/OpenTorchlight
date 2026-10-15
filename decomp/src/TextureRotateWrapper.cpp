#include "EmptyStrings.h"
#include "TextureRotateWrapper.h"
#include "AffectorWrapper.h"
#include "ResourceManager.h"

CTextureRotateWrapper::~CTextureRotateWrapper()
{
}

CTextureRotateWrapper::CTextureRotateWrapper(CResourceManager* resourceManager)
    : CAffectorWrapper(resourceManager, "TextureRotator")
{
}
#include "ParticlePropertyConversions.h"
namespace ParticleUniverse {
class TextureRotator {
public:
    void setRotation(DynamicAttribute*);
    void setRotationSpeed(DynamicAttribute*);
    DynamicAttribute* getRotation() const;
    DynamicAttribute* getRotationSpeed() const;
};
}


void CTextureRotateWrapper::setDynamicPropRotation(const float* values, unsigned int count)
{
    reinterpret_cast<ParticleUniverse::TextureRotator*>(m_pAffector)->setRotation(getDynPropFromArray(values, count));
}

float* CTextureRotateWrapper::getDynamicPropRotation(unsigned int& count)
{
    return getArrayFromDynProp(reinterpret_cast<ParticleUniverse::TextureRotator*>(m_pAffector)->getRotation(), count);
}

void CTextureRotateWrapper::setDynamicPropRotationSpeed(const float* values, unsigned int count)
{
    reinterpret_cast<ParticleUniverse::TextureRotator*>(m_pAffector)->setRotationSpeed(getDynPropFromArray(values, count));
}

float* CTextureRotateWrapper::getDynamicPropRotationSpeed(unsigned int& count)
{
    return getArrayFromDynProp(reinterpret_cast<ParticleUniverse::TextureRotator*>(m_pAffector)->getRotationSpeed(), count);
}
