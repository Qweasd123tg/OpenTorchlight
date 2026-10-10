bool CGameUI::modalDialogOpenPartial()
{
    for (unsigned int i = 0; i < m_dropdowns.size(); ++i)
        if (m_dropdowns[i]->m_bUnknown30) return true;
    return false;
}
