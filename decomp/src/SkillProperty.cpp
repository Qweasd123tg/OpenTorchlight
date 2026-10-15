#include "SkillProperty.h"
#include "Skill.h"
#include "BaseUnit.h"
#include "Character.h"


CBaseUnit* CSkillProperty::getOwner()
{
    return m_pSkill ? m_pSkill->m_pOwner : NULL;
}

CCharacter* CSkillProperty::getOwnerCharacter()
{
    if (m_pSkill)
    {
        CBaseUnit* owner = m_pSkill->m_pOwner;
        if (owner && owner->m_eBaseUnitType == 0)
            return static_cast<CCharacter*>(owner);
    }
    return NULL;
}

