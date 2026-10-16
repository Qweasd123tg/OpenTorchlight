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

#include "BaseUnit.h"
#include "Character.h"

bool CSkillManager::knowsSkill(const std::wstring& name)
{
    return m_SkillsByName.find(STRINGS::StringUpper(name)) != m_SkillsByName.end();
}

bool CSkillManager::getSkillIsUpdatingByName(const std::wstring& name)
{
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
        if (m_UpdatingSkills[i]->getName() == name)
            return true;
    return false;
}

bool CSkillManager::getSkillIsCooling(CSkill* skill)
{
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (m_OtherSkills[i]->m_pDataGroup == skill->m_pDataGroup && m_OtherSkills[i]->m_coolingTime > 0.0f)
            return true;
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
        if (m_UpdatingSkills[i]->m_pDataGroup == skill->m_pDataGroup && m_UpdatingSkills[i]->m_coolingTime > 0.0f)
            return true;
    return false;
}

float CSkillManager::getSkillCoolingTime(CSkill* skill)
{
    float result = 0.0f;
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (m_OtherSkills[i]->m_pDataGroup == skill->m_pDataGroup && m_OtherSkills[i]->m_coolingTime > 0.0f)
            result = std::max(result, m_OtherSkills[i]->m_coolingTime);
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
        if (m_UpdatingSkills[i]->m_pDataGroup == skill->m_pDataGroup && m_UpdatingSkills[i]->m_coolingTime > 0.0f)
            result = std::max(result, m_UpdatingSkills[i]->m_coolingTime);
    return result;
}

void CSkillManager::clearAllUnitReferences()
{
    for (std::map<std::wstring,TArrayList<CSkill*>*>::iterator i = m_SkillsByName.begin(); i != m_SkillsByName.end(); ++i) {
        CSkill* skill = (*i->second)[0];
        if (skill->m_pOwner) {
            skill->m_pOwner->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&skill->m_pOwner), skill->m_iOwnerSafePointerId);
            skill->m_pOwner = NULL;
        }
    }
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i) {
        CSkill* skill = m_UpdatingSkills[i];
        skill->m_Target.setObject(NULL);
        if (skill->m_pOwner) {
            skill->m_pOwner->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&skill->m_pOwner), skill->m_iOwnerSafePointerId);
            skill->m_pOwner = NULL;
        }
    }
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i) {
        CSkill* skill = m_OtherSkills[i];
        skill->m_Target.setObject(NULL);
        if (skill->m_pOwner) {
            skill->m_pOwner->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&skill->m_pOwner), skill->m_iOwnerSafePointerId);
            skill->m_pOwner = NULL;
        }
    }
}

void CSkillManager::attemptDeleteOfSkill(CSkill* skill)
{
    if (m_SkillsByName.find(STRINGS::StringUpper(skill->getName())) == m_SkillsByName.end())
        delete skill;
}

void CSkillManager::update(float elapsed)
{
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i) {
        CSkill* skill = m_UpdatingSkills[i];
        skill->updateSkill(elapsed);
        if (!skill->m_interruptible && skill->m_coolingTime <= 0.0f) {
            skill->stopSkill();
            m_UpdatingSkills.removeAt(i);
            --i;
            attemptDeleteOfSkill(skill);
        } else if (skill->m_eActivationType == static_cast<ESKILL_ACTIVATION_TYPE>(4)) {
            if (skill->calculateEffectiveSkillLevel())
                setSkillLevel(skill, skill->m_skillLevel);
        }
    }
}

void CSkillManager::triggerSkillEvent(ESKILL_EVENT_TYPE event, const Ogre::Vector3& position,
    const Ogre::Quaternion& orientation, CBaseUnit* target)
{
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i) {
        int type = m_UpdatingSkills[i]->getTargetType();
        if (type == 1 || type == 5 || type == 6) {
            Ogre::Vector3 targetPosition = m_UpdatingSkills[i]->m_targetPosition;
            m_UpdatingSkills[i]->triggerEvent(event, position, orientation, target, &targetPosition);
        } else {
            m_UpdatingSkills[i]->triggerEvent(event, position, orientation, target, NULL);
        }
    }
}

void CSkillManager::fireSkillsOnCreate(CBaseUnit* caster, ESKILL_ACTIVATION_TYPE activation,
    const Ogre::Vector3& position, const Ogre::Quaternion& orientation,
    const Ogre::Vector3& targetPosition, CCharacter* target)
{
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (m_OtherSkills[i]->hasEvent(static_cast<ESKILL_EVENT_TYPE>(10)))
            executeSkill(m_OtherSkills[i], caster, activation, position, orientation, targetPosition, target);
    triggerSkillEvent(static_cast<ESKILL_EVENT_TYPE>(10), position, orientation, target);
}
