unsigned int CSkill::getManaCost()
{
    return m_property ? static_cast<unsigned int>(m_property->m_iManaCost) : 0;
}
