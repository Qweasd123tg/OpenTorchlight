#include "DataGroup.h"
#include "GenericModel.h"
#include "Skill.h"
#include "SkillManager.h"
#include "SkillProperty.h"

#include <algorithm>
#include "Monster.h"

void CMonster::getRangeAI(float, CLevel&)
{
    m_returningToTown = true;
    if (!m_isPathing) {
        if (m_targetCharacter.getObject()) setAIState(static_cast<EAIState>(4));
        else setAIState(AISTATE_IDLE);
    }
}

void CMonster::notifyAISkillComplete()
{
    selectOffensiveSkill(false);
}

void CMonster::setPathToFollow(CPathController* path)
{
    CCharacter::setPathToFollow(path);
}

void CMonster::approachAI(float elapsed, CLevel& level)
{
    CCharacter::approachAI(elapsed,level);
}

bool CMonster::canAttackWithCurrentWeapon()
{
    if (m_attackDelay > 0.0f) return false;
    return CCharacter::canAttackWithCurrentWeapon();
}

CMonster::CMonster(CResourceManager* resources,int level)
    : CCharacter(resources), m_monsterName(), m_skillRandomizer(RANDOMIZER_NORMAL),
      m_attackDelay(0.0f), m_initialAttackDelay(0.0f), m_monsterFlag(false)
{
    m_iUnitLevel = std::max(level, int(m_iUnitLevel));
}

void CMonster::idleAIResurrecter(float elapsed,CLevel& level,bool flag)
{
    idleAINormal(elapsed,level,flag);
}

void CMonster::idleAIDefender(float elapsed,CLevel& level,bool flag)
{
    idleAINormal(elapsed,level,flag);
}

CMonster::~CMonster()
{
}

bool CMonster::hasOffensiveSkill()
{
    if (m_pSkillManager)
    {
        int count = m_pSkillManager->knownSkills(SKILL_ACTIVATION_ANY);
        m_pSkillManager->m_OtherSkills.find(m_activeSkill);
        for (int i = 0; i < count; ++i)
        {
            CSkill* skill = m_pSkillManager->getSkillByIndex(i);
            if (mana() >= static_cast<int>(skill->getManaCost()) &&
                mana() >= static_cast<int>(skill->getManaCostOT()) &&
                !m_pSkillManager->getSkillIsCooling(skill) &&
                (skill->m_property ? skill->m_property :
                    (skill->m_iSkillLevelCount ? skill->m_levelPropertyData[0] : NULL))->m_iSkillLevel == 2 &&
                ((!skill->m_bExecutedByProperty) & skill->m_bEnabled))
                return true;
        }
    }
    return false;
}

bool CMonster::hasDefensiveSkill()
{
    if (m_pSkillManager)
    {
        int count = m_pSkillManager->knownSkills(SKILL_ACTIVATION_ANY);
        m_pSkillManager->m_OtherSkills.find(m_activeSkill);
        for (int i = 0; i < count; ++i)
        {
            CSkill* skill = m_pSkillManager->getSkillByIndex(i);
            if (mana() >= static_cast<int>(skill->getManaCost()) &&
                mana() >= static_cast<int>(skill->getManaCostOT()) &&
                !m_pSkillManager->getSkillIsCooling(skill) &&
                ((skill->m_property ? skill->m_property : (skill->m_iSkillLevelCount ? skill->m_levelPropertyData[0] : NULL))->m_eTargetType == 3 ||
                 (skill->m_property ? skill->m_property : (skill->m_iSkillLevelCount ? skill->m_levelPropertyData[0] : NULL))->m_eTargetType == 10 ||
                 (skill->m_property ? skill->m_property : (skill->m_iSkillLevelCount ? skill->m_levelPropertyData[0] : NULL))->m_eTargetType == 9 ||
                 skill->m_skillType == 2 || skill->m_skillType == 3) &&
                ((!skill->m_bExecutedByProperty) & skill->m_bEnabled))
                return true;
        }
    }
    return false;
}

void CMonster::selectOffensiveSkill(bool requireCastable)
{
    if (!m_pSkillManager) return;
    int count = m_pSkillManager->knownSkills(SKILL_ACTIVATION_ANY);
    CSkill* previous = m_activeSkill;
    m_pSkillManager->m_OtherSkills.find(previous);
    if (count <= 0) return;
    m_skillRandomizer.clear();
    setActiveSkill(NULL, false);
    for (int i = 0; i < count; ++i)
    {
        CSkill* skill = m_pSkillManager->getSkillByIndex(i);
        if (mana() >= static_cast<int>(skill->getManaCost()) &&
            mana() >= static_cast<int>(skill->getManaCostOT()) &&
            !m_pSkillManager->getSkillIsCooling(skill) &&
            ((skill->m_property ? skill->m_property : (skill->m_iSkillLevelCount ? skill->m_levelPropertyData[0] : NULL))->m_iSkillLevel == 2 || skill->m_skillType == 1) &&
            ((!skill->m_bExecutedByProperty) & skill->m_bEnabled))
        {
            if (requireCastable)
            {
                setActiveSkill(skill, false);
                if (!canCastCurrentSkill(m_targetCharacter.getObject(), false, false)) continue;
            }
            m_skillRandomizer.addChoice(i, 1);
        }
    }
    if (m_skillRandomizer.hasChoices())
        setActiveSkill(m_pSkillManager->getSkillByIndex(m_skillRandomizer.getRandom()), false);
    else
        setActiveSkill(previous, false);
}

void CMonster::selectDefensiveSkill()
{
    if (!m_pSkillManager) return;
    int count = m_pSkillManager->knownSkills(SKILL_ACTIVATION_ANY);
    m_pSkillManager->m_OtherSkills.find(m_activeSkill);
    if (count <= 0) return;
    m_skillRandomizer.clear();
    setActiveSkill(NULL, false);
    for (int i = 0; i < count; ++i)
    {
        CSkill* skill = m_pSkillManager->getSkillByIndex(i);
        if (mana() >= static_cast<int>(skill->getManaCost()) &&
            mana() >= static_cast<int>(skill->getManaCostOT()) &&
            !m_pSkillManager->getSkillIsCooling(skill) &&
            ((skill->m_property ? skill->m_property : (skill->m_iSkillLevelCount ? skill->m_levelPropertyData[0] : NULL))->m_eTargetType == 3 ||
             (skill->m_property ? skill->m_property : (skill->m_iSkillLevelCount ? skill->m_levelPropertyData[0] : NULL))->m_eTargetType == 10 ||
             (skill->m_property ? skill->m_property : (skill->m_iSkillLevelCount ? skill->m_levelPropertyData[0] : NULL))->m_eTargetType == 9 || skill->m_skillType == 2) &&
            skill->m_iTargetAlignment != 2 &&
            ((!skill->m_bExecutedByProperty) & skill->m_bEnabled))
            m_skillRandomizer.addChoice(i, 1);
    }
    if (m_skillRandomizer.hasChoices())
        setActiveSkill(m_pSkillManager->getSkillByIndex(m_skillRandomizer.getRandom()), false);
}

void CMonster::fidgetAI(float elapsed, CLevel& level)
{
    if (!alive()) return;
    if (!m_pUnitModel->animationPlayingSubstring("FIDGET")) setAIState(AISTATE_IDLE);
    if (m_pMaster && !ISA(static_cast<UNITTYPES::EUNITTYPES>(169))) {
        Ogre::Vector3 position = getPosition(true);
        Ogre::Vector3 masterPosition = m_pMaster->getPosition(true);
        Ogre::Vector3 distance = masterPosition - position;
        distance.y = 0.0f;
        if (distance.length() > 8.0f) {
            setAIState(AISTATE_IDLE);
            blendAnimation("IDLE", true, 0.1f, 1.0f, -1.0f);
        }
    }
}

void CMonster::unitInit(CDataGroup* data, bool initialize)
{
    CCharacter::unitInit(data, initialize);
    m_initialAttackDelay = data->GetDataValue(L"AI_ATTACKCOOLDOWN", 0.0f);
    if (getUnitModel())
        static_cast<CGenericModel*>(getUnitModel())->m_animationStep = 0.01f;
}
