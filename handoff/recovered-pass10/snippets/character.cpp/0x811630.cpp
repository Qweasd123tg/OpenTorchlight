bool CCharacter::animationQueued(const std::string& animation) const
{
    return m_pUnitModel ? m_pUnitModel->animationQueued(animation) : false;
}
