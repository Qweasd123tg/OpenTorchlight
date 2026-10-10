#ifndef SKILL_H
#define SKILL_H

#include <string>
#include "RunicCore.h"
#include "SkillDefines.h"
#include "iUnitObserver.h"

class CDataGroup;
class CCharacter;
class CResourceManager;
class CSkillManager;
class CSkillProperty;

// Partial: members used by recovered TUs; unnamed regions are padding until
// Skill.cpp is recovered.
class CSkill : public CRunicCore, public iUnitObserver
{
public:
    bool getCanStop();
    bool getIsExclusive();
    bool getCanBeInterrupted();
    unsigned int getManaCost();
    unsigned int getManaCostOT();
    bool getRequiresPathable();
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
    void calculateEffectiveSkillLevel();
    CSkill(CResourceManager* resourceManager, CDataGroup* dataGroup);
    virtual ~CSkill();
    void assignSkillAnimations(CBaseUnit* unit);
    void _setLevelOfSkillFromSkillManager(unsigned int level);
    bool canAffixesAndEffectsBeAppliedToUnit(CBaseUnit*, CCharacter*);
    float getRange();
    float getFindTargetAngle();
    std::wstring getSkillLevelStats(CBaseUnit* unit, unsigned int level);
    std::wstring getDescription(CBaseUnit* unit, unsigned int level, bool flag);

    virtual void unitStateChange(CBaseUnit* unit, EUNIT_STATES state);

    // Enabled skills can be used and count for skill points (on by default);
    // the AI toggles it while an AI skill cooldown runs.
    void setEnabled(bool enabled) { m_bEnabled = enabled; }

private:
    friend class CCharacter;
    CResourceManager* m_resources;
    CSkillManager* m_pSkillManager;
    char m_SkillData28[0x30 - 0x28];
    CBaseUnit* m_pOwner;
    char m_SkillData38[0x60 - 0x38];
    ESKILL_ACTIVATION_TYPE m_eActivationType; // 0x60
    bool m_interruptible; // +0x64
    unsigned char m_Padding65[0x1];
    bool m_allowsTurning; // +0x66
    unsigned char m_Padding67;
    bool m_stopsPathingOnCompletion; // +0x68
    unsigned char m_Padding69;
    bool m_requiresPathable;
    // Set on skills that CExecuteSkillProps adds to a skill manager.
    bool m_bExecutedByProperty;
    char m_SkillData6C;
    bool m_bEnabled;
    char m_SkillData6E[0x90-0x6e];
    CSkillProperty* m_property;
    char m_SkillData98[8];
    CSkillProperty** m_levelPropertyData;
    unsigned int m_iSkillLevelCount; // 0xa8
    unsigned int m_levelPropertyCapacity;
    unsigned int m_levelPropertyGrow;
    char m_SkillDataB4[0xd0-0xb4];
    std::wstring m_sRequiredSkill;
    unsigned int m_iRequiredLevel;
    char m_SkillDataDC[4];
    unsigned int m_iEffectiveSkillLevel; // 0xe0
    unsigned int m_animationIndex;
    unsigned int m_animationIndexDW;
    union { unsigned int m_animationIndexLoopInto; int m_animationID; };
    unsigned int m_animationIndexDWLoopInto;
    unsigned int m_animationIndexLoopEnd;
    char m_SkillDataF8[0x108-0xf8];
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
    char m_SkillData148[8];
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
