bool CGameUI::isCinematicMenuOpen()
{
    return m_cinematicMenu ? (m_cinematicMenu->m_bUnknown30 || !m_cinematicMenu->m_bUnknown31) : false;
}
