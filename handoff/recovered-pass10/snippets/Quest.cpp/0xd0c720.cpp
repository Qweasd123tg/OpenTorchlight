void CQuest::setQuestAcceptDialogInteracted(bool value)
{
    for (unsigned int i = 0; i < m_acceptDialogs.size(); ++i) m_acceptDialogs[i]->m_bDialogInitialized = value;
}
