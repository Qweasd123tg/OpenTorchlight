bool CGameUI::handle_TogglePet(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    gTogglePet = true;
    return true;
}
