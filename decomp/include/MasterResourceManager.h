#ifndef MASTERRESOURCEMANAGER_H
#define MASTERRESOURCEMANAGER_H

#include "RunicCore.h"
#include <vector>
#include <string>
class CResourceManager;
class CAnimationSet;
class CGenericModel;
class BatchModelRef;
class CollisionModelRef;
class CResourceSettings;
class CGraph;
class CSharedStash;
class CRoomPieceDataInformation;
// Partial state reached through +0xf0 by the editor particle controls.
struct CEditorParticlePreviewState { unsigned char unknown[0x540]; bool paused; };

namespace Ogre { class SceneManager; class RenderTarget; }
class CMissilePreloader;
namespace ParticleUniverse { class ParticleSystemManager; }
class CHierarchy;
class CEffectGroupManager;
class CCollisionModel;
class CParticlePreloader;
class CSettings;
class CEffectGroupManager;
class CGraphManager;
class CSpawnClassParser;
class CSoundManager;
class CSoundBankDataInformation;

// Partial: declarations from MasterResourceManager.cpp used by recovered TUs;
// hierarchy, settings, audio and paperdoll-scene pointers are placed (the original object is 400 bytes).
class CMasterResourceManager : public CRunicCore
{
    friend class CGameClient;
public:
    CMasterResourceManager(CSettings*);
    void loadParticles();
    void reloadResources();
    void addResourceLocation(const std::wstring& path, const std::string& type, bool recursive);
    void removeUnused();
    void removeAll();
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
    CCollisionModel* addCollisionModel(std::wstring name);
    CGenericModel* addBatchModel(CResourceManager* resources, Ogre::SceneManager* sceneManager, std::wstring name, bool& shared);

private:
    unsigned char m_Unrecovered10[0x48-0x10];
public:
    CGraphManager* m_pGraphManager;
private:
    unsigned char m_Unrecovered50[8];
public:
    CEffectGroupManager* m_effectGroups;
    CMissilePreloader* m_missilePreloader; // +0x60
private:
    CResourceSettings* m_resourceSettings;
    unsigned char m_Unrecovered70[8];
public:
    CSpawnClassParser* m_pSpawnClassParser; // +0x78
private:

public:
    CHierarchy* m_pHierarchy;

private:
    unsigned char m_Unrecovered88[0x8];

public:
    CSettings* m_pSettings;
    CSoundManager* m_pSoundManager;
private:
    unsigned char m_UnrecoveredA0[0x10];
public:
    Ogre::RenderTarget* m_renderTarget; // +0xb0; add/removeViewport calls
private:
    unsigned char m_UnrecoveredB8[8];
public:
    bool m_loadingResources; // +0xc0, CGame::frameStarted
private:
    unsigned char m_UnrecoveredC1[7];
public:
    Ogre::SceneManager* m_pDefaultSceneManager; // +0xc8, ResourceManager constructor fallback
private:
public:
    Ogre::SceneManager* m_pSceneManager;
private:
public:
    Ogre::SceneManager* m_renderBehindParticleScene; // +0xd8
    Ogre::SceneManager* m_automapScene; // +0xe0
public:
    CRoomPieceDataInformation* m_pRoomPieceInformation; // +0xe8
    union {
        CEditorParticlePreviewState* m_pParticlePreview; // existing legacy pause view; not the real class
        ParticleUniverse::ParticleSystemManager* m_pParticleSystemManager; // actual pointer, +0xf0
    };
public:
    CParticlePreloader* m_pParticlePreloader;
public:
    CSoundBankDataInformation* m_pSoundBankDataInformation;
private:
    std::vector<std::string> m_resourceLocations; // +0x108
    std::vector<CollisionModelRef*> m_collisionModels;
    std::vector<BatchModelRef*> m_batchModels;
    std::vector<CAnimationSet*> m_animationSets;
    CGraph* m_experienceGraph;
    CGraph* m_fameGraph;
    CSharedStash* m_stash;
    unsigned char m_gap180[0x10];
};

#endif
