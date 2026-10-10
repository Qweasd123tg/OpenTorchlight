void CGameUI::toggleFPS()
{
    if (!m_displayStats) {
        m_settings->SetInt(KSETTINGS_DISPLAY_STATS, 1);
        m_rootWindow->addChildWindow(m_statsWindow);
    } else {
        m_settings->SetInt(KSETTINGS_DISPLAY_STATS, 0);
        m_rootWindow->removeChildWindow(m_statsWindow);
    }
    m_displayStats = !m_displayStats;
}
