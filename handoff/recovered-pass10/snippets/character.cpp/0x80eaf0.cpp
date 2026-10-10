void CCharacter::spendRangedPoint()
{
    int points = m_iUnusedStatPoints;
    if (points <= 0) return;
    ++m_rangedStat;
    m_iUnusedStatPoints = points - 1;
}
