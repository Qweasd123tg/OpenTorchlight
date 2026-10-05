#ifndef EFFECT_H
#define EFFECT_H
#include <string>
#include "RunicCore.h"
#include "EffectDefines.h"
class CBaseUnit;
class CSkill;
enum EEFFECT_VALUES {};
// Partial: full 0x138 allocation, original destructor slots and accessed fields.
class CEffect : public CRunicCore
{
public:
    enum ECALCULATETYPES {};
    CEffect(EEFFECT_TYPE,bool,EEFFECT_ACTIVATION,float,float,float,bool);
    CEffect(const CEffect* source);
    virtual ~CEffect();
    void setOwner(CBaseUnit* owner,bool recalculate);
    void setSkillOwner(CSkill* owner);
    float value(EEFFECT_VALUES value);
    void calculateBaseValue(ECALCULATETYPES type);
private:
    unsigned int m_iLevel;
    unsigned char m_EffectData14[8];
    EEFFECT_TYPE m_eType;
    unsigned char m_EffectData20[0x80-0x20];
    std::wstring m_sName;
    unsigned char m_EffectData88[0xc0-0x88];
    float m_fValueC0;
    unsigned char m_EffectDataC4[0x138-0xc4];
    friend class CBaseUnit;
    friend class CEquipment;
};
#endif
