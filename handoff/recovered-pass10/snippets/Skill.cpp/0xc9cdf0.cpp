unsigned int CSkill::getManaCostOT()
{
    return m_property ? static_cast<unsigned int>(m_property->m_iManaCostOverTime) : 0;
}
