bool CGameUI::handle_ToggleSkill(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    toggleSkill();
    return true;
}
