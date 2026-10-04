#ifndef EXECUTESKILLPROPS_H
#define EXECUTESKILLPROPS_H

#include <string>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include "RunicCore.h"

class CBaseUnit;
class CDataGroup;
class CSkill;
class CSkillEvent;

// Skill property that executes another skill (the SKILL value of its data
// group) through the skill manager of the owning skill.
class CExecuteSkillProps : public CRunicCore
{
public:
    CExecuteSkillProps(CSkill* skill, CSkillEvent* skillEvent, CDataGroup* dataGroup);
    virtual ~CExecuteSkillProps();

    bool executeSkill(CBaseUnit* caster, const Ogre::Vector3& position, const Ogre::Quaternion& orientation,
                      const Ogre::Vector3& targetPosition, CBaseUnit* target, int level);
    std::wstring getSkillStats(CBaseUnit* unit, int level);
    std::wstring getSkillDescription(CBaseUnit* unit, int level);

private:
    CSkill* m_pSkill;
    CSkillEvent* m_pSkillEvent;
    std::wstring m_sSkillName;
};

#endif
