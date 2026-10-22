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
#include "MasterResourceManager.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

namespace ParticleUniverse {
class ParticleSystem {
public:
    virtual ~ParticleSystem();
    void stop();
};
class ParticleSystemManager {
public:
    void destroyParticleSystem(ParticleSystem*, Ogre::SceneManager*);
};
}

CParticleCache::~CParticleCache()
{
    mCameraShakeSystems.deleteAll();
    for (unsigned int i = 0; i < mParticleSceneNodes.size(); ++i) {
        if (mParticleSceneNodes[i]) {
            OGRE_UTILITIES::removeChildFromParentNode(mParticleSceneNodes[i]);
            mParticleSceneNodes[i]->detachAllObjects();
            m_pSceneManager->destroySceneNode(mParticleSceneNodes[i]);
            mParticleSceneNodes[i] = NULL;
        }
    }
    for (unsigned int i = 0; i < mActiveParticleSystems.size(); ++i) {
        mActiveParticleSystems[i]->stop();
        CMasterResourceManager::getSingleton()->m_pParticleSystemManager->destroyParticleSystem(
            mActiveParticleSystems[i], m_pSceneManager);
    }
    mActiveParticleSystems.clear();
    for (unsigned int i = 0; i < mSoundSampleIDs.size(); ++i)
        m_pSoundBank->stop(mSoundSampleIDs[i]);
    mSoundSampleIDs.clear();
}

void CParticleCache::playSounds(Ogre::SceneNode* sceneNode)
{
    if (m_pSoundBank)
        for (unsigned int i = 0; i < mSoundSampleIDs.size(); ++i)
            m_pSoundBank->playSample(mSoundSampleIDs[i], sceneNode, mSoundSampleVolumes[i], 0.0f, false);
}


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
