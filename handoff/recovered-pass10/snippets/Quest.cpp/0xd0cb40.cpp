std::wstring CQuest::getQuestRewardString()
{
    if (m_pQuestRewards) return m_pQuestRewards->getRewardString();
    return EMPTY_WSTRING;
}
