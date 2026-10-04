#ifndef PARTICLECACHE_H
#define PARTICLECACHE_H

#include <string>

#include "RunicCore.h"
#include "SoundBank.h"
#include "TArrayList.h"

namespace Ogre
{
    class SceneManager;
    class SceneNode;
    class Vector3;
}

namespace ParticleUniverse
{
    class ParticleSystem;
}

class CParticleCache : public CRunicCore
{
public:
    CParticleCache(Ogre::SceneManager* sceneManager, CSoundBank* soundBank);
    virtual ~CParticleCache();

    void playCameraShakes(const Ogre::Vector3& shakeDirection);
    void playSounds(Ogre::SceneNode* sceneNode);

    TArrayList<ParticleUniverse::ParticleSystem*> mActiveParticleSystems;
    TArrayList<Ogre::SceneNode*> mParticleSceneNodes;
    TArrayList<int> mSoundSampleIDs;
    TArrayList<float> mSoundSampleVolumes;

    Ogre::SceneNode* m_pRootSceneNode;

    TArrayList<std::wstring*> mParticleSystemTemplateNames;
    TArrayList<std::wstring*> mParticleTechniqueTemplateNames;
    TArrayList<std::wstring*> mParticleEmitterTemplateNames;

    TArrayList<ParticleUniverse::ParticleSystem*> mCameraShakeSystems;

    Ogre::SceneManager* m_pSceneManager;
    CSoundBank* m_pSoundBank;
};

#endif
