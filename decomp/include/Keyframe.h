#ifndef KEYFRAME_H
#define KEYFRAME_H
#include "RunicCore.h"
// Partial: original 0x60-byte keyframe, only the animation-event code is named.
class CKeyframe : public CRunicCore
{
public:
    virtual ~CKeyframe();
    unsigned int getAnimationIndex() const { return m_animationIndex; }
    int getEventCode() const { return m_iEventCode; }
private:
    unsigned char m_KeyframeData10[0x28-0x10];
    unsigned int m_animationIndex; // +0x28
    unsigned char m_KeyframeData2C[0x58-0x2c];
    int m_iEventCode;
};
#endif
