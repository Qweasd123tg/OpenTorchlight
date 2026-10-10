bool CGameUI::handle_ToggleOptions(const CEGUI::EventArgs& event)
{
    closeAll();
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    m_optionsMenu->setOpen(true);
    return true;
}
