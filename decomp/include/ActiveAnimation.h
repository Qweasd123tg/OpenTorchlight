#ifndef ACTIVEANIMATION_H
#define ACTIVEANIMATION_H
#include "RunicCore.h"

class CActiveAnimation : public CRunicCore
{
public:
    virtual ~CActiveAnimation();
    unsigned int m_animation; // +0x10
    unsigned char m_gap14[4];
    float m_length; // +0x18
    float m_duration; // +0x1c
    float m_time; // +0x20
    bool m_loop; // +0x24
    bool m_playing; // +0x25
    bool m_queued; // +0x26
    bool m_flag27;
    bool m_flag28;
    bool m_flag29;
    bool m_flag2a;
    unsigned char m_gap2b;
    float m_blendRemaining; // +0x2c
    float m_blendDuration; // +0x30
    float m_weight; // +0x34
    float m_speed; // +0x38
    unsigned char m_gap3c[4];
};
#endif
