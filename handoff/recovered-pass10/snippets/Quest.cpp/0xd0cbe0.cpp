void CQuest::setIsComplete(bool value)
{
    if (m_complete != value) {
        m_complete = value;
        if (value) m_pQuestManager->questEventUpdate(static_cast<EQUEST_EVENTS>(4), NULL, NULL);
    }
}
