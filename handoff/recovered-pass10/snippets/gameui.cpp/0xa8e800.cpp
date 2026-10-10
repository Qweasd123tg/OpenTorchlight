bool CGameUI::handle_ToggleQuest(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    toggleQuest();
    return true;
}
