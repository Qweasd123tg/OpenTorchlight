#ifndef QUESTUNITDATA_H
#define QUESTUNITDATA_H

#include <OgreVector3.h>
#include <stdio.h>
#include <string>

#include "BaseUnit.h"
#include "DataGroup.h"
#include "Level.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CQuest;

class CQuestUnitData : public CRunicCore
{
public:
    virtual ~CQuestUnitData();

    int getDungeonFloorActiveOn();
    int getDeepestFloor();
    bool isComplete(bool includeChildren);
    void save(_IO_FILE* file);

    CBaseUnit* spawnUnit(CResourceManager* resourceManager,
                         const Ogre::Vector3& position);
    void spawnChildrenUnits(CResourceManager* resourceManager,
                            const Ogre::Vector3& position);
    CPositionableObject* createUnit(CLevel* level);

    CQuestUnitData(CQuest* quest);

    bool getIsRandom();
    bool parseDataGroup(CDataGroup* dataGroup, CDataGroup* questDataGroup);
    void cleanUpForQuestRemoveall(bool removeAll);
    CDataGroup* getSpawnClassUnitDataLookingFor();
    CDataGroup* getBaseUnitDataGroup();

    unsigned long unitPickedUp(CBaseUnit* unit);
    bool unitDropped(CBaseUnit* unit);
    bool unitDefeated(CBaseUnit* unit);
    bool unitInteracted(CBaseUnit* unit);

    void populate(CLevel* level);
    void reinitialize(bool resolveUnitData);
    void load(_IO_FILE* file, int version);
    std::wstring getUnitName();

    int m_questUnitDataId;
    unsigned char m_gap14[4] __attribute__((aligned(4)));

    CQuest* m_pQuest;

    CDataGroup* m_pBaseUnitDataGroup;
    CDataGroup* m_pQuestDataGroup;

    long long m_baseUnitGuid;
    int m_requiredUnitCount;
    int m_currentUnitCount;
    int m_spawnFromUnitType;
    int m_unitType;

    TArrayList<CQuestUnitData*> m_children;

    bool m_completed;
    bool m_makeChampion;
    bool m_removeFromInventory;
    bool m_createUnit;
    bool m_removeOnlyQuestItems;

    unsigned char m_gap65[3];

    std::wstring m_displayName;
    std::wstring m_uniqueUnitName;
    std::wstring m_spawnClass;
    std::wstring m_itemName;
    std::wstring m_monsterName;
    std::wstring m_unitTypeName;
    std::wstring m_spawnFromUnitTypeName;

    int m_relativeFloor;
    int m_specificFloor;
    int m_minCount;
    int m_maxCount;
    int m_spawnClassPreset;
    int m_unitSearchMode;

    bool m_neverDestroy;
    bool m_trackUnitEvents;

    unsigned char m_gapBA[6];

    std::wstring m_generatedChampionName;
};

#endif
