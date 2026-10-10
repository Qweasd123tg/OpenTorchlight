void CGameUI::toggleQuest()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_questMenu->openPartial() || !modalDialogOpen()) {
        if (!m_questMenu->openPartial()) closeRight();
        m_questMenu->setOpen(!m_questMenu->openPartial());
        m_topWindow->moveToFront();
    }
}
