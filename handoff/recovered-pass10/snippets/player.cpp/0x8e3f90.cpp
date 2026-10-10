void CPlayer::resetLevel()
{
    m_iUnitLevel = 1; m_experience = 0; m_fame = 0;
    calculateMaxHP();
    m_fHPFloat = static_cast<float>(m_maxHPBase);
    calculateMaxMana();
    m_fManaFloat = static_cast<float>(m_maxManaBase);
}
