#ifndef MASTERRESOURCEMANAGER_H
#define MASTERRESOURCEMANAGER_H

#include "RunicCore.h"
#include <vector>
#include <string>
class CAnimationSet;
class CGenericModel;
class BatchModelRef;
class CollisionModelRef;
class CResourceSettings;
class CGraph;
class CSharedStash;

namespace Ogre { class SceneManager; }
class CHierarchy;
class CEffectGroupManager;
class CCollisionModel;
class CParticlePreloader;
class CSettings;
class CEffectGroupManager;
class CGraphManager;
class CSoundManager;
class CSoundBankDataInformation;

// Partial: declarations from MasterResourceManager.cpp used by recovered TUs;
// hierarchy, settings, audio and paperdoll-scene pointers are placed (the original object is 400 bytes).
class CMasterResourceManager : public CRunicCore
{
public:
    void destroyStash();
    CollisionModelRef* getCollisionModel(CCollisionModel* model);
    BatchModelRef* getBatchModel(CGenericModel* model);
    void removeBatchModel(CGenericModel* model);
    CAnimationSet* getAnimationSet(CAnimationSet* model);
    void removeAnimationSet(CAnimationSet* model);
    void reloadSoundBankData();
    int getMaxFameLevel();
    int getMaxLevel();
    CollisionModelRef* getCollisionModel(std::wstring name);
    BatchModelRef* getBatchModel(std::wstring name);
    void createParticleReloader();
    void addAnimationSet(CAnimationSet* animations);
    CAnimationSet* getAnimationSet(std::wstring name);
    virtual ~CMasterResourceManager();

    static CMasterResourceManager* getSingleton();
    int experienceGate(int);
    int fameGate(int);
    void removeCollisionModel(CCollisionModel* model);

private:
    unsigned char m_Unrecovered10[0x48-0x10];
public:
    CGraphManager* m_pGraphManager;
private:
    unsigned char m_Unrecovered50[8];
public:
    CEffectGroupManager* m_effectGroups;
private:
    unsigned char m_Unrecovered60[8];
    CResourceSettings* m_resourceSettings;
    unsigned char m_Unrecovered70[0x10];

public:
    CHierarchy* m_pHierarchy;

private:
    unsigned char m_Unrecovered88[0x8];

public:
    CSettings* m_pSettings;
    CSoundManager* m_pSoundManager;
private:
    unsigned char m_UnrecoveredA0[0xd0-0xa0];
public:
    Ogre::SceneManager* m_pSceneManager;
private:
    unsigned char m_UnrecoveredD8[0xf8-0xd8];
public:
    CParticlePreloader* m_pParticlePreloader;
public:
    CSoundBankDataInformation* m_pSoundBankDataInformation;
private:
    unsigned char m_gap108[0x18];
    std::vector<CollisionModelRef*> m_collisionModels;
    std::vector<BatchModelRef*> m_batchModels;
    std::vector<CAnimationSet*> m_animationSets;
    CGraph* m_experienceGraph;
    CGraph* m_fameGraph;
    CSharedStash* m_stash;
    unsigned char m_gap180[0x10];
};

#endif
