void CGameClient::keyEvent(unsigned int event, unsigned int key, long character)
{
    if (m_pGameUI) m_pGameUI->keyEvent(event, key, character);
    m_keys.keyEvent(event, key);
}
