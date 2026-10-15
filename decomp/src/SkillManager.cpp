#include "SkillManager.h"
#include "Skill.h"
#include "StringUtilities.h"

bool m_gDisableSkillFromBeingCasted = false;

void CSkillManager::globallyDisableSkills(bool disabled)
{
    m_gDisableSkillFromBeingCasted = disabled;
}

unsigned int CSkillManager::getSkillLevel(CSkill* skill)
{
    return skill ? skill->m_skillLevel : 0;
}

CSkill* CSkillManager::getSkillByGuid(long long guid)
{
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (guid == m_OtherSkills[i]->getGuid())
            return m_OtherSkills[i];
    return NULL;
}

CSkill* CSkillManager::getSkillByGuid(long long guid, int level)
{
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (guid == m_OtherSkills[i]->getGuid() && level == m_OtherSkills[i]->getLevel())
            return m_OtherSkills[i];
    return NULL;
}

int CSkillManager::knownSkills(ESKILL_ACTIVATION_TYPE activation)
{
    if (activation == SKILL_ACTIVATION_ANY)
        return m_OtherSkills.size();
    int count = 0;
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (m_OtherSkills[i]->getActivationType() == activation)
            ++count;
    return count;
}

int CSkillManager::getNumOfSkillsExecutableByActivationType(ESKILL_ACTIVATION_TYPE activation)
{
    int count = 0;
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (activation == m_OtherSkills[i]->getActivationType() && !(m_OtherSkills[i]->m_coolingTime > 0.0f))
            ++count;
    return count;
}

int CSkillManager::getSkillPoints()
{
    unsigned int points = 0;
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (m_OtherSkills[i]->enabledWithoutProperty() &&
            m_OtherSkills[i]->m_skillType == 0)
            points += m_OtherSkills[i]->getLevel();
    return points;
}

void CSkillManager::hideWeaponTrailsOnCurrentSkill()
{
}

unsigned int CSkillManager::getSkillLevel(const std::wstring& name)
{
    CSkill* skill = getSkill(name);
    return skill ? skill->m_skillLevel : 0;
}

void CSkillManager::deleteSkill(CSkill* skill)
{
    if (skill)
        deleteSkill(skill->getName());
}

void CSkillManager::setSkillLevel(const std::wstring& name, unsigned int level)
{
    setSkillLevel(getSkill(name), level);
}

bool CSkillManager::getSkillCanBeExecuted(CSkill* skill, CBaseUnit* caster,
    ESKILL_ACTIVATION_TYPE activation, const Ogre::Vector3& targetPosition,
    CBaseUnit* target, bool flag)
{
    if (!skill || getSkillIsCooling(skill))
        return false;
    return skill->requirementsMet(caster, activation, &targetPosition, target, flag);
}


bool CSkillManager::getAnySkillsCoolingByActivationType(ESKILL_ACTIVATION_TYPE activation)
{
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (m_OtherSkills[i]->m_eActivationType == activation &&
            m_OtherSkills[i]->m_coolingTime > 0.0f)
            return true;
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
        if (m_UpdatingSkills[i]->m_eActivationType == activation &&
            m_UpdatingSkills[i]->m_coolingTime > 0.0f)
            return true;
    return false;
}

CSkill* CSkillManager::getSkill(const std::wstring& name, int level)
{
    std::wstring upperName = STRINGS::StringUpper(name);
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (STRINGS::StringUpper(m_OtherSkills[i]->getName()) == upperName &&
            m_OtherSkills[i]->m_skillLevel == level)
            return m_OtherSkills[i];
    return NULL;
}

CSkill* CSkillManager::getSkill(const std::wstring& name)
{
    std::map<std::wstring,TArrayList<CSkill*>*>::iterator found =
        m_SkillsByName.find(STRINGS::StringUpper(name));
    if (found != m_SkillsByName.end() && found->second->size())
        return (*found->second)[0];
    return NULL;
}

void CSkillManager::resetSkillLevels()
{
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (m_OtherSkills[i]->m_bEnabled & !m_OtherSkills[i]->m_bExecutedByProperty)
            if (m_OtherSkills[i]->m_skillType == 0)
                setSkillLevel(m_OtherSkills[i], 0);
}
