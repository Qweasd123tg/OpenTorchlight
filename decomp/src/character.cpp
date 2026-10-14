#include "SteamStats.h"
#include "SpawnClass.h"
#include "StringTranslate.h"
#include "GameClient.h"


#include "StringUtilities.h"
#include <OgreLogManager.h>
#include "EditorScene.h"

#include <CEGUIWindowManager.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreMesh.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <algorithm>
#include "AIManager.h"
#include "Achievement.h"
#include "Achievements.h"
#include "AnimationSet.h"
#include "AstarPathfinder.h"
#include "AttackDescription.h"
#include "CEGUIWindow.h"
#include "DataGroup.h"
#include "Effect.h"
#include "EffectManager.h"
#include "EmptyStrings.h"
#include "Equipment.h"
#include "GameGlobals.h"
#include "GameUI.h"
#include "Inventory.h"
#include "Keyframe.h"
#include "Level.h"
#include "LevelTemplateData.h"
#include "MasterResourceManager.h"
#include "Monster.h"
#include "OgreUtilities.h"
#include "Particle.h"
#include "Path.h"
// Keep the original mutable call without changing the legacy const path TU.
extern Ogre::Vector3 characterPathPoint(CPath*, unsigned int) __asm__("_ZN5CPath8GetPointEj");
#include "PathController.h"
#include "Player.h"
#include "Settings.h"
#include "Skill.h"
#include "SkillManager.h"
#include "SoundBank.h"
#include "Utilities.h"
#include "UtilitiesMath.h"
#include "Wardrobe.h"
#include "WeaponTrail.h"
#include "Character.h"

#include <cmath>

int CCharacter::petIndex(CCharacter* pet)
{
    for (unsigned int i = 0; i < m_Followers.size(); ++i)
    {
        if (m_Followers[i] == pet)
            return (int)i;
    }
    return -1;
}

bool CCharacter::hasPet(CCharacter* pet)
{
    return petIndex(pet) != -1;
}

bool CCharacter::alive()
{
    if (m_eAIState == AISTATE_DYING)
        return false;
    if (m_eAIState == AISTATE_DEAD)
        return false;
    return true;
}

int CCharacter::HP()
{
    return (int)floorf(m_fHPFloat);
}

int CCharacter::mana()
{
    return (int)floorf(m_fManaFloat);
}

bool CCharacter::spendPerkPoint()
{
    if (m_iUnusedPerkPoints <= 0)
        return false;
    m_iUnusedPerkPoints--;
    return true;
}

bool CCharacter::spendSkillPoint()
{
    if (m_iUnusedSkillPoints <= 0)
        return false;
    m_iUnusedSkillPoints--;
    return true;
}

void CCharacter::spendMeleePoint()
{
    int points = m_iUnusedStatPoints;
    if (points <= 0)
        return;
    m_iMeleeStat++;
    m_iUnusedStatPoints = points - 1;
}



int CCharacter::strength()
{
    int value = m_iMeleeStat;

    value += static_cast<int>(ceilf(
        static_cast<float>(value) *
        getEffectValue(static_cast<EEFFECT_TYPE>(0x47),
                       static_cast<EDAMAGE_TYPES>(7)) / 100.0f));

    value += static_cast<int>(ceilf(
        getEffectValue(static_cast<EEFFECT_TYPE>(0x45),
                       static_cast<EDAMAGE_TYPES>(7))));

    return value;
}

void CCharacter::giveGold(int amount)
{
    CCharacter* owner = this;
    while (owner->m_pMaster)
        owner = owner->m_pMaster;
    if (amount > 0)
    {
        owner->incrementJournalStatistic(static_cast<EJournalStatistic>(1), amount);
        int total = static_cast<unsigned int>(owner->m_iGold) + static_cast<unsigned int>(amount);
        if (owner->m_iGold > total)
        {
            owner->m_iGold = 0x7fffffff;
            return;
        }
        amount = total;
    }
    else
        amount += owner->m_iGold;
    owner->m_iGold = std::max(0, amount);
}

void CCharacter::openPortal(CLevel& level)
{
}

void CCharacter::openMapPortal(std::wstring dungeon, CLevel& level)
{
}

void CCharacter::catchFish()
{
}

void CCharacter::fishingAI(float elapsed, CLevel& level)
{
}

void CCharacter::reactToDamage(CCharacter* attacker, bool critical)
{
}

void CCharacter::equipmentDropped(CEquipment* equipment)
{
}

void CCharacter::equipmentUsed(CEquipment* equipment)
{
}

void CCharacter::missileBeingFired(CMissile* missile)
{
}

void CCharacter::missileDieing(CMissile* missile)
{
}

bool CCharacter::missileApplyingEffects(CMissile* missile, CCharacter* target, const Ogre::Vector3* position, float damageScale, float effectScale)
{
    return false;
}

bool CCharacter::getCharacterCanBeHarmedByMissile(CMissile* missile, CCharacter* target)
{
    return true;
}

#include <map>
#include <string>
#include "GenericModel.h"

void CCharacter::scaleUpdated(const Ogre::Vector3& scale)
{
    if (m_pUnitModel)
        m_pUnitModel->setPosition(Ogre::Vector3(0.0f, -m_fBaseUnitValue194 / m_vScale.z, 0.0f));
}

void CCharacter::setVisible(bool visible)
{
    m_characterVisible = (!m_forcedHidden) & visible;
}

void CCharacter::setMaximumTreeDepth(unsigned int depth)
{
    if (m_pathfinder) m_pathfinder->m_iMaxIterations = depth;
}

void CCharacter::stopPathing()
{
    if (m_isPathing) m_pathGraceTime = 10.0f;
    m_isPathing = false;
    m_pathDestination = m_vPosition;
}

bool CCharacter::performingAttack()
{
    return m_attack != NULL && m_attackTime > 0.0f;
}

bool CCharacter::performingAttackLoose()
{
    return m_attack != NULL && m_attackTime > 0.2f;
}

bool CCharacter::skillAllowsTurning()
{
    if (!m_activeSkill || m_skillTime < 0.1f) return true;
    return m_activeSkill->m_allowsTurning;
}

bool CCharacter::performingSkillLoose()
{
    if (m_activeSkill) {
        if (m_skillLooping) return true;
        if (m_skillTime > 0.0f) return !m_skillInterrupted;
    }
    return false;
}

int CCharacter::characterDamage()
{
    return 0;
}

int CCharacter::naturalArmor()
{
    return m_naturalArmor;
}

float CCharacter::HPFloat()
{
    return m_fHPFloat;
}

float CCharacter::manaFloat()
{
    return m_fManaFloat;
}

void CCharacter::giveUnusedPerkPoints(int amount)
{
    m_iUnusedPerkPoints += amount;
}

void CCharacter::giveUnusedStatPoints(int amount)
{
    m_iUnusedStatPoints += amount;
}

void CCharacter::giveUnusedSkillPoints(int amount)
{
    m_iUnusedSkillPoints += amount;
}

void CCharacter::spendRangedPoint()
{
    int points = m_iUnusedStatPoints;
    if (points <= 0) return;
    ++m_rangedStat;
    m_iUnusedStatPoints = points - 1;
}

void CCharacter::spendDefensePoint()
{
    int points = m_iUnusedStatPoints;
    if (points <= 0) return;
    ++m_defenseStat;
    m_iUnusedStatPoints = points - 1;
}

void CCharacter::spendMagicPoint()
{
    int points = m_iUnusedStatPoints;
    if (points <= 0) return;
    ++m_magicStat;
    m_iUnusedStatPoints = points - 1;
}

void CCharacter::reclaimMeleePoint()
{
    if (m_iMeleeStat > 2)
    {
        ++m_iUnusedStatPoints;
        --m_iMeleeStat;
    }
}

void CCharacter::reclaimRangedPoint()
{
    if (m_rangedStat > 2)
    {
        ++m_iUnusedStatPoints;
        --m_rangedStat;
    }
}

void CCharacter::reclaimDefensePoint()
{
    if (m_defenseStat > 2)
    {
        ++m_iUnusedStatPoints;
        --m_defenseStat;
    }
}

void CCharacter::reclaimMagicPoint()
{
    if (m_magicStat > 2)
    {
        ++m_iUnusedStatPoints;
        --m_magicStat;
    }
}

void CCharacter::addFame(unsigned int amount)
{
    m_fame += amount;
}

void CCharacter::setAllowJumpDown(bool allow)
{
    if (m_allowJumpDown != allow)
    {
        m_allowJumpDown = allow;
        updateAI(0.0f, true);
    }
}

unsigned int CCharacter::getAnimationPlaying()
{
    return m_pUnitModel ? m_pUnitModel->m_animationPlaying : 0;
}

float CCharacter::getAnimationSpeed()
{
    return m_pUnitModel ? m_pUnitModel->m_animationSpeed : 1.0f;
}

bool CCharacter::getAnimationLoop()
{
    return m_pUnitModel ? m_pUnitModel->m_animationLoop : false;
}

void CCharacter::setModelPathDummy(std::wstring path)
{
}

std::wstring CCharacter::getWardrobeHelmTexture()
{
    if (m_wardrobe) return m_wardrobe->m_textures[3];
    return EMPTY_WSTRING;
}

std::wstring CCharacter::getWardrobeBootsTexture()
{
    if (m_wardrobe) return m_wardrobe->m_textures[2];
    return EMPTY_WSTRING;
}

std::wstring CCharacter::getWardrobeGlovesTexture()
{
    if (m_wardrobe) return m_wardrobe->m_textures[1];
    return EMPTY_WSTRING;
}

std::wstring CCharacter::getWardrobeChestTexture()
{
    if (m_wardrobe) return m_wardrobe->m_textures[0];
    return EMPTY_WSTRING;
}

std::wstring CCharacter::getWardrobeShoulderMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[4];
    return EMPTY_WSTRING;
}

std::wstring CCharacter::getWardrobeHelmMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[3];
    return EMPTY_WSTRING;
}

std::wstring CCharacter::getWardrobeBootsMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[2];
    return EMPTY_WSTRING;
}

std::wstring CCharacter::getWardrobeGlovesMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[1];
    return EMPTY_WSTRING;
}

std::wstring CCharacter::getWardrobeChestMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[0];
    return EMPTY_WSTRING;
}

std::wstring CCharacter::getModelPath()
{
    if (m_pUnitModel) return m_pUnitModel->m_sModelPath;
    return EMPTY_WSTRING;
}

void CCharacter::setAnimationPlaying(unsigned int animation)
{
    if (m_pUnitModel) {
        m_pUnitModel->clearAnimations();
        CGenericModel* model = m_pUnitModel;
        model->m_animationPlaying = animation;
        if (model->m_animationSet && model->m_animationSet->m_lUnknown28.size()) {
            if (animation >= model->m_animationSet->m_lUnknown28.size()) {
                model->clearAnimations();
                model->m_animationPlaying = animation = 0;
            }
            model->playAnimation(animation, model->m_animationLoop, model->m_animationSpeed, -1.0f);
        }
    }
}

float CCharacter::followRange()
{
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(0)))
        return m_followRange * 2.0f;
    return m_followRange;
}

float CCharacter::getBravery()
{
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(3)))
        return m_bravery * 0.5f;
    return m_bravery;
}

void CCharacter::swapSkills()
{
    if (m_pUnitModel && m_pSkillManager && m_activeSkillGuid != m_leftSkillGuid &&
        m_pSkillManager->getSkillByGuid(m_leftSkillGuid)) {
        long long old = m_activeSkillGuid;
        m_activeSkillGuid = m_leftSkillGuid;
        m_leftSkillGuid = old;
    }
}

bool CCharacter::canLearnSpell(std::wstring name, int level)
{
    if (m_pSkillManager && m_pSkillManager->getSkill(name, level))
        return false;
    if (m_pMaster || ISA(static_cast<UNITTYPES::EUNITTYPES>(87)))
        return m_knownSpells[0].empty() || m_knownSpells[1].empty();
    return m_knownSpells[0].empty() || m_knownSpells[1].empty() ||
           m_knownSpells[2].empty() || m_knownSpells[3].empty();
}

void CCharacter::setRenderBehind(bool behind)
{
    if (m_pUnitModel)
    {
        m_pUnitModel->setRenderBehind(behind);
        if (behind)
            m_pUnitModel->getEntity()->setRenderQueueGroup(50);
        else if (m_pUnitModel->m_renderFlag23A)
            m_pUnitModel->getEntity()->setRenderQueueGroup(91);
        else
            m_pUnitModel->getEntity()->setRenderQueueGroup(88);
        if (m_pInventory)
        {
            for (int i = 0; i < 12; ++i)
            {
                CEquipment* equipment = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(i));
                if (equipment && (equipment->getUnitModel() || equipment->getUnitModelSecondary()))
                    equipment->setRenderBehind(behind);
            }
        }
    }
}

bool CCharacter::isDualWielding()
{
    if (m_pInventory && m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1)) &&
        m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1))->ISA(static_cast<UNITTYPES::EUNITTYPES>(8)) &&
        m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0)))
        return m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0))->ISA(static_cast<UNITTYPES::EUNITTYPES>(8));
    return false;
}

CEquipment* CCharacter::getWeaponInLeftHand()
{
    if (!m_pInventory) return NULL;
    return m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1));
}

CEquipment* CCharacter::getWeaponInRightHand()
{
    if (!m_pInventory) return NULL;
    return m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0));
}

void CCharacter::setHighlighted(bool highlighted)
{
    CBaseUnit::setHighlighted(highlighted);
    for (int i = 0; i < 12; ++i) {
        CEquipment* equipment = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(i));
        if (equipment && (equipment->getUnitModel() || equipment->getUnitModelSecondary()))
            equipment->setHighlighted(highlighted);
    }
}

int CCharacter::maximumSkillDamageForDisplay()
{
    if (m_pSkillManager) {
        CSkill* skill = m_pSkillManager->getSkillByGuid(m_activeSkillGuid);
        if (skill) return skill->getMaximumDamage();
    }
    return 0;
}

int CCharacter::minimumSkillDamageForDisplay()
{
    if (m_pSkillManager) {
        CSkill* skill = m_pSkillManager->getSkillByGuid(m_activeSkillGuid);
        if (skill) return skill->getMinimumDamage();
    }
    return 0;
}

void CCharacter::queueBlendAnimation(const std::string& animation, bool loop, float blend, float speed)
{
    if (m_pUnitModel) m_pUnitModel->queueBlendAnimation(animation, loop, blend, speed);
}

void CCharacter::returnToTownAI(float, CLevel&)
{
    m_returningToTown = true;
    if (!m_isPathing) {
        if (m_pSkillManager) m_pSkillManager->stopAllSkills(true, false, false);
        setAIState(static_cast<EAIState>(42));
        CAchievement* achievement = CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(2));
        if (achievement) achievement->forceComplete();
    }
}

bool CCharacter::characterShouldFadeOut()
{
    if (m_eAIState != AISTATE_DEAD || ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) return false;
    unsigned int property = KSETTINGS_DESTROY_MONSTERS_AFTER_DEATH;
    CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    return settings->GetInt(property) > 0;
}

bool CCharacter::animationExists(const std::string& animation) const
{
    return m_pUnitModel ? m_pUnitModel->animationExists(animation) : false;
}

bool CCharacter::isImmobile()
{
    return hasEffect(static_cast<EEFFECT_TYPE>(0x3f)) || m_moveSpeed == 0.0f;
}

void CCharacter::immobileAI(float)
{
    if (isImmobile()) {
        m_moveSpeed = 0.0f;
        m_movement = Ogre::Vector3(0.0f, 0.0f, 0.0f);
    } else setAIState(static_cast<EAIState>(0));
}

EAlignment CCharacter::getTargetAlignment()
{
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(1))) return static_cast<EAlignment>(3);
    return alignment() == static_cast<EAlignment>(1) ? static_cast<EAlignment>(5) : static_cast<EAlignment>(6);
}

void CCharacter::forceDisplayOfDamageAbsorbed()
{
    displayDamageAbsorbed(10000.0f);
}

void CCharacter::animationPlayAI(float elapsed)
{
    if (!m_pUnitModel->animationPlaying(m_aiAnimation) && !m_pUnitModel->animationQueued(m_aiAnimation)) {
        setAIState(static_cast<EAIState>(0));
        updateAI(elapsed, true);
    }
}

void CCharacter::blendAnimation(int animation, bool loop, float blend, float speed, float)
{
    if (m_pUnitModel) {
        if (m_weaponsHidden) {
            m_weaponsHidden = false;
            if (m_pRightHandNode) m_pRightHandNode->setVisible(true, true);
            if (m_pLeftHandNode) m_pLeftHandNode->setVisible(true, true);
        }
        m_moveSpeed = 1.0f;
        m_pUnitModel->blendAnimation(animation, loop, blend, speed, -1.0f);
    }
}

bool CCharacter::animationQueued(const std::string& animation) const
{
    return m_pUnitModel ? m_pUnitModel->animationQueued(animation) : false;
}

void CCharacter::incrementJournalStatistic(EJournalStatistic statistic, int amount)
{
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) {
        CPlayer* player = dynamic_cast<CPlayer*>(this);
        if (player) player->incrementJournalStatistic(statistic, amount);
    }
}

void CCharacter::updateSkill(float elapsed)
{
    if (m_pInventory) m_pInventory->updateSkillManagers(elapsed);
}

bool CCharacter::canAttackWithCurrentWeapon()
{
    if (m_pInventory) {
        CEquipment* equipment = NULL;
        if (!m_attackItem) equipment = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1));
        if (!equipment) equipment = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0));
        if (equipment && equipment->getSkillManager() && equipment->getSkillManager()->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0)))
            return !equipment->getSkillManager()->getAnySkillsCoolingByActivationType(static_cast<ESKILL_ACTIVATION_TYPE>(2));
    }
    return true;
}

float CCharacter::rangedRange()
{
    if (!m_attack)
    {
        selectAttack(ATTACK_RANGE_DEFAULT);
        return 0;
    }
    float range = m_attack->m_fRange;
    if (m_attackItem)
    {
        CEquipment* left = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1));
        CEquipment* right = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0));
        if (left && left->ISA(static_cast<UNITTYPES::EUNITTYPES>(35)))
            if (left->m_pAttackDescriptionOverride->m_fRange > range)
                range = left->m_pAttackDescriptionOverride->m_fRange;
        if (right && right->ISA(static_cast<UNITTYPES::EUNITTYPES>(35)))
            if (right->m_pAttackDescription->m_fRange > range)
                range = right->m_pAttackDescription->m_fRange;
    }
    return m_attackRadius * m_vScale.z + 0.2f + range;
}

float CCharacter::meleeRange()
{
    if (!m_attack)
    {
        selectAttack(ATTACK_RANGE_DEFAULT);
        return 0;
    }
    float range = m_attack->m_fRange;
    if (m_attackItem)
    {
        CEquipment* left = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1));
        CEquipment* right = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0));
        if (left && left->ISA(static_cast<UNITTYPES::EUNITTYPES>(60)))
            if (left->m_pAttackDescriptionOverride->m_fRange < range)
                range = left->m_pAttackDescriptionOverride->m_fRange;
        if (right && right->ISA(static_cast<UNITTYPES::EUNITTYPES>(60)))
            if (right->m_pAttackDescription->m_fRange < range)
                range = right->m_pAttackDescription->m_fRange;
    }
    return m_attackRadius * m_vScale.z + 0.2f + range;
}

void CCharacter::setToward(const Ogre::Vector3& direction)
{
    MATH::matrixRotationY(m_mOrientation, UTILITIES::VerifyFloat(atan2f(direction.x, direction.z), 0.01745329238474369f));
    setOrientation(m_mOrientation, false);
    extractOrientationVectors();
}

bool CCharacter::canPathTo(Ogre::Vector3 destination)
{
    bool wasInMap = m_bBaseUnitFlag19B;
    removeFromAvoidanceMap(*getLevel());
    m_pathfinder->m_bIgnoreOccupancy = true;
    bool found = m_pathfinder->findPath(m_vPosition.x, m_vPosition.z, destination.x, destination.z);
    if (!m_pathfinder->m_bCompletePath)
        found = false;
    if (wasInMap && m_eAIState != static_cast<EAIState>(5) && m_eAIState != static_cast<EAIState>(6))
        addToAvoidanceMap(*getLevel());
    m_pathfinder->m_bIgnoreOccupancy = false;
    return found;
}

void CCharacter::blendAnimation(const std::string& animation, bool loop, float blend, float speed, float)
{
    if (m_pUnitModel) {
        if (m_weaponsHidden) {
            m_weaponsHidden = false;
            if (m_pRightHandNode) m_pRightHandNode->setVisible(true, true);
            if (m_pLeftHandNode) m_pLeftHandNode->setVisible(true, true);
        }
        m_moveSpeed = 1.0f;
        m_pUnitModel->blendAnimation(animation, loop, blend, speed, -1.0f);
    }
}

bool CCharacter::animationPlaying(const std::string& animation) const
{
    return m_pUnitModel ? m_pUnitModel->animationPlaying(animation) : false;
}

void CCharacter::setActiveInLevel(bool active)
{
    if (active)
    {
        setVisible(false, true);
        setVisible(true, true);
        m_currentOpacity = 1;
        updateOpacity(0, true);
    }
    else
    {
        for (unsigned int i = 0; i < 12; ++i)
            if (m_equipmentParticles[i])
                m_equipmentParticles[i]->Stop(false);
        setVisible(false, true);
        CLevel* level = m_pResourceManager->getLevel();
        if (level)
            removeFromAvoidanceMap(*level);
        if (m_bBlocksPath)
            m_bPathingFlag19C = false;
    }
}

void CCharacter::setMeshVisible(bool visible, bool recursive)
{
    m_forcedHidden = !visible;
    if (recursive) setVisible(visible, true);
    else setVisible(visible);
    if (m_automapBillboard) getLevel()->setNPCAutomapBillboardVisible(m_automapBillboard, visible);
}

void CCharacter::toggleSecondaryWeaponSet()
{
    m_pInventory->swapWeaponSet();
    m_bSecondaryWeaponSet = !m_bSecondaryWeaponSet;
}

bool CCharacter::hasWeaponsInOffSet()
{
    if (!m_pInventory) return false;
    CEquipmentRef* first = m_pInventory->getEquipmentRefInSlot(12);
    CEquipmentRef* second = m_pInventory->getEquipmentRefInSlot(13);
    return first != NULL || second != NULL;
}

void CCharacter::setPaperdollItemSecondary(EEQUIP_LOCATIONS slot, Ogre::Entity* entity)
{
    if (m_PaperdollItemsSecondary[slot]) {
        m_PaperdollItemsSecondary[slot]->getMesh()->unload();
        OGRE_UTILITIES::detachEntityFromParent(m_PaperdollItemsSecondary[slot]);
        Ogre::MeshManager::getSingleton().remove(m_PaperdollItemsSecondary[slot]->getMesh()->getName());
        CMasterResourceManager::getSingleton()->m_pSceneManager->destroyEntity(m_PaperdollItemsSecondary[slot]);
        m_PaperdollItemsSecondary[slot] = NULL;
    }
    m_PaperdollItemsSecondary[slot] = entity;
}

void CCharacter::setPaperdollItem(EEQUIP_LOCATIONS slot, Ogre::Entity* entity)
{
    if (m_PaperdollItems[slot]) {
        m_PaperdollItems[slot]->getMesh()->unload();
        OGRE_UTILITIES::detachEntityFromParent(m_PaperdollItems[slot]);
        Ogre::MeshManager::getSingleton().remove(m_PaperdollItems[slot]->getMesh()->getName());
        CMasterResourceManager::getSingleton()->m_pSceneManager->destroyEntity(m_PaperdollItems[slot]);
        m_PaperdollItems[slot] = NULL;
    }
    m_PaperdollItems[slot] = entity;
}

float CCharacter::getEffectValue(EEFFECT_TYPE type, float base, const std::wstring& name)
{
    if (m_pEffectManager) {
        if (m_pInventory) {
            float value = m_pEffectManager->getEffectValue(type, name);
            return value + m_pInventory->getEffectValue(type, base, name);
        }
        return m_pEffectManager->getEffectValue(type, name);
    }
    if (m_pInventory) return m_pInventory->getEffectValue(type, base, name);
    return base;
}

float CCharacter::getEffectValueWithoutInventory(EEFFECT_TYPE type, EDAMAGE_TYPES damage)
{
    return m_pEffectManager ? m_pEffectManager->getEffectValue(type, damage) : 0.0f;
}

float CCharacter::getEffectValue(EEFFECT_TYPE type, EEQUIP_LOCATIONS excluded, EDAMAGE_TYPES damage)
{
    if (m_pEffectManager) {
        if (m_pInventory) {
            float value = m_pEffectManager->getEffectValue(type, damage);
            return value + m_pInventory->getEffectValueMinusEquipmentSlot(type, excluded, damage);
        }
        return m_pEffectManager->getEffectValue(type, damage);
    }
    if (m_pInventory) return m_pInventory->getEffectValueMinusEquipmentSlot(type, excluded, damage);
    return 0.0f;
}

float CCharacter::getEffectValue(EEFFECT_TYPE type, EDAMAGE_TYPES damage)
{
    if (m_pEffectManager) {
        if (m_pInventory) {
            float value = m_pEffectManager->getEffectValue(type, damage);
            return value + m_pInventory->getEffectValue(type, damage);
        }
        return m_pEffectManager->getEffectValue(type, damage);
    }
    if (m_pInventory) return m_pInventory->getEffectValue(type, damage);
    return 0.0f;
}

void CCharacter::calculateMaxMana()
{
    m_maxManaBase = m_iUnitLevel * 5 + 20;
    if (m_fManaFloat > float(maxMana())) m_fManaFloat = float(maxMana());
}

void CCharacter::modifyMana(float amount)
{
    if (getIsInGodMode()) {
        m_fManaFloat = float(maxMana());
        return;
    }
    m_fManaFloat += amount;
    if (m_fManaFloat > float(maxMana())) m_fManaFloat = float(maxMana());
    if (m_fManaFloat < 0.0f) m_fManaFloat = 0.0f;
}

int CCharacter::maxHP()
{
    float percent = getEffectValue(static_cast<EEFFECT_TYPE>(20), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
    if (m_pMaster) percent += m_pMaster->getEffectValue(static_cast<EEFFECT_TYPE>(104), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
    int base = std::max(m_maxHPBase + m_maxHPBonus, 1);
    float bonus = ceilf(float(base) * percent);
    float flat = ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(5), static_cast<EDAMAGE_TYPES>(7)));
    return int(bonus) + int(flat) + base;
}

void CCharacter::calculateMaxHP()
{
    if (m_pMaster && m_pMaster->ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) {
        m_maxHPBase = (m_iUnitLevel + 1) * 20 + 100;
        if (m_fHPFloat > float(maxHP())) m_fHPFloat = float(maxHP());
    }
    if (m_fHPFloat > float(maxHP())) m_fHPFloat = float(maxHP());
}

int CCharacter::defense()
{
    float percent = getEffectValue(static_cast<EEFFECT_TYPE>(17), static_cast<EDAMAGE_TYPES>(7));
    percent += getEffectValue(static_cast<EEFFECT_TYPE>(17), static_cast<EDAMAGE_TYPES>(6));
    int base = m_defenseStat;
    float percentageBonus = ceilf(static_cast<float>(base) * (percent / 100.0f));
    float flatBonus = ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(2), static_cast<EDAMAGE_TYPES>(7)));
    return static_cast<int>(percentageBonus) + static_cast<int>(flatBonus) + base;
}

int CCharacter::armorBonus()
{
    int base = m_pInventory->m_iUnknown10 + m_naturalArmor;
    float percent = getEffectValue(static_cast<EEFFECT_TYPE>(23), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
    if (m_pMaster) percent += m_pMaster->getEffectValue(static_cast<EEFFECT_TYPE>(97), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
    float bonus = ceilf(float(base) * percent);
    float flat = ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(8), static_cast<EDAMAGE_TYPES>(7)));
    return int(bonus) + int(flat) + base;
}

int CCharacter::AC()
{
    int armor = armorBonus();
    int total = armor + static_cast<int>(ceilf(static_cast<float>(armor) * (static_cast<float>(defense()) / 100.0f)));
    total -= static_cast<int>(ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(66), static_cast<EDAMAGE_TYPES>(7))));
    if (total < 0) total = 0;
    return total;
}

int CCharacter::minimumAC()
{
    return static_cast<int>(ceilf(static_cast<float>(AC()) * 0.5f));
}

int CCharacter::minimumDamageForDisplay(bool first, bool second, bool third)
{
    if (!m_attack) {
        selectAttack(static_cast<EATTACK_RANGE_TYPE>(0));
        if (!m_attack) return 0;
    }
    return static_cast<int>(ceilf(static_cast<float>(maximumDamageForDisplay(first, second, third)) * 0.5f));
}

int CCharacter::damageDefensePercent(EDAMAGE_TYPES type)
{
    float first = getEffectValue(static_cast<EEFFECT_TYPE>(26), type);
    return static_cast<int>(ceilf(first + getEffectValue(static_cast<EEFFECT_TYPE>(26), static_cast<EDAMAGE_TYPES>(6))));
}

float CCharacter::sightRange()
{
    float range = m_sightRange;
    if (m_pMaster && walkingSpeed() > 0 && runningSpeed() > 0)
        range = 35;
    range += getEffectValue(static_cast<EEFFECT_TYPE>(13), DAMAGE_TYPE_COUNT);
    range += getEffectValue(static_cast<EEFFECT_TYPE>(41), DAMAGE_TYPE_COUNT) * range;
    CLevel* level = getLevel();
    if (level && level->getLevelTemplateData())
        range += level->getLevelTemplateData()->getSightRangeModifier();
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(0)))
        range *= 2;
    return range;
}

int CCharacter::getBlockChance()
{
    float first = getEffectValue(static_cast<EEFFECT_TYPE>(33), static_cast<EDAMAGE_TYPES>(7));
    float chance = first + getEffectValue(static_cast<EEFFECT_TYPE>(62), static_cast<EDAMAGE_TYPES>(7)) + 0.0f;
    if (chance > 50.0f) return 50;
    return static_cast<int>(chance);
}

int CCharacter::getCriticalChance()
{
    int chance = static_cast<int>(ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(55), static_cast<EDAMAGE_TYPES>(7)) + 3.0f));
    return std::min(100, chance);
}

float CCharacter::getEffectValuesOfDamage()
{
    float penalty = getEffectValue(static_cast<EEFFECT_TYPE>(52), static_cast<EDAMAGE_TYPES>(7));
    float first = getEffectValue(static_cast<EEFFECT_TYPE>(7), static_cast<EDAMAGE_TYPES>(7));
    float second = getEffectValue(static_cast<EEFFECT_TYPE>(124), static_cast<EDAMAGE_TYPES>(7));
    if (penalty > 0.0f) penalty = -penalty;
    return second + first + penalty;
}

void CCharacter::hideCharacterText()
{
    if (m_characterText && m_characterTextVisible)
    {
        m_characterTextVisible = false;
        m_characterTextParent->removeChildWindow(m_characterText);
    }
}

void CCharacter::showCharacterText()
{
    if (m_characterText && !m_characterTextVisible)
    {
        m_characterTextVisible = true;
        m_characterTextParent->addChildWindow(m_characterText);
    }
}

void CCharacter::destroyCharacterText()
{
    hideCharacterText();
    if (m_characterText) {
        m_characterTextVisible = false;
        CEGUI::WindowManager::getSingleton().destroyWindow(m_characterText);
        m_characterText = NULL;
    }
}

void CCharacter::destroyIcons()
{
    if (m_pInventory) m_pInventory->destroyIcons();
}

void CCharacter::levelLoaded(CLevel*)
{
    if (m_pInventory) {
        for (unsigned int i = 0; i < 12; ++i) {
            if (m_pInventory->getEquipmentInSlot(i)) m_pInventory->getEquipmentInSlot(i)->resetVisualLayout();
        }
    }
}

void CCharacter::equipmentPickedUp(CEquipment*)
{
    if (m_pMaster && m_pInventory && m_pMaster->ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) {
        unsigned int count = m_pInventory->itemsInPane(static_cast<EINVENTORY_PANES>(0));
        if (count >= m_pInventory->getPaneSize(static_cast<EINVENTORY_PANES>(0)))
            m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(16));
    }
}

void CCharacter::setPathToFollow(CPathController* path)
{
    int savedIterations = m_savedPathIterations;
    if (m_pathfinder) m_pathfinder->m_iMaxIterations = savedIterations;
    m_pathToFollow.setObject(path);
    if (path && m_pathfinder) {
        m_savedPathIterations = m_pathfinder->m_iMaxIterations;
        m_pathfinder->m_iMaxIterations = 800;
    }
    m_pathGraceTime = 10.0f;
    m_pathTime = -1.0f;
}

bool CCharacter::transferEffect(CCharacter* source, CBaseUnit* owner, CEffect* effect)
{
    if (!effect)
        return false;
    if (!isEffectValidForUnit(source, owner, effect))
        return false;
    CEffect* copy = new CEffect(effect);
    copy->setOwner(owner, true);
    copy->m_activation = static_cast<EEFFECT_ACTIVATION>(1);
    addNewEffect(copy);
    return true;
}

void CCharacter::updateVisualEquippedItems(float elapsed)
{
    CInventory* inventory = m_pInventory;
    if (!inventory)
        return;
    if (inventory->getEquipmentInSlot(0))
        inventory->getEquipmentInSlot(0)->updateVisualLayout(elapsed);
    inventory = m_pInventory;
    if (inventory->getEquipmentInSlot(1))
        inventory->getEquipmentInSlot(1)->updateVisualLayout(elapsed);
    inventory = m_pInventory;
    if (inventory->getEquipmentInSlot(3))
        inventory->getEquipmentInSlot(3)->updateVisualLayout(elapsed);
    inventory = m_pInventory;
    if (inventory->getEquipmentInSlot(5))
        inventory->getEquipmentInSlot(5)->updateVisualLayout(elapsed);
}

void CCharacter::setAnimationLoop(bool loop)
{
    if (m_pUnitModel) {
        CGenericModel* model = m_pUnitModel;
        model->m_animationLoop = loop;
        unsigned int animation = model->m_animationPlaying;
        if (model->m_animationSet && model->m_animationSet->m_lUnknown28.size()) {
            if (animation >= model->m_animationSet->m_lUnknown28.size()) {
                model->clearAnimations();
                model->m_animationPlaying = animation = 0;
            }
            model->playAnimation(animation, model->m_animationLoop, model->m_animationSpeed, -1.0f);
        }
    }
}

void CCharacter::setAnimationSpeed(float speed)
{
    if (m_pUnitModel) {
        CGenericModel* model = m_pUnitModel;
        model->m_animationSpeed = speed;
        unsigned int animation = model->m_animationPlaying;
        if (model->m_animationSet && model->m_animationSet->m_lUnknown28.size()) {
            if (animation >= model->m_animationSet->m_lUnknown28.size()) {
                model->clearAnimations();
                model->m_animationPlaying = animation = 0;
            }
            model->playAnimation(animation, model->m_animationLoop, model->m_animationSpeed, -1.0f);
        }
    }
}

void CCharacter::clearAllUnitReferences()
{
    setTarget(NULL);
}

void CCharacter::removePets()
{
    for (unsigned int i = 0; i < m_Followers.size(); ++i) {
        m_Followers[i]->setMaster(NULL);
        m_Followers[i]->die(NULL, NULL, 0.0f, false);
    }
    m_Followers.clear();
}

void CCharacter::levelResetting()
{
    CBaseUnit::levelResetting();
    if (static_cast<float>(HP()) > 0.0f) setAIState(static_cast<EAIState>(0));
    setTarget(NULL);
}

void CCharacter::turnTowardPosition(const Ogre::Vector3& position, float elapsed)
{
    m_targetPosition = position;
    m_targetPosition.y = 0.0f;
    Ogre::Vector3 direction = position - m_vPosition;
    direction.normalise();
    turnToward(direction, elapsed);
}

void CCharacter::setTargetDirection(float x, float z)
{
    m_targetPosition = Ogre::Vector3(x, 0.0f, z);
    Ogre::Vector3 position = getPosition(true);
    m_targetDirection = Ogre::Vector3(m_targetPosition.x - position.x, 0.0f, m_targetPosition.z - position.z);
    m_targetDirection.normalise();
}

bool CCharacter::facingTarget()
{
    if (m_targetCharacter.getObject() || m_targetItem.getObject()) return facingTarget(m_targetCharacter.getObject(), m_targetItem.getObject());
    return false;
}

void CCharacter::performSkill(const std::wstring& name)
{
    if (m_pSkillManager) {
        CSkill* skill = m_pSkillManager->getSkill(name);
        if (skill) {
            if (!m_previousSkill && skill->m_iCharges == 1) m_previousSkill = m_activeSkill;
            setActiveSkill(skill, false);
            stopPathing();
            castSkill(-1);
        }
    }
}

CCharacter::CParticleAnimationTrigger::~CParticleAnimationTrigger()
{
    if (m_resources && m_node)
    {
        OGRE_UTILITIES::removeChildFromParentNode(m_node);
        if (m_nodeOwner)
            m_resources->getSceneManager()->destroySceneNode(m_node);
    }
    if (m_particle)
    {
        delete m_particle;
        m_particle = NULL;
    }
}

int CCharacter::baseAC()
{
    int armor = baseArmorBonus();
    int total = armor + static_cast<int>(ceilf(static_cast<float>(armor) * (static_cast<float>(m_defenseStat) / 100.0f)));
    if (total < 0) total = 0;
    return total;
}

void CCharacter::setWardrobeHelmTexture(std::wstring value)
{
    if (m_wardrobe) {
        m_wardrobe->setBaseTexture(static_cast<EWardrobeSlot>(3), value);
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

void CCharacter::setWardrobeBootsTexture(std::wstring value)
{
    if (m_wardrobe) {
        m_wardrobe->setBaseTexture(static_cast<EWardrobeSlot>(2), value);
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

void CCharacter::setWardrobeGlovesTexture(std::wstring value)
{
    if (m_wardrobe) {
        m_wardrobe->setBaseTexture(static_cast<EWardrobeSlot>(1), value);
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

void CCharacter::setWardrobeChestTexture(std::wstring value)
{
    if (m_wardrobe) {
        m_wardrobe->setBaseTexture(static_cast<EWardrobeSlot>(0), value);
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

void CCharacter::setWardrobeShoulderMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[4].assign(copied); }
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

void CCharacter::setWardrobeHelmMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[3].assign(copied); }
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

void CCharacter::setWardrobeBootsMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[2].assign(copied); }
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

void CCharacter::setWardrobeGlovesMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[1].assign(copied); }
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

void CCharacter::setWardrobeChestMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[0].assign(copied); }
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

void CCharacter::fishingAICast(float elapsed, CLevel& level)
{
    if (!m_pUnitModel->animationPlayingSubstring("FISHING_CAST"))
        setAIState(static_cast<EAIState>(33));
}

void CCharacter::levelUp()
{
    setLevel(m_iUnitLevel + 1, false);
    m_fHPFloat = static_cast<float>(maxHP());
    m_fManaFloat = static_cast<float>(maxMana());
    CPlayer* player = dynamic_cast<CPlayer*>(this);
    if (player)
    {
        m_iUnusedStatPoints += player->getStatsPointsAwardedForLevel(m_iUnitLevel);
        m_iUnusedSkillPoints += player->getSkillPointsAwardedForLevel(m_iUnitLevel);
    }
    if (m_pMaster && m_pMaster->ISA(UNITTYPES::PLAYER))
        if (m_pMaster->m_levelSound)
            m_pMaster->m_levelSound->queueGlobalSample(46, 1, 1);
}

void CCharacter::updateCameraOpacity(Ogre::Camera* camera, float elapsed)
{
    Ogre::Vector3 position = getPosition(true);
    float distance = (camera->getPosition() - position).length();
    if (distance < 6)
    {
        m_currentOpacity = std::max(0.0f, distance - 4.0f) * 0.5f;
        updateOpacity(0, true);
    }
    else if (elapsed > 0)
        updateOpacity(elapsed, false);
}

void CCharacter::removeFromAvoidanceMap(CLevel& level)
{
    if (!getLevel())
        return;
    if (m_bBaseUnitFlag19B)
    {
        for (unsigned int i = 0; i < getFollowerCount(); ++i)
            m_followerFlags[i] = false;
        if (m_Followers.size() > 0)
            for (unsigned int i = 0; i < getFollowerCount(); ++i)
            {
                m_followerFlags[i] = getFollower(i)->m_bBaseUnitFlag19B;
                getFollower(i)->removeFromAvoidanceMap(level);
            }
    }
    CBaseUnit::removeFromAvoidanceMap(level);
}

void CCharacter::followCharacter(CCharacter* target, CLevel& level)
{
    if (!target || target->m_eAIState == 5 || target->m_eAIState == 6)
        return;
    setTarget(target);
    if (m_targetCharacter.getObject())
    {
        bool wasInAvoidanceMap = m_targetCharacter.getObject()->m_bBaseUnitFlag19B;
        m_targetCharacter.getObject()->removeFromAvoidanceMap(level);
        setDestination(level, m_targetCharacter.getObject()->getPosition(true).x, m_targetCharacter.getObject()->getPosition(true).z);
        if (wasInAvoidanceMap)
            m_targetCharacter.getObject()->addToAvoidanceMap(level);
    }
}

void CCharacter::performUnknownSkill(CSkill* source)
{
    CSkill* skill;
    if (m_pSkillManager && !m_pSkillManager->getSkill(source->getName()))
        skill = cloneSkill(source);
    else
        skill = m_pSkillManager->getSkill(source->getName());
    if (skill)
    {
        if (skill->getAnimationIndex() == -1)
            m_pSkillManager->executeSkill(skill, this, static_cast<ESKILL_ACTIVATION_TYPE>(1),
                                         getPosition(true), m_pSceneNode->getOrientation(), getPosition(true), this);
        else
            performSkill(source->getName());
    }
}

void CCharacter::completeDeath(CLevel& level)
{
    setRenderBehind(false);
    if (m_weaponTrails[0])
    {
        m_weaponTrails[0]->setActive(false);
        m_weaponTrails[0]->setVisible(false);
    }
    if (m_weaponTrails[1])
    {
        m_weaponTrails[1]->setActive(false);
        m_weaponTrails[1]->setVisible(false);
    }
    if (m_weaponTrails[2])
    {
        m_weaponTrails[2]->setActive(false);
        m_weaponTrails[2]->setVisible(false);
    }
    if (m_weaponTrails[3])
    {
        m_weaponTrails[3]->setActive(false);
        m_weaponTrails[3]->setVisible(false);
    }
    if (m_pMaster)
        m_pMaster->removePet(this);
    setAIState(static_cast<EAIState>(6));
    removeFromAvoidanceMap(level);
    if (m_bBlocksPath)
        m_bPathingFlag19C = false;
    if (attachesToMaster() || getDestroyOnDeath() ||
        (m_pEffectManager && m_pEffectManager->hasEffect(static_cast<EEFFECT_TYPE>(129))))
        m_bBaseUnitFlag190 = true;
}

void CCharacter::sendToTown(CLevel& level)
{
    if (!level.getLevelTemplateData()->isTown() && m_pMaster)
    {
        m_townTravelTime = level.getDungeonDepth() * 10.0f;
        if (m_townTravelTime > 120)
            m_townTravelTime = 120;
        float reduction = getEffectValue(static_cast<EEFFECT_TYPE>(96), static_cast<EDAMAGE_TYPES>(7)) / 100;
        if (m_pMaster)
            reduction += m_pMaster->getEffectValue(static_cast<EEFFECT_TYPE>(96), static_cast<EDAMAGE_TYPES>(7)) / 100;
        m_townTravelTime = std::max(1.0f, m_townTravelTime - m_townTravelTime * reduction);
        setTarget(NULL);
        setTargetItem(NULL);
        setAIState(static_cast<EAIState>(41));
        Ogre::Vector3 position = level.randomOpenPositionRange(m_pMaster->getPosition(false), 20, 30, false);
        setDestination(level, position.x, position.z);
    }
}

void CCharacter::dyingAI(float elapsed, CLevel& level)
{
    if (m_deathPathActive)
    {
        float endHeight = characterPathPoint(m_deathPath, 1).y;
        float startHeight = characterPathPoint(m_deathPath, 0).y;
        float height = std::max(0.0f, m_vPosition.y - startHeight);
        m_deathPathDistance += ((endHeight - startHeight - height) * 0.65f + 0.75f) * (elapsed * m_deathPathSpeed);
        float distance = m_deathPathDistance;
        if (distance >= m_deathPath->m_fPathLength)
        {
            distance = m_deathPath->m_fPathLength;
            m_deathPathDistance = distance;
            completeDeath(level);
            m_deathPathActive = false;
            if (!m_deathPathSilent && m_levelSound)
                m_levelSound->playSample(17, m_pSceneNode, 0, 0, false);
        }
        m_vPosition = m_deathPath->GetSplinePositionAtDistance(distance);
        CPositionableObject::setPosition(m_vPosition);
    }
    else if (!m_pUnitModel->animationPlaying())
        completeDeath(level);
}

void CCharacter::learnSpell(std::wstring name, int level)
{
    for (unsigned int i = 0; i < 4; ++i) {
        if (!m_knownSpells[i].empty()) continue;
        m_knownSpells[i] = name;
        m_knownSpellLevels[i] = level;
        CSkill* skill = addSkillByName(name, false);
        if (skill) {
            skill->m_iRequiredLevel = 1;
            skill->m_iColumn = -1;
            skill->m_iCharges = -1;
            m_pSkillManager->setSkillLevel(skill, level);
        } else {
            Ogre::LogManager::getSingleton().logMessage(
                STRINGS::StringConvertToNarrow((L"Skill not found : " + name).c_str()),
                Ogre::LML_NORMAL, false);
        }
        return;
    }
}

void CCharacter::dropToGround(CLevel& level, float height, bool force)
{
    Ogre::Vector3 end = m_vPosition;
    float originalY = m_vPosition.y;
    m_vPosition.y = 100.0f;
    end.y = -100.0f;
    m_groundFlag = false;
    Ogre::Vector3 hit, normal, extra;
    unsigned int type;
    if (force) {
        if (level.rayCollision(m_vPosition, end, hit, normal, type, extra, false) && type != 100) {
            m_vPosition = hit;
            m_vPosition.y += m_fBaseUnitValue194;
        } else {
            m_vPosition.y = originalY;
        }
    } else {
        float radius = 0.1f;
        for (unsigned int i = 0; i < 30; ++i) {
            if (level.rayCollision(m_vPosition, end, hit, normal, type, extra, false) && type != 100) {
                m_vPosition = hit;
                m_vPosition.y += m_fBaseUnitValue194;
                break;
            }
            m_vPosition = level.randomOpenPosition(m_vPosition, radius, false);
            radius += 0.1f;
            end = m_vPosition;
            m_vPosition.y = 100.0f;
            end.y = -100.0f;
            radius = std::min(radius, height);
        }
    }
    setPosition(m_vPosition);
    extractOrientationVectors();
}

void CCharacter::updateActiveSkill(float elapsed)
{
    if (!m_activeSkill ||
        (m_activeSkill->m_animationIndexLoopInto != static_cast<unsigned int>(-1) &&
         !m_activeSkill->m_interruptible) || (!m_skillLooping && !(m_skillTime > 0.0f))) {
        m_skillLooping = false;
        m_skillTime = 0.0f;
        m_skillInterrupted = true;
        return;
    }
    if (static_cast<float>(m_activeSkill->getManaCostOT()) > 0.0f &&
        (m_activeSkill->m_animationIndexLoopInto == static_cast<unsigned int>(-1) ||
         m_skillInterrupted)) {
        float mana = m_fManaFloat;
        if (static_cast<float>(m_activeSkill->getManaCostOT()) * elapsed > mana) {
            int animation = m_activeSkill->getAnimationIndexLoopEnd();
            if (animation != -1) {
                blendAnimation(animation, true, 0.2f, 1.0f, -1.0f);
                queueBlendAnimation("IDLE", true, 0.2f, 1.0f);
            }
            m_skillLooping = false;
            m_skillTime = 0.0f;
            if (m_pSkillManager) m_pSkillManager->stopAllSkills(false, false, false);
            return;
        }
        modifyMana(static_cast<float>(m_activeSkill->getManaCostOT()) * -elapsed);
    }
    if (m_skillTime > 0.0f) {
        m_skillTime -= elapsed;
        if (m_skillTime <= 0.0f) {
            m_skillInterrupted = true;
            for (unsigned int i = 0; i < 2; ++i)
                if (m_weaponTrails[i]) {
                    m_weaponTrails[i]->setActive(false);
                    m_weaponTrails[i]->setVisible(false);
                }
            m_skillTime = 0.0f;
            if (m_activeSkill->m_animationIndexLoopInto == static_cast<unsigned int>(-1))
                m_skillLooping = false;
        }
    }
}

int CCharacter::damageDefense(EDAMAGE_TYPES type)
{
    float base = static_cast<float>(m_damageDefense[type]);
    float percent = getEffectValue(static_cast<EEFFECT_TYPE>(23), type);
    percent += getEffectValue(static_cast<EEFFECT_TYPE>(23), static_cast<EDAMAGE_TYPES>(6));
    float value = std::max(0.0f, base + base * (percent / 100.0f));
    value += getEffectValue(gDAMAGE_DEFENSE_EFFECT_TYPES[type], static_cast<EDAMAGE_TYPES>(7));
    int bonus = static_cast<int>(ceilf((static_cast<float>(defense()) / 100.0f) * value));
    int penalty = static_cast<int>(ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(66), static_cast<EDAMAGE_TYPES>(7))));
    return static_cast<int>(ceilf(static_cast<float>(bonus) + value - static_cast<float>(penalty)));
}

void CCharacter::setTarget(CCharacter* target)
{
    if (m_eAIState == AISTATE_DEAD) {
        if (!target) m_targetCharacter.setObject(NULL);
        return;
    }
    if (m_targetLocked) return;
    CCharacter* previous = m_targetCharacter.getObject();
    if (previous && m_pAIManager &&
        m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(5)) &&
        m_targetCharacter.getObject()->alive()) return;
    m_targetCharacter.setObject(target);
    m_targetItem.setObject(NULL);
    if (m_bBaseUnitFlag0 && previous != target && target && target->isPlayer())
        broadcastAlerted();
}

void CCharacter::playHitParticle(const Ogre::Vector3& from, const Ogre::Vector3& to, float distance)
{
    CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    CParticle* particle = m_equipmentParticles[settings->GetInt(KSETTINGS_SHOW_BLOOD) == 1 ? 1 : 2];
    if (particle) {
        Ogre::Vector3 direction = from - to;
        direction.y = 0.0f;
        direction.normalise();
        Ogre::Vector3 position = to + direction * distance + Ogre::Vector3::UNIT_Y * 1.25f;
        particle->setPosition(position);
        particle->Start();
    }
}

bool CCharacter::facingTarget(CCharacter* character, CItem* item)
{
    if (!character && !item) return false;
    CBaseUnit* target = character ? static_cast<CBaseUnit*>(character) : item;
    Ogre::Vector3 position = getPosition(true);
    Ogre::Vector3 direction = target->getPosition(true) - position;
    direction.y = 0.0f;
    direction.normalise();
    float facing = atan2f(m_vForward.x, m_vForward.z);
    float angle = atan2f(direction.x, direction.z);
    const float degrees = 180.0f / 3.14159f;
    return !(fabsf(angle * degrees - facing * degrees) > m_facingAngle * 0.5f);
}

void CCharacter::teleportToMaster(float distance)
{
    if (!m_pMaster && getLevel()) return;
    Ogre::Vector3 position = getPosition(true);
    Ogre::Vector3 direction = m_pMaster->getPosition(true) - position;
    direction.y = 0.0f;
    direction.normalise();
    direction *= distance;
    Ogre::Vector3 destination = m_pMaster->getPosition(true) - direction;
    bool wasInAvoidanceMap = m_bBaseUnitFlag19B;
    removeFromAvoidanceMap(*getLevel());
    setPosition(getLevel()->randomOpenPosition(destination, 8.0f, false));
    dropToGround(*getLevel(), 4.0f, false);
    if (wasInAvoidanceMap) addToAvoidanceMap(*getLevel());
}

bool CCharacter::moveToPosition(const Ogre::Vector3& position, bool passabilityFlag, bool force)
{
    bool wasInAvoidanceMap = m_bBaseUnitFlag19B;
    removeFromAvoidanceMap(*getLevel());
    Ogre::Vector3 start = getPosition(true);
    bool move = force || getLevel()->passableBetween(start, position, passabilityFlag);
    if (!move) {
        Ogre::Vector3 direction = position - start;
        direction.normalise();
        start += direction * 0.4f;
        move = getLevel()->passableBetween(start, position, passabilityFlag);
    }
    if (move) {
        setPosition(position);
        dropToGround(*getLevel(), 4.0f, force);
        const Ogre::Vector3& forward = getForward();
        m_targetPosition.x = position.x + forward.x;
        m_targetPosition.y = 0.0f;
        m_targetPosition.z = position.z + forward.z;
    }
    if (wasInAvoidanceMap) addToAvoidanceMap(*getLevel());
    return move;
}

void CCharacter::fishingSplash()
{
    if (!m_pUnitModel->animationPlayingSubstring("FISHING_BITE")) {
        blendAnimation("FISHING_BITE", false, 0.2f, 0.5f, -1.0f);
        m_pUnitModel->queueBlendAnimation("FISHING_IDLE", true, 0.2f, 1.0f);
    }
}

void CCharacter::setAIPlayAnimation(const std::string& animation, bool loop,
                                   float blendTime, float speed)
{
    m_aiAnimation = -1;
    if (!m_pUnitModel) return;
    m_aiAnimation = m_pUnitModel->getAnimationIndex(animation);
    if (m_aiAnimation == -1) return;
    setAIState(static_cast<EAIState>(35));
    if (blendTime != 0.0f && m_pUnitModel->getAnimationLengthSeconds(m_aiAnimation) != 0.0f)
        m_pUnitModel->blendAnimation(m_aiAnimation, loop, blendTime, 1.0f, -1.0f);
    else
        m_pUnitModel->playAnimation(m_aiAnimation, loop, speed, -1.0f);
    if (!loop && STRINGS::StringUpper(animation) != "IDLE")
        m_pUnitModel->queueBlendAnimation("IDLE", true, 0.2f, speed);
}

void CCharacter::removePet(std::wstring name)
{
    name = STRINGS::StringUpper(name);
    for (int i = 0; i < static_cast<int>(m_Followers.size()); ++i) {
        if (STRINGS::StringUpper(m_Followers[i]->getName()) == name) {
            CCharacter* pet = m_Followers[i];
            removePet(pet);
            pet->die(NULL, NULL, 0.0f, false);
            --i;
        }
    }
}

void CCharacter::spawningAI(float elapsed, CLevel& level)
{
    std::string animation = STRINGS::StringConvertToNarrow(
        STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"SPAWN_ANIM", L"SPAWN")).c_str());
    if (!m_pUnitModel->animationPlayingSubstring(animation)) {
        setRenderBehind(m_pDataGroup->GetDataValue(L"RENDERBEHIND", true));
        setAIState(static_cast<EAIState>(m_targetCharacter.getObject() ? 4 : 0));
    }
}

void CCharacter::setPathToFollowByName(const std::wstring& name)
{
    m_pathName = name;
    if (getSceneOwner() && !m_pathName.empty()) {
        TArrayList<CEditorBaseObject*>* paths =
            getSceneOwner()->GetObjectsCreatedByADescriptor(L"Pathing");
        if (paths) {
            for (unsigned int i = 0; i < paths->size(); ++i) {
                CPathController* path = static_cast<CPathController*>((*paths)[i]);
                if (path->m_pathName == name) {
                    m_pathToFollow.setObject(static_cast<CPathController*>((*paths)[i]));
                    return;
                }
            }
        }
    }
    m_pathToFollow.setObject(NULL);
}

bool CCharacter::attemptStopOfActiveSkill()
{
    if (!m_activeSkill || !m_pSkillManager)
    {
        m_skillLooping = false;
        return true;
    }
    if (m_activeSkill->m_animationIndexLoopInto != static_cast<unsigned int>(-1) && m_activeSkill->getCanStop())
    {
        m_skillLooping = false;
        m_skillTime = 0.0f;
        m_pSkillManager->stopSkillsByName(m_activeSkill->getName(), true);
        return true;
    }
    if (!m_skillLooping && m_skillInterrupted)
    {
        m_skillLooping = false;
        m_skillTime = 0.0f;
        m_pSkillManager->stopAllSkills(false, false, false);
        return true;
    }
    return false;
}

void CCharacter::performingSkillAI(float elapsed)
{
    if (!m_activeSkill ||
        (m_activeSkill->m_animationIndexLoopInto != static_cast<unsigned int>(-1) &&
         !m_activeSkill->m_interruptible) || (!m_skillLooping && !(m_skillTime > 0.0f)) ||
        static_cast<float>(HP()) <= 0.0f) {
        if (attemptStopOfActiveSkill()) {
            notifyAISkillComplete();
            setAIState(AISTATE_IDLE);
            updateAI(elapsed, true);
        }
    }
    if (!m_activeSkill || (m_skillTime > 0.0f && !m_skillInterrupted) ||
        m_activeSkill->getTargetType() != 2) return;
    bool stop = !m_targetCharacter.getObject() && !m_targetItem.getObject();
    if (!stop) stop = !validLineOfSight(*getLevel(), false);
    if (!stop) {
        CBaseUnit* target = m_targetCharacter.getObject();
        if (!target) target = m_targetItem.getObject();
        // The original reads the character reference here even for an item target.
        Ogre::Vector3 targetPosition = m_targetCharacter.getObject()->getPosition(true);
        Ogre::Vector3 position = getPosition(true);
        stop = !m_activeSkill->getIsInRange(position, targetPosition, this, target);
    }
    if (!stop) {
        stop = m_activeSkill->m_animationIndexLoopInto != static_cast<unsigned int>(-1) &&
               !m_activeSkill->m_interruptible;
        if (!stop && m_targetCharacter.getObject())
            stop = m_activeSkill->m_targetsDead ? m_targetCharacter.getObject()->alive()
                                                : !m_targetCharacter.getObject()->alive();
    }
    if (stop && attemptStopOfActiveSkill()) {
        notifyAISkillComplete();
        setAIState(AISTATE_IDLE);
        updateAI(elapsed, true);
    }
}

void CCharacter::createNewCharacter(std::wstring name)
{
    if (name.empty()) return;
    bool visible = m_bVisible;
    setVisible(false, true);
    if (m_pInventory) {
        CEquipment* right = getWeaponInRightHand();
        if (right) {
            m_pInventory->removeEquipment(right);
            delete right;
        }
        CEquipment* left = getWeaponInLeftHand();
        if (left) {
            m_pInventory->removeEquipment(left);
            delete left;
        }
        m_pInventory->removeListener(this);
        m_pInventory->freeInventory();
        if (m_pInventory) {
            delete m_pInventory;
            m_pInventory = NULL;
        }
    }
    convertCharacter(name, false);
    setVisible(visible, true);
}

bool CCharacter::performingSkill()
{
    return m_activeSkill && (m_activeSkill->m_animationID == -1 || m_activeSkill->m_interruptible)
        && (m_skillLooping || m_skillTime > 0.0f);
}

void CCharacter::removePet(CCharacter* pet)
{
    int index = petIndex(pet);
    if (index != -1) {
        int last = m_Followers.size() - 1;
        for (; index < last; ++index) {
            m_Followers[index] = m_Followers[index + 1];
            m_followerFlags[index] = m_followerFlags[index + 1];
        }
        m_Followers.pop_back();
        m_followerFlags.pop_back();
    }
}

unsigned int CCharacter::getArmorAndTrinketLevelCanEquip(bool base)
{
    ISA(static_cast<UNITTYPES::EUNITTYPES>(28));
    return base ? 0 : m_iUnitLevel;
}

unsigned int CCharacter::getWeaponLevelCanEquip(bool base)
{
    ISA(static_cast<UNITTYPES::EUNITTYPES>(28));
    return base ? 0 : m_iUnitLevel;
}

void CCharacter::stopParticles(bool immediate)
{
    for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
        if ((m_particleTriggers[i]->m_stopFlag59 || m_particleTriggers[i]->m_stopFlag5A)
            && m_particleTriggers[i]->m_particle)
            m_particleTriggers[i]->m_particle->Stop(immediate);
}

void CCharacter::setActiveSkill(CSkill* skill, bool keepCurrent)
{
    if (!keepCurrent) {
        m_activeSkillGuid = -1;
        m_activeSkill = NULL;
    }
    if (skill && m_pSkillManager) {
        int count = m_pSkillManager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0));
        for (int i = 0; i < count; ++i) {
            if (m_pSkillManager->getSkillByIndex(i) == skill) {
                if (!performingSkill()) m_activeSkill = skill;
                m_activeSkillGuid = skill->m_Guid;
                break;
            }
        }
    }
}

void CCharacter::cycleSkill(int direction)
{
    if (!m_pSkillManager) return;
    int count = m_pSkillManager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0));
    int start = m_pSkillManager->m_OtherSkills.find(m_activeSkill);
    if (count > 0) {
        int index = start;
        CSkill* skill;
        do {
            index += direction;
            if (index < 0) index = count - 1;
            else if (index >= count) index = 0;
            skill = m_pSkillManager->getSkillByIndex(index);
            if (skill) {
                skill->calculateEffectiveSkillLevel();
                if (skill->m_iEffectiveSkillLevel != 0 && skill->m_eActivationType != static_cast<ESKILL_ACTIVATION_TYPE>(4)
                    && !skill->m_bExecutedByProperty && skill->m_bEnabled) break;
            }
        } while (index != start);
        if (!performingSkill()) m_activeSkill = skill;
        m_activeSkillGuid = skill->m_Guid;
    }
}

void CCharacter::setAIState(EAIState state)
{
    m_eAIState = state;
    if (state != static_cast<EAIState>(2) && m_pathToFollow.getObject()) {
        CPathController* path = m_pathToFollow.getObject();
        CMonster* monster = dynamic_cast<CMonster*>(this);
        if (path->m_bWalkToPlayer || (monster && !monster->m_keepPathWhenAIChanges)) {
            if (!path->m_bUnknown136) {
                path->m_bUnknown136 = true;
                m_pathToFollow.getObject()->BroadcastEvent(110);
            }
            setPathToFollow(NULL);
        }
    }
}

CSkill* CCharacter::getKnownSpell(unsigned int index)
{
    if (index < 4 && m_pSkillManager && m_knownSpells[index] != EMPTY_WSTRING)
        return m_pSkillManager->getSkill(m_knownSpells[index], m_knownSpellLevels[index]);
    return NULL;
}

EAlignment CCharacter::alignment()
{
    if (hasEffect(static_cast<EEFFECT_TYPE>(0x50))) {
        if (m_alignment == static_cast<EAlignment>(1)) return static_cast<EAlignment>(2);
        if (m_alignment == static_cast<EAlignment>(2)) return static_cast<EAlignment>(1);
    }
    return m_alignment;
}

bool CCharacter::isEnemy(CCharacter* character)
{
    if (!character || character->alignment() == static_cast<EAlignment>(0) || alignment() == static_cast<EAlignment>(0)) return false;
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(1))) return true;
    if (character->alignment() == static_cast<EAlignment>(4) || alignment() == static_cast<EAlignment>(4)) return true;
    EAlignment own = alignment();
    return own != character->alignment();
}

bool CCharacter::isFriend(CCharacter* character)
{
    if (character->alignment() == static_cast<EAlignment>(0)) return true;
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(1))) return false;
    if (character->alignment() == static_cast<EAlignment>(4) || alignment() == static_cast<EAlignment>(4)) return false;
    EAlignment own = alignment();
    return own == character->alignment();
}

float CCharacter::attackRange()
{
    if (!m_attack) { selectAttack(static_cast<EATTACK_RANGE_TYPE>(0)); return 0.0f; }
    float range = m_attack->m_fRange;
    if (m_attackItem) {
        CEquipment* offhand = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1));
        CEquipment* mainhand = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0));
        if (mainhand && offhand && offhand->ISA(static_cast<UNITTYPES::EUNITTYPES>(8))) {
            if (offhand->ISA(static_cast<UNITTYPES::EUNITTYPES>(35)) || mainhand->ISA(static_cast<UNITTYPES::EUNITTYPES>(35))) {
                range = std::max(range, offhand->m_pAttackDescriptionOverride->m_fRange);
                range = std::max(range, mainhand->m_pAttackDescription->m_fRange);
            } else {
                range = std::min(range, offhand->m_pAttackDescriptionOverride->m_fRange);
                range = std::min(range, mainhand->m_pAttackDescription->m_fRange);
            }
        }
    }
    return (m_attackRadius * m_vScale.z + 0.2f) + range;
}

float CCharacter::viewAngle()
{
    float base = m_viewAngle;
    float flat = getEffectValue(static_cast<EEFFECT_TYPE>(0x0e), static_cast<EDAMAGE_TYPES>(7));
    float percent = getEffectValue(static_cast<EEFFECT_TYPE>(0x2a), static_cast<EDAMAGE_TYPES>(7));
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(0))) return 360.0f;
    float value = flat + base;
    return percent * value + value;
}

int CCharacter::dexterity()
{
    int base = m_rangedStat;
    float percent = ceilf(float(base) * getEffectValue(static_cast<EEFFECT_TYPE>(72), static_cast<EDAMAGE_TYPES>(7)) / 100.0f);
    float flat = ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(70), static_cast<EDAMAGE_TYPES>(7)));
    return int(percent) + int(flat) + base;
}

int CCharacter::maxMana()
{
    int base = std::max(int(float(m_maxManaBase) + m_maxManaBonus), 1);
    float percent = ceilf(float(base) * getEffectValue(static_cast<EEFFECT_TYPE>(0x13), static_cast<EDAMAGE_TYPES>(7)) / 100.0f);
    float flat = ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(4), static_cast<EDAMAGE_TYPES>(7)));
    return int(percent) + int(flat) + base;
}

bool CCharacter::isPetNearDeath()
{
    if (!m_pMaster || !m_bInvulnerable) return false;
    if (HP() <= 1) return true;
    int health = HP();
    return float(health) <= float(maxHP()) * 0.15f && m_eAIState == static_cast<EAIState>(10);
}

int CCharacter::magic()
{
    int base = m_magicStat;
    float percent = ceilf(float(base) * getEffectValue(static_cast<EEFFECT_TYPE>(18), static_cast<EDAMAGE_TYPES>(7)) / 100.0f);
    float flat = ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(3), static_cast<EDAMAGE_TYPES>(7)));
    return int(percent) + int(flat) + base;
}

float CCharacter::walkingSpeed()
{
    float percent = getEffectValue(static_cast<EEFFECT_TYPE>(0x15), static_cast<EDAMAGE_TYPES>(7));
    if (percent < 0.0f) {
        float resistance = getEffectValue(static_cast<EEFFECT_TYPE>(0x8c), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
        resistance = std::max(0.0f, std::min(1.0f, resistance));
        percent *= 1.0f - resistance;
    }
    float speed = m_walkingSpeed;
    speed = speed * percent / 100.0f + speed;
    return std::max(speed, 0.0f);
}

float CCharacter::runningSpeed()
{
    float percent = getEffectValue(static_cast<EEFFECT_TYPE>(0x15), static_cast<EDAMAGE_TYPES>(7));
    if (percent < 0.0f) {
        float resistance = getEffectValue(static_cast<EEFFECT_TYPE>(0x8c), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
        resistance = std::max(0.0f, std::min(1.0f, resistance));
        percent *= 1.0f - resistance;
    }
    float speed = m_runningSpeed;
    speed = speed * percent / 100.0f + speed;
    return std::max(speed, 0.0f);
}

void CCharacter::updateMana(float elapsed)
{
    if (m_eAIState == AISTATE_DYING || m_eAIState == AISTATE_DEAD) return;
    int maximum = maxMana();
    CGameGlobals* globals = CGameGlobals::getSingleton();
    modifyMana((float(maximum) / 100.0f) * globals->m_manaRegeneration * elapsed);
    float regeneration = getEffectValue(static_cast<EEFFECT_TYPE>(6), static_cast<EDAMAGE_TYPES>(7));
    float other = getEffectValue(static_cast<EEFFECT_TYPE>(0x7b), static_cast<EDAMAGE_TYPES>(7));
    modifyMana((other + regeneration) * elapsed);
}

bool CCharacter::blocked()
{
    int chance = getBlockChance();
    int roll = UTILITIES::randomIntegerBetweenVolatile(0, 100);
    return roll != 0 && roll != 100 && chance > roll;
}

float CCharacter::getDmgToReflectFromMissile()
{
    const EEFFECT_TYPE type = static_cast<EEFFECT_TYPE>(0x3c);
    if (!(getEffectValue(type, static_cast<EDAMAGE_TYPES>(7)) > 0.0f)) return 0.0f;
    float roll = UTILITIES::randomBetweenVolatile(0.0f, 100.0f);
    if (!(getEffectValue(type, static_cast<EDAMAGE_TYPES>(7)) >= roll)) return 0.0f;
    float minimum = 0.0f, maximum = 0.0f;
    CEffect* effect = m_pEffectManager ? m_pEffectManager->getEffect(type) : NULL;
    if (effect) { minimum = effect->m_reflectionMinimum; maximum = effect->m_reflectionMaximum; }
    if (m_pInventory) {
        for (int i = 0; i < 12; ++i) {
            CEquipment* item = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(i));
            if (item && item->m_pEffectManager) {
                effect = item->m_pEffectManager->getEffect(type);
                if (effect) {
                    minimum = std::max(minimum, effect->m_reflectionMinimum);
                    maximum = std::max(maximum, effect->m_reflectionMaximum);
                }
            }
        }
    }
    if (!(minimum > 0.0f || maximum > 0.0f)) return 1.0f;
    if (maximum <= 0.0f) return minimum / 100.0f;
    return UTILITIES::randomBetweenVolatile(minimum, maximum) / 100.0f;
}

void CCharacter::addToAvoidanceMap(CLevel& level)
{
    if (!m_pResourceManager || !m_pResourceManager->getLevel() || (!m_bVisible && !getEnabled())) return;
    if (!m_bBaseUnitFlag19B && !m_Followers.empty())
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_Followers.size()); ++i)
            if (m_followerFlags[i]) m_Followers[i]->addToAvoidanceMap(level);
    CBaseUnit::addToAvoidanceMap(level);
}

void CCharacter::unLearnSpell(std::wstring name, int level)
{
    if (!m_pSkillManager) return;
    for (unsigned int i = 0; i < 4; ++i) {
        if (m_knownSpells[i] == name && m_knownSpellLevels[i] == level) {
            CSkill* skill = m_pSkillManager->getSkill(m_knownSpells[i], level);
            if (skill) {
                if (m_activeSkillGuid == skill->m_Guid) m_activeSkillGuid = -1;
                if (m_leftSkillGuid == skill->m_Guid) m_leftSkillGuid = -1;
                if (m_leftMouseSkillGuid == skill->m_Guid) m_leftMouseSkillGuid = -1;
                if (m_activeSkill == skill) m_activeSkill = NULL;
                if (m_previousSkill == skill) m_previousSkill = NULL;
                m_pSkillManager->deleteSpecificSkill(skill);
            }
            for (; i < 3; ++i) {
                m_knownSpells[i] = m_knownSpells[i+1];
                m_knownSpellLevels[i] = m_knownSpellLevels[i+1];
            }
            m_knownSpells[3] = EMPTY_WSTRING;
            m_knownSpellLevels[3] = 0;
            break;
        }
    }
}

bool CCharacter::inDamageReactRange(CCharacter* character)
{
    Ogre::Vector3 source = getPosition(true);
    Ogre::Vector3 target = character->getPosition(true);
    Ogre::Vector3 distance(target.x - source.x, 0.0f, target.z - source.z);
    return distance.length() - m_fBaseUnitValue194 - character->m_fBaseUnitValue194 <= m_damageReactRange;
}

bool CCharacter::inInteractionRange()
{
    if (!m_targetItem.getObject()) return false;
    Ogre::Vector3 source = getPosition(true);
    Ogre::Vector3 target = m_targetItem.getObject()->getPosition(true);
    Ogre::Vector3 delta(target.x - source.x, 0.0f, target.z - source.z);
    float distance = delta.length();
    float range = 1.75f;
    if (m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(122)))
        range = m_isPathing ? 2.95f : 3.45f;
    return !(distance - m_fBaseUnitValue194 - m_targetItem.getObject()->m_fBaseUnitValue194 > range);
}

void CCharacter::setTargetItem(CItem* item)
{
    if ((m_eAIState == AISTATE_DYING || m_eAIState == AISTATE_DEAD) && item) return;
    m_targetItem.setObject(item);
    if (item) m_targetCharacter.setObject(NULL);
}

void CCharacter::notifyOfDeletion(CItem* item)
{
    if (m_attackItem == item) m_attackItem = NULL;
    if (m_targetItem.getObject() == item) setTargetItem(NULL);
}

bool CCharacter::inStrikeRange()
{
    if (!m_targetCharacter.getObject() && !m_targetItem.getObject()) return false;
    if (!m_attack) { selectAttack(static_cast<EATTACK_RANGE_TYPE>(0)); return false; }
    return inStrikeRange(m_targetCharacter.getObject(), m_targetItem.getObject(), NULL);
}

void CCharacter::updateAI(float elapsed, bool force)
{
    CCharacter* target = m_targetCharacter.getObject();
    if (target && (target->m_eAIState == AISTATE_DYING || target->m_eAIState == AISTATE_DEAD || !target->m_bInActiveRange)) setTarget(NULL);
    selectAttack(static_cast<EATTACK_RANGE_TYPE>(0));
    CLevel* level = getLevel();
    switch (m_eAIState) {
    case 3: attackAI(elapsed, *level); break;
    case 4: huntAI(elapsed, *level); break;
    case 5: dyingAI(elapsed, *level); break;
    case 7: getItemAI(elapsed, *level); break;
    case 9: approachAI(elapsed, *level); break;
    case 12: spawningAI(elapsed, *level); break;
    case 13: skillAI(elapsed, *level); break;
    case 14: performingSkillAI(elapsed); break;
    case 15: skillApproachAI(elapsed, *level, -1); break;
    case 29: interruptAI(elapsed, *level); break;
    case 32: fishingAICast(elapsed, *level); break;
    case 33: fishingAI(elapsed, *level); break;
    case 34: fishingAICatch(elapsed, *level); break;
    case 35: animationPlayAI(elapsed); break;
    case 40: immobileAI(elapsed); break;
    case 41: returnToTownAI(elapsed, *level); break;
    case 44: handInteractiveSequence(elapsed); break;
    default: break;
    }
}

void CCharacter::notifyOfDeletion(CCharacter* character)
{
    if (m_targetCharacter.getObject() == character) setTarget(NULL);
}

void CCharacter::setMaster(CCharacter* master)
{
    if (master) {
        m_pMaster = master;
        if (master->ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) m_masterFollowDelay = 0.5f;
        m_alignment = m_pMaster->alignment();
        if (m_pMaster) m_pMaster->ISA(static_cast<UNITTYPES::EUNITTYPES>(28));
    } else if (m_pMaster) m_pMaster = NULL;
    if (!isPetNearDeath() && m_eAIState != AISTATE_DYING && m_eAIState != AISTATE_DEAD
        && m_eAIState != static_cast<EAIState>(42) && m_eAIState != static_cast<EAIState>(41))
        setAIState(static_cast<EAIState>(0));
    setTarget(NULL);
    setTargetItem(NULL);
}

void CCharacter::doWeaponProcs(CEquipment* weapon, CBaseUnit* target)
{
    if (!target || !weapon || !weapon->m_pSkillManager) return;
    float radius = target->m_fBaseUnitValue194;
    Ogre::Vector3 targetPosition = target->getPosition(true);
    Ogre::Vector3 position = getPosition(true);
    Ogre::Vector3 direction(position.x - targetPosition.x, 0.0f, position.z - targetPosition.z);
    direction.normalise();
    Ogre::Vector3 effectPosition = direction * radius + targetPosition + Ogre::Vector3::UNIT_Y * 1.25f;
    for (unsigned int i = 0; i < static_cast<unsigned int>(weapon->m_pSkillManager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0))); ++i) {
        CSkill* skill = weapon->m_pSkillManager->getSkillByIndex(i);
        const Ogre::Quaternion& orientation = m_pSceneNode->getOrientation();
        weapon->m_pSkillManager->executeSkill(skill, this, static_cast<ESKILL_ACTIVATION_TYPE>(1),
            effectPosition, orientation, effectPosition, target);
    }
}

void CCharacter::playStrikeParticle(const Ogre::Vector3& from, const Ogre::Vector3& to,
                                    float distance, bool critical, bool blocked)
{
    if (!m_equipmentParticles[0]) return;
    Ogre::Vector3 direction(from.x - to.x, 0.0f, from.z - to.z);
    direction.normalise();
    Ogre::Vector3 position = direction * distance + to + Ogre::Vector3::UNIT_Y * 1.25f;
    if (blocked) {
        m_equipmentParticles[7]->setPosition(position);
        m_equipmentParticles[7]->Start();
    } else if (critical) {
        m_equipmentParticles[6]->setPosition(position);
        m_equipmentParticles[6]->Start();
    } else {
        m_equipmentParticles[0]->setPosition(position);
        m_equipmentParticles[0]->Start();
    }
}

void CCharacter::interruptAI(float elapsed, CLevel& level)
{
    if (!m_pUnitModel->animationPlayingSubstring("HIT")) setAIState(static_cast<EAIState>(0));
}

int CCharacter::getMaximumPetInstances()
{
    return m_pDataGroup->GetDataValue(L"MAXIMUM_PET_INSTANCES", 5);
}

std::wstring CCharacter::getDescription()
{
    return m_pDataGroup->GetDataValue(L"DESCRIPTION", EMPTY_WSTRING);
}

bool CCharacter::diesOnWarp()
{
    return m_pDataGroup->GetDataValue(L"DIES_ON_WARP", false);
}

bool CCharacter::getSpawnInvisible()
{
    return m_pDataGroup->GetDataValue(L"SPAWN_INVISIBLE", false);
}

bool CCharacter::getDestroyOnDeath()
{
    return m_pDataGroup->GetDataValue(L"DESTROY_ON_DEATH", false);
}

bool CCharacter::attachesToMaster()
{
    return m_pDataGroup->GetDataValue(L"ATTACHES_TO_MASTER", false);
}

std::wstring CCharacter::getMimicName()
{
    return m_pDataGroup->GetDataValue(L"DORMANTNAME", L"Chest");
}

int CCharacter::getDefaultMerchantTab()
{
    return m_pDataGroup->GetDataValue(L"MERCHANTTAB", 0);
}

std::wstring CCharacter::getSkillTabName(int tab)
{
    return m_pDataGroup->GetDataValue(L"SKILL_TAB" + STRINGS::GetValueAsWString(tab), L"Skills");
}

int CCharacter::baseArmorBonus()
{
    int base = m_naturalArmor + m_pInventory->m_iUnknown10;
    float flat = ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(8), 0.0f, L"INNATEARMOR"));
    return base + int(flat);
}

std::wstring CCharacter::getIntroCinematic()
{
    return m_pDataGroup->GetDataValue(L"INTRO_CINEMATIC", EMPTY_WSTRING);
}

float CCharacter::playerLevelForMerchantInventory()
{
    return m_pDataGroup->GetDataValue(L"PLAYER_LEVEL_FOR_MERCHANT", 0.0f);
}

void CCharacter::setAltSkillByName(std::wstring name)
{
    if (m_pUnitModel && m_pSkillManager) {
        CSkill* skill = m_pSkillManager->getSkill(STRINGS::StringUpper(name));
        if (skill) m_leftSkillGuid = skill->m_Guid;
    }
}

void CCharacter::setActiveSkillByName(std::wstring name)
{
    if (m_pUnitModel && m_pSkillManager) {
        CSkill* skill = m_pSkillManager->getSkill(STRINGS::StringUpper(name));
        if (skill) m_activeSkillGuid = skill->m_Guid;
    }
}

void CCharacter::deactivateEffect(CEffect* effect)
{
    EEFFECT_TYPE type = effect->m_eType;
    if (type == static_cast<EEFFECT_TYPE>(0x4a) || type == static_cast<EEFFECT_TYPE>(0x4c)
        || type == static_cast<EEFFECT_TYPE>(0x51) || type == static_cast<EEFFECT_TYPE>(0x69)
        || type == static_cast<EEFFECT_TYPE>(0x4b)) {
        if (!m_pSkillManager) return;
        std::wstring name = EMPTY_WSTRING;
        name = effect->m_sName;
        CSkill* skill = m_pSkillManager->getSkill(name, std::max(int(effect->m_iLevel), 1));
        if (skill) {
            if (m_activeSkillGuid == skill->m_Guid) m_activeSkillGuid = -1;
            if (m_leftSkillGuid == skill->m_Guid) m_leftSkillGuid = -1;
            if (m_leftMouseSkillGuid == skill->m_Guid) m_leftMouseSkillGuid = -1;
            if (m_activeSkill == skill) m_activeSkill = NULL;
            if (m_previousSkill == skill) m_previousSkill = NULL;
            m_pSkillManager->deleteSpecificSkill(skill);
        }
    }
}

void CCharacter::setLeftSkillByName(std::wstring name)
{
    if (m_pUnitModel && m_pSkillManager) {
        if (name == EMPTY_WSTRING) m_leftMouseSkillGuid = -1;
        else {
            CSkill* skill = m_pSkillManager->getSkill(STRINGS::StringUpper(name));
            if (skill) m_leftMouseSkillGuid = skill->m_Guid;
        }
    }
}

void CCharacter::handInteractiveSequence(float elapsed)
{
    if (performingSkill() && !attemptStopOfActiveSkill()) return;
    if (!m_pathToFollow.getObject()) stopPathing();
}

void CCharacter::unLearnSpell(int index)
{
    if (static_cast<unsigned int>(index) < 4 && m_knownSpells[index] != EMPTY_WSTRING)
        unLearnSpell(m_knownSpells[index], m_knownSpellLevels[index]);
}

void CCharacter::updateAttack(CLevel& level)
{
    if (!m_attack || !(m_attackTime > 0.0f) || m_eAIState == AISTATE_DYING || m_eAIState == AISTATE_DEAD) return;
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_pUnitModel->getAnimationEvents().size()); ++i) {
        if (m_pUnitModel->getAnimationEvents()[i]->getEventCode() == 0) {
            m_attackEvent = true;
            performAttack(NULL, 0, 1.0f, 1.0f, static_cast<EDAMAGE_TYPES>(7));
        }
    }
}

void CCharacter::interrupt(bool force)
{
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(2)))
        return;
    if (m_eAIState == 0x10 || m_eAIState == 0x29 || m_eAIState == 0x28 || m_eAIState == 0x23)
        return;
    if (m_activeSkill && (m_skillLooping || (m_skillTime > 0.0f && !m_skillInterrupted)))
    {
        if (!m_skillCanInterrupt)
            return;
        if (!m_pUnitModel->animationExists("HIT"))
        {
            blendAnimation(m_pUnitModel->findRandomAnimation("IDLE"), true, 0.2f, 1.0f, -1.0f);
            setAIState(static_cast<EAIState>(0));
            force = false;
        }
    }
    if (force && !m_pUnitModel->animationExists("HIT"))
        return;
    if (m_eAIState == 0x10 || m_eAIState == 0x28 || m_eAIState == 0x29 ||
        m_eAIState == AISTATE_DYING || m_eAIState == AISTATE_DEAD)
        return;
    m_attackTime = 0.0f;
    m_skillLooping = false;
    m_skillTime = 0.0f;
    if (m_pSkillManager)
        m_pSkillManager->stopAllSkills(false, false, false);
    if (force)
    {
        if (m_pUnitModel->animationExists("HIT"))
            blendAnimation(m_pUnitModel->findRandomAnimation("HIT"), false, 0.2f, 1.0f, -1.0f);
        m_pUnitModel->queueBlendAnimation("IDLE", true, 0.2f, 1.0f);
        setAIState(static_cast<EAIState>(0x1d));
    }
    if (m_isPathing)
        m_pathGraceTime = 10.0f;
    m_isPathing = false;
    m_pathDestination = m_vPosition;
    for (int i = 0; i < 2; ++i)
    {
        if (m_weaponTrails[i])
        {
            m_weaponTrails[i]->setActive(false);
            m_weaponTrails[i]->setVisible(false);
        }
    }
}

void CCharacter::updateSkillKeys(float)
{
    if (!m_activeSkill || (m_activeSkill->m_animationIndexLoopInto != static_cast<unsigned int>(-1) && !m_activeSkill->m_interruptible))
        return;
    if ((!m_skillLooping && !(m_skillTime > 0.0f)) || !m_pSkillManager ||
        m_eAIState == AISTATE_DYING || m_eAIState == AISTATE_DEAD)
        return;
    for (unsigned int i = 0; i < m_pUnitModel->getAnimationEvents().size(); ++i)
    {
        CKeyframe* key = m_pUnitModel->getAnimationEvents()[i];
        int event = key->getEventCode();
        if (event == 0 || event == 0x1c)
        {
            unsigned int animation = key->getAnimationIndex();
            if (animation == static_cast<unsigned int>(m_activeSkill->getAnimationIndexLoopEnd()) ||
                animation == static_cast<unsigned int>(m_activeSkill->getAnimationIndex()) ||
                animation == m_activeSkill->getAnimationIndexDW() ||
                animation == m_activeSkill->getAnimationIndexLoopInto() ||
                animation == m_activeSkill->getAnimationIndexDWLoopInto())
            {
                m_skillEventTriggered = true;
                const Ogre::Quaternion& orientation = m_pSceneNode->getOrientation();
                Ogre::Vector3 position = getPosition(true) + Ogre::Vector3(0.0f, -m_fBaseUnitValue194, 0.0f);
                m_pSkillManager->triggerSkillEvent(static_cast<ESKILL_EVENT_TYPE>(event == 0 ? 2 : 3), position, orientation, NULL);
            }
        }
        if (m_pUnitModel->getAnimationEvents()[i]->getEventCode() == 0xf)
            m_skillInterrupted = true;
    }
}

void CCharacter::setVisible(bool visible, bool immediate)
{
    visible = visible && !m_forcedHidden;
    if (visible == m_bVisible)
        return;
    for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
    {
        CParticleAnimationTrigger* trigger = m_particleTriggers[i];
        if ((!trigger->m_stopFlag59 && !trigger->m_stopFlag5A) || !trigger->m_particle)
            continue;
        if (trigger->m_stopFlag5A)
        {
            if (trigger->m_theme && !hasUnitTheme(trigger->m_theme))
                continue;
            if ((!trigger->m_stopOnDeath || (m_eAIState != AISTATE_DYING && m_eAIState != AISTATE_DEAD)) && visible)
                trigger->m_particle->Start();
            else
                trigger->m_particle->Stop(immediate);
        }
        if (!visible && trigger->m_stopFlag59)
            trigger->m_particle->setPosition(Ogre::Vector3(0.0f, -99999.0f, 0.0f));
    }
    if (!immediate)
    {
        setVisible(visible);
        return;
    }
    if (visible)
        m_characterVisible = true;
    else
    {
        for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
        {
            CParticleAnimationTrigger* trigger = m_particleTriggers[i];
            if (!trigger->m_stopFlag59 && !trigger->m_stopFlag5A && trigger->m_particle &&
                !trigger->m_particle->looping() && trigger->m_stopWhenHidden)
                trigger->m_particle->Stop(true);
        }
        m_characterVisible = false;
        for (int i = 0; i < 4; ++i)
        {
            if (m_weaponTrails[i])
            {
                m_weaponTrails[i]->setActive(false);
                m_weaponTrails[i]->setVisible(false);
            }
        }
        if (m_currentOpacity != 0.0f)
        {
            m_currentOpacity = 0.0f;
            updateOpacity(0.0f, true);
        }
    }
    CSceneNodeObject::setVisible(visible);
}

void CCharacter::updateOpacity(float elapsed, bool force)
{
    if (!m_pUnitModel)
        return;
    bool fadingIn = m_characterVisible;
    if (fadingIn && m_deathPathSilent && m_deathPathDistance / m_deathPath->m_fPathLength > 0.6f)
        fadingIn = false;
    if (!m_bInFadeRange)
        fadingIn = false;
    if (fadingIn)
    {
        if (!m_bVisible)
            setVisible(true, true);
        if (!(m_currentOpacity < 1.0f) && !force)
            return;
        m_currentOpacity += elapsed * 1.5f;
        if (m_currentOpacity > 1.0f)
            m_currentOpacity = 1.0f;
    }
    else
    {
        if (!(m_currentOpacity > 0.0f) && !force)
        {
            if (m_bVisible)
                setVisible(false, true);
            return;
        }
        if (!m_bInFadeRange)
            m_currentOpacity = 0.0f;
        if (m_deathPathSilent)
            m_currentOpacity += elapsed * -4.0f;
        else
            m_currentOpacity -= elapsed;
        if (m_currentOpacity < 0.0f)
            m_currentOpacity = 0.0f;
    }
    m_pUnitModel->setOpacity(m_currentOpacity);
    if (m_pInventory)
    {
        for (int i = 0; i < 12; ++i)
        {
            CEquipment* equipment = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(i));
            if (equipment)
            {
                if (equipment->getUnitModel())
                    static_cast<CGenericModel*>(equipment->getUnitModel())->setOpacity(m_currentOpacity);
                if (equipment->getUnitModelSecondary())
                    static_cast<CGenericModel*>(equipment->getUnitModelSecondary())->setOpacity(m_currentOpacity);
            }
        }
    }
    if (!fadingIn && force && m_bVisible)
        setVisible(false, true);
}

static void createEquipmentAndEquip(CCharacter* character, CDataGroup* data, const wchar_t* name, EEQUIP_LOCATIONS location, bool enchant)
{
    if (!name || !character || !data)
        return;
    CResourceManager* resources = character->getResourceManager();
    CInventory* inventory = character->getInventory();
    if (!resources || !inventory)
        return;
    CEquipment* equipment = resources->createEquipment(name, false, false);
    if (!equipment)
        return;
    inventory->pickupEquipment(equipment, true);
    if (enchant)
        equipment->enchant(true);
    if (location == 12)
        inventory->equipEquipmentIntoFirstFreeLocation(equipment);
    else
        inventory->equipEquipmentIntoSpecificLocation(equipment, location);
    static_cast<CGenericModel*>(equipment->getUnitModel())->getEntity()->setRenderQueueGroup(70);
}

void CCharacter::awardExperience(CLevel& level, CCharacter* source, int amount, bool fromMaster)
{
    if (m_experienceDisabled || ((m_eAIState == AISTATE_DYING || m_eAIState == AISTATE_DEAD) && amount > 0))
        return;
    if (!fromMaster)
    {
        int bonus = static_cast<int>(ceilf(static_cast<float>(amount) *
            (getEffectValue(static_cast<EEFFECT_TYPE>(0x44), static_cast<EDAMAGE_TYPES>(7)) / 100.0f)));
        amount = static_cast<unsigned int>(amount) + static_cast<unsigned int>(bonus);
    }
    if (source && source->HP() <= 0 && isPlayer())
    {
        incrementJournalStatistic(static_cast<EJournalStatistic>(6), 1);
        if (source->m_champion)
        {
            incrementJournalStatistic(static_cast<EJournalStatistic>(7), 1);
            if (source->getName() == L"Troll" || source->getName() == L"Troll Juggernaut")
                CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(0x13), 1);
        }
    }
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_Followers.size()); ++i)
        m_Followers[i]->awardExperience(level, source, amount, true);
    if (m_pMaster && !fromMaster)
        m_pMaster->awardExperience(level, source, amount, false);
    else
    {
        int previous = static_cast<int>(m_experience);
        int total = m_experience + static_cast<unsigned int>(amount);
        if (amount > 0 && previous > total)
            m_experience = 0x7fffffff;
        else
            m_experience = total < 0 ? 0 : total;
        ISA(static_cast<UNITTYPES::EUNITTYPES>(0x1c));
    }
    if (static_cast<int>(m_experience) >= CMasterResourceManager::getSingleton()->experienceGate(m_iUnitLevel) &&
        m_iUnitLevel < static_cast<unsigned int>(CMasterResourceManager::getSingleton()->getMaxLevel()))
    {
        levelUp();
        return;
    }
    if (static_cast<int>(m_experience) >= CMasterResourceManager::getSingleton()->experienceGate(m_iUnitLevel))
        m_experience = CMasterResourceManager::getSingleton()->experienceGate(m_iUnitLevel);
}

bool CCharacter::doWeaponSkill(CEquipment* equipment)
{
    Ogre::SceneNode* hand = m_pRightHandNode ? m_pRightHandNode : m_pLeftHandNode;
    if (!equipment || !equipment->getSkillManager())
        return false;
    Ogre::Vector3 position = hand->_getDerivedPosition();
    if (m_pInventory && m_pLeftHandNode && m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1)) == equipment)
        position = m_pLeftHandNode->_getDerivedPosition();
    Ogre::Vector3 relative = position - getPosition(true);
    relative.y = 0.0f;
    float distance = std::max(0.6f * m_fBaseUnitValue194, relative.length());
    position = getForward() * distance;
    position = getPosition(true) + position;
    position.y += 0.5f;
    bool executed = false;
    for (unsigned int i = 0; i < static_cast<unsigned int>(equipment->getSkillManager()->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0))); ++i)
    {
        CSkill* skill = equipment->getSkillManager()->getSkillByIndex(i);
        if (!skill->m_bExecutedByProperty && skill->m_bEnabled)
        {
            CBaseUnit* target = m_targetCharacter.getObject();
            if (!target)
                target = m_targetItem.getObject();
            Ogre::Vector3 aim = position + getForward() * 10.0f;
            const Ogre::Quaternion& orientation = m_pSceneNode->getOrientation();
            executed |= equipment->getSkillManager()->executeSkill(skill, this, static_cast<ESKILL_ACTIVATION_TYPE>(2), position, orientation, aim, target) != NULL;
        }
    }
    return executed;
}

bool CCharacter::inStrikeRange(CCharacter* target, CItem* item, CEquipment* equipment)
{
    if (!m_attack)
    {
        selectAttack(ATTACK_RANGE_DEFAULT);
        return false;
    }
    CItem* weapon = equipment ? equipment : m_attackItem;
    float bonus = weapon && weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x23))
        ? getEffectValue(static_cast<EEFFECT_TYPE>(0x4e), static_cast<EDAMAGE_TYPES>(7)) : 0.0f;
    if (target)
    {
        Ogre::Vector3 from = getPosition(true);
        Ogre::Vector3 to = target->getPosition(true);
        if (fabsf(to.y - from.y) > 2.5f && (!weapon || !weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x23))))
            return false;
        Ogre::Vector3 delta = to - from;
        delta.y = 0.0f;
        float distance = delta.length() - std::max(target->m_fBaseUnitValue194, 0.0f) - std::max(m_fBaseUnitValue194, 0.0f);
        float range = (m_attackRadius * m_vScale.z + 0.2f + m_attack->m_fStrikeRange) * m_attackRangeScale + bonus;
        return !(distance > range);
    }
    if (item)
    {
        Ogre::Vector3 from = getPosition(true);
        Ogre::Vector3 to = item->getPosition(true);
        if (fabsf(to.y - from.y) > 2.5f)
            return false;
        Ogre::Vector3 delta = to - from;
        delta.y = 0.0f;
        float distance = delta.length() - std::max(item->m_fBaseUnitValue194, 0.0f) - std::max(m_fBaseUnitValue194, 0.0f);
        float range = (m_attackRadius * m_vScale.z + 0.2f + m_attack->m_fStrikeRange) * m_attackRangeScale + bonus;
        return !(distance > range);
    }
    return true;
}

bool CCharacter::validLineOfSight(CLevel& level, bool flag)
{
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(4)))
        return true;
    if (!m_targetCharacter.getObject() && !m_targetItem.getObject())
        return true;
    Ogre::Vector3 modelPosition = static_cast<CPositionableObject*>(getUnitModel())->getPosition(false);
    Ogre::Vector3 start = getPosition(true) + modelPosition + Ogre::Vector3(0.0f, 1.5f, 0.0f);
    Ogre::Vector3 end = start;
    float height = start.y;
    if (m_targetItem.getObject())
    {
        Ogre::Vector3 position = m_targetItem.getObject()->getPosition(true);
        end.x = position.x;
        end.z = position.z;
    }
    else if (m_targetCharacter.getObject())
    {
        end = m_targetCharacter.getObject()->getPosition(true);
        float targetHeight = m_targetCharacter.getObject()->getPosition(true).y;
        height = targetHeight - getPosition(true).y + start.y;
    }
    else
    {
        end = start + m_vForward * 1.5f * m_attackRangeScale;
        height = end.y;
    }
    // The clamp measures the endpoint at the ray's starting height.
    float limit = Ogre::Vector3(end.x, start.y, end.z).length() / 5.0f;
    end.y = start.y + std::max(std::min(height - start.y, limit), -limit);
    return level.sightUnobstructed(start, end, flag);
}

bool CCharacter::inAttackRange(EATTACK_RANGE_TYPE)
{
    if (!m_targetCharacter.getObject() && !m_targetItem.getObject())
        return false;
    if (!m_attack)
    {
        selectAttack(ATTACK_RANGE_DEFAULT);
        if (!m_attack)
            return false;
    }
    bool ranged = (getWeaponInLeftHand() && getWeaponInLeftHand()->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x23))) ||
                  (getWeaponInRightHand() && getWeaponInRightHand()->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x23)));
    float bonus = ranged ? getEffectValue(static_cast<EEFFECT_TYPE>(0x4e), static_cast<EDAMAGE_TYPES>(7)) : 0.0f;
    float range = attackRange() * m_attackRangeScale;
    if (m_targetCharacter.getObject())
    {
        Ogre::Vector3 from = getPosition(true);
        Ogre::Vector3 to = m_targetCharacter.getObject()->getPosition(true);
        if (fabsf(to.y - from.y) > 2.5f && !ranged)
            return false;
        Ogre::Vector3 delta = to - from;
        delta.y = 0.0f;
        float distance = delta.length() - std::max(m_targetCharacter.getObject()->m_fBaseUnitValue194, 0.0f) - std::max(m_fBaseUnitValue194, 0.0f);
        return !(distance > range + bonus);
    }
    if (m_targetItem.getObject())
    {
        Ogre::Vector3 from = getPosition(true);
        Ogre::Vector3 to = m_targetItem.getObject()->getPosition(true);
        Ogre::Vector3 delta = to - from;
        delta.y = 0.0f;
        float distance = delta.length() - std::max(m_targetItem.getObject()->m_fBaseUnitValue194, 0.0f) - std::max(m_fBaseUnitValue194, 0.0f);
        return !(distance > range + bonus);
    }
    return true;
}

int CCharacter::inSkillRange(long long guid, bool ignoreMinimum)
{
    if (!m_targetCharacter.getObject() && !m_targetItem.getObject())
        return 2;
    if (guid == -1 && m_activeSkill)
        guid = m_activeSkill->m_Guid;
    if (!m_pSkillManager || !m_pSkillManager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0)))
        return 2;
    if (m_activeSkill != m_pSkillManager->getSkillByGuid(guid))
        m_activeSkill = m_pSkillManager->getSkillByGuid(guid);
    if (!m_activeSkill)
        return 2;
    float range = m_activeSkill->getRange();
    if (m_activeSkill->getTargetType() == 3 || m_activeSkill->getTargetType() == 10 || m_activeSkill->getTargetType() == 9)
        return 0;
    if (m_targetCharacter.getObject())
    {
        Ogre::Vector3 from = getPosition(true);
        Ogre::Vector3 to = m_targetCharacter.getObject()->getPosition(true);
        Ogre::Vector3 delta = to - from;
        delta.y = 0.0f;
        float distance = delta.length() - std::max(m_targetCharacter.getObject()->m_fBaseUnitValue194, 0.0f) - std::max(m_fBaseUnitValue194, 0.0f);
        if (distance > range)
            return 2;
        return ignoreMinimum ? 0 : m_activeSkill->getRangeMin() > distance;
    }
    if (m_targetItem.getObject())
    {
        Ogre::Vector3 from = getPosition(true);
        Ogre::Vector3 to = m_targetItem.getObject()->getPosition(true);
        Ogre::Vector3 delta = to - from;
        delta.y = 0.0f;
        float distance = delta.length() - std::max(m_targetItem.getObject()->m_fBaseUnitValue194, 0.0f) - std::max(m_fBaseUnitValue194, 0.0f);
        if (distance > range)
            return 2;
    }
    return 0;
}

CSkill* CCharacter::performSkill()
{
    if (!m_activeSkill)
        return NULL;
    if (m_activeSkill->m_allowsTurning)
    {
        CBaseUnit* target = m_targetCharacter.getObject();
        if (!target)
            target = m_targetItem.getObject();
        const Ogre::Quaternion& orientation = m_pSceneNode->getOrientation();
        Ogre::Vector3 position = getPosition(true) + Ogre::Vector3(0.0f, -m_fBaseUnitValue194, 0.0f);
        return m_pSkillManager->executeSkill(m_activeSkill, this, static_cast<ESKILL_ACTIVATION_TYPE>(3), position, orientation, m_targetPosition, target);
    }
    Ogre::Vector3 direction = m_targetPosition - getPosition(true);
    direction.y = 0.0f;
    direction.normalise();
    CBaseUnit* target = m_targetCharacter.getObject();
    if (!target)
        target = m_targetItem.getObject();
    Ogre::Quaternion orientation;
    orientation.FromAxes(Ogre::Vector3::UNIT_Y.crossProduct(direction), Ogre::Vector3::UNIT_Y, direction);
    Ogre::Vector3 position = getPosition(true) + Ogre::Vector3(0.0f, -m_fBaseUnitValue194, 0.0f);
    return m_pSkillManager->executeSkill(m_activeSkill, this, static_cast<ESKILL_ACTIVATION_TYPE>(3), position, orientation, m_targetPosition, target);
}

void CCharacter::startFishing()
{
    if (m_eAIState == 0x20 || m_eAIState == 0x21 || m_eAIState == 0x22)
        return;
    setAIState(static_cast<EAIState>(0x20));
    if (!m_pUnitModel->animationPlayingSubstring("FISHING_CAST"))
        blendAnimation("FISHING_CAST", false, 0.2f, 1.0f, -1.0f);
    if (!m_pUnitModel->animationQueued("FISHING_IDLE"))
        m_pUnitModel->queueBlendAnimation("FISHING_IDLE", true, 0.2f, 1.0f);
}

void CCharacter::addPet(CCharacter* pet)
{
    if (!pet || hasPet(pet))
        return;
    if (pet->getMaximumPetInstances() > 0)
    {
        int count = 0;
        for (unsigned int i = 0; i < m_Followers.size(); ++i)
            if (!m_Followers[i]->m_bInvulnerable && m_Followers[i]->getName() == pet->getName())
                ++count;
        if (count >= pet->getMaximumPetInstances())
        {
            int excess = count + 1 - pet->getMaximumPetInstances();
            for (unsigned int i = 0; i < m_Followers.size(); ++i)
            {
                CCharacter* follower = m_Followers[i];
                if (!follower->m_bInvulnerable && follower->getName() == pet->getName())
                {
                    follower->die(NULL, NULL, 0.0f, false);
                    if (--excess == 0)
                        break;
                }
            }
        }
    }
    m_Followers.push_back(pet);
    pet->setMaster(this);
    m_followerFlags.push_back(pet->m_bBaseUnitFlag19B);
}

void CCharacter::generateMerchantInventory()
{
    if (!m_pInventory || !m_pResourceManager || !m_pResourceManager->getLevel())
        return;
    float scale = playerLevelForMerchantInventory();
    int level = -1;
    if (scale > 0.0f && getLevel()->getPlayer())
        level = static_cast<int>(ceilf(static_cast<float>(getLevel()->getPlayer()->m_iUnitLevel) * scale));
    m_pInventory->m_bUnknown14 = false;
    TArrayList<CBaseUnit*> units(10);
    bool uniques = m_pDataGroup->GetDataValue(L"ALLOWS_MERCH_UNIQUES", false);
    bool magic = m_pDataGroup->GetDataValue(L"ALLOWS_MERCH_MAGIC", true);
    int flags = uniques ? 0 : 2;
    if (!magic)
        flags |= 4;
    if (!m_merchantSpawnClass)
        return;
    unsigned int count = UTILITIES::randomIntegerBetweenVolatile(m_merchantMinimum, m_merchantMaximum);
    m_pResourceManager->createUnitsBySpawnClass(m_merchantSpawnClass, units, count, this, this, level, flags);
    for (unsigned int i = 0; i < units.size(); ++i)
    {
        CEquipment* equipment = dynamic_cast<CEquipment*>(units[i]);
        if (ISA(static_cast<UNITTYPES::EUNITTYPES>(0x7f)) && !equipment->isMagical())
            equipment->enchant(true);
        else if (!uniques && equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x36)))
        {
            delete equipment;
            continue;
        }
        equipment->m_bUnknown348 = true;
        equipment->destroyItemText();
        CEquipment* added = m_pInventory->pickupEquipment(equipment, true);
        if (!added)
            delete equipment;
        else if (ISA(static_cast<UNITTYPES::EUNITTYPES>(0x7f)))
            added->recalculatePrice();
    }
}

void CCharacter::fameUp()
{
    ++m_fameLevel;
    CPlayer* player = dynamic_cast<CPlayer*>(this);
    if (player)
        m_iUnusedSkillPoints += player->getSkillPointsAwardedForFameLevel(m_iUnitLevel);
    if (m_levelSound)
        m_levelSound->queueGlobalSample(0x3d, 1.0f, 1.0f);
    CGameGlobals* globals = CGameGlobals::getSingleton();
    unsigned int rankIndex = std::min(static_cast<unsigned int>(m_fameLevel - 1), globals->m_configStrings.size() - 1);
    std::wstring rank = globals->m_configStrings[rankIndex];
    static std::wstring g_FameIncreased;
    if (g_FameIncreased.empty())
        g_FameIncreased = CStringTranslate::getSinglton()->getTranslateString(L"Fame Increased");
    static std::wstring g_YouAttainedRank;
    if (g_YouAttainedRank.empty())
        g_YouAttainedRank = CStringTranslate::getSinglton()->getTranslateString(L"You attain the rank of");
    m_pResourceManager->getGameUI()->setBigText(g_FameIncreased + L"!", 2.0f);
    m_pResourceManager->getGameUI()->setSmallText(g_YouAttainedRank + L" " + rank, 2.0f);
    if (m_fameLevel == CMasterResourceManager::getSingleton()->getMaxFameLevel())
    {
        CAchievement* achievement = CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(6));
        if (achievement)
            achievement->forceComplete();
    }
}

static void loadAndEquipSpawnClass(CCharacter* character, CDataGroup* data, const wchar_t* key, EEQUIP_LOCATIONS location)
{
    if (!data || !character || !character->getResourceManager() || !character->getInventory())
        return;
    CResourceManager* resources = character->getResourceManager();
    std::wstring name = data->GetDataValue(key, EMPTY_WSTRING);
    if (name.empty())
        return;
    CSpawnClass* spawnClass = resources->getSpawnClassByName(name);
    if (!spawnClass)
        return;
    TArrayList<CDataGroup*> groups;
    TArrayList<bool> enchant(5);
    spawnClass->rollSpawnClass(groups, &enchant, character, character, -1, static_cast<unsigned int>(-1), 0, -1, 0, 16);
    if (groups.size() == 0)
        return;
    if (location == 12)
    {
        for (unsigned int i = 0; i < groups.size(); ++i)
            createEquipmentAndEquip(character, data, groups[i]->GetDataValue(L"NAME", EMPTY_WSTRING).c_str(), static_cast<EEQUIP_LOCATIONS>(12), enchant[0]);
    }
    else
        createEquipmentAndEquip(character, data, groups[0]->GetDataValue(L"NAME", EMPTY_WSTRING).c_str(), location, enchant[0]);
}

void CCharacter::fishingAICatch(float, CLevel&)
{
    if (m_pUnitModel->animationPlayingSubstring("FISHING_CATCH"))
        return;
    static std::wstring g_Fishing;
    if (g_Fishing.empty())
        g_Fishing = CStringTranslate::getSinglton()->getTranslateString(L"Fishing");
    static std::wstring g_CaughtNothing;
    if (g_CaughtNothing.empty())
        g_CaughtNothing = CStringTranslate::getSinglton()->getTranslateString(L"You caught nothing");
    getLevel()->m_pGameClient->getGameUI()->openModalDialog(g_Fishing, g_CaughtNothing + L"!", false);
    setAIState(AISTATE_IDLE);
}

CCharacter* CCharacter::updateHP(CLevel& level, float elapsed)
{
    if (m_eAIState == AISTATE_DYING || m_eAIState == AISTATE_DEAD)
        return NULL;
    if (m_bInvulnerable && m_pMaster)
    {
        float maximum = static_cast<float>(maxHP());
        modifyHP(maximum / 100.0f * CGameGlobals::getSingleton()->m_petHPRegeneration * elapsed);
    }
    else if (CGameGlobals::getSingleton()->m_hpRegeneration != 0.0f)
    {
        float maximum = static_cast<float>(maxHP());
        modifyHP(maximum / 100.0f * CGameGlobals::getSingleton()->m_hpRegeneration * elapsed);
    }
    float change = getEffectValuesOfDamage() * elapsed;
    if (change < 0.0f)
        m_damageOverTimeTaken -= change;
    modifyHP(change);
    if (HP() > 0 || !m_pEffectManager)
        return NULL;
    CCharacter* killer = NULL;
    for (int group = 0; group < 2; ++group)
    {
        CEffectManager* manager = m_pEffectManager;
        TArrayList<CEffect*>& effects = manager->getActiveEffects(group);
        for (unsigned int i = 0; i < effects.size(); ++i)
        {
            CEffect* effect = effects[i];
            bool harmful = false;
            if (effect->m_eType == 7 || effect->m_eType == 0x34 || effect->m_eType == 0x7c)
                harmful = effect->value(static_cast<EEFFECT_VALUES>(0)) < 0.0f;
            if ((harmful || effects[i]->m_eType == 0x34) && effects[i]->m_sourceCharacter)
            {
                effects[i]->m_sourceCharacter->awardExperience(level, this, m_experienceReward, false);
                effects[i]->m_sourceCharacter->awardFame(level, this, m_fameReward, false);
                m_experienceReward = 0;
                m_fameReward = 0;
                killer = effects[i]->m_sourceCharacter;
                effects[i]->setOwner(NULL, true);
                break;
            }
        }
    }
    broadcastUnitState(static_cast<EUNIT_STATES>(4));
    return killer;
}

static void loadAndEquip(CCharacter* character, CDataGroup* data, const wchar_t* key, EEQUIP_LOCATIONS location)
{
    if (!data || !character)
        return;
    std::wstring name = data->GetDataValue(key, EMPTY_WSTRING);
    if (!name.empty())
        createEquipmentAndEquip(character, data, name.c_str(), location, false);
}

void CCharacter::createDefaultEquipment()
{
    if (!m_pDataGroup)
        return;
    CDataGroup* equipment = m_pDataGroup->GetDataGroupByName(L"EQUIPMENT", false);
    if (!equipment)
        return;
    loadAndEquip(this, equipment, L"RIGHTHAND", static_cast<EEQUIP_LOCATIONS>(0));
    loadAndEquip(this, equipment, L"LEFTHAND", static_cast<EEQUIP_LOCATIONS>(1));
    loadAndEquip(this, equipment, L"CHEST", static_cast<EEQUIP_LOCATIONS>(4));
    loadAndEquip(this, equipment, L"SHIELD", static_cast<EEQUIP_LOCATIONS>(11));
    loadAndEquip(this, equipment, L"SHOULDERS", static_cast<EEQUIP_LOCATIONS>(5));
    loadAndEquip(this, equipment, L"BOOTS", static_cast<EEQUIP_LOCATIONS>(6));
    loadAndEquip(this, equipment, L"GLOVES", static_cast<EEQUIP_LOCATIONS>(2));
    loadAndEquip(this, equipment, L"HELMET", static_cast<EEQUIP_LOCATIONS>(3));
    loadAndEquip(this, equipment, L"WEAPON", static_cast<EEQUIP_LOCATIONS>(12));
    loadAndEquipSpawnClass(this, equipment, L"SPAWNRIGHTHAND", static_cast<EEQUIP_LOCATIONS>(0));
    loadAndEquipSpawnClass(this, equipment, L"SPAWNLEFTHAND", static_cast<EEQUIP_LOCATIONS>(1));
    loadAndEquipSpawnClass(this, equipment, L"SPAWNCHEST", static_cast<EEQUIP_LOCATIONS>(4));
    loadAndEquipSpawnClass(this, equipment, L"SPAWNSHIELD", static_cast<EEQUIP_LOCATIONS>(11));
    loadAndEquipSpawnClass(this, equipment, L"SPAWNSHOULDERS", static_cast<EEQUIP_LOCATIONS>(5));
    loadAndEquipSpawnClass(this, equipment, L"SPAWNBOOTS", static_cast<EEQUIP_LOCATIONS>(6));
    loadAndEquipSpawnClass(this, equipment, L"SPAWNGLOVES", static_cast<EEQUIP_LOCATIONS>(2));
    loadAndEquipSpawnClass(this, equipment, L"SPAWNHELMET", static_cast<EEQUIP_LOCATIONS>(3));
    loadAndEquipSpawnClass(this, equipment, L"SPAWNCLASS", static_cast<EEQUIP_LOCATIONS>(12));
}

void CCharacter::transformCharacter(std::wstring name, float duration)
{
    CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(3))->forceComplete();
    if (STRINGS::StringUpper(name) == L"PET MIMIC")
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(0x1e))->forceComplete();
    if (duration == -999.0f)
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(4))->forceComplete();
    if (m_eAIState != 0x2a)
        setAIState(static_cast<EAIState>(0));
    m_transformationTime = duration;
    if (m_originalUnitGuid == -1)
        m_originalUnitGuid = m_iUnitValue1A0;
    std::wstring displayName = m_characterDisplayName;
    EAlignment previousAlignment = alignment();
    convertCharacter(name, true);
    setAlignment(previousAlignment);
    m_characterDisplayName = std::wstring(displayName);
    setVisible(false, true);
    setVisible(true, true);
}
