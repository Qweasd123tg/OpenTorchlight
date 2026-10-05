#ifndef SKILLMANAGER_H
#define SKILLMANAGER_H
#include <map>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <string>
#include "RunicCore.h"
#include "SafePointer.h"
#include "SkillDefines.h"
class CSkill;
class CBaseUnit;
class CResourceManager;
// Partial, with the complete 0x98 layout and original destructor slots.
class CSkillManager : public CRunicCore
{
friend class CEquipment;
public:
    static void globallyDisableSkills(bool disabled);
    CSkillManager(CResourceManager* resources,CBaseUnit* owner);
    virtual ~CSkillManager();
    CSkill* addSkill(const std::wstring& name,bool flag);
    CSkill* addSkill(CSkill* skill,bool flag1,bool flag2);
    CSkill* getSkill(const std::wstring& name);
    void update(float elapsed);
    void setSkillLevel(CSkill* skill,unsigned int level);
    unsigned int getSkillLevel(CSkill* skill);
    int knownSkills(ESKILL_ACTIVATION_TYPE activation);
    void stopAllSkills(bool flag1,bool flag2,bool flag3);
    bool getSkillCanBeExecuted(CSkill* skill, CBaseUnit* caster, ESKILL_ACTIVATION_TYPE activation,
                               const Ogre::Vector3& targetPosition, CBaseUnit* target, bool flag);
    CSkill* executeSkill(CSkill* skill, CBaseUnit* caster, ESKILL_ACTIVATION_TYPE activation,
                         const Ogre::Vector3& position, const Ogre::Quaternion& orientation,
                         const Ogre::Vector3& targetPosition, CBaseUnit* target);
private:
    CResourceManager* m_pResourceManager;
    std::map<std::wstring,TArrayList<CSkill*>*> m_SkillsByName;
    TArrayList<CSkill*> m_UpdatingSkills;
    TArrayList<CSkill*> m_OtherSkills;
    unsigned char m_SkillData78[0x10];
    TSafePointer<CBaseUnit> m_Owner;
};
#endif
