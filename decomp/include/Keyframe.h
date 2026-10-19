#ifndef KEYFRAME_H
#define KEYFRAME_H
#include "RunicCore.h"
#include <string>
#include <OgreVector3.h>
class CUnitTheme;
class CCameraShake;
// Partial: original 0x60-byte keyframe, only the animation-event code is named.
class CDataGroup;
class CKeyframe : public CRunicCore
{
public:
    CKeyframe(int animation, CDataGroup* group);
    virtual ~CKeyframe();
    unsigned int getAnimationIndex() const { return m_animationIndex; }
    int getEventCode() const { return m_iEventCode; }
private:
    friend class CGenericModel;
    friend class CCharacter;
    float m_frame; // +0x10, animation frame at 30 frames per second
    unsigned char m_KeyframeData14[4];
    std::wstring m_text; // +0x18
    std::string m_name; // +0x20
    unsigned int m_animationIndex; // +0x28
    Ogre::Vector3 m_offset; // +0x2c
    std::wstring m_themeName; // +0x38
    CUnitTheme* m_theme; // +0x40
    int m_mode; // +0x48
    bool m_flag4C;
    unsigned char m_KeyframeData4D[3];
    CCameraShake* m_cameraShake; // +0x50, owning
    int m_iEventCode;
};
#endif
