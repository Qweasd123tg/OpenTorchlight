#ifndef EFFECTDISPLAYVALUES_H
#define EFFECTDISPLAYVALUES_H
#include "RunicCore.h"
class CEffect;
class CEffectDisplayValues : public CRunicCore
{
public:
    virtual ~CEffectDisplayValues();
    CEffectDisplayValues()
        : CRunicCore(), m_duration(0), m_minimum(0), m_maximum(0),
          m_secondaryMinimum(0), m_secondaryMaximum(0), m_value24(0),
          m_scaled(false), m_effectType(0) {}
    CEffectDisplayValues(const CEffectDisplayValues& value)
        : CRunicCore(), m_duration(value.m_duration), m_minimum(value.m_minimum),
          m_maximum(value.m_maximum), m_secondaryMinimum(value.m_secondaryMinimum),
          m_secondaryMaximum(value.m_secondaryMaximum), m_value24(value.m_value24),
          m_scaled(value.m_scaled), m_effectType(value.m_effectType), m_effect(value.m_effect) {}
    CEffectDisplayValues& operator=(const CEffectDisplayValues& value)
    {
        m_duration=value.m_duration; m_minimum=value.m_minimum;
        m_maximum=value.m_maximum; m_secondaryMinimum=value.m_secondaryMinimum;
        m_secondaryMaximum=value.m_secondaryMaximum; m_value24=value.m_value24;
        m_scaled=value.m_scaled; m_effectType=value.m_effectType; m_effect=value.m_effect;
        return *this;
    }
    float m_duration; // +0x10
    float m_minimum; // +0x14
    float m_maximum; // +0x18
    float m_secondaryMinimum; // +0x1c
    float m_secondaryMaximum; // +0x20
    float m_value24;
    bool m_scaled; // +0x28
    int m_effectType; // +0x2c
    CEffect* m_effect; // +0x30
};
#endif
