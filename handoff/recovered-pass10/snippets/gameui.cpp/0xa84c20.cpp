void CGameUI::closeMenus()
{
    if (m_menuManager) m_menuManager->closeMenus();
    m_mouseThrough = false;
    m_leftSlot = -1;
    m_rightSlot = -1;
    m_pendingRightSlot = -1;
    m_keys.flushAll();
    m_mouse.flushAll();
}
