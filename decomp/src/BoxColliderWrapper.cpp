#include "EmptyStrings.h"
#include "BoxColliderWrapper.h"

namespace ParticleUniverse {
class BoxCollider
{
public:
    void setWidth(float width);
    void setHeight(float height);
    void setDepth(float depth);
};
}

CBoxColliderWrapper::CBoxColliderWrapper(CResourceManager* resources)
    : CColliderWrapper(resources, "BoxCollider")
{
    m_bCollider11A = true;
    reinterpret_cast<ParticleUniverse::BoxCollider*>(m_pAffector)->setWidth(5.0f);
    reinterpret_cast<ParticleUniverse::BoxCollider*>(m_pAffector)->setHeight(2.5f);
    reinterpret_cast<ParticleUniverse::BoxCollider*>(m_pAffector)->setDepth(5.0f);
}
#include "AffectorWrapper.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ParticleWrapper.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "SphereColliderWrapper.h"
#include "UtilitiesMath.h"

void CBoxColliderWrapper::updateAlignedBox()
{
}

void CBoxColliderWrapper::positionUpdated(const Ogre::Vector3& position)
{
    CAffectorWrapper::positionUpdated(position);
}

CBoxColliderWrapper::~CBoxColliderWrapper()
{
}

// The non-virtual thunk is compiler-generated and has no standalone
// C++98 source definition. It is emitted alongside the existing
// CBoxColliderWrapper::~CBoxColliderWrapper() definition to adjust
// this by -256 before transferring control to that destructor.
