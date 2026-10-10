void CGameUI::flushInput()
{
    m_mouseThrough = false;
    m_leftSlot = -1;
    m_rightSlot = -1;
    m_pendingRightSlot = -1;
    m_keys.flushAll();
    m_mouse.flushAll();
}
