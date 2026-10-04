#include "EmptyStrings.h"
#include "ParticleWrapper.h"
#include "DataGroup.h"
#include "ResourceManager.h"
#include "ParticleDynamicAttribute.h"
#include "ParticleUniverseConstants.h"

void CParticleWrapper::free()
{
}

namespace ParticleUniverse
{
    class ParticleSystem
    {
    public:
        void stop();
        void _resetBounds();
    };
}

void CParticleWrapper::stop()
{
    if (m_pParticleSystem) {
        m_bPlaying = false;
        m_pParticleSystem->stop();
        m_pParticleSystem->_resetBounds();
        BroadcastEvent(32);
    }
}

void CParticleWrapper::hideVisualSphereMesh()
{
    if (m_pVisualSphereNode == NULL)
        return;
    if (m_pSceneNode == NULL)
        return;
    if (m_pVisualSphereNode->getParentSceneNode() != NULL)
        m_pSceneNode->removeChild(m_pVisualSphereNode);
}

void CParticleWrapper::resourceFreeing()
{
}

void CParticleWrapper::resourceInit(CResourceManager* resourceManager, CDataGroup* dataGroup)
{
}

CParticleWrapper::~CParticleWrapper()
{
}
