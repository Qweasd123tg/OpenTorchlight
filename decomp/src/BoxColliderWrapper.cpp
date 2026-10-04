#include "EmptyStrings.h"
#include "BoxColliderWrapper.h"
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
