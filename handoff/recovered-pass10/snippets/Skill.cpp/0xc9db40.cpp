bool CSkill::rollCastChance()
{
    if (m_iChance > 99) return true;
    return UTILITIES::randomIntegerBetweenVolatile(0, 100) <= m_iChance;
}
