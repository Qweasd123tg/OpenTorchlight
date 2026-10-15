#include "GameClient.h"
#include "Level.h"
#include "Utilities.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#include "SoundBank.h"
#include "Path.h"
extern Ogre::Vector3 monsterPathPoint(CPath*, unsigned int) __asm__("_ZN5CPath8GetPointEj");

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

void CMonster::fleeAI(float, CLevel& level)
{
    setTarget(NULL);
    m_returningToTown = true;
    if (m_isPathing) return;
    if (UTILITIES::randomIntegerBetweenVolatile(0, 100) < 75)
    {
        selectDefensiveSkill();
        if (m_activeSkill && canCastCurrentSkill(NULL, false, false))
        {
            castSkill(-1);
            return;
        }
    }
    if (UTILITIES::randomIntegerBetweenVolatile(0, 100) < 75 && !isPetNearDeath() && !hasEffect(static_cast<EEFFECT_TYPE>(79)))
        setAIState(AISTATE_IDLE);
    if (m_pMaster && !ISA(static_cast<UNITTYPES::EUNITTYPES>(169)))
    {
        float upperZ = m_pMaster->getPosition(false).z + 16.0f;
        float lowerZ = m_pMaster->getPosition(true).z - 16.0f;
        float z = UTILITIES::randomBetweenVolatile(lowerZ, upperZ);
        float upperX = m_pMaster->getPosition(false).x + 16.0f;
        float lowerX = m_pMaster->getPosition(true).x - 16.0f;
        float x = UTILITIES::randomBetweenVolatile(lowerX, upperX);
        setDestination(level, x, z);
    }
    else
    {
        float z = UTILITIES::randomBetweenVolatile(m_vPosition.z - 5.0f, m_vPosition.z + 5.0f);
        float x = UTILITIES::randomBetweenVolatile(m_vPosition.x - 5.0f, m_vPosition.x + 5.0f);
        setDestination(level, x, z);
    }
}

bool CMonster::idleAINormal(float elapsed, CLevel&, bool flag)
{
    m_returningToTown = false;
    if (alignment() != 0 && !isPetNearDeath() && m_petMode == 1 && getLevel()->m_pGameClient->getGameState() == 1 &&
        !(m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL)->GetInt(KSETTINGS_PLAYER_UNTARGETABLE))
    {
        CCharacter* target = calculateTargetInSight(static_cast<EAlignment>(7), m_pMaster && attachesToMaster());
        if (target)
        {
            if (hasDefensiveSkill() && UTILITIES::randomIntegerBetweenVolatile(0, 100) < 35) selectDefensiveSkill();
            else selectOffensiveSkill(false);
            if (canCastCurrentSkill(target, false, false))
            {
                setTarget(target);
                stopPathing();
                setAIState(static_cast<EAIState>(13));
                updateAI(elapsed, !flag);
                return true;
            }
        }
        else if (!m_activeSkill)
        {
            if (hasDefensiveSkill() && UTILITIES::randomIntegerBetweenVolatile(0, 100) < 35) selectDefensiveSkill();
            else selectOffensiveSkill(false);
        }
        if (!target) return false;
        if (m_pMaster && !ISA(static_cast<UNITTYPES::EUNITTYPES>(169)))
        {
            Ogre::Vector3 targetPosition = target->getPosition(true);
            Ogre::Vector3 masterPosition = m_pMaster->getPosition(true);
            Ogre::Vector3 difference(masterPosition.x - targetPosition.x, 0.0f, masterPosition.z - targetPosition.z);
            if (difference.length() > 35.0f) return false;
        }
        if (isEnemy(target) && canAttackWithCurrentWeapon())
        {
            stopPathing();
            setAIState(static_cast<EAIState>(4));
            setTarget(target);
            if (m_levelSound) m_levelSound->playSample(13, m_pSceneNode, 0.0f, 0.0f, false);
            return true;
        }
    }
    else if (alignment() != 0 && !isPetNearDeath() && m_petMode != 1 && getLevel()->m_pGameClient->getGameState() == 1 &&
        !(m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL)->GetInt(KSETTINGS_PLAYER_UNTARGETABLE))
    {
        m_activeSkill = NULL;
        selectDefensiveSkill();
        if (canCastCurrentSkill(m_targetCharacter.getObject(), false, false))
        {
            castSkill(-1);
            return true;
        }
    }
    return false;
}

bool CMonster::idleAICircler(float elapsed, CLevel& level, bool flag)
{
    m_returningToTown = false;
    if (alignment() == 0 || isPetNearDeath()) return false;
    unsigned int property = KSETTINGS_PLAYER_UNTARGETABLE;
    CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    if (settings->GetInt(property)) return false;
    CCharacter* target = calculateTargetInSight(static_cast<EAlignment>(7), m_pMaster && attachesToMaster());
    bool targetAvailable = target != NULL;
    if (m_pMaster && target)
    {
        Ogre::Vector3 targetPosition = target->getPosition(true);
        Ogre::Vector3 masterPosition = m_pMaster->getPosition(true);
        Ogre::Vector3 difference(masterPosition.x - targetPosition.x, 0.0f, masterPosition.z - targetPosition.z);
        if (difference.length() > 35.0f) targetAvailable = false;
    }
    if (targetAvailable)
    {
        setTarget(target);
        if (canAttackWithCurrentWeapon() && inAttackRange(ATTACK_RANGE_DEFAULT))
        {
            stopPathing();
            setAIState(static_cast<EAIState>(4));
            setTarget(target);
            if (m_levelSound) m_levelSound->playSample(13, m_pSceneNode, 0.0f, 0.0f, false);
            return true;
        }
        if (hasDefensiveSkill() && UTILITIES::randomIntegerBetweenVolatile(0, 100) < 10) selectDefensiveSkill();
        else selectOffensiveSkill(false);
        if (m_activeSkill && canCastCurrentSkill(target, false, false))
        {
            setTarget(target);
            setAIState(static_cast<EAIState>(13));
            stopPathing();
            updateAI(elapsed, !flag);
            return true;
        }
        setAIState(static_cast<EAIState>(4));
        if (UTILITIES::randomIntegerBetweenVolatile(0, 100) < 20)
        {
            setAIState(static_cast<EAIState>(11));
            float upperZ = target->getPosition(false).z + 3.0f;
            float lowerZ = target->getPosition(true).z - 3.0f;
            float z = UTILITIES::randomBetweenVolatile(lowerZ, upperZ);
            float upperX = target->getPosition(false).x + 3.0f;
            float lowerX = target->getPosition(true).x - 3.0f;
            float x = UTILITIES::randomBetweenVolatile(lowerX, upperX);
            setDestination(level, x, z);
            return true;
        }
    }
    else if (!m_activeSkill)
    {
        if (hasDefensiveSkill() && UTILITIES::randomIntegerBetweenVolatile(0, 100) < 10) selectDefensiveSkill();
        else selectOffensiveSkill(false);
    }
    return false;
}

bool CMonster::idleAIRangedCaster(float elapsed, CLevel&, bool flag)
{
    m_returningToTown = false;
    if (alignment() == 0 || isPetNearDeath()) return false;
    unsigned int property = KSETTINGS_PLAYER_UNTARGETABLE;
    CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    if (settings->GetInt(property)) return false;
    CCharacter* target = calculateTargetInSight(static_cast<EAlignment>(7), m_pMaster && attachesToMaster());
    bool targetAvailable = target != NULL;
    if (m_pMaster && target)
    {
        Ogre::Vector3 targetPosition = target->getPosition(true);
        Ogre::Vector3 masterPosition = m_pMaster->getPosition(true);
        Ogre::Vector3 difference(masterPosition.x - targetPosition.x, 0.0f, masterPosition.z - targetPosition.z);
        if (difference.length() > 35.0f) targetAvailable = false;
    }
    if (targetAvailable)
    {
        setTarget(target);
        if (canAttackWithCurrentWeapon() && inAttackRange(ATTACK_RANGE_DEFAULT))
        {
            stopPathing();
            setAIState(static_cast<EAIState>(4));
            setTarget(target);
            if (m_levelSound) m_levelSound->playSample(13, m_pSceneNode, 0.0f, 0.0f, false);
            return true;
        }
        if (hasDefensiveSkill() && UTILITIES::randomIntegerBetweenVolatile(0, 100) < 35) selectDefensiveSkill();
        else selectOffensiveSkill(false);
        if (m_activeSkill && canCastCurrentSkill(target, false, false))
        {
            setTarget(target);
            setAIState(static_cast<EAIState>(13));
            stopPathing();
            updateAI(elapsed, !flag);
            return true;
        }
        if (UTILITIES::randomIntegerBetweenVolatile(0, 100) < 10)
        {
            setAIState(static_cast<EAIState>(10));
            return true;
        }
    }
    else if (!m_activeSkill)
    {
        if (hasDefensiveSkill() && UTILITIES::randomIntegerBetweenVolatile(0, 100) < 35) selectDefensiveSkill();
        else selectOffensiveSkill(false);
    }
    return false;
}

bool CMonster::idleAIRangedDefender(float elapsed, CLevel&, bool flag)
{
    m_returningToTown = false;
    if (alignment() == 0 || isPetNearDeath()) return false;
    unsigned int property = KSETTINGS_PLAYER_UNTARGETABLE;
    CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    if (settings->GetInt(property)) return false;
    CCharacter* target = calculateTargetInSight(static_cast<EAlignment>(7), m_pMaster && attachesToMaster());
    bool targetAvailable = target != NULL;
    if (m_pMaster && target && !ISA(static_cast<UNITTYPES::EUNITTYPES>(169)))
    {
        Ogre::Vector3 targetPosition = target->getPosition(true);
        Ogre::Vector3 masterPosition = m_pMaster->getPosition(true);
        Ogre::Vector3 difference(masterPosition.x - targetPosition.x, 0.0f, masterPosition.z - targetPosition.z);
        if (difference.length() > 35.0f) targetAvailable = false;
    }
    if (targetAvailable)
    {
        setTarget(target);
        if (canAttackWithCurrentWeapon() && inAttackRange(ATTACK_RANGE_DEFAULT))
        {
            stopPathing();
            setAIState(static_cast<EAIState>(4));
            setTarget(target);
            if (m_levelSound) m_levelSound->playSample(13, m_pSceneNode, 0.0f, 0.0f, false);
            return true;
        }
        selectDefensiveSkill();
        if (m_activeSkill && canCastCurrentSkill(NULL, false, false))
        {
            castSkill(-1);
            return true;
        }
        if (UTILITIES::randomIntegerBetweenVolatile(0, 100) < 10)
        {
            setAIState(static_cast<EAIState>(10));
            return true;
        }
    }
    else if (!m_activeSkill)
    {
        selectDefensiveSkill();
    }
    return false;
}

void CMonster::jumpDownAI(float elapsed, CLevel&)
{
    float previousDistance = m_deathPathDistance;
    monsterPathPoint(m_deathPath, 1);
    monsterPathPoint(m_deathPath, 0);
    if (m_deathPathDistance < m_deathPath->m_fPathLength * 0.5f)
        turnTowardPosition(monsterPathPoint(m_deathPath, 2), elapsed);
    m_deathPathDistance += elapsed * m_deathPathSpeed;
    if (m_deathPathDistance < m_deathPath->m_fPathLength)
    {
        float fraction = m_deathPathDistance / m_deathPath->m_fPathLength;
        float duration = m_pUnitModel->getAnimationLengthSeconds("JUMP_DOWN");
        m_pUnitModel->setAnimationTime(duration * fraction - elapsed);
    }
    if (m_deathPathDistance >= m_deathPath->m_fPathLength)
    {
        if (previousDistance < m_deathPath->m_fPathLength)
        {
            m_deathPathDistance = m_deathPath->m_fPathLength;
            if (m_levelSound) m_levelSound->playSample(17, m_pSceneNode, 0.0f, 0.0f, false);
            queueBlendAnimation("IDLE", true, 0.2f, 1.0f);
        }
        else
        {
            m_deathPathActive = false;
            if (m_pUnitModel->animationPlayingSubstring("IDLE")) setAIState(static_cast<EAIState>(4));
            return;
        }
    }
    m_vPosition = m_deathPath->GetSplinePositionAtDistance(m_deathPathDistance);
    setPosition(m_vPosition);
}
