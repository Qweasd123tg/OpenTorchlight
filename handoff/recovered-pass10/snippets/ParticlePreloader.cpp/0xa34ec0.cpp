void CParticlePreloader::aggressiveUnloadParticles()
{
    for (std::map<std::wstring, TArrayList<CParticleCache*>*>::iterator it = m_particleCaches.begin(); it != m_particleCaches.end(); ++it) {
        TArrayList<CParticleCache*>* list = it->second;
        unsigned int count = list->size();
        for (unsigned int i = 1; i < count; ++i) {
            CParticleCache* cache = (*list)[0];
            list->removeAt(0);
            if (cache) delete cache;
        }
    }
}
