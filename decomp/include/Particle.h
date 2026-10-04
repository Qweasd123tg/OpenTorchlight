#ifndef PARTICLE_H
#define PARTICLE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreCamera.h>
#include <OgreVector3.h>
#include <string>
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "TArrayList.h"
#include "iLevelUpdate.h"
class CParticleCache;
class CParticlePreloader;

class CParticle : public CPositionableObject, public iLevelUpdate
{
public:
    virtual ~CParticle();
    virtual long long updateLevelObject(float, Ogre::Camera*, const Ogre::Vector3&);
    void SetParticleDirection(const Ogre::Vector3&, const Ogre::Vector3&);
    void forceParticleUpdate(float);
    // unresolved: CParticle::getAllEmitters(TArrayList<ParticleUniverse::ParticleEmitter*>&)
    void Resume();
    void Pause();
    int looping();
    void Stop(bool);
    void Start();
    int getNumberOfParticlesUpdating(bool);
    CParticle(CParticlePreloader*, const std::wstring&, CResourceManager*);

    // fields
    CParticleCache* m_pParticleCache;
    void* m_pUnknown110;
    int m_iUnknown118;
    int m_iUnknown11C;
    float m_fUnknown120;
    bool m_bUnknown124;
    bool m_bUnknown125;
    bool m_bUnknown126;
    bool m_bUnknown127;
    bool m_bUnknown128;
    unsigned char m_gap129[0x7];
    CParticlePreloader* m_pParticlePreloader;
};

#endif
