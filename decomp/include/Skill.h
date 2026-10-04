#ifndef SKILL_H
#define SKILL_H

#include "RunicCore.h"
#include "SkillDefines.h"
#include "iUnitObserver.h"

class CDataGroup;
class CResourceManager;

// Partial: members used by recovered TUs; unnamed regions are padding until
// Skill.cpp is recovered.
class CSkill : public CRunicCore, public iUnitObserver
{
public:
    CSkill(CResourceManager* resourceManager, CDataGroup* dataGroup);
    virtual ~CSkill();
    void assignSkillAnimations(CBaseUnit* unit);

    virtual void unitStateChange(CBaseUnit* unit, EUNIT_STATES state);

    // Enabled skills can be used and count for skill points (on by default);
    // the AI toggles it while an AI skill cooldown runs.
    void setEnabled(bool enabled) { m_bEnabled = enabled; }

private:
    char m_SkillData[0x6d - 0x18];
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
    char m_SkillData120[4];
    int m_iCharges;
    std::wstring m_sAnimationOverride;
    std::wstring m_sAnimationOverrideDW;
    std::wstring m_sLoopAnimationOverride;
    std::wstring m_sLoopAnimationOverrideDW;
    char m_SkillData148[0x160 - 0x148];
    friend class CBaseUnit;
};

#endif
