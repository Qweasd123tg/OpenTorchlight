void CGameClient::destroyGameUI()
{
    if (m_pGameUI) { delete m_pGameUI; m_pGameUI = NULL; }
    m_pGameUI = NULL;
}
