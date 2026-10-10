 CSoundInstance::~CSoundInstance()
{
    if (m_pSound) { m_pSound->release(); m_pSound = NULL; }
}
