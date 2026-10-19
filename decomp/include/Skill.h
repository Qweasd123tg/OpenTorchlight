#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include "SafePointer.h"
#include "RunicCore.h"
#include "SkillDefines.h"
#include "iUnitObserver.h"
#include "TArrayList.h"

extern bool m_gAllowSkillTesting;

class CDataGroup;
class CCharacter;
class CResourceManager;
class CSkillManager;
class CSkillProperty;
class CSkillEvent;

// Partial: members used by recovered TUs; unnamed regions are padding until
// Skill.cpp is recovered.
class CSkill : public CRunicCore, public iUnitObserver
{
    friend class CTriggerUnit;
    friend class CSkillEvent;
    friend class CLevel;
    friend class CEffect;
    friend class CBreakable;
public:
    bool weaponRequirementsMet(CCharacter* character);
    bool requirementsMet(CBaseUnit*, ESKILL_ACTIVATION_TYPE, const Ogre::Vector3*, CBaseUnit*, bool);
    bool getCanStop();
    void attemptToStopSkill();
    bool getIsExclusive();
    bool getCanBeInterrupted();
    unsigned int getManaCost();
    unsigned int getManaCostOT();
    bool getRequiresPathable();
    int getTargetType();
    int getUnitTypeToTarget();
    CCharacter* getMasterOwnerCharacter();
    bool getTargetIsValid(CCharacter*, CCharacter*, const Ogre::Vector3*, bool);
    bool getIsInRange(const Ogre::Vector3& from, const Ogre::Vector3& to,
                      CBaseUnit* caster, CBaseUnit* target);
    int getAnimationIndex();
    unsigned int getAnimationIndexDW();
    unsigned int getAnimationIndexLoopInto();
    int getAnimationIndexLoopEnd();
    unsigned int getAnimationIndexDWLoopInto();
    unsigned int getChanceToCast();
    float getAnimationSpeedMult();
    float getRangeMin();
    float getRandomRange();
    float getRandomRangeMin();
    float getMinimumTime();
    CBaseUnit* getMasterOwner();
    CCharacter* getOwnerCharacter();
    float getCoolDown();
    int getMaximumDamage();
    int getMinimumDamage();
    bool rollCancelChance();
    bool rollCastChance();
    bool rollSkillChance();

    bool stopsPathingOnCompletion() const { return m_stopsPathingOnCompletion; }
    void fillOutStatBonuses(float (&values)[6], bool, unsigned int);
    const std::wstring& getName();
    const std::wstring& getSkillUsageDescription();
    int getSkillLevelCooldown(CBaseUnit*, unsigned int);
    int getSkillLevelManaCost(CBaseUnit*, unsigned int);
    int getSkillLevelManaCostOT(CBaseUnit*, unsigned int);
    std::wstring getSkillLevelDescription(CBaseUnit*, unsigned int);
    std::wstring getSkillTypeDisplayName();
    const std::wstring& getSkillIcon();
    const std::wstring& getSkillIconInactive();
    const std::wstring& getSkillRequiredForInvestment();
    const std::wstring& getDisplayName();
    unsigned int getLevelRequiredForInvestment();
    bool calculateEffectiveSkillLevel();
    bool hasEvent(ESKILL_EVENT_TYPE event);
    bool triggerEvent(ESKILL_EVENT_TYPE event, const Ogre::Vector3& position,
                      const Ogre::Quaternion& orientation, CBaseUnit* target,
                      const Ogre::Vector3* targetPosition);
    void updateSkill(float elapsed);
    void stopSkill();
    bool startSkill(CBaseUnit* caster, ESKILL_ACTIVATION_TYPE activation,
                    const Ogre::Vector3& position, const Ogre::Quaternion& orientation,
                    const Ogre::Vector3& targetPosition, CBaseUnit* target);
    CSkill(CResourceManager* resourceManager, CDataGroup* dataGroup);
    virtual ~CSkill();
    void assignSkillAnimations(CBaseUnit* unit);
    void _setLevelOfSkillFromSkillManager(unsigned int level);
    bool canAffixesAndEffectsBeAppliedToUnit(CBaseUnit*, CCharacter*);
    float getRange();
    float getFindTargetAngle();
    std::wstring getSkillLevelStats(CBaseUnit* unit, unsigned int level);
    std::wstring getDescription(CBaseUnit* unit, unsigned int level, bool flag);
    std::wstring getDescriptionRequirments(CBaseUnit* unit);

    virtual void unitStateChange(CBaseUnit* unit, EUNIT_STATES state);

    // Enabled skills can be used and count for skill points (on by default);
    // the AI toggles it while an AI skill cooldown runs.
    void setEnabled(bool enabled) { m_bEnabled = enabled; }

private:
    long long getGuid() const { return m_Guid; }
    unsigned int getLevel() const { return m_skillLevel; }
    ESKILL_ACTIVATION_TYPE getActivationType() const { return m_eActivationType; }
    bool enabledWithoutProperty() const { return m_bEnabled & !m_bExecutedByProperty; }

    friend class CSkillManager;
    friend class CSkillController;
    friend class CSkillEffectAndAffixes;
    friend class CAffix;
    friend class CSkillProperty;
    friend class CCharacter;
    friend class CPlayer;
    friend class CMonster;
    CResourceManager* m_resources;
    CSkillManager* m_pSkillManager;
    CDataGroup* m_pDataGroup; // +0x28
    CBaseUnit* m_pOwner;
    unsigned int m_iOwnerSafePointerId; // +0x38
    unsigned char m_Padding3C[4];
    TSafePointer<CBaseUnit> m_Target; // +0x40
    Ogre::Vector3 m_targetPosition; // +0x50
    int m_skillType; // +0x5c, indexes gSKILL_TYPE_NAMES
    ESKILL_ACTIVATION_TYPE m_eActivationType; // 0x60
    bool m_interruptible; // +0x64
    bool m_pendingStop; // +0x65
    bool m_allowsTurning; // +0x66
    unsigned char m_suppressNormalStop; // +0x67, checked alongside the death event
    bool m_stopsPathingOnCompletion; // +0x68
    bool m_requiresLineOfSight;
    bool m_requiresPathable;
    // Set on skills that CExecuteSkillProps adds to a skill manager.
    bool m_bExecutedByProperty;
    char m_SkillData6C;
    bool m_bEnabled;
    bool m_targetsDead; // +0x6e
    char m_SkillData6F;
    bool m_checksSilence; // +0x70
    char m_SkillData71[7];
    TArrayList<CDataGroup*> m_allowedTargetData; // +0x78
    CSkillProperty* m_property;
    CSkillProperty* m_baseProperty; // +0x98
    CSkillProperty** m_levelPropertyData;
    unsigned int m_iSkillLevelCount; // 0xa8
    unsigned int m_levelPropertyCapacity;
    unsigned int m_levelPropertyGrow;
    char m_SkillDataB4[4];
    TArrayList<CSkillEvent*> m_activeEvents; // +0xb8, owns the pointer array
    std::wstring m_sRequiredSkill;
    unsigned int m_iRequiredLevel;
    unsigned int m_skillLevel; // +0xdc
    unsigned int m_iEffectiveSkillLevel; // 0xe0
    unsigned int m_animationIndex;
    unsigned int m_animationIndexDW;
    union { unsigned int m_animationIndexLoopInto; int m_animationID; };
    unsigned int m_animationIndexDWLoopInto;
    unsigned int m_animationIndexLoopEnd;
    float m_animationSpeed; // +0xf8
    float m_coolingTime; // +0xfc
    float m_animationLength; // +0x100
    float m_animationTimeRemaining; // +0x104
    float m_elapsedSkillTime;
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
    std::wstring m_sAnimationOverrideLoopEnd; // +0x148
    long long m_Guid;
    unsigned int m_iDisplayedMaxRank; // 0x158, fallback to level count if zero
    char m_SkillData15C[4];
    friend class CInventoryMenu;
    friend class CPetMenu;
    friend class CSkillTooltip;
    friend class CBaseUnit;
    friend class CEquipment;
    friend class CExecuteSkillProps;
};

#endif
