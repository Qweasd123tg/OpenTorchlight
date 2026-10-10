void CCharacter::setVisible(bool visible)
{
    m_characterVisible = (!m_forcedHidden) & visible;
}
