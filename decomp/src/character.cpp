#include "Wardrobe.h"
#include "AIManager.h"
#include <CEGUIWindow.h>
#include "Character.h"
#include "EffectManager.h"
#include "EmptyStrings.h"
#include "GenericModel.h"
#include "Inventory.h"
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
    CCharacter* pMaster = this;
    while (pMaster->m_pMaster)
        pMaster = pMaster->m_pMaster;

    if (amount > 0)
    {
        pMaster->incrementJournalStatistic(static_cast<EJournalStatistic>(1), amount);
        if (pMaster->m_iGold > amount + pMaster->m_iGold)
            pMaster->m_iGold = 0x7fffffff;
        else
            pMaster->m_iGold += amount;
    }
    else
    {
        pMaster->m_iGold += amount;
    }

    pMaster->m_iGold = pMaster->m_iGold < 0 ? 0 : pMaster->m_iGold;
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


// Imported source candidates; historical status is not fresh acceptance.
void CCharacter::setVisible(bool visible)
{
    m_characterVisible = (!m_forcedHidden) & visible;
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

void CCharacter::queueBlendAnimation(const std::string& animation, bool loop, float blend, float speed)
{
    if (m_pUnitModel) m_pUnitModel->queueBlendAnimation(animation, loop, blend, speed);
}

bool CCharacter::animationExists(const std::string& animation) const
{
    return m_pUnitModel ? m_pUnitModel->animationExists(animation) : false;
}

bool CCharacter::animationQueued(const std::string& animation) const
{
    return m_pUnitModel ? m_pUnitModel->animationQueued(animation) : false;
}

bool CCharacter::animationPlaying(const std::string& animation) const
{
    return m_pUnitModel ? m_pUnitModel->animationPlaying(animation) : false;
}

bool CCharacter::isImmobile()
{
    return hasEffect(static_cast<EEFFECT_TYPE>(0x3f)) || m_moveSpeed == 0.0f;
}

void CCharacter::forceDisplayOfDamageAbsorbed()
{
    displayDamageAbsorbed(10000.0f);
}

void CCharacter::updateSkill(float elapsed)
{
    if (m_pInventory) m_pInventory->updateSkillManagers(elapsed);
}

void CCharacter::destroyIcons()
{
    if (m_pInventory) m_pInventory->destroyIcons();
}

void CCharacter::toggleSecondaryWeaponSet()
{
    m_pInventory->swapWeaponSet();
    m_bSecondaryWeaponSet = !m_bSecondaryWeaponSet;
}

float CCharacter::getEffectValueWithoutInventory(EEFFECT_TYPE type, EDAMAGE_TYPES damage)
{
    return m_pEffectManager ? m_pEffectManager->getEffectValue(type, damage) : 0.0f;
}

int CCharacter::minimumAC()
{
    return static_cast<int>(ceilf(static_cast<float>(AC()) * 0.5f));
}

void CCharacter::clearAllUnitReferences()
{
    setTarget(NULL);
}

bool CCharacter::facingTarget()
{
    if (m_targetCharacter || m_targetItem) return facingTarget(m_targetCharacter, m_targetItem);
    return false;
}

void CCharacter::stopPathing()
{
    if (m_isPathing) m_pathGraceTime = 10.0f;
    m_isPathing = false;
    m_pathDestination = m_vPosition;
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

std::wstring CCharacter::getWardrobeChestMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[0];
    return EMPTY_WSTRING;
}

void CCharacter::setWardrobeChestMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[0].assign(copied); }
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

std::wstring CCharacter::getWardrobeChestTexture()
{
    if (m_wardrobe) return m_wardrobe->m_textures[0];
    return EMPTY_WSTRING;
}

void CCharacter::setWardrobeChestTexture(std::wstring value)
{
    if (m_wardrobe) {
        m_wardrobe->setBaseTexture(static_cast<EWardrobeSlot>(0), value);
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

std::wstring CCharacter::getWardrobeGlovesMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[1];
    return EMPTY_WSTRING;
}

void CCharacter::setWardrobeGlovesMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[1].assign(copied); }
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

std::wstring CCharacter::getWardrobeGlovesTexture()
{
    if (m_wardrobe) return m_wardrobe->m_textures[1];
    return EMPTY_WSTRING;
}

void CCharacter::setWardrobeGlovesTexture(std::wstring value)
{
    if (m_wardrobe) {
        m_wardrobe->setBaseTexture(static_cast<EWardrobeSlot>(1), value);
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

std::wstring CCharacter::getWardrobeBootsMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[2];
    return EMPTY_WSTRING;
}

void CCharacter::setWardrobeBootsMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[2].assign(copied); }
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

std::wstring CCharacter::getWardrobeBootsTexture()
{
    if (m_wardrobe) return m_wardrobe->m_textures[2];
    return EMPTY_WSTRING;
}

void CCharacter::setWardrobeBootsTexture(std::wstring value)
{
    if (m_wardrobe) {
        m_wardrobe->setBaseTexture(static_cast<EWardrobeSlot>(2), value);
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

std::wstring CCharacter::getWardrobeHelmMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[3];
    return EMPTY_WSTRING;
}

void CCharacter::setWardrobeHelmMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[3].assign(copied); }
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

std::wstring CCharacter::getWardrobeHelmTexture()
{
    if (m_wardrobe) return m_wardrobe->m_textures[3];
    return EMPTY_WSTRING;
}

void CCharacter::setWardrobeHelmTexture(std::wstring value)
{
    if (m_wardrobe) {
        m_wardrobe->setBaseTexture(static_cast<EWardrobeSlot>(3), value);
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

std::wstring CCharacter::getWardrobeShoulderMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[4];
    return EMPTY_WSTRING;
}

void CCharacter::setWardrobeShoulderMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[4].assign(copied); }
        m_wardrobe->update(m_pInventory);
        getBones();
    }
}

std::wstring CCharacter::getModelPath()
{
    if (m_pUnitModel) return m_pUnitModel->m_sModelPath;
    return EMPTY_WSTRING;
}
