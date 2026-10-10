class CParticlePreloader;
extern CParticlePreloader* m_gParticlePreloader;
#include "GameVariables.h"
#include "ParticleCache.h"
#include "ParticlePreloader.h"


// Imported source candidates; historical status is not fresh acceptance.
CParticlePreloader* CParticlePreloader::getSingleton()
{
    return m_gParticlePreloader;
}

void CParticlePreloader::ReloadEditorParticles()
{
}

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

void CParticlePreloader::unloadParticlesOnLevelUnload()
{
    for (std::map<std::wstring, TArrayList<CParticleCache*>*>::iterator it = m_particleCaches.begin(); it != m_particleCaches.end(); ++it) {
        TArrayList<CParticleCache*>* list = it->second;
        unsigned int count = list->size() / 2;
        for (unsigned int i = 0; i < count; ++i) {
            CParticleCache* cache = (*list)[0];
            list->removeAt(0);
            if (cache) delete cache;
        }
    }
}
