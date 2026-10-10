void CGameUI::toggleWaypointMenu()
{
    if (m_waypointMenu) {
        unPause();
        closeAll();
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
        m_optionsMenu->setOpen(false);
        m_dialogMenu->setOpen(false);
        m_waypointMenu->setOpen(!m_waypointMenu->m_bUnknown30);
    }
}
