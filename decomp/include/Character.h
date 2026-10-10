#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "BaseUnit.h"
#include "SafePointer.h"
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
class CWardrobe;
class CParticle;
namespace Ogre { class Billboard; }
namespace CEGUI { class Window; }
class CPathController;
class CPath;
class CAstarPathfinder;
class CAttackDescription;
class CSoundBank;
class CWeaponTrail;

// Default range selection used by selectAttack in the original.
enum EATTACK_RANGE_TYPE { ATTACK_RANGE_DEFAULT = 0 };
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
    void completeDeath(CLevel& level);
    void doWeaponProcs(CEquipment* weapon, CBaseUnit* target);
    void playStrikeParticle(const Ogre::Vector3& source, const Ogre::Vector3& target, float radius, bool blocked, bool critical);

    bool diesOnWarp();
    bool getSpawnInvisible();
    bool getDestroyOnDeath();
    bool attachesToMaster();
    int getMaximumPetInstances();
    float playerLevelForMerchantInventory();
    std::wstring getDescription();
    std::wstring getMimicName();
    std::wstring getIntroCinematic();
    void sendToTown(CLevel& level);

    void setDestination(CLevel& level, float x, float z);
    void followCharacter(CCharacter* target, CLevel& level);
    float getDmgToReflectFromMissile();

    void updateCameraOpacity(Ogre::Camera* camera, float elapsed);

    bool canLearnSpell(std::wstring name, int level);
    float rangedRange();
    float meleeRange();
    float attackRange();
    bool canPathTo(Ogre::Vector3 destination);
    float sightRange();
    void updateAttack(CLevel& level);
    bool attemptStopOfActiveSkill();
    void performAttack(CEquipment* equipment, unsigned int attack, float damage, float effects, EDAMAGE_TYPES type);

    void updateOpacity(float elapsed, bool force);

    // Nested trigger layout comes from its 0x60-byte allocations and destructor.
    class CParticleAnimationTrigger : public CRunicCore
    {
    public:
        virtual ~CParticleAnimationTrigger();
        CResourceManager* m_resources; // +0x10
        CParticle* m_particle; // +0x18
        unsigned char m_Padding20[0x18];
        Ogre::SceneNode* m_node; // +0x38
        std::string m_name; // +0x40
        void* m_nodeOwner; // +0x48
        unsigned char m_Padding50[9];
        bool m_stopFlag59;
        bool m_stopFlag5A;
        unsigned char m_Padding5B[5];
    };

    void stopParticles(bool immediate);
    bool transferEffect(CCharacter* source, CBaseUnit* owner, CEffect* effect);
    void updateVisualEquippedItems(float elapsed);

    void setAltSkillByName(std::wstring name);

    EAIState getAIState() const { return m_eAIState; }

    void setVisible(bool visible, bool recursive);

    void blendAnimation(int animation, bool loop, float blend, float speed, float length);
    void blendAnimation(const std::string& animation, bool loop, float blend, float speed, float length);
    void setToward(const Ogre::Vector3& direction);
    bool characterShouldFadeOut();
    float viewAngle();
    void modifyMana(float amount);
    float walkingSpeed();
    float runningSpeed();
    void updateMana(float elapsed);
    void setAnimationPlaying(unsigned int animation);
    void setAnimationLoop(bool loop);
    void setAnimationSpeed(float speed);
    void turnTowardPosition(const Ogre::Vector3& position, float elapsed);
    void turnToward(const Ogre::Vector3& direction, float elapsed);
    void setTargetDirection(float x,float z);
    bool inDamageReactRange(CCharacter* character);
    bool inInteractionRange();
    void unLearnSpell(std::wstring name,int level);
    void performSkill(const std::wstring& name);
    void removePet(CCharacter* pet);
    float getEffectValue(EEFFECT_TYPE type,EEQUIP_LOCATIONS excluded,EDAMAGE_TYPES damage);

    void setMaster(CCharacter* master);

    void removePets();

    bool inStrikeRange();

    void notifyOfDeletion(CCharacter* character);

    void notifyOfDeletion(CItem* item);

    void destroyCharacterText();

    float getEffectValuesOfDamage();

    bool blocked();

    int damageDefensePercent(EDAMAGE_TYPES type);

    int armorBonus();
    int baseArmorBonus();
    void selectAttack(EATTACK_RANGE_TYPE type);
    bool inStrikeRange(CCharacter* target, CItem* item, CEquipment* equipment);

    bool isPetNearDeath();

    void animationPlayAI(float elapsed);

    bool isFriend(CCharacter* character);

    EAlignment getTargetAlignment();

    EAlignment alignment();

    int minimumSkillDamageForDisplay();

    int maximumSkillDamageForDisplay();

    bool isDualWielding();

    unsigned int getWeaponLevelCanEquip(bool base);

    unsigned int getArmorAndTrinketLevelCanEquip(bool base);

    bool skillAllowsTurning();

    bool performingSkill();

    bool performingAttack();

    void setMaximumTreeDepth(unsigned int depth);

    int characterDamage();

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
    bool facingTarget(CCharacter* target, CItem* item);
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
    void displayDamageAbsorbed(float elapsed);
    void getBones();

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
    CCharacter* getFollower(unsigned int index) { return m_Followers.size() == 0 ? NULL : m_Followers[index]; }
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
    friend class CPlayer;
    friend class CMonster;
    float m_pathTime; // +0x1e8
    unsigned char m_Padding1EC[0x14];
public:
    CGenericModel* m_pUnitModel;
    CGenericModel* m_pPaperdollModel;
private:
    unsigned char m_Padding210[0xc];
    Ogre::Vector3 m_pathDestination; // +0x21c
    Ogre::Vector3 m_targetPosition; // +0x228
    Ogre::Vector3 m_targetDirection; // +0x234
    unsigned char m_Padding240[0xc];
    Ogre::Vector3 m_movement; // +0x24c
    float m_moveSpeed; // +0x258
    unsigned char m_Padding25C[0x8];
    bool m_isPathing; // +0x264
    unsigned char m_Padding265;
    bool m_moveInputHeld;
    bool m_skillLooping; // +0x267
    CAstarPathfinder* m_pathfinder; // +0x268
    unsigned char m_Padding270[0x8];
    float m_pathGraceTime; // +0x278
    unsigned char m_Padding27C[0x10];
    float m_walkingSpeed; // +0x28c
    float m_runningSpeed; // +0x290
    unsigned char m_Padding294[4];
    CSoundBank* m_levelSound; // +0x298
    unsigned char m_Padding2A0[8];
    unsigned int m_aiAnimation; // +0x2a8
    unsigned char m_Padding2AC[0x3c];
public:
    Ogre::SceneNode* m_pRightHandNode;
private:
    Ogre::SceneNode* m_fishingNode;
public:
    Ogre::SceneNode* m_pLeftHandNode;
    Ogre::SceneNode* m_pShieldNode;
    Ogre::SceneNode* m_pLeftShoulderNode;
    Ogre::SceneNode* m_pRightShoulderNode;
    Ogre::SceneNode* m_pHeadNode;
private:
    unsigned char m_Padding320[0x1];
    bool m_returningToTown; // +0x321
    unsigned char m_Padding322[0xe];
    EAIState m_eAIState;
    unsigned char m_Padding334[0x4];
    EAlignment m_alignment; // +0x338
    unsigned char m_Padding33C[0x4];
    TSafePointer<CCharacter> m_targetCharacter; // +0x340
    TSafePointer<CItem> m_targetItem; // +0x350
    float m_sightRange; // +0x360
    unsigned char m_Padding364[4];
    float m_viewAngle; // +0x368
    unsigned char m_Padding36C[0x4];
    float m_followRange; // +0x370
    float m_damageReactRange;
    float m_attackTime; // +0x378
    bool m_attackEvent; // +0x37c
    bool m_skillInterrupted; // +0x37d
    unsigned char m_Padding37E[0x2];
    float m_skillTime; // +0x380
    unsigned char m_Padding384[0xc];
    CAttackDescription* m_attack; // +0x390
    CSkill* m_activeSkill; // +0x398
    CSkill* m_previousSkill; // +0x3a0
    unsigned char m_Padding3A8[0x8];
    long long m_activeSkillGuid; // +0x3b0
    long long m_leftSkillGuid; // +0x3b8
    long long m_leftMouseSkillGuid;
    std::wstring m_knownSpells[4]; // +0x3c8
    int m_knownSpellLevels[4]; // +0x3e8
    unsigned char m_Padding3F8[0x1c];
    float m_fHPFloat;
    int m_maxHPBase; // +0x418
    int m_maxHPBonus; // +0x41c
    unsigned char m_Padding420[0x4];
    int m_naturalArmor; // +0x424
    int m_rangedStat; // +0x428
    int m_iMeleeStat;
    int m_defenseStat; // +0x430
    int m_magicStat; // +0x434
    float m_fManaFloat;
    int m_maxManaBase; // +0x43c
    float m_maxManaBonus;
    int m_iGold;
    unsigned int m_experience; // +0x448
    unsigned int m_fame; // +0x44c
    unsigned char m_Padding450[0xc];
    int m_iUnusedStatPoints;
    int m_iUnusedSkillPoints;
    int m_iUnusedPerkPoints;
    unsigned char m_Padding468[0x10];
    CEGUI::Window* m_characterText; // +0x478
    CEGUI::Window* m_characterTextParent; // +0x480
    bool m_characterTextVisible; // +0x488
    unsigned char m_Padding489[0x7];
    CInventory* m_pInventory;
    CItem* m_attackItem; // +0x498
    friend class CInventoryMenu;
    friend class CStatsMenu;
    friend class CPetMenu;
    friend class CEnchantMenu;
    friend class CCombineMenu;
    friend class CStashMenu;
    friend class CMerchantMenu;
    bool m_bCharacterFlag4A0;
    unsigned char m_Padding4A1[7];
    TArrayList<CParticle*> m_equipmentParticles; // +0x4a8
    unsigned char m_Padding4C0[0x20];
    float m_attackRadius; // +0x4e0
    unsigned char m_Padding4E4[4];
    CWardrobe* m_wardrobe; // +0x4e8
    unsigned char m_Padding4F0[0x38];
    float m_currentOpacity; // +0x528
    bool m_characterVisible; // +0x52c
    unsigned char m_Padding52D[0x1];
    bool m_bInvulnerable;
    friend class CEquipment;
    unsigned char m_Padding52F[0x9];
    std::vector<bool> m_followerFlags; // +0x538
    Ogre::Entity* m_PaperdollItems[12];
    Ogre::Entity* m_PaperdollItemsSecondary[12];
    int m_damageDefense[8]; // +0x620
    CCharacter* m_pMaster;
    std::vector<CCharacter*> m_Followers;
    float m_masterFollowDelay; // +0x660
    unsigned char m_Padding664[4];
    float m_bravery; // +0x668
    unsigned char m_Padding66C[4];
    CPath* m_deathPath; // +0x670
    float m_deathPathDistance; // +0x678
    float m_deathPathSpeed; // +0x67c
    bool m_deathPathActive; // +0x680
    bool m_deathPathSilent; // +0x681
    bool m_allowJumpDown; // +0x682
    unsigned char m_Padding683;
    float m_townTravelTime; // +0x684
    unsigned char m_Padding688[0x10];
    CWeaponTrail* m_weaponTrails[4]; // +0x698
    unsigned char m_Padding6B8[0x4d];
    bool m_weaponsHidden; // +0x705
    unsigned char m_Padding706[0x7];
    bool m_forcedHidden; // +0x70d
    bool m_bSecondaryWeaponSet;
    char m_CharacterData70f;
    int m_petMode; // +0x710
    char m_CharacterData714[4];
    CAIManager* m_pAIManager;
    float m_CharacterValue720;
    unsigned char m_Padding724[4];
    Ogre::Billboard* m_automapBillboard;
    unsigned char m_Padding730[0x8];
    TArrayList<CParticleAnimationTrigger*> m_particleTriggers; // +0x738
    TSafePointer<CPathController> m_pathToFollow;
    std::wstring m_pathName;
    int m_savedPathIterations;
    unsigned char m_Padding76C[5];
    bool m_keepPathWhenAIChanges; // +0x771
    unsigned char m_Padding772[6];
};

#endif
