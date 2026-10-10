float CCharacter::followRange()
{
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(0)))
        return m_followRange * 2.0f;
    return m_followRange;
}
