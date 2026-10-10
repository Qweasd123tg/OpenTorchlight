bool CGameUI::handle_ClickThrough(const CEGUI::EventArgs& event)
{
    m_mouseThrough = true;
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    return true;
}
