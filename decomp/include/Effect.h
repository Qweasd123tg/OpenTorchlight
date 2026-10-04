#ifndef EFFECT_H
#define EFFECT_H
#include <string>
#include "RunicCore.h"
#include "EffectDefines.h"
enum EEFFECT_VALUES {};
// Partial: full 0x138 allocation, original destructor slots and accessed fields.
class CEffect : public CRunicCore
{
public:
    enum ECALCULATETYPES {};
    CEffect(EEFFECT_TYPE,bool,EEFFECT_ACTIVATION,float,float,float,bool);
    virtual ~CEffect();
    float value(EEFFECT_VALUES value);
    void calculateBaseValue(ECALCULATETYPES type);
private:
    unsigned int m_iLevel;
    unsigned char m_EffectData14[8];
    EEFFECT_TYPE m_eType;
    unsigned char m_EffectData20[0x80-0x20];
    std::wstring m_sName;
    unsigned char m_EffectData88[0x138-0x88];
    friend class CBaseUnit;
};
#endif
