std::wstring CGameClient::getPlayerClassName()
{
    if (m_pPlayer) return m_pPlayer->getPlayerClassName();
    return STRINGS::StringUpper(m_editorCreationClass);
}
