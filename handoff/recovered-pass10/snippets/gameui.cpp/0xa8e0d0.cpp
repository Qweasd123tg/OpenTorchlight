void CGameUI::closeAll()
{
    closeLeft();
    closeRight();
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    m_questDialogMenu->setOpen(false);
    m_dropdown530->setOpen(false);
    m_dropdown548->setOpen(false);
    m_tipMenu->setOpen(false);
}
