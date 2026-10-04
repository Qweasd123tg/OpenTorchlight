#ifndef ANIMATIONPLAYER_H
#define ANIMATIONPLAYER_H

#include <string>

#include "EditorBaseObject.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "SafePointer.h"
#include "TArrayList.h"

class CAnimationPlayer : public CEditorBaseObject
{
public:
    virtual ~CAnimationPlayer();

    CAnimationPlayer(CResourceManager* pResourceManager);

    void setAnimationDuration(float duration);
    void stopAnimation(bool forceIdle);
    void playAnimation(bool loop);
    void playAnimation();
    void update(float deltaTime);

    CResourceManager* m_pResourceManager;
    std::wstring m_sAnimationName;
    TArrayList<TSafePointer<CRunicCore>*> m_lAnimationTargets;
    std::wstring m_sCategory;
    std::wstring m_sUnitType;
    bool m_bStartOnLoad;
    bool m_bAnimationPlaying;
    bool m_bLoop;
    bool m_bPlayIdle;
    bool m_bDurationActive;
    unsigned char m_gap95[3];
    float m_fRemainingDuration;
    float m_fBlendTime;
    float m_fBlendOutTime;
    float m_fForceDuration;
};

#endif
