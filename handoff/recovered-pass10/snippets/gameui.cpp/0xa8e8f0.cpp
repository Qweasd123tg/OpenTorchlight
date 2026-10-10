bool CGameUI::handle_ToggleJournal(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    toggleJournal();
    return true;
}
