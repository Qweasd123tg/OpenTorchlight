void CEffect::playFX(CResourceManager* manager, const Ogre::Vector3& position)
{
    if (!m_particle) {
        m_particle=manager->createParticle(m_particleName.c_str());
        if (m_particle) {
            m_particle->setPosition(position);
            m_particle->Start();
        }
    }
}
