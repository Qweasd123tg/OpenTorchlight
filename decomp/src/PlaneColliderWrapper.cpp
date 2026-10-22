#include "EmptyStrings.h"
#include "PlaneColliderWrapper.h"

namespace ParticleUniverse {
class PlaneCollider
{
public:
    void setNormal(const Ogre::Vector3& normal);
};
}

CPlaneColliderWrapper::CPlaneColliderWrapper(CResourceManager* resources)
    : CColliderWrapper(resources, "PlaneCollider")
{
    m_bCollider11A = true;
    m_vNormal = Ogre::Vector3(0.0f, 1.0f, 0.0f);
    void (CPositionableObject::*setDimensions)(float, float, float) = &CPositionableObject::setScale;
    (this->*setDimensions)(5.0f, 5.0f, 5.0f);
}

void CPlaneColliderWrapper::updatePlane()
{
    reinterpret_cast<ParticleUniverse::PlaneCollider*>(m_pAffector)->setNormal(m_vNormal);
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

void CPlaneColliderWrapper::orientationUpdated(Ogre::Matrix4 const& orientation)
{
}

void CPlaneColliderWrapper::positionUpdated(const Ogre::Vector3& position)
{
    CAffectorWrapper::positionUpdated(position);
    updatePlane();
}

CPlaneColliderWrapper::~CPlaneColliderWrapper()
{
}

// A non-virtual destructor thunk has no C++98 source-level definition.
// It is emitted automatically by the compiler for the already-defined
// CPlaneColliderWrapper destructor.
