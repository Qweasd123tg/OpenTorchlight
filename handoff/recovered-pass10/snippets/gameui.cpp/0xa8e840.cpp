void CGameUI::toggleJournal()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_journalMenu->openPartial() || !modalDialogOpen()) {
        if (!m_journalMenu->openPartial()) closeRight();
        m_journalMenu->setOpen(!m_journalMenu->openPartial());
        m_topWindow->moveToFront();
    }
}
