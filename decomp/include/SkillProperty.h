#ifndef SKILLPROPERTY_H
#define SKILLPROPERTY_H

#include <string>

#include "RunicCore.h"
#include "TArrayList.h"

class CBaseUnit;
class CCharacter;
class CDataGroup;
class CResourceManager;
class CSkill;
class CSkillEffectAndAffixes;
class CSkillEvent;
class CUnitTheme;

namespace Ogre
{
class Vector3;
}

class CSkillProperty : public CRunicCore
{
public:
    virtual ~CSkillProperty();

    CBaseUnit* getOwner();
    CCharacter* getOwnerCharacter();

    void fillOutStatBonuses(float (&statBonuses)[6], bool includeBaseValues);
    bool canAffixesAndEffectsBeAppliedToUnit(CBaseUnit* unit,
                                             CCharacter* character);
    void addMinAndMaxValuesOfAnEffect(CResourceManager* resourceManager,
                                      unsigned int effectId,
                                      float& minimumValue,
                                      float& maximumValue);

    std::wstring getSkillDescription();
    bool applyAffixesAndEffectsToUnit(CCharacter* character,
                                      const Ogre::Vector3* position);
    float getCoolDown();
    CSkillEvent* cloneEventForSkill(CSkillEvent* event);
    std::wstring getSkillStats();

    CSkillProperty(CSkill* skill,
                   CResourceManager* resourceManager,
                   CSkillProperty* parentProperty,
                   CDataGroup* dataGroup,
                   unsigned int skillId);

    int m_iRequirementRight;
    int m_iRequirementLeft;
    bool m_bDuelWeaponRequired;

    CSkillEffectAndAffixes* m_pSkillEffectAndAffixes;
    CResourceManager* m_pResourceManager;
    CSkillProperty* m_pSkillProperty;
    CSkill* m_pSkill;
    unsigned int m_uiSkillId;
    int m_iLevelRequired;
    CDataGroup* m_pDataGroup;
    int m_iSkillLevel;

    TArrayList<TArrayList<CSkillEvent *> *> m_eventLists;

    int m_eTargetType;
    int m_eTargetUnitType;
    int m_iManaCost;
    int m_iManaCostOverTime;

    float m_fRange;
    int m_iMinimumRange;
    float m_fRandomRange;
    int m_iRandomRangeMinimum;
    float m_fFindTargetAngle;
    float m_fSpeed;
    float m_fCoolDown;
    float m_fMonsterCoolDown;
    float m_fMinimumTime;
    float m_fDurationOverride;
    float m_fSlowDown;
    int m_iChance;

    bool m_bHasAnimation;
    bool m_bInterruptable;
    bool m_bContinuousLooping;
    bool m_bExclusive;
    bool m_bSingleTarget;
    bool m_bUseWeaponAnimation;

    CUnitTheme* m_pRequiredTheme;
    CUnitTheme* m_pForbiddenTheme;

    std::wstring m_sSkillIcon;
    std::wstring m_sSkillIconInactive;
    std::wstring m_sName;
    std::wstring m_sDisplayName;
    std::wstring m_sUsageDescription;
    std::wstring m_sDescription;

    std::string m_sAnimation;
    std::string m_sAnimationDualWield;
    std::string m_sAnimationLoop;
    std::string m_sAnimationLoopEnd;
    std::string m_sAnimationDualWieldLoop;
};

#endif
