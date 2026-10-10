void CCharacter::showCharacterText()
{
    if (m_characterText && !m_characterTextVisible)
    {
        m_characterTextVisible = true;
        m_characterTextParent->addChildWindow(m_characterText);
    }
}
