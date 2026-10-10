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
