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
    char m_SkillData2[0x160 - 0x6e];
};

#endif
