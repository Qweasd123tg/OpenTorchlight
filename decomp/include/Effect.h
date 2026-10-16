#ifndef EFFECT_H
#define EFFECT_H
#include <string>
#include "RunicCore.h"
#include "SafePointer.h"
#include "EffectDefines.h"
#include "Constants.h"
class CBaseUnit;
class CCharacter;
class CResourceManager;
class CParticle;
#include <OgreVector3.h>
class CSkill;
enum EEFFECT_VALUES {};
// Partial: full 0x138 allocation, original destructor slots and accessed fields.
class CEffect : public CRunicCore
{
public:
    std::wstring getDisplayStats(unsigned int level, bool value);
    void getMaxCaculatedValue();
    void getMinCaculatedValue();
    void playFX(CResourceManager* manager, const Ogre::Vector3& position);
    bool fxShouldPlay();
    enum ECALCULATETYPES {};
    CEffect(EEFFECT_TYPE,bool,EEFFECT_ACTIVATION,float,float,float,bool);
    CEffect(const CEffect* source);
    virtual ~CEffect();
    void setOwner(CBaseUnit* owner,bool recalculate);
    void setSkillOwner(CSkill* owner);
    float value(EEFFECT_VALUES value);
    void calculateBaseValue(ECALCULATETYPES type);
private:
    friend class CEffectManager;
    unsigned int m_iLevel;
    EDAMAGE_TYPES m_eDamageType;
    unsigned char m_EffectData18[4];
    EEFFECT_TYPE m_eType;
    EEFFECT_ACTIVATION m_activation; // +0x20
    float m_fValue24;
    unsigned char m_EffectData28[0x33-0x28];
    bool m_flag33;
    unsigned char m_EffectData34[0x48-0x34];
    TSafePointer<CBaseUnit> m_Owner;
    CCharacter* m_sourceCharacter; // +0x58
    unsigned char m_EffectData60[8];
    CSkill* m_pSkillOwner; // +0x68, hasEffectFromSkill
    unsigned char m_EffectData70[0x80-0x70];
    std::wstring m_sName;
    unsigned char m_EffectData88[0xa8-0x88];
    CParticle* m_particle;
    std::wstring m_particleName;
    unsigned char m_EffectDataB8[8];
    float m_fValueC0;
    float m_fValueC4;
    float m_fValueC8;
    float m_reflectionMinimum; // +0xcc
    float m_reflectionMaximum; // +0xd0
    unsigned char m_EffectDataD4[0x138-0xd4];
    friend class CAffix;
    friend class CBaseUnit;
    friend class CCharacter;
    friend class CPlayer;
    friend class CEquipment;
    friend class CInventory;
};
#endif
