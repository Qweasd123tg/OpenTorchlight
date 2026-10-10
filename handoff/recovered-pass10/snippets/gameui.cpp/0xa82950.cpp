bool CGameUI::getDieMenuIsOpen()
{
    return m_dieMenu ? (m_dieMenu->m_bUnknown30 || !m_dieMenu->m_bUnknown31) : false;
}
