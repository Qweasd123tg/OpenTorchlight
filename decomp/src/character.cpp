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
