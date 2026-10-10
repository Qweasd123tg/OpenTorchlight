#ifndef PLAYER_H
#define PLAYER_H

#include <OgreCamera.h>
#include <vector>
class CLevelState;
#include "Character.h"

// Partial: Player.cpp is not recovered. Virtual overrides follow the original
// vtable; the unexamined player fields retain their original extent.
class CPlayer : public CCharacter
{
friend class CGameClient;
public:
    std::wstring getPlayerClassName();
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
    void setLeftMappedFunctionSkill(unsigned int,long long);
    void setMappedFunctionSkill(unsigned int,long long);
    bool addWaypoint(std::wstring dungeon, int depth);
    void soldItem(CEquipment*);
    void incrementJournalStatistic(EJournalStatistic,int);
    void attemptToStopPlayerSkill(bool force);
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

private:
    unsigned char m_gap720[0x780-0x720];
    long long m_itemLinks[2];
    unsigned char m_gap790[1];
    unsigned char m_cheatMarker;
    unsigned char m_gap792[6];
    std::vector<CLevelState*> m_savedLevels;
    unsigned char m_gap7b0[0x7dc-0x7b0];
    int m_journalStats[43];
    std::wstring m_manaGraph;
    std::wstring m_hpGraph;
    std::wstring m_statPointsGraph;
    std::wstring m_skillPointsGraph;
    std::wstring m_famePointsGraph;
    long long m_skillMap[10];
    long long m_leftSkillMap[10];
    long long m_functionSkills[12];
    long long m_leftFunctionSkills[12];
    unsigned char m_gapa10[0xa70-0xa10];
};

#endif
