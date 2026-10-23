#include "AnimationSet.h"
#include "BatchModelRef.h"
#include "CollisionModel.h"
#include "CollisionModelRef.h"
#include "GenericModel.h"
#include "Graph.h"
#include "MasterResourceManager.h"
#include "ParticlePreloader.h"
#include "SharedStash.h"
#include "SoundBankDataInformation.h"
#include "SoundManager.h"
#include "EmptyStrings.h"
#include "GameVariables.h"
#include "BatchModelRef.h"
#include "CollisionModelRef.h"
#include "MasterResourceManager.h"
#include "RunicCore.h"

CMasterResourceManager* CMasterResourceManager::getSingleton()
{
    return (CMasterResourceManager*)m_pMasterResourceManager;
}

BatchModelRef::BatchModelRef()
    : CRunicCore(), m_pBatchModel(NULL)
{
}

CollisionModelRef::CollisionModelRef()
    : CRunicCore(), m_pCollisionModel(NULL)
{
}

BatchModelRef::~BatchModelRef()
{
    if (m_pBatchModel)
    {
        delete m_pBatchModel;
        m_pBatchModel = 0;
    }
}

CollisionModelRef::~CollisionModelRef()
{
    if (m_pCollisionModel) { delete m_pCollisionModel; m_pCollisionModel = NULL; }
}


// Imported source candidates; historical status is not fresh acceptance.
void CMasterResourceManager::destroyStash()
{
    if (m_stash) { delete m_stash; m_stash = NULL; }
    m_stash = NULL;
}

CollisionModelRef* CMasterResourceManager::getCollisionModel(CCollisionModel* model)
{
    for (unsigned int i = 0; i < m_collisionModels.size(); ++i)
        if (m_collisionModels[i]->m_pCollisionModel == model) return m_collisionModels[i];
    return NULL;
}

void CMasterResourceManager::removeCollisionModel(CCollisionModel* model)
{
    CollisionModelRef* found = getCollisionModel(model);
    if (found) --found->m_referenceCount;
}

BatchModelRef* CMasterResourceManager::getBatchModel(CGenericModel* model)
{
    for (unsigned int i = 0; i < m_batchModels.size(); ++i)
        if (m_batchModels[i]->m_pBatchModel == model) return m_batchModels[i];
    return NULL;
}

void CMasterResourceManager::removeBatchModel(CGenericModel* model)
{
    BatchModelRef* found = getBatchModel(model);
    if (found) --found->m_referenceCount;
}

CAnimationSet* CMasterResourceManager::getAnimationSet(CAnimationSet* model)
{
    for (unsigned int i = 0; i < m_animationSets.size(); ++i)
        if (m_animationSets[i] == model) return m_animationSets[i];
    return NULL;
}

void CMasterResourceManager::removeAnimationSet(CAnimationSet* model)
{
    CAnimationSet* found = getAnimationSet(model);
    if (found) --found->m_nAnimationCount;
}

void CMasterResourceManager::reloadSoundBankData()
{
    if (m_pSoundManager && m_pSoundBankDataInformation) {
        m_pSoundManager->stopAllSounds();
        m_pSoundBankDataInformation->reload(m_resourceSettings);
    }
}

int CMasterResourceManager::getMaxFameLevel()
{
    return m_fameGraph->getControlPoints();
}

int CMasterResourceManager::fameGate(int level)
{
    if (!level) return 0;
    if (level > m_fameGraph->getControlPoints()) level = m_fameGraph->getControlPoints();
    return static_cast<int>(m_fameGraph->getValue(static_cast<float>(level), 0));
}

int CMasterResourceManager::getMaxLevel()
{
    return m_experienceGraph->getControlPoints();
}

int CMasterResourceManager::experienceGate(int level)
{
    if (!level) return 0;
    if (level > m_experienceGraph->getControlPoints()) level = m_experienceGraph->getControlPoints();
    return static_cast<int>(m_experienceGraph->getValue(static_cast<float>(level), 0));
}

CollisionModelRef* CMasterResourceManager::getCollisionModel(std::wstring name)
{
    for (unsigned int i = 0; i < m_collisionModels.size(); ++i)
        if (m_collisionModels[i]->m_sUnknown20 == name) return m_collisionModels[i];
    return NULL;
}

BatchModelRef* CMasterResourceManager::getBatchModel(std::wstring name)
{
    for (unsigned int i = 0; i < m_batchModels.size(); ++i)
        if (m_batchModels[i]->m_sBatchModelName == name) return m_batchModels[i];
    return NULL;
}

void CMasterResourceManager::createParticleReloader()
{
    if (!m_pParticlePreloader) m_pParticlePreloader = new CParticlePreloader(m_resourceSettings);
}

void CMasterResourceManager::addAnimationSet(CAnimationSet* animations)
{
    m_animationSets.push_back(animations);
}

CAnimationSet* CMasterResourceManager::getAnimationSet(std::wstring name)
{
    for (unsigned int i = 0; i < m_animationSets.size(); ++i)
        if (m_animationSets[i]->m_wsName == name) return m_animationSets[i];
    return NULL;
}

#include "FileSystem.h"

void CMasterResourceManager::removeUnused()
{
    for (int i = 0; i < static_cast<int>(m_collisionModels.size()); ++i) {
        if (m_collisionModels[i]->m_referenceCount == 0) {
            delete m_collisionModels[i];
            m_collisionModels[i] = NULL;
            m_collisionModels[i] = m_collisionModels[m_collisionModels.size() - 1];
            m_collisionModels.pop_back();
            --i;
        }
    }
    for (int i = 0; i < static_cast<int>(m_batchModels.size()); ++i) {
        if (m_batchModels[i]->m_referenceCount == 0) {
            delete m_batchModels[i];
            m_batchModels[i] = NULL;
            m_batchModels[i] = m_batchModels[m_batchModels.size() - 1];
            m_batchModels.pop_back();
            --i;
        }
    }
    for (int i = 0; i < static_cast<int>(m_animationSets.size()); ++i) {
        if (m_animationSets[i]->m_nAnimationCount == 0) {
            delete m_animationSets[i];
            m_animationSets[i] = NULL;
            m_animationSets[i] = m_animationSets[m_animationSets.size() - 1];
            m_animationSets.pop_back();
            --i;
        }
    }
}

void CMasterResourceManager::removeAll()
{
    for (unsigned int i = 0; i < m_collisionModels.size(); ++i) {
        if (m_collisionModels[i]) {
            delete m_collisionModels[i];
            m_collisionModels[i] = NULL;
        }
    }
    m_collisionModels.clear();
    for (unsigned int i = 0; i < m_batchModels.size(); ++i) {
        if (m_batchModels[i]) {
            delete m_batchModels[i];
            m_batchModels[i] = NULL;
        }
    }
    m_batchModels.clear();
    for (unsigned int i = 0; i < m_animationSets.size(); ++i) {
        if (m_animationSets[i]) {
            delete m_animationSets[i];
            m_animationSets[i] = NULL;
        }
    }
    m_animationSets.clear();
}

CGenericModel* CMasterResourceManager::addBatchModel(CResourceManager* resources, Ogre::SceneManager* scene, std::wstring name, bool& shared)
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(name, info, false, true, false);
    if (!info.m_bExists)
        return NULL;
    shared = true;
    BatchModelRef* found = getBatchModel(name);
    if (found) {
        ++found->m_referenceCount;
        return found->m_pBatchModel;
    }
    CGenericModel* model = new CGenericModel(resources, NULL, name, EMPTY_WSTRING, false);
    if (model->getAnimationCount()) {
        shared = false;
        return model;
    }
    BatchModelRef* reference = new BatchModelRef;
    m_batchModels.push_back(reference);
    reference->m_pBatchModel = model;
    reference->m_referenceCount = 1;
    reference->m_sBatchModelName = name;
    return reference->m_pBatchModel;
}

CCollisionModel* CMasterResourceManager::addCollisionModel(std::wstring name)
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(name, info, false, true, false);
    if (!info.m_bExists)
        return NULL;
    CollisionModelRef* found = getCollisionModel(name);
    if (found) {
        ++found->m_referenceCount;
        return found->m_pCollisionModel;
    }
    CollisionModelRef* reference = new CollisionModelRef;
    m_collisionModels.push_back(reference);
    reference->m_pCollisionModel = new CCollisionModel(m_pDefaultSceneManager, name);
    reference->m_referenceCount = 1;
    reference->m_sUnknown20 = name;
    return reference->m_pCollisionModel;
}

#include "ParticlePreloader.h"
#include "MissilePreloader.h"
#include "EffectGroupManager.h"
#include "GraphManager.h"
#include "SkillParser.h"
#include "SpawnClassParser.h"
#include "StringUtilities.h"
#include <OgreResourceGroupManager.h>

void CMasterResourceManager::loadParticles()
{
    if (m_pParticleSystemManager && m_pSettings && m_pSoundManager && m_pDefaultSceneManager) {
        createParticleReloader();
        m_pParticlePreloader->ReloadParticles();
    }
}

void CMasterResourceManager::reloadResources()
{
    m_pMasterResourceManager->m_pGraphManager->reload();
    m_pMasterResourceManager->m_effectGroups->reload();
    m_pMasterResourceManager->m_pParticlePreloader->ReloadParticles();
    m_pMasterResourceManager->m_missilePreloader->reloadMissiles();
    CSkillParser::reloadSkills();
    m_pMasterResourceManager->m_pSpawnClassParser->reloadFromDirectory(L"media/SpawnClasses/");
    m_pMasterResourceManager->reloadSoundBankData();
    m_experienceGraph = m_pGraphManager->getGraph(L"EXPERIENCEGATE");
    m_fameGraph = m_pGraphManager->getGraph(L"FAMEGATE");
}

void CMasterResourceManager::addResourceLocation(const std::wstring& path, const std::string& group, bool reload)
{
    std::string location = STRINGS::StringConvertToUTF8(std::wstring(STRINGS::StringUpper(path).c_str()));
    bool found = false;
    for (int i = 0; i < static_cast<int>(m_resourceLocations.size()); ++i)
        if (m_resourceLocations[i] == location) { found = true; break; }
    if (found && !reload) return;
    if (!found) m_resourceLocations.push_back(location);
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(location, "FileSystem", group.empty() ? Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME : group, true);
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(group.empty() ? Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME : group);
}

#include "Settings.h"
#include "ResourceSettings.h"
#include "FileSystem.h"
#include "StringTranslate.h"
#include "SteamStats.h"
#include "Achievements.h"
#include "Achievement.h"
#include "EffectDefines.h"
#include "Hierarchy.h"
#include "UnitThemes.h"
#include "Recipes.h"
#include "Sets.h"
#include "RoomPieceDataInformation.h"
#include "Cinematics.h"
#include "RandomNames.h"
#include "GameGlobals.h"
#include "UnitResourceList.h"
#include "DungeonManager.h"
#include "GameSpeed.h"
#include "ParticleUniversePlugin.h"
#include <OgreRoot.h>
#include <ParticleUniverseSystemManager.h>

CMasterResourceManager::CMasterResourceManager(CSettings* settings)
    : m_translate(NULL), m_globals(NULL), m_unitThemes(NULL), m_recipes(NULL),
      m_sets(NULL), m_cinematics(NULL), m_randomNames(NULL), m_pGraphManager(NULL),
      m_dungeons(NULL), m_effectGroups(NULL), m_missilePreloader(NULL),
      m_resourceSettings(NULL), m_skillParser(NULL), m_pSpawnClassParser(NULL),
      m_pHierarchy(NULL), m_pSettings(settings), m_pSoundManager(NULL),
      m_console(NULL), m_gameSpeed(NULL), m_fileSystem(NULL),
      m_loadingResources(false), m_flagC1(true), m_pDefaultSceneManager(NULL),
      m_pRoomPieceInformation(NULL), m_pParticleSystemManager(NULL),
      m_pParticlePreloader(NULL), m_pSoundBankDataInformation(NULL),
      m_experienceGraph(NULL), m_fameGraph(NULL), m_stash(NULL),
      m_steamStats(NULL), m_achievements(NULL)
{
    m_pMasterResourceManager = this;
    m_fileSystem = new CFileSystem(m_pSettings->m_pCmdLineParser->GetStringParam(L"COMPRESS", EMPTY_WSTRING) != EMPTY_WSTRING);
    m_resourceSettings = new CResourceSettings;
    m_resourceSettings->LoadSettings(L"");
    m_translate = new CStringTranslate(m_resourceSettings->GetString(KRESOURCESETTING_S_TRANSLATE_FILE));
    m_steamStats = new CSteamStats;
    m_achievements = new CAchievements;
    parseEffects();
    m_pHierarchy = new CHierarchy(L"media/unittypes.hie");
    m_unitThemes = new CUnitThemes(L"media/unitthemes/");
    m_recipes = new CRecipes(L"media/recipes/");
    m_cinematics = new CCinematics(L"media/cinematics/");
    m_randomNames = OGRE_NEW_T(CRandomNames, Ogre::MEMCATEGORY_GENERAL)(L"media/randomnames.dat");
    m_globals = new CGameGlobals(L"media/globals.dat");
    m_unitResourceList = new CUnitResourceList;
    m_unitResourceList->InitUnitResourceList(m_resourceSettings, m_pHierarchy);
    m_pGraphManager = new CGraphManager(m_resourceSettings->GetString(KRESOURCESETTING_S_GRAPH_MANAGER));
    m_experienceGraph = m_pGraphManager->getGraph(L"EXPERIENCEGATE");
    m_fameGraph = m_pGraphManager->getGraph(L"FAMEGATE");
    m_effectGroups = new CEffectGroupManager(m_resourceSettings->GetString(KRESOURCESETTING_S_AFFIXES_FOLDER).c_str());
    m_sets = new CSets(L"media/sets/", m_effectGroups);
    m_pRoomPieceInformation = new CRoomPieceDataInformation(m_resourceSettings);
    m_pSoundBankDataInformation = new CSoundBankDataInformation(m_resourceSettings);
    m_dungeons = new CDungeonManager(L"media/dungeons/");
    m_skillParser = new CSkillParser(m_resourceSettings);
    m_missilePreloader = new CMissilePreloader(m_resourceSettings);
    m_pSpawnClassParser = new CSpawnClassParser;
    m_gameSpeed = new CGameSpeed(L"media/graphs/camerashakes/DecelerateGameSpeed.dat", L"media/graphs/camerashakes/DecelerateGameSpeed.dat");
    m_stash = new CSharedStash(L"sharedstash.bin", L"sharedstashh.bin");
    m_steamStats->update(0.0f);
    m_steamStats->update(0.0f);
    if (m_fileSystem->getNumberOfMods())
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(26))->forceComplete();
    if (m_fileSystem->getNumberOfMods() > 4)
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(27))->forceComplete();
    if (m_fileSystem->getNumberOfMods() > 9)
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(28))->forceComplete();
    ParticleUniverse::ParticleUniversePlugin* plugin = new ParticleUniverse::ParticleUniversePlugin;
    Ogre::Root::getSingleton().installPlugin(plugin);
    m_pParticleSystemManager = ParticleUniverse::ParticleSystemManager::getSingletonPtr();
}

CMasterResourceManager::~CMasterResourceManager()
{
    for (unsigned int i = 0; i < m_collisionModels.size(); ++i) {
        if (m_collisionModels[i]) {
            delete m_collisionModels[i];
            m_collisionModels[i] = NULL;
        }
    }
    for (unsigned int i = 0; i < m_batchModels.size(); ++i) {
        if (m_batchModels[i]) {
            delete m_batchModels[i];
            m_batchModels[i] = NULL;
        }
    }
    for (unsigned int i = 0; i < m_animationSets.size(); ++i) {
        if (m_animationSets[i]) {
            delete m_animationSets[i];
            m_animationSets[i] = NULL;
        }
    }
    m_animationSets.clear();
    if (m_achievements) { delete m_achievements; m_achievements = NULL; }
    if (m_steamStats) { delete m_steamStats; m_steamStats = NULL; }
    if (m_stash) { delete m_stash; m_stash = NULL; }
    if (m_missilePreloader) { delete m_missilePreloader; m_missilePreloader = NULL; }
    if (m_pParticlePreloader) { delete m_pParticlePreloader; m_pParticlePreloader = NULL; }
    if (m_pHierarchy) { delete m_pHierarchy; m_pHierarchy = NULL; }
    if (m_unitResourceList) { delete m_unitResourceList; m_unitResourceList = NULL; }
    if (m_resourceSettings) {
        m_resourceSettings->SaveSettings(L"");
        if (m_resourceSettings) { delete m_resourceSettings; m_resourceSettings = NULL; }
    }
    if (m_pRoomPieceInformation) { delete m_pRoomPieceInformation; m_pRoomPieceInformation = NULL; }
    if (m_pSoundBankDataInformation) { delete m_pSoundBankDataInformation; m_pSoundBankDataInformation = NULL; }
    if (m_pSpawnClassParser) { delete m_pSpawnClassParser; m_pSpawnClassParser = NULL; }
    if (m_pGraphManager) { delete m_pGraphManager; m_pGraphManager = NULL; }
    if (m_skillParser) { delete m_skillParser; m_skillParser = NULL; }
    if (m_effectGroups) { delete m_effectGroups; m_effectGroups = NULL; }
    if (m_gameSpeed) { delete m_gameSpeed; m_gameSpeed = NULL; }
    if (m_unitThemes) { delete m_unitThemes; m_unitThemes = NULL; }
    if (m_recipes) { delete m_recipes; m_recipes = NULL; }
    if (m_cinematics) { delete m_cinematics; m_cinematics = NULL; }
    if (m_sets) { delete m_sets; m_sets = NULL; }
    if (m_randomNames) { OGRE_DELETE_T(m_randomNames, CRandomNames, Ogre::MEMCATEGORY_GENERAL); m_randomNames = NULL; }
    if (m_translate) { delete m_translate; m_translate = NULL; }
    if (m_globals) { delete m_globals; m_globals = NULL; }
    if (m_fileSystem) { delete m_fileSystem; m_fileSystem = NULL; }
    m_pMasterResourceManager = NULL;
}
