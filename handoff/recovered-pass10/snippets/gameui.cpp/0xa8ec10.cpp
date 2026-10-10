void CGameUI::toggleDeath()
{
    if (m_dieMenu) {
        unPause();
        closeAll();
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
        m_optionsMenu->setOpen(false);
        m_dialogMenu->setOpen(false);
        m_dieMenu->setOpen(!m_dieMenu->m_bUnknown30);
    }
}
