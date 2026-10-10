void CGameClient::reloadSoundBankData()
{
    if (m_masterResources) { m_soundManager->stopAllSounds(); m_masterResources->reloadSoundBankData(); }
}
