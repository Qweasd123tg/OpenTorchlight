#include "EmptyStrings.h"
#include "PlaneColliderWrapper.h"
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
