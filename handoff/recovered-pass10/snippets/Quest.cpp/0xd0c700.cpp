CPlayer* CQuest::getPlayer()
{
    if (m_pQuestManager) return m_pQuestManager->m_pPlayer;
    return NULL;
}
