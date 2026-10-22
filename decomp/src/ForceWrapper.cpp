#include "EmptyStrings.h"
#include "ForceWrapper.h"

namespace ParticleUniverse {
class ForceAffector
{
public:
    enum ForceApplication { FA_AVERAGE, FA_ADD };
    void setForceVector(const Ogre::Vector3& force);
    void setForceApplication(ForceApplication application);
};
}

CForceWrapper::CForceWrapper(CResourceManager* resources, std::string name)
    : CAffectorWrapper(resources, name)
{
    reinterpret_cast<ParticleUniverse::ForceAffector*>(m_pAffector)->setForceVector(
        Ogre::Vector3(0.0f, 0.0f, 0.0f));
    reinterpret_cast<ParticleUniverse::ForceAffector*>(m_pAffector)->setForceApplication(
        ParticleUniverse::ForceAffector::FA_ADD);
    enablePositioning(false);
}

CForceWrapper::~CForceWrapper()
{
}

CForceWrapper::~CForceWrapper();
