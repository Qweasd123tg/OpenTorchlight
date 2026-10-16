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
};
}

void CVortexWrapper::getDynamicPropRotationSpeed(unsigned int& count)
{
    getArrayFromDynProp(
        reinterpret_cast<ParticleUniverse::VortexAffector*>(m_pAffector)->getRotationSpeed(),
        count);
}
