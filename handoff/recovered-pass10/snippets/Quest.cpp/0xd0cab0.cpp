int CQuest::getQuestRewardFame()
{
    CQuestRewards* rewards = m_pQuestRewards;
    if (rewards) { rewards->calculateRewards(); return static_cast<int>(rewards->m_fFame); }
    return 0;
}
