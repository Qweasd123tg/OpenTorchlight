#include "EmptyStrings.h"
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

#include "Particle.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include "MasterResourceManager.h"
#include "Layout.h"
namespace ParticleUniverse {
class ParticleSystemManager { public: void removeAllParticleSystemTemplates(); };
}

unsigned int CParticlePreloader::getParticleCacheCount()
{
    unsigned int count = 0;
    for (std::map<std::wstring,TArrayList<CParticleCache*>*>::iterator it = m_particleCaches.begin(); it != m_particleCaches.end(); ++it)
        count += it->second->size();
    return count;
}

void CParticlePreloader::getFileNames(std::wstring& names)
{
    for (std::map<std::wstring,std::wstring>::iterator it = m_particleNames.begin(); it != m_particleNames.end(); ++it)
        names += it->first + L"\n";
    names += L"Total particles loaded: " + STRINGS::GetValueAsWString(static_cast<int>(m_particleNames.size()));
}

std::wstring CParticlePreloader::getParticleNameByFileName(const std::wstring& filename)
{
    std::wstring name = STRINGS::StringUpper(FILESYSTEM::CleanPath(filename));
    std::map<std::wstring,std::wstring>::iterator it = m_particleNames.find(name);
    if (it != m_particleNames.end())
        return it->second;
    return EMPTY_WSTRING;
}

CParticle* CParticlePreloader::GetParticle(CResourceManager* resources, const wchar_t* filename)
{
    if (m_particleScripts.empty())
        return 0;
    return new CParticle(this, filename, resources);
}

void CParticlePreloader::returnParticleCache(CParticleCache* cache)
{
    if (!cache)
        return;
    if (cache->m_pRootSceneNode)
        cache->m_pRootSceneNode->add(cache);
    else
        delete cache;
}

void CParticlePreloader::clean()
{
    m_particleNames.clear();
    if (m_resourceManager)
        CMasterResourceManager::getSingleton()->m_pParticleSystemManager->removeAllParticleSystemTemplates();
    for (std::map<std::wstring,TArrayList<std::string>*>::iterator it = m_particleScripts.begin(); it != m_particleScripts.end(); ++it) {
        if (it->second)
            delete it->second;
        it->second = 0;
    }
    m_particleScripts.clear();
    for (std::map<std::wstring,TArrayList<CParticleCache*>*>::iterator it = m_particleCaches.begin(); it != m_particleCaches.end(); ++it) {
        it->second->deleteAll();
        if (it->second)
            delete it->second;
        it->second = 0;
    }
    m_particleCaches.clear();
    if (m_layout) {
        delete m_layout;
        m_layout = 0;
    }
}
