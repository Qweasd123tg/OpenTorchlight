#ifndef KEYFRAME_H
#define KEYFRAME_H
#include "RunicCore.h"
// Partial: original 0x60-byte keyframe, only the animation-event code is named.
class CKeyframe : public CRunicCore
{
public:
    virtual ~CKeyframe();
    int getEventCode() const { return m_iEventCode; }
private:
    unsigned char m_KeyframeData10[0x58-0x10];
    int m_iEventCode;
};
#endif
