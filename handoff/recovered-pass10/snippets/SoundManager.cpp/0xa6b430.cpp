std::wstring CSoundManager::getMusicFilePlaying()
{
    if (m_iUnknown6D0) return m_iUnknown6D0->m_soundName;
    return EMPTY_WSTRING;
}
