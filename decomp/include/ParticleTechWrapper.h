#ifndef PARTICLETECHWRAPPER_H
#define PARTICLETECHWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreCamera.h>
#include <OgreVector3.h>
#include <string>
#include "ParticleWrapper.h"
#include "ResourceManager.h"
#include "iLevelUpdate.h"
class CAffectorWrapper;
class CParticleEmitterWrapper;

class CParticleTechWrapper : public CParticleWrapper, public iLevelUpdate
{
public:
    virtual ~CParticleTechWrapper();
    virtual void setParentGuid(long long);
    virtual void setEnabled(bool);
    virtual void stop();
    virtual void start();
    virtual bool isPlaying();
    virtual void setActivated(bool);
    virtual long long updateLevelObject(float, Ogre::Camera*, const Ogre::Vector3&);
    void setBillboardOrigin(unsigned int);
    void removeAffector(CAffectorWrapper*);
    void addAffector(CAffectorWrapper*);
    void removeEmitter(CParticleEmitterWrapper*);
    void addEmitter(CParticleEmitterWrapper*);
    void setFlipbookHeight(int);
    void setFlipbookWidth(int);
    void setRibbonLocalTrail(bool);
    void setRibbonEndFade(bool);
    void setRibbonMaxChains(unsigned int);
    void setRibbonLength(float);
    void setRibbonWidth(float);
    void setBillboardRotationType(unsigned int);
    void setRenderQueue(unsigned int);
    void setSortIndex(unsigned int);
    void setAsLight(bool);
    void setSorts(bool);
    void forceStop();
    void createTextureMaterial();
    void setDepthCheck(bool);
    void setParticleRenderStyle(unsigned int);
    void setTexturePath(const std::wstring&);
    void setVScroll(float);
    void setUScroll(float);
    void setRenderType(unsigned int, bool);
    void setModelPath(const std::wstring&);
    CParticleTechWrapper(CResourceManager*);
    void setDepthBias(float);

    // fields
    unsigned char m_AlwaysUp[0x18] __attribute__((aligned(8)));
    float m_fRibbonLength;
    float m_fRibbonWidth;
    int m_iRibbonMaxChains;
    bool m_bRibbonEndFade;
    bool m_bRibbonLocalTrail;
    unsigned char m_gap166[0x2];
    int m_iFlipbookWidth;
    int m_iFlipbookHeight;
    float m_fUScroll;
    float m_fVScroll;
    bool m_bSorts;
    unsigned char m_gap179[0x7];
    unsigned char m_pUnknown180[0x8] __attribute__((aligned(8)));
    long long m_iUnknown188;
    long long m_iUnknown190;
    long long m_iUnknown198;
    unsigned char m_pUnknown1A0[0x8] __attribute__((aligned(8)));
    void* m_pUnknown1A8;
    void* m_pTexturePath;
    void* m_pModelPath;
    void* m_pUnknown1C0;
    unsigned int m_iParticleRenderStyle;
    bool m_bDepthCheck;
    bool m_bIsLight;
    bool m_bUnknown1CE;
    unsigned char m_gap1CF[0x1];
    unsigned int m_iSortIndex;
    float m_fDepthBias;
    unsigned char m_Unknown1D8[0x18] __attribute__((aligned(8)));
    unsigned char m_Unknown1F0[0x18] __attribute__((aligned(8)));
    bool m_bUnknown208;
};

#endif
