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

public:
    // Inline accessors behind the descriptors' property functions.
    void setStartOnLoad(bool value) { m_bStartOnLoad = value; }
    void setBlendTime(float value) { m_fBlendTime = value; }
    void setBlendOutTime(float value) { m_fBlendOutTime = value; }
    void setForceDuration(float value) { m_fForceDuration = value; }
    void setPlayIdle(bool value) { m_bPlayIdle = value; }
    bool getPlayIdle() const { return m_bPlayIdle; }
    float getForceDuration() const { return m_fForceDuration; }
    float getBlendOutTime() const { return m_fBlendOutTime; }
    float getBlendTime() const { return m_fBlendTime; }
    bool getStartOnLoad() const { return m_bStartOnLoad; }
};

#endif
