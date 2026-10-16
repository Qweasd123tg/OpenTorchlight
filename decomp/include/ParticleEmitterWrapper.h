#ifndef PARTICLEEMITTERWRAPPER_H
#define PARTICLEEMITTERWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include "ParticleTechWrapper.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "iSelected.h"

namespace ParticleUniverse { class ParticleEmitter; }

class CParticleEmitterWrapper : public CPositionableObject, public iSelected
{
public:
    virtual ~CParticleEmitterWrapper();
    virtual void setParentGuid(long long);
    virtual void setEnabled(bool);
    virtual bool getEnabled();
    virtual void positionUpdated(const Ogre::Vector3&);
    virtual void editorSelectionChanged(bool);
    bool getIsDoneEmitting();
    void starting();
    void setBoxDepth(float);
    void setBoxHeight(float);
    void setBoxWidth(float);
    void setPositionEnd(const Ogre::Vector3&);
    void setMaxLineDeviation(float);
    void setMaxLineIncrement(float);
    void setMinLineIncrement(float);
    void setParentTechniqueWrapper(CParticleTechWrapper*);
    void destroyEmitter();
    void setKeepLocal(bool);
    void setRadius(float);
    void setCircleFixedSize(bool);
    void setCircleStep(const float*, unsigned int);
    float* getCircleStep(unsigned int&);
    float* getCircleDegrees(unsigned int&);
    float* getMaxRadius(unsigned int&);
    float* getMinRadius(unsigned int&);
    void setCircleDegrees(const float*, unsigned int);
    void setMaxRadius(const float*, unsigned int);
    void setMinRadius(const float*, unsigned int);
    CParticleEmitterWrapper(CResourceManager*);
    void setEmitterType(int);

    // fields
    CParticleTechWrapper* m_pParticleTechWrapper;
    union {
        unsigned char m_ParticleDirection[0x18] __attribute__((aligned(8)));
        struct {
            ParticleUniverse::ParticleEmitter* m_pEmitter; // +0x110
            float m_fRadius; // +0x118
            float m_fMinLineIncrement; // +0x11c
            float m_fMaxLineIncrement; // +0x120
            float m_fMaxLineDeviation; // +0x124
        };
    };
    int m_iEmitterType;
    float m_fBoxWidth;
    float m_fBoxHeight;
    float m_fBoxDepth;
    bool m_bEnabled;
    bool m_bCircleFixedSize;
    unsigned char m_gap13A[0x2];
    Ogre::Vector3 m_PositionEnd;
    void* m_pUnknown148;
    void* m_pUnknown150;
    void* m_pUnknown158;
    void* m_pUnknown160;
};

#endif
