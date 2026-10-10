void CGameUI::removeMenuListener(EMENU_TYPE type, iMenuListener* listener)
{
    if (type == 0)
    {
        if (m_questDialogMenu) m_questDialogMenu->removeMenuListener(listener);
    }
    else if (type == 1)
    {
        if (m_cinematicMenu) m_cinematicMenu->removeMenuListener(listener);
    }
}
