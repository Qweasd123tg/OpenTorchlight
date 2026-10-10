bool CGameUI::questDialogOpen()
{
    return m_questDialogMenu ? (m_questDialogMenu->m_bUnknown30 || !m_questDialogMenu->m_bUnknown31) : false;
}
