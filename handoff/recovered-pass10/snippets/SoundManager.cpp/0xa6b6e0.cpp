FMOD::SoundGroup* CSoundManager::createSoundGroup(std::string name)
{
    if (!m_iUnknown18) return NULL;
    FMOD::SoundGroup* group;
    m_iUnknown18->createSoundGroup(name.c_str(), &group);
    return group;
}
