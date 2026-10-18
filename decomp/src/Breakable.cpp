#include "EmptyStrings.h"
#include "Breakable.h"
#include "Character.h"
#include "CollisionModel.h"
#include "DataGroup.h"
#include "FileUtilities.h"
#include "GenericModel.h"
#include "Level.h"
#include "LevelTemplateData.h"
#include "MasterResourceManager.h"
#include "Particle.h"
#include "ParticlePreloader.h"
#include "Skill.h"
#include "SkillManager.h"
#include "SoundBank.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "StringUtilities.h"
#include <OgreEntity.h>

CBreakable::CBreakable(CResourceManager* resources)
    : CItem(resources), m_interacted(false), m_pUnitModel(NULL),
      m_collisionModel(NULL), m_particle(NULL)
{
    if (!m_pSoundBank)
    {
        CSoundManager* sound = NULL;
        if (m_pResourceManager)
            sound = CMasterResourceManager::getSingleton()->m_pSoundManager;
        m_pSoundBank = new CSoundBank(*sound, false);
    }
}

CBreakable::~CBreakable()
{
    if (m_pUnitModel)
    {
        delete m_pUnitModel;
        m_pUnitModel = NULL;
    }
    CMasterResourceManager::getSingleton()->removeCollisionModel(m_collisionModel);
    if (m_pSoundBank)
    {
        delete m_pSoundBank;
        m_pSoundBank = NULL;
    }
    if (m_particle)
    {
        delete m_particle;
        m_particle = NULL;
    }
}

void CBreakable::update(Ogre::Camera* camera, const Ogre::Vector3& position, float elapsed)
{
    CItem::update(camera, position, elapsed);
    if (m_bInActiveRange && !m_bItemFlag218)
    {
        if (m_bBlocksPath)
            m_bPathingFlag19C = true;
    }
    else if (m_bBlocksPath)
        m_bPathingFlag19C = false;
}

void CBreakable::setActiveInLevel(bool active)
{
    if (m_bItemFlag1F0)
    {
        updateCullingBounds();
        setVisible(active);
        if (active)
        {
            snapToGround();
            addToAvoidanceMap(*(m_pResourceManager ? m_pResourceManager->getLevel() : NULL));
        }
        else
            removeFromAvoidanceMap(*(m_pResourceManager ? m_pResourceManager->getLevel() : NULL));
    }
}

bool CBreakable::interact(CCharacter* character)
{
    if (m_interacted)
        return false;
    m_interacted = true;
    CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
    if (!level)
        return false;
    m_bItemFlag1F0 = false;
    removeFromAvoidanceMap(*level);
    int index = selectRandomSkill();
    CSkill* skill = index == -1 ? NULL : m_pSkillManager->getSkillByIndex(index);
    if (skill)
    {
        bool blocks = false;
        if (m_bBlocksPath)
        {
            blocks = m_bPathingFlag19C;
            m_bPathingFlag19C = false;
        }
        Ogre::Vector3 target = character ? character->getPosition(true) : getPosition(true);
        const Ogre::Quaternion& orientation = m_pSceneNode->getOrientation();
        Ogre::Vector3 source = getPosition(true) + Ogre::Vector3(0.0f, -m_fBaseUnitValue194, 0.0f);
        if (m_pSkillManager->executeSkill(skill, this, SKILL_ACTIVATION_ANY, source,
                                        orientation, target, character) && character &&
            character->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x1c)) &&
            skill->m_skillType != 2)
        {
            if (character->m_levelSound)
                character->m_levelSound->queueGlobalSample(0x36, 1.0f, 1.0f);
            character->incrementJournalStatistic(static_cast<EJournalStatistic>(0xa), 1);
        }
        if (m_bBlocksPath)
            m_bPathingFlag19C = blocks;
    }
    if (m_particle)
    {
        m_particle->setPosition(getPosition(true) + m_vUp * 0.1f);
        m_particle->Start();
    }
    m_pSoundBank->playSample(0, m_pSceneNode, 0.0f, 0.0f, false);
    level->rollTreasure(character, NULL, m_vPosition);
    setVisible(false, true);
    if (m_bBlocksPath)
        m_bPathingFlag19C = false;
    m_bItemFlag218 = true;
    CItem::interact(character);
    return true;
}

void CBreakable::setRimlight(std::wstring texture)
{
    if (m_pUnitModel)
        m_pUnitModel->setRimLighting(texture);
}

void CBreakable::unitInit(CDataGroup* data, bool initialize)
{
    if (!data)
        return;
    CItem::unitInit(data, initialize);
    std::wstring directory = data->GetDataValue(L"RESOURCEDIRECTORY", EMPTY_WSTRING);
    std::wstring mesh = data->GetDataValue(L"MESHFILE", EMPTY_WSTRING);
    std::wstring collision = data->GetDataValue(L"COLLISIONFILE", L"media/models/collider.mesh");
    bool skinning = m_pDataGroup->GetDataValue(L"ALLOW_HWSKINNING", true);
    if (m_bLevelLighting)
        skinning = false;
    if (mesh != EMPTY_WSTRING)
    {
        mesh = FILESYSTEM::CleanPath(directory + L"/" + mesh + L".mesh");
        m_pUnitModel = m_pResourceManager->createGenericModel(
            m_pResourceManager ? m_pResourceManager->getSceneManager() : NULL,
            mesh.c_str(), EMPTY_WSTRING.c_str(), skinning, false, true);
        sceneNodeAddChild(m_pUnitModel);
        m_pUnitModel->setVisible(true);
        m_pUnitModel->setPosition(0.0f, 0.0f, 0.0f);
        m_pUnitModel->getEntity()->setRenderQueueGroup(0x32);
        CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
        CLevelTemplateData* levelData = level ? level->getLevelTemplateData() : NULL;
        m_pUnitModel->setRimLighting(levelData ? levelData->m_sRimlightTexture :
                                  std::wstring(L"media/sharedtexture/rimlight.dds"));
        m_pUnitModel->setRenderBehind(true);
    }
    collision = FILESYSTEM::CleanPath(collision);
    m_collisionModel = CMasterResourceManager::getSingleton()->addCollisionModel(collision);
    if (m_bBlocksPath)
        m_bPathingFlag19C = true;
    std::wstring particle = STRINGS::StringUpper(data->GetDataValue(L"INTERACT_PARTICLE", EMPTY_WSTRING));
    if (particle != EMPTY_WSTRING)
    {
        if (particle.size() > 8 &&
            (particle.find(L"/") != std::wstring::npos || particle.find(L"\\") != std::wstring::npos))
            CMasterResourceManager::getSingleton()->m_pParticlePreloader->LoadParticle(particle);
        m_particle = m_pResourceManager->createParticle(particle.c_str());
    }
    CSoundBankDataInformation* sounds = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    std::wstring sound = m_pDataGroup->GetDataValue(L"INTERACT_SOUND", EMPTY_WSTRING);
    CSoundData* soundData = sounds->getSoundDataObject(STRINGS::StringUpper(sound).c_str());
    if (soundData)
        m_pSoundBank->addSample(0, soundData->m_iGuid);
    setCastsShadows(m_pDataGroup->GetDataValue(L"SHADOWS", true));
    setVisible(false, true);
    m_bItemFlag1F0 = true;
    unitInitThemes();
}
