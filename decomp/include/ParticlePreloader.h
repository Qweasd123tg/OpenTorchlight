#ifndef PARTICLEPRELOADER_H
#define PARTICLEPRELOADER_H
#include "RunicCore.h"
#include <string>
#include <map>
#include "TArrayList.h"
class CParticleCache;
class CResourceSettings;
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
private:
    unsigned char m_Unrecovered10[0x50-0x10];
    std::map<std::wstring,TArrayList<CParticleCache*>*> m_particleCaches;
    unsigned char m_gap80[0xc8-0x80];
};
#endif
