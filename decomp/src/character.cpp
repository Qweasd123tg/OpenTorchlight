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
            if ((harmful || effects[i]->m_eType == 0x34) && effects[i]->m_sourceCharacter.getObject())
            {
                effects[i]->m_sourceCharacter.getObject()->awardExperience(level, this, m_experienceReward, false);
                effects[i]->m_sourceCharacter.getObject()->awardFame(level, this, m_fameReward, false);
                m_experienceReward = 0;
                m_fameReward = 0;
                killer = effects[i]->m_sourceCharacter.getObject();
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

#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreSceneManager.h>

void CCharacter::configureParticleTrigger(CParticleAnimationTrigger* trigger, unsigned int bone)
{
    if (!trigger)
        return;
    bool everyBone = trigger->m_name == "Every Bone";
    Ogre::SceneNode* parent = m_pSceneNode;
    if (getUnitModel() && static_cast<CGenericModel*>(getUnitModel())->m_pSkeleton && trigger->m_name != "")
    {
        if (trigger->m_name == "Random" || everyBone || static_cast<CGenericModel*>(getUnitModel())->m_pSkeleton->hasBone(trigger->m_name))
        {
            std::string name = trigger->m_name;
            Ogre::Bone* node;
            if (trigger->m_name == "Random" || everyBone)
            {
                if (!everyBone)
                    bone = static_cast<unsigned int>(UTILITIES::randomBetweenVolatile(0.0f,
                        static_cast<float>(static_cast<CGenericModel*>(getUnitModel())->m_pSkeleton->getNumBones() - 1)));
                node = static_cast<CGenericModel*>(getUnitModel())->m_pSkeleton->getBone(static_cast<unsigned short>(bone));
                if (node)
                    name = node->getName();
            }
            else
                node = static_cast<CGenericModel*>(getUnitModel())->m_pSkeleton->getBone(name);
            trigger->m_nodeOwner = node;
            if (node)
            {
                trigger->m_name = node->getName();
                if (trigger->m_stopWhenHidden)
                {
                    parent = getResourceManager()->getSceneManager()->createSceneNode();
                    m_pSceneNode->addChild(parent);
                    trigger->m_node = parent;
                }
            }
        }
    }
    if (trigger->m_stopWhenHidden)
        trigger->m_particle->sceneNodeSetParent(parent, false);
}

void CCharacter::displayPath()
{
    if (!m_weaponTrails[3])
    {
        Ogre::SceneManager* scene = m_pResourceManager ? m_pResourceManager->getSceneManager() : NULL;
        m_weaponTrails[3] = new CWeaponTrail(scene, STRINGS::uniqueName("trail_"), 50, 2.0f);
        m_weaponTrails[3]->setMaterialName("WeaponTrail");
    }
    m_weaponTrails[3]->setActive(true);
    Ogre::Vector3 down = Ogre::Vector3::NEGATIVE_UNIT_Y;
    for (int i = 0; i < static_cast<int>(m_movementPath->m_lPoints.size()); ++i)
    {
        Ogre::Vector3 point = characterPathPoint(m_movementPath, i);
        point.y = getPosition(false).y;
        m_weaponTrails[3]->update(0.0f, &point, &down, false, NULL);
    }
}

void CCharacter::calculateActiveRange(const Ogre::Vector3& position)
{
    bool forced = m_pResourceManager->getEditorIsRunning();
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) || m_alwaysActive ||
        (m_pMaster && m_pMaster->m_bInActiveRange) || m_eAIState == 5)
        forced = true;
    if (m_activeSkill && (m_activeSkill->m_animationID == -1 || m_activeSkill->m_interruptible) &&
        (m_skillLooping || m_skillTime > 0.0f))
        forced = true;
    else if (m_pSkillManager && m_pSkillManager->m_UpdatingSkills.size())
        forced = true;
    float x = position.x - m_vPosition.x;
    float z = position.z - m_vPosition.z;
    float distance = sqrtf(x * x + 0.0f + z * z);
    float rangeModifier;
    if (forced)
    {
        rangeModifier = 1000.0f;
        m_bInActiveRange = true;
        m_bInFadeRange = true;
    }
    else
    {
        CLevel* level = getLevel();
        CLevelTemplateData* data = level ? level->getLevelTemplateData() : NULL;
        float range = data && !data->getUnitLightFade() ?
            CGameGlobals::getSingleton()->getOutdoorUnitActiveRange() :
            CGameGlobals::getSingleton()->getIndoorUnitActiveRange();
        rangeModifier = getEffectValueWithoutInventory(static_cast<EEFFECT_TYPE>(44), DAMAGE_TYPE_COUNT);
        level = getLevel();
        data = level ? level->getLevelTemplateData() : NULL;
        if (data && m_eAIState != 5 && m_eAIState != 6)
            rangeModifier += data->getSightRangeModifier();
        if (rangeModifier != 0.0f)
            range += (rangeModifier * range) / 100.0f;
        if (distance > range)
        {
            m_bInActiveRange = false;
            m_bInFadeRange = CGameGlobals::getSingleton()->getUnitNearRange() >= distance;
        }
        else
        {
            m_bInActiveRange = true;
            m_bInFadeRange = true;
        }
    }
    m_castsDynamicShadow = false;
    if (getCastsShadows())
    {
        CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
        if (settings->GetInt(KSETTINGS_SHADOWS_ENABLED) > 0)
        {
            m_castsDynamicShadow = true;
            if (!m_bInActiveRange || distance > CGameGlobals::getSingleton()->getUnitShadowRange() ||
                m_eAIState == 12 || fabsf(position.y - m_vPosition.y) > 3.0f || m_eAIState == 6)
                m_castsDynamicShadow = false;
        }
    }
    if (m_bInActiveRange)
    {
        if (rangeModifier != 0.0f)
            distance /= rangeModifier / 100.0f;
        m_aiThinkTier = 3;
        if (distance <= 10.0f)
            m_aiThinkTier = 0;
        else if (distance <= 15.0f)
            m_aiThinkTier = 1;
        else if (distance <= 20.0f)
            m_aiThinkTier = 2;
        else if (distance <= 25.0f)
            m_aiThinkTier = 3;
    }
    if (m_pMaster && m_pMaster->ISA(static_cast<UNITTYPES::EUNITTYPES>(28)))
        m_aiThinkTier = 0;
}

void CCharacter::createPathfinder(CLevel& level)
{
    if (m_pathfinder)
    {
        delete m_pathfinder;
        m_pathfinder = NULL;
    }
    float originX = level.topLeftX();
    float originY = level.topLeftY();
    m_pathfinder = new CAstarPathfinder(originX, originY, level.m_passWidth, level.m_passHeight,
        level.m_mapPassability, level.m_objectPassability, 0.4f);
    m_savedPathIterations = m_pathfinder->m_iMaxIterations;
    if (m_isPathing)
        m_pathGraceTime = 10.0f;
    m_isPathing = false;
    m_pathDestination = m_vPosition;
    if (m_pendingPetSpawn)
    {
        TArrayList<CDataGroup*> units;
        m_pendingPetSpawn->rollSpawnClass(units, NULL, this, this, -1, static_cast<unsigned int>(-1), 0, -1, 0, 0);
        for (unsigned int i = 0; i < units.size(); ++i)
        {
            CBaseUnit* unit = m_pResourceManager->createUnit(units[i], level.m_dungeonDepth, false, false);
            Ogre::Vector3 direction(0.0f, 0.0f, 1.0f);
            float angle = static_cast<float>(static_cast<double>(UTILITIES::randomBetweenVolatile(0.0f, 360.0f)) * 0.01745329252);
            MATH::rotateY(&direction, angle);
            unit->setDirection(direction);
            CCharacter* character = dynamic_cast<CCharacter*>(unit);
            if (character)
            {
                Ogre::Vector3 position = getPosition(true);
                Ogre::Vector3 spawnPosition = level.randomOpenPositionRange(position, 1.0f, 4.0f, true);
                level.addCharacter(character, spawnPosition, false);
                addPet(character);
            }
        }
        m_pendingPetSpawn = NULL;
    }
}

void CCharacter::updateBonePositions()
{
    if (m_pRightHandNode)
    {
        Ogre::Vector3 position = m_pUnitModel->getPosition(false);
        position += m_rightHandBone->_getDerivedPosition();
        m_pRightHandNode->setPosition(position);
        m_pRightHandNode->setOrientation(m_rightHandBone->_getDerivedOrientation());
    }
    if (m_fishingNode)
    {
        Ogre::Vector3 position = m_pUnitModel->getPosition(false);
        position += m_fishingBone->_getDerivedPosition();
        m_fishingNode->setPosition(position);
        m_fishingNode->setOrientation(m_fishingBone->_getDerivedOrientation());
    }
    if (m_pLeftHandNode)
    {
        Ogre::Vector3 position = m_pUnitModel->getPosition(false);
        position += m_leftHandBone->_getDerivedPosition();
        m_pLeftHandNode->setPosition(position);
        m_pLeftHandNode->setOrientation(m_leftHandBone->_getDerivedOrientation());
    }
    if (m_pShieldNode)
    {
        Ogre::Vector3 position = m_pUnitModel->getPosition(false);
        position += m_shieldBone->_getDerivedPosition();
        m_pShieldNode->setPosition(position);
        m_pShieldNode->setOrientation(m_shieldBone->_getDerivedOrientation());
    }
    if (m_pRightShoulderNode)
    {
        Ogre::Vector3 position = m_pUnitModel->getPosition(false);
        position += m_leftShoulderBone->_getDerivedPosition();
        m_pRightShoulderNode->setPosition(position);
        m_pRightShoulderNode->setOrientation(m_leftShoulderBone->_getDerivedOrientation());
    }
    if (m_pLeftShoulderNode)
    {
        Ogre::Vector3 position = m_pUnitModel->getPosition(false);
        position += m_rightShoulderBone->_getDerivedPosition();
        m_pLeftShoulderNode->setPosition(position);
        m_pLeftShoulderNode->setOrientation(m_rightShoulderBone->_getDerivedOrientation());
    }
    if (m_pHeadNode)
    {
        Ogre::Vector3 position = m_pUnitModel->getPosition(false);
        position += m_headBone->_getDerivedPosition();
        m_pHeadNode->setPosition(position);
        m_pHeadNode->setOrientation(m_headBone->_getDerivedOrientation());
    }
    for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
    {
        if (m_particleTriggers[i]->m_node && m_particleTriggers[i]->m_nodeOwner &&
            m_particleTriggers[i]->m_stopWhenHidden)
        {
            Ogre::Vector3 position = m_pUnitModel->getPosition(false);
            position += m_particleTriggers[i]->m_nodeOwner->_getDerivedPosition();
            m_particleTriggers[i]->m_node->setPosition(position);
            if (!m_particleTriggers[i]->m_stopFlag59)
                m_particleTriggers[i]->m_node->setOrientation(m_particleTriggers[i]->m_nodeOwner->_getDerivedOrientation());
        }
        else if (m_particleTriggers[i]->m_stopFlag59 && m_particleTriggers[i]->m_nodeOwner &&
                 m_particleTriggers[i]->m_particle)
        {
            Ogre::Vector3 position = m_particleTriggers[i]->m_nodeOwner->_getDerivedPosition();
            Ogre::Vector3 origin = getPosition(true);
            position += m_particleTriggers[i]->m_offset;
            position = getOrientation() * position;
            m_particleTriggers[i]->m_particle->setPosition(origin + position);
        }
    }
}

#include "UnitTheme.h"
#include "UnitThemeParticle.h"
#include "ParticlePreloader.h"

void CCharacter::createSpecificUnitThemeParticles(CUnitTheme* theme)
{
    if (!theme || !m_pUnitModel)
        return;
    for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
        if (m_particleTriggers[i]->m_particle && m_particleTriggers[i]->m_theme == theme)
            return;
    for (unsigned int i = 0; i < theme->m_particles.size(); ++i)
    {
        CUnitThemeParticle* descriptor = theme->m_particles[i];
        if (!ISA(static_cast<UNITTYPES::EUNITTYPES>(descriptor->m_iUnitTypeID)))
            continue;
        unsigned int count = descriptor->m_iCount ? descriptor->m_iCount : 1;
        if (descriptor->m_wstrBone == L"Every Bone")
            count = static_cast<CGenericModel*>(getUnitModel())->m_pSkeleton->getNumBones();
        for (unsigned int bone = 0; bone < count; ++bone)
        {
            CParticleAnimationTrigger* trigger = new CParticleAnimationTrigger;
            trigger->m_resources = m_pResourceManager;
            trigger->m_particle = NULL;
            trigger->m_stopOnDeath = false;
            trigger->m_animationIndex = -1;
            trigger->m_offset = Ogre::Vector3::ZERO;
            trigger->m_node = NULL;
            trigger->m_nodeOwner = NULL;
            trigger->m_theme = NULL;
            trigger->m_stopWhenHidden = true;
            trigger->m_stopFlag59 = false;
            trigger->m_stopFlag5A = false;
            m_particleTriggers.add(trigger);
            std::wstring name = STRINGS::StringUpper(CMasterResourceManager::getSingleton()->m_pParticlePreloader->getParticleNameByFileName(descriptor->m_wstrFile));
            if (name.empty())
            {
                name = STRINGS::StringUpper(descriptor->m_wstrFile);
                CMasterResourceManager::getSingleton()->m_pParticlePreloader->LoadParticle(name, name);
            }
            trigger->m_particle = CMasterResourceManager::getSingleton()->m_pParticlePreloader->GetParticle(m_pResourceManager, STRINGS::StringUpper(descriptor->m_wstrFile).c_str());
            if (trigger->m_particle)
            {
                trigger->m_particle->setPosition(Ogre::Vector3::ZERO);
                trigger->m_stopOnDeath = true;
                trigger->m_animationIndex = -1;
                trigger->m_theme = theme;
                trigger->m_stopWhenHidden = descriptor->m_bAttaches;
                trigger->m_stopFlag59 = descriptor->m_bFollows;
                STRINGS::StringConvertToNarrow(descriptor->m_wstrBone, trigger->m_name);
                configureParticleTrigger(trigger, bone);
            }
        }
    }
}

void CCharacter::unitThemeUpdated(CUnitTheme* theme, bool stopping)
{
    if (!stopping)
    {
        bool exists = false;
        for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
            if (m_particleTriggers[i]->m_theme == theme && m_particleTriggers[i]->m_particle)
            {
                exists = true;
                break;
            }
        if (!exists)
            createSpecificUnitThemeParticles(theme);
    }
    for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
    {
        if (m_particleTriggers[i]->m_theme != theme || !m_particleTriggers[i]->m_particle)
            continue;
        if (stopping)
            m_particleTriggers[i]->m_particle->Stop(!m_particleTriggers[i]->m_particle->getVisible());
        else
        {
            if (m_particleTriggers[i]->m_nodeOwner)
            {
                if (m_particleTriggers[i]->m_stopWhenHidden && m_particleTriggers[i]->m_node)
                {
                    m_particleTriggers[i]->m_node->setPosition(m_particleTriggers[i]->m_nodeOwner->_getDerivedPosition());
                    if (!m_particleTriggers[i]->m_stopFlag59)
                        m_particleTriggers[i]->m_node->setOrientation(m_particleTriggers[i]->m_nodeOwner->_getDerivedOrientation());
                }
                else if (!m_particleTriggers[i]->m_stopWhenHidden)
                {
                    Ogre::Vector3 modelPosition = m_pUnitModel->getPosition(false);
                    Ogre::Vector3 origin = getPosition(true);
                    Ogre::Vector3 bonePosition = m_particleTriggers[i]->m_nodeOwner->_getDerivedPosition();
                    Ogre::Vector3 position = getOrientation() * bonePosition;
                    m_particleTriggers[i]->m_particle->setPosition((position + origin) + modelPosition);
                }
            }
            else if (!m_particleTriggers[i]->m_stopWhenHidden)
            {
                Ogre::Vector3 modelPosition = m_pUnitModel->getPosition(false);
                Ogre::Vector3 origin = getPosition(true);
                Ogre::Vector3 position = getOrientation() * m_particleTriggers[i]->m_offset;
                m_particleTriggers[i]->m_particle->setPosition((position + origin) + modelPosition);
            }
            m_particleTriggers[i]->m_particle->Start();
        }
    }
}

#include "UnitThemes.h"
void CCharacter::createAdditionalUnitThemeParticles()
{
    if (!m_pUnitModel)
        return;
    CUnitThemes* themes = CUnitThemes::getSingleton();
    for (unsigned int themeIndex = 0; themeIndex < themes->getThemes().size(); ++themeIndex)
    {
        CUnitTheme* theme = themes->getThemes()[themeIndex];
        bool exists = false;
        for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
            if (m_particleTriggers[i]->m_particle && m_particleTriggers[i]->m_theme == theme)
            {
                exists = true;
                break;
            }
        if (exists)
            continue;
        for (unsigned int i = 0; i < theme->m_particles.size(); ++i)
        {
            CUnitThemeParticle* descriptor = theme->m_particles[i];
            if (!ISA(static_cast<UNITTYPES::EUNITTYPES>(descriptor->m_iUnitTypeID)))
                continue;
            unsigned int count = descriptor->m_iCount ? descriptor->m_iCount : 1;
            if (descriptor->m_wstrBone == L"Every Bone")
                count = static_cast<CGenericModel*>(getUnitModel())->m_pSkeleton->getNumBones();
            for (unsigned int bone = 0; bone < count; ++bone)
            {
                CParticleAnimationTrigger* trigger = new CParticleAnimationTrigger;
                trigger->m_resources = m_pResourceManager;
                trigger->m_particle = NULL;
                trigger->m_stopOnDeath = false;
                trigger->m_animationIndex = -1;
                trigger->m_offset = Ogre::Vector3::ZERO;
                trigger->m_node = NULL;
                trigger->m_nodeOwner = NULL;
                trigger->m_theme = NULL;
                trigger->m_stopWhenHidden = true;
                trigger->m_stopFlag59 = false;
                trigger->m_stopFlag5A = false;
                m_particleTriggers.add(trigger);
                std::wstring name = STRINGS::StringUpper(CMasterResourceManager::getSingleton()->m_pParticlePreloader->getParticleNameByFileName(descriptor->m_wstrFile));
                if (name.empty())
                {
                    name = STRINGS::StringUpper(descriptor->m_wstrFile);
                    CMasterResourceManager::getSingleton()->m_pParticlePreloader->LoadParticle(name, name);
                }
                trigger->m_particle = CMasterResourceManager::getSingleton()->m_pParticlePreloader->GetParticle(m_pResourceManager, STRINGS::StringUpper(descriptor->m_wstrFile).c_str());
                if (trigger->m_particle)
                {
                    trigger->m_particle->setPosition(Ogre::Vector3::ZERO);
                    trigger->m_stopOnDeath = true;
                    trigger->m_animationIndex = -1;
                    trigger->m_theme = theme;
                    trigger->m_stopWhenHidden = true;
                    trigger->m_stopFlag59 = false;
                    STRINGS::StringConvertToNarrow(descriptor->m_wstrBone, trigger->m_name);
                    configureParticleTrigger(trigger, bone);
                }
            }
        }
    }
}

void CCharacter::getBones()
{
    if (!m_pUnitModel)
        return;
    Ogre::SkeletonInstance* skeleton = m_pUnitModel->m_pSkeleton;
    if (skeleton)
    {
        for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
            if (m_particleTriggers[i]->m_nodeOwner)
                m_particleTriggers[i]->m_nodeOwner = skeleton->getBone(m_particleTriggers[i]->m_name);
        const char* right = NULL;
        if (skeleton->hasBone("tag_righthand"))
            right = "tag_righthand";
        else if (skeleton->hasBone("Bip01 R Hand"))
            right = "Bip01 R Hand";
        if (right)
        {
            m_rightHandBone = skeleton->getBone(right);
            m_fishingBone = skeleton->getBone(right);
            if (!m_pRightHandNode)
            {
                m_pRightHandNode = m_pResourceManager->getSceneManager()->createSceneNode();
                m_pSceneNode->addChild(m_pRightHandNode);
                float scale = m_pDataGroup->GetDataValue(L"WEAPON_SCALE", 1.0f);
                m_pRightHandNode->setScale(scale, scale, scale);
            }
            if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) && !m_fishingNode)
            {
                m_fishingNode = m_pResourceManager->getSceneManager()->createSceneNode();
                m_pSceneNode->addChild(m_fishingNode);
                m_fishingNode->setVisible(false, true);
            }
        }
        const char* left = NULL;
        if (skeleton->hasBone("tag_lefthand"))
            left = "tag_lefthand";
        else if (skeleton->hasBone("Bip01 L Hand"))
            left = "Bip01 L Hand";
        if (left)
        {
            m_leftHandBone = skeleton->getBone(left);
            if (!m_pLeftHandNode)
            {
                m_pLeftHandNode = m_pResourceManager->getSceneManager()->createSceneNode();
                m_pSceneNode->addChild(m_pLeftHandNode);
                float scale = m_pDataGroup->GetDataValue(L"WEAPON_SCALE", 1.0f);
                m_pLeftHandNode->setScale(scale, scale, scale);
            }
        }
        if (skeleton->hasBone("tag_leftarm"))
        {
            m_shieldBone = skeleton->getBone("tag_leftarm");
            if (!m_pShieldNode)
            {
                m_pShieldNode = m_pResourceManager->getSceneManager()->createSceneNode();
                m_pSceneNode->addChild(m_pShieldNode);
                float scale = m_pDataGroup->GetDataValue(L"SHIELD_SCALE", 1.0f);
                m_pShieldNode->setScale(scale, scale, scale);
            }
        }
        if (skeleton->hasBone("Bip01 Head"))
        {
            m_headBone = skeleton->getBone("Bip01 Head");
            if (!m_pHeadNode)
            {
                m_pHeadNode = m_pResourceManager->getSceneManager()->createSceneNode();
                m_pSceneNode->addChild(m_pHeadNode);
            }
        }
        if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) && skeleton->hasBone("Bip01 R Clavicle"))
        {
            m_leftShoulderBone = skeleton->getBone("Bip01 R Clavicle");
            if (!m_pRightShoulderNode)
            {
                m_pRightShoulderNode = m_pResourceManager->getSceneManager()->createSceneNode();
                m_pSceneNode->addChild(m_pRightShoulderNode);
            }
        }
        if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) && skeleton->hasBone("Bip01 L Clavicle"))
        {
            m_rightShoulderBone = skeleton->getBone("Bip01 L Clavicle");
            if (!m_pLeftShoulderNode)
            {
                m_pLeftShoulderNode = m_pResourceManager->getSceneManager()->createSceneNode();
                m_pSceneNode->addChild(m_pLeftShoulderNode);
            }
        }
    }
    if (m_pInventory)
        for (unsigned int i = 0; i < 12; ++i)
        {
            CEquipment* equipment = m_pInventory->getEquipmentInSlot(i);
            if (equipment)
                equipment->attachToGivenLocation(m_pInventory->m_pPositionableObject, static_cast<EEQUIP_LOCATIONS>(i));
        }
    updateBonePositions();
}

void CCharacter::displayDamageAbsorbed(float elapsed)
{
    if (!m_damageDisplayEnabled) return;
    m_damageDisplayTime -= elapsed;
    if (m_damageOverTimeTaken == 0.0f || m_damageDisplayTime >= 0.0f) return;
    m_damageDisplayTime = 0.5f;
    bool friendly = ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) ||
        (m_pMaster && m_pMaster->ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) || alignment() == static_cast<EAlignment>(1);
    CEGUI::colour first(1.0f, friendly ? 0.2f : 0.77f, friendly ? 0.2f : 0.0f, 1.0f);
    CEGUI::colour second(1.0f, friendly ? 0.2f : 0.77f, friendly ? 0.2f : 0.0f, 1.0f);
    std::string text = STRINGS::GetValueAsString(static_cast<int>(std::ceil(m_damageOverTimeTaken)));
    m_pResourceManager->getLevel()->m_pGameClient->getGameUI()->addTextEvent(getPosition(true) + Ogre::Vector3::UNIT_Y, text, 1.0f, 255.0f, second, first);
    m_damageOverTimeTaken = 0.0f;
}

bool CCharacter::isEffectValidForUnit(CCharacter*, CBaseUnit* target, CEffect* effect)
{
    if (!effect) return false;
    int type = static_cast<int>(effect->m_eType);
    if (!m_characterFlag52F && (type == 52 || type == 7 || type == 124)) return false;
    switch (type)
    {
    case 65:
        return canLearnSpell(effect->m_sName, static_cast<int>(effect->value(static_cast<EEFFECT_VALUES>(0))));
    case 110:
        return true;
    case 6:
    case 123:
    case 7:
    case 124:
        if (effect->value(static_cast<EEFFECT_VALUES>(0)) < 0.0f || !target ||
            !target->ISA(static_cast<UNITTYPES::EUNITTYPES>(33)) || !target->dontUseOnFull()) return true;
        if (type == 6 || type == 123)
        {
            int current = mana();
            if (current == maxMana()) return false;
        }
        else
        {
            int current = HP();
            if (current == maxHP()) return false;
        }
        return !m_pEffectManager || !m_pEffectManager->hasEffect(effect->m_sName);
    case 45:
    {
        CLevel* level = m_pResourceManager->getLevel();
        if (!level) return false;
        CLevelTemplateData* data = level->getLevelTemplateData();
        if (data && data->permitsPortal())
        {
            incrementJournalStatistic(static_cast<EJournalStatistic>(13), 1);
            return true;
        }
        if (m_levelSound) m_levelSound->queueGlobalSample(51, 0.0f, 0.1f);
        return false;
    }
    case 52:
        return m_eAIState != static_cast<EAIState>(5) && m_eAIState != static_cast<EAIState>(6);
    case 64:
        return !hasUnitTheme(L"STUNNED");
    case 80:
        return m_eAIState != static_cast<EAIState>(5) && m_eAIState != static_cast<EAIState>(6) &&
            m_alignment == static_cast<EAlignment>(2) && !isPlayer() && (!m_pMaster || !m_pMaster->isPlayer());
    case 141:
    {
        CLevel* level = m_pResourceManager->getLevel();
        if (!level) return false;
        CLevelTemplateData* data = level->getLevelTemplateData();
        return data && (data->permitsPortal() || data->isTown());
    }
    }
    if (target && target->ISA(static_cast<UNITTYPES::EUNITTYPES>(33)) && target->dontUseOnFull())
    {
        if (!ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) return false;
        if (m_pEffectManager && m_pEffectManager->hasEffect(effect->m_sName)) return false;
    }
    return effect->m_activation == EFFECT_ACTIVATION_PASSIVE ||
        effect->m_activation == EFFECT_ACTIVATION_DYNAMIC || effect->m_activation == EFFECT_ACTIVATION_TRANSFER;
}

void CCharacter::modifyHP(float change)
{
    if (!m_characterFlag52F && change < 0.0f) return;
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(167)) && hasUnitTheme(L"MIMICIDLE")) return;
    float oldHP = m_fHPFloat;
    float currentHP = oldHP;
    if (oldHP <= 0.0f && change > 0.0f)
    {
        if (static_cast<float>(maxHP()) > change) return;
        currentHP = m_fHPFloat;
    }
    if (currentHP == 0.0f && change >= static_cast<float>(maxHP())) m_experienceReward = 0;
    if (getIsInGodMode())
    {
        m_fHPFloat = static_cast<float>(maxHP());
        return;
    }
    if (!ISA(static_cast<UNITTYPES::EUNITTYPES>(28)))
        broadcastHPThreshholdEvents(static_cast<float>(m_maxHPBase), m_fHPFloat, m_previousThresholdHP, change);
    m_fHPFloat += change;
    if (m_fHPFloat > static_cast<float>(maxHP())) m_fHPFloat = static_cast<float>(maxHP());
    if (m_bInvulnerable && m_fHPFloat < 1.0f)
    {
        if (m_pEffectManager) m_pEffectManager->removeEffect(L"POISON", true);
        m_fHPFloat = 1.0f;
    }
    else if (m_fHPFloat < 0.0f)
    {
        m_fHPFloat = 0.0f;
        forceDisplayOfDamageAbsorbed();
    }
    if (m_previousThresholdHP > m_fHPFloat) m_previousThresholdHP = m_fHPFloat;
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28)))
    {
        if (m_fHPFloat <= static_cast<float>(maxHP()) * 0.2f &&
            oldHP > static_cast<float>(maxHP()) * 0.2f && m_levelSound)
            m_levelSound->queueGlobalSample(52, 0.0f, 0.1f);
    }
    else if (m_pMaster && m_pMaster->isPlayer() && m_bInvulnerable && oldHP > 1.0f &&
        m_fHPFloat <= 1.0f && m_pMaster->getFollower(0) == this && m_pMaster->m_levelSound)
        m_pMaster->m_levelSound->queueGlobalSample(45, 1.0f, 1.0f);
}

#include "Affix.h"
void CCharacter::executeProcs(EEFFECT_TYPE type, CBaseUnit* target)
{
    if (hasEffect(type) && m_pSkillManager)
        for (int group = 0; group < 2; ++group)
        {
            TArrayList<CEffect*>& effects = m_pEffectManager->getActiveEffects(group);
            for (unsigned int i = 0; i < effects.size(); ++i)
            {
                if (effects[i]->m_eType != type) continue;
                int roll = UTILITIES::randomIntegerBetweenVolatile(0, 100);
                if (!(effects[i]->value(static_cast<EEFFECT_VALUES>(0)) >= static_cast<float>(roll))) continue;
                CSkill* skill = m_pSkillManager->getSkill(effects[i]->m_sName, effects[i]->m_iLevel);
                if (!skill) continue;
                switch (static_cast<int>(type))
                {
                case 74: case 75: case 81: case 105:
                {
                    m_procTime = 1.0f;
                    Ogre::Vector3 destination = target ? target->getPosition(true) : getPosition(true);
                    const Ogre::Quaternion& orientation = m_pSceneNode->getOrientation();
                    Ogre::Vector3 source = getPosition(true);
                    m_pSkillManager->executeSkill(skill, this, static_cast<ESKILL_ACTIVATION_TYPE>(1), source, orientation, destination, target);
                    break;
                }
                case 76:
                {
                    Ogre::Vector3 destination = target ? target->getPosition(true) : getPosition(true);
                    const Ogre::Quaternion& orientation = m_pSceneNode->getOrientation();
                    Ogre::Vector3 source = target ? target->getPosition(true) : getPosition(true);
                    m_pSkillManager->executeSkill(skill, this, static_cast<ESKILL_ACTIVATION_TYPE>(1), source, orientation, destination, target);
                    break;
                }
                }
            }
        }
    if (m_pInventory) m_pInventory->executeProcs(type, target);
}

void CCharacter::applyDamageEffects(CCharacter* target, float amount, int (*damages)[2], unsigned int count, bool force)
{
    if (amount <= 0.0f || !target || (count == 1 && damages[0][0] == 0)) return;
    int sums[7] = {0,0,0,0,0,0,0};
    for (unsigned int i = 0; i < count; ++i)
        if (damages[i][0] != 0)
            sums[damages[i][0]] = static_cast<int>(static_cast<float>(sums[damages[i][0]]) + static_cast<float>(damages[i][1]));
    for (unsigned int type = 0; type < 7; ++type)
    {
        int damage = sums[type];
        if (damage <= 0) continue;
        int defense = m_damageDefense[type];
        if (!force)
        {
            float roll = UTILITIES::randomBetweenVolatile(0.0f, 1.0f);
            float chance = static_cast<float>(damage) / ((static_cast<float>(defense) + static_cast<float>(damage)) * 5.0f);
            if (!(chance >= roll)) continue;
        }
        const wchar_t* normal;
        const wchar_t* player;
        switch (type)
        {
        case 2: normal=L"DAMAGEEFFECTONFIRE"; player=L"DAMAGEEFFECTONFIREPLAYER"; break;
        case 3: normal=L"DAMAGEEFFECTFROZEN"; player=L"DAMAGEEFFECTFROZENPLAYER"; break;
        case 4: normal=L"DAMAGEEFFECTELECTRICITY"; player=L"DAMAGEEFFECTELECTRICITYPLAYER"; break;
        case 5: normal=L"DAMAGEEFFECTPOISONED"; player=L"DAMAGEEFFECTPOISONEDPLAYER"; break;
        default: return;
        }
        CAffix* affix = NULL;
        if (m_pEffectManager)
            affix = m_pEffectManager->getAffix(isPlayer() ? player : normal);
        if (!affix)
        {
            unsigned int level = target->m_iUnitLevel;
            affix = addAffix(isPlayer() ? player : normal, level, target, 1.0f);
        }
        if (affix)
        {
            if (type == 2) affix->m_fDuration = UTILITIES::randomBetweenVolatile(3.0f, 7.0f);
            else if (type == 3)
            {
                if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) affix->m_fDuration = UTILITIES::randomBetweenVolatile(1.5f, 2.0f);
                else affix->m_fDuration = UTILITIES::randomBetweenVolatile(3.0f, 4.0f);
            }
            else affix->m_fDuration = UTILITIES::randomBetweenVolatile(3.0f, 5.0f);
        }
        return;
    }
}

#include "Console.h"
int CCharacter::modifyDamage(int damage, EDAMAGE_TYPES type, int totalDamage, float scale)
{
    int armor;
    if (type == static_cast<EDAMAGE_TYPES>(0))
    {
        int maximum = AC();
        armor = UTILITIES::randomIntegerBetweenVolatile(minimumAC(), maximum);
    }
    else
    {
        int maximum = std::max(0, static_cast<int>(static_cast<float>(damageDefense(type))));
        armor = UTILITIES::randomIntegerBetweenVolatile(static_cast<int>(std::ceil(static_cast<float>(maximum) * 0.5f)), maximum);
    }
    if (totalDamage >= 0 && damage >= 0)
        damage -= static_cast<int>((static_cast<float>(armor) * scale) * (static_cast<float>(damage) / static_cast<float>(totalDamage)));
    float currentDamage = static_cast<float>(damage);
    damage = static_cast<int>(currentDamage + (static_cast<float>(damageDefensePercent(type)) / 100.0f) * currentDamage);
    if (!hasEffect(static_cast<EEFFECT_TYPE>(122)))
        return damage <= 0 && type == static_cast<EDAMAGE_TYPES>(0) ? 1 : std::max(0, damage);
    bool absorbed = false;
    for (int group = 0; group < 2; ++group)
    {
        TArrayList<CEffect*>& effects = m_pEffectManager->getActiveEffects(group);
        for (unsigned int i = 0; i < effects.size(); ++i)
        {
            if (effects[i]->m_eType == static_cast<EEFFECT_TYPE>(122) &&
                (effects[i]->m_fValue24 == -900.0f || effects[i]->m_fValue24 == -1000.0f ||
                 !(effects[i]->m_fRemainingDuration >= effects[i]->m_fValue24)) &&
                !effects[i]->m_bDead && (effects[i]->m_eDamageType == type || effects[i]->m_eDamageType == static_cast<EDAMAGE_TYPES>(6)))
            {
                float value = effects[i]->value(static_cast<EEFFECT_VALUES>(0));
                if (value >= static_cast<float>(damage))
                {
                    effects[i]->m_fValueC4 = effects[i]->value(static_cast<EEFFECT_VALUES>(0)) - static_cast<float>(damage);
                    effects[i]->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
                    absorbed = true;
                    break;
                }
                effects[i]->m_fValueC4 = 0.0f;
                effects[i]->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
                if (effects[i]->m_fValue24 != -900.0f && effects[i]->m_fValue24 != -1000.0f)
                    effects[i]->m_fRemainingDuration = effects[i]->m_fValue24;
                effects[i]->m_bDead = true;
                damage -= static_cast<int>(value);
            }
            if (damage <= 0) break;
        }
        if (absorbed || damage <= 0)
        {
            absorbed = true;
            break;
        }
    }
    if (!absorbed) return std::max(0, damage);
    static std::wstring g_Absorbed;
    if (g_Absorbed.empty()) g_Absorbed = CStringTranslate::getSinglton()->getTranslateString(L"Absorbed");
    CEGUI::colour first(1.0f, 0.67f, 0.16f, 1.0f);
    CEGUI::colour second(1.0f, 0.67f, 0.16f, 1.0f);
    std::string text = STRINGS::StringConvertToUTF8(g_Absorbed + L"!");
    m_pResourceManager->getLevel()->m_pGameClient->getGameUI()->addTextEvent(getPosition(true) + Ogre::Vector3::UNIT_Y * 1.2f, text, 1.0f, 255.0f, second, first);
    if (m_levelSound) m_levelSound->playSample(7, m_pSceneNode, 0.0f, 0.0f, false);
    CDynamicPropertyFile* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    if (settings->GetInt(KSETTINGS_COMBAT_LOG) > 0)
        m_pResourceManager->getLevel()->m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Absorbed!");
    return 0;
}

void CCharacter::applyInstantEffect(CEffect* effect)
{
    m_attack = NULL;
    float amount = effect->m_fValueC0;
    CBaseUnit* owner = effect->m_Owner.getObject();
    CCharacter* character = owner ? dynamic_cast<CCharacter*>(owner) : NULL;
    switch (static_cast<int>(effect->m_eType))
    {
    case 7: case 124: case 52:
    {
        if (effect->m_eType == static_cast<EEFFECT_TYPE>(52) && amount > 0.0f) amount = -amount;
        if (!(amount < 0.0f)) { modifyHP(amount); return; }
        if (blocked())
        {
            static std::wstring g_Blocked;
            if (g_Blocked.empty()) g_Blocked = CStringTranslate::getSinglton()->getTranslateString(L"Blocked");
            CEGUI::colour first(1.0f,0.67f,0.16f,1.0f), second(1.0f,0.67f,0.16f,1.0f);
            std::string text = STRINGS::StringConvertToUTF8(g_Blocked + L"!");
            m_pResourceManager->getLevel()->m_pGameClient->getGameUI()->addTextEvent(getPosition(true)+Ogre::Vector3::UNIT_Y*1.2f,text,1.0f,255.0f,second,first);
            if (m_levelSound) m_levelSound->playSample(7,m_pSceneNode,0.0f,0.0f,false);
            CDynamicPropertyFile* settings=m_pResourceManager?CMasterResourceManager::getSingleton()->m_pSettings:NULL;
            if (settings->GetInt(KSETTINGS_COMBAT_LOG)>0)
                m_pResourceManager->getLevel()->m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Blocked!");
            return;
        }
        if (character)
        {
            float specific=character->getEffectValue(static_cast<EEFFECT_TYPE>(25),effect->m_eDamageType)/100.0f;
            float all=character->getEffectValue(static_cast<EEFFECT_TYPE>(25),static_cast<EDAMAGE_TYPES>(6))/100.0f;
            amount+=static_cast<float>(static_cast<int>(std::ceil((all+specific)*amount)));
            if (character->rollCritical(this))
            {
                int half=static_cast<int>(amount*0.5f);
                float bonus=character->getEffectValue(static_cast<EEFFECT_TYPE>(89),static_cast<EDAMAGE_TYPES>(7))/100.0f;
                amount+=static_cast<float>(static_cast<int>(static_cast<float>(half)*bonus)+half);
                int roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
                if (static_cast<float>(roll)>getEffectValue(static_cast<EEFFECT_TYPE>(136),static_cast<EDAMAGE_TYPES>(7))) interrupt(true);
            }
        }
        int rawDamage=static_cast<int>(std::fabs(amount));
        int damage=modifyDamage(rawDamage,effect->m_eDamageType,rawDamage,1.0f);
        if (!damage) damage=1;
        float maximum=effect->value(static_cast<EEFFECT_VALUES>(3));
        float minimum=effect->value(static_cast<EEFFECT_VALUES>(2));
        float force=UTILITIES::randomBetweenVolatile(minimum,maximum);
        Ogre::Vector3 from=character?character->getPosition(true):getPosition(true);
        applyDamage(*getLevel(),from,static_cast<float>(damage),effect->m_direction,force,character,false,true,true,false,0);
        int damages[1][2]={{static_cast<int>(effect->m_eDamageType),damage}};
        applyDamageEffects(this,static_cast<float>(damage),damages,1,false);
        float radius=m_fBaseUnitValue194;
        Ogre::Vector3 targetPosition=getPosition(true);
        Ogre::Vector3 sourcePosition=character?character->getPosition(true):getPosition(true);
        (character?character:this)->playStrikeParticle(sourcePosition,targetPosition,radius,false,false);
        if (m_levelSound)
        {
            int sample=2;
            switch (static_cast<int>(effect->m_eDamageType)) {case 2:sample=4;break;case 3:sample=3;break;case 4:sample=5;break;case 5:sample=6;break;}
            m_levelSound->playSample(sample,m_pSceneNode,0.0f,0.0f,false);
        }
        if (m_fHPFloat<=0.0f)
        {
            if (effect->m_pSkillOwner.getObject())
            {
                const Ogre::Quaternion& orientation=m_pSceneNode->getOrientation();
                Ogre::Vector3 position=getPosition(true);
                effect->m_pSkillOwner.getObject()->triggerEvent(static_cast<ESKILL_EVENT_TYPE>(8),position,orientation,this,NULL);
            }
            BroadcastEvent(4);
        }
        return;
    }
    case 45: openPortal(*getLevel()); break;
    case 56:
    {
        float chance=effect->value(static_cast<EEFFECT_VALUES>(0));
        if (m_alwaysActive) chance=0.0f;
        else if (m_champion) chance/=3.0f;
        int roll=UTILITIES::randomIntegerBetweenVolatile(1,100);
        if (chance>=static_cast<float>(roll))
        {
            roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
            if (static_cast<float>(roll)>getEffectValue(static_cast<EEFFECT_TYPE>(136),static_cast<EDAMAGE_TYPES>(7)))
            { interrupt(true); reactToDamage(character,true); }
        }
        break;
    }
    case 57: {float duration=effect->value(static_cast<EEFFECT_VALUES>(0));transformCharacter(effect->m_sName,duration);break;}
    case 65:
    {
        int level=static_cast<int>(effect->value(static_cast<EEFFECT_VALUES>(0)));
        if (canLearnSpell(effect->m_sName,level))
        {
            if (isPlayer()&&m_levelSound) m_levelSound->queueGlobalSample(65,0.0f,0.1f);
            level=static_cast<int>(effect->value(static_cast<EEFFECT_VALUES>(0)));
            learnSpell(effect->m_sName,level);
            m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(8));
        }
        break;
    }
    case 67: removePet(effect->m_sName); break;
    case 73: transformCharacter(effect->m_sName,-999.0f); break;
    case 74:
        if (owner->ISA(static_cast<UNITTYPES::EUNITTYPES>(2))&&effect->m_Owner.getObject())
            static_cast<CEquipment*>(effect->m_Owner.getObject())->executeProcs(this,static_cast<EEFFECT_TYPE>(74),this);
        else executeProcs(static_cast<EEFFECT_TYPE>(74),this);
        break;
    case 110: die(character,NULL,0.0f,false); break;
    case 111:
        if (effect->value(static_cast<EEFFECT_VALUES>(0))==1.0f) {setVisible(false,false);m_forcedHidden=true;}
        else {m_forcedHidden=false;setVisible(true,false);}
        break;
    case 112:
        if (effect->value(static_cast<EEFFECT_VALUES>(0))==1.0f) {m_forcedHidden=false;setVisible(true,true);}
        else {setVisible(false,true);m_forcedHidden=true;}
        break;
    case 113:
        if (isPlayer())
        {
            std::wstring warpName=EMPTY_WSTRING;
            int depth=static_cast<int>(effect->value(static_cast<EEFFECT_VALUES>(0)));
            m_pResourceManager->getGameClient()->warpLevels(effect->m_sName,0,depth,false,warpName,false);
        }
        break;
    case 114: if(isPlayer()){int old=m_iMeleeStat;float value=effect->value(static_cast<EEFFECT_VALUES>(0));m_iMeleeStat=static_cast<int>(static_cast<float>(old)+value);}break;
    case 115: if(isPlayer()){int old=m_rangedStat;float value=effect->value(static_cast<EEFFECT_VALUES>(0));m_rangedStat=static_cast<int>(static_cast<float>(old)+value);}break;
    case 116: if(isPlayer()){int old=m_magicStat;float value=effect->value(static_cast<EEFFECT_VALUES>(0));m_magicStat=static_cast<int>(static_cast<float>(old)+value);}break;
    case 117: if(isPlayer()){int old=m_maxHPBonus;float value=effect->value(static_cast<EEFFECT_VALUES>(0));m_maxHPBonus=static_cast<int>(static_cast<float>(old)+value);}break;
    case 118: if(isPlayer()){int old=m_defenseStat;float value=effect->value(static_cast<EEFFECT_VALUES>(0));m_defenseStat=static_cast<int>(static_cast<float>(old)+value);}break;
    case 119: if(isPlayer()){float old=m_maxManaBonus;float value=effect->value(static_cast<EEFFECT_VALUES>(0));m_maxManaBonus=old+value;}break;
    case 120: if(isPlayer()){int old=m_iUnusedStatPoints;float value=effect->value(static_cast<EEFFECT_VALUES>(0));m_iUnusedStatPoints=static_cast<int>(static_cast<float>(old)+value);}break;
    case 127:
        if (m_pSkillManager)
        {
            int roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
            if (effect->value(static_cast<EEFFECT_VALUES>(0))>=static_cast<float>(roll)) m_pSkillManager->stopSkillsByName(effect->m_sName,true);
        }
        break;
    case 141: openMapPortal(effect->m_sName,*getLevel()); break;
    case 142:
        if (!m_Followers.empty())
        {
            unsigned int index=UTILITIES::randomIntegerBetweenVolatile(0,static_cast<int>(m_Followers.size())-1);
            CCharacter* follower=getFollower(index);
            if (follower)
            {
                Ogre::Quaternion orientation=getOrientationQuaternion();
                Ogre::Vector3 position=getPosition(false);
                setOrientation(follower->getOrientationQuaternion());
                setPosition(follower->getPosition(false));
                follower->setOrientation(orientation);
                follower->setPosition(position);
            }
        }
        break;
    case 143:
        if (isPlayer()) {CPlayer* player=dynamic_cast<CPlayer*>(this);if(player)player->resetSkills();}
        break;
    }
}

bool CCharacter::applyEffectOnUnit(CCharacter* source, CBaseUnit* target, CEffect* effect)
{
    if (!effect || !isEffectValidForUnit(source,target,effect)) return false;
    if (effect->m_fValue24==-900.0f) {applyInstantEffect(effect);return true;}
    int type=static_cast<int>(effect->m_eType);
    if (type==47 && effect->m_fValue24!=-1000.0f) effect->m_fValue24=effect->m_fValueC0;
    CEffect* copied=NULL;
    bool react=false;
    switch(type)
    {
    case 7: case 124: copied=copyEffect(target,effect);break;
    case 56:
    {
        float chance=effect->value(static_cast<EEFFECT_VALUES>(0));
        if(m_alwaysActive)chance=0.0f;else if(m_champion)chance/=3.0f;
        int roll=UTILITIES::randomIntegerBetweenVolatile(1,100);
        if(chance>=static_cast<float>(roll))
        {
            roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
            if(static_cast<float>(roll)>getEffectValue(static_cast<EEFFECT_TYPE>(136),static_cast<EDAMAGE_TYPES>(7)))interrupt(true);
            react=true;
        }
        break;
    }
    case 63: copied=copyEffect(target,effect);m_movement=Ogre::Vector3::ZERO;break;
    case 64:
    {
        react=true;
        if(m_eAIState==static_cast<EAIState>(5)||m_eAIState==static_cast<EAIState>(6))break;
        int roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
        if(!(effect->m_fValueC0>=static_cast<float>(roll)))break;
        roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
        if(!(static_cast<float>(roll)>getEffectValue(static_cast<EEFFECT_TYPE>(139),static_cast<EDAMAGE_TYPES>(7))))break;
        roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
        if(!(static_cast<float>(roll)>getEffectValue(static_cast<EEFFECT_TYPE>(53),static_cast<EDAMAGE_TYPES>(7))))break;
        interrupt(true);copied=copyEffect(target,effect);break;
    }
    case 79:
    {
        if(m_eAIState==static_cast<EAIState>(5)||m_eAIState==static_cast<EAIState>(6)||isPlayer()||m_eAIState==static_cast<EAIState>(40))break;
        int roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
        if(!(effect->m_fValueC0>=static_cast<float>(roll)))break;
        roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
        if(!(static_cast<float>(roll)>getEffectValue(static_cast<EEFFECT_TYPE>(121),static_cast<EDAMAGE_TYPES>(7))))break;
        if(m_eAIState!=static_cast<EAIState>(10))
        {
            if(m_levelSound)m_levelSound->playSample(14,m_pSceneNode,0.0f,0.0f,false);
        }
        if(m_eAIState!=static_cast<EAIState>(10)||m_pathGraceTime>0.5f)
        {
            interrupt(true);setAIState(static_cast<EAIState>(10));
            if(effect->m_Owner.getObject()&&m_pResourceManager&&m_pResourceManager->getLevel())
            {
                Ogre::Vector3 ownerPosition=effect->m_Owner.getObject()->getPosition(true);
                Ogre::Vector3 direction=getPosition(true)-ownerPosition;
                direction.normalise();
                direction*=UTILITIES::randomBetweenVolatile(3.0f,5.0f);
                direction+=getPosition(true);
                setDestination(*getLevel(),direction.x,direction.z);
            }
        }
        copied=copyEffect(target,effect);break;
    }
    case 80: case 128:
    {
        if(m_eAIState==static_cast<EAIState>(5)||m_eAIState==static_cast<EAIState>(6))return false;
        if(type==80&&isPlayer())return false;
        int roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
        if(!(effect->m_fValueC0>=static_cast<float>(roll)))return false;
        roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
        if(!(static_cast<float>(roll)>getEffectValue(static_cast<EEFFECT_TYPE>(type==80?137:138),static_cast<EDAMAGE_TYPES>(7))))return false;
        copied=copyEffect(target,effect);break;
    }
    case 106: case 107: case 108: case 109:
    {
        react=true;
        if(m_eAIState==static_cast<EAIState>(5)||m_eAIState==static_cast<EAIState>(6))break;
        int roll=UTILITIES::randomIntegerBetweenVolatile(0,100);
        if(!(effect->m_fValueC0>=static_cast<float>(roll)))break;
        if(type!=106)
        {
            int defense=type==107?m_damageDefense[2]:type==108?m_damageDefense[5]:m_damageDefense[4];
            float power=static_cast<float>(m_value6D0);
            float chance=power/(static_cast<float>(defense)+power);
            float random=UTILITIES::randomBetweenVolatile(0.0f,1.0f);
            if(!(chance>=random))break;
        }
        interrupt(true);copied=copyEffect(target,effect);break;
    }
    case 110: die(reinterpret_cast<CCharacter*>(target),NULL,0.0f,false);break;
    default:
        if(effect->m_activation==EFFECT_ACTIVATION_PASSIVE||effect->m_activation==EFFECT_ACTIVATION_DYNAMIC||effect->m_activation==EFFECT_ACTIVATION_TRANSFER)
            copied=copyEffect(target,effect);
        break;
    }
    if(react)reactToDamage(reinterpret_cast<CCharacter*>(target),true);
    if(target)
    {
        if(isEnemy(reinterpret_cast<CCharacter*>(target))&&(m_eAIState==static_cast<EAIState>(2)||m_eAIState==static_cast<EAIState>(0))&&effect->m_eType!=static_cast<EEFFECT_TYPE>(144))
        {
            getLevel()->reactToAreaDamage(reinterpret_cast<CCharacter*>(target),this);
            reactToDamage(reinterpret_cast<CCharacter*>(target),true);
        }
        if(target->ISA(static_cast<UNITTYPES::EUNITTYPES>(33))&&copied)
        {
            float percent=getEffectValue(static_cast<EEFFECT_TYPE>(90),static_cast<EDAMAGE_TYPES>(7))/100.0f;
            if(percent!=0.0f)
            {
                for(unsigned int i=0;i<4;++i)
                {
                    copied->m_values[i]=copied->m_values[i]*percent+copied->m_values[i];
                    copied->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
                }
                float flag=static_cast<float>(copied->m_modifierFlag32);
                copied->m_modifierFlag32=(flag*percent+flag)!=0.0f;
                copied->m_fValueC0=copied->m_fValueC0*percent+copied->m_fValueC0;
            }
        }
    }
    return true;
}

#include "CameraShake.h"
#include "CameraControl.h"
int CCharacter::maxDamage(CAttackDescription* attack, CCharacter* target)
{
    if (!attack) {
        attack = m_attack;
        if (!attack) {
            selectAttack(static_cast<EATTACK_RANGE_TYPE>(0));
            attack = m_attack;
            if (!attack) return 0;
        }
    }
    if (target && target->ISA(static_cast<UNITTYPES::EUNITTYPES>(27))) alignment();
    int baseDamage = 0;
    EDAMAGE_TYPES damageType;
    if (m_bCharacterFlag4A0) {
        baseDamage = static_cast<int>(attack->m_DamageMaximums[0]);
        damageType = static_cast<EDAMAGE_TYPES>(attack->m_iUnknown78);
    } else if (!m_attacks.empty()) {
        baseDamage = static_cast<int>(m_attacks[0]->m_DamageMaximums[0]);
        damageType = static_cast<EDAMAGE_TYPES>(m_attacks[0]->m_iUnknown78);
    }
    EEQUIP_LOCATIONS location = static_cast<EEQUIP_LOCATIONS>(1);
    if (m_attackItem && m_attackItem == m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1)))
        location = static_cast<EEQUIP_LOCATIONS>(0);
    bool ranged = m_attackItem && m_attackItem->ISA(static_cast<UNITTYPES::EUNITTYPES>(35));
    float bonus = getEffectValue(static_cast<EEFFECT_TYPE>(ranged ? 16 : 15), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
    bonus += static_cast<float>(ranged ? dexterity() : strength()) / 100.0f;
    if (m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1)) &&
        m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0)) &&
        !m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1))->ISA(static_cast<UNITTYPES::EUNITTYPES>(21)))
        bonus += getEffectValue(static_cast<EEFFECT_TYPE>(88), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
    if (ranged) {
        if (m_attackItem->ISA(static_cast<UNITTYPES::EUNITTYPES>(163)))
            bonus += getEffectValue(static_cast<EEFFECT_TYPE>(102), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
        if (m_attackItem->ISA(static_cast<UNITTYPES::EUNITTYPES>(164)))
            bonus += getEffectValue(static_cast<EEFFECT_TYPE>(103), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
    } else if (m_attackItem) {
        if (m_attackItem->ISA(static_cast<UNITTYPES::EUNITTYPES>(162)))
            bonus += getEffectValue(static_cast<EEFFECT_TYPE>(99), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
        if (m_attackItem->ISA(static_cast<UNITTYPES::EUNITTYPES>(164)))
            bonus += getEffectValue(static_cast<EEFFECT_TYPE>(103), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
    }
    bonus += getEffectValue(static_cast<EEFFECT_TYPE>(25), location, damageType) / 100.0f;
    bonus += getEffectValue(static_cast<EEFFECT_TYPE>(25), static_cast<EDAMAGE_TYPES>(6)) / 100.0f;
    if (m_pMaster) bonus += m_pMaster->getEffectValue(static_cast<EEFFECT_TYPE>(91), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
    int extra = static_cast<int>(ceilf(static_cast<float>(baseDamage) * bonus));
    int flat = static_cast<int>(ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(ranged ? 1 : 0), static_cast<EDAMAGE_TYPES>(7))));
    baseDamage += extra + flat;
    baseDamage += static_cast<int>(getEffectValue(static_cast<EEFFECT_TYPE>(10), location, damageType));
    return static_cast<int>(static_cast<float>(baseDamage) * m_CharacterValue720);
}

bool CCharacter::rollCritical(CCharacter* target)
{
    float roll = UTILITIES::randomBetweenVolatile(1.0f, 100.0f);
    float chance = getEffectValue(static_cast<EEFFECT_TYPE>(55), static_cast<EDAMAGE_TYPES>(7)) + roll;
    if (chance < 97.0f && static_cast<int>(ceilf(chance)) != 97 && !m_flag700) return false;
    static std::wstring g_CriticalStrike;
    if (g_CriticalStrike.empty()) g_CriticalStrike = CStringTranslate::getSinglton()->getTranslateString(L"Critical Strike");
    CEGUI::colour first(0.196f, 0.745f, 1.0f, 1.0f), second(0.196f, 0.745f, 1.0f, 1.0f);
    std::string text = STRINGS::StringConvertToUTF8(g_CriticalStrike + L"!");
    m_pResourceManager->getLevel()->m_pGameClient->getGameUI()->addTextEvent(target->getPosition(true) + Ogre::Vector3::UNIT_Y * 1.2f, text, 1.0f, 255.0f, second, first);
    if (m_levelSound) m_levelSound->playSample(9, m_pSceneNode, 0.0f, 0.0f, false);
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) {
        CCameraShake* shake = new CCameraShake(L"CRITICAL", m_vForward, 0.2f);
        shake->m_fMagnitudeMultiplier = 0.7f;
        Ogre::Vector3 position = getPosition(true);
        shake->m_fCameraPositionX = position.x;
        shake->m_fCameraPositionY = position.y;
        shake->m_fCameraPositionZ = position.z;
        shake->m_bCameraShakeActive = true;
        CCameraControl* control = m_pResourceManager->getCameraControl();
        TSafePointer<CCameraShake>* pointer = OGRE_NEW_T(TSafePointer<CCameraShake>, Ogre::MEMCATEGORY_GENERAL)();
        pointer->setObject(shake);
        control->m_cameraShakes.add(pointer);
    }
    return true;
}

void CCharacter::awardFame(CLevel& level, CCharacter* source, int amount, bool bonus)
{
    if (!amount) return;
    if (!ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) &&
        (!m_pMaster || !m_pMaster->ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) &&
        (!m_pMaster || !m_pMaster->m_pMaster || !m_pMaster->m_pMaster->ISA(static_cast<UNITTYPES::EUNITTYPES>(28)))) return;
    if (!bonus) {
        float extra = getEffectValue(static_cast<EEFFECT_TYPE>(77), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
        amount += static_cast<int>(ceilf(static_cast<float>(amount) * extra));
    }
    if (m_pMaster && !bonus) m_pMaster->awardFame(level, source, amount, false);
    else {
        static std::wstring g_Fame;
        if (g_Fame.empty()) g_Fame = CStringTranslate::getSinglton()->getTranslateString(L"Fame");
        CEGUI::colour first(1.0f, 0.77f, 1.0f, 1.0f), second(1.0f, 0.77f, 1.0f, 1.0f);
        std::string text = STRINGS::StringConvertToUTF8(STRINGS::GetValueAsWString(amount) + L" " + g_Fame);
        m_pResourceManager->getLevel()->m_pGameClient->getGameUI()->addTextEvent(getPosition(true) + Ogre::Vector3::UNIT_Y, text, 1.0f, 255.0f, second, first);
        int oldFame = static_cast<int>(m_fame);
        int sum = static_cast<int>(m_fame + static_cast<unsigned int>(amount));
        m_fame = amount > 0 && oldFame > sum ? 0x7fffffffU : static_cast<unsigned int>(std::max(0, sum));
        ISA(static_cast<UNITTYPES::EUNITTYPES>(28));
    }
    int fame = static_cast<int>(m_fame), currentLevel = m_fameLevel;
    int gate = CMasterResourceManager::getSingleton()->fameGate(currentLevel);
    if (fame >= gate && static_cast<unsigned int>(CMasterResourceManager::getSingleton()->getMaxFameLevel()) > static_cast<unsigned int>(m_fameLevel)) {
        for (;;) {
            fame = static_cast<int>(m_fame); currentLevel = m_fameLevel;
            if (fame < CMasterResourceManager::getSingleton()->fameGate(currentLevel)) return;
            currentLevel = m_fameLevel;
            if (static_cast<unsigned int>(CMasterResourceManager::getSingleton()->getMaxFameLevel()) <= static_cast<unsigned int>(currentLevel)) return;
            fameUp();
        }
    }
    fame = static_cast<int>(m_fame); currentLevel = m_fameLevel;
    if (fame >= CMasterResourceManager::getSingleton()->fameGate(currentLevel)) {
        currentLevel = m_fameLevel;
        m_fame = CMasterResourceManager::getSingleton()->fameGate(currentLevel);
    }
}

#include "SteamStats.h"
void CCharacter::applyDamage(CLevel& level, const Ogre::Vector3& from, float amount,
                            const Ogre::Vector3& direction, float force, CCharacter* attacker,
                            bool glancing, bool react, bool hitParticle, bool silent, unsigned int flags)
{
    if (amount == 0.0f || m_eAIState == static_cast<EAIState>(5) || m_eAIState == static_cast<EAIState>(6) || !m_characterFlag52F) return;
    if (m_eAIState >= static_cast<EAIState>(32) && m_eAIState <= static_cast<EAIState>(34)) {
        setAIState(static_cast<EAIState>(2));
        setTargetItem(NULL);
    }
    if (hitParticle) {
        float radius = m_fBaseUnitValue194;
        Ogre::Vector3 position = getPosition(true);
        playHitParticle(from, position, radius);
    }
    static std::wstring g_GlancingBlow;
    if (g_GlancingBlow.empty()) g_GlancingBlow = CStringTranslate::getSinglton()->getTranslateString(L"Glancing Blow");
    if (glancing) {
        bool friendly = ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) ||
            (m_pMaster && m_pMaster->ISA(static_cast<UNITTYPES::EUNITTYPES>(28)));
        CEGUI::colour first(1.0f, friendly ? 0.2f : 0.77f, friendly ? 0.2f : 0.0f, 1.0f);
        CEGUI::colour second(1.0f, friendly ? 0.2f : 0.77f, friendly ? 0.2f : 0.0f, 1.0f);
        std::string text = STRINGS::StringConvertToUTF8(g_GlancingBlow + L"!");
        level.m_pGameClient->getGameUI()->addTextEvent(getPosition(true) + Ogre::Vector3::UNIT_Y * 1.2f, text, 1.0f, 255.0f, second, first);
    } else if (attacker != this || !attacker) m_damageOverTimeTaken += amount;
    if (react && m_procTime <= 0.0f) executeProcs(static_cast<EEFFECT_TYPE>(81), attacker);
    if (attacker && attacker->ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) {
        int current = CSteamStats::getSingleton()->getStatInt(static_cast<ESTATS>(3));
        int damage = static_cast<int>(amount);
        if (current < damage) CSteamStats::getSingleton()->setStatInt(static_cast<ESTATS>(3), static_cast<unsigned int>(damage));
    }
    modifyHP(-amount);
    if (m_fHPFloat <= 0.0f) {
        float threshold = static_cast<float>(maxHP()) * 1.75f;
        die(attacker, &direction, force, silent || amount >= threshold);
        if (attacker) {
            attacker->awardExperience(level, this, m_experienceReward, false);
            attacker->awardFame(level, this, m_fameReward, false);
            m_experienceReward = 0;
            m_fameReward = 0;
        }
    }
    if (attacker && react) {
        level.reactToAreaDamage(attacker, this);
        if (m_fHPFloat > 0.0f) reactToDamage(attacker, true);
    }
    if (react && !(flags & 0x300) && attacker && m_fHPFloat > 0.0f &&
        attacker->m_eAIState != static_cast<EAIState>(5) && attacker->m_eAIState != static_cast<EAIState>(6) &&
        (getEffectValue(static_cast<EEFFECT_TYPE>(48), static_cast<EDAMAGE_TYPES>(7)) != 0.0f ||
         getEffectValue(static_cast<EEFFECT_TYPE>(32), static_cast<EDAMAGE_TYPES>(7)) != 0.0f)) {
        float percent = getEffectValue(static_cast<EEFFECT_TYPE>(32), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
        int reflected = attacker->modifyDamage(static_cast<int>(amount * percent), static_cast<EDAMAGE_TYPES>(0), static_cast<int>(amount), percent);
        float flat = getEffectValue(static_cast<EEFFECT_TYPE>(48), static_cast<EDAMAGE_TYPES>(7));
        attacker->HP();
        Ogre::Vector3 position = getPosition(false);
        attacker->applyDamage(level, position, flat + static_cast<float>(reflected), direction, 0.0f, this, false, false, flags != 0, false, 0);
    }
    if (m_pAIManager && !m_targetCharacter.getObject()) m_pAIManager->addAIFlag(static_cast<EAIFLAG_TYPES>(0), 3.0f);
}


bool CCharacter::canCastCurrentSkill(CBaseUnit* target, bool testCast, bool skipChance)
{
    if (!m_pSkillManager || !getEnabled() || !m_activeSkill) return false;
    if (!skipChance && !m_activeSkill->rollCastChance()) return false;
    int available = mana();
    int cost = m_activeSkill->getManaCost();
    bool sufficient = available >= cost;
    if (sufficient) {
        available = mana();
        cost = m_activeSkill->getManaCostOT();
        sufficient = available >= cost;
    }
    if (!sufficient) {
        if (isPlayer()) {
            m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(4));
            if (m_levelSound) m_levelSound->queueGlobalSample(53, 0.0f, 0.1f);
        }
        return false;
    }
    if (m_pSkillManager->getSkillIsCooling(m_activeSkill)) return false;
    if (!target) {
        target = m_targetCharacter.getObject();
        if (!target) target = m_targetItem.getObject();
    }
    if (target && !isPlayer() && dynamic_cast<CCharacter*>(target) &&
        m_activeSkill->getTargetType() != 3 && m_activeSkill->getTargetType() != 10 &&
        m_activeSkill->getTargetType() != 1 && m_activeSkill->getTargetType() != 11 &&
        m_activeSkill->getTargetType() != 6 && m_activeSkill->getTargetType() != 5) {
        EAlignment targetAlignment = getTargetAlignment();
        if (m_activeSkill->getTargetType() == 2 && m_activeSkill->m_iTargetAlignment == 1 && targetAlignment == static_cast<EAlignment>(6))
            targetAlignment = static_cast<EAlignment>(2);
        Ogre::Vector3 position = getPosition(true);
        CCharacter* character = dynamic_cast<CCharacter*>(target);
        if (!m_activeSkill->getTargetIsValid(character, this, &position, false)) {
            Ogre::Vector3 right = Ogre::Vector3::UNIT_Y.crossProduct(m_targetDirection);
            Ogre::Quaternion orientation;
            orientation.FromAxes(right, Ogre::Vector3::UNIT_Y, m_targetDirection);
            Ogre::Matrix4 view(orientation);
            view.setTrans(m_vPosition);
            float skillRange = m_activeSkill->getRange();
            float radius = m_attackRadius;
            float scale = m_vScale.z;
            float rangeScale = m_attackRangeScale;
            float angle = m_activeSkill->getFindTargetAngle();
            CCharacter* found = getLevel()->findCharacterWithinView(view, targetAlignment, 0.0f, angle,
                ((radius * scale + 0.2f) + skillRange) * rangeScale + 1.0f, true, this, m_activeSkill);
            if (!found) return false;
            target = found;
            setTarget(found);
        }
    }
    return m_pSkillManager->getSkillCanBeExecuted(m_activeSkill, this, static_cast<ESKILL_ACTIVATION_TYPE>(3), m_targetPosition, target, testCast);
}

#include "QuestManager.h"

void CCharacter::approachAI(float, CLevel&)
{
    CPositionableObject* target = m_targetCharacter.getObject();
    if (!target) target = m_targetItem.getObject();
    if (!target) {
        setAIState(static_cast<EAIState>(0));
        return;
    }
    Ogre::Vector3 position = getPosition(true);
    Ogre::Vector3 destination = target->getPosition(true);
    Ogre::Vector3 difference = destination - position;
    difference.y = 0.0f;
    float distance = difference.length();
    m_returningToTown = distance >= m_nearWalkRadius;
    if (distance <= 2.0f || (!m_isPathing && distance <= 2.75f)) {
        stopPathing();
        CCharacter* character = m_targetCharacter.getObject();
        EAIState state;
        bool stopTarget = true;
        if (CQuestManager::getSingleton()->getQuestForNPC(character)) state = static_cast<EAIState>(30);
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(130))) state = static_cast<EAIState>(21);
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(175))) state = static_cast<EAIState>(27);
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(132))) state = static_cast<EAIState>(25);
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(133))) state = static_cast<EAIState>(26);
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(134))) state = static_cast<EAIState>(17);
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(41))) state = static_cast<EAIState>(19);
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(128))) {
            state = static_cast<EAIState>(36);
            stopTarget = false;
        } else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(170))) {
            if (m_pResourceManager->getGameClient()->getPlayerIsCheat()) return;
            state = static_cast<EAIState>(37);
            stopTarget = false;
        } else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(104))) state = static_cast<EAIState>(30);
        else {
            if (!m_isPathing) {
                setTarget(NULL);
                setAIState(static_cast<EAIState>(2));
            }
            return;
        }
        setAIState(state);
        if (stopTarget) {
            m_targetCharacter.getObject()->setTarget(this);
            m_targetCharacter.getObject()->stopPathing();
        }
    } else if (!m_isPathing) {
        setTarget(NULL);
        setAIState(static_cast<EAIState>(2));
    }
}

void CCharacter::attackAI(float elapsed, CLevel& level)
{
    CCharacter* character = m_targetCharacter.getObject();
    if ((character && (character->m_eAIState == static_cast<EAIState>(5) ||
         character->m_eAIState == static_cast<EAIState>(6) || isPetNearDeath() ||
         m_targetCharacter.getObject()->isPetNearDeath() || !m_targetCharacter.getObject()->availableForCommand())) ||
        (!m_targetCharacter.getObject() && (!m_targetItem.getObject() ||
         !m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(29))))) {
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        setTargetItem(NULL);
        return;
    }
    if (!m_attack) selectAttack(ATTACK_RANGE_DEFAULT);
    if (!m_attack) {
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        return;
    }
    Ogre::Vector3 position = getPosition(true);
    CPositionableObject* target = m_targetCharacter.getObject();
    if (!target) target = m_targetItem.getObject();
    Ogre::Vector3 destination = target->getPosition(true);
    Ogre::Vector3 difference = destination - position;
    difference.y = 0.0f;
    float distance = difference.length();
    if (distance >= m_followRange && !m_pMaster) {
        stopPathing();
        setAIState(static_cast<EAIState>(2));
        setTarget(NULL);
        return;
    }
    if ((inAttackRange(ATTACK_RANGE_DEFAULT) && validLineOfSight(level, false)) || m_moveInputHeld) {
        stopPathing();
        CPositionableObject* current = m_targetCharacter.getObject();
        if (!current) current = m_targetItem.getObject();
        Ogre::Vector3 targetPosition = current->getPosition(true);
        turnTowardPosition(targetPosition, elapsed);
        if (facingTarget()) {
            attack();
            setAIState(static_cast<EAIState>(0));
        }
        if (m_pMaster && !ISA(static_cast<UNITTYPES::EUNITTYPES>(169))) {
            Ogre::Vector3 own = getPosition(true);
            Ogre::Vector3 master = m_pMaster->getPosition(true);
            Ogre::Vector3 delta = master - own;
            delta.y = 0.0f;
            if (delta.length() > 35.0f) {
                setTarget(NULL);
                setAIState(static_cast<EAIState>(2));
            }
        }
    } else {
        if (m_attack && m_attackTime > 0.2f) return;
        if (m_activeSkill && (m_skillLooping || (m_skillTime > 0.0f && !m_skillInterrupted))) return;
        setAIState(static_cast<EAIState>(4));
    }
}

void CCharacter::skillAI(float elapsed, CLevel& level)
{
    CCharacter* character = m_targetCharacter.getObject();
    if ((character && (character->m_eAIState == static_cast<EAIState>(5) ||
         character->m_eAIState == static_cast<EAIState>(6) || isPetNearDeath() ||
         m_targetCharacter.getObject()->isPetNearDeath() || !m_targetCharacter.getObject()->availableForCommand())) ||
        (!m_targetCharacter.getObject() && (!m_targetItem.getObject() ||
         !m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(29))))) {
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        setTargetItem(NULL);
        return;
    }
    if (!m_activeSkill) {
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        return;
    }
    Ogre::Vector3 position = getPosition(true);
    CPositionableObject* target = m_targetCharacter.getObject();
    if (!target) target = m_targetItem.getObject();
    Ogre::Vector3 destination = target->getPosition(true);
    Ogre::Vector3 difference = destination - position;
    difference.y = 0.0f;
    float distance = difference.length();
    if (!ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) && distance >= m_followRange && !m_pMaster) {
        stopPathing();
        setAIState(static_cast<EAIState>(2));
        setTarget(NULL);
        return;
    }
    int range = inSkillRange(-1, false);
    if (range == 1) {
        if (!ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) {
            stopPathing();
            setAIState(static_cast<EAIState>(2));
            setTarget(NULL);
            return;
        }
        range = 0;
    }
    bool needsSight = m_activeSkill->getTargetType() != 3 && m_activeSkill->getTargetType() != 10 &&
        m_activeSkill->getTargetType() != 9;
    if ((range == 0 && (!needsSight || validLineOfSight(level, false))) || m_moveInputHeld) {
        stopPathing();
        CPositionableObject* current = m_targetCharacter.getObject();
        if (!current) current = m_targetItem.getObject();
        Ogre::Vector3 targetPosition = current->getPosition(true);
        turnTowardPosition(targetPosition, elapsed);
        if (facingTarget() && !castSkill(-1)) setAIState(static_cast<EAIState>(2));
        if (m_pMaster && !ISA(static_cast<UNITTYPES::EUNITTYPES>(169))) {
            Ogre::Vector3 own = getPosition(true);
            Ogre::Vector3 master = m_pMaster->getPosition(true);
            Ogre::Vector3 delta = master - own;
            delta.y = 0.0f;
            if (delta.length() > 35.0f) {
                setTarget(NULL);
                setAIState(static_cast<EAIState>(2));
            }
        }
    } else {
        if (m_activeSkill && (m_skillLooping || (m_skillTime > 0.0f && !m_skillInterrupted))) return;
        if (canCastCurrentSkill(m_targetCharacter.getObject(), true, true))
            setAIState(static_cast<EAIState>(15));
        else {
            m_activeSkill = NULL;
            setAIState(static_cast<EAIState>(2));
            updateAI(0.0f, true);
        }
    }
}

void CCharacter::huntAI(float elapsed, CLevel& level)
{
    CCharacter* character = m_targetCharacter.getObject();
    if ((character && (character->m_eAIState == static_cast<EAIState>(5) ||
         character->m_eAIState == static_cast<EAIState>(6) || isPetNearDeath() ||
         m_targetCharacter.getObject()->isPetNearDeath())) ||
        (!m_targetCharacter.getObject() && (!m_targetItem.getObject() ||
         !m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(29)))) ||
        (m_targetCharacter.getObject() && isFriend(m_targetCharacter.getObject()))) {
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        setTargetItem(NULL);
        return;
    }
    Ogre::Vector3 position = getPosition(true);
    CPositionableObject* target = m_targetCharacter.getObject();
    if (!target) target = m_targetItem.getObject();
    Ogre::Vector3 destination = target->getPosition(true);
    Ogre::Vector3 difference = destination - position;
    difference.y = 0.0f;
    float distance = difference.length();
    if (!ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) && distance >= m_followRange &&
        (!m_pMaster || !m_pMaster->isPlayer()) && !m_moveInputHeld) {
        stopPathing();
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        setTargetItem(NULL);
        return;
    }
    bool sight = validLineOfSight(level, false);
    bool range = inAttackRange(ATTACK_RANGE_DEFAULT);
    if ((!range || !sight) && !m_moveInputHeld && m_pathGraceTime > 0.5f) {
        bool follow = !m_isPathing;
        if (m_isPathing && m_targetCharacter.getObject()) {
            Ogre::Vector3 current = m_targetCharacter.getObject()->getPosition(true);
            Ogre::Vector3 delta = current - m_targetPosition;
            delta.y = 0.0f;
            follow = delta.length() >= 1.0f;
        }
        if (follow) {
            if (m_targetCharacter.getObject()) followCharacter(m_targetCharacter.getObject(), level);
            else {
                float z = m_targetItem.getObject()->getPosition(true).z;
                float x = m_targetItem.getObject()->getPosition(true).x;
                setDestination(level, x, z);
            }
        }
        if (!m_isPathing) {
            setTarget(NULL);
            setTargetItem(NULL);
            setAIState(static_cast<EAIState>(0));
            return;
        }
    }
    if ((inAttackRange(ATTACK_RANGE_DEFAULT) && sight && canAttackWithCurrentWeapon()) || m_moveInputHeld) {
        setAIState(static_cast<EAIState>(3));
        stopPathing();
        updateAI(elapsed, true);
    }
}

void CCharacter::getItemAI(float, CLevel& level)
{
    if (!m_targetItem.getObject()) {
        setAIState(static_cast<EAIState>(0));
        return;
    }
    if (m_pMaster) m_returningToTown = true;
    Ogre::Vector3 position = getPosition(true);
    Ogre::Vector3 destination = m_targetItem.getObject()->getPosition(true);
    Ogre::Vector3 difference = destination - position;
    difference.y = 0.0f;
    float distance = difference.length();
    if (m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(30))) {
        if (m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(29))) {
            bool sight = validLineOfSight(level, false);
            if (inAttackRange(ATTACK_RANGE_DEFAULT) && sight) {
                stopPathing();
                if (facingTarget()) {
                    attack();
                    setAIState(static_cast<EAIState>(0));
                }
                return;
            }
        }
    } else if (m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(32))) {
        bool sight = validLineOfSight(level, true);
        if (inInteractionRange() && sight) {
            stopPathing();
            if (!facingTarget()) return;
            if (m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(122))) startFishing();
            else if (m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(157))) setAIState(static_cast<EAIState>(22));
            else if (m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(158))) setAIState(static_cast<EAIState>(23));
            else if (m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(159))) setAIState(static_cast<EAIState>(24));
            else {
                setAIState(static_cast<EAIState>(0));
                m_targetItem.getObject()->interact(this);
            }
            return;
        }
    } else if (inInteractionRange()) {
        setAIState(static_cast<EAIState>(0));
        getItem(m_targetItem.getObject(), level);
        return;
    }
    if (distance > m_fBaseUnitValue194) {
        if (m_isPathing) return;
        float z = m_targetItem.getObject()->getPosition(true).z;
        float x = m_targetItem.getObject()->getPosition(true).x;
        setDestination(level, x, z);
        removeFromAvoidanceMap(level);
    }
    if (!m_isPathing) {
        setTargetItem(NULL);
        setAIState(static_cast<EAIState>(2));
    }
}

void CCharacter::skillApproachAI(float elapsed, CLevel& level, long long guid)
{
    CCharacter* character = m_targetCharacter.getObject();
    if ((character && (character->m_eAIState == static_cast<EAIState>(5) ||
         character->m_eAIState == static_cast<EAIState>(6) || isPetNearDeath() ||
         m_targetCharacter.getObject()->isPetNearDeath())) ||
        (!m_targetCharacter.getObject() && !m_targetItem.getObject())) {
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        return;
    }
    if ((!m_targetCharacter.getObject() && !m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(29))) ||
        (m_targetCharacter.getObject() && isFriend(m_targetCharacter.getObject()))) {
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        setTargetItem(NULL);
        return;
    }
    if (guid == -1 && m_activeSkill) guid = m_activeSkill->getGuid();
    if (!m_pSkillManager || !m_pSkillManager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0))) return;
    if (m_activeSkill != m_pSkillManager->getSkillByGuid(guid)) m_activeSkill = m_pSkillManager->getSkillByGuid(guid);
    if (!m_activeSkill) return;
    if (!canCastCurrentSkill(m_targetCharacter.getObject(), true, true)) {
        setAIState(static_cast<EAIState>(2));
        updateAI(0.0f, true);
        return;
    }
    Ogre::Vector3 position = getPosition(true);
    CPositionableObject* target = m_targetCharacter.getObject();
    if (!target) target = m_targetItem.getObject();
    Ogre::Vector3 destination = target->getPosition(true);
    Ogre::Vector3 difference = destination - position;
    difference.y = 0.0f;
    float distance = difference.length();
    m_returningToTown = distance >= m_nearWalkRadius;
    if (!ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) && (!m_pMaster || !m_pMaster->isPlayer()) &&
        distance >= m_followRange && !m_moveInputHeld) {
        stopPathing();
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        setTargetItem(NULL);
        return;
    }
    bool sight = m_activeSkill->getTargetType() == 3 || m_activeSkill->getTargetType() == 10 ||
        m_activeSkill->getTargetType() == 9;
    if (!sight) sight = validLineOfSight(level, false);
    int range = inSkillRange(guid, false);
    if (range == 1) {
        if (!ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) {
            m_activeSkill = NULL;
            stopPathing();
            setAIState(static_cast<EAIState>(2));
            setTarget(NULL);
            return;
        }
        range = 0;
    }
    if ((range != 0 || !sight) && !m_moveInputHeld && m_pathGraceTime > 1.0f) {
        bool follow = !m_isPathing;
        if (m_isPathing && m_targetCharacter.getObject()) {
            Ogre::Vector3 current = m_targetCharacter.getObject()->getPosition(true);
            Ogre::Vector3 delta = current - m_targetPosition;
            delta.y = 0.0f;
            follow = delta.length() >= 4.0f;
        }
        if (follow) {
            if (m_activeSkill && m_activeSkill->rollCancelChance() && elapsed != 0.0f) {
                setAIState(static_cast<EAIState>(2));
                updateAI(0.0f, true);
                return;
            }
            if (m_targetCharacter.getObject()) followCharacter(m_targetCharacter.getObject(), level);
            else {
                float z = m_targetItem.getObject()->getPosition(true).z;
                float x = m_targetItem.getObject()->getPosition(true).x;
                setDestination(level, x, z);
            }
        }
        if (!m_isPathing) {
            setTarget(NULL);
            setTargetItem(NULL);
            setAIState(static_cast<EAIState>(0));
            return;
        }
    }
    if ((inSkillRange(guid, false) == 0 && sight) || m_moveInputHeld) {
        setAIState(static_cast<EAIState>(13));
        stopPathing();
        updateAI(elapsed, true);
    }
}

#include "CharacterSaveState.h"
#include "ItemSaveState.h"

void CCharacter::fillSaveState(CCharacterSaveState& state)
{
    state.m_position = getPosition(true);
    if (m_iRoomIndex == -1)
        m_iRoomIndex = getLevel()->getRoomIndexThatPositionIsIn(state.m_position);
    state.m_value184 = m_iRoomIndex;
    state.m_flag20C = m_forcedHidden;
    state.m_alignment = m_alignment;
    state.m_transformationTime = m_transformationTime;
    state.m_townTravelTime = m_townTravelTime;
    state.m_guid10 = getOriginalGuid();
    state.m_flag18 = m_bSaveFlag191;
    state.m_guid28 = m_originalUnitGuid;
    state.m_guid20 = m_iUnitValue1A0;
    state.m_orientation = getOrientation();
    state.m_valueD0 = m_iUnitLevel;
    state.m_valueD8 = m_fameLevel;
    state.m_value64 = getLevel()->getLevelDepth();
    state.m_guid50 = m_pMaster ? m_pMaster->getOriginalGuid() : -1;
    state.m_flag32 = m_champion;
    state.m_petMode = m_petMode;
    state.m_guid200 = m_iQuestGuid;
    state.m_value208 = m_iQuestState;
    state.m_guid58 = m_iSpawnerGuid;
    state.m_flag33 = m_bSecondaryWeaponSet;
    for (unsigned int i = 0; i < 7; ++i) state.m_damageDefense[i] = m_damageDefense[i];
    state.m_playTime = m_playTime;
    state.m_scale = m_vScale.z;
    state.m_bravery = m_bravery;
    state.m_valueD4 = m_experience;
    state.m_valueDC = m_fame;
    state.m_hp = m_fHPFloat;
    state.m_valueE8 = m_maxHPBonus;
    state.m_valueE4 = m_maxHPBase;
    state.m_mana = m_fManaFloat;
    state.m_maxManaBonus = static_cast<int>(m_maxManaBonus);
    state.m_maxManaBase = m_maxManaBase;
    state.m_defenseStat = m_defenseStat;
    state.m_magicStat = m_magicStat;
    state.m_rangedStat = m_rangedStat;
    state.m_meleeStat = m_iMeleeStat;
    state.m_experienceReward = m_experienceReward;
    state.m_fameReward = m_fameReward;
    state.m_flag31 = getEnabled();
    state.m_freeStatPoints = m_iUnusedStatPoints;
    state.m_freeSkillPoints = m_iUnusedSkillPoints;
    state.m_freePerkPoints = m_iUnusedPerkPoints;
    state.m_value174 = m_iGold;
    state.m_name = m_characterDisplayName;
    state.m_guidB8 = m_activeSkillGuid;
    int count = m_pSkillManager ? m_pSkillManager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0)) : 0;
    state.m_values.clear();
    for (int i = 0; i < count; ++i)
        state.m_values.push_back(m_pSkillManager->getSkillByIndex(i)->getLevel());
    state.m_guidC0 = m_leftSkillGuid;
    state.m_guidC8 = m_leftMouseSkillGuid;
    for (unsigned int i = 0; i < 4; ++i) {
        state.m_knownSpells[i] = m_knownSpells[i];
        state.m_spellLevels[i] = m_knownSpellLevels[i];
    }
    if (m_pInventory) {
        int items = m_pInventory->m_equipmentRefs.size();
        for (int i = 0; i < items; ++i) {
            CItemSaveState* saved = new CItemSaveState;
            CEquipmentRef* item = m_pInventory->m_equipmentRefs[i];
            item->m_pEquipment->fillSaveState(*saved, item->m_iSlot, item->m_flag20);
            state.m_pets.push_back(saved);
        }
    }
    if (m_pEffectManager) {
        for (unsigned int group = 0; group < 3; ++group) {
            TArrayList<CEffect*>& effects = m_pEffectManager->getActiveEffects(group);
            for (unsigned int i = 0; i < effects.size(); ++i) {
                if (effects[i]->m_flag33) {
                    CEffect* saved = new CEffect(effects[i]);
                    saved->setOwner(NULL, true);
                    saved->setSkillOwner(NULL);
                    saved->m_fValueC0 = effects[i]->m_fValueC0;
                    state.m_items[group].push_back(saved);
                }
            }
        }
    }
}

namespace {
void deleteCharacterPaperdollEntity(Ogre::Entity*& entity)
{
    if (!entity) return;
    entity->getMesh()->unload();
    if (entity->getParentSceneNode()) {
        OGRE_UTILITIES::detachEntityFromParent(entity);
        CMasterResourceManager::getSingleton()->m_pSceneManager->destroyEntity(entity);
    }
    Ogre::MeshManager& manager = Ogre::MeshManager::getSingleton();
    manager.remove(entity->getMesh()->getName());
    entity = NULL;
}
}

void CCharacter::deleteUnitSpecificData()
{
    m_particleTriggers.deleteAll();
    for (unsigned int i = 0; i < m_equipmentParticles.size(); ++i) {
        if (m_equipmentParticles[i]) {
            delete m_equipmentParticles[i];
            m_equipmentParticles[i] = NULL;
        }
        m_equipmentParticles[i] = NULL;
    }
    for (unsigned int i = 0; i < 12; ++i) {
        deleteCharacterPaperdollEntity(m_PaperdollItems[i]);
        deleteCharacterPaperdollEntity(m_PaperdollItemsSecondary[i]);
    }
    if (m_pPaperdollModel) {
        delete m_pPaperdollModel;
        m_pPaperdollModel = NULL;
    }
    for (unsigned int i = 0; i < m_attacks.size(); ++i) {
        if (m_attacks[i]) {
            delete m_attacks[i];
            m_attacks[i] = NULL;
        }
    }
    m_attacks.clear();
    m_attack = NULL;
    Ogre::SceneNode** nodes[] = { &m_pRightHandNode, &m_fishingNode, &m_pLeftHandNode,
        &m_pShieldNode, &m_pRightShoulderNode, &m_pLeftShoulderNode, &m_pHeadNode };
    for (unsigned int i = 0; i < 7; ++i) {
        Ogre::SceneNode*& node = *nodes[i];
        if (node) {
            m_pSceneNode->removeChild(node);
            node->removeAllChildren();
            m_pResourceManager->getSceneManager()->destroySceneNode(node);
        }
    }
    if (m_wardrobe) {
        delete m_wardrobe;
        m_wardrobe = NULL;
    }
    if (m_pPaperdollModel) {
        delete m_pPaperdollModel;
        m_pPaperdollModel = NULL;
    }
    CMasterResourceManager::getSingleton()->removeCollisionModel(m_collisionModel);
    if (m_levelSound) {
        delete m_levelSound;
        m_levelSound = NULL;
    }
    if (m_secondarySound) {
        delete m_secondarySound;
        m_secondarySound = NULL;
    }
    m_pRightHandNode = NULL;
    m_fishingNode = NULL;
    m_rightHandBone = NULL;
    m_fishingBone = NULL;
    m_pLeftHandNode = NULL;
    m_leftHandBone = NULL;
    m_pShieldNode = NULL;
    m_shieldBone = NULL;
    m_pRightShoulderNode = NULL;
    m_leftShoulderBone = NULL;
    m_pLeftShoulderNode = NULL;
    m_rightShoulderBone = NULL;
    m_pHeadNode = NULL;
    m_headBone = NULL;
}

CCharacter::~CCharacter()
{
    destroyCharacterText();
    if (m_pMaster) m_pMaster->removePet(this);
    if (m_pAIManager) {
        delete m_pAIManager;
        m_pAIManager = NULL;
    }
    m_pathToFollow.setObject(NULL);
    setVisible(false, true);
    for (unsigned int i = 0; i < 4; ++i) {
        if (m_weaponTrails[i]) {
            delete m_weaponTrails[i];
            m_weaponTrails[i] = NULL;
        }
    }
    if (m_deathPath) {
        delete m_deathPath;
        m_deathPath = NULL;
    }
    if (m_pInventory) {
        m_pInventory->removeListener(this);
        m_pInventory->freeInventory();
        if (m_pInventory) {
            delete m_pInventory;
            m_pInventory = NULL;
        }
    }
    deleteUnitSpecificData();
    m_equipmentParticles.deleteAll();
    if (m_pUnitModel) {
        delete m_pUnitModel;
        m_pUnitModel = NULL;
    }
    if (m_movementPath) {
        delete m_movementPath;
        m_movementPath = NULL;
    }
    if (m_pathfinder) {
        delete m_pathfinder;
        m_pathfinder = NULL;
    }
}

#include "StringUtilities.h"
#include "Utilities.h"

void CCharacter::selectAttack(EATTACK_RANGE_TYPE type)
{
    if ((m_attack && m_attackTime > 0.0f) || !m_pUnitModel) return;
    m_attack = NULL;
    bool secondary = false;
    if (m_pInventory && m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0))) {
        if (m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1)) &&
            m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1))->ISA(static_cast<UNITTYPES::EUNITTYPES>(8))) {
            if (type == 0) secondary = m_attackFlag37E;
            else if (type == 1) secondary = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1))->ISA(static_cast<UNITTYPES::EUNITTYPES>(60));
            else if (type == 2) secondary = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1))->ISA(static_cast<UNITTYPES::EUNITTYPES>(35));
        }
    } else if (m_pInventory && m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1)) &&
               m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1))->ISA(static_cast<UNITTYPES::EUNITTYPES>(8))) {
        secondary = true;
    } else {
        if (static_cast<int>(m_attacks.size()) == 0) return;
        m_attackItem = NULL;
        m_attack = m_attacks[UTILITIES::randomIntegerBetweenVolatile(0, static_cast<int>(m_attacks.size()) - 1)];
        if (!m_attack) return;
        m_attack->m_animationIndex = m_pUnitModel->findRandomAnimation(m_attack->m_sAnimationName);
        if (!m_weaponTrails[0]) {
            Ogre::SceneManager* scene = m_pResourceManager ? m_pResourceManager->getSceneManager() : NULL;
            m_weaponTrails[0] = new CWeaponTrail(scene, STRINGS::uniqueName("trail_"), 20, 1.0f);
            m_weaponTrails[0]->setMaterialName(alignment() == 1 ? "WeaponTrail" : "WeaponTrailEvil");
        }
        return;
    }
    m_attackItem = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(secondary ? 1 : 0));
    CEquipment* equipment = static_cast<CEquipment*>(m_attackItem);
    m_attack = secondary ? equipment->m_pAttackDescriptionOverride : equipment->m_pAttackDescription;
    if (m_attack) m_attack->m_animationIndex = m_pUnitModel->findRandomAnimation(m_attack->m_sAnimationName);
    if (m_attackItem->ISA(static_cast<UNITTYPES::EUNITTYPES>(102))) return;
    unsigned int index = secondary ? 1 : 0;
    if (!m_weaponTrails[index]) {
        Ogre::SceneManager* scene = m_pResourceManager ? m_pResourceManager->getSceneManager() : NULL;
        m_weaponTrails[index] = new CWeaponTrail(scene, STRINGS::uniqueName("trail_"), 20, 1.0f);
        m_weaponTrails[index]->setMaterialName(alignment() == 1 ? "WeaponTrail" : "WeaponTrailEvil");
    }
    m_weaponTrails[index]->setWeaponEntity(static_cast<CGenericModel*>(m_attackItem->getUnitModel())->getEntity());
}

void CCharacter::turnToward(const Ogre::Vector3& direction, float elapsed)
{
    if (m_eAIState == 6 || m_eAIState == 5 || m_eAIState == 12 || m_eAIState == 40 || m_turnRate288 == 0.0f) return;
    m_targetDirection = direction;
    float current = atan2f(m_vForward.x, m_vForward.z);
    float wanted = atan2f(direction.x, direction.z);
    float difference = wanted * 57.295825958251953125f - current * 57.295825958251953125f;
    if (difference > 180.0f) difference -= 360.0f;
    if (difference < -180.0f) difference += 360.0f;
    if (fabsf(difference) > 5.0f) m_turnFlag265 = true;
    float step = 0.0f;
    if (difference < 0.0f) {
        float speed = -m_turnRate288 * (difference < -1.0f ? fabsf(difference) : 1.0f);
        step = std::max(-1000.0f, speed) * elapsed;
        if (difference > step) step = difference;
    } else if (difference > 0.0f) {
        float speed = m_turnRate288 * (difference > 1.0f ? fabsf(difference) : 1.0f);
        step = std::min(1000.0f, speed) * elapsed;
        if (step > difference) step = difference;
    }
    float modifier = getEffectValue(static_cast<EEFFECT_TYPE>(21), static_cast<EDAMAGE_TYPES>(7));
    if (modifier < 0.0f) {
        float resistance = getEffectValue(static_cast<EEFFECT_TYPE>(140), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
        resistance = std::min(1.0f, std::max(0.0f, resistance));
        modifier *= 1.0f - resistance;
    }
    if (m_pMaster) modifier += m_pMaster->getEffectValue(static_cast<EEFFECT_TYPE>(92), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
    float factor = modifier > 10.0f ? 1.10000002384185791015625f : std::max(0.5f, 1.0f + modifier / 100.0f);
    Ogre::Matrix4 rotation;
    MATH::matrixRotationY(rotation, UTILITIES::VerifyFloat(step * 0.01745329238474369f * factor, 0.01745329238474369f));
    m_mOrientation = m_mOrientation * rotation;
    // The native deferred-orientation byte is part of this opaque span.
    if (!m_Padding730[0]) setOrientation(m_mOrientation, false);
    extractOrientationVectors();
}

bool CCharacter::attack()
{
    CCharacter* target = m_targetCharacter.getObject();
    if (!target && !m_targetItem.getObject() && !m_moveInputHeld) return false;
    if (!m_pInventory || static_cast<unsigned int>(m_attacks.size()) == 0 || m_attackFlag1F5) return false;
    if (m_activeSkill && (m_skillLooping || (m_skillTime > 0.0f && !m_skillInterrupted))) return false;
    if (target && target->ISA(static_cast<UNITTYPES::EUNITTYPES>(167)) && target->hasUnitTheme(L"MIMICIDLE")) {
        if (m_attackItem && m_attackItem->ISA(static_cast<UNITTYPES::EUNITTYPES>(35))) {
            if (!m_moveInputHeld) {
                float z = m_targetCharacter.getObject()->getPosition(true).z;
                float x = m_targetCharacter.getObject()->getPosition(true).x;
                setDestination(*getLevel(), x, z);
                return false;
            }
        } else {
            m_targetCharacter.getObject()->reactToDamage(this, true);
            return false;
        }
    }
    float range = attackRange();
    float rangeScale = m_attackRangeScale;
    CEquipment* secondary = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1));
    CEquipment* primary = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0));
    if (primary && secondary && secondary->ISA(static_cast<UNITTYPES::EUNITTYPES>(8))) {
        float nearRange, farRange;
        if ((secondary->ISA(static_cast<UNITTYPES::EUNITTYPES>(35)) && !primary->ISA(static_cast<UNITTYPES::EUNITTYPES>(35))) ||
            (primary->ISA(static_cast<UNITTYPES::EUNITTYPES>(35)) && !secondary->ISA(static_cast<UNITTYPES::EUNITTYPES>(35)))) {
            farRange = rangedRange();
            nearRange = meleeRange();
        } else {
            nearRange = farRange = range * rangeScale;
        }
        if (nearRange != farRange || m_targetCharacter.getObject() || m_targetItem.getObject()) {
            CBaseUnit* other = m_targetCharacter.getObject();
            if (!other) other = m_targetItem.getObject();
            if (other) {
                Ogre::Vector3 position = getPosition(true);
                Ogre::Vector3 destination = other->getPosition(true);
                Ogre::Vector3 delta(destination.x-position.x, 0.0f, destination.z-position.z);
                float distance = delta.length() - std::max(0.0f, other->m_fBaseUnitValue194) - std::max(0.0f, m_fBaseUnitValue194);
                selectAttack(static_cast<EATTACK_RANGE_TYPE>(nearRange >= distance ? 1 : 2));
            } else selectAttack(static_cast<EATTACK_RANGE_TYPE>(2));
        }
    } else selectAttack(static_cast<EATTACK_RANGE_TYPE>(0));
    if (!m_attack || m_attack->m_animationIndex == -1) return false;
    if (!(m_attackTime > 0.0f) && !(m_activeSkill && (m_skillLooping || (m_skillTime > 0.0f && !m_skillInterrupted)))) {
        m_Padding4D0[0] = 1;
        m_attackEvent = false;
        float modifier = getEffectValue(static_cast<EEFFECT_TYPE>(22), static_cast<EDAMAGE_TYPES>(7));
        if (modifier < 0.0f) {
            float resistance = getEffectValue(static_cast<EEFFECT_TYPE>(140), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
            resistance = std::min(1.0f, std::max(0.0f, resistance));
            modifier *= 1.0f-resistance;
        }
        float speed = std::max(0.2f, (1.0f + modifier / 100.0f) / m_attack->m_fAttackSpeed);
        if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(1))) speed *= 1.5f;
        m_attackTime = m_pUnitModel->getAnimationLengthSeconds(m_attack->m_animationIndex) / speed;
        m_pUnitModel->clearQueuedAnimations();
        blendAnimation(m_attack->m_animationIndex, false, 0.2f, speed, -1.0f);
        m_pUnitModel->queueBlendAnimation("IDLE", true, 0.2f, 1.0f);
        if (m_attack->m_bUnknown18 && m_attackItem && m_levelSound) m_levelSound->playSample(26, m_pSceneNode, 0.0f, 0.0f, false);
    }
    m_fidgetTime = std::min(m_fidgetTime, 5.0f);
    return true;
}

void CCharacter::updatePathFollowing(bool force)
{
    if (!force && !getEnabled()) {
        stopPathing();
        return;
    }
    if (!m_pathToFollow.getObject()) return;
    Ogre::Vector3 position = getPosition(true);
    position.y = 0.0f;
    bool changed = false;
    if (m_pathTime <= 0.0f) {
        m_pathTime = m_Padding770 ? m_pathToFollow.getObject()->getClosestPctOfPath(position) : 0.95f;
        changed = true;
    }
    Ogre::Vector3 point = m_pathToFollow.getObject()->getNextPointAtPercent(m_pathTime, this, m_Padding770 != 0);
    float x = point.x-position.x;
    float y = 0.0f-position.y;
    float z = point.z-position.z;
    if ((x*x + y*y) + z*z <= 2.0f) {
        float closest = m_pathToFollow.getObject()->getClosestPctOfPath(position);
        m_pathTime = m_Padding770 ? std::max(m_pathTime, closest) : std::min(m_pathTime, closest);
        if (m_Padding770) {
            if (m_pathTime <= 1.0f || changed) {
                m_pathTime += 0.05f;
                if (!(m_pathTime < 0.95f)) {
                    m_pathTime = 1.0f;
                    if (m_keepPathWhenAIChanges) {
                        m_Padding770 = 0;
                        changed = true;
                    } else if (!m_pathToFollow.getObject()->m_bUnknown136) {
                        m_pathToFollow.getObject()->m_bUnknown136 = true;
                        m_pathToFollow.getObject()->BroadcastEvent(110);
                        changed = false;
                    } else changed = true;
                } else changed = true;
            }
        } else if (m_pathTime >= 0.0f) {
            m_pathTime -= 0.05f;
            if (0.05f >= m_pathTime) {
                m_pathTime = 0.0f;
                if (m_keepPathWhenAIChanges) m_Padding770 = 1;
            }
            changed = true;
        }
    }
    CPathController* path = m_pathToFollow.getObject();
    if (!path) return;
    bool needsDestination = changed || (!m_isPathing && !path->m_bUnknown136);
    m_returningToTown = path->m_bUnitRunsOnPath;
    if (!needsDestination) return;
    Ogre::Vector3 destination = m_pathToFollow.getObject()->getNextPointAtPercent(m_pathTime, this, m_Padding770 != 0);
    setDestination(*getLevel(), destination.x, destination.z);
    if (!m_isPathing && !m_pathToFollow.getObject()->m_bUnknown136) {
        m_pathToFollow.getObject()->m_bUnknown136 = true;
        m_pathToFollow.getObject()->BroadcastEvent(110);
    }
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) && m_pathToFollow.getObject() && m_pathToFollow.getObject()->m_bUnknown136)
        setPathToFollow(NULL);
}

void CCharacter::updatePathing(float elapsed)
{
    if (!m_isPathing) return;
    Ogre::Vector3 nearest, offset;
    unsigned int index;
    float distance;
    m_movementPath->FindNearestPoint(m_vPosition, nearest, offset, index, distance, 0.0f);
    if (distance >= m_movementPath->m_fPathLength) {
        stopPathing();
        return;
    }
    float ahead = distance + 0.1f;
    if (ahead > m_movementPath->m_fPathLength) ahead = m_movementPath->m_fPathLength;
    m_pathDestination = m_movementPath->GetPositionAtDistance(ahead);
    ahead = distance + 0.3f;
    if (ahead > m_movementPath->m_fPathLength) ahead = m_movementPath->m_fPathLength;
    Ogre::Vector3 forward = m_movementPath->GetSplinePositionAtDistance(ahead);
    ahead -= 0.3f;
    if (ahead < 0.0f) ahead = 0.0f;
    Ogre::Vector3 behind = m_movementPath->GetSplinePositionAtDistance(ahead);
    Ogre::Vector3 direction = forward-behind;
    direction.normalise();
    turnToward(direction, elapsed);
    float previousY = m_movement.y;
    m_movement = Ogre::Vector3(m_pathDestination.x-nearest.x, 0.0f, m_pathDestination.z-nearest.z);
    m_movement.normalise();
    Ogre::Vector3 normal;
    std::memcpy(&normal, m_Padding6D4+4, sizeof(normal));
    m_movement = normal.crossProduct(m_movement).crossProduct(m_groundFlag ? normal : Ogre::Vector3::UNIT_Y);
    float projectedY = m_movement.y;
    m_movementPath->FindNearestPoint(forward, nearest, offset, index, ahead, 0.0f);
    if (distance >= ahead && m_movementPath->m_fPathLength < 1.0f) stopPathing();
    float speed = m_returningToTown && m_runningSpeed > m_walkingSpeed ? runningSpeed() : walkingSpeed();
    float scale;
    std::memcpy(&scale, m_Padding25C, sizeof(scale));
    m_movement *= speed * scale;
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(1))) {
        std::memcpy(&scale, m_Padding25C, sizeof(scale));
        m_movement *= 1.5f * scale;
    }
    m_movement.y += previousY-projectedY;
}

#include "CameraControl.h"

void CCharacter::spawn()
{
    if (m_pResourceManager->getCameraControl()) {
        CCameraControl* camera = m_pResourceManager->getCameraControl();
        Ogre::Vector3 position(camera->m_fUnknown4C, camera->m_fUnknown50, camera->m_fUnknown54);
        calculateActiveRange(position);
    }
    std::string animation = STRINGS::StringConvertToNarrow(STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"SPAWN_ANIM", L"SPAWN")).c_str());
    if (m_pUnitModel && m_pUnitModel->animationExistsSubstring(animation) && m_bVisible && m_bInActiveRange) {
        setAIState(static_cast<EAIState>(12));
        int index = m_pUnitModel->findRandomAnimation(animation);
        m_pUnitModel->playAnimation(index, false, 1.0f, -1.0f);
        m_pUnitModel->queueBlendAnimation("IDLE", true, 0.2f, 1.0f);
        if (getSpawnInvisible()) {
            m_currentOpacity = 0.0f;
            updateOpacity(0.0f, true);
        }
        setRenderBehind(false);
        if (m_levelSound) m_levelSound->playSample(19, m_pSceneNode, 0.0f, 0.0f, false);
        if (m_equipmentParticles[5]) {
            Ogre::Vector3 offset = m_pUnitModel->getPosition(false);
            Ogre::Vector3 position = getPosition(true);
            position += offset;
            std::memcpy(m_Padding210, &position, sizeof(position));
            m_equipmentParticles[5]->setPosition(position);
            m_equipmentParticles[5]->Start();
        }
    } else setAIState(static_cast<EAIState>(m_targetCharacter.getObject() ? 4 : 2));
}

CCharacter* CCharacter::calculateTargetInSight(EAlignment alignment, bool attached)
{
    if (alignment == static_cast<EAlignment>(7)) alignment = getTargetAlignment();
    Ogre::Matrix4 transformation = m_mOrientation;
    transformation.setTrans(m_vPosition);
    float angle = viewAngle();
    float range = sightRange();
    float multiplier = 1.0f-getEffectValue(static_cast<EEFFECT_TYPE>(144), static_cast<EDAMAGE_TYPES>(7));
    multiplier = multiplier > 0.0f ? std::min(multiplier,1.0f) : 0.0f;
    float minimum;
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(167)) && hasUnitTheme(L"MIMICIDLE")) {
        std::memcpy(&range, m_Padding36C, sizeof(range));
    }
    std::memcpy(&minimum, m_Padding36C, sizeof(minimum));
    float scaledRange = range*multiplier;
    CCharacter* target = getLevel()->findCharacterWithinView(transformation, alignment, minimum*multiplier, angle*multiplier, scaledRange, attached, this, NULL);
    if (!target && m_activeSkill) {
        float skillAngle = m_activeSkill->getFindTargetAngle();
        std::memcpy(&minimum, m_Padding36C, sizeof(minimum));
        target = getLevel()->findCharacterWithinView(transformation, static_cast<EAlignment>(m_activeSkill->m_iTargetAlignment), minimum*multiplier, skillAngle*multiplier, scaledRange, attached, this, m_activeSkill);
    }
    if (m_pMaster && !target && !ISA(static_cast<UNITTYPES::EUNITTYPES>(169))) {
        Ogre::Matrix4 masterTransform = m_pMaster->getOrientation();
        masterTransform.setTrans(m_pMaster->getPosition(true));
        std::memcpy(&minimum, m_Padding36C, sizeof(minimum));
        target = getLevel()->findCharacterWithinView(masterTransform, alignment, minimum, angle, range, attached, this, NULL);
    }
    return target;
}

static void setCharacterEquipmentAlignmentTextures(CEquipment* equipment, const wchar_t* outline, const wchar_t* highlight)
{
    if (equipment->getUnitModel()) {
        { std::wstring name(outline); static_cast<CGenericModel*>(equipment->getUnitModel())->setRenderBehindTexture(name); }
        { std::wstring name(highlight); static_cast<CGenericModel*>(equipment->getUnitModel())->setHighlightTexture(name); }
    }
    if (equipment->getUnitModelSecondary()) {
        { std::wstring name(outline); static_cast<CGenericModel*>(equipment->getUnitModelSecondary())->setRenderBehindTexture(name); }
        // The native secondary-model branch highlights the primary model again.
        { std::wstring name(highlight); static_cast<CGenericModel*>(equipment->getUnitModel())->setHighlightTexture(name); }
    }
}

void CCharacter::setAlignment(EAlignment alignment)
{
    m_alignment = alignment;
    if (!m_pUnitModel || !m_Padding4A1[0] || !m_pInventory) return;
    if (alignment == static_cast<EAlignment>(4) || alignment == static_cast<EAlignment>(2)) {
        if (ISA(static_cast<UNITTYPES::EUNITTYPES>(167))) {
            m_pUnitModel->setRenderBehindTexture(L"media/sharedtextures/outlineblue.dds");
            m_pUnitModel->setHighlightTexture(L"media/sharedtextures/highlight.dds");
        } else {
            m_pUnitModel->setRenderBehindTexture(L"media/sharedtextures/outlinered.dds");
            m_pUnitModel->setHighlightTexture(L"media/sharedtextures/highlightred.dds");
        }
        for (unsigned int i = 0; i < 12; ++i) {
            CEquipment* equipment = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(i));
            if (equipment) setCharacterEquipmentAlignmentTextures(equipment, L"media/sharedtextures/outlinered.dds", L"media/sharedtextures/highlightred.dds");
        }
    } else {
        m_pUnitModel->setRenderBehindTexture(L"media/sharedtextures/outlineblue.dds");
        m_pUnitModel->setHighlightTexture(L"media/sharedtextures/highlight.dds");
        m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0));
        for (unsigned int i = 0; i < 12; ++i) {
            CEquipment* equipment = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(i));
            if (equipment) setCharacterEquipmentAlignmentTextures(equipment, L"media/sharedtextures/outlineblue.dds", L"media/sharedtextures/highlight.dds");
        }
    }
}

CCharacter::CCharacter(CResourceManager* resources)
    : CBaseUnit(resources, static_cast<EBASEUNIT_TYPE>(0)),
      m_pathTime(-1.0f),
      m_damageOverTimeTaken(0.0f),
      m_damageDisplayTime(0.0f),
      m_groundFlag(false),
      m_attackFlag1F5(false),
      m_pUnitModel(NULL),
      m_pPaperdollModel(NULL),
      m_pathDestination(Ogre::Vector3(0,0,0)),
      m_movement(Ogre::Vector3(0,0,0)),
      m_moveSpeed(1.0f),
      m_isPathing(false),
      m_turnFlag265(false),
      m_moveInputHeld(false),
      m_skillLooping(false),
      m_pathfinder(NULL),
      m_movementPath(NULL),
      m_pathGraceTime(10.0f),
      m_idleSoundTime(0.0f),
      m_fidgetTime(100.0f),
      m_turnRate288(10.0f),
      m_walkingSpeed(2.5f),
      m_runningSpeed(6.25f),
      m_levelSound(NULL),
      m_secondarySound(NULL),
      m_aiAnimation(static_cast<unsigned int>(-1)),
      m_rightHandBone(NULL),
      m_fishingBone(NULL),
      m_leftHandBone(NULL),
      m_shieldBone(NULL),
      m_leftShoulderBone(NULL),
      m_rightShoulderBone(NULL),
      m_headBone(NULL),
      m_pRightHandNode(NULL),
      m_fishingNode(NULL),
      m_pLeftHandNode(NULL),
      m_pShieldNode(NULL),
      m_pLeftShoulderNode(NULL),
      m_pRightShoulderNode(NULL),
      m_pHeadNode(NULL),
      m_returningToTown(true),
      m_eAIState(static_cast<EAIState>(0)),
      m_aiType(0),
      m_alignment(static_cast<EAlignment>(2)),
      m_sightRange(7.0f),
      m_nearWalkRadius(0.0f),
      m_viewAngle(90.0f),
      m_followRange(18.0f),
      m_damageReactRange(2.0f),
      m_attackTime(0.0f),
      m_attackEvent(false),
      m_skillInterrupted(false),
      m_attackFlag37E(false),
      m_skillTime(0.0f),
      m_skillEventTriggered(false),
      m_playTime(0.0f),
      m_attack(NULL),
      m_activeSkill(NULL),
      m_previousSkill(NULL),
      m_skillCanInterrupt(false),
      m_activeSkillGuid(-1),
      m_leftSkillGuid(-1),
      m_leftMouseSkillGuid(-1),
      m_flag410(false),
      m_fHPFloat(7.0f),
      m_maxHPBase(7),
      m_maxHPBonus(0),
      m_previousThresholdHP(9999999.0f),
      m_naturalArmor(0),
      m_rangedStat(0),
      m_iMeleeStat(0),
      m_defenseStat(10),
      m_magicStat(10),
      m_fManaFloat(0.0f),
      m_maxManaBase(0),
      m_maxManaBonus(0.0f),
      m_iGold(0),
      m_experience(0),
      m_fame(0),
      m_fameLevel(1),
      m_experienceReward(0),
      m_fameReward(0),
      m_iUnusedStatPoints(0),
      m_iUnusedSkillPoints(0),
      m_iUnusedPerkPoints(0),
      m_characterText(NULL),
      m_characterTextParent(NULL),
      m_characterTextVisible(false),
      m_pInventory(NULL),
      m_attackItem(NULL),
      m_bCharacterFlag4A0(true),
      m_equipmentParticles(12),
      m_collisionModel(NULL),
      m_attackRangeScale(1.0f),
      m_attackRadius(0.75f),
      m_wardrobe(NULL),
      m_aiThinkTier(0),
      m_aiThinkTime(100.0f),
      m_currentOpacity(0.99900001287460327f),
      m_characterVisible(true),
      m_bInvulnerable(false),
      m_characterFlag52F(true),
      m_castsDynamicShadow(false),
      m_damageShapeEnabled(true),
      m_pMaster(NULL),
      m_masterFollowDelay(1.0f),
      m_bravery(1.0f),
      m_deathPath(NULL),
      m_deathPathDistance(0.0f),
      m_deathPathActive(false),
      m_deathPathSilent(false),
      m_allowJumpDown(false),
      m_townTravelTime(0.0f),
      m_transformationTime(0.0f),
      m_originalUnitGuid(-1),
      m_pendingPetSpawn(NULL),
      m_merchantSpawnClass(NULL),
      m_merchantMinimum(0),
      m_merchantMaximum(0),
      m_value6D0(0),
      m_flag700(false),
      m_experienceDisabled(false),
      m_champion(false),
      m_spawnFlag703(false),
      m_spawnFlag704(false),
      m_weaponsHidden(false),
      m_procTime(0.0f),
      m_targetLocked(false),
      m_forcedHidden(false),
      m_bSecondaryWeaponSet(false),
      m_petMode(1),
      m_pAIManager(NULL),
      m_CharacterValue720(1.0f),
      m_automapBillboard(NULL),
      m_particleTriggers(10),
      m_savedPathIterations(0),
      m_keepPathWhenAIChanges(false),
      m_alwaysActive(false),
      m_damageDisplayEnabled(true)
{
    std::memset(m_Padding1F6+2,0,4);
    std::memset(m_Padding240,0,12);
    const float scales[] = {1.0f,1.0f};
    std::memcpy(m_Padding25C,scales,sizeof(scales));
    const float grace = 10.0f;
    std::memcpy(m_Padding27C,&grace,sizeof(grace));
    m_Padding320[0] = 0;
    m_Padding322[0] = 0;
    std::memset(m_Padding322+2,0,4);
    std::memcpy(m_Padding322+6,scales,sizeof(scales));
    const float minimum = 4.5f;
    std::memcpy(m_Padding36C,&minimum,sizeof(minimum));
    m_Padding4A1[0] = 1;
    m_Padding4D0[0] = m_Padding4D0[1] = 0;
    const float attackValues[] = {0.5f,0.375f};
    std::memcpy(m_Padding4D0+4,attackValues,sizeof(attackValues));
    m_Padding52D[0] = 0;
    m_Padding664[0] = 0;
    const int one = 1;
    std::memcpy(m_Padding66C,&one,sizeof(one));
    const float groundValues[] = {0.0f,0.0f,1.0f,0.0f};
    std::memcpy(m_Padding6D4,groundValues,sizeof(groundValues));
    m_Padding730[0] = 0;
    m_Padding770 = 1;
    m_Padding773 = 0;
    for (unsigned int i=0;i<4;++i) {
        m_knownSpells[i] = EMPTY_WSTRING;
        m_knownSpellLevels[i] = 0;
        m_weaponTrails[i] = NULL;
    }
    m_bInActiveRange = false;
    m_movementPath = new CPath(EMPTY_STRING,false,Ogre::Vector3(0,0,0));
    m_eAIState = static_cast<EAIState>(0);
    for (unsigned int i=0;i<12;++i) m_equipmentParticles.add(NULL);
    for (unsigned int i=0;i<12;++i) {
        m_PaperdollItems[i] = NULL;
        m_PaperdollItemsSecondary[i] = NULL;
    }
    for (unsigned int i=0;i<7;++i) m_damageDefense[i] = 0;
}



#include "UnitResourceList.h"

void CCharacter::revertTransformation()
{
    m_transformationTime = 0.0f;
    CDataGroup* original = m_pResourceManager->getMasterResourceList()->getDataGroupByGuid(m_originalUnitGuid);
    if (original)
    {
        if (m_pDataGroup && m_pSkillManager)
        {
            std::vector<CDataGroup*> skills;
            unsigned int count = m_pDataGroup->GetDataGroupsMatchingName(L"SKILL", &skills);
            for (unsigned int i = 0; i < count; ++i)
            {
                std::wstring name = EMPTY_WSTRING;
                name = skills[i]->GetDataValue(L"NAME", name);
                int level = skills[i]->GetDataValue(L"LEVEL", m_pDataGroup->GetDataValue(L"LEVEL", static_cast<int>(m_iUnitLevel)));
                CSkill* skill = m_pSkillManager->getSkill(name, std::max(1, level));
                if (skill)
                {
                    if (m_activeSkillGuid == skill->getGuid())
                        m_activeSkillGuid = -1;
                    if (m_leftSkillGuid == skill->getGuid())
                        m_leftSkillGuid = -1;
                    if (m_leftMouseSkillGuid == skill->getGuid())
                        m_leftMouseSkillGuid = -1;
                    if (m_activeSkill == skill)
                        m_activeSkill = NULL;
                    if (m_previousSkill == skill)
                        m_previousSkill = NULL;
                    m_pSkillManager->deleteSpecificSkill(skill);
                }
            }
        }
        std::wstring displayName = m_characterDisplayName;
        EAlignment previousAlignment = alignment();
        deleteUnitSpecificData();
        unitInit(original, true);
        setAlignment(previousAlignment);
        m_characterDisplayName = std::wstring(displayName);
        Ogre::Vector3 position = getPosition(true);
        m_equipmentParticles[8]->setPosition(position);
        m_equipmentParticles[8]->Start();
    }
    m_originalUnitGuid = -1;
    setVisible(false, true);
    setVisible(true, true);
}


void CCharacter::convertCharacter(std::wstring name, bool showParticles)
{
    bool initialize = m_pDataGroup != NULL;
    if (m_pResourceManager && m_pResourceManager->getLevel() && m_pResourceManager->getLevel()->m_flag258)
        initialize = m_pResourceManager->getGameClient()->storedUnitExists(getOriginalGuid());
    if (m_pInventory)
    {
        CEquipment* equipment = getWeaponInRightHand();
        if (equipment)
        {
            m_pInventory->removeEquipment(equipment);
            delete equipment;
        }
        equipment = getWeaponInLeftHand();
        if (equipment)
        {
            m_pInventory->removeEquipment(equipment);
            delete equipment;
        }
    }
    if (m_pDataGroup && m_pSkillManager)
    {
        std::vector<CDataGroup*> skills;
        unsigned int count = m_pDataGroup->GetDataGroupsMatchingName(L"SKILL", &skills);
        for (unsigned int i = 0; i < count; ++i)
        {
            std::wstring skillName = EMPTY_WSTRING;
            skillName = skills[i]->GetDataValue(L"NAME", skillName);
            int level = skills[i]->GetDataValue(L"LEVEL", m_pDataGroup->GetDataValue(L"LEVEL", static_cast<int>(m_iUnitLevel)));
            CSkill* skill = m_pSkillManager->getSkill(skillName, std::max(1, level));
            if (skill)
            {
                if (m_activeSkillGuid == skill->getGuid())
                    m_activeSkillGuid = -1;
                if (m_leftSkillGuid == skill->getGuid())
                    m_leftSkillGuid = -1;
                if (m_leftMouseSkillGuid == skill->getGuid())
                    m_leftMouseSkillGuid = -1;
                if (m_activeSkill == skill)
                    m_activeSkill = NULL;
                if (m_previousSkill == skill)
                    m_previousSkill = NULL;
                m_pSkillManager->deleteSpecificSkill(skill);
            }
        }
    }
    CDataGroup* data = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(L"MONSTERS", name);
    if (!data)
        data = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(L"PLAYERS", name);
    if (data)
    {
        deleteUnitSpecificData();
        unitInit(data, initialize);
        if (showParticles && !m_pResourceManager->getEditorIsRunning())
        {
            Ogre::Vector3 position = getPosition(true);
            m_equipmentParticles[8]->setPosition(position);
            m_equipmentParticles[8]->Start();
        }
    }
    else
        Ogre::LogManager::getSingleton().logMessage(
            STRINGS::StringConvertToNarrow((L"Missing datagroup for character " + name).c_str()), Ogre::LML_NORMAL, false);
}


int CCharacter::maximumDamageForDisplay(bool melee, bool elementalOnly, bool unmodified)
{
    if (!m_attack)
    {
        selectAttack(static_cast<EATTACK_RANGE_TYPE>(0));
        if (!m_attack)
            return 0;
    }
    int maximum = 0;
    for (int hand = 1; hand >= 0; --hand)
    {
        EEQUIP_LOCATIONS slot = static_cast<EEQUIP_LOCATIONS>(hand);
        if (!m_pInventory->getEquipmentEquippedAt(slot) ||
            m_pInventory->getEquipmentEquippedAt(slot)->ISA(static_cast<UNITTYPES::EUNITTYPES>(35)) == melee ||
            (hand == 1 && !m_pInventory->getEquipmentEquippedAt(slot)->ISA(static_cast<UNITTYPES::EUNITTYPES>(8))))
            continue;
        CEquipment* weapon = m_pInventory->getEquipmentEquippedAt(slot);
        int damage = elementalOnly ? 0 : weapon->maximumDamage();
        float physicalBonus = 0.0f;
        if (!unmodified)
        {
            bool ranged = weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(35));
            if (ranged)
            {
                physicalBonus = getEffectValue(static_cast<EEFFECT_TYPE>(16), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
                physicalBonus += static_cast<float>(dexterity()) / 100.0f;
            }
            else
            {
                physicalBonus = getEffectValue(static_cast<EEFFECT_TYPE>(15), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
                physicalBonus += static_cast<float>(strength()) / 100.0f;
            }
            if (m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1)) &&
                m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0)) &&
                !m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1))->ISA(static_cast<UNITTYPES::EUNITTYPES>(21)))
                physicalBonus += getEffectValue(static_cast<EEFFECT_TYPE>(88), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
            if (weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(ranged ? 163 : 162)))
                physicalBonus += getEffectValue(static_cast<EEFFECT_TYPE>(ranged ? 102 : 99), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
            if (weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(164)))
                physicalBonus += getEffectValue(static_cast<EEFFECT_TYPE>(103), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
            physicalBonus += getEffectValue(static_cast<EEFFECT_TYPE>(25), static_cast<EDAMAGE_TYPES>(0)) / 100.0f;
            physicalBonus += getEffectValue(static_cast<EEFFECT_TYPE>(25), static_cast<EDAMAGE_TYPES>(6)) / 100.0f;
            int percentDamage = static_cast<int>(ceilf(static_cast<float>(damage) * physicalBonus));
            damage += percentDamage + static_cast<int>(ceilf(getEffectValue(
                static_cast<EEFFECT_TYPE>(ranged ? 1 : 0), static_cast<EDAMAGE_TYPES>(7))));
        }
        int elementalDamage = 0;
        for (unsigned int i = 0; i < weapon->m_ElementalDamageTypes.size(); ++i)
        {
            if (elementalOnly && weapon->m_ElementalDamageTypes[i] == static_cast<EDAMAGE_TYPES>(0))
                continue;
            int amount = weapon->m_ElementalDamageBonuses[i] + weapon->m_InherentElementalDamage[i];
            if (!unmodified)
            {
                float bonus = getEffectValue(static_cast<EEFFECT_TYPE>(25), weapon->m_ElementalDamageTypes[i]) / 100.0f;
                bonus += getEffectValue(static_cast<EEFFECT_TYPE>(25), static_cast<EDAMAGE_TYPES>(6)) / 100.0f;
                if (weapon->m_ElementalDamageTypes[i] != static_cast<EDAMAGE_TYPES>(0))
                    bonus += static_cast<float>(magic()) / 100.0f;
                bonus += physicalBonus;
                amount += static_cast<int>(ceilf(static_cast<float>(amount) * bonus));
            }
            elementalDamage += amount;
        }
        int total = damage + elementalDamage;
        total += static_cast<int>(ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(10), static_cast<EDAMAGE_TYPES>(0))));
        for (int i = 0; i < 7; ++i)
        {
            if (elementalOnly && i == 0)
                continue;
            EDAMAGE_TYPES type = static_cast<EDAMAGE_TYPES>(i);
            int amount = static_cast<int>(ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(10), type)));
            if (!unmodified)
            {
                float bonus = getEffectValue(static_cast<EEFFECT_TYPE>(25), type) / 100.0f;
                bonus += getEffectValue(static_cast<EEFFECT_TYPE>(25), static_cast<EDAMAGE_TYPES>(6)) / 100.0f;
                if (i != 0)
                    bonus += static_cast<float>(magic()) / 100.0f;
                amount += static_cast<int>(ceilf(static_cast<float>(amount) * bonus));
            }
            total += amount;
        }
        if (total > maximum)
            maximum = total;
    }
    if (!maximum && !m_attacks.empty() && melee && !elementalOnly)
    {
        maximum = m_attacks[0]->m_DamageMaximums[0];
        for (int i = 1; i < 7; ++i)
        {
            int amount = m_attacks[0]->m_DamageMaximums[i];
            if (!unmodified)
            {
                float bonus = getEffectValue(static_cast<EEFFECT_TYPE>(25), static_cast<EDAMAGE_TYPES>(i)) / 100.0f;
                bonus += getEffectValue(static_cast<EEFFECT_TYPE>(25), static_cast<EDAMAGE_TYPES>(6)) / 100.0f;
                amount += static_cast<int>(ceilf(static_cast<float>(amount) * bonus));
            }
            maximum += amount;
        }
    }
    if (!m_attackItem && melee)
    {
        unsigned int originalLevel;
        std::memcpy(&originalLevel, m_Padding66C, sizeof(originalLevel));
        if (originalLevel < m_iUnitLevel)
            maximum = static_cast<int>(static_cast<float>(maximum) *
                (static_cast<float>(m_iUnitLevel) - static_cast<float>(originalLevel) + 100.0f) / 100.0f);
        if (unmodified)
            maximum = static_cast<int>(static_cast<float>(m_iMeleeStat + 100) * static_cast<float>(maximum) / 100.0f);
        else
        {
            int base = static_cast<int>(static_cast<float>(strength() + 100) * static_cast<float>(maximum) / 100.0f);
            float bonus = getEffectValue(static_cast<EEFFECT_TYPE>(25), static_cast<EDAMAGE_TYPES>(0)) / 100.0f;
            bonus += getEffectValue(static_cast<EEFFECT_TYPE>(25), static_cast<EDAMAGE_TYPES>(6)) / 100.0f;
            bonus += getEffectValue(static_cast<EEFFECT_TYPE>(15), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
            if (m_pMaster)
                bonus += m_pMaster->getEffectValue(static_cast<EEFFECT_TYPE>(91), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
            int percent = static_cast<int>(ceilf(static_cast<float>(base) * bonus));
            int flat = static_cast<int>(ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(0), static_cast<EDAMAGE_TYPES>(7))));
            int extra = static_cast<int>(ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(10), static_cast<EDAMAGE_TYPES>(0))));
            maximum = base + percent + flat + extra;
        }
    }
    return maximum;
}


void CCharacter::updateInTownTimer(float elapsed, CLevel& level)
{
    bool postpone = !m_pResourceManager->getGameUI() ||
        m_pResourceManager->getGameUI()->getUIIsInCinematic();
    if (!(m_townTravelTime > 0.0f))
        return;
    m_townTravelTime -= elapsed;
    bool finished = m_townTravelTime <= 0.0f;
    if (!finished && !level.m_pLevelTemplateData->isTown())
        return;
    if (postpone)
    {
        if (finished)
            m_townTravelTime = 0.1f;
        return;
    }
    modifyHP(static_cast<float>(maxHP()));
    m_townTravelTime = 0.0f;
    setAIState(static_cast<EAIState>(0));
    if (m_pMaster)
    {
        Ogre::Vector3 position = level.randomOpenPositionRange(m_pMaster->getPosition(true), 18.0f, 25.0f, false);
        setPosition(position);
        dropToGround(level, 4.0f, false);
        if (m_pMaster->m_levelSound)
            m_pMaster->m_levelSound->queueGlobalSample(44, 0.0f, 0.1f);
    }
    CInventory* inventory = m_pInventory;
    bool sold = false;
    int gold = 0;
    for (int i = 0; i < static_cast<int>(inventory->m_equipmentRefs.size()); ++i)
    {
        CEquipment* equipment = inventory->m_equipmentRefs[i]->m_pEquipment;
        if (!equipment->getIsQuestUnit() && inventory->m_equipmentRefs[i]->m_iSlot > 11)
        {
            m_pInventory->removeEquipment(equipment);
            --i;
            m_pMaster->giveGold(equipment->sellPrice());
            gold += equipment->sellPrice();
            sold = true;
            delete equipment;
        }
    }
    if (sold)
    {
        std::wstring description = CStringTranslate::getSinglton()->getTranslateString(L"Gold from the sale of items.");
        std::wstring amount = STRINGS::GetValueAsWString(static_cast<unsigned int>(gold));
        std::wstring message = CStringTranslate::getSinglton()->getTranslateString(
            level.m_iLevelDepth == 0 && level.m_pLevelTemplateData->isTown() ?
            L"Your pet meets you in town, and brings you" : L"Your pet returns from town, and brings you");
        message = message + L"\n" + amount + L" " + description;
        std::wstring title = CStringTranslate::getSinglton()->getTranslateString(L"Pet");
        m_pResourceManager->getLevel()->m_pGameClient->getGameUI()->openModalDialog(title, message, false);
    }
    else
    {
        std::wstring message = CStringTranslate::getSinglton()->getTranslateString(
            level.m_iLevelDepth == 0 && level.m_pLevelTemplateData->isTown() ?
            L"Your pet meets you in town." : L"Your pet returns from town.");
        std::wstring title = CStringTranslate::getSinglton()->getTranslateString(L"Pet");
        m_pResourceManager->getLevel()->m_pGameClient->getGameUI()->openModalDialog(title, message, false);
    }
    modifyHP(static_cast<float>(maxHP()));
}

#include "ItemGold.h"

void CCharacter::getItem(CItem* item, CLevel& level)
{
    if (!item)
        return;
    if (item->ISA(static_cast<UNITTYPES::EUNITTYPES>(34)))
    {
        CItemGold* gold = dynamic_cast<CItemGold*>(item);
        gold->playTakeSound(NULL);
        giveGold(gold->m_goldAmount);
        setTargetItem(NULL);
        static std::wstring g_Gold;
        if (g_Gold.empty())
            g_Gold = CStringTranslate::getSinglton()->getTranslateString(L"Gold");
        CEGUI::colour top(1.0f,0.9f,0.6f,1.0f);
        CEGUI::colour bottom(1.0f,0.9f,0.6f,1.0f);
        std::string message = STRINGS::StringConvertToUTF8(STRINGS::GetValueAsWString(gold->m_goldAmount) + L" " + g_Gold);
        Ogre::Vector3 position = item->getPosition(true) + Ogre::Vector3::UNIT_Y;
        m_pResourceManager->getLevel()->m_pGameClient->getGameUI()->addTextEvent(position,message,1.0f,255.0f,top,bottom);
        level.deleteItem(item);
        return;
    }
    CEquipment* equipment = dynamic_cast<CEquipment*>(item);
    if (!equipment)
        return;
    if (!level.removeItem(item,true))
    {
        setTargetItem(NULL);
        return;
    }
    equipment->playTakeSound(NULL);
    CEquipment* pickedUp = m_pInventory->pickupEquipment(equipment,true);
    if (!pickedUp)
    {
        if (m_pInventory->equipEquipmentIntoFirstFreeLocation(equipment))
            pickedUp = equipment;
        else
        {
            if (isPlayer())
            {
                m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(2));
                if (m_levelSound)
                    m_levelSound->queueGlobalSample(47,0.0f,0.1f);
            }
            else if (m_pMaster && m_pMaster->isPlayer() && m_pMaster->m_levelSound)
                m_pMaster->m_levelSound->queueGlobalSample(42,0.0f,0.1f);
            level.addItem(equipment,m_vPosition,true);
            equipment->setPosition(m_vPosition);
            equipment->drop();
            setTargetItem(NULL);
            return;
        }
    }
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28)))
    {
        if (pickedUp->ISA(static_cast<UNITTYPES::EUNITTYPES>(120)))
            m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(10));
        else if (pickedUp->ISA(static_cast<UNITTYPES::EUNITTYPES>(129)))
            m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(19));
        if (!pickedUp->m_bUnknown348)
            m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(1));
    }
    setTargetItem(NULL);
    if (m_pInventory->canEquip(pickedUp,false))
    {
        m_pInventory->equipEquipmentIntoFirstFreeLocation(pickedUp);
        bool behind;
        std::memcpy(&behind,m_Padding4A1,sizeof(behind));
        setRenderBehind(behind);
    }
}

void CCharacter::setRimlight(std::wstring texture)
{
    if (!m_pDataGroup)
        return;
    if (m_pUnitModel)
        m_pUnitModel->setRimLighting(texture);
    if (m_wardrobe)
        m_pUnitModel->setTextureOverride(m_wardrobe->m_texture,"HELMET","SHOULDERS");
    if (m_pPaperdollModel)
    {
        m_pPaperdollModel->setRimLighting(texture);
        if (m_wardrobe)
            m_pPaperdollModel->setTextureOverride(m_wardrobe->m_texture,"HELMET","SHOULDERS");
    }
    std::wstring overrideTexture = m_pDataGroup->GetDataValue(L"TEXTURE_OVERRIDE",EMPTY_WSTRING);
    if (!overrideTexture.empty())
    {
        m_pUnitModel->setTextureOverride(overrideTexture);
        if (m_pPaperdollModel)
            m_pPaperdollModel->setTextureOverride(overrideTexture);
    }
    std::vector<CDataGroup*> replacements;
    unsigned int count = m_pDataGroup->GetDataGroupsMatchingName(L"TEXTURE_REPLACE",&replacements);
    for (unsigned int i=0;i<count;++i)
    {
        std::wstring name = replacements[i]->GetDataValue(L"NAME",L"");
        std::wstring replacement = replacements[i]->GetDataValue(L"TEXTURE",L"");
        m_pUnitModel->setTextureOverrideSingle(STRINGS::StringConvertToNarrow(name.c_str()),replacement);
        if (m_pPaperdollModel)
            m_pPaperdollModel->setTextureOverrideSingle(STRINGS::StringConvertToNarrow(name.c_str()),replacement);
    }
    if (m_pInventory)
    {
        for (unsigned int i=0;i<12;++i)
        {
            CEquipment* equipment=m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(i));
            if (equipment)
                equipment->setRimlight(texture);
        }
    }
}

bool CCharacter::castSkill(long long guid)
{
    if (m_attack && m_attackTime > 0.2f)
        return true;
    if (m_activeSkill && (m_activeSkill->m_animationID == -1 || m_activeSkill->m_interruptible) &&
        (m_skillLooping || m_skillTime > 0.0f))
        return true;
    if (guid == -1 && m_activeSkill)
        guid = m_activeSkill->getGuid();
    if (!m_pSkillManager || !m_pSkillManager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0)))
        return false;
    if (m_activeSkill != m_pSkillManager->getSkillByGuid(guid))
        m_activeSkill = m_pSkillManager->getSkillByGuid(guid);
    if (!m_activeSkill)
        return false;
    if (m_activeSkill->m_SkillData6C && m_attack && m_attackTime > 0.0f)
        return false;
    int available = mana();
    bool insufficient = available < static_cast<int>(m_activeSkill->getManaCost());
    if (!insufficient)
    {
        available = mana();
        insufficient = available < static_cast<int>(m_activeSkill->getManaCostOT());
    }
    if (insufficient)
    {
        if (m_activeSkill && (m_activeSkill->m_animationID == -1 || m_activeSkill->m_interruptible) &&
            (m_skillLooping || m_skillTime > 0.0f))
            return false;
        if (m_levelSound && !m_levelSound->bankPlaying(33))
            m_levelSound->playSample(33,m_pSceneNode,0.0f,0.0f,false);
        if (isPlayer())
        {
            m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(4));
            if (m_levelSound)
                m_levelSound->queueGlobalSample(53,0.0f,0.1f);
        }
        return false;
    }
    EAlignment targetAlignment = getTargetAlignment();
    if (m_activeSkill->getTargetType() == 2 && m_targetCharacter.getObject())
    {
        if (m_activeSkill->m_iTargetAlignment == 2)
        {
            if (isFriend(m_targetCharacter.getObject()))
                setTarget(NULL);
        }
        else if (m_activeSkill->m_iTargetAlignment == 1)
        {
            if (targetAlignment == static_cast<EAlignment>(6))
                targetAlignment = static_cast<EAlignment>(2);
            if (isEnemy(m_targetCharacter.getObject()))
                setTarget(NULL);
        }
    }
    if (!m_targetCharacter.getObject() && !m_targetItem.getObject() && m_activeSkill->getFindTargetAngle() > 0.0f)
    {
        Ogre::Quaternion orientation;
        orientation.FromAxes(Ogre::Vector3::UNIT_Y.crossProduct(m_targetDirection),Ogre::Vector3::UNIT_Y,m_targetDirection);
        Ogre::Matrix4 view(orientation);
        view.setTrans(m_vPosition);
        float range = m_activeSkill->getRange();
        range = (m_attackRadius * m_vScale.z + 0.2f + range) * m_attackRangeScale;
        float angle = m_activeSkill->getFindTargetAngle();
        CCharacter* target = getLevel()->findCharacterWithinView(view,targetAlignment,0.0f,angle,range+1.0f,true,this,m_activeSkill);
        if (target)
            setTarget(target);
        if (!m_targetCharacter.getObject())
        {
            float itemRange = (m_attackRadius * m_vScale.z + 0.2f + range) * m_attackRangeScale + 1.0f;
            CItem* item = getLevel()->findItemWithinView(view,angle,itemRange);
            if (item)
                setTargetItem(item);
        }
    }
    if (m_activeSkill->getTargetType() == 1 || m_activeSkill->getTargetType() == 11 ||
        m_activeSkill->getTargetType() == 5 || m_activeSkill->getTargetType() == 6)
    {
        if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28)))
        {
            getLevel()->m_pGameClient->findWorldLocation(m_targetPosition,true);
            Ogre::Vector3 from = m_targetPosition + Ogre::Vector3(0.0f,100.0f,0.0f);
            Ogre::Vector3 to = m_targetPosition;
            to.y -= 100.0f;
            Ogre::Vector3 hit,normal,point;
            unsigned int material;
            if (getLevel()->rayCollision(from,to,hit,normal,material,point,true) && material != 100)
                m_targetPosition = hit + Ogre::Vector3(0.0f,0.1f,0.0f);
        }
        else
        {
            if (m_targetCharacter.getObject())
            {
                float radius = m_targetCharacter.getObject()->m_fBaseUnitValue194;
                m_activeSkill->m_targetPosition = m_targetCharacter.getObject()->getPosition(true) + Ogre::Vector3(0.0f,-radius,0.0f);
            }
            else if (m_targetItem.getObject())
            {
                // The original reads the absent character's +194 field here.
                float radius = m_targetCharacter.getObject()->m_fBaseUnitValue194;
                m_activeSkill->m_targetPosition = m_targetItem.getObject()->getPosition(true) + Ogre::Vector3(0.0f,-radius,0.0f);
            }
            else
            {
                float range = m_activeSkill->getRange();
                Ogre::Vector3 forward = getForward() * range;
                float radius = m_fBaseUnitValue194;
                m_activeSkill->m_targetPosition = getPosition(true) + Ogre::Vector3(0.0f,-radius,0.0f) + forward;
            }
            Ogre::Vector3* position = m_pSkillManager->getPositionForSkill(m_activeSkill,m_targetCharacter.getObject());
            if (position)
                m_targetPosition = *position;
        }
        setTarget(NULL);
        setTargetItem(NULL);
        float targetY = m_targetPosition.y;
        m_targetPosition -= getPosition(true);
        m_targetPosition.y = 0.0f;
        float distance = m_targetPosition.length();
        if (distance > m_activeSkill->getRange())
        {
            m_targetPosition.normalise();
            m_targetPosition *= m_activeSkill->getRange();
        }
        distance = m_targetPosition.length();
        Ogre::Vector3 step = m_targetPosition;
        m_targetPosition += getPosition(true);
        if (m_activeSkill->getRequiresPathable())
        {
            step.normalise();
            step *= -0.4f;
            int count = static_cast<int>(distance / 0.4f) - 2;
            bool found = false;
            for (int i=0;i<count;++i)
            {
                if (canPathTo(m_targetPosition))
                {
                    while (!m_pathfinder->reachedGoal())
                        m_pathfinder->advanceNextNode();
                    m_targetPosition.x = m_pathfinder->getNodeX();
                    m_targetPosition.z = m_pathfinder->getNodeY();
                    found = true;
                    break;
                }
                m_targetPosition += step;
            }
            if (!found)
                m_targetPosition = getPosition(true);
        }
        else if (isPlayer())
            m_targetPosition.y = targetY;
    }
    CBaseUnit* target = m_targetCharacter.getObject();
    if (!target)
        target = m_targetItem.getObject();
    if (!m_pSkillManager->getSkillCanBeExecuted(m_activeSkill,this,static_cast<ESKILL_ACTIVATION_TYPE>(3),m_targetPosition,target,false))
        return false;
    if (isPlayer() && m_targetCharacter.getObject() && !facingTarget())
    {
        setAIState(static_cast<EAIState>(13));
        return false;
    }
    if (m_activeSkill && (m_activeSkill->m_animationID == -1 || m_activeSkill->m_interruptible) &&
        (m_skillLooping || m_skillTime > 0.0f))
        return false;
    CSkill* performed = performSkill();
    if (!performed)
        return false;
    incrementJournalStatistic(static_cast<EJournalStatistic>(8),1);
    m_skillCanInterrupt = m_activeSkill->getCanBeInterrupted();
    if (!m_gAllowSkillTesting)
        modifyMana(-static_cast<float>(m_activeSkill->getManaCost()));
    if (m_isPathing)
        m_pathGraceTime = 10.0f;
    m_isPathing = false;
    m_Padding4D0[1] = 1;
    m_skillEventTriggered = false;
    m_skillInterrupted = false;
    m_pathDestination = m_vPosition;
    performed->assignSkillAnimations(this);
    float bonus = getEffectValue(static_cast<EEFFECT_TYPE>(29),static_cast<EDAMAGE_TYPES>(7));
    if (bonus < 0.0f)
    {
        float resistance = getEffectValue(static_cast<EEFFECT_TYPE>(140),static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
        resistance = std::min(1.0f,std::max(resistance,0.0f));
        bonus *= 1.0f-resistance;
    }
    float speed = (1.0f + bonus / 100.0f) * performed->getAnimationSpeedMult();
    speed = speed < 0.2f ? 0.2f : speed;
    performed->m_animationSpeed = speed;
    int animation = isDualWielding() ? m_activeSkill->getAnimationIndexDW() : m_activeSkill->getAnimationIndex();
    int loop = isDualWielding() ? m_activeSkill->getAnimationIndexDWLoopInto() : m_activeSkill->getAnimationIndexLoopInto();
    if (m_gAllowSkillTesting && animation == -1)
    {
        animation = static_cast<CGenericModel*>(getUnitModel())->getAnimationIndex("rslash_1");
        if (animation == -1)
            animation = 1;
    }
    m_skillTime = m_pUnitModel->getAnimationLengthSeconds(animation) / speed;
    m_pUnitModel->clearQueuedAnimations();
    if (animation != -1 && loop == -1)
    {
        blendAnimation(animation,false,0.2f,speed,m_skillTime);
        m_pUnitModel->queueBlendAnimation("IDLE",true,0.2f,1.0f);
        m_skillLooping = true;
        setAIState(static_cast<EAIState>(14));
    }
    else if (animation == -1 && loop != -1)
    {
        blendAnimation(loop,true,0.2f,speed,-1.0f);
        m_skillLooping = true;
        setAIState(static_cast<EAIState>(14));
    }
    else if (animation != -1 && loop != -1)
    {
        blendAnimation(animation,false,0.2f,speed,m_skillTime);
        m_pUnitModel->queueBlendAnimation(static_cast<unsigned int>(loop),true,0.2f,1.0f);
        m_skillLooping = true;
        setAIState(static_cast<EAIState>(14));
    }
    m_fidgetTime = m_fidgetTime > 5.0f ? 5.0f : m_fidgetTime;
    if (!m_activeSkill->m_iCharges)
        setActiveSkill(m_pSkillManager->getSkillByIndex(0),false);
    if (m_previousSkill)
    {
        setActiveSkill(m_previousSkill,false);
        m_previousSkill = NULL;
    }
    return true;
}

bool CCharacter::attemptJumpDown()
{
    if (!m_targetCharacter.getObject() || !m_pUnitModel->animationExists("JUMP_DOWN"))
        return false;
    Ogre::Vector3 start = getPosition(true) + Ogre::Vector3(0.0f, 2.5f, 0.0f);
    Ogre::Vector3 end = m_targetCharacter.getObject()->getPosition(true);
    end.y = start.y;
    Ogre::Vector3 direction = end - start;
    float distance = direction.normalise();
    if (distance > sightRange())
        return false;
    direction.normalise();
    end = start + direction * std::min(3.0f, distance);
    Ogre::Vector3 position, hit, normal, other;
    unsigned int material;
    if (getLevel()->sphereCollision(start, end, 0.05f, position, hit, normal, material, other))
        return false;
    Ogre::Vector3 open = getLevel()->randomOpenPosition(end, 1.0f, false);
    if (open == end)
        return false;
    start.x = end.x = open.x;
    start.z = end.z = open.z;
    start.y = 100.0f;
    end.y = -100.0f;
    if (!getLevel()->rayCollision(start, end, hit, normal, material, other, false))
        return false;
    float drop = m_vPosition.y - hit.y;
    if (!(drop > 0.8f && drop < 6.5f) || material == 100 || !(normal.y > 0.8f))
        return false;
    Ogre::Vector3 landing = hit + Ogre::Vector3(0.0f, 1.0f, 0.0f) * m_fBaseUnitValue194;
    if (m_isPathing)
        m_pathGraceTime = 10.0f;
    m_pathDestination = m_vPosition;
    m_isPathing = false;
    setAllowJumpDown(false);
    if (!m_deathPath)
        m_deathPath = new CPath("DROP", false, Ogre::Vector3(0.0f, 0.0f, 0.0f));
    m_deathPathActive = true;
    m_deathPathDistance = 0.0f;
    m_deathPath->Clear();
    Ogre::Vector3 middle = m_vPosition + Ogre::Vector3(
        (landing.x - m_vPosition.x) * 0.65f, 0.0f, (landing.z - m_vPosition.z) * 0.65f);
    middle.y += UTILITIES::randomBetweenVolatile(1.5f, 2.0f);
    m_deathPath->AddPoint(m_vPosition, -60.0f, 60.0f);
    m_deathPath->AddPoint(middle, -60.0f, 60.0f);
    m_deathPath->AddPoint(landing, -60.0f, 60.0f);
    m_deathPathSpeed = 10.0f;
    m_deathPathSpeed = 4.0f / m_deathPath->m_fPathLength * m_deathPathSpeed;
    if (m_deathPathSpeed < 9.0f)
        m_deathPathSpeed = 9.0f;
    if (m_deathPathSpeed > 10.0f)
        m_deathPathSpeed = 10.0f;
    m_deathPathSpeed += UTILITIES::randomBetweenVolatile(0.0f, 2.0f);
    m_deathPathSpeed *= m_pDataGroup->GetDataValue(L"JUMP_SPEED", 1.0f);
    float length = m_pUnitModel->getAnimationLengthSeconds("JUMP_DOWN");
    float speed = length / (m_deathPath->m_fPathLength / m_deathPathSpeed);
    blendAnimation("JUMP_DOWN", false, 0.05f, speed, -1.0f);
    if (!m_deathPathSilent)
    {
        queueBlendAnimation("JUMP_LAND", false, 0.1f, 1.0f);
        queueBlendAnimation("IDLE", false, 0.2f, 1.0f);
    }
    setAIState(static_cast<EAIState>(16));
    return true;
}

void CCharacter::equipmentUnequipped(CEquipment* equipment)
{
    if (!equipment)
        return;
    if (m_attackItem == equipment)
        m_attackItem = NULL;
    if (m_wardrobe && (equipment->isWardrobed(getName()) ||
        equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(12)) || equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(20))))
    {
        m_wardrobe->update(m_pInventory);
        getBones();
    }
    setRenderBehind(m_Padding4A1[0] != 0);
    if (equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(8)))
    {
        for (unsigned int i = 0; i < 2; ++i)
            if (m_weaponTrails[i])
            {
                m_weaponTrails[i]->setActive(false);
                m_weaponTrails[i]->setVisible(false);
            }
    }
    std::vector<CDataGroup*> groups;
    unsigned int count = equipment->getDataGroup()->GetDataGroupsMatchingName(L"SKILL_TO_GIVE", &groups);
    for (unsigned int i = 0; i < count; ++i)
    {
        std::wstring name = EMPTY_WSTRING;
        name = groups[i]->GetDataValue(L"NAME", name);
        int level = groups[i]->GetDataValue(L"LEVEL", equipment->getDataGroup()->GetDataValue(L"LEVEL", 1));
        CSkill* skill = m_pSkillManager->getSkill(name, std::max(1, level));
        if (skill)
        {
            if (m_activeSkillGuid == skill->getGuid())
                m_activeSkillGuid = -1;
            if (m_leftSkillGuid == skill->getGuid())
                m_leftSkillGuid = -1;
            if (m_leftMouseSkillGuid == skill->getGuid())
                m_leftMouseSkillGuid = -1;
            if (m_activeSkill == skill)
                m_activeSkill = NULL;
            if (m_previousSkill == skill)
                m_previousSkill = NULL;
            m_pSkillManager->deleteSpecificSkill(skill);
        }
    }
    if (m_pSkillManager)
    {
        Ogre::Vector3 target = getPosition(true);
        Ogre::Quaternion orientation = getOrientationQuaternion();
        Ogre::Vector3 position = getPosition(true);
        m_pSkillManager->startPassiveSkills(this, position, orientation, target);
    }
    if (m_pEffectManager)
        m_pEffectManager->calculateEffectValues();
}

void CCharacter::equipmentEquipped(CEquipment* equipment)
{
    if (!equipment)
        return;
    if (!m_attackItem && equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(8)))
        m_attackItem = equipment;
    if (m_wardrobe && (equipment->isWardrobed(getName()) ||
        equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(12)) || equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(20))))
    {
        m_wardrobe->update(m_pInventory);
        getBones();
    }
    updateOpacity(0.0f, true);
    setRenderBehind(m_Padding4A1[0] != 0);
    setAlignment(alignment());
    std::vector<CDataGroup*> groups;
    unsigned int count = equipment->getDataGroup()->GetDataGroupsMatchingName(L"SKILL_TO_GIVE", &groups);
    for (unsigned int i = 0; i < count; ++i)
    {
        std::wstring name = EMPTY_WSTRING;
        name = groups[i]->GetDataValue(L"NAME", name);
        int level = groups[i]->GetDataValue(L"LEVEL", equipment->getDataGroup()->GetDataValue(L"LEVEL", 1));
        int charges = groups[i]->GetDataValue(L"CHARGES", equipment->getDataGroup()->GetDataValue(L"CHARGES", static_cast<unsigned int>(-1)));
        CSkill* skill = addSkillByName(name, true);
        if (skill)
        {
            skill->m_iColumn = -1;
            skill->m_iCharges = charges;
            m_pSkillManager->setSkillLevel(skill, level);
        }
        else
            Ogre::LogManager::getSingleton().logMessage(
                STRINGS::StringConvertToNarrow((L"Skill not found : " + name).c_str()), Ogre::LML_NORMAL, false);
    }
    CSkillManager* skills = m_pSkillManager;
    if (skills)
    {
        Ogre::Vector3 target = getPosition(true);
        Ogre::Quaternion orientation = getOrientationQuaternion();
        Ogre::Vector3 position = getPosition(true);
        skills->startPassiveSkills(this, position, orientation, target);
    }
    if (m_pEffectManager)
        m_pEffectManager->calculateEffectValues();
}

#include "SettingsVariables.h"

void CCharacter::setDestination(CLevel& level, float x, float z)
{
    if (!m_pathfinder)
        return;
    if (m_eAIState >= 32 && m_eAIState <= 34)
        setAIState(static_cast<EAIState>(2));
    bool held = m_moveInputHeld;
    if (m_activeSkill && (m_activeSkill->m_animationID == -1 || m_activeSkill->m_interruptible) &&
        (m_skillLooping || m_skillTime > 0.0f) && m_activeSkill->m_stopsPathingOnCompletion)
        held = false;
    if (m_eAIState == 6 || m_eAIState == 5 || m_eAIState == 12 ||
        (walkingSpeed() == 0.0f && runningSpeed() == 0.0f) || held)
    {
        if (m_isPathing)
            m_pathGraceTime = 10.0f;
        m_pathDestination = m_vPosition;
        m_isPathing = false;
        if (held)
            attack();
        m_targetPosition = Ogre::Vector3(x, 0.0f, z);
        return;
    }
    m_pathGraceTime = 0.0f;
    m_targetPosition = Ogre::Vector3(x, m_vPosition.y, z);
    if (m_attack && m_attackTime > 0.2f)
    {
        if (!m_activeSkill)
            return;
        if (!m_skillLooping && (!(m_skillTime > 0.0f) || m_skillInterrupted))
            return;
        if (!m_activeSkill->m_stopsPathingOnCompletion)
            return;
    }
    else if (m_activeSkill && (m_skillLooping || (m_skillTime > 0.0f && !m_skillInterrupted)) &&
             !m_activeSkill->m_stopsPathingOnCompletion)
        return;
    if (m_activeSkill && (m_activeSkill->m_animationID == -1 || m_activeSkill->m_interruptible) &&
        (m_skillLooping || m_skillTime > 0.0f) && m_activeSkill->m_stopsPathingOnCompletion)
    {
        Ogre::Vector3 direction(x - m_vPosition.x, 0.0f, z - m_vPosition.z);
        if (direction.length() < 2.0f)
        {
            direction.normalise();
            direction *= 2.0f;
            m_targetPosition = direction + m_vPosition;
            x = m_targetPosition.x;
            z = m_targetPosition.z;
        }
    }
    bool wasOnAvoidanceMap = m_bBaseUnitFlag19B;
    removeFromAvoidanceMap(level);
    bool ignoreOccupancy = !m_pResourceManager->getGameUI() ||
        m_pResourceManager->getGameUI()->getUIIsInCinematic();
    if (ignoreOccupancy)
        m_pathfinder->m_bIgnoreOccupancy = true;
    if (!m_pathfinder->findPath(m_vPosition.x, m_vPosition.z, x, z))
    {
        if (wasOnAvoidanceMap && m_eAIState != 5 && m_eAIState != 6)
            addToAvoidanceMap(level);
        if (ignoreOccupancy)
            m_pathfinder->m_bIgnoreOccupancy = false;
        return;
    }
    if (ignoreOccupancy)
        m_pathfinder->m_bIgnoreOccupancy = false;
    if (!m_pathfinder->reachedGoal())
    {
        m_movementPath->Clear();
        Ogre::Vector3 anchor(0.0f, 0.0f, 0.0f);
        Ogre::Vector3 node(0.0f, 0.0f, 0.0f);
        m_pathfinder->advanceNextNode();
        bool checkGoal = true;
        for (;;)
        {
            if (checkGoal && m_pathfinder->reachedGoal())
                break;
            node.x = m_pathfinder->getNodeX();
            node.z = m_pathfinder->getNodeY();
            node.y = 0.0f;
            bool addedPoint = false;
            if (m_movementPath->m_lPoints.empty())
            {
                anchor = Ogre::Vector3(m_vPosition.x, 0.0f, m_vPosition.z);
                m_movementPath->AddPoint(anchor, -60.0f, 60.0f);
                addedPoint = true;
            }
            else if (!level.passableBetween(anchor, node, false))
            {
                anchor = node;
                m_movementPath->AddPoint(anchor, -60.0f, 60.0f);
                addedPoint = true;
            }
            m_pathfinder->advanceNextNode();
            checkGoal = true;
            if (m_pathfinder->reachedGoal() && !addedPoint)
            {
                if (!level.passableBetween(anchor, m_targetPosition, false) || !level.positionPassable(m_targetPosition))
                {
                    m_movementPath->AddPoint(node, -60.0f, 60.0f);
                    if (m_pathfinder->reachedGoal())
                        break;
                    checkGoal = false;
                }
            }
        }
        if (!m_movementPath->m_lPoints.empty())
        {
            if (level.positionPassable(m_targetPosition) &&
                level.passableBetween(characterPathPoint(m_movementPath, m_movementPath->m_lPoints.size() - 1), m_targetPosition, false))
                m_movementPath->AddPoint(Ogre::Vector3(x, 0.0f, z), -60.0f, 60.0f);
            else
                m_targetPosition = characterPathPoint(m_movementPath, m_movementPath->m_lPoints.size() - 1);
            m_isPathing = true;
            m_pathDestination = characterPathPoint(m_movementPath, 0);
            m_pathDestination.y = 0.0f;
        }
    }
    if (0.0f >= m_movementPath->m_fPathLength)
        m_isPathing = false;
    if (wasOnAvoidanceMap && m_eAIState != 5 && m_eAIState != 6)
        addToAvoidanceMap(level);
    CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    if (settings->GetInt(KSETTINGS_DISPLAY_PATHING))
        displayPath();
}

#include "Graph.h"
#include "GraphManager.h"
#include "UnitSpawner.h"

void CCharacter::applySaveState(CCharacterSaveState& state)
{
    setPosition(state.m_position);
    setOrientation(state.m_orientation, false);
    m_characterDisplayName = state.m_name;
    m_iRoomIndex = state.m_value184;
    setEnabled(state.m_flag31);
    setLevel(state.m_valueD0, false);
    m_fameLevel = state.m_valueD8;
    if (state.m_guid10 != -1)
        setOriginalGuid(state.m_guid10);
    m_petMode = state.m_petMode;
    m_bSecondaryWeaponSet = state.m_flag33;
    m_iQuestGuid = state.m_guid200;
    m_iQuestState = state.m_value208;
    for (unsigned int i = 0; i < 7; ++i)
        m_damageDefense[i] = state.m_damageDefense[i];
    m_playTime = state.m_playTime;
    setScale(state.m_scale);
    m_bravery = state.m_bravery;
    m_champion = state.m_flag32;
    m_originalUnitGuid = state.m_guid28;
    m_experience = state.m_valueD4;
    m_fame = state.m_valueDC;
    m_fHPFloat = state.m_hp;
    m_maxHPBonus = state.m_valueE8;
    m_maxHPBase = state.m_valueE4;
    m_fManaFloat = state.m_mana;
    m_maxManaBase = state.m_maxManaBase;
    m_maxManaBonus = static_cast<float>(state.m_maxManaBonus);
    m_defenseStat = state.m_defenseStat;
    m_magicStat = state.m_magicStat;
    m_rangedStat = state.m_rangedStat;
    m_iMeleeStat = state.m_meleeStat;
    m_experienceReward = state.m_experienceReward;
    m_fameReward = state.m_fameReward;
    m_iUnusedStatPoints = state.m_freeStatPoints;
    m_iUnusedSkillPoints = state.m_freeSkillPoints;
    m_iUnusedPerkPoints = state.m_freePerkPoints;
    m_iGold = state.m_value174;
    m_characterDisplayName = state.m_name;
    m_activeSkillGuid = state.m_guidB8;
    m_leftSkillGuid = state.m_guidC0;
    m_leftMouseSkillGuid = state.m_guidC8;
    if (m_pSkillManager)
    {
        unsigned int count = m_pSkillManager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0));
        for (unsigned int i = 0; i < count; ++i)
        {
            CSkill* skill = m_pSkillManager->getSkillByIndex(i);
            if (skill && i < state.m_values.size())
                m_pSkillManager->setSkillLevel(skill, state.m_values[i]);
        }
    }
    for (unsigned int i = 0; i < 4; ++i)
    {
        if (state.m_knownSpells[i] != EMPTY_WSTRING)
            learnSpell(state.m_knownSpells[i], state.m_spellLevels[i]);
        else
            state.m_knownSpells[i] = EMPTY_WSTRING;
    }
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(41)) || ISA(static_cast<UNITTYPES::EUNITTYPES>(130)))
        m_bInvulnerable = true;
    if (m_pInventory)
    {
        bool generated = false;
        if (ISA(static_cast<UNITTYPES::EUNITTYPES>(41)) &&
            m_playTime > static_cast<float>(CGameGlobals::getSingleton()->m_merchantRespawnTime))
        {
            m_playTime = 0.0f;
            if (m_pInventory)
            {
                delete m_pInventory;
                m_pInventory = NULL;
            }
            m_pInventory = new CInventory(this, 42);
            m_pInventory->addSection(static_cast<EINVENTORY_PANES>(3), 42);
            m_pInventory->addSection(static_cast<EINVENTORY_PANES>(4), 42);
            m_pInventory->addListener(this);
            generateMerchantInventory();
            generated = true;
        }
        if (!generated)
        {
            m_pInventory->m_bUnknown15 = true;
            for (int i = 0; i < static_cast<int>(state.m_pets.size()); ++i)
            {
                if (state.m_pets[i]->m_iUnitValue60 == -1)
                    continue;
                CBaseUnit* unit = m_pResourceManager->createUnit(state.m_pets[i]->m_iUnitValue60, 1, true, false);
                if (!unit)
                    continue;
                CEquipment* equipment = dynamic_cast<CEquipment*>(unit);
                int slot = state.m_pets[i]->m_iIndex;
                equipment->applySaveState(*state.m_pets[i]);
                equipment->setRenderBehind(m_Padding4A1[0] != 0);
                CEquipment* picked = m_pInventory->pickupEquipment(equipment, slot, true);
                if (!picked)
                    delete equipment;
                else if (ISA(static_cast<UNITTYPES::EUNITTYPES>(127)))
                    picked->recalculatePrice();
            }
            m_pInventory->m_bUnknown15 = false;
        }
        if (ISA(static_cast<UNITTYPES::EUNITTYPES>(41)))
            m_pInventory->m_bUnknown14 = false;
    }
    for (unsigned int group = 0; group < 3; ++group)
    {
        for (unsigned int i = 0; i < state.m_items[group].size(); ++i)
        {
            float value = state.m_items[group][i]->m_fValueC0;
            CEffect* effect = addNewEffect(state.m_items[group][i]);
            if (effect)
            {
                effect->m_fValueC0 = value;
                activateEffect(effect);
            }
        }
        state.m_items[group].clear();
    }
    CLevel* level = getLevel();
    if (state.m_guid58 != -1 && m_pResourceManager && level)
    {
        int count = level->getRoomScenes().size();
        for (int i = 0; i < count; ++i)
        {
            CEditorScene* scene = level->getRoomScenes()[i];
            TArrayList<CEditorBaseObject*> objects;
            scene->GetObjectsCreatedByADescriptor(L"Unit Spawner", &objects);
            for (unsigned int j = 0; j < objects.size(); ++j)
            {
                CUnitSpawner* spawner = dynamic_cast<CUnitSpawner*>(objects[j]);
                if (spawner && spawner->getOriginalGuid() == state.m_guid58)
                    spawner->addSpawnedUnit(this);
            }
        }
        Ogre::LogManager::getSingleton().logMessage(
            "Unable to find unit spawner for monster.  Meaning the unit spawner didn't spawn this time either because of a bug or editor logic.", Ogre::LML_CRITICAL, false);
    }
    if (m_champion)
    {
        if (m_pDataGroup && !m_pDataGroup->GetDataValue(L"BOSS_CHAMPION", false))
        {
            addUnitTheme(L"CHAMPION");
            m_alwaysActive = false;
        }
        else
            m_alwaysActive = true;
    }
    m_transformationTime = state.m_transformationTime;
    m_townTravelTime = state.m_townTravelTime;
    if (m_townTravelTime > 0.0f)
        setAIState(static_cast<EAIState>(42));
    setAlignment(static_cast<EAlignment>(state.m_alignment));
    if (state.m_flag20C != m_forcedHidden)
        setMeshVisible(!state.m_flag20C, false);
    CGraph* graph = m_pResourceManager->getGraphDamage();
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(28)))
        graph = CGraphManager::getSingleton()->getGraph(L"DAMAGE_MONSTER");
    m_value6D0 = static_cast<int>(floorf(graph->getValue(static_cast<float>(m_iUnitLevel), 0)));
    if (state.m_guid50 != -1 && m_pResourceManager && getLevel())
    {
        CBaseUnit* unit = getLevel()->getCharacterByOriginalGuid(state.m_guid50, -1, -1);
        CCharacter* owner = dynamic_cast<CCharacter*>(unit);
        if (!owner)
        {
            CPlayer* player = m_pResourceManager->getGameClient()->getPlayer();
            if (player->getOriginalGuid() == state.m_guid50)
                owner = player;
            else
                for (unsigned int i = 0; i < player->m_Followers.size(); ++i)
                    if (player->m_Followers[i]->getOriginalGuid() == state.m_guid50)
                    {
                        owner = player->m_Followers[i];
                        break;
                    }
        }
        if (owner)
            owner->addPet(this);
    }
}

#include "CameraControl.h"
#include "CameraShake.h"

static void characterDeathShake(CResourceManager* resources, CCameraShake* shake, const Ogre::Vector3& position)
{
    shake->m_fCameraPositionX = position.x;
    shake->m_fCameraPositionY = position.y;
    shake->m_fCameraPositionZ = position.z;
    shake->m_bCameraShakeActive = true;
    resources->getCameraControl()->addCameraShake(shake,true);
}

void CCharacter::die(CCharacter* killer, const Ogre::Vector3* direction, float force, bool silent)
{
    if (!m_iUnitLevel)
        return;
    if (m_pMaster)
        m_pMaster->removePet(this);
    if (m_eAIState == AISTATE_DYING || m_eAIState == AISTATE_DEAD)
        return;
    if (hasUnitTheme(L"STUNNED"))
        removeUnitTheme(L"STUNNED");
    m_bInActiveRange = true;
    m_bInFadeRange = true;
    if (m_pEffectManager && m_pEffectManager->hasEffect(static_cast<EEFFECT_TYPE>(129)))
    {
        m_equipmentParticles[8]->setPosition(getPosition(true));
        m_equipmentParticles[8]->Start();
        setMeshVisible(false,true);
    }
    incrementJournalStatistic(static_cast<EJournalStatistic>(5),1);
    if (m_isPathing)
        m_pathGraceTime = 10.0f;
    m_isPathing = false;
    m_pathDestination = m_vPosition;
    if (m_bBlocksPath)
        m_bPathingFlag19C = false;
    setAIState(AISTATE_DYING);
    m_attackTime = 0.0f;
    m_skillTime = 0.0f;
    m_skillLooping = false;
    if (HP() > 0)
        modifyHP(static_cast<float>(-HP()));
    if (m_pSkillManager)
    {
        m_pSkillManager->stopAllSkills(true,true,false);
        if (m_pSkillManager)
        {
            CCharacter* target = m_targetCharacter.getObject();
            Ogre::Vector3 targetPosition = getPosition(true);
            Ogre::Quaternion orientation = getOrientationQuaternion();
            Ogre::Vector3 position = getPosition(true);
            m_pSkillManager->fireSkillsOnDeath(this,SKILL_ACTIVATION_NORMAL,position,orientation,targetPosition,target);
        }
    }
    executeProcs(static_cast<EEFFECT_TYPE>(105),killer);
    CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    int blood = settings->GetInt(KSETTINGS_SHOW_BLOOD);
    CParticle* deathParticle = m_equipmentParticles[blood == 1 ? 3 : 4];
    if (deathParticle)
    {
        Ogre::Vector3 position;
        std::memcpy(&position,m_Padding210,sizeof(position));
        deathParticle->setPosition(position);
        deathParticle->Start();
    }
    for (unsigned int i=0;i<m_particleTriggers.size();++i)
    {
        if (m_particleTriggers[i]->m_stopOnDeath && m_particleTriggers[i]->m_particle)
        {
            CParticle* particle = m_particleTriggers[i]->m_particle;
            particle->Stop(!particle->getVisible());
        }
    }
    if (m_levelSound)
        m_levelSound->playSample(12,m_pSceneNode,0.0f,0.0f,false);
    m_attack = NULL;
    setTarget(NULL);
    if (m_deathPath)
    {
        m_deathPath->Clear();
        m_deathPathActive = false;
    }

    bool handledAnimation = false;
    if (m_pEffectManager && !ISA(UNITTYPES::PLAYER) && !m_champion)
    {
        if (m_pEffectManager->getAffix(L"DAMAGEEFFECTFROZEN") || silent)
        {
            CCameraShake* shake = NULL;
            if (m_pEffectManager->getAffix(L"DAMAGEEFFECTFROZEN"))
            {
                m_equipmentParticles[9]->setPosition(getPosition(true));
                m_equipmentParticles[9]->Start();
                shake = new CCameraShake(L"CRYSTALEXPLODE",m_vUp,0.2f);
                shake->m_bCameraFallsOffWithDistance = true;
            }
            else if (m_equipmentParticles[10] && blood == 1)
            {
                CParticle* particle = m_equipmentParticles[10];
                if (particle)
                {
                    particle->setPosition(getPosition(true));
                    particle->Start();
                    shake = new CCameraShake(L"DEATHEXPLODE",m_vUp,0.3f);
                    shake->m_fMagnitudeMultiplier = UTILITIES::randomBetweenVolatile(0.5f,0.75f);
                    shake->m_bCameraFallsOffWithDistance = true;
                }
            }
            if (shake)
            {
                characterDeathShake(m_pResourceManager,shake,getPosition(true));
                setVisible(false,true);
                if (m_pUnitModel)
                    m_pUnitModel->clearAnimations();
                m_forcedHidden = true;
                CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(24),1);
                handledAnimation = true;
            }
        }
    }

    if (!handledAnimation && direction && force > 0.0f && m_pUnitModel->animationExists("DEATH_FLIGHT"))
    {
        if (!m_deathPath)
            m_deathPath = new CPath("DROP",false,Ogre::Vector3(0.0f,0.0f,0.0f));
        m_deathPathActive = true;
        m_deathPathDistance = 0.0f;
        m_deathPath->Clear();
        Ogre::Vector3 start = getPosition(true);
        Ogre::Vector3 end = *direction * force + start;
        Ogre::Vector3 minimum = start;
        Ogre::Vector3 maximum = start;
        MATH::expandBounds(minimum,maximum,end);
        minimum += Ogre::Vector3(m_fBaseUnitValue194 * -2.0f,m_fBaseUnitValue194 * -2.0f,m_fBaseUnitValue194 * -2.0f);
        maximum += Ogre::Vector3(m_fBaseUnitValue194 + m_fBaseUnitValue194,m_fBaseUnitValue194 + m_fBaseUnitValue194,m_fBaseUnitValue194 + m_fBaseUnitValue194);
        CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
        level->sortForCollision(minimum,maximum);
        Ogre::Vector3 collision;
        Ogre::Vector3 hit;
        Ogre::Vector3 normal;
        Ogre::Vector3 extra;
        unsigned int type;
        CBaseUnit* collidedUnit = NULL;
        level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
        bool sphereCollision = level->preSortedSphereCollision(start+Ogre::Vector3(0.0f,2.5f,0.0f),end+Ogre::Vector3(0.0f,2.5f,0.0f),0.4f,collision,hit,normal,type,extra,&collidedUnit,false);
        if (sphereCollision)
        {
            end.x = collision.x;
            end.z = collision.z;
        }
        m_deathPathSilent = true;
        static const Ogre::Vector3 dropVectors[5] = {
            Ogre::Vector3(0.0f,0.0f,0.0f), Ogre::Vector3(0.25f,0.0f,0.0f),
            Ogre::Vector3(-0.25f,0.0f,0.0f), Ogre::Vector3(0.0f,0.0f,0.25f),
            Ogre::Vector3(0.0f,0.0f,-0.25f)
        };
        float bestHeight = -4.0f;
        float endX = end.x;
        float endZ = end.z;
        bool missedGround = false;
        for (unsigned int i=0;i<5;++i)
        {
            Ogre::Vector3 to(endX+dropVectors[i].x,-100.0f,endZ+dropVectors[i].z);
            Ogre::Vector3 from(to.x,100.0f,to.z);
            level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            if (!level->rayCollision(from,to,hit,normal,type,extra,false))
            {
                m_deathPathSilent = true;
                missedGround = true;
                break;
            }
            float height = start.y - hit.y;
            if (height < 4.0f && height > bestHeight)
            {
                float zero = m_fBaseUnitValue194 * 0.0f;
                end = Ogre::Vector3(zero+hit.x,hit.y+m_fBaseUnitValue194,hit.z+zero);
                m_deathPathSilent = false;
                bestHeight = height;
            }
        }
        if (missedGround || m_deathPathSilent)
            end.y -= 5.0f;
        else if (!sphereCollision)
        {
            Ogre::Vector3 extended = *direction * 5.0f + start;
            minimum = maximum = start;
            MATH::expandBounds(minimum,maximum,extended);
            float low = m_fBaseUnitValue194 * -2.0f;
            float high = m_fBaseUnitValue194 + m_fBaseUnitValue194;
            minimum += Ogre::Vector3(low,low,low);
            maximum += Ogre::Vector3(high,high,high);
            level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            level->sortForCollision(minimum,maximum);
            m_deathPathSilent = true;
            level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            bool grounded = level->rayCollision(Ogre::Vector3(extended.x,100.0f,extended.z),Ogre::Vector3(extended.x,-100.0f,extended.z),hit,normal,type,extra,false);
            if (grounded && !(start.y-hit.y >= 4.0f))
                m_deathPathSilent = false;
            if (m_deathPathSilent)
            {
                end = extended;
                end.y -= 5.0f;
            }
        }
        Ogre::Vector3 middle((end.x-start.x)*0.5f+start.x,start.y+0.0f,(end.z-start.z)*0.5f+start.z);
        middle.y = UTILITIES::randomBetweenVolatile(2.0f,2.8f) + start.y;
        m_deathPath->AddPoint(start,-60.0f,60.0f);
        m_deathPath->AddPoint(middle,-60.0f,60.0f);
        m_deathPath->AddPoint(end,-60.0f,60.0f);
        m_deathPathSpeed = (4.0f / m_deathPath->m_fPathLength) * 10.0f;
        if (m_deathPathSpeed < 9.0f)
            m_deathPathSpeed = 9.0f;
        else if (m_deathPathSpeed > 12.0f)
            m_deathPathSpeed = 12.0f;
        if (m_deathPathSilent)
            m_deathPathSpeed *= 1.5f;
        m_deathPathSpeed = UTILITIES::randomBetweenVolatile(0.0f,2.0f) + m_deathPathSpeed;
        float length = m_pUnitModel->getAnimationLengthSeconds("DEATH_FLIGHT");
        blendAnimation("DEATH_FLIGHT",false,0.05f,length/(m_deathPath->m_fPathLength/m_deathPathSpeed),-1.0f);
        if (!m_deathPathSilent)
            queueBlendAnimation("DEATH_LAND",false,0.0f,1.0f);
        if (killer && killer->isPlayer())
        {
            CCameraShake* shake = new CCameraShake(L"KILL",m_vUp,0.2f);
            shake->m_fMagnitudeMultiplier = 0.5f;
            characterDeathShake(m_pResourceManager,shake,getPosition(true));
        }
        handledAnimation = true;
    }
    if (!handledAnimation)
    {
        if (m_pUnitModel->animationExistsSubstring("DIE"))
            blendAnimation(m_pUnitModel->findRandomAnimation("DIE"),false,0.2f,1.0f,-1.0f);
        else
            m_pUnitModel->clearAnimations();
    }
    if (!ISA(UNITTYPES::PLAYER) && alignment() != static_cast<EAlignment>(1) && killer && !m_spawnFlag704)
    {
        if (!m_merchantSpawnClass)
        {
            Ogre::Vector3 position = getPosition(true);
            CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            level->rollTreasure(killer,this,position);
        }
        else
        {
            CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            Ogre::Vector3 position = getPosition(true);
            unsigned int count = UTILITIES::randomIntegerBetweenVolatile(m_merchantMinimum,m_merchantMaximum);
            m_pResourceManager->createUnitsBySpawnClassAtPositionInLevel(m_merchantSpawnClass,count,position,level,this,killer,-1);
            position = getPosition(true);
            level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            level->rollMoney(killer,this,position,false);
        }
    }
    CBaseUnit::broadcastUnitState(static_cast<EUNIT_STATES>(1));
    CBaseUnit::broadcastKilled();
    CBaseUnit::questEventFire(static_cast<EQUEST_EVENTS>(1),killer,this);
}

#include "Console.h"
#include "GameSpeed.h"

namespace {
float characterRollPercent(float value)
{
    if (value > 100.0f) return 100.0f;
    return value < -100.0f ? -100.0f : value;
}
void characterRollText(CGameUI* ui, CCharacter* recipient, const std::wstring& text,
                       float height, const CEGUI::colour& color)
{
    std::string utf8 = STRINGS::StringConvertToUTF8(text);
    Ogre::Vector3 offset = Ogre::Vector3::UNIT_Y * height;
    Ogre::Vector3 position = recipient->getPosition(true);
    position = offset + position;
    ui->addTextEvent(position, utf8, 1.0f, 255.0f, color, color);
}
}

bool CCharacter::rollAttack(CLevel& level, CCharacter* target, CEquipment* weapon,
                            unsigned int flags, float damageScale, float armorScale,
                            EDAMAGE_TYPES overrideType)
{
    if (!target || target->m_eAIState == static_cast<EAIState>(5) ||
        target->m_eAIState == static_cast<EAIState>(6)) return false;
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(167)) && hasUnitTheme(L"MIMICIDLE")) return false;
    CAttackDescription* description = m_attack;
    if (!weapon) weapon = static_cast<CEquipment*>(m_attackItem);
    if (weapon) {
        if (weapon == getWeaponInLeftHand()) description = weapon->m_pAttackDescriptionOverride;
        else if (weapon == getWeaponInRightHand()) description = weapon->m_pAttackDescription;
        else {
            description = weapon->m_pAttackDescriptionOverride;
            if (!description) description = weapon->m_pAttackDescription;
        }
    }
    float reflection = target->getDmgToReflectFromMissile();
    bool armed = weapon != NULL;
    if (armed && reflection > 0.0f && weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(35))) {
        if (m_levelSound) m_levelSound->playSample(34, target->m_pSceneNode, 0.0f, 0.0f, false);
        CEffect* effect = new CEffect(static_cast<EEFFECT_TYPE>(61), true,
            static_cast<EEFFECT_ACTIVATION>(0), 0.3f, 1.0f, 0.0f, false);
        effect->m_reflectionMinimum = reflection;
        effect->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
        applyEffectOnUnit(target, target, effect);
        delete effect;
        return false;
    }
    if (!description) return false;
    bool critical = rollCritical(target);
    bool normalizeSpeed = (flags & 1024) != 0;
    int maximum = maxDamage(description, target);
    float attackSpeed = description->m_fAttackSpeed;
    if (damageScale != 1.0f) maximum = static_cast<int>(static_cast<float>(maximum) * damageScale);
    if (normalizeSpeed) maximum = static_cast<int>(ceilf(static_cast<float>(maximum) / (attackSpeed * 0.73333335f)));
    int minimum = static_cast<int>(ceilf(static_cast<float>(maximum) * 0.5f));
    CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    bool combatLog = settings->GetInt(KSETTINGS_COMBAT_LOG) > 0;
    int baseRoll = UTILITIES::randomIntegerBetweenVolatile(minimum, maximum);
    if (combatLog) {
        level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(L"Combat Rolls for Character :" + m_characterDisplayName);
        level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(
            L" Base Weapon Damage Range " + STRINGS::GetValueAsWString(minimum) + L"-" + STRINGS::GetValueAsWString(maximum));
        level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Rolled Weapon Damage " + STRINGS::GetValueAsWString(baseRoll));
    }
    if (critical) {
        int bonus = static_cast<int>(static_cast<float>(maximum) * 0.5f);
        float effect = getEffectValue(static_cast<EEFFECT_TYPE>(89), static_cast<EDAMAGE_TYPES>(7));
        baseRoll = bonus + maximum + static_cast<int>(static_cast<float>(bonus) * (effect / 100.0f));
        if (combatLog) level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Critical! Damage altered to " + STRINGS::GetValueAsWString(baseRoll));
    }
    EDAMAGE_TYPES baseType = overrideType == static_cast<EDAMAGE_TYPES>(7) ?
        static_cast<EDAMAGE_TYPES>(description->m_iUnknown78) : overrideType;
    int damage = target->modifyDamage(baseRoll, baseType, baseRoll, armorScale);
    if (combatLog) level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Damage after armor absorption " + STRINGS::GetValueAsWString(damage));
    int damages[8][2];
    damages[0][0] = baseType;
    damages[0][1] = damage;
    // The first pass computes the maximum for absorption and interruption;
    // the second pass rolls each component independently.
    int rolledTotal = baseRoll;
    unsigned int damageCount = 1;
    for (int pass = 0; pass != 2; ++pass) {
        for (int component = 0; component != 7; ++component) {
            int inherent = weapon ? weapon->getDamageBonus(static_cast<EDAMAGE_TYPES>(component)) :
                (component ? static_cast<int>(m_attacks[0]->m_DamageMaximums[component]) : 0);
            bool noInherent = inherent < 1;
            EDAMAGE_TYPES type = overrideType == static_cast<EDAMAGE_TYPES>(7) ?
                static_cast<EDAMAGE_TYPES>(component) : overrideType;
            int flat = static_cast<int>(ceilf(getEffectValue(static_cast<EEFFECT_TYPE>(10), static_cast<EDAMAGE_TYPES>(component))));
            if (flat < 1 && noInherent) continue;
            if (damageScale != 1.0f) inherent = static_cast<int>(static_cast<float>(inherent) * damageScale);
            float componentBonus = getEffectValue(static_cast<EEFFECT_TYPE>(25), type);
            float allBonus = getEffectValue(static_cast<EEFFECT_TYPE>(25), static_cast<EDAMAGE_TYPES>(6));
            float bonus = allBonus / 100.0f + componentBonus / 100.0f;
            float attributeBonus;
            int attribute;
            if (!weapon || !weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(35))) {
                attributeBonus = getEffectValue(static_cast<EEFFECT_TYPE>(15), static_cast<EDAMAGE_TYPES>(7));
                attribute = strength();
            } else {
                attributeBonus = getEffectValue(static_cast<EEFFECT_TYPE>(16), static_cast<EDAMAGE_TYPES>(7));
                attribute = dexterity();
            }
            bonus = attributeBonus / 100.0f + bonus + static_cast<float>(attribute) / 100.0f;
            if (weapon) {
                if (weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(162)))
                    bonus = getEffectValue(static_cast<EEFFECT_TYPE>(99), static_cast<EDAMAGE_TYPES>(7)) / 100.0f + bonus;
                if (weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(163)))
                    bonus = getEffectValue(static_cast<EEFFECT_TYPE>(102), static_cast<EDAMAGE_TYPES>(7)) / 100.0f + bonus;
                if (weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(164)))
                    bonus = getEffectValue(static_cast<EEFFECT_TYPE>(103), static_cast<EDAMAGE_TYPES>(7)) / 100.0f + bonus;
            }
            if (type > 0 && armed) bonus = static_cast<float>(magic()) / 100.0f + bonus;
            if (m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1)) &&
                m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0)) &&
                !m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1))->ISA(static_cast<UNITTYPES::EUNITTYPES>(21)))
                bonus = getEffectValue(static_cast<EEFFECT_TYPE>(88), static_cast<EDAMAGE_TYPES>(7)) / 100.0f + bonus;
            int increase = static_cast<int>(ceilf(static_cast<float>(inherent) * bonus));
            if (pass == 0) {
                int componentMaximum = increase + inherent;
                if (normalizeSpeed) componentMaximum = static_cast<int>(ceilf(static_cast<float>(componentMaximum) / (attackSpeed * 0.73333335f)));
                if (critical) {
                    float effect = getEffectValue(static_cast<EEFFECT_TYPE>(89), static_cast<EDAMAGE_TYPES>(7));
                    int half = static_cast<int>(static_cast<float>(componentMaximum) * 0.5f);
                    componentMaximum = half + componentMaximum + static_cast<int>(static_cast<float>(half) * (effect / 100.0f));
                }
                maximum = flat + maximum + componentMaximum;
            } else {
                float componentMaximum = static_cast<float>(inherent + flat + increase);
                if (normalizeSpeed) componentMaximum = static_cast<float>(static_cast<int>(ceilf(static_cast<float>(static_cast<int>(componentMaximum)) / (attackSpeed * 0.73333335f))));
                int componentMinimum = static_cast<int>(ceilf(static_cast<float>(static_cast<int>(componentMaximum)) * 0.5f));
                int rolled = UTILITIES::randomIntegerBetweenVolatile(componentMinimum, static_cast<int>(componentMaximum));
                if (critical) {
                    int half = static_cast<int>(static_cast<float>(static_cast<int>(componentMaximum)) * 0.5f);
                    float effect = getEffectValue(static_cast<EEFFECT_TYPE>(89), static_cast<EDAMAGE_TYPES>(7));
                    rolled = half + static_cast<int>(componentMaximum) + static_cast<int>(static_cast<float>(half) * (effect / 100.0f));
                }
                if (combatLog) {
                    level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Elemental Damage Type :  " + gDAMAGE_TYPES[type]);
                    level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Elemental Damage Range " + STRINGS::GetValueAsWString(componentMinimum) + L"-" + STRINGS::GetValueAsWString(static_cast<int>(componentMaximum)));
                    level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Rolled Elemental Damage " + STRINGS::GetValueAsWString(rolled));
                }
                if (rolled > 0) {
                    rolledTotal += rolled;
                    rolled = target->modifyDamage(rolled, type, maximum, armorScale);
                    if (combatLog) level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Elemental Damage after absorption " + STRINGS::GetValueAsWString(rolled));
                }
                damage += rolled;
                damages[damageCount][0] = type;
                damages[damageCount++][1] = rolled;
            }
        }
    }
    float interruption = getEffectValue(static_cast<EEFFECT_TYPE>(56), static_cast<EDAMAGE_TYPES>(7));
    bool interruptTarget;
    if (static_cast<float>(rolledTotal) / static_cast<float>(maximum) > 0.8f ||
        static_cast<float>(target->maxHP()) * 0.5f < static_cast<float>(damage) ||
        static_cast<float>(UTILITIES::randomIntegerBetweenVolatile(1, 100)) < interruption)
        interruptTarget = true;
    else {
        interruptTarget = critical;
        if (!critical) {
            interruptTarget = target->m_activeSkill &&
                (target->m_skillLooping || (target->m_skillTime > 0.0f && !target->m_skillInterrupted)) &&
                target->m_skillCanInterrupt;
        }
    }
    if (interruption < 0.0f && static_cast<float>(UTILITIES::randomIntegerBetweenVolatile(0, 100)) < -interruption)
        interruptTarget = false;
    int interruptRoll = UTILITIES::randomIntegerBetweenVolatile(1, 100);
    float resistance = target->getEffectValue(static_cast<EEFFECT_TYPE>(136), static_cast<EDAMAGE_TYPES>(7));
    if (resistance < static_cast<float>(interruptRoll) && interruptTarget) {
        target->interrupt(true);
        if (combatLog) level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Interrupted Target");
    }
    float force = 0.0f;
    if (critical || (flags & 8)) force = UTILITIES::randomBetweenVolatile(1.0f, 4.0f) * 1.5f;
    else if (UTILITIES::randomBetweenVolatile(0.0f, 1.0f) < 0.7f)
        force = UTILITIES::randomBetweenVolatile(1.0f, 4.0f);
    if (combatLog) level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Totalled Damage " + STRINGS::GetValueAsWString(damage));
    bool absorbed = baseRoll != damage && damage == 1;
    if (absorbed) critical = false;
    else if (!(flags & 4096)) {
        {
            float percent = characterRollPercent(getEffectValue(static_cast<EEFFECT_TYPE>(30), static_cast<EDAMAGE_TYPES>(7)));
            float amount = getEffectValue(static_cast<EEFFECT_TYPE>(49), static_cast<EDAMAGE_TYPES>(7));
            static std::wstring g_HP;
            if (g_HP.empty()) g_HP = CStringTranslate::getSinglton()->getTranslateString(L"HP");
            amount = (percent * static_cast<float>(damage)) / 100.0f + amount;
            if (amount > 0.0f) {
                modifyHP(amount);
                CEGUI::colour color(0.16f, 0.6f, 0.16f, 1.0f);
                characterRollText(level.m_pGameClient->getGameUI(), this,
                    L"+" + STRINGS::GetValueAsWString(static_cast<int>(ceilf(amount))) + L" " + g_HP, 1.2f, color);
            } else if (amount < 0.0f) {
                modifyHP(amount);
                CEGUI::colour color(1.0f, 0.67f, 0.16f, 1.0f);
                characterRollText(level.m_pGameClient->getGameUI(), this,
                    L"-" + STRINGS::GetValueAsWString(static_cast<int>(ceilf(amount))) + L" " + g_HP, 1.2f, color);
            }
        }
        if (m_pMaster) {
            float percent = characterRollPercent(getEffectValue(static_cast<EEFFECT_TYPE>(126), static_cast<EDAMAGE_TYPES>(7)));
            float amount = getEffectValue(static_cast<EEFFECT_TYPE>(125), static_cast<EDAMAGE_TYPES>(7));
            static std::wstring g_HP;
            if (g_HP.empty()) g_HP = CStringTranslate::getSinglton()->getTranslateString(L"HP");
            amount = (percent * static_cast<float>(damage)) / 100.0f + amount;
            if (amount > 0.0f) {
                m_pMaster->modifyHP(amount);
                CEGUI::colour color(0.16f, 0.6f, 0.16f, 1.0f);
                characterRollText(level.m_pGameClient->getGameUI(), m_pMaster,
                    L"+" + STRINGS::GetValueAsWString(static_cast<int>(ceilf(amount))) + L" " + g_HP, 1.2f, color);
            } else if (amount < 0.0f) {
                m_pMaster->modifyHP(amount);
                CEGUI::colour color(1.0f, 0.67f, 0.16f, 1.0f);
                characterRollText(level.m_pGameClient->getGameUI(), m_pMaster,
                    L"-" + STRINGS::GetValueAsWString(static_cast<int>(ceilf(amount))) + L" " + g_HP, 1.2f, color);
            }
        }
        float percent = characterRollPercent(getEffectValue(static_cast<EEFFECT_TYPE>(31), static_cast<EDAMAGE_TYPES>(7)));
        float amount = getEffectValue(static_cast<EEFFECT_TYPE>(50), static_cast<EDAMAGE_TYPES>(7));
        amount = (static_cast<float>(damage) * percent) / 100.0f + amount;
        if (amount != 0.0f) {
            static std::wstring g_Mana;
            if (g_Mana.empty()) g_Mana = CStringTranslate::getSinglton()->getTranslateString(L"Mana");
            modifyMana(amount);
            CEGUI::colour color(0.46f, 0.46f, 1.0f, 1.0f);
            characterRollText(level.m_pGameClient->getGameUI(), this,
                L"+" + STRINGS::GetValueAsWString(static_cast<int>(ceilf(amount))) + L" " + g_Mana, 1.5f, color);
            target->modifyMana(-amount);
        }
    }
    bool wasBlocked = target->blocked();
    if (wasBlocked) {
        static std::wstring g_Blocked;
        if (g_Blocked.empty()) g_Blocked = CStringTranslate::getSinglton()->getTranslateString(L"Blocked");
        CEGUI::colour color(1.0f, 0.67f, 0.16f, 1.0f);
        characterRollText(level.m_pGameClient->getGameUI(), target, g_Blocked + L"!", 1.2f, color);
        if (m_levelSound) m_levelSound->playSample(7, m_pSceneNode, 0.0f, 0.0f, false);
        damage = 0;
        if (combatLog) level.m_pGameClient->getGameUI()->m_console->addTextNoHistory(L" Blocked!");
    }
    if (absorbed && m_levelSound) m_levelSound->playSample(8, m_pSceneNode, 0.0f, 0.0f, false);
    float applied = static_cast<float>(damage);
    float targetHP = static_cast<float>(target->HP());
    if (targetHP < applied) applied = static_cast<float>(target->HP());
    target->HP();
    target->applyDamageEffects(this, applied, damages, damageCount, critical);
    float knockback = getEffectValue(static_cast<EEFFECT_TYPE>(12), static_cast<EDAMAGE_TYPES>(7));
    if (weapon) {
        knockback += weapon->getEffectValue(static_cast<EEFFECT_ACTIVATION>(1), static_cast<EEFFECT_TYPE>(12), 0.0f, static_cast<EDAMAGE_TYPES>(7));
        for (unsigned int i = 0; i < weapon->m_SocketedEquipment.size(); ++i)
            knockback += weapon->m_SocketedEquipment[i]->getEffectValue(static_cast<EEFFECT_ACTIVATION>(1), static_cast<EEFFECT_TYPE>(12), 0.0f, static_cast<EDAMAGE_TYPES>(7));
    }
    if (knockback > 0.0f) {
        CEffect* effect = new CEffect(static_cast<EEFFECT_TYPE>(43), false, static_cast<EEFFECT_ACTIVATION>(1),
            static_cast<float>(static_cast<int>(knockback * 0.5f + 2.0f)), knockback * 0.1f + 2.0f, 0.0f, false);
        effect->setName(L"KNOCKBACK");
        Ogre::Vector3 sourcePosition = getPosition(true);
        Ogre::Vector3 targetPosition = target->getPosition(true);
        Ogre::Vector3 direction(targetPosition.x - sourcePosition.x, 0.0f, targetPosition.z - sourcePosition.z);
        direction.normalise();
        effect->m_direction = direction;
        target->addNewEffect(effect);
    }
    float degrade = getEffectValue(static_cast<EEFFECT_TYPE>(54), static_cast<EDAMAGE_TYPES>(7));
    if (degrade > 0.0f) {
        CEffect* effect = new CEffect(static_cast<EEFFECT_TYPE>(66), false, static_cast<EEFFECT_ACTIVATION>(1),
            static_cast<float>(static_cast<int>(degrade)), 10.0f, 0.0f, false);
        effect->setName(L"DegradeArmor");
        target->addNewEffect(effect);
    }
    if (m_pEffectManager) {
        for (int i = 0; i != 145; ++i) {
            m_pEffectManager->transferEffects(target, static_cast<EEFFECT_ACTIVATION>(2), static_cast<EEFFECT_TYPE>(i));
            if (m_pInventory) {
                if (m_pInventory->m_pEffectManager)
                    m_pInventory->m_pEffectManager->transferEffects(target, static_cast<EEFFECT_ACTIVATION>(2), static_cast<EEFFECT_TYPE>(i));
                m_pInventory->transferEffects(target, static_cast<EEFFECT_ACTIVATION>(2), static_cast<EEFFECT_TYPE>(i));
            }
        }
    }
    EAIState oldState = target->m_eAIState;
    Ogre::Vector3 sourcePosition = getPosition(true);
    Ogre::Vector3 targetPosition = target->getPosition(true);
    Ogre::Vector3 direction(targetPosition.x - sourcePosition.x, 0.0f, targetPosition.z - sourcePosition.z);
    direction.normalise();
    float rotation = UTILITIES::randomBetweenVolatile(-10.0f, 10.0f);
    MATH::rotateY(&direction, static_cast<float>(static_cast<double>(rotation) * 0.017453292519943295));
    sourcePosition = getPosition(true);
    target->applyDamage(level, sourcePosition, static_cast<float>(damage), direction, force, this,
        absorbed, true, true, critical, flags);
    if (!(flags & 2048) || critical || wasBlocked) {
        float radius = target->m_fBaseUnitValue194;
        targetPosition = target->getPosition(true);
        sourcePosition = getPosition(true);
        playStrikeParticle(sourcePosition, targetPosition, radius, critical, wasBlocked);
    }
    if (critical && oldState != static_cast<EAIState>(5) && oldState != static_cast<EAIState>(6) &&
        (target->m_eAIState == static_cast<EAIState>(5) || target->m_eAIState == static_cast<EAIState>(6)) &&
        ISA(static_cast<UNITTYPES::EUNITTYPES>(28))) {
        CGameSpeed::getSingleton();
        CGameSpeed::addSpeedModifier(static_cast<EGAMESPEED_TYPE>(0), 0.5f, 1.0f);
    }
    return true;
}

#include "Graph.h"
#include "GraphManager.h"

static CGraph* characterChampionGraph(int difficulty, const wchar_t* base)
{
    std::wstring name(base);
    switch (difficulty)
    {
    case 0: name += L"_EASY"; break;
    case 1: break;
    case 2: name += L"_HARD"; break;
    case 3: name += L"_VERYHARD"; break;
    default: return NULL;
    }
    return CGraphManager::getSingleton()->getGraph(name);
}

void CCharacter::makeChampion(const std::wstring& name, int, std::wstring theme)
{
    if (m_champion)
        return;
    if (!m_pDataGroup->GetDataValue(L"UNIQUENAME",false))
        m_characterDisplayName = name;
    m_champion = true;
    m_bravery = 1.0f;
    setScale(m_vScale.z + 0.2f);

    float first = m_pDataGroup->GetDataValue(L"MINHP",0.0f);
    float second = m_pDataGroup->GetDataValue(L"MAXHP",0.0f);
    float maximum = first > second ? first : second;
    first = m_pDataGroup->GetDataValue(L"MINHP",0.0f);
    second = m_pDataGroup->GetDataValue(L"MAXHP",0.0f);
    float minimum = first < second ? first : second;
    if (maximum != 0.0f)
    {
        std::wstring graphName = STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"HEALTH_GRAPH",EMPTY_WSTRING));
        CGraph* graph;
        if (graphName == EMPTY_WSTRING)
            graph = characterChampionGraph(m_pResourceManager->getGameClient()->m_startDifficulty,L"HEALTH_CHAMPIONMONSTER_BYLEVEL");
        else
            graph = CGraphManager::getSingleton()->getGraph(graphName);
        float value = graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)),0);
        minimum = (minimum / 100.0f) * value;
        maximum = value * (maximum / 100.0f);
    }
    m_experienceReward = m_pDataGroup->GetDataValue(L"XP",0);
    if (m_experienceReward)
    {
        CGraph* graph = characterChampionGraph(m_pResourceManager->getGameClient()->m_startDifficulty,L"EXPERIENCE_CHAMPIONMONSTER");
        float value = graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)),0);
        // Native squares the graph result; XP only controls entry to this branch.
        m_experienceReward = static_cast<int>((value / 100.0f) * value);
    }
    m_fameReward = 100;
    CGraph* fame = characterChampionGraph(m_pResourceManager->getGameClient()->m_startDifficulty,L"FAME_CHAMPIONMONSTER");
    float fameValue = fame->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)),0);
    m_fameReward = static_cast<int>((fameValue / 100.0f) * fameValue);
    int hp = static_cast<int>(UTILITIES::randomBetweenVolatile(minimum,maximum));
    m_maxHPBase = hp;
    m_fHPFloat = static_cast<float>(hp);
    m_naturalArmor = m_pDataGroup->GetDataValue(L"ARMOR",0);
    if (m_naturalArmor)
    {
        std::wstring graphName = STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"ARMOR_GRAPH",EMPTY_WSTRING));
        CGraph* graph;
        if (graphName == EMPTY_WSTRING)
            graph = characterChampionGraph(m_pResourceManager->getGameClient()->m_startDifficulty,L"ARMOR_CHAMPIONMONSTER_BYLEVEL");
        else
            graph = CGraphManager::getSingleton()->getGraph(graphName);
        float value = graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)),0);
        m_naturalArmor = static_cast<int>(ceilf(value * (static_cast<float>(m_naturalArmor) / 100.0f)));
    }
    for (unsigned int i=0;i<7;++i)
    {
        int armor = m_pDataGroup->GetDataValue(L"ARMOR_" + STRINGS::StringUpper(gDAMAGE_TYPES[i]),-1);
        if (static_cast<float>(armor) != -1.0f)
            m_damageDefense[i] = static_cast<int>(ceilf((static_cast<float>(armor) / 100.0f) * static_cast<float>(m_naturalArmor)));
    }
    if (m_damageDefense[0])
    {
        m_naturalArmor = m_damageDefense[0];
        m_damageDefense[0] = 0;
    }
    m_pDataGroup->GetDataValue(L"MINDAMAGE",0);
    if (m_pDataGroup->GetDataValue(L"MAXDAMAGE",0))
    {
        std::wstring graphName = STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"DAMAGE_GRAPH",EMPTY_WSTRING));
        CGraph* graph;
        if (graphName == EMPTY_WSTRING)
            graph = characterChampionGraph(m_pResourceManager->getGameClient()->m_startDifficulty,L"DAMAGE_CHAMPIONMONSTER");
        else
            graph = CGraphManager::getSingleton()->getGraph(graphName);
        // The native damage graph is evaluated without storing its result.
        graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)),0);
    }
    if (!theme.empty())
        addUnitTheme(theme);
}

#include "Graph.h"
#include "GraphManager.h"

static CGraph* characterLevelGraph(int difficulty, const wchar_t* base, CGraph* fallback = NULL)
{
    std::wstring name(base);
    switch (difficulty)
    {
    case 0: name += L"_EASY"; break;
    case 1: break;
    case 2: name += L"_HARD"; break;
    case 3: name += L"_VERYHARD"; break;
    default: return fallback;
    }
    return CGraphManager::getSingleton()->getGraph(name);
}

void CCharacter::setLevel(unsigned int level, bool apply)
{
    if (m_iUnitLevel == level)
        return;
    m_iUnitLevel = level;
    if (ISA(UNITTYPES::PLAYER) && !apply)
        return;

    float first = m_pDataGroup->GetDataValue(L"MINHP",1.0f);
    float second = m_pDataGroup->GetDataValue(L"MAXHP",1.0f);
    float maximum = first > second ? first : second;
    first = m_pDataGroup->GetDataValue(L"MINHP",1.0f);
    second = m_pDataGroup->GetDataValue(L"MAXHP",1.0f);
    float minimum = first < second ? first : second;
    if (maximum <= 0.1f)
        minimum = maximum = 1.0f;
    if (maximum != 0.0f)
    {
        std::wstring name = STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"HEALTH_GRAPH",EMPTY_WSTRING));
        CGraph* graph = name == EMPTY_WSTRING
            ? characterLevelGraph(m_pResourceManager->getGameClient()->m_startDifficulty,L"HEALTH_MONSTER_BYLEVEL")
            : CGraphManager::getSingleton()->getGraph(name);
        float value = graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)),0);
        minimum = (minimum / 100.0f) * value;
        maximum = value * (maximum / 100.0f);
    }
    if (m_experienceReward)
    {
        CGraph* graph = characterLevelGraph(m_pResourceManager->getGameClient()->m_startDifficulty,L"EXPERIENCE_MONSTER");
        float value = graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)),0);
        m_experienceReward = static_cast<int>((value / 100.0f) * value);
    }
    m_maxHPBase = static_cast<int>(UTILITIES::randomBetweenVolatile(minimum,maximum));
    float percentage = m_pDataGroup->GetDataValue(L"SET_HP_PCT",1.0f);
    float hpMaximum = static_cast<float>(m_maxHPBase);
    float scaledHP = percentage * hpMaximum;
    float hp = scaledHP < hpMaximum ? scaledHP : hpMaximum;
    hp = hp > 1.0f ? hp : 1.0f;
    m_fHPFloat = static_cast<float>(static_cast<int>(hp));
    calculateMaxMana();
    m_fManaFloat = static_cast<float>(m_maxManaBase);

    m_naturalArmor = m_pDataGroup->GetDataValue(L"ARMOR",0);
    if (m_naturalArmor)
    {
        std::wstring name = STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"ARMOR_GRAPH",EMPTY_WSTRING));
        CGraph* graph = name == EMPTY_WSTRING
            ? characterLevelGraph(m_pResourceManager->getGameClient()->m_startDifficulty,L"ARMOR_MONSTER_BYLEVEL")
            : CGraphManager::getSingleton()->getGraph(name);
        float value = graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)),0);
        m_naturalArmor = static_cast<int>(ceilf(value * (static_cast<float>(m_naturalArmor) / 100.0f)));
    }
    for (unsigned int i=0;i<7;++i)
    {
        int armor = m_pDataGroup->GetDataValue(L"ARMOR_" + STRINGS::StringUpper(gDAMAGE_TYPES[i]),-1);
        if (static_cast<float>(armor) != -1.0f)
            m_damageDefense[i] = static_cast<int>(ceilf((static_cast<float>(armor) / 100.0f) * static_cast<float>(m_naturalArmor)));
    }
    if (m_damageDefense[0])
    {
        m_naturalArmor = m_damageDefense[0];
        m_damageDefense[0] = 0;
    }

    int minimumPercent = m_pDataGroup->GetDataValue(L"MINDAMAGE",0);
    int maximumPercent = m_pDataGroup->GetDataValue(L"MAXDAMAGE",0);
    unsigned int minimumDamage = 0;
    unsigned int maximumDamage = 0;
    int secondaryMinimum = 0;
    int secondaryMaximum = 0;
    if (maximumPercent)
    {
        std::wstring name = STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"DAMAGE_GRAPH",EMPTY_WSTRING));
        CGraph* graph = name == EMPTY_WSTRING
            ? characterLevelGraph(m_pResourceManager->getGameClient()->m_startDifficulty,L"DAMAGE_MONSTER")
            : CGraphManager::getSingleton()->getGraph(name);
        if (ISA(UNITTYPES::PLAYER))
            graph = CGraphManager::getSingleton()->getGraph(L"DAMAGE_MONSTER");
        float value = graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)),0);
        m_value6D0 = static_cast<int>(floorf(value));
        minimumDamage = static_cast<int>(ceilf(value * (static_cast<float>(minimumPercent) / 100.0f)));
        maximumDamage = static_cast<int>(ceilf(value * (static_cast<float>(maximumPercent) / 100.0f)));
        // An unknown difficulty retains the previous damage graph in the native branch.
        graph = characterLevelGraph(m_pResourceManager->getGameClient()->m_startDifficulty,L"HEALTH_MONSTER_BYLEVEL",graph);
        value = graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)),0);
        m_value6D0 = static_cast<unsigned int>(static_cast<long>(value));
        secondaryMinimum = static_cast<int>(static_cast<float>(static_cast<int>(ceilf((static_cast<float>(minimumPercent) / 100.0f) * value))) * 0.5f);
        secondaryMaximum = static_cast<int>(static_cast<float>(static_cast<int>(ceilf((static_cast<float>(maximumPercent) / 100.0f) * value))) * 0.5f);
    }
    m_attackFlag1F5 = m_pDataGroup->GetDataValue(L"NO_UNARMED_ATTACKS",false);
    bool create = m_attacks.empty();
    CAttackDescription* attack;
    if (create)
    {
        float strikeRange;
        float attackRange;
        std::memcpy(&strikeRange,m_Padding4D0+4,sizeof(strikeRange));
        std::memcpy(&attackRange,m_Padding4D0+8,sizeof(attackRange));
        attack = new CAttackDescription("ATTACK",false,attackRange,strikeRange,minimumDamage,maximumDamage,0,1.0f);
        // These native fields are signed damage values, not floating point scalars.
        std::memcpy(attack->m_AttackData5C,&secondaryMinimum,sizeof(secondaryMinimum));
        std::memcpy(attack->m_AttackData5C+4,&secondaryMaximum,sizeof(secondaryMaximum));
    }
    else
    {
        attack = m_attacks[0];
        attack->m_DamageMinimums[0] = minimumDamage;
        attack->m_DamageMaximums[0] = maximumDamage;
    }
    for (unsigned int i=0;i<7;++i)
    {
        int damage = m_pDataGroup->GetDataValue(L"DAMAGE_" + STRINGS::StringUpper(gDAMAGE_TYPES[i]),-1);
        if (static_cast<float>(damage) != -1.0f)
            attack->m_DamageMaximums[i] = static_cast<int>(ceilf((static_cast<float>(damage) / 100.0f) * static_cast<float>(static_cast<int>(maximumDamage))));
    }
    if (create)
        m_attacks.push_back(attack);
}

#include "Affix.h"

void CCharacter::updateEffects(float elapsed, CLevel&)
{
    if (!m_pEffectManager)
        return;
    m_Padding52D[0] = 0;
    m_impulse[0] = m_impulse[1] = m_impulse[2] = 0.0f;
    for (unsigned int group=0;group<2;++group)
    {
        CEffectManager* manager = m_pEffectManager;
        TArrayList<CEffect*>& effects = manager->getActiveEffects(group);
        for (unsigned int i=0;i<effects.size();++i)
        {
            CEffect* effect = effects[i];
            if (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f)
                effect->m_fRemainingDuration = elapsed + effect->m_fRemainingDuration;
            effect = effects[i];
            bool expired = (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f
                && effect->m_fValue24 <= effect->m_fRemainingDuration) || effect->m_bDead;
            if (expired && effect->m_eType == static_cast<EEFFECT_TYPE>(47))
                die(NULL,NULL,0.0f,false);
            effect = effects[i];
            expired = (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f
                && effect->m_fValue24 <= effect->m_fRemainingDuration) || effect->m_bDead;
            if (expired && (effect->m_eType == static_cast<EEFFECT_TYPE>(74) || effect->m_eType == static_cast<EEFFECT_TYPE>(76)
                || effect->m_eType == static_cast<EEFFECT_TYPE>(81) || effect->m_eType == static_cast<EEFFECT_TYPE>(105)
                || effect->m_eType == static_cast<EEFFECT_TYPE>(75)) && m_pSkillManager)
            {
                std::wstring name = EMPTY_WSTRING;
                name = effects[i]->m_sName;
                effect = effects[i];
                if (m_pSkillManager)
                {
                    int level = static_cast<int>(effect->m_iLevel);
                    if (level < 1)
                        level = 1;
                    CSkill* skill = m_pSkillManager->getSkill(name,level);
                    if (skill)
                    {
                        if (m_activeSkillGuid == skill->m_Guid)
                            m_activeSkillGuid = -1;
                        if (m_leftSkillGuid == skill->m_Guid)
                            m_leftSkillGuid = -1;
                        if (m_leftMouseSkillGuid == skill->m_Guid)
                            m_leftMouseSkillGuid = -1;
                        if (m_activeSkill == skill)
                            m_activeSkill = NULL;
                        if (m_previousSkill == skill)
                            m_previousSkill = NULL;
                        m_pSkillManager->deleteSpecificSkill(skill);
                    }
                }
                continue;
            }

            effect = effects[i];
            expired = (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f
                && effect->m_fValue24 <= effect->m_fRemainingDuration) || effect->m_bDead;
            if (expired && effect->m_eType == static_cast<EEFFECT_TYPE>(61) && effect->m_Owner.getObject())
            {
                CCharacter* attacker = dynamic_cast<CCharacter*>(effect->m_Owner.getObject());
                if (attacker)
                {
                    CCharacter* previousTarget = attacker->m_targetCharacter.getObject();
                    attacker->setTarget(this);
                    float previousValue = attacker->m_CharacterValue720;
                    if (effects[i]->m_reflectionMinimum > 0.0f)
                        attacker->m_CharacterValue720 = effects[i]->m_reflectionMinimum;
                    CEquipment* weapon;
                    if (getWeaponInLeftHand())
                        weapon = getWeaponInLeftHand();
                    else
                        weapon = getWeaponInRightHand();
                    attacker->performAttack(weapon,35,1.0f,1.0f,static_cast<EDAMAGE_TYPES>(7));
                    attacker->setTarget(previousTarget);
                    attacker->m_CharacterValue720 = previousValue;
                }
            }
            effect = effects[i];
            if (effect->m_eType == static_cast<EEFFECT_TYPE>(80))
            {
                expired = (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f
                    && effect->m_fValue24 <= effect->m_fRemainingDuration) || effect->m_bDead;
                bool remove = expired || m_eAIState == AISTATE_DYING || m_eAIState == AISTATE_DEAD;
                if (!remove)
                {
                    if (!hasUnitTheme(L"TURNED"))
                        addUnitTheme(L"TURNED");
                    else
                        remove = true;
                }
                if (remove)
                {
                    effect = effects[i];
                    expired = (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f
                        && effect->m_fValue24 <= effect->m_fRemainingDuration) || effect->m_bDead;
                    if (expired)
                        removeUnitTheme(L"TURNED");
                }
            }
            effect = effects[i];
            if (effect->m_eType == static_cast<EEFFECT_TYPE>(64))
            {
                expired = (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f
                    && effect->m_fValue24 <= effect->m_fRemainingDuration) || effect->m_bDead;
                if (expired || hasUnitTheme(L"STUNNED"))
                {
                    effect = effects[i];
                    expired = (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f
                        && effect->m_fValue24 <= effect->m_fRemainingDuration) || effect->m_bDead;
                    if (expired)
                    {
                        m_moveSpeed = 1.0f;
                        removeUnitTheme(L"STUNNED");
                        if (m_eAIState == static_cast<EAIState>(40))
                            setAIState(static_cast<EAIState>(0));
                    }
                }
                else if (m_eAIState != static_cast<EAIState>(12) && m_eAIState != AISTATE_DYING
                    && m_eAIState != AISTATE_DEAD && m_eAIState != static_cast<EAIState>(41)
                    && m_eAIState != static_cast<EAIState>(16))
                {
                    if (m_pUnitModel && m_pUnitModel->animationExists("STUNNED"))
                        blendAnimation("STUNNED",true,0.2f,1.0f,-1.0f);
                    else
                        blendAnimation("IDLE",true,0.2f,1.0f,-1.0f);
                    addUnitTheme(L"STUNNED");
                    m_moveSpeed = 0.0f;
                    m_movement = Ogre::Vector3(0.0f,0.0f,0.0f);
                    setAIState(static_cast<EAIState>(40));
                    if (m_isPathing)
                        m_pathGraceTime = 10.0f;
                    m_isPathing = false;
                    m_pathDestination = m_vPosition;
                }
            }
            static const unsigned int elementalTypes[4] = {107,106,109,108};
            static const wchar_t* const elementalNames[4] = {
                L"DAMAGEEFFECTONFIRE",L"DAMAGEEFFECTFROZEN",L"DAMAGEEFFECTELECTRICITY",L"DAMAGEEFFECTPOISONED"
            };
            static const wchar_t* const playerNames[4] = {
                L"DAMAGEEFFECTONFIREPLAYER",L"DAMAGEEFFECTFROZENPLAYER",L"DAMAGEEFFECTELECTRICITYPLAYER",L"DAMAGEEFFECTPOISONEDPLAYER"
            };
            for (unsigned int elemental=0;elemental<4;++elemental)
            {
                effect = effects[i];
                bool active = (effect->m_fValue24 == -900.0f || effect->m_fValue24 == -1000.0f
                    || effect->m_fRemainingDuration < effect->m_fValue24) && !effect->m_bDead;
                if (effect->m_eType == static_cast<EEFFECT_TYPE>(elementalTypes[elemental]) && active
                    && m_eAIState != static_cast<EAIState>(12) && m_eAIState != AISTATE_DYING
                    && m_eAIState != AISTATE_DEAD && m_eAIState != static_cast<EAIState>(41)
                    && m_eAIState != static_cast<EAIState>(16))
                {
                    if (effects[i]->m_fValue24 != -900.0f && effects[i]->m_fValue24 != -1000.0f)
                    {
                        CAffix* affix = NULL;
                        if (m_pEffectManager)
                        {
                            const wchar_t* name = ISA(UNITTYPES::PLAYER) ? playerNames[elemental] : elementalNames[elemental];
                            affix = m_pEffectManager->getAffix(name);
                        }
                        if (affix)
                            affix->m_fDuration = effects[i]->m_fValue24;
                        else
                        {
                            effect = effects[i];
                            float duration = effect->m_fValue24;
                            CBaseUnit* owner = effect->m_Owner.getObject();
                            unsigned int level = effect->m_iLevel;
                            const wchar_t* name = ISA(UNITTYPES::PLAYER) ? playerNames[elemental] : elementalNames[elemental];
                            addAffix(name,level,owner,duration);
                        }
                    }
                    effect = effects[i];
                    if (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f)
                        effect->m_fRemainingDuration = effect->m_fValue24;
                    effect->m_bDead = true;
                }
            }
            if (effects[i]->m_eType == static_cast<EEFFECT_TYPE>(59))
            {
                float scale = effects[i]->value(static_cast<EEFFECT_VALUES>(0));
                float maximum = effects[i]->value(static_cast<EEFFECT_VALUES>(1));
                effect = effects[i];
                expired = (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f
                    && effect->m_fValue24 <= effect->m_fRemainingDuration) || effect->m_bDead;
                if (expired)
                    scale = 1.0f;
                else
                {
                    if (effects[i]->m_fValue24 != -1000.0f)
                    {
                        effect = effects[i];
                        scale = (maximum-scale) * (effect->m_fRemainingDuration/effect->m_fValue24);
                    }
                    if (scale == 0.0f)
                        scale = 1.0f;
                }
                static_cast<CGenericModel*>(getUnitModel())->setScale(scale);
            }
            if (effects[i]->fxShouldPlay())
            {
                Ogre::Vector3 offset(Ogre::Vector3::UNIT_Y.x*0.1f,Ogre::Vector3::UNIT_Y.y*0.1f,Ogre::Vector3::UNIT_Y.z*0.1f);
                Ogre::Vector3 position = getPosition(true);
                position.y = offset.y + position.y;
                position.x = offset.x + position.x;
                position.z = offset.z + position.z;
                effects[i]->playFX(m_pResourceManager,position);
            }
            effect = effects[i];
            if (effect->m_eType == static_cast<EEFFECT_TYPE>(7) || effect->m_eType == static_cast<EEFFECT_TYPE>(52)
                || effect->m_eType == static_cast<EEFFECT_TYPE>(124))
            {
                if (!(effects[i]->value(static_cast<EEFFECT_VALUES>(0)) >= 0.0f) && effects[i]->m_fValue24 != -900.0f)
                    m_Padding52D[0] = 1;
            }
            effect = effects[i];
            if (effect->m_eType == static_cast<EEFFECT_TYPE>(43) && effect->m_activation == static_cast<EEFFECT_ACTIVATION>(1))
            {
                float resistance = getEffectValue(static_cast<EEFFECT_TYPE>(53),static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
                resistance = resistance < 1.0f ? resistance : 1.0f;
                resistance = resistance > 0.0f ? resistance : 0.0f;
                effect = effects[i];
                float value = effect->value(static_cast<EEFFECT_VALUES>(0)) * (1.0f-resistance);
                m_impulse[2] = effect->m_direction.z * value + m_impulse[2];
                m_impulse[1] = effect->m_direction.y * value + m_impulse[1];
                m_impulse[0] = value * effect->m_direction.x + m_impulse[0];
                value = effects[i]->value(static_cast<EEFFECT_VALUES>(0));
                float decay = powf(0.001f,elapsed);
                effects[i]->m_fValueC4 = decay * value;
                effects[i]->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
            }
            if (effects[i]->m_fValue24 == -900.0f)
                applyInstantEffect(effects[i]);
        }
    }
    m_impulse[1] = 0.0f;
    float magnitude = sqrtf(m_impulse[0]*m_impulse[0]+0.0f+m_impulse[2]*m_impulse[2]);
    float maximum;
    if (!ISA(UNITTYPES::PLAYER) || magnitude <= 10.0f)
    {
        if (magnitude <= 30.0f)
            return;
        maximum = 30.0f;
    }
    else
        maximum = 10.0f;
    magnitude = sqrtf(m_impulse[0]*m_impulse[0]+m_impulse[1]*m_impulse[1]+m_impulse[2]*m_impulse[2]);
    if (magnitude > 1.0e-8f)
    {
        float reciprocal = 1.0f / magnitude;
        m_impulse[0] *= reciprocal;
        m_impulse[1] *= reciprocal;
        m_impulse[2] *= reciprocal;
    }
    m_impulse[0] *= maximum;
    m_impulse[1] *= maximum;
    m_impulse[2] *= maximum;
}

#include <OgreNode.h>

void CCharacter::performAttack(CEquipment* equipment, unsigned int flags, float damage, float effects, EDAMAGE_TYPES type)
{
    m_attackFlag37E = !m_attackFlag37E;
    CEquipment* weapon = equipment;
    CAttackDescription* description = NULL;
    if (equipment)
    {
        if (equipment == getWeaponInLeftHand())
            description = equipment->m_pAttackDescriptionOverride;
        else if (equipment == getWeaponInRightHand())
            description = equipment->m_pAttackDescription;
        else
        {
            description = equipment->m_pAttackDescription;
            if (!description)
                description = equipment->m_pAttackDescriptionOverride;
        }
    }
    else
        weapon = static_cast<CEquipment*>(m_attackItem);
    if (!description)
    {
        description = m_attack;
        if (!description)
        {
            selectAttack(static_cast<EATTACK_RANGE_TYPE>(0));
            description = m_attack;
            if (!description)
                return;
        }
    }
    CItem* item = NULL;
    if (m_targetItem.getObject())
    {
        if (!m_targetItem.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(30)))
            setTargetItem(NULL);
        item = m_targetItem.getObject();
    }
    CCharacter* target = m_targetCharacter.getObject();
    if (target && !(flags & 64))
    {
        if (!isEnemy(target))
            return;
        item = NULL;
    }
    if (!(flags & 16))
    {
        executeProcs(static_cast<EEFFECT_TYPE>(74),target ? static_cast<CBaseUnit*>(target) : static_cast<CBaseUnit*>(item));
        if (weapon)
        {
            if (doWeaponSkill(weapon))
                return;
            if (weapon->fireMissiles(this,target))
                return;
        }
    }
    float extraRange = 0.0f;
    float angle = 60.0f;
    if (weapon && weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(35)))
    {
        extraRange = getEffectValue(static_cast<EEFFECT_TYPE>(78),static_cast<EDAMAGE_TYPES>(7));
        angle = 10.0f;
    }
    if ((!item && !target) || !inStrikeRange(target,item,weapon))
    {
        Ogre::Matrix4 view = m_mOrientation;
        view[0][3] = m_vPosition.x;
        view[1][3] = m_vPosition.y;
        view[2][3] = m_vPosition.z;
        float radius = m_attackRadius;
        float scale = m_vScale.z;
        float strike = description->m_fStrikeRange;
        float rangeScale = m_attackRangeScale;
        EAlignment alignment = getTargetAlignment();
        CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
        CCharacter* found = level->findCharacterWithinView(view,alignment,0.0f,angle,
            (scale*radius+0.2f+(strike+extraRange))*rangeScale+1.0f,true,NULL,NULL);
        if (found)
            target = found;
        else if (!target)
        {
            level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            CItem* foundItem = level->findItemWithinView(view,angle,
                (m_vScale.z*m_attackRadius+0.2f+description->m_fStrikeRange)*m_attackRangeScale+1.0f);
            if (foundItem)
                item = foundItem;
        }
    }

    bool blocked = false;
    if (!(flags & 4))
    {
        if (!weapon || !weapon->ISA(static_cast<UNITTYPES::EUNITTYPES>(35)))
        {
            Ogre::Vector3 from = getPosition(true);
            from.y += 5.0f;
            Ogre::Vector3 to = from;
            if (item)
                to = item->getPosition(true);
            else if (target)
                to = target->getPosition(true);
            to.y = from.y;
            Ogre::Vector3 firstHit,secondHit,extra;
            unsigned int collisionType;
            CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            if (level->rayCollision(from,to,firstHit,secondHit,collisionType,extra,false))
            {
                const Ogre::Vector3& forward = getForward();
                from.y -= forward.y * 1.25f;
                from.z -= forward.z * 1.25f;
                from.x -= forward.x * 1.25f;
                const Ogre::Vector3& firstRight = getRight();
                from.z = firstRight.z * 0.75f + from.z;
                from.y = firstRight.y * 0.75f + from.y;
                from.x = firstRight.x * 0.75f + from.x;
                const Ogre::Vector3& secondRight = getRight();
                to.z = secondRight.z * 0.75f + to.z;
                to.y = secondRight.y * 0.75f + to.y;
                to.x = secondRight.x * 0.75f + to.x;
                level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
                if (level->rayCollision(from,to,firstHit,secondHit,collisionType,extra,false))
                {
                    const Ogre::Vector3& thirdRight = getRight();
                    from.y -= thirdRight.y * 1.25f;
                    from.x -= thirdRight.x * 1.25f;
                    from.z -= thirdRight.z * 1.25f;
                    const Ogre::Vector3& fourthRight = getRight();
                    to.y -= fourthRight.y * 1.25f;
                    to.x -= fourthRight.x * 1.25f;
                    to.z -= fourthRight.z * 1.25f;
                    level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
                    blocked = level->rayCollision(from,to,firstHit,secondHit,collisionType,extra,false);
                }
            }
        }
        else
        {
            bool trail = weapon->ISA(UNITTYPES::BOW) || weapon->ISA(UNITTYPES::CROSSBOW)
                || weapon->ISA(UNITTYPES::RIFLE) || weapon->ISA(UNITTYPES::PISTOL);
            if (trail)
            {
                if (!m_weaponTrails[2])
                {
                    Ogre::SceneManager* scene = m_pResourceManager ? m_pResourceManager->getSceneManager() : NULL;
                    m_weaponTrails[2] = new CWeaponTrail(scene,STRINGS::uniqueName("trail_"),2,0.4f);
                    m_weaponTrails[2]->setMaterialName("ArrowTrail");
                }
                m_weaponTrails[2]->setActive(true);
            }
            CGenericModel* model = static_cast<CGenericModel*>(weapon->getUnitModel());
            Ogre::Vector3 from = model->getEntity()->getParentNode()->_getDerivedPosition();
            if (flags & 32)
            {
                float height = from.y;
                from = getPosition(false);
                from.y = height;
            }
            Ogre::Vector3 to = from;
            float aimHeight;
            if (item)
            {
                to = item->getPosition(true);
                float height = from.y;
                Ogre::Vector3 targetPosition = item->getPosition(true);
                float targetFloor = targetPosition.y - item->m_fBaseUnitValue194;
                Ogre::Vector3 position = getPosition(true);
                aimHeight = targetFloor - (position.y-m_fBaseUnitValue194) + height;
            }
            else if (target)
            {
                to = target->getPosition(true);
                float height = from.y;
                Ogre::Vector3 targetPosition = target->getPosition(true);
                float targetFloor = targetPosition.y - target->m_fBaseUnitValue194;
                Ogre::Vector3 position = getPosition(true);
                aimHeight = targetFloor - (position.y-m_fBaseUnitValue194) + height;
            }
            else
            {
                extraRange = m_attackRangeScale * description->m_fStrikeRange + extraRange;
                aimHeight = m_vForward.y * extraRange + from.y;
                to.z = m_vForward.z * extraRange + from.z;
                to.y = 0.0f;
                to.x = extraRange * m_vForward.x + from.x;
            }
            // Native bounds the elevation using absolute target X/Z and source Y.
            float elevationLimit = sqrtf(to.x*to.x+from.y*from.y+to.z*to.z) / 5.0f;
            float elevation = aimHeight - from.y;
            elevation = elevation < elevationLimit ? elevation : elevationLimit;
            float negativeLimit = -elevationLimit;
            elevation = elevation > negativeLimit ? elevation : negativeLimit;
            to.y = elevation + from.y;
            Ogre::Vector3 end(to.x+0.0f,to.y+0.8f,to.z+0.0f);
            Ogre::Vector3 start(from.x+0.0f,from.y+0.8f,from.z+0.0f);
            Ogre::Vector3 hit,normal,extra;
            unsigned int collisionType;
            CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            blocked = level->rayCollision(start,end,hit,normal,collisionType,extra,false);
            if (blocked)
            {
                to.x = hit.x;
                to.y = from.y;
                to.z = hit.z;
            }
            if (trail)
            {
                Ogre::Vector3 side(to.x-from.x,0.0f,to.z-from.z);
                side.normalise();
                side = side.crossProduct(Ogre::Vector3::UNIT_Y);
                m_weaponTrails[2]->update(0.0f,&from,&side,false,NULL);
                m_weaponTrails[2]->update(0.0f,&to,&side,false,NULL);
                m_weaponTrails[2]->m_fading = true;
                m_weaponTrails[2]->setMaterialName(flags & 32 ? "ArrowTrailReflect" : "ArrowTrail");
            }
        }
    }
    if (!(flags & 1) && !inStrikeRange(target,item,NULL))
        return;
    if (!(flags & 2) && !facingTarget(target,item))
        return;
    bool hit = false;
    if (item)
    {
        if (!item->m_bItemFlag1F0)
        {
            setTargetItem(NULL);
            return;
        }
        item->interact(this);
        incrementJournalStatistic(static_cast<EJournalStatistic>(11),1);
        Ogre::Vector3 targetPosition = item->getPosition(true);
        Ogre::Vector3 position = getPosition(true);
        playStrikeParticle(position,targetPosition,0.6f,false,false);
        hit = !blocked;
    }
    else if (target && !blocked)
    {
        CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
        hit = rollAttack(*level,target,equipment,flags,damage,effects,type);
    }
    if (!hit)
    {
        if (m_levelSound)
            m_levelSound->playSample(15,m_pSceneNode,0.0f,0.0f,false);
        return;
    }
    CBaseUnit* victim = target ? static_cast<CBaseUnit*>(target) : static_cast<CBaseUnit*>(item);
    executeProcs(static_cast<EEFFECT_TYPE>(75),victim);
    executeProcs(static_cast<EEFFECT_TYPE>(76),victim);
    if (weapon && victim)
        doWeaponProcs(weapon,victim);
    CSoundBank* sound = m_levelSound;
    if (description->m_bUnknown18 || !sound)
    {
        if (!weapon)
            return;
        sound = weapon->m_pSoundBank;
        if (!sound)
            return;
    }
    sound->playSample(1,m_pSceneNode,0.0f,0.0f,false);
}

#include <OgreBillboard.h>

void CCharacter::updateMotion(float elapsed, CLevel& level)
{
    if (m_eAIState == static_cast<EAIState>(16) || m_eAIState == AISTATE_DYING || m_eAIState == AISTATE_DEAD)
        return;
    if (m_pResourceManager->getEditorIsRunning())
        return;
    if (!getEnabled() && !m_bVisible)
        return;
    float gravity = -150.0f;
    if (m_motionBlocked || m_eAIState == AISTATE_DYING || m_eAIState == AISTATE_DEAD)
    {
        if (m_motionBlocked)
            gravity = 0.0f;
        m_impulse[0] *= 0.0f;
        m_impulse[1] *= 0.0f;
        m_impulse[2] *= 0.0f;
    }
    if (!m_isPathing && sqrtf(m_impulse[0]*m_impulse[0]+m_impulse[1]*m_impulse[1]+m_impulse[2]*m_impulse[2]) < 0.01f && m_groundFlag)
        return;
    bool previouslyBlocked = m_motionBlocked;
    m_motionBlocked = false;
    bool restoreAvoidance = false;
    if (m_pMaster && m_pMaster->m_bBlocksPath && m_pMaster->m_bPathingFlag19C)
    {
        m_pMaster->m_bPathingFlag19C = false;
        if (m_pMaster->m_pMaster && m_pMaster->m_pMaster->m_bBlocksPath)
            m_pMaster->m_pMaster->m_bPathingFlag19C = false;
        restoreAvoidance = true;
    }
    for (unsigned int i=0;i<m_Followers.size();++i)
    {
        CCharacter* follower = m_Followers[i];
        if (follower->m_bBlocksPath && follower->m_bPathingFlag19C)
        {
            restoreAvoidance = true;
            if (follower->m_bBlocksPath)
                follower->m_bPathingFlag19C = false;
        }
        for (unsigned int j=0;j<m_Followers[i]->m_Followers.size();++j)
        {
            CCharacter* child = m_Followers[i]->m_Followers[j];
            if (child->m_bBlocksPath && child->m_bPathingFlag19C && child->m_bBlocksPath)
                child->m_bPathingFlag19C = false;
        }
    }
    float multiplier = hasEffect(static_cast<EEFFECT_TYPE>(63))
        ? getEffectValue(static_cast<EEFFECT_TYPE>(63),static_cast<EDAMAGE_TYPES>(7)) : 1.0f;
    float zeroAcceleration = elapsed * 0.0f;
    float zeroDistance = elapsed * zeroAcceleration * 0.5f;
    Ogre::Vector3 position;
    position.y = elapsed * gravity * elapsed * 0.5f + elapsed * m_impulse[1]
        + m_movement.y * multiplier * m_moveSpeed * elapsed + m_vPosition.y;
    position.x = elapsed * m_impulse[0] + m_movement.x * multiplier * m_moveSpeed * elapsed
        + zeroDistance + m_vPosition.x;
    position.z = elapsed * m_impulse[2] + multiplier * m_movement.z * m_moveSpeed * elapsed
        + zeroDistance + m_vPosition.z;
    if (m_groundFlag)
        position.y += 0.01f;
    Ogre::Vector3 desired = position;
    bool previouslyGrounded = m_groundFlag;
    Ogre::Vector3 start = m_vPosition;
    m_movement.x += zeroAcceleration;
    m_groundFlag = false;
    m_movement.y += gravity * elapsed;
    m_movement.z += zeroAcceleration;
    Ogre::Vector3 initialImpulse(m_impulse[0],m_impulse[1],m_impulse[2]);
    Ogre::Vector3 minimum = start;
    Ogre::Vector3 maximum = start;
    MATH::expandBounds(minimum,maximum,position);
    float expansion = m_fBaseUnitValue194 * -4.0f;
    minimum.x += expansion;
    minimum.y -= 100.0f;
    minimum.z += expansion;
    expansion = m_fBaseUnitValue194 * 4.0f;
    maximum.x += expansion;
    maximum.y += 100.0f;
    maximum.z += expansion;
    level.sortForCollision(minimum,maximum);
    Ogre::Vector3 collision,contact,normal,extra;
    CBaseUnit* collidedUnit = NULL;
    unsigned int collisionType;
    unsigned int iterations = 0;
    unsigned int limit = 4;
    bool sphere = level.preSortedSphereCollision(desired+Ogre::Vector3(0.0f,100.0f,0.0f),desired,
        m_fBaseUnitValue194,collision,contact,normal,collisionType,extra,&collidedUnit,true);
    if (sphere && collisionType != 100 && normal.y > 0.2f && collision.y <= desired.y+0.3f)
    {
        limit = 5;
        iterations = 1;
        desired = collision;
        start.y = collision.y;
    }
    Ogre::Vector3 displacement = desired - start;
    bool obstacle = false;
    Ogre::Vector3 obstacleContact;
    float floorHeight = 2.0f;
    if (m_pResourceManager->getGameUI() && !m_pResourceManager->getGameUI()->getUIIsInCinematic())
    {
        while (level.preSortedSphereCollision(start,desired,m_fBaseUnitValue194,
            collision,contact,normal,collisionType,extra,&collidedUnit,true) && iterations < limit)
        {
            m_motionBlocked = false;
            float dot = m_movement.x*normal.x + m_movement.y*normal.y + m_movement.z*normal.z;
            if (dot < 0.0f)
            {
                m_movement.x -= normal.x * dot;
                m_movement.y -= normal.y * dot;
                m_movement.z -= dot * normal.z;
            }
            if (normal.y < 0.6f)
            {
                Ogre::Vector3 horizontal(normal.x,0.0f,normal.z);
                float length = sqrtf(normal.x*normal.x + 0.0f + normal.z*normal.z);
                if (length > 1.0e-8)
                {
                    float reciprocal = 1.0f / length;
                    horizontal.x = normal.x * reciprocal;
                    horizontal.y = reciprocal * 0.0f;
                    horizontal.z = reciprocal * normal.z;
                }
                dot = m_impulse[0]*horizontal.x + m_impulse[1]*horizontal.y + m_impulse[2]*horizontal.z;
                if (dot < 0.0f)
                {
                    m_impulse[0] -= horizontal.x * dot;
                    m_impulse[1] -= horizontal.y * dot;
                    m_impulse[2] -= dot * horizontal.z;
                }
            }
            if (normal.y > 0.2f && collisionType != 100)
            {
                m_groundNormal[0] = normal.x;
                m_groundFlag = true;
                m_groundNormal[1] = normal.y;
                m_groundNormal[2] = normal.z;
            }
            float originalLength = sqrtf(displacement.x*displacement.x + displacement.y*displacement.y + displacement.z*displacement.z);
            dot = displacement.x*normal.x + normal.y*displacement.y + displacement.z*normal.z;
            bool steep = normal.y < 0.2f;
            if (steep)
                obstacleContact = contact;
            if (dot > 0.0f)
                normal = Ogre::Vector3(0.0f,0.0f,0.0f);
            Ogre::Vector3 slide(displacement.x-normal.x*dot,displacement.y-normal.y*dot,displacement.z-normal.z*dot);
            if (steep)
                displacement = slide;
            float length = sqrtf(slide.x*slide.x + slide.y*slide.y + slide.z*slide.z);
            if (length > 1.0e-8)
            {
                float reciprocal = 1.0f / length;
                slide.x *= reciprocal;
                slide.y *= reciprocal;
                slide.z *= reciprocal;
            }
            desired.z = slide.z * originalLength;
            desired.y = slide.y * originalLength + start.y;
            desired.x = steep ? originalLength * slide.x + start.x : slide.x * originalLength + start.x;
            desired.z += start.z;
            obstacle = steep;
            if (steep)
                limit = 10;
            position = collision;
            ++iterations;
        }
        floorHeight = 0.9f;
    }
    bool floor = level.preSortedRayCollision(position+Ogre::Vector3(0.0f,floorHeight,0.0f),
        Ogre::Vector3(position.x,position.y-5.0f,position.z),contact,normal,collisionType,extra,false);
    if (!floor || (normal.y > 0.7f && collisionType == 100))
        m_motionBlocked = true;
    else if (!(m_fBaseUnitValue194+0.1f > fabsf(contact.y-position.y)) || !(normal.y > 0.2f) || collisionType == 100)
    {
        if (position.y < m_fBaseUnitValue194+contact.y)
            position.y = m_fBaseUnitValue194+contact.y;
        m_motionBlocked = false;
    }
    else
    {
        if (fabsf(contact.y-position.y) < m_fBaseUnitValue194+0.02f)
            position.y = m_fBaseUnitValue194+contact.y;
        m_groundNormal[1] = normal.y;
        m_groundFlag = true;
        m_motionBlocked = false;
        m_groundNormal[0] = normal.x;
        m_groundNormal[2] = normal.z;
    }
    if (restoreAvoidance)
    {
        if (m_pMaster)
        {
            if (m_pMaster->m_bBlocksPath)
                m_pMaster->m_bPathingFlag19C = true;
            if (m_pMaster->m_pMaster && m_pMaster->m_pMaster->m_bBlocksPath)
                m_pMaster->m_pMaster->m_bPathingFlag19C = true;
        }
        for (unsigned int i=0;i<m_Followers.size();++i)
        {
            if (m_Followers[i]->m_bBlocksPath)
                m_Followers[i]->m_bPathingFlag19C = true;
            for (unsigned int j=0;j<m_Followers[i]->m_Followers.size();++j)
            {
                CCharacter* child = m_Followers[i]->m_Followers[j];
                if (child->m_bBlocksPath && child->m_bPathingFlag19C && child->m_bBlocksPath)
                    child->m_bPathingFlag19C = true;
            }
        }
    }
    if (!m_motionBlocked)
        m_motionBlockedTime = 0.0f;
    else
        m_motionBlockedTime = elapsed + m_motionBlockedTime;
    if (m_motionBlocked)
    {
        if (!previouslyBlocked)
        {
            position = start;
            m_movement.x *= 0.0f;
            m_movement.y *= 0.0f;
            m_movement.z *= 0.0f;
        }
        else if (m_motionBlockedTime > 0.1f)
        {
            Ogre::Vector3 open = level.randomOpenItemPosition(start,1.0f,false);
            Ogre::Vector3 direction(open.x-position.x,0.0f,open.z-position.z);
            if (direction.length() < 1.0f)
                direction.normalise();
            position.z = direction.z * 4.0f * elapsed + position.z;
            position.y = direction.y * 4.0f * elapsed + position.y;
            position.x = direction.x * 4.0f * elapsed + position.x;
            CPositionableObject::setPosition(position);
        }
    }
    if (m_groundFlag)
    {
        bool keepPosition = true;
        if (m_isPathing || sqrtf(initialImpulse.x*initialImpulse.x+initialImpulse.y*initialImpulse.y+initialImpulse.z*initialImpulse.z) > 0.0f)
        {
            if (walkingSpeed() != 0.0f || runningSpeed() != 0.0f)
                keepPosition = false;
        }
        if (keepPosition)
        {
            position.x = start.x;
            position.z = start.z;
            if (previouslyGrounded)
                position.y = start.y;
        }
    }
    if (!iterations)
        m_groundFlag = false;
    else if (obstacle && m_isPathing)
    {
        Ogre::Vector3 absolute = getPosition(true);
        Ogre::Vector3 offset(absolute.x-m_targetPosition.x,0.0f,absolute.z-m_targetPosition.z);
        if (m_fBaseUnitValue194 + m_fBaseUnitValue194 < offset.length())
        {
            if (m_movementTimer > m_masterFollowDelay)
            {
                float radius = m_fBaseUnitValue194 + 0.4f;
                Ogre::Vector3 low(-radius+obstacleContact.x,obstacleContact.y+0.0f,obstacleContact.z-radius);
                Ogre::Vector3 high(obstacleContact.x+radius,obstacleContact.y+0.0f,obstacleContact.z+radius);
                level.incrementObjectPassability(low,high,radius);
                setDestination(level,m_targetPosition.x,m_targetPosition.z);
                level.decrementObjectPassability(low,high,radius);
                m_movementTimer = 0.0f;
            }
        }
        else
        {
            if (m_isPathing)
                m_pathGraceTime = 10.0f;
            m_isPathing = false;
            m_pathDestination = m_vPosition;
        }
    }
    if (m_motionBlocked || previouslyBlocked)
    {
        position.y = start.y;
        if (m_motionBlocked && m_motionBlockedTime > 0.5f)
        {
            m_vPosition = position;
            dropToGround(level,1.0f,false);
            position = m_vPosition;
        }
    }
    CPositionableObject::setPosition(position);
    extractOrientationVectors();
    if (m_automapBillboard)
        m_automapBillboard->setPosition(position);
    if (!m_groundFlag && !m_motionBlocked)
    {
        m_movement.x = 0.0f;
        m_movement.z = 0.0f;
    }
    else
    {
        m_movement.x *= 0.0f;
        m_movement.y *= 0.0f;
        m_movement.z *= 0.0f;
    }
    for (unsigned int i=0;i<m_Followers.size();++i)
        if (m_Followers[i]->attachesToMaster())
            m_Followers[i]->CPositionableObject::setPosition(getPosition(true));
}

#include "FileUtilities.h"
#include "RandomNames.h"
#include <OgreAxisAlignedBox.h>

void CCharacter::unitInit(CDataGroup* data, bool initialize)
{
    deleteUnitSpecificData();
    if (!data)
        return;
    CBaseUnit::unitInit(data,initialize);
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(131)))
        m_bInvulnerable = true;
    if (!m_pInventory)
    {
        if (ISA(UNITTYPES::MERCHANT))
        {
            m_pInventory = new CInventory(this,42);
            m_pInventory->addSection(static_cast<EINVENTORY_PANES>(3),42);
            m_pInventory->addSection(static_cast<EINVENTORY_PANES>(4),42);
        }
        else if (ISA(UNITTYPES::STASH))
            m_pInventory = new CInventory(this,42);
        else if (ISA(static_cast<UNITTYPES::EUNITTYPES>(87)))
        {
            m_pInventory = new CInventory(this,21);
            m_pInventory->addSection(static_cast<EINVENTORY_PANES>(1),21);
            m_pInventory->addSection(static_cast<EINVENTORY_PANES>(2),21);
        }
        else if (ISA(UNITTYPES::SHAREDSTASH))
            m_pInventory = new CInventory(this,0);
        else
            m_pInventory = new CInventory(this,21);
        if (m_pInventory)
            m_pInventory->addListener(this);
    }

    m_iUnitLevel = data->GetDataValue(L"LEVEL",static_cast<int>(m_iUnitLevel));
    m_Padding730[0] = data->GetDataValue(L"NO_ORIENTATION",false);
    m_bravery = data->GetDataValue(L"BRAVERY",1.0f);
    m_fBaseUnitValue194 = data->GetDataValue(L"COLLISION_RADIUS",0.3f);
    unsigned int level = m_iUnitLevel;
    m_iUnitLevel = 0;
    setLevel(level,true);
    m_damageDisplayEnabled = data->GetDataValue(L"DISPLAYDMG",true);
    m_Padding664[0] = data->GetDataValue(L"CANMATCHSPEED",false);
    m_Padding4A1[0] = data->GetDataValue(L"RENDERBEHIND",true);
    m_experienceReward = data->GetDataValue(L"XP",0);
    m_facingAngle = data->GetDataValue(L"ATTACKANGLE",60.0f);
    m_walkingSpeed = data->GetDataValue(L"WALKINGSPEED",2.5f);
    m_runningSpeed = data->GetDataValue(L"RUNNINGSPEED",6.25f);
    float walkMultiplier = m_pDataGroup->GetDataValue(L"WALK_ANIM_MULT",1.0f);
    float runMultiplier = m_pDataGroup->GetDataValue(L"RUN_ANIM_MULT",1.0f);
    std::memcpy(m_Padding322+6,&walkMultiplier,sizeof(walkMultiplier));
    std::memcpy(m_Padding322+10,&runMultiplier,sizeof(runMultiplier));
    m_damageShapeEnabled = data->GetDataValue(L"TARGETABLE",true);
    m_bCharacterFlag4A0 = data->GetDataValue(L"USEWEAPONDAMAGE",true);
    m_flag410 = data->GetDataValue(L"WARDROBE",false);
    m_wardrobeNames[0] = data->GetDataValue(L"WARDROBE_BASE",EMPTY_WSTRING);
    m_wardrobeNames[1] = data->GetDataValue(L"CHEST_BASE",EMPTY_WSTRING);
    m_wardrobeNames[2] = data->GetDataValue(L"BOOTS_BASE",EMPTY_WSTRING);
    m_wardrobeNames[3] = data->GetDataValue(L"GLOVES_BASE",EMPTY_WSTRING);
    m_wardrobeNames[4] = data->GetDataValue(L"HELMET_BASE_MESH",EMPTY_WSTRING);
    m_wardrobeNames[5] = data->GetDataValue(L"SHOULDER_BASE_MESH",EMPTY_WSTRING);
    m_bInvulnerable = data->GetDataValue(L"INVINCIBLE",false);
    if (!initialize)
        giveGold(data->GetDataValue(L"GOLD",0));
    m_characterFlag52F = data->GetDataValue(L"DAMAGEABLE",true);
    float attackRange = data->GetDataValue(L"ATTACK_RANGE",0.375f);
    std::memcpy(m_Padding4D0+8,&attackRange,sizeof(attackRange));
    float strikeRange = data->GetDataValue(L"STRIKE_RANGE",0.5f);
    std::memcpy(m_Padding4D0+4,&strikeRange,sizeof(strikeRange));
    m_attackRangeScale = data->GetDataValue(L"RANGE_MULTIPLIER",1.0f);
    m_attackRadius = data->GetDataValue(L"REACH_BONUS",0.75f);
    SetName(data->GetDataValue(L"NAME",L""));
    std::wstring displayName = data->GetDataValue(L"DISPLAYNAME",L"");
    if (displayName.empty())
        displayName = data->GetDataValue(L"NAME",L"MONSTER");
    m_characterDisplayName = displayName;
    m_followRange = data->GetDataValue(L"FOLLOW_RADIUS",18.0f);
    float motionRadius = data->GetDataValue(L"MOTION_RADIUS",4.5f);
    std::memcpy(m_Padding36C,&motionRadius,sizeof(motionRadius));
    if (motionRadius > 0.0f && !ISA(static_cast<UNITTYPES::EUNITTYPES>(167)))
    {
        int difficulty = m_pResourceManager->getGameClient()->m_startDifficulty;
        if (difficulty >= 0 && difficulty <= 3)
        {
            float bonus;
            std::memcpy(&bonus,CGameGlobals::getSingleton()->m_GlobalsData98+4*difficulty,sizeof(bonus));
            motionRadius += bonus;
        }
        motionRadius = motionRadius > 0.0f ? motionRadius : 0.0f;
        std::memcpy(m_Padding36C,&motionRadius,sizeof(motionRadius));
    }
    m_nearWalkRadius = data->GetDataValue(L"NEAR_WALK_RADIUS",0.0f);
    m_sightRange = data->GetDataValue(L"SIGHT_RADIUS",7.0f);
    if (m_sightRange > 0.0f && !ISA(static_cast<UNITTYPES::EUNITTYPES>(167)))
    {
        int difficulty = m_pResourceManager->getGameClient()->m_startDifficulty;
        if (difficulty >= 0 && difficulty <= 3)
        {
            float bonus;
            std::memcpy(&bonus,CGameGlobals::getSingleton()->m_GlobalsData98+4*difficulty,sizeof(bonus));
            m_sightRange += bonus;
        }
        m_sightRange = m_sightRange > 0.0f ? m_sightRange : 0.0f;
    }
    m_damageReactRange = data->GetDataValue(L"DAMAGE_REACT_RADIUS",2.0f);
    m_viewAngle = data->GetDataValue(L"VIEW_ANGLE",90.0f);
    m_turnRate288 = data->GetDataValue(L"TURN_RATE",10.0f);
    std::wstring directory = data->GetDataValue(L"RESOURCEDIRECTORY",EMPTY_WSTRING);
    std::wstring mesh = data->GetDataValue(L"MESHFILE",EMPTY_WSTRING);
    loadModel(FILESYSTEM::CleanPath(directory+L"/"+mesh+L".mesh"),EMPTY_WSTRING);
    std::wstring alignment = m_pDataGroup->GetDataValue(L"ALIGNMENT",L"EVIL");
    for (int i=0;i<7;++i)
        if (alignment == KALIGNMENT_STRINGS[i])
        {
            setAlignment(static_cast<EAlignment>(i));
            break;
        }
    if (!initialize)
        createDefaultEquipment();
    CDataGroup* treasure = data->GetDataGroupByName(L"TREASURE",false);
    if (treasure)
    {
        m_merchantSpawnClass = m_pResourceManager->getSpawnClassByName(treasure->GetDataValue(L"SPAWNCLASS",EMPTY_WSTRING));
        m_merchantMinimum = treasure->GetDataValue(L"MIN",1);
        m_merchantMaximum = treasure->GetDataValue(L"MAX",1);
    }
    if (ISA(UNITTYPES::MERCHANT) && m_merchantSpawnClass && !initialize)
        generateMerchantInventory();
    if (!m_pAIManager)
    {
        m_pAIManager = new CAIManager(this);
        m_pAIManager->initalize();
    }
    m_pendingPetSpawn = NULL;
    if (!initialize && m_pResourceManager && m_pResourceManager->getLevel())
        m_pendingPetSpawn = m_pResourceManager->getSpawnClassByName(data->GetDataValue(L"MINION_SPAWNCLASS",EMPTY_WSTRING));
    if (m_pSkillManager)
    {
        Ogre::Vector3 targetPosition = getPosition(true);
        Ogre::Quaternion orientation = getOrientationQuaternion();
        Ogre::Vector3 position = getPosition(true);
        m_pSkillManager->fireSkillsOnCreate(this,SKILL_ACTIVATION_NORMAL,position,orientation,targetPosition,NULL);
    }
    if (m_pDataGroup->GetDataValue(L"CHAMPION",false))
    {
        makeChampion(CRandomNames::getSingleton()->generateName(true),m_iUnitLevel+1,L"CHAMPION");
        m_alwaysActive = false;
    }
    else if (m_pDataGroup->GetDataValue(L"BOSS_CHAMPION",false))
    {
        makeChampion(m_characterDisplayName,m_iUnitLevel+1,EMPTY_WSTRING);
        m_alwaysActive = true;
    }
    if (m_pDataGroup->GetDataValue(L"RENDERALWAYS",false))
    {
        m_Padding773 = 1;
        Ogre::AxisAlignedBox bounds(-100000.0f,-100000.0f,-100000.0f,100000.0f,100000.0f,100000.0f);
        static_cast<CGenericModel*>(getUnitModel())->getEntity()->getMesh()->_setBounds(bounds,true);
    }
    m_spawnFlag703 = m_pDataGroup->GetDataValue(L"DONTDROPGOLD",false);
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(167)))
        addUnitTheme(L"MIMICIDLE");
    CBaseUnit::unitInitThemes();
}

#include "ParticlePreloader.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "CollisionModel.h"
#include "CollisionList.h"
#include "CullingBounds.h"
#include "FileUtilities.h"
#include <OgreSkeletonInstance.h>

namespace {
float characterLoadMaximum(float first, float second) { return first > second ? first : second; }
float characterLoadMinimum(float first, float second) { return first < second ? first : second; }
}

void CCharacter::loadModel(std::wstring modelName, std::wstring animationName)
{
    CResourceManager* resources = m_pResourceManager;
    if (m_pUnitModel) { delete m_pUnitModel; m_pUnitModel = NULL; }
    bool hardwareSkinning = m_pDataGroup->GetDataValue(L"ALLOW_HWSKINNING", true);
    bool wardrobeModel = !m_wardrobeNames[0].empty() && m_flag410;
    m_pUnitModel = resources->createGenericModel(NULL, modelName.c_str(), animationName.c_str(), hardwareSkinning, wardrobeModel, true);
    bool softBlend = m_pDataGroup->GetDataValue(L"SOFTBLEND", false);
    if (m_pUnitModel) {
        m_pUnitModel->m_gap23B = softBlend;
        Ogre::SceneManager* paperdollScene = ISA(static_cast<UNITTYPES::EUNITTYPES>(87)) ?
            CMasterResourceManager::getSingleton()->m_renderBehindParticleScene : CMasterResourceManager::getSingleton()->m_pSceneManager;
        if (ISA(UNITTYPES::PLAYER) || (ISA(static_cast<UNITTYPES::EUNITTYPES>(87)) && m_bInvulnerable)) {
            if (m_pPaperdollModel) { delete m_pPaperdollModel; m_pPaperdollModel = NULL; }
            wardrobeModel = !m_wardrobeNames[0].empty() && m_flag410;
            m_pPaperdollModel = resources->createGenericModel(paperdollScene, modelName.c_str(), animationName.c_str(), hardwareSkinning, wardrobeModel, true);
            if (m_pPaperdollModel) {
                m_pPaperdollModel->setPosition(0.0f, 0.0f, 0.0f);
                m_pPaperdollModel->setVisible(true);
                m_pPaperdollModel->setScale(getScale().y);
                if (m_pResourceManager && m_pResourceManager->getLevel()) {
                    CLevelTemplateData* data = m_pResourceManager->getLevel()->m_pLevelTemplateData;
                    std::wstring rim = data ? data->m_sRimlightTexture : L"media/sharedtextures/rimlight.dds";
                    m_pPaperdollModel->setRimLighting(rim);
                }
            }
        }
        if (m_pUnitModel && m_flag410) {
            paperdollScene = ISA(static_cast<UNITTYPES::EUNITTYPES>(87)) ?
                CMasterResourceManager::getSingleton()->m_renderBehindParticleScene : CMasterResourceManager::getSingleton()->m_pSceneManager;
            if (m_wardrobe) { delete m_wardrobe; m_wardrobe = NULL; }
            Ogre::SceneManager* scene = m_pResourceManager ? m_pResourceManager->getSceneManager() : NULL;
            m_wardrobe = new CWardrobe(this, scene, paperdollScene, m_pUnitModel, m_pPaperdollModel,
                m_wardrobeNames[0], m_wardrobeNames[1], m_wardrobeNames[2], m_wardrobeNames[3], m_wardrobeNames[4], m_wardrobeNames[5]);
            m_wardrobe->update(NULL);
            getBones();
        }
    }
    if (!m_flag410 && m_renderBehind && m_pResourceManager && m_pResourceManager->getLevel()) {
        CLevelTemplateData* data = m_pResourceManager->getLevel()->m_pLevelTemplateData;
        std::wstring rim = data ? data->m_sRimlightTexture : L"media/sharedtextures/rimlight.dds";
        m_pUnitModel->setRimLighting(rim);
    }
    if (m_wardrobe && m_wardrobe->m_baseImage)
        m_pUnitModel->setTextureOverride(m_wardrobe->m_texture, "HELMET", "SHOULDERS");
    std::wstring texture = m_pDataGroup->GetDataValue(L"TEXTURE_OVERRIDE", EMPTY_WSTRING);
    if (!texture.empty()) {
        m_pUnitModel->setTextureOverride(texture);
        if (m_pPaperdollModel) m_pPaperdollModel->setTextureOverride(texture);
    }
    std::vector<CDataGroup*> replacements;
    unsigned int replacementCount = m_pDataGroup->GetDataGroupsMatchingName(L"TEXTURE_REPLACE", &replacements);
    for (unsigned int i = 0; i < replacementCount; ++i) {
        CDataGroup* data = replacements[i];
        std::wstring name = data->GetDataValue(L"NAME", L"");
        std::wstring textureName = data->GetDataValue(L"TEXTURE", L"");
        m_pUnitModel->setTextureOverrideSingle(STRINGS::StringConvertToNarrow(name.c_str()), textureName);
        if (m_pPaperdollModel) m_pPaperdollModel->setTextureOverrideSingle(STRINGS::StringConvertToNarrow(name.c_str()), textureName);
    }
    CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    if (!settings->GetInt(KSETTINGS_NO_SOUNDS)) {
        if (m_levelSound) { delete m_levelSound; m_levelSound = NULL; }
        CSoundManager* sound = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSoundManager : NULL;
        m_levelSound = new CSoundBank(*sound, false);
        if (!m_secondarySound) {
            sound = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSoundManager : NULL;
            m_secondarySound = new CSoundBank(*sound, false);
        }
    }
    CSoundBankDataInformation* sounds = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    if (m_pUnitModel) {
        int sample = 0;
        for (unsigned int animation = 0; static_cast<int>(animation) < static_cast<int>(m_pUnitModel->getAnimationCount()); ++animation) {
            for (unsigned int index = 0; static_cast<int>(index) < static_cast<int>(m_pUnitModel->getKeyCount(animation)); ++index) {
                CKeyframe* key = m_pUnitModel->getKeyFrame(animation, index);
                if (key->m_iEventCode == 3 || key->m_iEventCode == 27) {
                    CSoundData* sound = sounds->getSoundDataObject(key->m_text);
                    if (sound && m_secondarySound) m_secondarySound->addSample(sample, sound->m_iGuid);
                    m_pUnitModel->addValueIndex(animation, key, sample);
                    ++sample;
                } else if (key->m_iEventCode == 4 || key->m_iEventCode == 5) {
                    unsigned int count = key->m_mode;
                    if (key->m_name == "Every Bone")
                        count = static_cast<CGenericModel*>(getUnitModel())->m_pSkeleton->getNumBones();
                    for (unsigned int bone = 0; bone < count; ++bone) {
                        CParticleAnimationTrigger* trigger = new CParticleAnimationTrigger;
                        trigger->m_resources = m_pResourceManager;
                        trigger->m_particle = NULL;
                        trigger->m_stopOnDeath = false;
                        trigger->m_animationIndex = -1;
                        trigger->m_offset = Ogre::Vector3(0.0f,0.0f,0.0f);
                        trigger->m_node = NULL;
                        trigger->m_nodeOwner = NULL;
                        trigger->m_theme = NULL;
                        trigger->m_stopWhenHidden = true;
                        trigger->m_stopFlag59 = false;
                        trigger->m_stopFlag5A = false;
                        m_pUnitModel->addValueIndex(animation, key, m_particleTriggers.size());
                        m_particleTriggers.add(trigger);
                        std::wstring particleName = STRINGS::StringUpper(CMasterResourceManager::getSingleton()->m_pParticlePreloader->getParticleNameByFileName(key->m_text));
                        if (particleName.empty()) {
                            std::wstring name = STRINGS::StringUpper(key->m_text);
                            std::wstring path = STRINGS::StringUpper(key->m_text);
                            CMasterResourceManager::getSingleton()->m_pParticlePreloader->LoadParticle(path, name);
                        }
                        std::wstring name = STRINGS::StringUpper(key->m_text);
                        trigger->m_particle = CMasterResourceManager::getSingleton()->m_pParticlePreloader->GetParticle(m_pResourceManager, name.c_str());
                        if (trigger->m_particle) {
                            trigger->m_particle->CPositionableObject::setPosition(key->m_offset);
                            trigger->m_offset = key->m_offset;
                            trigger->m_stopOnDeath = key->m_iEventCode == 5;
                            trigger->m_animationIndex = key->m_animationIndex;
                            trigger->m_theme = key->m_theme;
                            trigger->m_stopWhenHidden = key->m_flag4C;
                            trigger->m_name = key->m_name;
                            trigger->m_stopFlag59 = false;
                            trigger->m_stopFlag5A = STRINGS::StringUpper(m_pUnitModel->getAnimationName(animation)) == "BIND";
                            configureParticleTrigger(trigger, bone);
                        }
                    }
                }
            }
        }
        m_pUnitModel->setParentGuid(getGuid());
        m_pUnitModel->sceneNodeSetParent(NULL, false);
        sceneNodeAddChild(m_pUnitModel);
        m_pUnitModel->setVisible(true);
        Ogre::Vector3 position(0.0f, -m_fBaseUnitValue194 / m_vScale.z, 0.0f);
        m_pUnitModel->CPositionableObject::setPosition(position);
    }
    for (unsigned int i = 0; i != 67; ++i) {
        std::wstring name = m_pDataGroup->GetDataValue(KSOUNDBANK_STRINGS[i], EMPTY_WSTRING);
        if (name != EMPTY_WSTRING) {
            CSoundData* sound = sounds->getSoundDataObject(STRINGS::StringUpper(name));
            if (sound && m_levelSound) m_levelSound->addSample(i, sound->m_iGuid);
        }
    }
    const wchar_t* names[] = {L"MISSILEREFLECT",L"LOWMANA",L"METALBLOCK",L"ELEMENTALFIREGETHIT",L"ELEMENTALICEGETHIT",L"ELEMENTALELECTRICGETHIT",L"ELEMENTALPOISONGETHIT",L"SWORDFLESH",L"BLOCK",L"CRITICALSTRIKE"};
    const int slots[] = {34,33,7,4,3,5,6,2,8,9};
    for (unsigned int i = 0; i != 10; ++i) {
        if (i == 1 && !ISA(UNITTYPES::PLAYER)) continue;
        CSoundData* sound = sounds->getSoundDataObject(names[i]);
        if (sound && m_levelSound) m_levelSound->addSample(slots[i], sound->m_iGuid);
    }
    getBones();
    std::wstring aiType = STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"AITYPE", L""));
    if (!aiType.empty())
        for (unsigned int i = 0; i != 7; ++i)
            if (aiType == KAITYPE_STRINGS[i]) m_aiType = i;
    setVisible(true, true);
    setRenderBehind(m_renderBehind);
    m_equipmentParticles[0] = m_pResourceManager->createParticle(L"HIT");
    m_equipmentParticles[8] = m_pResourceManager->createParticle(L"TRANSFORM");
    m_equipmentParticles[6] = m_pResourceManager->createParticle(L"CRITICAL");
    m_equipmentParticles[7] = m_pResourceManager->createParticle(L"BLOCK");
    m_equipmentParticles[9] = m_pResourceManager->createParticle(L"ICEEXPLODE");
    const wchar_t* particleKeys[] = {L"PARTICLE_GETHIT",L"PARTICLE_GETHIT_CENSOR",L"PARTICLE_DEATH",L"PARTICLE_DEATH_CENSOR",L"PARTICLE_EXPLODE",L"PARTICLE_EXPLODE_CENSOR",L"PARTICLE_SPAWN"};
    const unsigned int particleSlots[] = {1,2,3,11,10,11,5};
    for (unsigned int i = 0; i != 7; ++i) {
        std::wstring name = m_pDataGroup->GetDataValue(particleKeys[i], EMPTY_WSTRING);
        if (!name.empty()) {
            if (name.size() > 8 && name[name.size()-8] == L'.') CParticlePreloader::getSingleton()->LoadParticle(name);
            m_equipmentParticles[particleSlots[i]] = m_pResourceManager->createParticle(name.c_str());
        }
    }
    std::wstring collision = m_pDataGroup->GetDataValue(L"COLLISIONFILE", EMPTY_WSTRING);
    if (collision == EMPTY_WSTRING) collision = L"media/models/collider.mesh";
    else {
        std::wstring directory = m_pDataGroup->GetDataValue(L"RESOURCEDIRECTORY", EMPTY_WSTRING);
        collision = FILESYSTEM::CleanPath(directory + L"/" + collision + L".mesh");
    }
    collision = FILESYSTEM::CleanPath(collision);
    m_collisionModel = CMasterResourceManager::getSingleton()->addCollisionModel(collision);
    CCollisionList* list = m_collisionModel->getCollisionList();
    float localMinY = 0.0f + list->m_vBoundsMax.y;
    float localMinX = list->m_vBoundsMax.x + -0.25f;
    float localMinZ = -0.25f + list->m_vBoundsMax.z;
    list = m_collisionModel->getCollisionList();
    float localMaxY = 1.0f + list->m_vBoundsMin.y;
    float localMaxX = list->m_vBoundsMin.x + 0.25f;
    float localMaxZ = 0.25f + list->m_vBoundsMin.z;
    m_pCullingBounds->m_vLocalMinimum = Ogre::Vector3(localMinX,localMinY,localMinZ);
    m_pCullingBounds->m_vLocalMaximum = Ogre::Vector3(localMaxX,localMaxY,localMaxZ);
    float extent = characterLoadMaximum(-localMinX, localMaxX);
    extent = characterLoadMaximum(-localMinZ, extent);
    extent = characterLoadMaximum(localMaxZ, extent);
    float lower = characterLoadMinimum(-extent, localMinX);
    lower = characterLoadMinimum(-localMaxZ, lower);
    lower = characterLoadMinimum(localMinZ, lower);
    float upperZ = characterLoadMaximum(-lower, localMaxZ);
    upperZ = characterLoadMaximum(-localMinZ, upperZ);
    float opposite = -upperZ;
    if (extent > upperZ) { opposite = -extent; upperZ = extent; }
    float lowerZ = characterLoadMinimum(-extent, localMinZ);
    lowerZ = characterLoadMinimum(opposite, lowerZ);
    lowerZ = characterLoadMinimum(lower, lowerZ);
    m_pCullingBounds->m_vMinimum = Ogre::Vector3(lower,localMinY,lowerZ);
    m_pCullingBounds->m_vMaximum = Ogre::Vector3(extent,localMaxY,upperZ);
    CBaseUnit::updateCullingBounds();
    setAlignment(alignment());
    if (m_pUnitModel && !m_attacks.empty())
        m_attacks[0]->m_animationIndex = m_pUnitModel->getAnimationIndex(m_attacks[0]->m_sAnimationName);
}

#include "CullingBounds.h"
#include "Editor.h"
#include "SettingsVariables.h"
#include <OgreAxisAlignedBox.h>

void CCharacter::update(Ogre::Camera* camera, const Ogre::Vector3& cameraPosition, float elapsed)
{
    if (m_levelSound && m_secondarySound)
    {
        m_levelSound->update(elapsed,m_pSceneNode);
        m_secondarySound->update(elapsed,m_pSceneNode);
    }
    updateOpacity(elapsed,false);
    m_playTime = elapsed + m_playTime;
    CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
    if (!m_bRangeEnabled)
    {
        if (m_bBaseUnitFlag19B)
            removeFromAvoidanceMap(*level);
        return;
    }
    if (level && m_eAIState == static_cast<EAIState>(42))
    {
        CLevel* currentLevel = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
        if (currentLevel->m_pGameClient->getGameState() == static_cast<EGameState>(1))
        {
            setVisible(false,true);
            removeFromAvoidanceMap(*level);
            updateInTownTimer(elapsed,*level);
            return;
        }
    }
    calculateActiveRange(cameraPosition);
    bool fadeOut = characterShouldFadeOut();
    if (fadeOut)
        setVisible(false);
    if (!m_bInActiveRange)
    {
        setVisible(false);
        if (m_eAIState == AISTATE_DEAD && m_currentOpacity <= 0.0f)
        {
            CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
            if (settings->GetInt(KSETTINGS_DESTROY_MONSTERS_AFTER_DEATH))
                m_bBaseUnitFlag190 = true;
            else
            {
                settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
                if (settings->GetFloat(KSETTINGS_F_AVERAGE_FPS) <= 30.0f)
                    m_bBaseUnitFlag190 = true;
            }
        }
        fadeOut = true;
        if (!m_bVisible)
        {
            if (m_bBlocksPath)
                m_bPathingFlag19C = false;
            CLevel* currentLevel = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            removeFromAvoidanceMap(*currentLevel);
            setTarget(NULL);
            return;
        }
    }
    if (!m_flag773 && !m_bVisible && !getEnabled())
    {
        Ogre::AxisAlignedBox bounds(m_pCullingBounds->getWorldMinimum(),m_pCullingBounds->getWorldMaximum());
        if (!camera->isVisible(bounds,NULL) && !getIsPlayer())
            setVisible(false,true);
        else if (!m_forcedHidden)
            setVisible(!fadeOut);
        if (m_bBlocksPath)
            m_bPathingFlag19C = false;
        CLevel* currentLevel = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
        removeFromAvoidanceMap(*currentLevel);
        setTarget(NULL);
        return;
    }
    if (m_pUnitModel)
    {
        float light = 1.0f;
        if (!m_pResourceManager->getEditorIsRunning() && level->m_pLevelTemplateData->getUnitLightFade()
            && (CEditor::getSingleton()->getFlags() & 2))
        {
            Ogre::Vector3 offset(m_vPosition.x-cameraPosition.x,0.0f,m_vPosition.z-cameraPosition.z);
            float start = level->m_pLevelTemplateData->m_unitFadeStart;
            float distance = offset.length() - start;
            distance = distance > 0.0f ? distance : 0.0f;
            float range = level->m_pLevelTemplateData->m_unitFadeDistance - start;
            distance = distance < range ? distance : range;
            float height = fabsf(m_vPosition.y-cameraPosition.y) / 3.0f;
            height = height < 1.0f ? height : 1.0f;
            light = (1.0f-distance/range) * (1.0f-height);
            CLevel* currentLevel = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            if (currentLevel && currentLevel->m_pGameClient->getGameState() == static_cast<EGameState>(0))
                light = 1.0f;
        }
        m_pUnitModel->setLightOverride(light);
        if (m_pInventory && m_pInventory->m_equipmentRefs.size())
        {
            for (unsigned int i=0;i<12;++i)
            {
                CEquipment* equipment = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(i));
                if (equipment)
                {
                    if (equipment->getUnitModel())
                        static_cast<CGenericModel*>(equipment->getUnitModel())->setLightOverride(light);
                    if (equipment->getUnitModelSecondary())
                        static_cast<CGenericModel*>(equipment->getUnitModelSecondary())->setLightOverride(light);
                }
            }
        }
        Ogre::Vector3 modelPosition = m_pUnitModel->getPosition(false);
        Ogre::Vector3 absolute = getPosition(true);
        m_lastWorldPosition[1] = absolute.y + modelPosition.y;
        m_lastWorldPosition[0] = absolute.x + modelPosition.x;
        m_lastWorldPosition[2] = absolute.z + modelPosition.z;
    }
    m_pathGraceTime = elapsed + m_pathGraceTime;
    if (m_pathGraceTime > 100.0f)
        m_pathGraceTime = 100.0f;
    m_idleSoundTime = elapsed + m_idleSoundTime;
    if (m_idleSoundTime > 100.0f)
        m_idleSoundTime = 100.0f;
    m_fidgetTime = elapsed + m_fidgetTime;
    if (m_fidgetTime > 100.0f)
        m_fidgetTime = 100.0f;
    m_movementTimer = elapsed + m_movementTimer;
    if (m_movementTimer > 100.0f)
        m_movementTimer = 100.0f;
    if (m_transformationTime > 0.0f && m_transformationTime != -999.0f)
    {
        m_transformationTime -= elapsed;
        if (m_transformationTime <= 0.0f)
            revertTransformation();
    }
    if (m_attackTime > 0.0f)
    {
        m_attackTime -= elapsed;
        if (m_attackTime <= 0.0f)
        {
            if (!m_attackEvent && m_eAIState != AISTATE_DYING && m_eAIState != AISTATE_DEAD)
            {
                m_attackEvent = true;
                performAttack(NULL,0,1.0f,1.0f,static_cast<EDAMAGE_TYPES>(7));
            }
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
            m_attackTime = 0.0f;
        }
    }
    CLevel* currentLevel = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
    if (currentLevel && currentLevel->m_pGameClient->getGameState() == static_cast<EGameState>(1))
        updateEffects(elapsed,*currentLevel);
    if (m_pEffectManager)
    {
        m_pEffectManager->calculateEffectValues();
        m_pEffectManager->deleteDeadEffects();
    }
    currentLevel = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
    CCharacter* killer = updateHP(*currentLevel,elapsed);
    updateMana(elapsed);
    updateActiveSkill(elapsed);
    displayDamageAbsorbed(elapsed);
    currentLevel = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
    removeFromAvoidanceMap(*currentLevel);
    if (m_bBlocksPath)
        m_bPathingFlag19C = false;
    if (m_pAIManager)
        m_pAIManager->update(elapsed);
    updateAI(elapsed,false);
    if (elapsed == 0.0f)
    {
        if (m_eAIState != AISTATE_DYING && m_eAIState != AISTATE_DEAD)
        {
            if (m_bBlocksPath)
                m_bPathingFlag19C = true;
            currentLevel = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            addToAvoidanceMap(*currentLevel);
        }
        return;
    }
    m_turnFlag265 = false;
    if (m_fHPFloat <= 0.0f && m_eAIState != AISTATE_DYING && m_eAIState != AISTATE_DEAD)
        die(killer,NULL,0.0f,false);
    if (m_targetCharacter.getObject() && ISA(static_cast<UNITTYPES::EUNITTYPES>(131))
        && m_targetCharacter.getObject()->ISA(UNITTYPES::PLAYER)
        && m_targetCharacter.getObject()->m_targetCharacter.getObject() != this)
        setTarget(NULL);
    bool turned = false;
    if (m_pMaster)
    {
        if ((m_pMaster->m_eAIState == AISTATE_DYING || m_pMaster->m_eAIState == AISTATE_DEAD)
            && !m_pMaster->ISA(UNITTYPES::PLAYER))
            setMaster(NULL);
        if (m_pMaster && (m_eAIState == static_cast<EAIState>(2) || m_eAIState == static_cast<EAIState>(4)
            || m_eAIState == static_cast<EAIState>(15)) && attachesToMaster())
        {
            const Ogre::Vector3& forward = m_pMaster->getForward();
            Ogre::Vector3 position = m_pMaster->getPosition(true);
            turnTowardPosition(position+forward,elapsed*0.25f);
            turned = true;
        }
    }
    if (!turned)
    {
        CSkill* skill = m_activeSkill;
        if (skill && (skill->m_animationID == -1 || skill->m_interruptible)
            && (m_skillLooping || !(m_skillTime <= 0.0f)) && m_skillTime >= 0.1f
            && !skill->m_allowsTurning && m_eAIState != static_cast<EAIState>(40))
        {
            if (m_isPathing && (m_moveInputHeld || m_skillLooping || (m_skillTime > 0.0f && !m_skillInterrupted))
                && ((skill->m_animationID != -1 && !skill->m_interruptible) || (!m_skillLooping && m_skillTime <= 0.0f)
                    || !skill->m_stopsPathingOnCompletion))
            {
                m_pathGraceTime = 10.0f;
                m_isPathing = false;
                m_pathDestination = m_vPosition;
            }
            Ogre::Vector3 position = getPosition(true);
            turnTowardPosition(position+m_targetDirection,elapsed);
        }
        else if (m_targetCharacter.getObject() && !m_isPathing && m_eAIState != static_cast<EAIState>(12)
            && m_eAIState != AISTATE_DYING && m_eAIState != AISTATE_DEAD
            && m_eAIState != static_cast<EAIState>(41) && m_eAIState != static_cast<EAIState>(16))
            turnTowardPosition(m_targetCharacter.getObject()->getPosition(true),elapsed);
        else if (m_targetItem.getObject() && !m_isPathing && m_eAIState != static_cast<EAIState>(16))
            turnTowardPosition(m_targetItem.getObject()->getPosition(true),elapsed);
        else
        {
            bool turn = true;
            if (!m_moveInputHeld && (!skill || (skill->m_animationID != -1 && !skill->m_interruptible)
                || (!m_skillLooping && m_skillTime <= 0.0f)))
                turn = false;
            if (turn && skill && (skill->m_animationID == -1 || skill->m_interruptible)
                && (m_skillLooping || m_skillTime > 0.0f) && skill->m_stopsPathingOnCompletion)
                turn = false;
            if (turn)
            {
                if (m_isPathing && (m_moveInputHeld || (skill && (m_skillLooping || (m_skillTime > 0.0f && !m_skillInterrupted)))))
                {
                    m_pathGraceTime = 10.0f;
                    m_isPathing = false;
                    m_pathDestination = m_vPosition;
                }
                turnTowardPosition(m_targetPosition,elapsed);
            }
        }
    }
    updatePathing(elapsed);
    currentLevel = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
    updateMotion(elapsed,*currentLevel);
    updateVisualEquippedItems(elapsed);
    if (m_eAIState != AISTATE_DYING && m_eAIState != AISTATE_DEAD)
    {
        if (m_bBlocksPath)
            m_bPathingFlag19C = true;
        currentLevel = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
        addToAvoidanceMap(*currentLevel);
    }
    if (!m_flag773)
    {
        Ogre::AxisAlignedBox bounds(m_pCullingBounds->getWorldMinimum(),m_pCullingBounds->getWorldMaximum());
        if (!camera->isVisible(bounds,NULL) && !getIsPlayer())
            setVisible(false,true);
        else if (!m_forcedHidden)
            setVisible(!fadeOut);
    }
    CBaseUnit::update(camera,cameraPosition,elapsed);
    if (m_procTime > 0.0f)
        m_procTime -= elapsed;
    setAllowJumpDown(false);
}

#include <OgreMaterialManager.h>
#include <OgreTechnique.h>
#include <OgrePass.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include "CameraShake.h"
#include "CameraControl.h"
#include <cstring>

void CCharacter::updateAnimation(float elapsed)
{
    if (m_pPaperdollModel) m_pPaperdollModel->updateAnimation(elapsed, false);
    if (!m_pUnitModel) return;
    if (!m_bInActiveRange) setVisible(false);
    else {
        CBaseUnit::updateCullingBounds();
        Ogre::Vector3 modelPosition = m_pUnitModel->getPosition(false);
        Ogre::Vector3 position = getPosition(true);
        m_lastWorldPosition[0] = position.x + modelPosition.x;
        m_lastWorldPosition[1] = position.y + modelPosition.y;
        m_lastWorldPosition[2] = position.z + modelPosition.z;
    }
    if (m_eAIState != static_cast<EAIState>(12) && m_eAIState != static_cast<EAIState>(5) && !m_bVisible)
        if (!m_forcedHidden || !getEnabled()) return;
    if (getCastsShadows() && m_bInActiveRange && m_pInventory) {
        m_pUnitModel->setCastsShadows(m_castsDynamicShadow);
        for (int i = 0; i != 12; ++i) {
            CEquipment* equipment = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(i));
            if (!equipment) continue;
            if (equipment->getUnitModel())
                static_cast<CGenericModel*>(equipment->getUnitModel())->setCastsShadows(m_castsDynamicShadow);
            if (equipment->getUnitModelSecondary())
                static_cast<CGenericModel*>(equipment->getUnitModelSecondary())->setCastsShadows(m_castsDynamicShadow);
        }
    }
    if (m_pUnitModel) m_pUnitModel->updateAnimation(elapsed, false);
    updateBonePositions();
    updateAttack(*(m_pResourceManager ? m_pResourceManager->getLevel() : NULL));
    updateSkillKeys(elapsed);
    updateSkill(elapsed);
    if (m_weaponTrails[0]) m_weaponTrails[0]->update(elapsed, NULL, NULL, false, this);
    if (m_weaponTrails[1]) m_weaponTrails[1]->update(elapsed, NULL, NULL, false, this);
    if (m_weaponTrails[2]) m_weaponTrails[2]->update(elapsed, NULL, NULL, false, NULL);
    if (elapsed == 0.0f || !getUnitModel()) return;
    for (unsigned int event = 0;
         event < static_cast<CGenericModel*>(getUnitModel())->m_AnimationEvents.size(); ++event) {
        CKeyframe* key = static_cast<CGenericModel*>(getUnitModel())->m_AnimationEvents[event];
        if (!key || (key->m_theme && !hasUnitTheme(key->m_theme))) continue;
        switch (key->m_iEventCode) {
        case 3:
        case 27:
            if (m_secondarySound) {
                key = m_pUnitModel->m_AnimationEvents[event];
                if (m_pUnitModel->getValueIndexes(key->m_animationIndex, key)->size()) {
                    Ogre::SceneNode* node = key->m_iEventCode == 27 ? NULL : m_pSceneNode;
                    key = m_pUnitModel->m_AnimationEvents[event];
                    m_secondarySound->playSample((*m_pUnitModel->getValueIndexes(key->m_animationIndex, key))[0], node, 0.0f, 0.0f, false);
                }
            }
            break;
        case 4:
        case 5:
            if (key->m_animationIndex != static_cast<unsigned int>(-1)) {
                for (unsigned int i = 0; i < m_pUnitModel->getValueIndexes(key->m_animationIndex, key)->size(); ++i) {
                    unsigned int index = (*m_pUnitModel->getValueIndexes(key->m_animationIndex, key))[i];
                    if (index >= m_particleTriggers.size() || !m_particleTriggers[index]->m_particle) continue;
                    if ((!m_particleTriggers[index]->m_stopWhenHidden || m_particleTriggers[index]->m_stopFlag59) &&
                        m_particleTriggers[index]->m_nodeOwner) {
                        Ogre::Vector3 bonePosition = m_particleTriggers[index]->m_nodeOwner->_getDerivedPosition();
                        Ogre::Vector3 modelPosition = m_pUnitModel->getPosition(false);
                        Ogre::Vector3 position = getPosition(true);
                        CParticleAnimationTrigger* trigger = m_particleTriggers[index];
                        Ogre::Vector3 local(bonePosition.x + trigger->m_offset.x,
                                            bonePosition.y + trigger->m_offset.y,
                                            bonePosition.z + trigger->m_offset.z);
                        const Ogre::Matrix4& orientation = getOrientation();
                        float inverseW = 1.0f / (orientation[3][0]*local.x + orientation[3][1]*local.y + orientation[3][2]*local.z + orientation[3][3]);
                        Ogre::Vector3 result(
                            (orientation[0][0]*local.x + orientation[0][1]*local.y + orientation[0][2]*local.z + orientation[0][3])*inverseW + position.x + modelPosition.x,
                            (orientation[1][0]*local.x + orientation[1][1]*local.y + orientation[1][2]*local.z + orientation[1][3])*inverseW + position.y + modelPosition.y,
                            (orientation[2][0]*local.x + orientation[2][1]*local.y + orientation[2][2]*local.z + orientation[2][3])*inverseW + position.z + modelPosition.z);
                        m_particleTriggers[index]->m_particle->CPositionableObject::setPosition(result);
                    } else if (!m_particleTriggers[index]->m_stopWhenHidden) {
                        CParticleAnimationTrigger* trigger = m_particleTriggers[index];
                        const Ogre::Matrix4& orientation = getOrientation();
                        Ogre::Vector3 local = trigger->m_offset;
                        float inverseW = 1.0f / (orientation[3][0]*local.x + orientation[3][1]*local.y + orientation[3][2]*local.z + orientation[3][3]);
                        Ogre::Vector3 rotated(
                            (orientation[0][0]*local.x + orientation[0][1]*local.y + orientation[0][2]*local.z + orientation[0][3])*inverseW,
                            (orientation[1][0]*local.x + orientation[1][1]*local.y + orientation[1][2]*local.z + orientation[1][3])*inverseW,
                            (orientation[2][0]*local.x + orientation[2][1]*local.y + orientation[2][2]*local.z + orientation[2][3])*inverseW);
                        Ogre::Vector3 modelPosition = m_pUnitModel->getPosition(false);
                        Ogre::Vector3 position = getPosition(true);
                        Ogre::Vector3 result(position.x + modelPosition.x + rotated.x,
                                             position.y + modelPosition.y + rotated.y,
                                             position.z + modelPosition.z + rotated.z);
                        m_particleTriggers[index]->m_particle->CPositionableObject::setPosition(result);
                    } else {
                        CParticleAnimationTrigger* trigger = m_particleTriggers[index];
                        trigger->m_particle->CPositionableObject::setPosition(trigger->m_offset);
                    }
                    m_particleTriggers[index]->m_particle->Start();
                }
            }
            break;
        case 6:
            incrementJournalStatistic(static_cast<EJournalStatistic>(3), 1);
            if (m_levelSound) m_levelSound->playSample(0, m_pSceneNode, 0.0f, 0.0f, false);
            break;
        case 7: {
            key = m_pUnitModel->m_AnimationEvents[event];
            int mode = key->m_mode;
            if (!m_attackItem) {
                unsigned int trail = mode < 2 ? 0 : 1;
                if (!m_weaponTrails[trail]) {
                    Ogre::SceneManager* scene = m_pResourceManager ? m_pResourceManager->getSceneManager() : NULL;
                    m_weaponTrails[trail] = new CWeaponTrail(scene, STRINGS::uniqueName("trail_"), 20, 1.0f);
                    m_weaponTrails[trail]->setMaterialName(alignment() == static_cast<EAlignment>(1) ? "WeaponTrail" : "WeaponTrailEvil");
                    key = m_pUnitModel->m_AnimationEvents[event];
                }
                std::string nodeName = key->m_name;
                if (nodeName != EMPTY_STRING && static_cast<CGenericModel*>(getUnitModel())->m_pSkeleton->hasBone(nodeName)) {
                    Ogre::Bone* bone = static_cast<CGenericModel*>(getUnitModel())->m_pSkeleton->getBone(nodeName);
                    if (bone) m_weaponTrails[trail]->setWeaponNode(bone);
                    m_weaponTrails[trail]->setActive(true);
                    key = m_pUnitModel->m_AnimationEvents[event];
                    std::memcpy(&m_weaponTrails[trail]->m_positionOffset, &key->m_offset, 12);
                }
                key = m_pUnitModel->m_AnimationEvents[event];
            } else if (m_pInventory) {
                CEquipment* left = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1));
                CWeaponTrail* active = NULL;
                if (mode < 2) {
                    if (m_weaponTrails[0] && m_attackItem &&
                        m_attackItem == m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0)) &&
                        !m_attackItem->ISA(static_cast<UNITTYPES::EUNITTYPES>(102))) {
                        m_weaponTrails[0]->setWeaponEntity(static_cast<CGenericModel*>(m_attackItem->getUnitModel())->getEntity());
                        m_weaponTrails[0]->setActive(true);
                        active = m_weaponTrails[0];
                    }
                } else {
                    if (!m_weaponTrails[1]) {
                        Ogre::SceneManager* scene = m_pResourceManager ? m_pResourceManager->getSceneManager() : NULL;
                        m_weaponTrails[1] = new CWeaponTrail(scene, STRINGS::uniqueName("trail_"), 20, 1.0f);
                        m_weaponTrails[1]->setMaterialName(alignment() == static_cast<EAlignment>(1) ? "WeaponTrail" : "WeaponTrailEvil");
                    }
                    if (mode == 2 && m_weaponTrails[1] && left && !left->ISA(static_cast<UNITTYPES::EUNITTYPES>(102))) {
                        m_weaponTrails[1]->setWeaponEntity(static_cast<CGenericModel*>(left->getUnitModel())->getEntity());
                        m_weaponTrails[1]->setActive(true);
                        active = m_weaponTrails[1];
                    }
                }
                if (active) std::memset(&active->m_positionOffset, 0, 12);
                key = m_pUnitModel->m_AnimationEvents[event];
            }
            std::string material = STRINGS::StringConvertToNarrow(key->m_text.c_str());
            if (material.empty()) {
                if (m_weaponTrails[0]) m_weaponTrails[0]->setMaterialName(alignment() == static_cast<EAlignment>(1) ? "WeaponTrail" : "WeaponTrailEvil");
                if (m_weaponTrails[1]) m_weaponTrails[1]->setMaterialName(alignment() == static_cast<EAlignment>(1) ? "WeaponTrail" : "WeaponTrailEvil");
            } else {
                if (!Ogre::MaterialManager::getSingleton().resourceExists(material)) {
                    Ogre::MaterialPtr created = Ogre::MaterialManager::getSingleton().create(material, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
                    created->setReceiveShadows(false);
                    created->setLightingEnabled(false);
                    Ogre::Pass* pass = created->getTechnique(0)->getPass(0);
                    pass->setDepthCheckEnabled(false);
                    pass->setSelfIllumination(0.0f, 0.0f, 0.0f);
                    pass->setDepthWriteEnabled(false);
                    created->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
                    created->setCullingMode(Ogre::CULL_NONE);
                    pass->createTextureUnitState(material);
                    if (m_weaponTrails[0]) m_weaponTrails[0]->setMaterialName(material);
                    if (m_weaponTrails[1]) m_weaponTrails[1]->setMaterialName(material);
                } else {
                    if (m_weaponTrails[0]) m_weaponTrails[0]->setMaterialName(material);
                    if (m_weaponTrails[1]) m_weaponTrails[1]->setMaterialName(material);
                }
            }
            break;
        }
        case 8:
            if (m_pInventory) {
                if (m_pSkillManager) m_pSkillManager->hideWeaponTrailsOnCurrentSkill();
                int mode = m_pUnitModel->m_AnimationEvents[event]->m_mode;
                CEquipment* left = m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1));
                bool hide = false;
                unsigned int trail = mode < 2 ? 0 : 1;
                if (!m_attackItem) hide = m_weaponTrails[trail] && m_weaponTrails[trail]->isVisible();
                else if (mode < 2)
                    hide = m_weaponTrails[0] && m_attackItem == m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0)) && !m_attackItem->ISA(static_cast<UNITTYPES::EUNITTYPES>(102));
                else hide = mode == 2 && left && m_weaponTrails[1] && !left->ISA(static_cast<UNITTYPES::EUNITTYPES>(102));
                if (hide) { m_weaponTrails[trail]->setActive(false); m_weaponTrails[trail]->setVisible(false); }
            }
            break;
        case 9:
            if (m_attack && m_levelSound) {
                CSoundBank* bank = m_levelSound;
                if (m_attack->m_bUnknown18) bank = m_attackItem ? m_attackItem->m_pSoundBank : NULL;
                if (bank) bank->playSample(10, m_pSceneNode, 0.0f, 0.0f, false);
            }
            break;
        case 10: m_bBlocksPath = true; m_bPathingFlag19C = true; break;
        case 11: m_bBlocksPath = false; break;
        case 12: {
            const std::string& name = m_pUnitModel->m_AnimationEvents[event]->m_name;
            if (name == EMPTY_STRING) {
                for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
                    if (m_particleTriggers[i]->m_animationIndex != -1)
                        m_particleTriggers[i]->m_particle->Stop(!m_particleTriggers[i]->m_particle->getVisible());
            } else {
                for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
                    if (m_particleTriggers[i]->m_name == m_pUnitModel->m_AnimationEvents[event]->m_name)
                        m_particleTriggers[i]->m_particle->Stop(!m_particleTriggers[i]->m_particle->getVisible());
            }
            break;
        }
        case 13:
            for (unsigned int i = 0; i < m_particleTriggers.size(); ++i)
                if (m_particleTriggers[i]->m_animationIndex == static_cast<int>(m_pUnitModel->m_AnimationEvents[event]->m_animationIndex))
                    m_particleTriggers[i]->m_particle->Stop(!m_particleTriggers[i]->m_particle->getVisible());
            break;
        case 14:
        case 26:
            if (m_pUnitModel->m_AnimationEvents[event]->m_cameraShake) {
                CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
                CGameClient* client = level->m_pGameClient;
                Ogre::Vector3 position = getPosition(true);
                float x = position.x - client->m_audioListenerPosition.x;
                float y = position.y - client->m_audioListenerPosition.y;
                float z = position.z - client->m_audioListenerPosition.z;
                float magnitude = sqrtf(x*x + y*y + z*z) / -9.0f + 1.0f + 0.1f;
                magnitude = magnitude > 0.0f ? magnitude : 0.0f;
                if (static_cast<CGenericModel*>(getUnitModel())->m_AnimationEvents[event]->m_iEventCode == 26) {
                    magnitude = 1.0f;
                    m_pUnitModel->m_AnimationEvents[event]->m_cameraShake->m_bCameraFallsOffWithDistance = false;
                }
                m_pUnitModel->m_AnimationEvents[event]->m_cameraShake->m_fMagnitudeMultiplier = magnitude;
                position = getPosition(true);
                CCameraShake* shake = m_pUnitModel->m_AnimationEvents[event]->m_cameraShake;
                shake->m_fCameraPositionX = position.x; shake->m_fCameraPositionY = position.y; shake->m_fCameraPositionZ = position.z;
                shake->m_bCameraShakeActive = true;
                shake = m_pUnitModel->m_AnimationEvents[event]->m_cameraShake;
                CCameraControl* camera = m_pResourceManager->getCameraControl();
                TSafePointer<CCameraShake>* safe = new TSafePointer<CCameraShake>;
                safe->setObject(shake);
                camera->m_cameraShakesSecondary.add(safe);
            }
            break;
        case 16: m_damageShapeEnabled = false; break;
        case 17: m_damageShapeEnabled = true; break;
        case 18: m_moveSpeed = 0.0f; m_movement.x *= 0.0f; m_movement.y *= 0.0f; m_movement.z *= 0.0f; break;
        case 19: m_moveSpeed = 1.0f; break;
        case 20:
            m_weaponsHidden = false;
            if (m_pRightHandNode) {
                if (m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0)))
                    m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0))->setElementalParticlesEnabled(true);
                m_pRightHandNode->setVisible(true, true);
            }
            if (m_pLeftHandNode) {
                if (m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1)))
                    m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1))->setElementalParticlesEnabled(true);
                m_pLeftHandNode->setVisible(true, true);
            }
            break;
        case 21:
            m_weaponsHidden = true;
            if (m_pRightHandNode) {
                m_pRightHandNode->setVisible(false, true);
                if (m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0)))
                    m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0))->setElementalParticlesEnabled(false);
            }
            if (m_pLeftHandNode) {
                m_pLeftHandNode->setVisible(false, true);
                if (m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1)))
                    m_pInventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1))->setElementalParticlesEnabled(false);
            }
            break;
        case 22: setVisible(false, true); m_forcedHidden = true; break;
        case 23: m_forcedHidden = false; setVisible(true, true); break;
        case 24: setVisible(false, false); m_forcedHidden = true; break;
        case 25: m_forcedHidden = false; setVisible(true, false); break;
        default: break;
        }
    }
    if (m_attack && m_attackTime > 0.2f) return;
    if (m_activeSkill && (m_skillLooping || (m_skillTime > 0.0f && !m_skillInterrupted))) return;
    if (m_eAIState == static_cast<EAIState>(5) || m_eAIState == static_cast<EAIState>(6) || m_aiType == 6) return;
    float movementEffect = getEffectValue(static_cast<EEFFECT_TYPE>(21), static_cast<EDAMAGE_TYPES>(7));
    if (movementEffect > 100.0f) movementEffect = 100.0f;
    else {
        if (movementEffect < 0.0f) {
            float resistance = getEffectValue(static_cast<EEFFECT_TYPE>(140), static_cast<EDAMAGE_TYPES>(7)) / 100.0f;
            if (resistance >= 1.0f) resistance = 1.0f;
            else if (resistance <= 0.0f) resistance = 0.0f;
            movementEffect *= 1.0f - resistance;
        }
        if (movementEffect < -100.0f) movementEffect = -100.0f;
    }
    float multiplier = movementEffect / 100.0f + 1.0f;
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(1))) multiplier *= 1.5f;
    bool running = m_returningToTown;
    if (m_pMaster && !ISA(static_cast<UNITTYPES::EUNITTYPES>(169))) {
        if (!m_returningToTown) running = false;
        else if (m_runningSpeed > m_walkingSpeed && runningSpeed() > 0.0f) {
            float ownSpeed = runningSpeed();
            float masterSpeed = m_pMaster->runningSpeed();
            if (!(masterSpeed + 2.0f <= ownSpeed) && movementEffect >= 0.0f && m_canMatchSpeed) {
                if (runningSpeed() > 0.0f) {
                    masterSpeed = m_pMaster->runningSpeed();
                    ownSpeed = runningSpeed();
                    multiplier = (masterSpeed + 2.0f) / ownSpeed;
                } else multiplier = 0.0f;
            }
        }
    }
    float animationSpeed = multiplier * (running && m_runningSpeed > m_walkingSpeed ? m_runAnimationMult : m_walkAnimationMult);
    if (multiplier < 0.1f) multiplier = 0.1f;
    if (animationSpeed < 0.1f) animationSpeed = 0.1f;
    bool playIdleSound = false;
    if (m_eAIState != static_cast<EAIState>(35)) {
        if (!m_isPathing) {
            if (static_cast<unsigned int>(m_eAIState) - 32 < 3) {
                if (m_fishingNode) m_fishingNode->setVisible(true, true);
            } else if (m_eAIState != static_cast<EAIState>(16) && m_eAIState != static_cast<EAIState>(12) &&
                       !m_pResourceManager->getEditorIsRunning()) {
                if (m_turnFlag265 && m_pUnitModel->animationExists("WALK")) {
                    if (!m_pUnitModel->animationPlaying("WALK"))
                        blendAnimation("WALK", true, 0.2f, (1.0f / m_vScale.z) * animationSpeed, -1.0f);
                    else if (animationSpeed != m_lastAnimationSpeed)
                        m_pUnitModel->setAnimationSpeed("WALK", (1.0f / m_vScale.z) * animationSpeed);
                } else if (m_eAIState == static_cast<EAIState>(40) && m_pUnitModel->animationExists("STUNNED")) {
                    if (!m_pUnitModel->animationPlaying("STUNNED") && !m_pUnitModel->animationQueued("STUNNED"))
                        blendAnimation("STUNNED", true, 0.2f, 1.0f, -1.0f);
                } else if (ISA(static_cast<UNITTYPES::EUNITTYPES>(167)) && hasUnitTheme(L"MIMICIDLE") &&
                           m_pUnitModel->animationExists("ASLEEP")) {
                    if (!m_pUnitModel->animationPlaying("ASLEEP") && !m_pUnitModel->animationQueued("ASLEEP"))
                        blendAnimation("ASLEEP", true, 0.2f, 1.0f, -1.0f);
                } else if (!m_pUnitModel->animationPlaying("IDLE") && !m_pUnitModel->animationQueued("IDLE"))
                    blendAnimation("IDLE", true, 0.2f, 1.0f, -1.0f);
                playIdleSound = m_idleSoundTime > 10.0f;
            }
        } else {
            bool allow = !m_activeSkill || !m_activeSkill->m_stopsPathingOnCompletion ||
                (m_activeSkill->m_animationIndexLoopInto != -1 && !m_activeSkill->m_interruptible);
            if (!allow) allow = !m_skillLooping && m_skillTime <= 0.0f;
            if (m_eAIState != static_cast<EAIState>(16) && allow) {
                bool runAnimation = running && m_runningSpeed > m_walkingSpeed;
                std::string animation;
                if (runAnimation) animation = m_pUnitModel->animationExists("RUN") ? "RUN" : "WALK";
                else animation = m_pUnitModel->animationExists("WALK") ? "WALK" : "RUN";
                if (!m_pUnitModel->animationPlaying(animation))
                    blendAnimation(animation, true, 0.2f, (1.0f / m_vScale.z) * animationSpeed, -1.0f);
                else if (animationSpeed != m_lastAnimationSpeed)
                    m_pUnitModel->setAnimationSpeed(animation, (1.0f / m_vScale.z) * animationSpeed);
                if (!runAnimation) playIdleSound = m_idleSoundTime > 8.0f && m_eAIState == static_cast<EAIState>(2);
            }
        }
    }
    if (playIdleSound && m_levelSound && std::rand() % 1000 < 5) {
        m_levelSound->playSample(11, m_pSceneNode, 0.0f, 0.0f, false);
        m_idleSoundTime = 0.0f;
    }
    m_lastAnimationSpeed = animationSpeed;
    m_animationSpeedMultiplier = multiplier;
}
