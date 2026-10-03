#ifndef AISKILLMANAGER_H
#define AISKILLMANAGER_H

#include <string>

#include "RunicCore.h"
#include "AIDefines.h"
#include "TArrayList.h"

class CAIManager;
class CAISkill;
class CCharacter;

// Skill cooldowns of a character's AI. A skill on cooldown is matched by name;
// while it runs, the character's skill of that name is enabled.
class CAISkillManager : public CRunicCore
{
public:
    CAISkillManager(CAIManager* aiManager, CCharacter* character);
    virtual ~CAISkillManager();

    CAISkill* getSkill(std::wstring name);
    bool hasAISkill(CAISkill* skill);
    void addAISkill(CAISkill* skill, float time);
    void removeAISkill(CAISkill* skill);
    void updateAISkill(std::wstring name, float elapsed);
    void updateAISkills(float elapsed);

    void skillAdded(std::wstring name);
    void skillRemoved(std::wstring name);

private:
    TArrayList<CAISkill*> m_Skills;
    CCharacter* m_pCharacter;
    CAIManager* m_pAIManager;
};

#endif
