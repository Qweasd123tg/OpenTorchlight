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
    char m_SkillData38[0x6b - 0x38];
    // Set on skills that CExecuteSkillProps adds to a skill manager.
    bool m_bExecutedByProperty;
    char m_SkillData6C;
    bool m_bEnabled;
    char m_SkillData2[0xd0 - 0x6e];
    std::wstring m_sRequiredSkill;
    unsigned int m_iRequiredLevel;
    char m_SkillDataDC[0x10c - 0xdc];
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
    char m_SkillData148[0x160 - 0x148];
    friend class CBaseUnit;
    friend class CEquipment;
    friend class CExecuteSkillProps;
};

#endif
