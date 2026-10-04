#ifndef ANIMATIONPLAYER_H
#define ANIMATIONPLAYER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include "EditorBaseObject.h"
#include "ResourceManager.h"

class CAnimationPlayer : public CEditorBaseObject
{
public:
    virtual ~CAnimationPlayer();
    void setAnimationDuration(float);
    CAnimationPlayer(CResourceManager*);
    void stopAnimation(bool);
    void playAnimation(bool);
    void playAnimation();
    void update(float);

    // fields
    CResourceManager* m_pResourceManager;
    std::wstring m_sAnimationName;
    unsigned char m_Unknown68[0x18] __attribute__((aligned(8)));
    long long m_Category;
    void* m_pUnitString;
    bool m_bStartOnLoad;
    bool m_bUnknown91;
    bool m_bUnknown92;
    bool m_bPlayIdle;
    bool m_bUnknown94;
    unsigned char m_gap95[0x3];
    float m_fUnknown98;
    float m_fBlendTime;
    float m_fBlendOutTime;
    float m_fForceDuration;
};

#endif
