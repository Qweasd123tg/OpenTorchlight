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

class CParticleEmitterWrapper : public CPositionableObject, public iSelected
{
public:
    virtual ~CParticleEmitterWrapper();
    virtual void setParentGuid(long long);
    virtual void setEnabled(bool);
    virtual bool getEnabled();
    virtual void positionUpdated(const Ogre::Vector3&);
    virtual void editorSelectionChanged(bool);
    unsigned int getIsDoneEmitting();
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
    void getCircleStep(unsigned int&);
    void getCircleDegrees(unsigned int&);
    void getMaxRadius(unsigned int&);
    void getMinRadius(unsigned int&);
    void setCircleDegrees(const float*, unsigned int);
    void setMaxRadius(const float*, unsigned int);
    void setMinRadius(const float*, unsigned int);
    CParticleEmitterWrapper(CResourceManager*);
    void setEmitterType(int);

    // fields
    CParticleTechWrapper* m_pParticleTechWrapper;
    unsigned char m_ParticleDirection[0x18] __attribute__((aligned(8)));
    int m_iEmitterType;
    float m_fBoxWidth;
    float m_fBoxHeight;
    float m_fBoxDepth;
    bool m_bEnabled;
    bool m_bCircleFixedSize;
    unsigned char m_gap13A[0x2];
    long long m_iPositionEnd;
    int m_iPositionEnd_144;
    void* m_pUnknown148;
    void* m_pUnknown150;
    void* m_pUnknown158;
    void* m_pUnknown160;
};

#endif
