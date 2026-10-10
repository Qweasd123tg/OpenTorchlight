void CGameUI::toggleStats()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_characterStatsMenu->openPartial() || !modalDialogOpen()) {
        if (!m_characterStatsMenu->openPartial()) closeLeft();
        m_characterStatsMenu->setOpen(!m_characterStatsMenu->openPartial());
        m_topWindow->moveToFront();
    }
}
