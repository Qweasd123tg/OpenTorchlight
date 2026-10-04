#ifndef SKILL_H
#define SKILL_H

#include <string>
#include "RunicCore.h"
#include "SkillDefines.h"
#include "iUnitObserver.h"

class CDataGroup;
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
    char m_SkillData2[0x10c - 0x6e];
    int m_iSkillField10C;
    char m_SkillData110[0x120 - 0x110];
    int m_iTargetAlignment; // EAlignment
    int m_iSkillField124;
    char m_SkillData128[0x160 - 0x128];
    friend class CBaseUnit;
    friend class CExecuteSkillProps;
};

#endif
