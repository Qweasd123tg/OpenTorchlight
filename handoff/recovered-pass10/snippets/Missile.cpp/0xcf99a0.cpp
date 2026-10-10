std::wstring CMissile::getParticleFile(EMISSILE_PARTICLES particle)
{
    if(m_particles[particle])return m_particleFiles[particle];
    return EMPTY_WSTRING;
}
