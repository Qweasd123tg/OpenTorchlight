bool CGameClient::getPlayerIsCheat()
{
    return m_pPlayer && m_pPlayer->m_cheatMarker == 0xd6;
}
