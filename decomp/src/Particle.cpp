#include "EmptyStrings.h"
#include "Particle.h"
#include "BaseUnit.h"
#include "CollisionList.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

void CParticle::SetParticleDirection(const Ogre::Vector3&, const Ogre::Vector3&)
{
}

long long CParticle::updateLevelObject(float delta, Ogre::Camera* camera, const Ogre::Vector3& position)
{
    return updateLevelObject(delta, camera, position);
}

CParticle::~CParticle()
{
}
