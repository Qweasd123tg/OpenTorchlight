bool CLevel::isDormant()
{
    if (m_pGameClient) return m_pGameClient->m_bStateControl10BC;
    return false;
}
