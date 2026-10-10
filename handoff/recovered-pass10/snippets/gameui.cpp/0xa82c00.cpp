bool CGameUI::eitherCoveredPartial()
{
    for (unsigned int i = 0; i < m_submenus.size(); ++i)
        if (m_submenus[i]->openPartial()) return true;
    return false;
}
