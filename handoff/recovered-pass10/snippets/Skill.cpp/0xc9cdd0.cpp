bool CSkill::getCanBeInterrupted()
{
    return m_property ? m_property->m_bInterruptable : false;
}
