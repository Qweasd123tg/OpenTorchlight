void CCharacter::reclaimDefensePoint()
{
    if (m_defenseStat > 2)
    {
        ++m_iUnusedStatPoints;
        --m_defenseStat;
    }
}
