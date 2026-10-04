#ifndef SPAWNCLASSDATA_H
#define SPAWNCLASSDATA_H

#include <string>
#include "Character.h"
#include "DataGroup.h"
#include "Graph.h"
#include "Randomizer.h"
#include "RunicCore.h"
#include "SpawnClass.h"
#include "TArrayList.h"

class CSpawnClassData : public CRunicCore
{
public:
    virtual ~CSpawnClassData();

    void addSpawnClass(CSpawnClass* spawnClass);
    int getUnitObjectCount();
    void addUnitDataObject(CDataGroup* dataGroup);
    void addUnitDataObjects(TArrayList<CDataGroup*>& dataGroups);
    void fillRandomizer(CCharacter* character, int minimumLevel, int levelOffset,
                        int rarityOverride, int flags);
    unsigned long calculateChoices(CCharacter* character, int minimumLevel,
                                   int levelOffset, int rarityOverride, int flags);

    CSpawnClassData(const std::wstring& name);

    void rollSpawnClassData(TArrayList<CDataGroup*>& dataGroups,
                            TArrayList<bool>* primaryChoices,
                            CCharacter* character,
                            CCharacter* rollingCharacter,
                            int minimumLevel, int levelOffset,
                            int bonusPercentage, int rarityOverride,
                            int flags);

    std::wstring m_sName;
    TArrayList<CDataGroup*> m_lUnitDataObjects;

    int m_iMinimumLevel;
    int m_iLevelOffset;
    int m_iRarityOverride;
    int m_iFlags;

    CRandomizer* m_pRandomizer;
    CRandomizer* m_pType1Randomizer;
    CRandomizer* m_pType2Randomizer;

    CSpawnClass* m_pSpawnClass;
    bool m_bIsInitialized;
    unsigned char m_abPadding61[7];

    TArrayList<int> m_lPrimaryRandomizerIDs;

    CGraph* m_pMinimumLevelGraph;
    CGraph* m_pMaximumLevelGraph;
};

#endif
