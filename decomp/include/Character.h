#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "BaseUnit.h"
#include "GameEnums.h"
#include "EquipmentDefines.h"
#include "WardrobeDefines.h"
#include "iInventoryListener.h"
#include "iMissile.h"

class CAIManager;
class CItem;
class CGenericModel;
class CCharacterSaveState;
class CPathController;
class CSkill;
class CInventory;
enum EJournalStatistic { EJournalStatistic_GEN_LAST = 0x7fffffff };

// Partial: AI states of a character (character+0x330). Only the values used by
// recovered code are named; the names are ours.
enum EAIState
{
    // Leaves updateAI without an action; berserk resets the AI to it.
    AISTATE_IDLE = 2,
    // Dead or dying: alive() is false for it and for AISTATE_DEAD, and both
    // make updateHP and updateMotion leave the unit alone.
    AISTATE_DYING = 5,
    // The state that additionally drives the corpse fade-out in
    // characterShouldFadeOut.
    AISTATE_DEAD = 6
};

// Partial: members used by recovered TUs. The vtable is complete; return
// types of virtual methods that recovered code does not call are not verified
// yet. Unnamed regions are padding until character.cpp is recovered.
class CEquipment;
class CCharacter : public CBaseUnit, public iInventoryListener, public iMissile
{
public:
    void setActiveSkill(CSkill*,bool);
    void setLeftSkillByName(std::wstring);
    bool performingAttackLoose();
    void toggleSecondaryWeaponSet();
    CSkill* getKnownSpell(unsigned int);
    std::wstring getSkillTabName(int);
    CEquipment* getWeaponInLeftHand();
    CCharacter(CResourceManager* resourceManager);
    virtual ~CCharacter();

    virtual void setVisible(bool visible);
    virtual void scaleUpdated(const Ogre::Vector3& scale);
    virtual void setActiveInLevel(bool active);
    virtual void unitThemeUpdated(CUnitTheme* theme, bool updated);
    virtual void* getUnitModel();
    virtual void* getUnitCollisionModel();
    virtual void unitInit(CDataGroup* dataGroup, bool initialize);
    virtual void levelResetting();
    virtual void update(Ogre::Camera* camera, const Ogre::Vector3& cameraPosition, float elapsed);
    virtual void setHighlighted(bool highlighted);
    virtual bool isEffectValidForUnit(CCharacter* source, CBaseUnit* target, CEffect* effect);
    virtual bool applyEffectOnUnit(CCharacter* source, CBaseUnit* target, CEffect* effect);
    virtual float getEffectValue(EEFFECT_TYPE type, float value, const std::wstring& name);
    virtual void deactivateEffect(CEffect* effect);
    virtual void removeFromAvoidanceMap(CLevel& level);
    virtual void addToAvoidanceMap(CLevel& level);

    virtual bool getIsPlayer();
    virtual void levelLoaded(CLevel* level);
    virtual bool getIsInGodMode();
    virtual void fillSaveState(CCharacterSaveState& saveState);
    virtual void applySaveState(CCharacterSaveState& saveState);
    virtual void missileBeingFired(CMissile* missile);
    virtual void missileDieing(CMissile* missile);
    virtual bool missileApplyingEffects(CMissile* missile, CCharacter* target, const Ogre::Vector3* position,
                                        float damageScale, float effectScale);
    virtual bool getCharacterCanBeHarmedByMissile(CMissile* missile, CCharacter* target);
    virtual bool missileValidateTargetBeforeLaunch(CMissile* missile, CPositionableObject* target,
                                                   Ogre::Vector3& position);
    virtual void equipmentPickedUp(CEquipment* equipment);
    virtual void equipmentDropped(CEquipment* equipment);
    virtual void equipmentEquipped(CEquipment* equipment);
    virtual void equipmentUnequipped(CEquipment* equipment);
    virtual void equipmentUsed(CEquipment* equipment);
    virtual void inventoryDestroyed();
    virtual void updateAnimation(float elapsed);
    virtual void loadModel(std::wstring model, std::wstring skeleton);
    virtual void setPathToFollow(CPathController* path);
    virtual void setLevel(unsigned int level, bool apply);
    virtual void levelUp();
    virtual void fameUp();
    virtual void die(CCharacter* killer, const Ogre::Vector3* direction, float force, bool silent);
    virtual void startFishing();
    virtual void catchFish();
    virtual void setAIState(EAIState state);
    virtual void reactToDamage(CCharacter* attacker, bool critical);
    virtual void updateAI(float elapsed, bool force);
    virtual void dyingAI(float elapsed, CLevel& level);
    virtual void returnToTownAI(float elapsed, CLevel& level);
    virtual void handInteractiveSequence(float elapsed);
    virtual void spawningAI(float elapsed, CLevel& level);
    virtual void updateActiveSkill(float elapsed);
    virtual void performingSkillAI(float elapsed);
    virtual void interruptAI(float elapsed, CLevel& level);
    virtual void fishingAICast(float elapsed, CLevel& level);
    virtual void immobileAI(float elapsed);
    virtual void fishingAI(float elapsed, CLevel& level);
    virtual void fishingAICatch(float elapsed, CLevel& level);
    virtual void huntAI(float elapsed, CLevel& level);
    virtual void skillApproachAI(float elapsed, CLevel& level, long long skillGuid);
    virtual void getItemAI(float elapsed, CLevel& level);
    virtual void approachAI(float elapsed, CLevel& level);
    virtual void attackAI(float elapsed, CLevel& level);
    virtual void skillAI(float elapsed, CLevel& level);
    virtual void openPortal(CLevel& level);
    virtual void openMapPortal(std::wstring dungeon, CLevel& level);
    virtual bool canAttackWithCurrentWeapon();
    virtual void applyAchievementsForKilledCharacter(CCharacter* killed);
    virtual void notifyAISkillComplete();
    virtual void calculateMaxMana();
    virtual void calculateMaxHP();

    int petIndex(CCharacter* pet);
    bool hasPet(CCharacter* pet);

    bool castSkill(long long);
    void setTargetItem(CItem*);
    void setRenderBehind(bool);
    bool spendPerkPoint();
    bool spendSkillPoint();
    void spendMeleePoint();
    void spendRangedPoint();
    void spendMagicPoint();
    void spendDefensePoint();
    void reclaimMeleePoint();
    void reclaimRangedPoint();
    void reclaimMagicPoint();
    void reclaimDefensePoint();


    void incrementJournalStatistic(EJournalStatistic statistic,int amount);
    void performUnknownSkill(CSkill* skill);
    float getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES);
    bool isEnemy(CCharacter*);
    bool rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES);
    int minimumDamageForDisplay(bool,bool,bool);
    int maximumDamageForDisplay(bool,bool,bool);
    int getCriticalChance();
    int getBlockChance();
    int baseAC();
    int AC();
    int minimumAC();
    int damageDefense(EDAMAGE_TYPES);
    int strength();
    int dexterity();
    int magic();
    int defense();
    bool performingSkillLoose();
    void giveGold(int amount);
    void setPaperdollItem(EEQUIP_LOCATIONS,Ogre::Entity*);
    void setPaperdollItemSecondary(EEQUIP_LOCATIONS,Ogre::Entity*);
    int getGold() const { return m_iGold; }

    bool alive();
    void setInvulnerable(bool value) { m_bInvulnerable = value; }
    void stopPathing();
    void dropToGround(CLevel& level, float height, bool force);
    void teleportToMaster(float distance);
    unsigned int getFollowerCount() { return m_Followers.size(); }
    CCharacter* getFollower(unsigned int index) { return m_Followers.empty() ? NULL : m_Followers[index]; }
    void setMeshVisible(bool visible, bool recursive);
    void modifyHP(float change);
    int HP();
    int maxHP();
    int mana();
    int maxMana();
    void setAIPlayAnimation(const std::string& animation, bool loop, float blendTime, float speed);
    void interrupt(bool force);
    void setTarget(CCharacter* target);
    void setAlignment(EAlignment alignment);

    CAIManager* getAIManager() { return m_pAIManager; }

private:
    friend class CGameUI;
    char m_CharacterData[0x200-0x1e8];
public:
    CGenericModel* m_pUnitModel;
    CGenericModel* m_pPaperdollModel;
private:
    char m_CharacterData210[0x2e8-0x210];
public:
    Ogre::SceneNode* m_pRightHandNode;
private:
    char m_CharacterData2F0[0x8];
public:
    Ogre::SceneNode* m_pLeftHandNode;
    Ogre::SceneNode* m_pShieldNode;
    Ogre::SceneNode* m_pLeftShoulderNode;
    Ogre::SceneNode* m_pRightShoulderNode;
    Ogre::SceneNode* m_pHeadNode;
private:
    char m_CharacterData320[0x330 - 0x320];
    EAIState m_eAIState;
    char m_CharacterData334[0x414 - 0x334];
    float m_fHPFloat;
    char m_CharacterData418[0x42c - 0x418];
    int m_iMeleeStat;
    char m_CharacterData430[0x438 - 0x430];
    float m_fManaFloat;
    char m_CharacterData43c[0x444 - 0x43c];
    int m_iGold;
    char m_CharacterData448[0x45c - 0x448];
    int m_iUnusedStatPoints;
    int m_iUnusedSkillPoints;
    int m_iUnusedPerkPoints;
    char m_CharacterData468[0x490 - 0x468];
    CInventory* m_pInventory;
    char m_CharacterData498[8];
    friend class CInventoryMenu;
    friend class CStatsMenu;
    friend class CPetMenu;
    friend class CEnchantMenu;
    friend class CCombineMenu;
    bool m_bCharacterFlag4A0;
    char m_CharacterData4A1[0x52e - 0x4a1];
    bool m_bInvulnerable;
    friend class CEquipment;
    char m_CharacterData52F[0x560 - 0x52f];
    Ogre::Entity* m_PaperdollItems[12];
    Ogre::Entity* m_PaperdollItemsSecondary[12];
    char m_CharacterData620[0x640 - 0x620];
    CCharacter* m_pMaster;
    std::vector<CCharacter*> m_Followers;
    char m_CharacterData660[0x70e - 0x660];
    bool m_bSecondaryWeaponSet;
    char m_CharacterData70f[0x718 - 0x70f];
    CAIManager* m_pAIManager;
};

#endif
