void CMasterResourceManager::reloadSoundBankData()
{
    if (m_pSoundManager && m_pSoundBankDataInformation) {
        m_pSoundManager->stopAllSounds();
        m_pSoundBankDataInformation->reload(m_resourceSettings);
    }
}
