bool CCharacter::animationPlaying(const std::string& animation) const
{
    return m_pUnitModel ? m_pUnitModel->animationPlaying(animation) : false;
}
