void CCharacter::reclaimMagicPoint()
{
    if (m_magicStat > 2)
    {
        ++m_iUnusedStatPoints;
        --m_magicStat;
    }
}
