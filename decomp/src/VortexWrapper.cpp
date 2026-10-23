#include "VortexWrapper.h"

CVortexWrapper::~CVortexWrapper()
{
}

#include "ParticlePropertyConversions.h"

namespace ParticleUniverse
{
class VortexAffector
{
public:
    DynamicAttribute* getRotationSpeed() const;
    void setRotationSpeed(DynamicAttribute* speed);
    void setRotationVector(const Ogre::Vector3& rotation);
};
}

CVortexWrapper::CVortexWrapper(CResourceManager* resources)
    : CAffectorWrapper(resources, "Vortex")
{
    reinterpret_cast<ParticleUniverse::VortexAffector*>(m_pAffector)->setRotationVector(
        Ogre::Vector3(0.0f, 1.0f, 0.0f));
}

void CVortexWrapper::getDynamicPropRotationSpeed(unsigned int& count)
{
    getArrayFromDynProp(
        reinterpret_cast<ParticleUniverse::VortexAffector*>(m_pAffector)->getRotationSpeed(),
        count);
}

void CVortexWrapper::setDynamicPropRotationSpeed(const float* values, unsigned int count)
{
    ParticleUniverse::DynamicAttribute* speed = getDynPropFromArray(values, count);
    reinterpret_cast<ParticleUniverse::VortexAffector*>(m_pAffector)->setRotationSpeed(speed);
}
