#ifndef SKILL_H
#define SKILL_H

#include <string>
#include "RunicCore.h"
#include "SkillDefines.h"
#include "iUnitObserver.h"

class CDataGroup;
class CCharacter;
class CResourceManager;
class CSkillManager;

// Partial: members used by recovered TUs; unnamed regions are padding until
// Skill.cpp is recovered.
class CSkill : public CRunicCore, public iUnitObserver
{
public:
    void fillOutStatBonuses(float (&values)[6], bool, unsigned int);
    const std::wstring& getName();
    const std::wstring& getSkillUsageDescription();
    int getSkillLevelCooldown(CBaseUnit*, unsigned int);
    int getSkillLevelManaCost(CBaseUnit*, unsigned int);
    int getSkillLevelManaCostOT(CBaseUnit*, unsigned int);
    std::wstring getSkillLevelDescription(CBaseUnit*, unsigned int);
    std::wstring getSkillTypeDisplayName();
    const std::wstring& getSkillIcon();
    const std::wstring& getSkillIconInactive();
    const std::wstring& getSkillRequiredForInvestment();
    const std::wstring& getDisplayName();
    unsigned int getLevelRequiredForInvestment();
    void calculateEffectiveSkillLevel();
    CSkill(CResourceManager* resourceManager, CDataGroup* dataGroup);
    virtual ~CSkill();
    void assignSkillAnimations(CBaseUnit* unit);
    void _setLevelOfSkillFromSkillManager(unsigned int level);
    bool canAffixesAndEffectsBeAppliedToUnit(CBaseUnit*, CCharacter*);
    float getRange();
    float getFindTargetAngle();
    std::wstring getSkillLevelStats(CBaseUnit* unit, unsigned int level);
    std::wstring getDescription(CBaseUnit* unit, unsigned int level, bool flag);

    virtual void unitStateChange(CBaseUnit* unit, EUNIT_STATES state);

    // Enabled skills can be used and count for skill points (on by default);
    // the AI toggles it while an AI skill cooldown runs.
    void setEnabled(bool enabled) { m_bEnabled = enabled; }

private:
    char m_SkillData[0x20 - 0x18];
    CSkillManager* m_pSkillManager;
    char m_SkillData28[0x30 - 0x28];
    CBaseUnit* m_pOwner;
    char m_SkillData38[0x60 - 0x38];
    ESKILL_ACTIVATION_TYPE m_eActivationType; // 0x60
    char m_SkillData64[0x6b - 0x64];
    // Set on skills that CExecuteSkillProps adds to a skill manager.
    bool m_bExecutedByProperty;
    char m_SkillData6C;
    bool m_bEnabled;
    char m_SkillData2[0xa8 - 0x6e];
    unsigned int m_iSkillLevelCount; // 0xa8
    char m_SkillDataAC[0xd0 - 0xac];
    std::wstring m_sRequiredSkill;
    unsigned int m_iRequiredLevel;
    char m_SkillDataDC[4];
    unsigned int m_iEffectiveSkillLevel; // 0xe0
    char m_SkillDataE4[0x10c - 0xe4];
    int m_iColumn;
    int m_iRow;
    int m_iPane;
    int m_iChance;
    int m_iCancelChance;
    int m_iTargetAlignment; // EAlignment
    int m_iCharges;
    std::wstring m_sAnimationOverride;
    std::wstring m_sAnimationOverrideDW;
    std::wstring m_sLoopAnimationOverride;
    std::wstring m_sLoopAnimationOverrideDW;
    char m_SkillData148[8];
    long long m_Guid;
    unsigned int m_iDisplayedMaxRank; // 0x158, fallback to level count if zero
    char m_SkillData15C[4];
    friend class CInventoryMenu;
    friend class CPetMenu;
    friend class CSkillTooltip;
    friend class CBaseUnit;
    friend class CEquipment;
    friend class CExecuteSkillProps;
};

#endif
