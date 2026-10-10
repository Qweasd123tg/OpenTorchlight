bool CGameUI::handle_ToggleStats(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    gToggleStats = true;
    return true;
}
