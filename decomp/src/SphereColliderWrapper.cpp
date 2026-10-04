#include "EmptyStrings.h"
#include "SphereColliderWrapper.h"
#include "AffectorWrapper.h"
#include "ColliderWrapper.h"
#include "ResourceManager.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ParticleWrapper.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

void CSphereColliderWrapper::updateCircle()
{
}

void CSphereColliderWrapper::positionUpdated(const Ogre::Vector3& position)
{
    CAffectorWrapper::positionUpdated(position);
}

CSphereColliderWrapper::~CSphereColliderWrapper()
{
}

// The non-virtual thunk has no C++98 source-level definition. It is
// compiler-generated for the already-defined
// CSphereColliderWrapper destructor.

CSphereColliderWrapper::CSphereColliderWrapper(CResourceManager* resourceManager)
    : CColliderWrapper(resourceManager, "SphereCollider")
{
    *(bool *)(reinterpret_cast<char *>(this) + 0x11a) = true;
}
