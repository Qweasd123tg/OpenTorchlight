void CSoundManager::updateAudioLevels(float soundVolume, float musicVolume, bool soundMute, bool musicMute)
{
    if (!m_bUnknown6A8) return;
    FMOD::SoundGroup* sounds;
    if (m_iUnknown18->getMasterSoundGroup(&sounds) == FMOD_OK) sounds->setVolume(soundVolume);
    FMOD::ChannelGroup* channels;
    if (m_iUnknown18->getMasterChannelGroup(&channels) == FMOD_OK) { channels->setVolume(soundVolume); channels->setMute(soundMute); }
    if (m_iUnknown6D0) {
        m_iUnknown6E0->setVolume(musicVolume);
        if (m_iUnknown6D8) {
            FMOD::Channel* channel;
            m_iUnknown18->getChannel(m_iUnknown6D8, &channel);
            channel->setMute(musicMute);
        }
    }
}
