void CCharacter::spendDefensePoint()
{
    int points = m_iUnusedStatPoints;
    if (points <= 0) return;
    ++m_defenseStat;
    m_iUnusedStatPoints = points - 1;
}
