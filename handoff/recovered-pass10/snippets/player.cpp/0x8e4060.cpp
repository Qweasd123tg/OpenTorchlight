void CPlayer::removeLevelSavedState(unsigned int index)
{
    if (static_cast<int>(index) < static_cast<int>(m_savedLevels.size())) {
        if (m_savedLevels[static_cast<int>(index)]) { delete m_savedLevels[static_cast<int>(index)]; m_savedLevels[static_cast<int>(index)] = NULL; }
        m_savedLevels[static_cast<int>(index)] = m_savedLevels[m_savedLevels.size() - 1];
    }
    m_savedLevels.pop_back();
}
