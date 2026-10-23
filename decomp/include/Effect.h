#ifndef EFFECT_H
#define EFFECT_H
#include <string>
#include "RunicCore.h"
#include "SafePointer.h"
#include "EffectDisplayValues.h"
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
class CDataGroup;
class CEffectDisplayValues;
enum EEFFECT_STAT_MODIFIERS {};
enum EEFFECT_VALUES {};
std::wstring getRangeOfValues(float minimum, float maximum, bool percent);
// Partial: full 0x138 allocation, original destructor slots and accessed fields.
class CEffect : public CRunicCore
{
    friend class CTriggerUnit;
public:
    std::wstring getDisplayStats(unsigned int level, bool value);
    std::wstring getDisplayStats(CEffectDisplayValues& values);
    std::wstring getDamageTypeDisplayString(EDAMAGE_TYPES type);
    CEffectDisplayValues getVisualCalculatedValues(unsigned int level, bool value);
    void initValues();
    void clone(const CEffect* source);
    void setGraphs(std::wstring name);
    void setName(const std::wstring& name);
    void setFX(const std::wstring& name);
    float modifyEffectsByCharacter(CCharacter* character);
    CEffect(CDataGroup* data, CBaseUnit* owner);
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
    friend class CCharacterSaveState;
    friend class CItemSaveState;
    friend class CDamageShape;
    friend class CUnitSpawner;
    unsigned int m_iLevel;
    EDAMAGE_TYPES m_eDamageType;
    float m_fRemainingDuration; // +0x18
    EEFFECT_TYPE m_eType;
    EEFFECT_ACTIVATION m_activation; // +0x20
    float m_fValue24;
    bool m_bFlag28;
    unsigned char m_padding29[3];
    int m_value2C;
    unsigned char m_flag30;
    unsigned char m_flag31;
    union { unsigned char m_padding32; bool m_modifierFlag32; }; // +0x32
    bool m_flag33;
    bool m_bDead;
    bool m_showStats; // +0x35
    bool m_useOwnerLevel; // +0x36
    bool m_flag37;
    float m_value38;
    int m_value3C;
    int m_value40;
    int m_value44;
    TSafePointer<CBaseUnit> m_Owner;
    TSafePointer<CCharacter> m_sourceCharacter; // +0x58
    TSafePointer<CSkill> m_pSkillOwner; // +0x68
    std::wstring m_name78;
    std::wstring m_sName;
    std::wstring m_name88;
    std::wstring m_name90;
    Ogre::Vector3 m_direction; // +0x98
    unsigned char m_EffectDataA4[4];
    CParticle* m_particle;
    std::wstring m_particleName;
    CAffix* m_pAffixOwner; // +0xb8
    float m_fValueC0;
    union
    {
        float m_values[4]; // +0xc4, indexed by EEFFECT_VALUES
        struct
        {
            float m_fValueC4;
            float m_fValueC8;
            float m_reflectionMinimum; // +0xcc
            float m_reflectionMaximum; // +0xd0
        };
    };
    unsigned char m_paddingD4[4];
    CGraph* m_graphs[4]; // +0xd8
    TArrayList<EEFFECT_STAT_MODIFIERS> m_statModifiers; // +0xf8
    TArrayList<float> m_statModifierValues; // +0x110
    CResourceManager* m_resources; // +0x128
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
