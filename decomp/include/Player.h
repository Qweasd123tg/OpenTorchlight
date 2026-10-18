#ifndef PLAYER_H
#define PLAYER_H

#include <OgreCamera.h>
#include <vector>
class CLevelState;
#include "Character.h"
class CLevelState;
class CDungeonTracker;
class CParticle;
class CQuestManager;
class CPath;
class CDynamicLine;

// Partial: Player.cpp is not recovered. Virtual overrides follow the original
// vtable; the unexamined player fields retain their original extent.
class CPlayer : public CCharacter
{
    friend class CSpawnClassData;
friend class CGameClient;
public:
    void storeLevelSavedState(CLevel& level);
    bool removeItemFromInventoryOrPetsInventoryByGuid(long long guid, bool wholeStack, bool destroy, UNITTYPES::EUNITTYPES type);
    bool removeQuestItemFromInventoryOrPetsInventoryByGuid(long long quest, long long guid, bool wholeStack, bool destroy, UNITTYPES::EUNITTYPES type);
    void setQuestManager(CQuestManager* manager);
    void updateFishingLine(float elapsed);
    void firstTimeSetup();
    void resetStatPoints();
    void resetSkills();
    void calculateNaturalArmor();
    void createPortals(CLevel& level);

    CQuestManager* getQuestManager() { return m_questManager; }

    int getDungeonRank(std::wstring dungeon);
    int getMaxDepth(std::wstring dungeon);
    CLevelState* getLevelSavedState(std::wstring dungeon,int level);
    bool hasLevelSavedState(std::wstring dungeon,int level);
    bool hasDungeonHistory(std::wstring dungeon);

    void clearSkillMap();
    void clearSkillFunctionMap();
    void clearItemLinkMap();
    void resetLevel();
    void removeLevelSavedState(unsigned int index);
    void clearLevelHistory();
    void setJournalStatistic(EJournalStatistic statistic, int amount);
    int getSkillPointsAwardedForFameLevel(unsigned int level);
    int getSkillPointsAwardedForLevel(unsigned int level);
    int getStatsPointsAwardedForLevel(unsigned int level);

    std::wstring getPlayerClassName();
    void setLeftMappedFunctionSkill(unsigned int,long long);
    void setMappedFunctionSkill(unsigned int,long long);
    bool addWaypoint(std::wstring dungeon, int depth);
    void soldItem(CEquipment*);
    void incrementJournalStatistic(EJournalStatistic,int);
    void attemptToStopPlayerSkill(bool force);
    CPlayer(CResourceManager* resources);
    virtual ~CPlayer();
    virtual void unitInit(CDataGroup*, bool);
    virtual void levelResetting();
    virtual void update(Ogre::Camera*, const Ogre::Vector3&, float);
    virtual bool getIsPlayer();
    virtual void levelLoaded(CLevel*);
    virtual bool getIsInGodMode();
    virtual void fillSaveState(CCharacterSaveState&);
    virtual void applySaveState(CCharacterSaveState&);
    virtual void updateAnimation(float);
    virtual void loadModel(std::wstring, std::wstring);
    virtual void levelUp();
    virtual void die(CCharacter*, const Ogre::Vector3*, float, bool);
    virtual void startFishing();
    virtual void catchFish();
    virtual void setAIState(EAIState);
    virtual void fishingAI(float, CLevel&);
    virtual void fishingAICatch(float, CLevel&);
    virtual void openPortal(CLevel&);
    virtual void openMapPortal(std::wstring, CLevel&);
    virtual void applyAchievementsForKilledCharacter(CCharacter*);
    virtual void calculateMaxMana();
    virtual void calculateMaxHP();

    void clearDungeonHistory(std::wstring dungeon);
    void updateStoredLevels(CLevel& level);
    void updateDungeonTracking(std::wstring name, int depth);

private:
    friend class CSteamStats;
    CParticle* m_levelUpParticle; // +0x778
    long long m_itemLinks[2]; // +0x780
    bool m_godMode; // +0x790
    unsigned char m_cheatMarker;
    unsigned char m_Padding792[6];
    std::vector<CLevelState*> m_savedLevels; // +0x798
    bool m_hasPortal; // +0x7b0
    unsigned char m_Padding7B1[3];
    int m_portalDepth; // +0x7b4
    std::wstring m_portalDungeon; // +0x7b8
    Ogre::Vector3 m_portalPosition; // +0x7c0
    int m_returnDepth; // +0x7cc
    std::wstring m_returnDungeon; // +0x7d0
    int m_levelSaveSerial; // +0x7d8
    union {
        int m_journalStats[43];
        // This overlay begins at +0x7dc; packing preserves the original
        // absolute alignment of pointer fields at +0x830 and +0x868.
        struct __attribute__((packed)) {
    int m_journalPrefix[18]; // +0x7dc
    unsigned char m_Padding824[4];
    CGenericModel* m_fishingPole; // +0x828
    CGenericModel* m_fishingParticle; // +0x830, the animated fish model
    CPath* m_fishingPath; // +0x838
    CDynamicLine* m_fishingLine; // +0x840
    Ogre::SceneNode* m_fishingLineNode; // +0x848
    float m_fishingTime; // +0x850
    float m_fishingValue854; // +0x854
    float m_fishingDelay; // +0x858
    bool m_fishingFlag; // +0x85c
    unsigned char m_Padding85D[0x3];
    float m_fishingValue860; // +0x860
    unsigned char m_Padding864[0x4];
    CQuestManager* m_questManager; // +0x868
    unsigned char m_Padding870[0x14];
    float m_deathDelay; // +0x884
        };
    };
    std::wstring m_manaGraph; // +0x888
    std::wstring m_hpGraph; // +0x890
    std::wstring m_statPointsGraph; // +0x898
    std::wstring m_skillPointsGraph; // +0x8a0
    std::wstring m_famePointsGraph; // +0x8a8
    long long m_skillMap[10]; // +0x8b0
    long long m_leftSkillMap[10]; // +0x900
    long long m_functionSkills[12]; // +0x950
    long long m_leftFunctionSkills[12]; // +0x9b0
    unsigned char m_PaddingA10[4];
    bool m_playerTranslucent; // +0xa14
    bool m_saveOnDeath; // +0xa15
    bool m_followersEnabled; // +0xa16
    unsigned char m_PaddingA17[0x29];
    TArrayList<CDungeonTracker*> m_dungeonTrackers; // +0xa40
    TArrayList<std::wstring> m_loadedModNames; // +0xa58
};

#endif
