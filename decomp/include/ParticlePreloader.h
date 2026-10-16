#ifndef PARTICLEPRELOADER_H
#define PARTICLEPRELOADER_H
#include "RunicCore.h"
#include <string>
#include <map>
#include "TArrayList.h"
class CParticleCache;
class CResourceSettings;
class CResourceManager;
class CParticle;
class CLayout;
class CSoundBank;
class CDataGroup;
// Partial pointer interface: original CRunicCore base and observed size 0xc8.
class CParticlePreloader : public CRunicCore
{
public:
    CParticlePreloader(CResourceSettings*);
    static CParticlePreloader* getSingleton();
    void ReloadEditorParticles();
    void aggressiveUnloadParticles();
    void unloadParticlesOnLevelUnload();
    virtual ~CParticlePreloader();
    void LoadParticle(std::wstring path);
    void LoadParticle(std::wstring path, std::wstring name);
    void LoadParticle(CDataGroup*);
    unsigned int getParticleCacheCount();
    void getFileNames(std::wstring&);
    std::wstring getParticleNameByFileName(const std::wstring&);
    CParticle* GetParticle(CResourceManager*, const wchar_t*);
    CParticleCache* getParticleCache(const std::wstring&);
    void returnParticleCache(CParticleCache*);
    void clean();
    void ReloadParticles();
private:
    CResourceManager* m_resourceManager; // +0x10
    CResourceSettings* m_resourceSettings; // +0x18
    std::map<std::wstring,TArrayList<std::string>*> m_particleScripts; // +0x20
    std::map<std::wstring,TArrayList<CParticleCache*>*> m_particleCaches;
    std::map<std::wstring,std::wstring> m_particleNames; // +0x80
    unsigned char m_unknownB0[4]; // +0xb0; constructor clears this slot
    CSoundBank* m_soundBank; // +0xb8
    CLayout* m_layout; // +0xc0
};
#endif
