void CMasterResourceManager::createParticleReloader()
{
    if (!m_pParticlePreloader) m_pParticlePreloader = new CParticlePreloader(m_resourceSettings);
}
