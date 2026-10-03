#ifndef AISTATWATCHER_H
#define AISTATWATCHER_H

#include <string>

#include "RunicCore.h"
#include "AIDefines.h"
#include "Constants.h"
#include "TArrayList.h"
#include "UnitTypes.h"

class CAIManager;
class CAISkill;
class CCharacter;
class CDataGroup;

// One AI/STAT data group of a unit: watches a stat of the character and, while
// the condition holds (or, inverted, while it does not), puts AI flags on the
// targets and starts AI skill cooldowns.
class CAIStatWatcher : public CRunicCore
{
public:
    CAIStatWatcher(CDataGroup* dataGroup, CAIManager* aiManager);
    virtual ~CAIStatWatcher();

    void update(float elapsed);
    void getTargets(TArrayList<CCharacter*>& targets);
    void addFlag();
    void removeFlag();
    void addSkill();
    void removeSkill();

private:
    CAIManager* m_pAIManager;
    CCharacter* m_pCharacter;
    EAISTAT_TYPE m_eStat;
    EAISTAT_LOGIC m_eLogic;
    TArrayList<EAIFLAG_TYPES> m_Flags;
    TArrayList<CAISkill*> m_Skills;
    // Guids of the targets that got the flags.
    TArrayList<long long> m_FlaggedUnits;
    // Never filled in the shipped build.
    TArrayList<long long> m_SkilledUnits;
    EAISTAT_TARGET m_eTarget;
    UNITTYPES::EUNITTYPES m_eTargetUnitType;
    EAlignment m_eTargetAlignment;
    float m_fTargetArea;
    float m_fDuration;
    float m_fValue;
    bool m_bOnlyOnce;
    bool m_bTriggered;
    std::string m_sAnimation;
    bool m_bEnableOnEvent;
    bool m_bIncludeLiving;
    bool m_bIncludeDead;
};

#endif
