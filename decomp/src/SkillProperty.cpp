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


std::wstring CSkillProperty::getSkillDescription()
{
    return m_sDescription;
}

float CSkillProperty::getCoolDown()
{
    if (m_pSkill && m_pSkill->m_pOwner &&
        m_pSkill->m_pOwner->m_eBaseUnitType == 0 &&
        m_pSkill->m_pOwner->ISA(UNITTYPES::MONSTER))
        return m_fMonsterCoolDown;
    return m_fCoolDown;
}

#include "SkillEffectAndAffixes.h"
#include "Character.h"

bool CSkillProperty::applyAffixesAndEffectsToUnit(CCharacter* character, const Ogre::Vector3* position)
{
    if (character && !m_pSkillEffectAndAffixes)
        return false;
    CCharacter* owner = dynamic_cast<CCharacter*>(m_pSkill->getMasterOwner());
    return m_pSkillEffectAndAffixes->applyAffixesAndEffects(character, owner, position, false);
}
