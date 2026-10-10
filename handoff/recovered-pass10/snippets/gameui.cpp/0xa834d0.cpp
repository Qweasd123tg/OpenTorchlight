void CGameUI::refreshQuestMenu()
{
    if (m_questMenu->open() || m_questMenu->openPartial()) m_questMenu->updateLayout();
}
