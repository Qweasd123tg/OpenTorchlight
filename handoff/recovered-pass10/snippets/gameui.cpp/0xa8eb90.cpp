void CGameUI::toggleOptions()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (!m_optionsMenu->m_bUnknown30) closeAll();
    if (m_optionsMenu) {
        m_dialogMenu->setOpen(false);
        m_optionsMenu->setOpen(!m_optionsMenu->m_bUnknown30);
    }
}
