#include "EmptyStrings.h"
#include "ScaleWrapper.h"
#include "AffectorWrapper.h"
#include "ResourceManager.h"
#include "ParticleDynamicAttribute.h"
#include "ParticleUniverseConstants.h"
#include "ParticleWrapper.h"

void CScaleWrapper::getDynamicPropYScale(unsigned int& prop)
{
    extern void getArrayFromDynProp(
        ParticleUniverse::DynamicAttribute*,
        unsigned int&
    );

    getArrayFromDynProp(
        *reinterpret_cast<ParticleUniverse::DynamicAttribute **>(
            reinterpret_cast<char *>(
                *reinterpret_cast<void **>(
                    reinterpret_cast<char *>(this) + 0x110
                )
            ) + 0x160
        ),
        prop
    );
}

namespace ParticleUniverse
{
    class DynamicAttribute;

    class ScaleAffector
    {
    public:
        void setDynScaleY(DynamicAttribute *attribute);
        void setDynScaleX(DynamicAttribute*);
        void setDynScaleZ(DynamicAttribute*);
    };
}

extern ParticleUniverse::DynamicAttribute *getDynPropFromArray(
    float const *scale, unsigned int count);

void CScaleWrapper::setDynamicPropYScale(float const* scale, unsigned int count)
{
    reinterpret_cast<ParticleUniverse::ScaleAffector *>(m_pAffector)->setDynScaleY(
        getDynPropFromArray(scale, count));
}

CScaleWrapper::~CScaleWrapper()
{
}

// The non-virtual thunk to CScaleWrapper::~CScaleWrapper() is compiler-generated
// and has no independently definable C++98 source definition.

CScaleWrapper::CScaleWrapper(CResourceManager* resourceManager)
    : CAffectorWrapper(resourceManager, "Scale")
{
    float scale[2] = {0.0f, 1.0f};
    setDynamicPropXScale(scale, 2);
    setDynamicPropYScale(scale, 2);
    setDynamicPropZScale(scale, 2);
}

void CScaleWrapper::setDynamicPropZScale(const float* values, unsigned int count)
{
    reinterpret_cast<ParticleUniverse::ScaleAffector*>(m_pAffector)->setDynScaleZ(getDynPropFromArray(values, count));
}

void CScaleWrapper::setDynamicPropXScale(const float* values, unsigned int count)
{
    reinterpret_cast<ParticleUniverse::ScaleAffector*>(m_pAffector)->setDynScaleX(getDynPropFromArray(values, count));
}

void CScaleWrapper::getDynamicPropZScale(unsigned int& prop)
{
    extern void getArrayFromDynProp(
        ParticleUniverse::DynamicAttribute*,
        unsigned int&
    );

    getArrayFromDynProp(
        *reinterpret_cast<ParticleUniverse::DynamicAttribute **>(
            reinterpret_cast<char *>(
                *reinterpret_cast<void **>(
                    reinterpret_cast<char *>(this) + 0x110
                )
            ) + 0x168
        ),
        prop
    );
}

void CScaleWrapper::getDynamicPropXScale(unsigned int& prop)
{
    extern void getArrayFromDynProp(
        ParticleUniverse::DynamicAttribute*,
        unsigned int&
    );

    getArrayFromDynProp(
        *reinterpret_cast<ParticleUniverse::DynamicAttribute **>(
            reinterpret_cast<char *>(
                *reinterpret_cast<void **>(
                    reinterpret_cast<char *>(this) + 0x110
                )
            ) + 0x158
        ),
        prop
    );
}
