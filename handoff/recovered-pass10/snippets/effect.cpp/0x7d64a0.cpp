bool CEffect::fxShouldPlay()
{
    if (m_particle && m_particle->m_pParticleCache) return false;
    return m_particleName != EMPTY_WSTRING;
}
