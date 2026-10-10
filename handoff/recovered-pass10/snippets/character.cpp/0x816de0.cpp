void CCharacter::hideCharacterText()
{
    if (m_characterText && m_characterTextVisible)
    {
        m_characterTextVisible = false;
        m_characterTextParent->removeChildWindow(m_characterText);
    }
}
