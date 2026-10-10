std::wstring CQuest::getQuestDetails()
{
    if (m_pQuestDialog) return replaceStringTags(m_pQuestDialog->getDialog(false));
    return EMPTY_WSTRING;
}
