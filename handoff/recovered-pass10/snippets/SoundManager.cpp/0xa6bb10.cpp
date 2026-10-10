void CSoundInstance::clear()
{
    m_soundName.clear();
    m_stream.setNull();
    m_pSound->release();
    m_pSound = NULL;
    m_soundType = static_cast<SOUND_TYPE>(0);
    m_referenceCount = 0;
    m_pSoundData = NULL;
}
