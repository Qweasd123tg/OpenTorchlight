bool CCharacter::animationExists(const std::string& animation) const
{
    return m_pUnitModel ? m_pUnitModel->animationExists(animation) : false;
}
