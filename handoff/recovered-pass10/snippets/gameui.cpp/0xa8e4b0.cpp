void CGameUI::toggleSettings()
{
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    m_optionsMenu->setOpen(false);
    if (m_dialogMenu) m_dialogMenu->setOpen(!m_dialogMenu->m_bUnknown30);
}
