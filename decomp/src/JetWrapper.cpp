#include "EmptyStrings.h"
#include "JetWrapper.h"
#include "AffectorWrapper.h"
#include "ResourceManager.h"
#include "ParticleDynamicAttribute.h"
#include "ParticleUniverseConstants.h"
#include "ParticleWrapper.h"

void CJetWrapper::getDynamicPropAcceleration(unsigned int& accelerationArrayIndex)
{
    extern void getArrayFromDynProp(ParticleUniverse::DynamicAttribute*, unsigned int&);

    getArrayFromDynProp(
        *reinterpret_cast<ParticleUniverse::DynamicAttribute **>(
            *reinterpret_cast<char **>(reinterpret_cast<char *>(this) + 0x110) + 0x158),
        accelerationArrayIndex);
}

CJetWrapper::~CJetWrapper()
{
}

/* The non-virtual thunk to CJetWrapper::~CJetWrapper() is compiler-generated. */

CJetWrapper::CJetWrapper(CResourceManager* resourceManager)
    : CAffectorWrapper(resourceManager, "Jet")
{
}
