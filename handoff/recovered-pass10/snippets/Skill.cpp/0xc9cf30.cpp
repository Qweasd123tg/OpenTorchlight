unsigned int CSkill::getChanceToCast()
{
    return m_property ? m_property->m_iChance : static_cast<unsigned int>(-1);
}
