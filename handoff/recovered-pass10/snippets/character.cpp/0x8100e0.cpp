bool CCharacter::isImmobile()
{
    return hasEffect(static_cast<EEFFECT_TYPE>(0x3f)) || m_moveSpeed == 0.0f;
}
