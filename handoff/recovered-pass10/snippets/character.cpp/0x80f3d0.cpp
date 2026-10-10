float CCharacter::getBravery()
{
    if (m_pAIManager && m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(3)))
        return m_bravery * 0.5f;
    return m_bravery;
}
