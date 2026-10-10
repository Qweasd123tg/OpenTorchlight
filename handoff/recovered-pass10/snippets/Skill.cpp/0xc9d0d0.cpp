CBaseUnit* CSkill::getMasterOwner()
{
    return m_pSkillManager ? m_pSkillManager->m_Owner.getObject() : NULL;
}
