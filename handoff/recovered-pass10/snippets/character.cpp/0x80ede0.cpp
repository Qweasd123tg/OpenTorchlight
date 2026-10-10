void CCharacter::setAllowJumpDown(bool allow)
{
    if (m_allowJumpDown != allow)
    {
        m_allowJumpDown = allow;
        updateAI(0.0f, true);
    }
}
