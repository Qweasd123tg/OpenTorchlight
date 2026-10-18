#include "BaseUnit.h"
#include "Character.h"
#include "EmptyStrings.h"
#include "Skill.h"
#include "SkillManager.h"
#include "SkillProperty.h"
#include "Utilities.h"
#include <math.h>


// Imported source candidates; historical status is not fresh acceptance.
const std::wstring& CSkill::getSkillRequiredForInvestment()
{
    return m_sRequiredSkill;
}

bool CSkill::getCanStop()
{
    return !m_property || m_elapsedSkillTime >= m_property->m_fMinimumTime;
}

bool CSkill::getIsExclusive()
{
    return m_property ? m_property->m_bExclusive : false;
}

bool CSkill::getCanBeInterrupted()
{
    return m_property ? m_property->m_bInterruptable : false;
}

unsigned int CSkill::getManaCost()
{
    return m_property ? static_cast<unsigned int>(m_property->m_iManaCost) : 0;
}

unsigned int CSkill::getManaCostOT()
{
    return m_property ? static_cast<unsigned int>(m_property->m_iManaCostOverTime) : 0;
}

bool CSkill::getRequiresPathable()
{
    return m_property ? m_requiresPathable : false;
}

const std::wstring& CSkill::getSkillIcon()
{
    return m_property ? m_property->m_sSkillIcon : EMPTY_WSTRING;
}

const std::wstring& CSkill::getSkillIconInactive()
{
    return m_property ? m_property->m_sSkillIconInactive : EMPTY_WSTRING;
}

const std::wstring& CSkill::getName()
{
    return m_property ? m_property->m_sName : EMPTY_WSTRING;
}

const std::wstring& CSkill::getSkillUsageDescription()
{
    return m_property ? m_property->m_sUsageDescription : EMPTY_WSTRING;
}

const std::wstring& CSkill::getDisplayName()
{
    return m_property ? m_property->m_sDisplayName : EMPTY_WSTRING;
}

int CSkill::getAnimationIndex()
{
    return m_property ? m_animationIndex : static_cast<unsigned int>(-1);
}

unsigned int CSkill::getAnimationIndexDW()
{
    return m_property ? m_animationIndexDW : static_cast<unsigned int>(-1);
}

unsigned int CSkill::getAnimationIndexLoopInto()
{
    return m_property ? m_animationIndexLoopInto : static_cast<unsigned int>(-1);
}

int CSkill::getAnimationIndexLoopEnd()
{
    return m_property ? m_animationIndexLoopEnd : static_cast<unsigned int>(-1);
}

unsigned int CSkill::getAnimationIndexDWLoopInto()
{
    return m_property ? m_animationIndexDWLoopInto : static_cast<unsigned int>(-1);
}

unsigned int CSkill::getChanceToCast()
{
    return m_property ? m_property->m_iChance : static_cast<unsigned int>(-1);
}

float CSkill::getAnimationSpeedMult()
{
    return m_property ? m_property->m_fSpeed : 4294967296.0f;
}

float CSkill::getFindTargetAngle()
{
    return m_property ? m_property->m_fFindTargetAngle : 0.0f;
}

float CSkill::getRange()
{
    return m_property ? m_property->m_fRange : 1.0f;
}

float CSkill::getRangeMin()
{
    return m_property ? m_property->m_iMinimumRange : 0.0f;
}

float CSkill::getRandomRange()
{
    return m_property ? m_property->m_fRandomRange : 1.0f;
}

float CSkill::getRandomRangeMin()
{
    return m_property ? m_property->m_iRandomRangeMinimum : 0.0f;
}

float CSkill::getMinimumTime()
{
    return m_property ? m_property->m_fMinimumTime : 1.0f;
}

CBaseUnit* CSkill::getMasterOwner()
{
    return m_pSkillManager ? m_pSkillManager->m_Owner.getObject() : NULL;
}

CCharacter* CSkill::getOwnerCharacter()
{
    if (m_pOwner && m_pOwner->m_eBaseUnitType == 0)
        return dynamic_cast<CCharacter*>(m_pOwner);
    return NULL;
}

bool CSkill::canAffixesAndEffectsBeAppliedToUnit(CBaseUnit* unit, CCharacter* character)
{
    if (!m_property) return false;
    CSkillProperty* property = m_property;
    if (!character) character = getOwnerCharacter();
    return property->canAffixesAndEffectsBeAppliedToUnit(unit, character);
}

float CSkill::getCoolDown()
{
    return m_property ? m_property->getCoolDown() : 1.0f;
}

int CSkill::getMaximumDamage()
{
    if (!m_property) return 0;
    float minimum = 0.0f;
    float maximum = 0.0f;
    m_property->addMinAndMaxValuesOfAnEffect(m_resources, 0x34, minimum, maximum);
    return static_cast<int>(ceilf(maximum));
}

int CSkill::getMinimumDamage()
{
    if (!m_property) return 0;
    float minimum = 0.0f;
    float maximum = 0.0f;
    m_property->addMinAndMaxValuesOfAnEffect(m_resources, 0x34, minimum, maximum);
    return static_cast<int>(ceilf(minimum));
}

bool CSkill::rollCancelChance()
{
    if (m_iCancelChance > 99) return true;
    return UTILITIES::randomIntegerBetweenVolatile(0, 100) <= m_iCancelChance;
}

bool CSkill::rollCastChance()
{
    if (m_iChance > 99) return true;
    return UTILITIES::randomIntegerBetweenVolatile(0, 100) <= m_iChance;
}

void CSkill::fillOutStatBonuses(float (&bonuses)[6], bool includeBase, unsigned int level)
{
    CSkillProperty* property = m_property;
    if (level > 0 && level != static_cast<unsigned int>(-1) && level <= m_iSkillLevelCount)
        property = (*reinterpret_cast<TArrayList<CSkillProperty*>*>(&m_levelPropertyData))[level - 1];
    if (property) property->fillOutStatBonuses(bonuses, includeBase);
}

#include "ResourceManager.h"
#include "Level.h"
#include "EffectManager.h"
#include "Equipment.h"
#include "StringTranslate.h"
#include "StringUtilities.h"

unsigned int CSkill::getLevelRequiredForInvestment()
{
    CSkillProperty* property = m_iSkillLevelCount ? m_levelPropertyData[0] : m_property;
    unsigned int maximum = m_iSkillLevelCount ? m_iSkillLevelCount : 1;
    if (static_cast<int>(m_skillLevel) <= static_cast<int>(maximum) &&
        static_cast<int>(m_skillLevel) < static_cast<int>(m_iSkillLevelCount))
    {
        unsigned int index = m_skillLevel < m_levelPropertyCapacity ? m_skillLevel : 0;
        if (m_levelPropertyData[index])
            property = m_levelPropertyData[index];
    }
    return property && property->m_iLevelRequired ? property->m_iLevelRequired : m_iRequiredLevel + m_skillLevel;
}

bool CSkill::hasEvent(ESKILL_EVENT_TYPE event)
{
    if (!m_property)
        return true;
    if (static_cast<unsigned int>(event) > 10)
        return false;
    TArrayList<CSkillEvent*>* events = m_property->m_eventLists[event];
    return events && events->size();
}

int CSkill::getTargetType()
{
    return m_property ? m_property->m_eTargetType : 0;
}

int CSkill::getUnitTypeToTarget()
{
    return m_property ? m_property->m_eTargetUnitType : 0;
}

CCharacter* CSkill::getMasterOwnerCharacter()
{
    if ((!m_pOwner || m_pOwner->m_eBaseUnitType == static_cast<EBASEUNIT_TYPE>(0)) && m_pSkillManager)
        return dynamic_cast<CCharacter*>(m_pSkillManager->m_Owner.getObject());
    return NULL;
}

bool CSkill::getIsInRange(const Ogre::Vector3& from, const Ogre::Vector3& to,
                        CBaseUnit* caster, CBaseUnit* target)
{
    float distance = (from - to).length();
    if (m_requiresLineOfSight && m_resources->getLevel())
    {
        if (caster)
            caster->removeFromAvoidanceMap(*m_resources->getLevel());
        if (target)
            target->removeFromAvoidanceMap(*m_resources->getLevel());
        bool passable = m_resources->getLevel()->passableBetween(from, to, false);
        if (caster)
            caster->addToAvoidanceMap(*m_resources->getLevel());
        if (target)
            target->addToAvoidanceMap(*m_resources->getLevel());
        if (!passable)
            return false;
    }
    if (!(distance >= (m_property ? m_property->m_iMinimumRange : 0.0f)))
        return false;
    return distance <= (m_property ? m_property->m_fRange : 1.0f);
}

bool CSkill::getTargetIsValid(CCharacter* target, CCharacter* caster,
                             const Ogre::Vector3*, bool dead)
{
    CCharacter* unit = m_property && m_property->m_eTargetType == 3 ? caster : target;
    if (!unit)
        return false;
    if (dead || m_targetsDead)
    {
        if (unit->HP() > 0)
            return false;
    }
    else if (unit->HP() <= 0)
        return false;
    if (m_property && m_property->m_eTargetUnitType &&
        !unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_property->m_eTargetUnitType)))
        return false;
    if (m_allowedTargetData.size())
    {
        bool found = false;
        for (unsigned int i = 0; i < m_allowedTargetData.size(); ++i)
            if (unit->m_pDataGroup == m_allowedTargetData[i])
            {
                found = true;
                break;
            }
        if (!found)
            return false;
    }
    if (m_property)
    {
        if (m_property->m_eTargetType == 10)
        {
            if (unit == caster || unit->m_pMaster == caster ||
                (caster && caster->m_pMaster && caster->m_pMaster == unit))
                return true;
        }
        else if (m_property->m_eTargetType == 9 && unit->m_pMaster == caster)
            return true;
    }
    if (caster->alignment() == 0)
        return false;
    if (m_property && m_property->m_eTargetType == 4)
        return true;
    bool enemy = caster->isEnemy(unit);
    if (caster->alignment() == 4)
        return true;
    if (m_iTargetAlignment == 2)
        return enemy;
    if (m_iTargetAlignment == 1)
        return !enemy;
    return false;
}

bool CSkill::weaponRequirementsMet(CCharacter* character)
{
    bool dual = m_property->m_bDuelWeaponRequired;
    CEquipment* right = character->getWeaponInRightHand();
    CEquipment* left = character->getWeaponInLeftHand();
    bool rightMatches = right && right->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_property->m_iRequirementRight));
    bool leftMatches = left && left->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_property->m_iRequirementLeft));
    if (dual)
        return rightMatches && leftMatches;
    if (rightMatches || !m_property->m_iRequirementRight)
        return true;
    if (left && left->ISA(static_cast<UNITTYPES::EUNITTYPES>(38)) &&
        left->ISA(static_cast<UNITTYPES::EUNITTYPES>(10)))
        return left->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_property->m_iRequirementRight));
    return false;
}

bool CSkill::rollSkillChance()
{
    if (!m_property || static_cast<unsigned int>(m_property->m_iChance) > 99)
        return true;
    unsigned int chance = UTILITIES::randomIntegerBetweenVolatile(0, 100);
    return !m_property || chance <= static_cast<unsigned int>(m_property->m_iChance);
}

std::wstring CSkill::getSkillLevelDescription(CBaseUnit* unit, unsigned int level)
{
    if (!m_property)
        return EMPTY_WSTRING;
    CBaseUnit* owner = m_pOwner;
    TSafePointer<CBaseUnit>* ownerReference = reinterpret_cast<TSafePointer<CBaseUnit>*>(&m_pOwner);
    ownerReference->setObject(unit);
    unsigned int index = level - 1;
    if (index > static_cast<unsigned int>(-3))
        index = m_iEffectiveSkillLevel - 1;
    CSkillProperty* property = m_iSkillLevelCount ? m_levelPropertyData[0] : m_property;
    unsigned int maximum = m_iSkillLevelCount ? m_iSkillLevelCount : 1;
    if (index <= maximum && index < m_iSkillLevelCount)
    {
        unsigned int slot = index < m_levelPropertyCapacity ? index : 0;
        if (m_levelPropertyData[slot])
            property = m_levelPropertyData[slot];
    }
    if (property)
        return property->getSkillDescription();
    ownerReference->setObject(owner);
    return EMPTY_WSTRING;
}

std::wstring CSkill::getSkillLevelStats(CBaseUnit* unit, unsigned int level)
{
    if (!m_property)
        return EMPTY_WSTRING;
    CBaseUnit* owner = m_pOwner;
    TSafePointer<CBaseUnit>* ownerReference = reinterpret_cast<TSafePointer<CBaseUnit>*>(&m_pOwner);
    ownerReference->setObject(unit);
    unsigned int index = level - 1;
    if (index > static_cast<unsigned int>(-3))
        index = m_iEffectiveSkillLevel - 1;
    CSkillProperty* property = m_iSkillLevelCount ? m_levelPropertyData[0] : m_property;
    unsigned int maximum = m_iSkillLevelCount ? m_iSkillLevelCount : 1;
    if (index <= maximum && index < m_iSkillLevelCount)
    {
        unsigned int slot = index < m_levelPropertyCapacity ? index : 0;
        if (m_levelPropertyData[slot])
            property = m_levelPropertyData[slot];
    }
    if (property)
        return property->getSkillStats();
    ownerReference->setObject(owner);
    return EMPTY_WSTRING;
}

int CSkill::getSkillLevelManaCostOT(CBaseUnit* unit, unsigned int level)
{
    if (!m_property)
        return 0;
    CBaseUnit* owner = m_pOwner;
    TSafePointer<CBaseUnit>* ownerReference = reinterpret_cast<TSafePointer<CBaseUnit>*>(&m_pOwner);
    ownerReference->setObject(unit);
    unsigned int index = level - 1;
    if (index > static_cast<unsigned int>(-3))
        index = m_iEffectiveSkillLevel - 1;
    CSkillProperty* property = m_iSkillLevelCount ? m_levelPropertyData[0] : m_property;
    unsigned int maximum = m_iSkillLevelCount ? m_iSkillLevelCount : 1;
    if (index <= maximum && index < m_iSkillLevelCount)
    {
        unsigned int slot = index < m_levelPropertyCapacity ? index : 0;
        if (m_levelPropertyData[slot])
            property = m_levelPropertyData[slot];
    }
    if (property)
        return static_cast<int>(property->m_iManaCostOverTime);
    ownerReference->setObject(owner);
    return 0;
}

int CSkill::getSkillLevelManaCost(CBaseUnit* unit, unsigned int level)
{
    if (!m_property)
        return 0;
    CBaseUnit* owner = m_pOwner;
    TSafePointer<CBaseUnit>* ownerReference = reinterpret_cast<TSafePointer<CBaseUnit>*>(&m_pOwner);
    ownerReference->setObject(unit);
    unsigned int index = level - 1;
    if (index > static_cast<unsigned int>(-3))
        index = m_iEffectiveSkillLevel - 1;
    CSkillProperty* property = m_iSkillLevelCount ? m_levelPropertyData[0] : m_property;
    unsigned int maximum = m_iSkillLevelCount ? m_iSkillLevelCount : 1;
    if (index <= maximum && index < m_iSkillLevelCount)
    {
        unsigned int slot = index < m_levelPropertyCapacity ? index : 0;
        if (m_levelPropertyData[slot])
            property = m_levelPropertyData[slot];
    }
    if (property)
        return static_cast<int>(property->m_iManaCost);
    ownerReference->setObject(owner);
    return 0;
}

int CSkill::getSkillLevelCooldown(CBaseUnit* unit, unsigned int level)
{
    if (!m_property)
        return 0;
    CBaseUnit* owner = m_pOwner;
    TSafePointer<CBaseUnit>* ownerReference = reinterpret_cast<TSafePointer<CBaseUnit>*>(&m_pOwner);
    ownerReference->setObject(unit);
    unsigned int index = level - 1;
    if (index > static_cast<unsigned int>(-3))
        index = m_iEffectiveSkillLevel - 1;
    CSkillProperty* property = m_iSkillLevelCount ? m_levelPropertyData[0] : m_property;
    unsigned int maximum = m_iSkillLevelCount ? m_iSkillLevelCount : 1;
    if (index <= maximum && index < m_iSkillLevelCount)
    {
        unsigned int slot = index < m_levelPropertyCapacity ? index : 0;
        if (m_levelPropertyData[slot])
            property = m_levelPropertyData[slot];
    }
    if (property)
        return static_cast<int>(property->getCoolDown());
    ownerReference->setObject(owner);
    return 0;
}

bool CSkill::calculateEffectiveSkillLevel()
{
    int level = m_skillLevel;
    CCharacter* character = getMasterOwnerCharacter();
    if (character && level)
    {
        level += static_cast<int>(character->getEffectValue(static_cast<EEFFECT_TYPE>(82), 0.0f,
                                        STRINGS::StringUpper(getName())));
        if (m_skillType == 2)
            level += static_cast<int>(character->getEffectValue(static_cast<EEFFECT_TYPE>(86), static_cast<EDAMAGE_TYPES>(7)));
        else if (m_skillType == 3)
            level += static_cast<int>(character->getEffectValue(static_cast<EEFFECT_TYPE>(87), static_cast<EDAMAGE_TYPES>(7)));
        else if (m_skillType == 1)
            level += static_cast<int>(character->getEffectValue(static_cast<EEFFECT_TYPE>(85), static_cast<EDAMAGE_TYPES>(7)));
        character = character->m_pMaster;
        if (character)
        {
            level += static_cast<int>(character->getEffectValue(static_cast<EEFFECT_TYPE>(82), 0.0f,
                                            STRINGS::StringUpper(getName())));
            if (m_skillType == 2)
                level += static_cast<int>(character->getEffectValue(static_cast<EEFFECT_TYPE>(86), static_cast<EDAMAGE_TYPES>(7)));
            else if (m_skillType == 3)
                level += static_cast<int>(character->getEffectValue(static_cast<EEFFECT_TYPE>(87), static_cast<EDAMAGE_TYPES>(7)));
            else if (m_skillType == 1)
                level += static_cast<int>(character->getEffectValue(static_cast<EEFFECT_TYPE>(85), static_cast<EDAMAGE_TYPES>(7)));
        }
    }
    int maximum = m_iSkillLevelCount ? m_iSkillLevelCount : 1;
    if (level >= maximum)
        level = maximum;
    if (static_cast<unsigned int>(level) == m_iEffectiveSkillLevel)
        return false;
    m_iEffectiveSkillLevel = level;
    _setLevelOfSkillFromSkillManager(m_skillLevel);
    return true;
}

void CSkill::_setLevelOfSkillFromSkillManager(unsigned int level)
{
    if (level == static_cast<unsigned int>(-1))
        m_skillLevel = 1;
    else
    {
        unsigned int maximum = m_iSkillLevelCount ? m_iSkillLevelCount : 1;
        m_skillLevel = level > maximum ? maximum : level;
    }
    calculateEffectiveSkillLevel();
    if (!m_iSkillLevelCount || !m_iEffectiveSkillLevel)
        m_property = m_baseProperty;
    else
    {
        unsigned int index = m_iEffectiveSkillLevel - 1;
        if (index >= m_iSkillLevelCount)
            index = m_iSkillLevelCount - 1;
        m_property = m_levelPropertyData[index < m_levelPropertyCapacity ? index : 0];
    }
}

void CSkill::unitStateChange(CBaseUnit* unit, EUNIT_STATES state)
{
    if (!unit)
        return;
    if (static_cast<int>(state) == 1)
        unit->getLevel()->removeListenerFromUnit(unit, this);
    else if (static_cast<int>(state) == 4)
    {
        unit->getLevel()->removeListenerFromUnit(unit, this);
        if (unit->m_pEffectManager && unit->m_pEffectManager->hasEffectFromSkill(this) && unit->getSceneNode())
        {
            CCharacter* character = dynamic_cast<CCharacter*>(unit);
            const Ogre::Quaternion& orientation = unit->getSceneNode()->getOrientation();
            Ogre::Vector3 position = unit->getPosition(true);
            triggerEvent(static_cast<ESKILL_EVENT_TYPE>(8), position, orientation, character, NULL);
        }
    }
}

CSkill::~CSkill()
{
    if (m_resources->getLevel())
        m_resources->getLevel()->removeListenerFromUnits(this);
    for (unsigned int i = m_iSkillLevelCount; i;)
    {
        --i;
        unsigned int slot = i < m_levelPropertyCapacity ? i : 0;
        if (m_levelPropertyData[slot])
        {
            delete m_levelPropertyData[i < m_levelPropertyCapacity ? i : 0];
            m_levelPropertyData[i < m_levelPropertyCapacity ? i : 0] = NULL;
        }
    }
    if (m_baseProperty)
    {
        delete m_baseProperty;
        m_baseProperty = NULL;
    }
    m_allowedTargetData.clear();
    m_iSkillLevelCount = 0;
    m_levelPropertyCapacity = 0;
    if (m_levelPropertyData)
        delete[] m_levelPropertyData;
    m_levelPropertyData = NULL;
    m_property = NULL;
    m_interruptible = false;
    if (m_pOwner)
    {
        m_pOwner->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&m_pOwner), m_iOwnerSafePointerId);
        m_pOwner = NULL;
    }
    m_iOwnerSafePointerId = static_cast<unsigned int>(-1);
}

std::wstring CSkill::getSkillTypeDisplayName()
{
    std::wstring name = EMPTY_WSTRING;
    switch (m_skillType)
    {
    case 0:
        {
            static std::wstring g_ClassSkill;
            if (g_ClassSkill.empty())
                g_ClassSkill = CStringTranslate::getSinglton()->getTranslateString(L"Class Skill");
            name = g_ClassSkill;
        }
        break;
    case 1:
        {
            static std::wstring g_OffensiveSpell;
            if (g_OffensiveSpell.empty())
                g_OffensiveSpell = CStringTranslate::getSinglton()->getTranslateString(L"Offensive Spell");
            name = g_OffensiveSpell;
        }
        break;
    case 2:
        {
            static std::wstring g_DefensiveSpell;
            if (g_DefensiveSpell.empty())
                g_DefensiveSpell = CStringTranslate::getSinglton()->getTranslateString(L"Defensive Spell");
            name = g_DefensiveSpell;
        }
        break;
    case 3:
        {
            static std::wstring g_CharmSpell;
            if (g_CharmSpell.empty())
                g_CharmSpell = CStringTranslate::getSinglton()->getTranslateString(L"Charm Spell");
            name = g_CharmSpell;
        }
        break;
    }
    return name;
}

bool CSkill::requirementsMet(CBaseUnit* caster, ESKILL_ACTIVATION_TYPE activation,
                             const Ogre::Vector3* targetPosition, CBaseUnit* target, bool ignoreRange)
{
    if (m_gAllowSkillTesting)
        return true;
    if (!m_bEnabled || !caster || !m_property)
        return false;
    if (activation != static_cast<ESKILL_ACTIVATION_TYPE>(0) &&
        m_eActivationType != activation && m_eActivationType != static_cast<ESKILL_ACTIVATION_TYPE>(0))
        return false;
    if (!m_iCharges)
        return false;
    if (m_property->m_pRequiredTheme && !caster->hasUnitTheme(m_property->m_pRequiredTheme))
        return false;
    if (m_property->m_pForbiddenTheme && caster->hasUnitTheme(m_property->m_pForbiddenTheme))
        return false;
    if (m_checksSilence && caster->m_pEffectManager &&
        caster->m_pEffectManager->hasEffect(static_cast<EEFFECT_TYPE>(128)))
        return false;
    int type = m_property->m_eTargetType;
    if (type == 2)
    {
        if (!target)
            return false;
        if (!ignoreRange)
        {
            Ogre::Vector3 targetPosition = target->getPosition(true);
            Ogre::Vector3 position = caster->getPosition(true);
            if (!getIsInRange(position, targetPosition, caster, target))
                return false;
        }
    }
    else if (type == 1)
    {
        if (!targetPosition)
            return false;
        if (!ignoreRange)
        {
            Ogre::Vector3 position = caster->getPosition(true);
            if (!getIsInRange(position, *targetPosition, caster, target))
                return false;
        }
    }
    else if (type == 7)
    {
        if (!target || !target->ISA(static_cast<UNITTYPES::EUNITTYPES>(2)))
            return false;
    }
    else if (type == 8 && target && target->ISA(static_cast<UNITTYPES::EUNITTYPES>(2)))
    {
        CEquipment* equipment = dynamic_cast<CEquipment*>(target);
        if (!equipment || equipment->m_bUnknown348)
            return false;
    }
    CCharacter* character = dynamic_cast<CCharacter*>(caster);
    return !character || weaponRequirementsMet(character);
}

bool CSkill::startSkill(CBaseUnit* caster, ESKILL_ACTIVATION_TYPE,
                       const Ogre::Vector3& position, const Ogre::Quaternion& orientation,
                       const Ogre::Vector3& targetPosition, CBaseUnit* target)
{
    if (!caster || !m_property)
        return false;
    m_pendingStop = false;
    assignSkillAnimations(caster);
    calculateEffectiveSkillLevel();
    if (!rollSkillChance())
        return false;
    reinterpret_cast<TSafePointer<CBaseUnit>*>(&m_pOwner)->setObject(caster);
    m_Target.setObject(target);
    m_targetPosition = targetPosition;
    if (m_pOwner->m_eBaseUnitType == static_cast<EBASEUNIT_TYPE>(0))
        m_property->m_iSkillLevel = m_iTargetAlignment;
    m_interruptible = true;
    m_coolingTime = m_property->getCoolDown();
    m_animationTimeRemaining = m_animationLength;
    m_elapsedSkillTime = 0.0f;
    m_animationSpeed = 1.0f;
    triggerEvent(static_cast<ESKILL_EVENT_TYPE>(0), position, orientation, target, &targetPosition);
    return true;
}
