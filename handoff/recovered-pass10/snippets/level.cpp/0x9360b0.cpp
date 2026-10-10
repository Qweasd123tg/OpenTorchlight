bool CLevel::getAutomapVisible()
{
    if (m_automap && !m_automap->m_bFullscreen) return m_automap->m_bVisible;
    return false;
}
