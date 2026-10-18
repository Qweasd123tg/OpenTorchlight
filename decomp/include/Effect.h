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
class CAffix;
class CUnitTheme;
class CGraph;
enum EEFFECT_STAT_MODIFIERS {};
enum EEFFECT_VALUES {};
// Partial: full 0x138 allocation, original destructor slots and accessed fields.
class CEffect : public CRunicCore
{
public:
    std::wstring getDisplayStats(unsigned int level, bool value);
    float getMaxCaculatedValue();
    float getMinCaculatedValue();
    void playFX(CResourceManager* manager, const Ogre::Vector3& position);
    bool fxShouldPlay();
    enum ECALCULATETYPES {};
    CEffect(EEFFECT_TYPE,bool,EEFFECT_ACTIVATION,float,float,float,bool);
    CEffect(const CEffect* source);
    virtual ~CEffect();
    void setOwner(CBaseUnit* owner,bool recalculate);
    void setSkillOwner(CSkill* owner);
    void setAffixOwner(CAffix* owner);
    float value(EEFFECT_VALUES value);
    float calculateBaseValue(ECALCULATETYPES type);
private:
    friend class CEffectManager;
    unsigned int m_iLevel;
    EDAMAGE_TYPES m_eDamageType;
    float m_fRemainingDuration; // +0x18
    EEFFECT_TYPE m_eType;
    EEFFECT_ACTIVATION m_activation; // +0x20
    float m_fValue24;
    bool m_bFlag28;
    unsigned char m_EffectData29[0x31-0x29];
    unsigned char m_flag31;
    unsigned char m_padding32;
    bool m_flag33;
    bool m_bDead;
    unsigned char m_EffectData35[0x48-0x35];
    TSafePointer<CBaseUnit> m_Owner;
    CCharacter* m_sourceCharacter; // +0x58
    unsigned char m_EffectData60[8];
    CSkill* m_pSkillOwner; // +0x68, hasEffectFromSkill
    unsigned char m_EffectData70[0x80-0x70];
    std::wstring m_sName;
    std::wstring m_name88;
    unsigned char m_EffectData90[8];
    Ogre::Vector3 m_direction; // +0x98
    unsigned char m_EffectDataA4[4];
    CParticle* m_particle;
    std::wstring m_particleName;
    CAffix* m_pAffixOwner; // +0xb8
    float m_fValueC0;
    float m_fValueC4;
    float m_fValueC8;
    float m_reflectionMinimum; // +0xcc
    float m_reflectionMaximum; // +0xd0
    unsigned char m_paddingD4[4];
    CGraph* m_graphs[4]; // +0xd8
    TArrayList<EEFFECT_STAT_MODIFIERS> m_statModifiers; // +0xf8
    TArrayList<float> m_statModifierValues; // +0x110
    unsigned char m_EffectData128[8];
    CUnitTheme* m_pUnitTheme; // +0x130
    friend class CAffix;
    friend class CSkillEffectAndAffixes;
    friend class CBaseUnit;
    friend class CCharacter;
    friend class CPlayer;
    friend class CEquipment;
    friend class CInventory;
};
#endif
