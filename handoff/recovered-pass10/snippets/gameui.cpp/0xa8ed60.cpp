void CGameUI::toggleDialog()
{
    if (m_dropdown530) {
        unPause();
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
        m_dropdown530->setOpen(!m_dropdown530->m_bUnknown30);
    }
}
