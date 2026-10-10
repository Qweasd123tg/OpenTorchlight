void CCharacter::spendMagicPoint()
{
    int points = m_iUnusedStatPoints;
    if (points <= 0) return;
    ++m_magicStat;
    m_iUnusedStatPoints = points - 1;
}
