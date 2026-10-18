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




#include "SkillParser.h"
#include "Item.h"



void CSkillManager::stopSkillsByName(std::wstring name, bool force)
{
    name = STRINGS::StringUpper(name);
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
        if (STRINGS::StringUpper(m_UpdatingSkills[i]->getName()) == name)
        {
            if (force) m_UpdatingSkills[i]->stopSkill();
            else m_UpdatingSkills[i]->attemptToStopSkill();
        }
}

void CSkillManager::decrementSkillCharges(CSkill* skill)
{
    if (!skill) return;
    std::map<std::wstring,TArrayList<CSkill*>*>::iterator found = m_SkillsByName.find(STRINGS::StringUpper(skill->getName()));
    if (found == m_SkillsByName.end()) return;
    int charges = (*found->second)[0]->m_iCharges;
    if (charges <= 0) return;
    --charges;
    for (unsigned int i = 0; i < found->second->size(); ++i) (*found->second)[i]->m_iCharges = charges;
}

void CSkillManager::deleteSkill(const std::wstring& name)
{
    std::map<std::wstring,TArrayList<CSkill*>*>::iterator found = m_SkillsByName.find(STRINGS::StringUpper(name));
    if (found == m_SkillsByName.end()) return;
    for (unsigned int i = 0; i < found->second->size(); ++i)
    {
        CSkill* skill = (*found->second)[i];
        m_OtherSkills.remove(skill);
        if (m_UpdatingSkills.find(skill) == -1) delete skill;
    }
    delete found->second;
    found->second = NULL;
    m_SkillsByName.erase(found);
}

CSkill* CSkillManager::addSkill(const std::wstring& name, bool flag)
{
    if (!flag)
    {
        std::map<std::wstring,TArrayList<CSkill*>*>::iterator found = m_SkillsByName.find(STRINGS::StringUpper(name));
        if (found != m_SkillsByName.end()) return (*found->second)[0];
    }
    CSkill* skill = CSkillParser::getSkill(m_pResourceManager, name);
    if (!skill) return NULL;
    return addSkill(skill, false, flag);
}

void CSkillManager::notifyOfDeletion(CCharacter* character)
{
    for (std::map<std::wstring,TArrayList<CSkill*>*>::iterator i = m_SkillsByName.begin(); i != m_SkillsByName.end(); ++i)
    {
        CSkill* skill = (*i->second)[0];
        if (skill->getOwnerCharacter() == character && skill->m_pOwner)
        {
            skill->m_pOwner->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&skill->m_pOwner), skill->m_iOwnerSafePointerId);
            skill->m_pOwner = NULL;
        }
    }
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
    {
        CSkill* skill = m_UpdatingSkills[i];
        if (skill->m_Target.getObject() == character) skill->m_Target.setObject(NULL);
        if (skill->getOwnerCharacter() == character && skill->m_pOwner)
        {
            skill->m_pOwner->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&skill->m_pOwner), skill->m_iOwnerSafePointerId);
            skill->m_pOwner = NULL;
        }
    }
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
    {
        CSkill* skill = m_OtherSkills[i];
        if (skill->m_Target.getObject() == character) skill->m_Target.setObject(NULL);
        if (skill->getOwnerCharacter() == character && skill->m_pOwner)
        {
            skill->m_pOwner->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&skill->m_pOwner), skill->m_iOwnerSafePointerId);
            skill->m_pOwner = NULL;
        }
    }
}

void CSkillManager::notifyOfDeletion(CItem* item)
{
    for (std::map<std::wstring,TArrayList<CSkill*>*>::iterator i = m_SkillsByName.begin(); i != m_SkillsByName.end(); ++i)
    {
        CSkill* skill = (*i->second)[0];
        if (skill->m_pOwner == item && item)
        {
            item->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&skill->m_pOwner), skill->m_iOwnerSafePointerId);
            skill->m_pOwner = NULL;
        }
    }
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
    {
        CSkill* skill = m_UpdatingSkills[i];
        if (skill->m_Target.getObject() == item) skill->m_Target.setObject(NULL);
        if (skill->m_pOwner == item && item)
        {
            item->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&skill->m_pOwner), skill->m_iOwnerSafePointerId);
            skill->m_pOwner = NULL;
        }
    }
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
    {
        CSkill* skill = m_OtherSkills[i];
        if (skill->m_Target.getObject() == item) skill->m_Target.setObject(NULL);
        if (skill->m_pOwner == item && item)
        {
            item->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&skill->m_pOwner), skill->m_iOwnerSafePointerId);
            skill->m_pOwner = NULL;
        }
    }
}

CSkillManager::~CSkillManager()
{
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i) attemptDeleteOfSkill(m_UpdatingSkills[i]);
    for (std::map<std::wstring,TArrayList<CSkill*>*>::iterator i = m_SkillsByName.begin(); i != m_SkillsByName.end(); ++i)
    {
        i->second->deleteAll();
        delete i->second;
        i->second = NULL;
    }
}

CSkillManager::CSkillManager(CResourceManager* resources, CBaseUnit* owner)
    : CRunicCore(), m_pResourceManager(resources), m_UpdatingSkills(10),
      m_OtherSkills(10)
{
    m_Owner.setObject(owner);
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

void CSkillManager::stopAllSkills(bool force, bool keepDeathSkills, bool includePassive)
{
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
        if (includePassive || m_UpdatingSkills[i]->m_eActivationType != static_cast<ESKILL_ACTIVATION_TYPE>(4))
        {
            if (force)
            {
                if (!keepDeathSkills || (!m_UpdatingSkills[i]->hasEvent(static_cast<ESKILL_EVENT_TYPE>(9)) &&
                                         !m_UpdatingSkills[i]->m_suppressNormalStop))
                    m_UpdatingSkills[i]->stopSkill();
            }
            else if (!keepDeathSkills || (!m_UpdatingSkills[i]->hasEvent(static_cast<ESKILL_EVENT_TYPE>(9)) &&
                                          !m_UpdatingSkills[i]->m_suppressNormalStop))
                m_UpdatingSkills[i]->attemptToStopSkill();
        }
}

void CSkillManager::startPassiveSkills(CBaseUnit* caster, const Ogre::Vector3& position,
    const Ogre::Quaternion& orientation, const Ogre::Vector3& targetPosition)
{
    for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
        if (m_UpdatingSkills[i]->m_eActivationType == static_cast<ESKILL_ACTIVATION_TYPE>(4))
            m_UpdatingSkills[i]->stopSkill();
    update(0.0f);
    CCharacter* character = dynamic_cast<CCharacter*>(caster);
    if (character)
        for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
            if (m_OtherSkills[i]->m_eActivationType == static_cast<ESKILL_ACTIVATION_TYPE>(4))
            {
                CSkill* skill = m_OtherSkills[i];
                skill->calculateEffectiveSkillLevel();
                if (skill->m_iEffectiveSkillLevel && m_OtherSkills[i]->weaponRequirementsMet(character))
                    executeSkill(m_OtherSkills[i], caster, static_cast<ESKILL_ACTIVATION_TYPE>(4),
                                 position, orientation, targetPosition, caster);
            }
}

void CSkillManager::fireSkillsOnDeath(CBaseUnit* caster, ESKILL_ACTIVATION_TYPE activation,
    const Ogre::Vector3& position, const Ogre::Quaternion& orientation,
    const Ogre::Vector3& targetPosition, CCharacter* target)
{
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (m_OtherSkills[i]->hasEvent(static_cast<ESKILL_EVENT_TYPE>(9)))
        {
            if (m_OtherSkills[i]->getTargetType() == 1 || m_OtherSkills[i]->getTargetType() == 5 ||
                m_OtherSkills[i]->getTargetType() == 6)
            {
                Ogre::Vector3* skillPosition = getPositionForSkill(m_OtherSkills[i], NULL);
                target = NULL;
                executeSkill(m_OtherSkills[i], caster, activation, position, orientation,
                             skillPosition ? *skillPosition : targetPosition, target);
            }
            else
                executeSkill(m_OtherSkills[i], caster, activation, position, orientation, targetPosition, target);
        }
    triggerSkillEvent(static_cast<ESKILL_EVENT_TYPE>(9), position, orientation, target);
}

void CSkillManager::deleteSpecificSkill(CSkill* skill)
{
    m_OtherSkills.remove(skill);
    bool hasSameLevel = false;
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (m_OtherSkills[i]->getName() == skill->getName() && m_OtherSkills[i]->m_skillLevel == skill->m_skillLevel)
            hasSameLevel = true;
    for (int i = 0; i < static_cast<int>(m_UpdatingSkills.size()); ++i)
        if (m_UpdatingSkills[i] == skill)
        {
            skill->stopSkill();
            m_UpdatingSkills.removeAt(i);
            --i;
        }
    std::map<std::wstring,TArrayList<CSkill*>*>::iterator found = m_SkillsByName.find(STRINGS::StringUpper(skill->getName()));
    if (found != m_SkillsByName.end())
    {
        for (int i = 0; i < static_cast<int>(found->second->size()); ++i)
        {
            CSkill* entry = (*found->second)[i];
            if ((entry == skill || !hasSameLevel) && m_UpdatingSkills.find(entry) == -1)
            {
                found->second->removeAt(i);
                delete entry;
                --i;
            }
        }
        if (!hasSameLevel || m_SkillsByName.empty())
        {
            delete found->second;
            found->second = NULL;
            m_SkillsByName.erase(found);
        }
    }
}

void CSkillManager::setSkillLevel(CSkill* skill, unsigned int level)
{
    if (skill->m_eActivationType == static_cast<ESKILL_ACTIVATION_TYPE>(4) && level)
        for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
            if (m_UpdatingSkills[i]->m_eActivationType == static_cast<ESKILL_ACTIVATION_TYPE>(4))
                m_UpdatingSkills[i]->stopSkill();
    for (unsigned int i = 0; i < m_OtherSkills.size(); ++i)
        if (skill->getName() == m_OtherSkills[i]->getName())
            skill->_setLevelOfSkillFromSkillManager(level);
    std::map<std::wstring,TArrayList<CSkill*>*>::iterator found = m_SkillsByName.find(STRINGS::StringUpper(skill->getName()));
    if (found != m_SkillsByName.end())
        for (unsigned int i = 0; i < found->second->size(); ++i)
            (*found->second)[i]->_setLevelOfSkillFromSkillManager(level);
    if (skill->m_eActivationType == static_cast<ESKILL_ACTIVATION_TYPE>(4) && level)
        startPassiveSkills(m_Owner.getObject(), m_Owner.getObject()->getPosition(true),
                           m_Owner.getObject()->getOrientationQuaternion(), m_Owner.getObject()->getPosition(true));
}

CSkill* CSkillManager::addSkill(CSkill* skill, bool clone, bool addToList)
{
    if (!skill)
        return NULL;
    CSkill* result = skill;
    if (clone)
    {
        unsigned int level = skill->m_skillLevel;
        result = new CSkill(m_pResourceManager, skill->m_pDataGroup);
        result->_setLevelOfSkillFromSkillManager(level);
        result->m_bExecutedByProperty = !skill->enabledWithoutProperty();
        result->m_iCharges = skill->m_iCharges;
        result->m_iColumn = skill->m_iColumn;
    }
    std::map<std::wstring,TArrayList<CSkill*>*>::iterator found =
        m_SkillsByName.find(STRINGS::StringUpper(result->getName()));
    if (found == m_SkillsByName.end())
    {
        m_SkillsByName[STRINGS::StringUpper(result->getName())] = new TArrayList<CSkill*>(1);
        found = m_SkillsByName.find(STRINGS::StringUpper(result->getName()));
        m_OtherSkills.add(result);
    }
    else if (addToList)
        m_OtherSkills.add(result);
    found->second->add(result);
    result->m_pSkillManager = this;
    return result;
}

CSkill* CSkillManager::executeSkill(const std::wstring& name, CBaseUnit* caster,
    ESKILL_ACTIVATION_TYPE activation, const Ogre::Vector3& position,
    const Ogre::Quaternion& orientation, const Ogre::Vector3& targetPosition,
    CBaseUnit* target, int level)
{
    if (m_gDisableSkillFromBeingCasted)
        return NULL;
    std::map<std::wstring,TArrayList<CSkill*>*>::iterator found =
        m_SkillsByName.find(STRINGS::StringUpper(name));
    if (found == m_SkillsByName.end())
        return NULL;
    CSkill* skill = NULL;
    CSkill* last = NULL;
    for (unsigned int i = 0; i < found->second->size(); ++i)
    {
        if (!(*found->second)[i]->m_interruptible)
        {
            skill = (*found->second)[i];
            break;
        }
        last = (*found->second)[i];
    }
    if (!skill && last)
    {
        skill = addSkill(last, true, false);
        skill->_setLevelOfSkillFromSkillManager(level);
    }
    if (!skill)
        return NULL;
    if (skill->getIsExclusive())
        for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
            if (m_UpdatingSkills[i]->m_Guid == skill->m_Guid)
                m_UpdatingSkills[i]->stopSkill();
    if (m_UpdatingSkills.find(skill) != -1)
        return NULL;
    if (!skill->startSkill(caster, activation, position, orientation, targetPosition, target))
        return NULL;
    m_UpdatingSkills.add(skill);
    decrementSkillCharges(skill);
    return skill;
}

CSkill* CSkillManager::executeSkill(CSkill* skill, CBaseUnit* caster,
    ESKILL_ACTIVATION_TYPE activation, const Ogre::Vector3& position,
    const Ogre::Quaternion& orientation, const Ogre::Vector3& targetPosition,
    CBaseUnit* target)
{
    if (!skill || m_gDisableSkillFromBeingCasted)
        return NULL;
    if (skill->getIsExclusive())
        for (unsigned int i = 0; i < m_UpdatingSkills.size(); ++i)
            if (m_UpdatingSkills[i]->m_Guid == skill->m_Guid)
                m_UpdatingSkills[i]->stopSkill();
    if (m_UpdatingSkills.find(skill) != -1)
        return executeSkill(skill->getName(), caster, activation, position,
                            orientation, targetPosition, target, skill->m_skillLevel);
    if (!skill->startSkill(caster, activation, position, orientation, targetPosition, target))
        return NULL;
    m_UpdatingSkills.add(skill);
    decrementSkillCharges(skill);
    return skill;
}


bool CSkillManager::showWeaponTrailsOnCurrentSkill(CEquipment*,CEquipment*)
{
    return false;
}

#include "Utilities.h"
#include <cmath>

Ogre::Vector3* CSkillManager::getPositionForSkill(CSkill* skill,CBaseUnit* target)
{
    m_skillPosition=skill->m_targetPosition;
    int targetType=skill->getTargetType();
    if(targetType==5 || targetType==6) {
        m_skillPosition.x=UTILITIES::randomBetweenVolatile(-1.0f,1.0f);
        m_skillPosition.y=UTILITIES::randomBetweenVolatile(-1.0f,1.0f);
        m_skillPosition.normalise();
        if(targetType==5) {
            float range=skill->getRandomRange();
            float minimum=skill->getRandomRangeMin();
            m_skillPosition*=range-minimum;
            Ogre::Vector3 direction=m_skillPosition;
            direction.normalise();
            m_skillPosition+=direction*skill->getRandomRangeMin();
            if(m_Owner.getObject()) {
                if(target) {
                    Ogre::Vector3 ownerPosition=m_Owner.getObject()->getPosition(true);
                    Ogre::Vector3 targetPosition=target->getPosition(true);
                    Ogre::Vector3 forward(targetPosition.x-ownerPosition.x,0,targetPosition.z-ownerPosition.z);
                    float distance=std::sqrt(forward.x*forward.x+0.0f+forward.z*forward.z);
                    float range=skill->getRange();
                    distance=distance<range?distance:range;
                    float minimum=skill->getRangeMin();
                    distance=distance>minimum?distance:minimum;
                    forward.normalise();
                    Ogre::Vector3 offset(0,-m_Owner.getObject()->m_fBaseUnitValue194,0);
                    Ogre::Vector3 position=m_Owner.getObject()->getPosition(true);
                    m_skillPosition=forward*distance+position+offset+m_skillPosition;
                } else {
                    Ogre::Vector3 offset(0,-m_Owner.getObject()->m_fBaseUnitValue194,0);
                    Ogre::Vector3 position=m_Owner.getObject()->getPosition(true);
                    m_skillPosition=position+offset+m_skillPosition;
                }
            } else if(target) {
                Ogre::Vector3 offset(0,-target->m_fBaseUnitValue194,0);
                Ogre::Vector3 position=target->getPosition(true);
                m_skillPosition=position+offset+m_skillPosition;
            }
        } else {
            float range=skill->getRange();
            float minimum=skill->getRangeMin();
            m_skillPosition*=range-minimum;
            Ogre::Vector3 direction=m_skillPosition;
            direction.normalise();
            m_skillPosition+=direction*skill->getRangeMin();
            m_skillPosition*=0.25f;
            if(target) {
                if(m_Owner.getObject()) {
                    m_skillPosition+=m_Owner.getObject()->getPosition(true);
                    Ogre::Vector3 ownerPosition=m_Owner.getObject()->getPosition(true);
                    Ogre::Vector3 targetPosition=target->getPosition(true);
                    Ogre::Vector3 forward=targetPosition-ownerPosition;
                    forward.normalise();
                    float range=skill->getRange();
                    m_skillPosition=forward*-0.5f*range+Ogre::Vector3(0,-m_Owner.getObject()->m_fBaseUnitValue194,0)+m_skillPosition;
                } else {
                    m_skillPosition+=target->getPosition(true);
                    float range=skill->getRange();
                    Ogre::Vector3 forward=target->getForward();
                    m_skillPosition=forward*-0.5f*range+Ogre::Vector3(0,-m_Owner.getObject()->m_fBaseUnitValue194,0)+m_skillPosition;
                }
            } else if(m_Owner.getObject()) {
                m_skillPosition+=m_Owner.getObject()->getPosition(true);
                float range=skill->getRange();
                Ogre::Vector3 forward=m_Owner.getObject()->getForward();
                m_skillPosition=forward*-0.5f*range+Ogre::Vector3(0,-m_Owner.getObject()->m_fBaseUnitValue194,0)+m_skillPosition;
            }
        }
    } else if(targetType!=1)
        return NULL;
    return &m_skillPosition;
}
