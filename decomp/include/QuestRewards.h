#ifndef QUESTREWARDS_H
#define QUESTREWARDS_H

#include "DataGroup.h"
#include "RunicCore.h"
#include "TArrayList.h"

#include <string>

class CBaseUnit;
class CQuest;
class CSpawnClass;
class CUnitCreateRef;

class CQuestRewards : public CRunicCore
{
public:
    virtual ~CQuestRewards();

    void destroyIcons();
    void rewardPlayer();
    CQuestRewards(CQuest *pQuest);
    long long parseRewardTag(CDataGroup *pDataGroup);
    void calculateRewards();
    TArrayList<CBaseUnit> *getRewardItems();
    std::wstring getRewardString();
    void reInitializeRewards();

    CQuest *m_pQuest;
    float m_fExperience;
    float m_fGold;
    float m_fFame;
    unsigned char m_Reserved24[4] __attribute__((aligned(4)));
    CSpawnClass *m_pSpawnClass;
    TArrayList<CUnitCreateRef> m_unitRewardReferences;
    float m_fExperienceMinPercent;
    float m_fExperienceMaxPercent;
    float m_fGoldMinPercent;
    float m_fGoldMaxPercent;
    float m_fFameMinPercent;
    float m_fFameMaxPercent;
    TArrayList<CBaseUnit> m_rewardItems;
};

#endif
