#include "EmptyStrings.h"
#include "ExecuteSkillProps.h"
#include "Constants.h"
#include "SkillDefines.h"
#include "EffectDefines.h"
#include "EditorDefines.h"
#include "ResourceManager.h"
#include "Character.h"
#include "DataGroup.h"
#include "Level.h"
#include "Skill.h"
#include "SkillManager.h"
#include <OgreMatrix4.h>

CExecuteSkillProps::~CExecuteSkillProps()
{
    m_pSkill = NULL;
    m_pSkillEvent = NULL;
}

CExecuteSkillProps::CExecuteSkillProps(CSkill* skill, CSkillEvent* skillEvent, CDataGroup* dataGroup)
    : m_pSkill(skill), m_pSkillEvent(skillEvent)
{
    if (dataGroup != NULL)
        m_sSkillName = dataGroup->GetDataValue(L"SKILL", EMPTY_WSTRING);
}

bool CExecuteSkillProps::executeSkill(CBaseUnit* caster, const Ogre::Vector3& position,
                                      const Ogre::Quaternion& orientation, const Ogre::Vector3& targetPosition,
                                      CBaseUnit* target, int level)
{
    if (m_pSkill == NULL)
        return false;
    CSkillManager* skillManager = m_pSkill->m_pSkillManager;
    if (skillManager == NULL)
        return false;

    CSkill* skill = skillManager->addSkill(m_sSkillName, false);
    skill->m_bExecutedByProperty = true;
    skill->_setLevelOfSkillFromSkillManager(level);

    CCharacter* owner = dynamic_cast<CCharacter*>(m_pSkill->m_pOwner);
    if (target == NULL && owner != NULL)
    {
        Ogre::Matrix4 view(orientation);
        view.setTrans(position);
        float range = skill->getRange();
        float angle = skill->getFindTargetAngle();
        CLevel* currentLevel = caster->getLevel();
        target = currentLevel->findCharacterWithinView(view, (EAlignment)skill->m_iTargetAlignment, 0.0f, angle,
                                                range + 0.2f + 1.0f, true, (CCharacter*)caster, NULL);
    }
    if (!skillManager->getSkillCanBeExecuted(skill, caster, SKILL_ACTIVATION_ANY, targetPosition, target, false))
        return false;
    return skillManager->executeSkill(skill, caster, SKILL_ACTIVATION_ANY, position, orientation,
                                      targetPosition, target) != NULL;
}

std::wstring CExecuteSkillProps::getSkillStats(CBaseUnit* unit, int level)
{
    if (m_pSkill == NULL)
        return L"";
    CSkillManager* skillManager = m_pSkill->m_pSkillManager;
    if (skillManager == NULL)
        return L"";
    CSkill* skill = skillManager->addSkill(m_sSkillName, false);
    skill->_setLevelOfSkillFromSkillManager(level);
    return skill->getSkillLevelStats(unit, level);
}

std::wstring CExecuteSkillProps::getSkillDescription(CBaseUnit* unit, int level)
{
    if (m_pSkill == NULL)
        return L"";
    CSkillManager* skillManager = m_pSkill->m_pSkillManager;
    if (skillManager == NULL)
        return L"";
    CSkill* skill = skillManager->addSkill(m_sSkillName, false);
    skill->_setLevelOfSkillFromSkillManager(level);
    return skill->getDescription(unit, level, false);
}
