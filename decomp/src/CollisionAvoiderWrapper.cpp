#include "CollisionAvoiderWrapper.h"

CCollisionAvoiderWrapper::~CCollisionAvoiderWrapper()
{
}

#include <map>
#include <string>
#include "AffectorWrapper.h"

void CCollisionAvoiderWrapper::positionUpdated(const Ogre::Vector3& position)
{
    CAffectorWrapper::positionUpdated(position);
}

void CCollisionAvoiderWrapper::updateCircle()
{
}

namespace ParticleUniverse {
class CollisionAvoidanceAffector { public: void setRadius(float radius); };
}
CCollisionAvoiderWrapper::CCollisionAvoiderWrapper(CResourceManager* resources)
    : CColliderWrapper(resources, "CollisionAvoidance")
{
    m_bCollider11A = false;
    reinterpret_cast<ParticleUniverse::CollisionAvoidanceAffector*>(m_pAffector)->setRadius(1.0f);
}
