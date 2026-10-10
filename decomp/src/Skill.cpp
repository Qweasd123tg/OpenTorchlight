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
