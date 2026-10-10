void CPlayer::clearLevelHistory()
{
    for (int i = 0; i < static_cast<int>(m_savedLevels.size()); ++i)
        if (!m_savedLevels[i]->m_bUnknownB0) { removeLevelSavedState(i); --i; }
}
