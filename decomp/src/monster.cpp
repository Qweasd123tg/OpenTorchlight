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

void CMonster::updateAI(float elapsed, bool force)
{
    m_attackDelay -= elapsed;
    if (m_pSkillManager && performingSkill() && m_eAIState != 14 && m_eAIState != 13)
        m_pSkillManager->stopAllSkills(false, false, false);
    if (m_eAIState == 44 || m_eAIState == 35 || m_pathToFollow.getObject())
        force = true;
    m_aiThinkTime += elapsed;
    if (!(force || m_aiThinkTime >= KAIThinkTime[m_aiThinkTier] || m_deathPathActive))
        return;
    m_aiThinkTime = 0.0f;
    if (m_targetCharacter.getObject() &&
        (!m_targetCharacter.getObject()->alive() || !m_targetCharacter.getObject()->m_bInActiveRange))
        setTarget(NULL);
    CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    if (settings->GetInt(KSETTINGS_AI_FREEZE) > 0)
        return;
    CLevel* level = getLevel();
    if (alive() && (level->isDormant() || !getEnabled()))
    {
        if (!performingAttack() && !performingSkill() && m_eAIState != 2 &&
            m_eAIState != 35 && m_eAIState != 16 && m_eAIState != 41 &&
            m_eAIState != 42 && m_eAIState != 40)
            setAIState(AISTATE_IDLE);
        else if (performingSkill())
            attemptStopOfActiveSkill();
    }
    switch (m_eAIState)
    {
    case 0:
        if (!performingAttack() && !performingSkill())
            setAIState(AISTATE_IDLE);
        break;
    case 1: fidgetAI(elapsed, *level); break;
    case 2: idleAI(elapsed, *level, force); break;
    case 3: attackAI(elapsed, *level); break;
    case 4: huntAI(elapsed, *level); break;
    case 5: dyingAI(elapsed, *level); break;
    case 7: getItemAI(elapsed, *level); break;
    case 9: approachAI(elapsed, *level); break;
    case 10: fleeAI(elapsed, *level); break;
    case 11: getRangeAI(elapsed, *level); break;
    case 12: spawningAI(elapsed, *level); break;
    case 13: skillAI(elapsed, *level); break;
    case 14: performingSkillAI(elapsed); break;
    case 15: skillApproachAI(elapsed, *level, -1); break;
    case 16: jumpDownAI(elapsed, *level); break;
    case 29: interruptAI(elapsed, *level); break;
    case 35: animationPlayAI(elapsed); break;
    case 41: returnToTownAI(elapsed, *level); break;
    default: break;
    }
}

void CMonster::reactToDamage(CCharacter* attacker, bool critical)
{
    if (!alive() || m_pResourceManager->getGameClient()->m_cameraState == 1 ||
        m_eAIState == 16 || m_eAIState == 41 || m_eAIState == 40 ||
        m_eAIState == 35 || m_eAIState == 42)
        return;
    if (m_eAIState == 1)
        blendAnimation("IDLE", true, 0.1f, 1.0f, -1.0f);
    if (!attacker || attacker == this || m_eAIState == 10 || isPetNearDeath())
        return;
    CSettings* settings = m_pResourceManager ? CMasterResourceManager::getSingleton()->m_pSettings : NULL;
    if (settings->GetInt(KSETTINGS_PLAYER_UNTARGETABLE) == 1)
        return;
    m_aiThinkTime = KAIThinkTime[m_aiThinkTier];
    if (critical && ISA(static_cast<UNITTYPES::EUNITTYPES>(167)))
        removeUnitTheme(L"MIMICIDLE");
    float maximum = static_cast<float>(maxHP());
    float current = std::min(maximum, static_cast<float>(HP()));
    bool flee = false;
    if (maximum > 0.0f && critical)
    {
        if (!m_petMode)
            flee = true;
        else if (1.0f - getBravery() > current / maximum)
        {
            if (!m_petMode || UTILITIES::randomIntegerBetweenVolatile(0, 100) < 50)
                flee = true;
        }
    }
    if (flee)
    {
        interrupt(true);
        setAIState(static_cast<EAIState>(10));
        if (getLevel())
        {
            Ogre::Vector3 difference = getPosition(true) - attacker->getPosition(true);
            difference.normalise();
            float distance = UTILITIES::randomBetweenVolatile(3.0f, 5.0f);
            Ogre::Vector3 position = getPosition(true);
            setDestination(*getLevel(), position.x + difference.x * distance, position.z + difference.z * distance);
        }
        return;
    }
    if (!attacker->alive() || !isEnemy(attacker) || !attacker->m_damageShapeEnabled)
        return;
    if (UTILITIES::randomIntegerBetweenVolatile(0, 100) < 10 &&
        (!m_targetCharacter.getObject() || m_targetCharacter.getObject() != attacker) && m_eAIState != 10)
    {
        setTarget(NULL);
        setAIState(AISTATE_IDLE);
    }
    if (m_petMode && (m_eAIState == 2 || m_eAIState == 0 || m_eAIState == 1))
    {
        stopPathing();
        setAIState(static_cast<EAIState>(4));
        setTarget(attacker);
        if (m_levelSound)
            m_levelSound->playSample(13, m_pSceneNode, 0.0f, 0.0f, false);
    }
}

#include "AIManager.h"
#include "LevelTemplateData.h"

void CMonster::huntAI(float, CLevel& level)
{
    if (!m_targetCharacter.getObject() || !m_targetCharacter.getObject()->alive() ||
        isPetNearDeath() || m_targetCharacter.getObject()->isPetNearDeath() ||
        !canAttackWithCurrentWeapon() || !m_targetCharacter.getObject() || !m_targetCharacter.getObject()->alive())
    {
        setAIState(AISTATE_IDLE);
        setTarget(NULL);
        return;
    }
    if (isFriend(m_targetCharacter.getObject()))
    {
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        return;
    }
    if (m_allowJumpDown)
    {
        if (!m_targetCharacter.getObject())
            return;
        float targetHeight = m_targetCharacter.getObject()->getPosition(true).y;
        if (getPosition(false).y - 1.0f > targetHeight)
            attemptJumpDown();
    }
    if (!m_targetCharacter.getObject())
        return;
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(1)))
    {
        CCharacter* target = calculateTargetInSight(static_cast<EAlignment>(3), true);
        if (target && target != m_targetCharacter.getObject())
        {
            Ogre::Vector3 position = getPosition(true);
            float currentDistance = (m_targetCharacter.getObject()->getPosition(true) - position).length();
            position = getPosition(true);
            float newDistance = (target->getPosition(true) - position).length();
            if (currentDistance - 0.1f > newDistance)
                setTarget(target);
        }
    }
    Ogre::Vector3 position = getPosition(true);
    Ogre::Vector3 targetPosition = m_targetCharacter.getObject()->getPosition(true);
    Ogre::Vector3 distance(targetPosition.x - position.x, 0.0f, targetPosition.z - position.z);
    float length = distance.length();
    m_returningToTown = length >= m_nearWalkRadius;
    float followRange = m_followRange;
    float bonus = getEffectValue(static_cast<EEFFECT_TYPE>(44), DAMAGE_TYPE_COUNT);
    float limit = followRange + (bonus * followRange) / 100.0f + getLevel()->getLevelTemplateData()->getSightRangeModifier();
    if (length >= limit && !m_pMaster)
    {
        stopPathing();
        setAIState(AISTATE_IDLE);
        setTarget(NULL);
        return;
    }
    bool lineOfSight = validLineOfSight(level, false);
    if ((!inAttackRange(ATTACK_RANGE_DEFAULT) || !lineOfSight) && m_pathGraceTime > 0.5f)
    {
        if (walkingSpeed() == 0.0f && runningSpeed() == 0.0f)
        {
            setAIState(AISTATE_IDLE);
            return;
        }
        if (m_aiType == 3 && UTILITIES::randomIntegerBetweenVolatile(0, 100) < 10)
        {
            setAIState(static_cast<EAIState>(10));
            return;
        }
        if (m_aiType == 1 && UTILITIES::randomIntegerBetweenVolatile(0, 100) < 10)
        {
            setAIState(static_cast<EAIState>(10));
            return;
        }
        if (m_aiType == 4 && UTILITIES::randomIntegerBetweenVolatile(0, 100) < 10)
        {
            setAIState(static_cast<EAIState>(11));
            float upperZ = m_targetCharacter.getObject()->getPosition(false).z + 3.0f;
            float lowerZ = m_targetCharacter.getObject()->getPosition(true).z - 3.0f;
            float z = UTILITIES::randomBetweenVolatile(lowerZ, upperZ);
            float upperX = m_targetCharacter.getObject()->getPosition(false).x + 3.0f;
            float lowerX = m_targetCharacter.getObject()->getPosition(true).x - 3.0f;
            float x = UTILITIES::randomBetweenVolatile(lowerX, upperX);
            setDestination(level, x, z);
            return;
        }
        bool follow = !m_isPathing;
        if (!follow)
        {
            targetPosition = m_targetCharacter.getObject()->getPosition(true);
            distance = Ogre::Vector3(targetPosition.x - m_targetPosition.x, 0.0f, targetPosition.z - m_targetPosition.z);
            follow = distance.length() >= 1.0f;
        }
        if (follow)
            followCharacter(m_targetCharacter.getObject(), level);
        if (!m_isPathing)
        {
            setAIState(AISTATE_IDLE);
            return;
        }
    }
    if (inAttackRange(ATTACK_RANGE_DEFAULT) && lineOfSight)
    {
        setAIState(static_cast<EAIState>(3));
        attackAI(0.0f, level);
        stopPathing();
        return;
    }
    if (m_activeSkill &&
        (m_activeSkill->m_property ? m_activeSkill->m_property :
            (m_activeSkill->m_iSkillLevelCount ? m_activeSkill->m_levelPropertyData[0] : NULL))->m_iSkillLevel == 2 &&
        canCastCurrentSkill(m_targetCharacter.getObject(), false, false))
    {
        setAIState(static_cast<EAIState>(13));
        skillAI(0.0f, level);
        return;
    }
    if (UTILITIES::randomIntegerBetweenVolatile(0, 100) < 10)
        selectOffensiveSkill(false);
    if (m_pMaster && m_targetCharacter.getObject())
    {
        targetPosition = m_targetCharacter.getObject()->getPosition(true);
        Ogre::Vector3 masterPosition = m_pMaster->getPosition(true);
        distance = Ogre::Vector3(masterPosition.x - targetPosition.x, 0.0f, masterPosition.z - targetPosition.z);
        if (distance.length() > 35.0f)
        {
            setTarget(NULL);
            setAIState(AISTATE_IDLE);
        }
    }
}

#include "Equipment.h"

void CMonster::attackAI(float elapsed, CLevel& level)
{
    if (m_attackDelay > 0.0f)
    {
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        return;
    }
    if (m_targetItem.getObject())
        setTargetItem(NULL);
    if (!m_targetCharacter.getObject() || !m_targetCharacter.getObject()->alive() || isPetNearDeath() ||
        m_targetCharacter.getObject()->isPetNearDeath() || !m_targetCharacter.getObject()->alive() ||
        m_targetCharacter.getObject()->m_eAIState == 42 || m_targetCharacter.getObject()->m_eAIState == 41)
    {
        setAIState(AISTATE_IDLE);
        setTarget(NULL);
        return;
    }
    if (isFriend(m_targetCharacter.getObject()))
    {
        setAIState(static_cast<EAIState>(0));
        setTarget(NULL);
        return;
    }
    if (!m_attack || m_attackFlag1F5)
    {
        selectAttack(ATTACK_RANGE_DEFAULT);
        if (!m_attack || m_attackFlag1F5)
        {
            setActiveSkill(NULL, false);
            selectOffensiveSkill(true);
            if (m_activeSkill && inSkillRange(-1, false) == 0)
                castSkill(-1);
            return;
        }
    }
    Ogre::Vector3 position = getPosition(true);
    Ogre::Vector3 targetPosition = m_targetCharacter.getObject()->getPosition(true);
    Ogre::Vector3 difference(targetPosition.x - position.x, 0.0f, targetPosition.z - position.z);
    if (difference.length() >= m_followRange)
    {
        stopPathing();
        setAIState(AISTATE_IDLE);
        setTarget(NULL);
        return;
    }
    turnTowardPosition(m_targetCharacter.getObject()->getPosition(true), elapsed);
    if (facingTarget())
    {
        setActiveSkill(NULL, false);
        selectOffensiveSkill(true);
        if (m_activeSkill && inSkillRange(-1, false) == 0)
        {
            castSkill(-1);
            return;
        }
    }
    if (!inAttackRange(ATTACK_RANGE_DEFAULT) || !validLineOfSight(level, false))
    {
        if (!performingAttack())
            setAIState(static_cast<EAIState>(4));
        return;
    }
    if (!performingAttack())
    {
        if (m_aiType == 4 && UTILITIES::randomIntegerBetweenVolatile(0, 100) < 25)
        {
            setAIState(static_cast<EAIState>(11));
            float upperZ = m_targetCharacter.getObject()->getPosition(false).z + 3.0f;
            float lowerZ = m_targetCharacter.getObject()->getPosition(true).z - 3.0f;
            float z = UTILITIES::randomBetweenVolatile(lowerZ, upperZ);
            float upperX = m_targetCharacter.getObject()->getPosition(false).x + 3.0f;
            float lowerX = m_targetCharacter.getObject()->getPosition(true).x - 3.0f;
            float x = UTILITIES::randomBetweenVolatile(lowerX, upperX);
            setDestination(level, x, z);
            return;
        }
        if (facingTarget())
        {
            selectAttack(ATTACK_RANGE_DEFAULT);
            if (attack())
            {
                if (m_attackItem)
                    m_attackDelay = std::max(0.0f, m_attackDelay) + static_cast<CEquipment*>(m_attackItem)->m_fUnknown408;
                m_attackDelay = std::max(m_attackDelay, 0.0f) + m_initialAttackDelay;
            }
        }
    }
    if (!canAttackWithCurrentWeapon())
        setAIState(static_cast<EAIState>(10));
}

#include <cstdlib>

void CMonster::idleAI(float elapsed, CLevel& level, bool flag)
{
    bool handled = false;
    if (getEnabled() && !m_pathToFollow.getObject())
    {
        switch (m_aiType)
        {
        case 0: case 2: case 5: handled = idleAINormal(elapsed, level, flag); break;
        case 1: handled = idleAIRangedDefender(elapsed, level, flag); break;
        case 3: handled = idleAIRangedCaster(elapsed, level, flag); break;
        case 4: handled = idleAICircler(elapsed, level, flag); break;
        default: break;
        }
    }
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(167)))
    {
        if (m_eAIState == 2)
        {
            if (hasUnitTheme(L"MIMICIDLE"))
                return;
        }
        else
            removeUnitTheme(L"MIMICIDLE");
    }
    if (handled)
        return;
    if (m_pUnitModel && getEnabled() && !m_isPathing && !m_pathToFollow.getObject() && m_eAIState == 2 &&
        UTILITIES::randomIntegerBetweenVolatile(0, 1000) < 10)
    {
        if (m_fidgetTime <= 10.0f)
            return;
        if (!m_pUnitModel->animationExistsSubstring("FIDGET"))
            return;
        m_pUnitModel->blendAnimation(m_pUnitModel->findRandomAnimation("FIDGET"), false, 0.2f, 1.0f, -1.0f);
        queueBlendAnimation("IDLE", true, 0.2f, 1.0f);
        setAIState(static_cast<EAIState>(1));
        if (m_levelSound)
            m_levelSound->playSample(11, m_pSceneNode, 0.0f, 0.0f, false);
        m_idleSoundTime = 0.0f;
        m_fidgetTime = 0.0f;
        return;
    }
    if (walkingSpeed() == 0.0f || m_monsterFlag)
        return;
    bool holdPosition = m_targetCharacter.getObject() &&
        m_targetCharacter.getObject()->ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) &&
        m_targetCharacter.getObject()->m_targetCharacter.getObject() == this && ISA(static_cast<UNITTYPES::EUNITTYPES>(131));
    if (holdPosition)
    {
        if (m_pathToFollow.getObject())
            updatePathFollowing(false);
        else
            stopPathing();
    }
    else if (m_pathToFollow.getObject())
        updatePathFollowing(false);
    else if (!m_isPathing && UTILITIES::randomBetweenVolatile(0.0f, 1000.0f) < 100.0f)
    {
        if (m_pMaster && getEnabled() && !ISA(static_cast<UNITTYPES::EUNITTYPES>(169)))
        {
            Ogre::Vector3 center = m_pMaster->getPosition(true);
            const Ogre::Vector3& forward = m_pMaster->getForward();
            float centerX = center.x + forward.x * 3.0f;
            float centerZ = center.z + forward.z * 3.0f;
            float upperZ = m_pMaster->getPosition(true).z + 7.2f;
            float z = UTILITIES::randomBetweenVolatile(centerZ - 7.2f, upperZ);
            float upperX = m_pMaster->getPosition(true).x + 7.2f;
            float x = UTILITIES::randomBetweenVolatile(centerX - 7.2f, upperX);
            setDestination(level, x, z);
        }
        else if (getEnabled())
        {
            float z = UTILITIES::randomBetweenVolatile(m_vPosition.z - 8.0f, m_vPosition.z + 8.0f);
            float x = UTILITIES::randomBetweenVolatile(m_vPosition.x - 8.0f, m_vPosition.x + 8.0f);
            setDestination(level, x, z);
        }
        else
            stopPathing();
    }
    if (!m_pMaster || attachesToMaster() || m_pathToFollow.getObject() || !getEnabled() ||
        ISA(static_cast<UNITTYPES::EUNITTYPES>(169)))
        return;
    m_returningToTown = m_pMaster->m_returningToTown && m_pMaster->m_runningSpeed > m_pMaster->m_walkingSpeed;
    if (m_petMode && m_pMaster->m_targetCharacter.getObject() && isEnemy(m_pMaster->m_targetCharacter.getObject()) && !isPetNearDeath())
    {
        Ogre::Vector3 targetPosition = m_pMaster->m_targetCharacter.getObject()->getPosition(true);
        Ogre::Vector3 masterPosition = m_pMaster->getPosition(true);
        Ogre::Vector3 distance(masterPosition.x - targetPosition.x, 0.0f, masterPosition.z - targetPosition.z);
        if (distance.length() <= 8.0f)
        {
            setTarget(m_pMaster->m_targetCharacter.getObject());
            setAIState(static_cast<EAIState>(4));
            return;
        }
    }
    Ogre::Vector3 position = getPosition(true);
    Ogre::Vector3 masterPosition = m_pMaster->getPosition(true);
    Ogre::Vector3 difference(masterPosition.x - position.x, 0.0f, masterPosition.z - position.z);
    float masterDistance = difference.length();
    if (masterDistance > 6.0f)
        m_returningToTown = true;
    else if (masterDistance <= 8.0f && !m_pMaster->m_isPathing)
        m_returningToTown = false;
    if (masterDistance > 25.0f && walkingSpeed() > 0.0f)
        teleportToMaster(20.0f);
    if (isPetNearDeath())
        m_returningToTown = true;
    float distance;
    if (m_isPathing)
    {
        masterPosition = m_pMaster->getPosition(true);
        difference = Ogre::Vector3(masterPosition.x - m_targetPosition.x, 0.0f, masterPosition.z - m_targetPosition.z);
        distance = difference.length();
    }
    else
    {
        position = getPosition(true);
        masterPosition = m_pMaster->getPosition(true);
        difference = Ogre::Vector3(masterPosition.x - position.x, 0.0f, masterPosition.z - position.z);
        distance = difference.length();
    }
    if (std::rand() % 1000 < 100 || distance > 8.0f || isPetNearDeath())
    {
        if (isPetNearDeath())
            setAIState(static_cast<EAIState>(10));
        if ((isPetNearDeath() && !m_isPathing) || (distance > 8.0f && m_pathGraceTime > 0.25f))
        {
            m_returningToTown = true;
            Ogre::Vector3 center = m_pMaster->getPosition(true);
            const Ogre::Vector3& forward = m_pMaster->getForward();
            float centerX = center.x + forward.x * 3.0f;
            float centerZ = center.z + forward.z * 3.0f;
            float upperZ = m_pMaster->getPosition(true).z + 7.2f;
            float z = UTILITIES::randomBetweenVolatile(centerZ - 7.2f, upperZ);
            float upperX = m_pMaster->getPosition(true).x + 7.2f;
            float x = UTILITIES::randomBetweenVolatile(centerX - 7.2f, upperX);
            setDestination(level, x, z);
        }
    }
}
