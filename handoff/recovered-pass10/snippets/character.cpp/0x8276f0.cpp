bool CCharacter::facingTarget()
{
    if (m_targetCharacter || m_targetItem) return facingTarget(m_targetCharacter, m_targetItem);
    return false;
}
