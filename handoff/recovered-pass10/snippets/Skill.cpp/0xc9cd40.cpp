bool CSkill::getCanStop()
{
    return !m_property || m_elapsedSkillTime >= m_property->m_fMinimumTime;
}
