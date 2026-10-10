bool CGameUI::handle_ToggleMap(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_level && !m_paused) m_level->toggleAutomap();
    return true;
}
