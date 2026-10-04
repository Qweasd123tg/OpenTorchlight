#ifndef PARTICLEWRAPPER_H
#define PARTICLEWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "DataGroup.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "iRandomWeight.h"
#include "iResource.h"
#include "iSelected.h"

class CParticleWrapper : public CPositionableObject, public iResource, public iRandomWeight, public iSelected
{
public:
    virtual ~CParticleWrapper();
    virtual void setVisible(bool);
    virtual void editorSelectionChanged(bool);
    virtual unsigned int GetRandomWeight();
    virtual void SetRandomWeight(unsigned int);
    virtual void resourceInit(CResourceManager*, CDataGroup*);
    virtual void resourceFreeing();
    virtual void free();
    virtual void stop();
    virtual void start();
    virtual char isPlaying();
    void hideVisualSphereMesh();
    void updateParticleSystem(float);
    void showVisualSphereMesh();
    void createParticleSystem();
    CParticleWrapper(CResourceManager*);

    // fields
    unsigned char m_pWorldScaleVelocity[0x8] __attribute__((aligned(8)));
    void* m_pUnknown120;
    long long m_iUnknown128;
    bool m_bUnknown130;
    unsigned char m_gap131[0x3];
    unsigned int m_iRandomWeight;
};

#endif
