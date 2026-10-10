void CGameUI::togglePet()
{
    unPause();
    CEGUI::Window* window = m_foldout->m_window;
    if (window->getParent()) window->getParent()->removeChildWindow(window);
    if (m_inventoryMenu->openPartial() || !modalDialogOpen()) {
        if (!m_inventoryMenu->openPartial()) closeLeft();
        m_inventoryMenu->setOpen(!m_inventoryMenu->openPartial());
        m_topWindow->moveToFront();
    }
}
