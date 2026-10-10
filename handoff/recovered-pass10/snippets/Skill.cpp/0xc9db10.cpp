bool CSkill::rollCancelChance()
{
    if (m_iCancelChance > 99) return true;
    return UTILITIES::randomIntegerBetweenVolatile(0, 100) <= m_iCancelChance;
}
