#ifndef SKILLEFFECTANDAFFIXES_H
#define SKILLEFFECTANDAFFIXES_H

#include <string>
#include <OgreVector3.h>
#include "RunicCore.h"
#include "TArrayList.h"

class CSkill;
class CDataGroup;
class CBaseUnit;
class CCharacter;
class CResourceManager;
class CEffect;
class CAffix;

// SkillEffectAndAffixes.cpp: original CRunicCore base, size 0x98.
class CSkillEffectAndAffixes : public CRunicCore
{
public:
    class CSkillAffixData : public CRunicCore
    {
    public:
        virtual ~CSkillAffixData();
        std::wstring m_name; // +0x10
        int m_value18;
        unsigned int m_unitType; // +0x1c
        int m_targetType; // +0x20
        float m_durationOverride; // +0x24
    };

    class CSkillEffectData : public CRunicCore
    {
    public:
        virtual ~CSkillEffectData();
        bool m_flag10;
        unsigned char m_padding11[7];
        TArrayList<CEffect*> m_effects; // +0x18
        int m_value30;
        int m_value34;
    };

    virtual ~CSkillEffectAndAffixes();
    CSkillEffectAndAffixes(CSkill* skill, CDataGroup* data, CSkillEffectAndAffixes* source);
    void setDurationOverride(float duration);
    void createAffixesForDisplay(CResourceManager* resources);
    bool isDamaging();
    std::wstring getDisplayStats();
    bool removeAffixesAndEffects(CBaseUnit* unit, CCharacter* character);
    void appendName(const std::wstring& name);
    bool effectsTargetEnemy(CBaseUnit* unit);
    std::wstring getPortalSkillName();
    void fillOutStatBonuses(float (&values)[6], bool includeBaseValues);
    bool canAffixesAndEffectsBeAppliedToUnit(CBaseUnit* unit, CCharacter* character);
    void addMinAndMaxValuesOfAnEffect(CResourceManager* resources, unsigned int effect,
                                      float& minimum, float& maximum);
    bool applyAffixesAndEffects(CBaseUnit* unit, CCharacter* character,
                                const Ogre::Vector3* position, bool flag);

    CSkill* m_pSkill; // +0x10
    TArrayList<CSkillAffixData*> m_affixData; // +0x18
    TArrayList<CSkillEffectData*> m_effectData; // +0x30
    TArrayList<CAffix*> m_displayAffixes; // +0x48
    TArrayList<std::wstring> m_affixNames; // +0x60
    TArrayList<std::wstring> m_effectNames; // +0x78
    std::wstring m_name; // +0x90
};

#endif
