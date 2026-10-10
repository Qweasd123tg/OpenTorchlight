void CGameUI::toggleSkill()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_skillsMenu->openPartial() || !modalDialogOpen()) {
        if (!m_skillsMenu->openPartial()) closeRight();
        m_skillsMenu->setOpen(!m_skillsMenu->openPartial());
        m_topWindow->moveToFront();
    }
}
