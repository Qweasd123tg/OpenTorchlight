void CCharacter::reclaimRangedPoint()
{
    if (m_rangedStat > 2)
    {
        ++m_iUnusedStatPoints;
        --m_rangedStat;
    }
}
