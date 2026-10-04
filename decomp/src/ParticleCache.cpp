#include "EmptyStrings.h"
#include "ParticleCache.h"
#include "CameraShake.h"
#include "RunicCore.h"
#include "SoundBank.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreGpuCommandBufferFlush.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "UtilitiesMath.h"

void CParticleCache::playCameraShakes(const Ogre::Vector3& shakeDirection)
{
    for (unsigned int i = 0; i < mCameraShakeSystems.size(); ++i)
        reinterpret_cast<CCameraShake *>(mCameraShakeSystems[i])->startCameraShake(shakeDirection, false);
}

CParticleCache::CParticleCache(Ogre::SceneManager* sceneManager, CSoundBank* soundBank)
    : CRunicCore(),
      mActiveParticleSystems(2),
      mParticleSceneNodes(2),
      mSoundSampleIDs(1),
      mSoundSampleVolumes(1),
      m_pRootSceneNode(0),
      mParticleSystemTemplateNames(2),
      mParticleTechniqueTemplateNames(2),
      mParticleEmitterTemplateNames(2),
      mCameraShakeSystems(1),
      m_pSceneManager(sceneManager),
      m_pSoundBank(soundBank)
{
}
