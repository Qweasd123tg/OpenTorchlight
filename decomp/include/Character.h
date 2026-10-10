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

namespace CEGUI { class Window; }
class CAIManager;
class CItem;
class CGenericModel;
class CCharacterSaveState;
class CPathController;
class CSkill;
class CInventory;
class CWardrobe;
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
friend class CPlayer;
friend class CGameClient;
public:
    void destroyCharacterText();
    EAlignment alignment();
    void displayDamageAbsorbed(float);
    void getBones();
    bool facingTarget(CCharacter*,CItem*);

    int naturalArmor();
    float HPFloat();
    float manaFloat();
    void giveUnusedPerkPoints(int amount);
    void giveUnusedStatPoints(int amount);
    void giveUnusedSkillPoints(int amount);
    void addFame(unsigned int amount);
    void setAllowJumpDown(bool allow);
    unsigned int getAnimationPlaying();
    float getAnimationSpeed();
    bool getAnimationLoop();
    void setModelPathDummy(std::wstring path);
    float followRange();
    float getBravery();
    CEquipment* getWeaponInRightHand();
    void queueBlendAnimation(const std::string& animation, bool loop, float blend, float speed);
    bool animationExists(const std::string& animation) const;
    bool animationQueued(const std::string& animation) const;
    bool animationPlaying(const std::string& animation) const;
    bool isImmobile();
    void forceDisplayOfDamageAbsorbed();
    void updateSkill(float elapsed);
    void destroyIcons();
    float getEffectValueWithoutInventory(EEFFECT_TYPE type, EDAMAGE_TYPES damage);
    void clearAllUnitReferences();
    bool facingTarget();
    void hideCharacterText();
    void showCharacterText();
    std::wstring getWardrobeChestMesh();
    void setWardrobeChestMesh(std::wstring value);
    std::wstring getWardrobeChestTexture();
    void setWardrobeChestTexture(std::wstring value);
    std::wstring getWardrobeGlovesMesh();
    void setWardrobeGlovesMesh(std::wstring value);
    std::wstring getWardrobeGlovesTexture();
    void setWardrobeGlovesTexture(std::wstring value);
    std::wstring getWardrobeBootsMesh();
    void setWardrobeBootsMesh(std::wstring value);
    std::wstring getWardrobeBootsTexture();
    void setWardrobeBootsTexture(std::wstring value);
    std::wstring getWardrobeHelmMesh();
    void setWardrobeHelmMesh(std::wstring value);
    std::wstring getWardrobeHelmTexture();
    void setWardrobeHelmTexture(std::wstring value);
    std::wstring getWardrobeShoulderMesh();
    void setWardrobeShoulderMesh(std::wstring value);
    std::wstring getModelPath();

    int getDefaultMerchantTab();
    void setActiveSkill(CSkill*,bool);
    void unLearnSpell(int);
    void setActiveSkillByName(std::wstring);
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

    void cycleSkill(int);
    bool hasWeaponsInOffSet();
    void swapSkills();
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
    char m_CharacterData210[0x21c-0x210];
    Ogre::Vector3 m_pathDestination;
    char m_CharacterData228[0x258-0x228];
    float m_moveSpeed;
    char m_CharacterData25C[0x264-0x25c];
    bool m_isPathing;
    char m_CharacterData265[1];
    bool m_moveInputHeld;
    char m_CharacterData267[0x278-0x267];
    float m_pathGraceTime;
    char m_CharacterData27C[0x2e8-0x27c];
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
    char m_CharacterData334[0x340-0x334];
    CCharacter* m_targetCharacter;
    char m_CharacterData348[8];
    CItem* m_targetItem;
    char m_CharacterData358[0x370-0x358];
    float m_followRange;
    char m_CharacterData374[0x414-0x374];
    float m_fHPFloat;
    int m_maxHPBase;
    char m_CharacterData41c[8];
    int m_naturalArmor;
    int m_rangedStat;
    int m_iMeleeStat;
    int m_defenseStat;
    int m_magicStat;
    float m_fManaFloat;
    int m_maxManaBase;
    char m_CharacterData440[4];
    int m_iGold;
    unsigned int m_experience;
    unsigned int m_fame;
    char m_CharacterData450[0x45c-0x450];
    int m_iUnusedStatPoints;
    int m_iUnusedSkillPoints;
    int m_iUnusedPerkPoints;
    char m_CharacterData468[0x478-0x468];
    CEGUI::Window* m_characterText;
    CEGUI::Window* m_characterTextParent;
    bool m_characterTextVisible;
    char m_CharacterData489[0x490-0x489];
    CInventory* m_pInventory;
    char m_CharacterData498[8];
    friend class CInventoryMenu;
    friend class CStatsMenu;
    friend class CPetMenu;
    friend class CEnchantMenu;
    friend class CCombineMenu;
    friend class CStashMenu;
    friend class CMerchantMenu;
    bool m_bCharacterFlag4A0;
    char m_CharacterData4A1[0x4e8-0x4a1];
    CWardrobe* m_wardrobe;
    char m_CharacterData4F0[0x52c-0x4f0];
    bool m_characterVisible;
    char m_CharacterData52D;
    bool m_bInvulnerable;
    friend class CEquipment;
    char m_CharacterData52F[0x560 - 0x52f];
    Ogre::Entity* m_PaperdollItems[12];
    Ogre::Entity* m_PaperdollItemsSecondary[12];
    char m_CharacterData620[0x640 - 0x620];
    CCharacter* m_pMaster;
    std::vector<CCharacter*> m_Followers;
    char m_CharacterData660[8];
    float m_bravery;
    char m_CharacterData66C[0x682-0x66c];
    bool m_allowJumpDown;
    char m_CharacterData683[0x70d-0x683];
    bool m_forcedHidden;
    bool m_bSecondaryWeaponSet;
    char m_CharacterData70f[0x718 - 0x70f];
    CAIManager* m_pAIManager;
};

#endif
