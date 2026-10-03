#ifndef AIMANAGER_H
#define AIMANAGER_H

#include "RunicCore.h"
#include "AIDefines.h"
#include "TArrayList.h"

class CAIFlag;
class CAIFlagManager;
class CAISkill;
class CAISkillManager;
class CAIStatWatcher;
class CBaseUnit;
class CCharacter;
class CLevel;
class CResourceManager;

// AI state of one character: timed flags, skill cooldowns, stat watchers from
// the unit's AI data and the guids of the units in its formation.
class CAIManager : public CRunicCore
{
public:
    CAIManager(CCharacter* character);
    virtual ~CAIManager();

    // Creates the stat watchers from the unit's AI/STAT data groups.
    void initalize();
    void update(float elapsed);

    CResourceManager* getResourceManager();
    CLevel* getLevel();
    CCharacter* getCharacter() { return m_pCharacter; }

    void addFormationUnit(CBaseUnit* unit);
    TArrayList<long long>& getFormationUnits() { return m_FormationUnits; }

    CAIFlag* addAIFlag(EAIFLAG_TYPES type, float time);
    bool hasAIFlag(EAIFLAG_TYPES type);
    void removeAIFlag(EAIFLAG_TYPES type);

    void addAISkill(CAISkill* skill, float time);
    bool hasAISkill(CAISkill* skill);
    void removeAISkill(CAISkill* skill);

private:
    CCharacter* m_pCharacter;
    CAIFlagManager* m_pFlagManager;
    CAISkillManager* m_pSkillManager;
    TArrayList<CAIStatWatcher*> m_StatWatchers;
    TArrayList<long long> m_FormationUnits;
};

#endif
